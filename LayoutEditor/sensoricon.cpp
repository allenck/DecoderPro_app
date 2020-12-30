#include "sensoricon.h"
#include "instancemanager.h"
#include "layouteditor.h"
#include "positionablepopuputil.h"
#include "coordinateedit.h"
#include "sensortextedit.h"
#include "sensorpopuputil.h"
#include "lnsensor.h"
#include "tableitempanel.h"
#include "picklistmodel.h"
#include "iconadder.h"
#include <QStatusBar>
#include "displayframe.h"
#include "jmricolorchooser.h"

//SensorIcon::SensorIcon(QObject *parent) :
//    PositionableIcon(parent)
//{
//}
/**
 * An icon to display a status of a Sensor.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author PeteCressman Copyright (C) 2010, 2011
 * @version $Revision: 22576 $
 */

///*public*/ class SensorIcon extends PositionableIcon implements java.beans.PropertyChangeListener {



/*public*/ SensorIcon::SensorIcon(Editor* editor) : PositionableIcon(editor, (Positionable*)this)
{
    this->editor = editor;
    common();
    // super ctor call to make sure this is an icon label
    setIcon("none", new NamedIcon(":/resources/icons/smallschematics/tracksegments/circuit-error.gif",
                        ":/resources/icons/smallschematics/tracksegments/circuit-error.gif"));
    setPopupUtility(new SensorPopupUtil((Positionable*)this, this));

}

/*public*/ SensorIcon::SensorIcon(NamedIcon* s, Editor* editor) : PositionableIcon(s,editor, (Positionable*)this)
{
    // super ctor call to make sure this is an icon label
    //super(s, editor);
    common();
    PositionableIcon::parent = (Positionable*)this;
    setOpaque(false);
    this->editor = editor;
    _control = true;
    debug = log->isDebugEnabled();
    setPopupUtility(new SensorPopupUtil((Positionable*)this, this));
    //_namedIcon = s;
    setIcon("none",s);
}

/*public*/ SensorIcon::SensorIcon(QString s, Editor* editor) : PositionableIcon(s, editor, (Positionable*)this)
{
    //super(s, editor);
    this->editor = editor;
    common();
    _control = true;
    debug = log->isDebugEnabled();
    displayState(sensorState());
    setPopupUtility(new SensorPopupUtil((Positionable*)this, this));
}
void SensorIcon::common()
{
 setObjectName("SensorIcon");
 log = new Logger("SensorIcon", this);
 debug = false;
 momentary = false;
 textColorActive = QColor(Qt::black);
 textColorInActive = QColor(Qt::black);
 textColorUnknown = QColor(Qt::black);
 textColorInconsistent = QColor(Qt::black);
 backgroundColorActive = QColor();
 backgroundColorInActive = QColor();
 backgroundColorUnknown = QColor();
 backgroundColorInconsistent = QColor();
 flashStateOn = -1;
 flashStateOff = -1;
 flashon = false;
 namedSensor = NULL;
 _iconMap = NULL;
 _state2nameMap = new QHash <int, QString>();
 _name2stateMap = new QHash <QString, int>();
 makeIconMap();
 JLabel::hide();
}

//@Override
/*public*/ Positionable* SensorIcon::deepClone() {
    SensorIcon* pos = new SensorIcon(_editor);
    return finishClone((Positionable*)pos);
}

//@Override
/*public*/ Positionable* SensorIcon::finishClone(Positionable* p) {
    SensorIcon* pos = (SensorIcon*)p;
    pos->setSensor(getNamedSensor()->getName());
    pos->makeIconMap();
    pos->_iconMap = cloneMap(_iconMap, pos);
    pos->setMomentary(getMomentary());
    pos->originalText = originalText;
    pos->setText(getText());
//    pos->setIcon("",NULL);
    pos->_namedIcon = NULL;
    pos->activeText = activeText;
    pos->inactiveText = inactiveText;
    pos->inconsistentText = inconsistentText;
    pos->unknownText = unknownText;
    pos->textColorInconsistent = textColorInconsistent;
    pos->textColorUnknown = textColorUnknown;
    pos->textColorInActive = textColorInActive;
    pos->textColorActive = textColorActive;
    pos->backgroundColorInActive = backgroundColorInActive;
    pos->backgroundColorActive = backgroundColorActive;
    pos->backgroundColorUnknown = backgroundColorUnknown;
    pos->backgroundColorInconsistent = backgroundColorInconsistent;
    return  PositionableIcon::finishClone((Positionable*)pos);
}


/**
 * Attached a named sensor to this display item
 * @param pName System/user name to lookup the sensor object
 */
/*public*/ void SensorIcon::setSensor(QString pName)
{
 SensorManager* manager = NULL;
 if ((manager = InstanceManager::sensorManagerInstance())!=NULL)
 {
  //manager = (SensorManager*)editor->lnSensorManager;
  Sensor* sensor = NULL;
  //SensorManager* manager = InstanceManager::sensorManagerInstance();
//  if(InstanceManager::managerLists->contains("LnSensorManager"))
//   sensor = ((LnSensorManager*)manager)->provideSensor(pName);
//  else
  //sensor = ((InternalSensorManager*)manager)->provideSensor(pName);
  sensor = ((ProxySensorManager*)manager)->provideSensor(pName);
  if (sensor != NULL)
  {
   setSensor(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, sensor));
   //   if(!connect(((LnSensor*)sensor), SIGNAL(propertyChange(QString,int,int)), this, SLOT(propertyChange(QString,int,int))))
//   if(!connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*))))
//       qDebug()<< "connect failed!";
  }
  else
  {
   log->error("Sensor '"+pName+"' not available, icon won't see changes");
  }
 }
 else
 {
  log->error("No SensorManager for this protocol, icon won't see changes");
 }
}
/**
 * Attached a named sensor to this display item
 * @param s the Sensor
 */
/*public*/ void SensorIcon::setSensor(NamedBeanHandle<Sensor*>* s)
{
 if (namedSensor != NULL)
 {
  getSensor()->removePropertyChangeListener((PropertyChangeListener*)this);
 }

 namedSensor = s;
 if (namedSensor != NULL)
 {
  if (_iconMap==NULL)
  {
   makeIconMap();
  }
  displayState(sensorState());
  qDebug() << QString("Sensor state = %1").arg(sensorState());
  getSensor()->addPropertyChangeListener((PropertyChangeListener*)this, s->getName(), "SensorIcon on Panel " /*+ _editor->getName()*/);
  setName(namedSensor->getName());  // Swing name for e.g. tests
 }
 setAttributes();
}

/*private*/ void SensorIcon::setAttributes()
{
 if (isText())
 {
  if (namedSensor!=NULL)
  {
   if (getSensor()->getUserName()!=NULL)
   {
    QString userName=getSensor()->getUserName();
    if (activeText==NULL)
        activeText=userName;
    if (inactiveText==NULL)
        inactiveText = userName;
    if (inconsistentText==NULL)
        inconsistentText=userName;
    if (unknownText==NULL)
        unknownText=userName;
   }
   else
   {
    if (activeText==NULL)
        activeText=tr("Active");
    if (inactiveText==NULL)
        inactiveText = tr("Inactive");
    if (inconsistentText==NULL)
        inconsistentText=tr("Inconsistent");
    if (unknownText==NULL)
        unknownText=tr("Unknown");
   }
  }
  if (activeText==NULL)
  {
   activeText=tr("Active");
   textColorActive=QColor(Qt::red);
  }
  if (inactiveText==NULL)
  {
   inactiveText = tr("Inactive");
   textColorInActive=QColor(Qt::yellow);
  }
  inactiveText = tr("Inactive");
  if (inconsistentText==NULL)
   inconsistentText=tr("Inconsistent");
  if (unknownText==NULL)
   unknownText=tr("Unknown");
  if (!textColorActive.isValid())
   textColorActive=QColor(Qt::red);
  if (!textColorInActive.isValid())
    textColorInActive=QColor(Qt::yellow);
  if (!textColorUnknown.isValid())
    textColorUnknown=QColor(Qt::black);
  if (!textColorInconsistent.isValid())
    textColorInconsistent=QColor(Qt::blue);
  setOpaque(true);
  }
  else
  {
   setOpaque(false);
  }
  displayState(sensorState());
  if (debug) log->debug(tr("setSensor: namedSensor= ")+
                         ((namedSensor==NULL)?QString("NULL"): getNameString())+
                         tr(" isIcon= ")+(isIcon()?QString("yes"):QString("no"))+tr(", isText= ")+(isText()?QString("yes"):QString("no"))+tr(", activeText= ")+activeText);
  if(_editor != NULL)
    _editor->repaint();

}

/*public*/ Sensor* SensorIcon::getSensor() {
    if (namedSensor==NULL) {
        return NULL;
    }
    return namedSensor->getBean();
}

/*public*/ NamedBean* SensorIcon::getNamedBean(){
    return getSensor();
}

/*public*/ NamedBeanHandle<Sensor*>* SensorIcon::getNamedSensor() {
    return namedSensor;
}

void SensorIcon::makeIconMap()
{
 _iconMap = new QMap<QString, NamedIcon*>();
 _name2stateMap = new QHash <QString, int>();
 _name2stateMap->insert("BeanStateUnknown", /*Sensor::UNKNOWN*/0x01);
 _name2stateMap->insert("BeanStateInconsistent", /*(Sensor::INCONSISTENT)*/0x08);
 _name2stateMap->insert("SensorStateActive", /*(Sensor::ACTIVE)*/0x02);
 _name2stateMap->insert("SensorStateInactive", /*(Sensor::INACTIVE)*/0x04);
 _state2nameMap = new QHash <int, QString>();
 _state2nameMap->insert(/*(Sensor::UNKNOWN)*/0x01, "BeanStateUnknown");
 _state2nameMap->insert(/*(Sensor::INCONSISTENT)*/0x08, "BeanStateInconsistent");
 _state2nameMap->insert(/*(Sensor::ACTIVE)*/0x02, "SensorStateActive");
 _state2nameMap->insert(/*(Sensor::INACTIVE)*/0x04, "SensorStateInactive");
}
/**
* Place icon by its bean state name key found in jmri.NamedBeanBundle.properties
* That is, by its localized bean state name
*/
/*public*/ void SensorIcon::setIcon(QString name, NamedIcon* icon)
{
 if (log->isDebugEnabled()) log->debug("setIcon for name \""+name+"\"");
 if (_iconMap==NULL)
 {
  makeIconMap();
 }
 if(_iconMap->value("none") && name != "none")
  _iconMap->remove("none");
 if(_iconMap->value(name))
  _iconMap->remove(name);
 _iconMap->insert(name, icon);
 displayState(sensorState());
 PositionableLabel::setName(name);
}

/**
* Get icon by its localized bean state name
*/
//@Override
/*public*/ NamedIcon* SensorIcon::getIcon(QString state) {
    return _iconMap->value(state);
}
/*public*/ NamedIcon* SensorIcon::getIcon(int state) {
    return _iconMap->value(_state2nameMap->value(state));
}

//@Override
/*public*/ QString SensorIcon::getFamily() {
    return _iconFamily;
}
//@Override
/*public*/ void SensorIcon::setFamily(QString family) {
    _iconFamily = family;
}

/**
 * Get current state of attached sensor
 * @return A state variable from a Sensor, e.g. Sensor.ACTIVE
 */
int SensorIcon::sensorState() {
    if (namedSensor != NULL) return ((AbstractSensor*)getSensor())->getKnownState();
    else return Sensor::UNKNOWN;
}

// update icon as state of turnout changes
///*public*/ void SensorIcon::propertyChange(PropertyChangeEvent* e)
//void SensorIcon::propertyChange(QString propertyName, int old, int now)
void SensorIcon::propertyChange(PropertyChangeEvent* e)
{
 //if (debug) log->debug("property change: "+e->toString());
 if (e->getPropertyName()==("KnownState"))
 {
  int now = (int) e->getNewValue().toInt();
  displayState(now);
  //_editor->repaint();
  //_editor->addToTarget((Positionable*)this);
  updateScene();
 }
}

//@Override
/*public*/ QString SensorIcon::getNameString()
{
 QString name;
 if (namedSensor == NULL) name = tr("<Not connected>");
 else if (getSensor()->getUserName()==NULL)
  name = getSensor()->getSystemName();
 else
  name = getSensor()->getUserName()+" ("+getSensor()->getSystemName()+")";
 return name;
}
#if 0
JCheckBoxMenuItem  momentaryItem = new JCheckBoxMenuItem(Bundle.getMessage("Momentary"));
#endif
/**
 * Pop-up just displays the sensor name
 */
//@Override
/*public*/ bool SensorIcon::showPopUp(QMenu* popup)
{
 if (isEditable())
 {
  if(isIcon())
  {
//    popup.add(new AbstractAction(Bundle.getMessage("ChangeToText")) {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            changeLayoutSensorType();
//        }
//    });
   QAction* changeToTextAction = new QAction(tr("ChangeToText"),this);
   popup->addAction(changeToTextAction);
   connect(changeToTextAction, SIGNAL(triggered()),this, SLOT(changeLayoutSensorType()));
  } else
  {
//    popup.add(new AbstractAction(Bundle.getMessage("ChangeToIcon")) {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            changeLayoutSensorType();
//        }
//    });
   QAction* changeToIconAction = new QAction(tr("ChangeToIcon"), this);
   popup->addAction(changeToIconAction);
   connect(changeToIconAction, SIGNAL(triggered()),this, SLOT(changeLayoutSensorType()));
  }

//   popup.add(momentaryItem);
//   momentaryItem.setSelected (getMomentary());
//   momentaryItem.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                setMomentary(momentaryItem.isSelected());
//            }
//        });
  QAction* momentaryAction = new QAction(tr("Momentary"),this);
  momentaryAction->setCheckable(true);
  momentaryAction->setChecked(getMomentary());
  popup->addAction(momentaryAction);
  connect(momentaryAction, SIGNAL(toggled(bool)), this, SLOT(setMomentary(bool)));
 } else
 {
  if(getPopupUtility()!=NULL)
   getPopupUtility()->setAdditionalViewPopUpMenu(popup);
 }
 return true;
}
/******** popup AbstractAction.actionPerformed method overrides *********/

// overide
//@Override
/*public*/ bool SensorIcon::setTextEditMenu(QMenu* popup)
{
 if (debug) log->debug(tr("setTextEditMenu isIcon=")+(isIcon()?"yes":"no")+", isText="+(isText()?"yes":"no"));
#if 1
 if (isIcon())
 {
  popup->addAction(CoordinateEdit::getTextEditAction((Positionable*)this, "Overlay Icon with Text...",this));
 }
 else
 {
//  popup.add(new AbstractAction(Bundle.getMessage("SetSensorText")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                QString name = getNameQString();
//                sensorTextEdit(name);
//            }
//        });
  QAction* setSensorTextAction = new QAction(tr("Set Text for Sensor States"),this);
  popup->addAction(setSensorTextAction);
  connect(setSensorTextAction, SIGNAL(triggered()), this, SLOT(on_setSensorTextAction()));
  if (isText() && !isIcon())
  {
   QMenu* stateColor = new QMenu(tr("State Colors"));
   stateColor->addMenu(stateMenu(tr("Unknown"), UNKNOWN_FONT_COLOR)); //Unknown
   stateColor->addMenu(stateMenu(tr("Active"), ACTIVE_FONT_COLOR)); //Active
   stateColor->addMenu(stateMenu(tr("Inactive"), INACTIVE_FONT_COLOR)); //Inactive
   stateColor->addMenu(stateMenu(tr("Inconsistent"), INCONSISTENT_FONT_COLOR)); //Inconsistent
   popup->addMenu(stateColor);
  }
 }
#endif
    return true;
}
#if 1 //TODO:
/*public*/ void SensorIcon::sensorTextEdit(QString name)
{
 if (debug) log->debug("make text edit menu");

 SensorTextEdit* f = new SensorTextEdit();

// TODO:    f->addHelpMenu("package.jmri.jmrit.display.SensorTextEdit", true);
 try
 {
  f->initComponents(this, name);
 }
 catch (Exception* ex)
 {
  log->error("Exception: "+ex->getMessage());
 }
 f->setVisible(true);
}
#endif
/**
 * Drive the current state of the display from the state of the
 * turnout.
 */
/*public*/ void SensorIcon::displayState(int state)
{
 if (getNamedSensor() == NULL)
 {
  if(debug) log->debug("Display state "+QString("%1").arg(state)+", disconnected");
 }
 else if (isIcon())
 {
  NamedIcon* icon = getIcon(state);
  if (icon!=NULL)
  {
   PositionableIcon::setIcon(icon);
  }
 }
 else if (isText())
 {
  switch (state)
  {
    case /*Sensor::UNKNOWN*/0x01:
        PositionableIcon::setText(unknownText);
        getPopupUtility()->setBackgroundColor(backgroundColorUnknown);
        getPopupUtility()->setForeground(textColorUnknown);
        break;
    case Sensor::ACTIVE:
        PositionableIcon::setText(activeText);
        getPopupUtility()->setBackgroundColor(backgroundColorActive);
        getPopupUtility()->setForeground(textColorActive);
        break;
    case Sensor::INACTIVE:
        PositionableIcon::setText(inactiveText);
        getPopupUtility()->setBackgroundColor(backgroundColorInActive);
        getPopupUtility()->setForeground(textColorInActive);
        break;
    default:
        PositionableIcon::setText(inconsistentText);
        getPopupUtility()->setBackgroundColor(backgroundColorInconsistent);
        getPopupUtility()->setForeground(textColorInconsistent);
        break;
   }
   rotate(getDegrees());
  }

  updateSize();
  editor->redrawPanel(); // to update track occupancy displayed.
}

/*public*/ bool SensorIcon::setEditItemMenu(QMenu* popup)
{
 //QString txt = java.text.MessageFormat.format(Bundle.getMessage("EditItem"), Bundle.getMessage("Sensor"));
 QString txt = tr("Edit Sensor Item");
 QAction* editSensorItemAction = new QAction(txt, this);

//    popup.add(new AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                editItem();
//            }
//        });
 popup->addAction(editSensorItemAction);
 connect(editSensorItemAction, SIGNAL(triggered()), this, SLOT(on_editSensorItemAction_triggered()));
 return true;
}
void SensorIcon::on_editSensorItemAction_triggered()
{
 editItem();
}

 UpdateActionListener::UpdateActionListener(SensorIcon* parent)
 {
  this->parent = parent;
 }

 /*public*/ void UpdateActionListener::actionPerformed(JActionEvent* /*a*/)
 {
  parent->updateItem();
 }

/*protected*/ void SensorIcon::editItem()
{
 makePaletteFrame(tr("Edit %1 Item").arg("Sensor"));
 _itemPanel = new TableItemPanel(_paletteFrame, "Sensor", _iconFamily,
                                   PickListModel::sensorPickModelInstance(), _editor, this);
//    ActionListener updateAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateItem();
//        }
//    };
 UpdateActionListener* updateAction = new UpdateActionListener(this);
 // duplicate _iconMap map with unscaled and unrotated icons
 QMap<QString, NamedIcon*>* map = new QMap<QString, NamedIcon*>();
 QMapIterator<QString, NamedIcon*> it(*_iconMap);
 while (it.hasNext())
 {
  //Entry<QString, NamedIcon> entry = it.next();
  it.next();
  NamedIcon* oldIcon = it.value();
  NamedIcon* newIcon = cloneIcon(oldIcon, this);
  newIcon->rotate(0, this);
  newIcon->scale(1.0, this);
  newIcon->setRotation(4, this);
  map->insert(it.key(), newIcon);
 }
 _itemPanel->init(updateAction, map);
 _itemPanel->setSelection(getSensor());
 //_paletteFrame->layout()->addWidget(_itemPanel);
 _paletteFrame->setCentralWidget(_itemPanel);
 _paletteFrame->pack();
 _paletteFrame->setVisible(true);
}

void SensorIcon::updateItem()
{
 QMap<QString, NamedIcon*>* oldMap = cloneMap(_iconMap, this);
 setSensor(_itemPanel->getTableSelection()->getSystemName());
 _iconFamily = _itemPanel->getFamilyName();
 QMap <QString, NamedIcon*>* iconMap = _itemPanel->getIconMap();
 if (iconMap!=NULL)
 {
  QMapIterator<QString, NamedIcon*> it(*iconMap);
  while (it.hasNext())
  {
   //Entry<QString, NamedIcon> entry = it.next();
   it.next();
   if (log->isDebugEnabled()) log->debug("key= "+it.key());
   NamedIcon* newIcon = it.value();
   NamedIcon* oldIcon = oldMap->value(it.key());
   newIcon->setLoad(oldIcon->getDegrees(), oldIcon->getScale(), this);
   newIcon->setRotation(oldIcon->getRotation(), this);
   setIcon(it.key(), newIcon);
  }
 }   // otherwise retain current map
//        jmri.jmrit.catalog->ImageIndexLayoutEditor*.checkImageIndex();
 finishItemUpdate(_paletteFrame, _itemPanel);

 invalidate();
}

//@Override
/*public*/ bool SensorIcon::setEditIconMenu(QMenu* popup)
{
 //QString txt = java.text.MessageFormat.format(Bundle.getMessage("EditItem"), Bundle.getMessage("Sensor"));
 QString txt = tr("Edit Sensor Icon");
 QAction* editSensorIconAction = new QAction(txt,this);
// popup->add(new AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                edit();
//            }
//        });
 popup->addAction(editSensorIconAction);
 //connect(editSensorIconAction, SIGNAL(triggered()), this, SLOT(on_setSensorTextAction()));
 connect(editSensorIconAction, SIGNAL(triggered()), this, SLOT(edit()));
    return true;
}

//@Override
/*protected*/ void SensorIcon::edit() /*override*/
{
 makeIconEditorFrame(this, "Sensor", true, NULL);
 QFont f = _iconEditorFrame->font();
 f.setPointSize(8);
 _iconEditorFrame->setFont(f);
 _iconEditor->setPickList(PickListModel::sensorPickModelInstance());
 _iconEditorFrame->statusBar()->setHidden(true);
 _iconEditorFrame->resize(220,800);
 _iconEditorFrame->setMinimumHeight(500);
 QStringListIterator e (_iconMap->keys());
 int i = 0;
 while (e.hasNext())
 {
  QString key =e.next();

 _iconEditor->setIcon(i++, /*_state2nameMap.get(key)*/ key, _iconMap->value(key));
 }
 _iconEditor->makeIconPanel(false);

 // set default icons, then override with this turnout's icons
//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateSensor();
//        }
//    };
 EditActionListener* addIconAction = new EditActionListener(this);

 _iconEditor->complete(addIconAction, true, true, true);
 _iconEditorFrame->pack();

 _iconEditor->setSelection(getSensor());
}

EditActionListener::EditActionListener(SensorIcon *parent)
{
 this->parent = parent;
}

void EditActionListener::actionPerformed(JActionEvent */*a*/ )
{
 parent->updateSensor();
}

void SensorIcon::updateSensor()
{
#if 1 // TODO:
 QMap<QString, NamedIcon*>* oldMap = cloneMap(_iconMap, this);
 setSensor(_iconEditor->getTableSelection()->getDisplayName());
 QMap <QString, NamedIcon*>* iconMap = _iconEditor->getIconMap();

 QMapIterator<QString, NamedIcon*> it(*iconMap);
 while (it.hasNext())
 {
  it.next();
  if (log->isDebugEnabled()) log->debug("key= "+it.key());
  NamedIcon* newIcon = it.value();
  NamedIcon* oldIcon = oldMap->value(it.key());
  newIcon->setLoad(oldIcon->getDegrees(), oldIcon->getScale(), this);
  newIcon->setRotation(oldIcon->getRotation(), this);
  setIcon(it.key(), newIcon);
 }
 _iconEditorFrame->close();
 _iconEditorFrame = NULL;
 _iconEditor = NULL;
 invalidate();
#endif
}

// Original text is used when changing between icon and text, this allows for a undo when reverting back.
/*public*/ void SensorIcon::setOriginalText(QString s) {
    originalText=s;
}
/*public*/ QString SensorIcon::getOriginalText() { return originalText; }

//@Override
/*public*/ void SensorIcon::setText(QString s) {
//    setOpaque(false);
   if ( PositionableIcon::_rotateText && !_icon) {
        return;
    }
    _text = (s!=NULL && s.length()>0);
    PositionableIcon::setText(s);
    updateSize();
}

/*public*/ bool SensorIcon::getMomentary() { return momentary; }
/*public*/ void SensorIcon::setMomentary(bool m) { momentary = m; }

/*public*/ bool SensorIcon::buttonLive()
{
 if (namedSensor==NULL)
 {  // no sensor connected for this protocol
  log->error("No sensor connection, can't process click");
  return false;
 }
 return _editor->getFlag(LayoutEditor::OPTION_CONTROLS, isControlling());
}

//@Override
/*public*/ void SensorIcon::doMousePressed(QGraphicsSceneMouseEvent* e)
{
 if (debug) log->debug(tr("doMousePressed buttonLive=")+(buttonLive()?"yes":"no")+", getMomentary="+(getMomentary()?"yes":"no"));
 bRightButton = e->buttons() & Qt::RightButton;
 if (getMomentary() && buttonLive() /*&& !e.isMetaDown()*/ && /*!e.isAltDown()*/!(e->modifiers()&Qt::AltModifier))
 {
  // this is a momentary button press
  try
  {
   ((AbstractSensor*)getSensor())->setKnownState(Sensor::ACTIVE);
  } catch (JmriException* reason)
  {
   log->warn("Exception setting momentary sensor: "+reason->toString());
  }
 }
 //super.doMousePressed(e);
 PositionableIcon::doMousePressed(e);
}


//@Override
/*public*/ void SensorIcon::doMouseReleased(QGraphicsSceneMouseEvent* e)
{
 if (getMomentary() && buttonLive() /*&& !e.isMetaDown()*/ && /*!e.isAltDown()*/!(e->modifiers()&Qt::AltModifier))
 // this is a momentary button release
 {
  try
  {
   ((AbstractSensor*)getSensor())->setKnownState(Sensor::INACTIVE);
  } catch (JmriException reason)
  {
   log->warn("Exception setting momentary sensor: "+reason.toString());
  }
 }
 //super.doMouseReleased(e);
 PositionableIcon::doMouseReleased(e);
}

//@Override
/*public*/ void SensorIcon::doMouseClicked(QGraphicsSceneMouseEvent* e)
{
 if(e == NULL) return;
 if(bRightButton) return;
 if (buttonLive() && !getMomentary())
 {
  // this button responds to clicks
  if ( /*&& !e.isMetaDown() && !e.isAltDown()*/!(e->modifiers()&Qt::AltModifier) )
  {
   try
   {
    if (((AbstractSensor*)getSensor())->getKnownState()==Sensor::INACTIVE)
        ((AbstractSensor*)getSensor())->setKnownState(Sensor::ACTIVE);
    else
        ((AbstractSensor*)getSensor())->setKnownState(Sensor::INACTIVE);
    qDebug() << tr("sensor %1 state set to %2 (%3)" ).arg(getSensor()->getDisplayName()).arg(((AbstractSensor*)getSensor())->getKnownState()).arg(((AbstractSensor*)getSensor())->getStateName(((AbstractSensor*)getSensor())->getKnownState()));
   } catch (JmriException reason)
   {
    log->warn("Exception flipping sensor: "+reason.toString());
   }
  }
 }
 //super.doMouseClicked(e);
 PositionableIcon::doMouseClicked(e);
}

//@Override
/*public*/ void SensorIcon::dispose() {
    if (namedSensor != NULL) {
//        getSensor()->removePropertyChangeListener(this);
    }
    namedSensor = NULL;
    _iconMap = NULL;
    _name2stateMap = NULL;
    _state2nameMap = NULL;

   PositionableIcon::dispose();
}

/*protected*/ QMap<QString, NamedIcon*>* SensorIcon::cloneMap(QMap<QString, NamedIcon*>* map,
                                                         SensorIcon* pos)
{
 QMap<QString, NamedIcon*>* clone = new QMap<QString, NamedIcon*>();
 if (map!=NULL)
 {
//  Iterator<Entry<Integer, NamedIcon>> it = map.entrySet().iterator();
//  while (it.hasNext())
//  {
//    Entry<Integer, NamedIcon> entry = it.next();
//    clone.put(entry.getKey(), cloneIcon(entry.getValue(), pos));
//    if (pos!=NULL)
//    {
//        pos->setIcon(pos->_state2nameMap.get(entry.getKey()), _iconMap.get(entry.getKey()));
//    }
//  }
  QMapIterator<QString, NamedIcon*> it(*map);
  while(it.hasNext())
  {
   it.next();
   clone->insert(it.key(), cloneIcon(it.value(),pos));
//   if(pos != NULL)
//    pos->setIcon(pos->_state2nameMap->value(it.key()), _iconMap->value(it.key()));
  }
 }
 return clone;
}

/*public*/ void SensorIcon::setTextActive(QColor color){
    textColorActive=color;
    displayState(sensorState());
}

/*public*/ QColor SensorIcon::getTextActive(){
    return textColorActive;
}


/*public*/ void SensorIcon::setTextInActive(QColor color){
    textColorInActive=color;
    displayState(sensorState());
}

/*public*/ QColor SensorIcon::getTextInActive(){
    return textColorInActive;
}

/*public*/ void SensorIcon::setTextUnknown(QColor color){
    textColorUnknown=color;
    displayState(sensorState());
}

/*public*/ QColor SensorIcon::getTextUnknown(){
    return textColorUnknown;
}

/*public*/ void SensorIcon::setTextInconsistent(QColor color){
    textColorInconsistent=color;
    displayState(sensorState());
}

/*public*/ QColor SensorIcon::getTextInconsistent(){
    return textColorInconsistent;
}


/*public*/ void SensorIcon::setBackgroundActive(QColor color){
    if (!color.isValid())
        setOpaque(false);
    else
        setOpaque(true);
    backgroundColorActive=color;
    displayState(sensorState());
}

/*public*/ QColor SensorIcon::getBackgroundActive(){
    return backgroundColorActive;
}


/*public*/ void SensorIcon::setBackgroundInActive(QColor color){
    if (!color.isValid())
        setOpaque(false);
    else
        setOpaque(true);
    backgroundColorInActive=color;
    displayState(sensorState());
}

/*public*/ QColor SensorIcon::getBackgroundInActive(){
    return backgroundColorInActive;
}

/*public*/ void SensorIcon::setBackgroundUnknown(QColor color){
    if (!color.isValid())
        setOpaque(false);
    else
        setOpaque(true);
    backgroundColorUnknown=color;
    displayState(sensorState());
}

/*public*/ QColor SensorIcon::getBackgroundUnknown(){
    return backgroundColorUnknown;
}

/*public*/ void SensorIcon::setBackgroundInconsistent(QColor color){
    if (!color.isValid())
        setOpaque(false);
    else
        setOpaque(true);
    backgroundColorInconsistent=color;
    displayState(sensorState());
}

/*public*/ QColor SensorIcon::getBackgroundInconsistent(){
    return backgroundColorInconsistent;
}


/*public*/ QString SensorIcon::getActiveText() { return activeText; }
/*public*/ void SensorIcon::setActiveText(QString i) {
    activeText = i;
    displayState(sensorState());
}

/*public*/ QString SensorIcon::getInactiveText() { return inactiveText; }
/*public*/ void SensorIcon::setInactiveText(QString i) {
    inactiveText = i;
    displayState(sensorState());
}

/*public*/ QString SensorIcon::getInconsistentText() { return inconsistentText; }
/*public*/ void SensorIcon::setInconsistentText(QString i) {
    inconsistentText = i;
    displayState(sensorState());
}

/*public*/ QString SensorIcon::getUnknownText() { return unknownText; }
/*public*/ void SensorIcon::setUnknownText(QString i) {
    unknownText = i;
    displayState(sensorState());
}

QMenu* SensorIcon::stateMenu(const QString name, int state)
{
 QMenu* menu = new QMenu(name);
 QMenu* colorMenu = new QMenu(tr("Font Color"));
 getPopupUtility()->makeColorMenu(colorMenu, state);
 menu->addMenu(colorMenu);
 colorMenu = new QMenu(tr("Font Background Color"));
 getPopupUtility()->makeColorMenu(colorMenu, state + 1);
 menu->addMenu(colorMenu);
 return menu;
}


void SensorIcon::changeLayoutSensorType()
{
//        NamedBeanHandle <Sensor> handle = getNamedSensor();
 if (isIcon())
 {
  _icon = false;
  _text = true;
  setIcon("", NULL);
  setOriginalText(getUnRotatedText());
  setSuperText(NULL);
  setOpaque(true);
 }
 else if (isText())
 {
  _icon = true;
  _text = (originalText!=NULL && originalText.length()>0);
  setSuperText(getOriginalText());
  setOpaque(false);
 }
 _namedIcon = NULL;
 displayState(sensorState());
//        setAttributes();
//        setSensor(handle);
 int deg = getDegrees();
 rotate(deg);
 if (deg!=0 && _text && !_icon)
 {
  setSuperText(NULL);
 }
}


/*synchronized*/ /*public*/ void SensorIcon::flashSensor(int tps, int state1, int state2){
    if((flashTimer!=NULL) && flashTimer->isActive())
        return;
    //Set the maximum number of state changes to 10 per second
    if(tps >10){
        tps=10;
    } else if (tps<=0) {
        return;
    }
    if((_state2nameMap->value(state1)==NULL) || _state2nameMap->value(state2)==NULL){
        log->error("one or other of the states passed for flash is NULL");
        return;
    } else if (state1==state2){
        log->info("Both states to flash between are the same, therefore no flashing will occur");
        return;
    }
    int interval = (1000/tps)/2;
    flashStateOn = state1;
    flashStateOff = state2;
//    if(taskPerformer==NULL){
//        taskPerformer = new ActionListener() {
//              /*public*/ void actionPerformed(ActionEvent evt) {
//                  if(flashon){
//                    flashon=false;
//                    displayState(flashStateOn);
//                  } else {
//                    flashon=true;
//                    displayState(flashStateOff);
//                  }
//              }
//        };
//    }
    flashTimer = new QTimer();
    flashTimer->start(interval);
}
void SensorIcon::on_timeout()
{
 if(flashon)
 {
  flashon=false;
   displayState(flashStateOn);
   updateScene();
 }
 else
 {
   flashon=true;
   displayState(flashStateOff);
   updateScene();
 }
}
/*synchronized*/ /*public*/ void SensorIcon::stopFlash()
{
 if(flashTimer!=NULL)
     flashTimer->stop();
 displayState(sensorState());
 updateScene();
}
#if 0 // See class SensorPopupUtil
class SensorPopupUtil extends PositionablePopupUtil {

    SensorPopupUtil(Positionable parent, javax.swing.JComponent textComp) {
        super(parent, textComp);
    }
    @Override
    /*public*/ void setTextJustificationMenu(JPopupMenu popup) {
        if (isText()) { super.setTextJustificationMenu(popup); }
    }
    @Override
    /*public*/ void setTextOrientationMenu(JPopupMenu popup) {
        if (isText()) { super.setTextOrientationMenu(popup); }
    }
    @Override
    /*public*/ void setFixedTextMenu(JPopupMenu popup) {
        if (isText()) { super.setFixedTextMenu(popup); }
    }
    @Override
    /*public*/ void setTextMarginMenu(JPopupMenu popup) {
        if (isText()) { super.setTextMarginMenu(popup); }
    }
    @Override
    /*public*/ void setTextBorderMenu(JPopupMenu popup) {
        if (isText()) { super.setTextBorderMenu(popup); }
    }
    @Override
    /*public*/ void setTextFontMenu(JPopupMenu popup) {
        if (isText()) { super.setTextFontMenu(popup); }
    }

    @Override
    @SuppressWarnings("fallthrough")
    /*protected*/ void makeColorMenu(JMenu colorMenu, int type) {
        ButtonGroup buttonGrp = new ButtonGroup();
        addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("Black"), Color.black, type);
        addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("DarkGray"),Color.darkGray, type);
        addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("Gray"),Color.gray, type);
        addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("LightGray"),Color.lightGray, type);
        addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("White"),Color.white, type);
        addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("Red"),Color.red, type);
        addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("Orange"),Color.orange, type);
        addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("Yellow"),Color.yellow, type);
        addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("Green"),Color.green, type);
        addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("Blue"),Color.blue, type);
        addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("Magenta"),Color.magenta, type);
        switch(type){
            case UNKOWN_BACKGROUND_COLOR :
            case ACTIVE_BACKGROUND_COLOR :
            case INACTIVE_BACKGROUND_COLOR :
            case INCONSISTENT_BACKGROUND_COLOR : addColorMenuEntry(colorMenu, buttonGrp, Bundle.getMessage("Clear"), NULL, type);
        }
    }

    @Override
    /*protected*/ void addColorMenuEntry(JMenu menu, ButtonGroup colorButtonGroup,
                           final QString name, final Color color, final int colorType) {
        ActionListener a = new ActionListener() {
            //final QString desiredName = name;
            final Color desiredColor = color;
            /*public*/ void actionPerformed(ActionEvent e) {
                switch (colorType){
                    case FONT_COLOR :
                        setForeground(desiredColor);
                        break;
                    case BACKGROUND_COLOR :
                        if(color==NULL){
                            setOpaque(false);
                            //We need to force a redisplay when going to clear as the area
                            //doesn't always go transparent on the first click.
                            java.awt.Point p = getLocation();
                            int w = getWidth();
                            int h = getHeight();
                            java.awt.Container parent = getParent();
                            // force redisplay
                            parent.validate();
                            parent.repaint(p.x,p.y,w,h);
                        }
                        else
                            setBackgroundColor(desiredColor);
                        break;
                    case BORDER_COLOR :
                        setBorderColor(desiredColor);
                        break;
                    case UNKOWN_FONT_COLOR :
                        setTextUnknown(desiredColor);
                        break;
                    case UNKOWN_BACKGROUND_COLOR :
                        setBackgroundUnknown(desiredColor);
                        break;
                    case ACTIVE_FONT_COLOR :
                        setTextActive(desiredColor);
                        break;
                    case ACTIVE_BACKGROUND_COLOR :
                        setBackgroundActive(desiredColor);
                        break;
                    case INACTIVE_FONT_COLOR :
                        setTextInActive(desiredColor);
                        break;
                    case INACTIVE_BACKGROUND_COLOR :
                        setBackgroundInActive(desiredColor);
                        break;
                    case INCONSISTENT_FONT_COLOR :
                        setTextInconsistent(desiredColor);
                        break;
                    case INCONSISTENT_BACKGROUND_COLOR :
                        setBackgroundInconsistent(desiredColor);
                        break;
                    default : break;
                }
            }
        };
        JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
        r.addActionListener(a);

        switch (colorType) {
            case FONT_COLOR:
                setColorButton(getForeground(), color, r);
                break;
            case BACKGROUND_COLOR:
                setColorButton(getBackground(), color, r);
                break;
            case BORDER_COLOR:
                setColorButton(getBorderColor(), color, r);
                break;
            case UNKOWN_FONT_COLOR:
                setColorButton(getTextUnknown(), color, r);
                break;
            case UNKOWN_BACKGROUND_COLOR:
                setColorButton(getBackgroundUnknown(), color, r);
                break;
            case ACTIVE_FONT_COLOR:
                setColorButton(getTextActive(), color, r);
                break;
            case ACTIVE_BACKGROUND_COLOR:
                setColorButton(getBackgroundActive(), color, r);
                break;
            case INACTIVE_FONT_COLOR:
                setColorButton(getTextInActive(), color, r);
                break;
            case INACTIVE_BACKGROUND_COLOR:
                setColorButton(getBackgroundInActive(), color, r);
                break;
            case INCONSISTENT_FONT_COLOR:
                setColorButton(getTextInconsistent(), color, r);
                break;
            case INCONSISTENT_BACKGROUND_COLOR:
                setColorButton(getBackgroundInconsistent(), color, r);
                break;
            default : break;
        }
        colorButtonGroup.add(r);
        menu.add(r);
    }
}
#endif
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SensorIcon.class.getName());
//}
void SensorIcon::on_setSensorTextAction()
{
 QString name = getNameString();
 sensorTextEdit(name);
}
/*public*/ bool SensorIcon::updateScene() // TODO: this function not in Java
{
 QGraphicsPixmapItem* item = NULL;
 QString state = "BeanStateUnknown";
 int iState = 0;
 if(getSensor() != NULL)
  iState=((AbstractSensor*)getSensor())->getKnownState();
 state = _state2nameMap->value(iState);
 if(state == "")
  return false; // should not happen!

 if(_itemGroup != NULL)
 {
  QList<QGraphicsItem*> itemList = _itemGroup->childItems();
  foreach(QGraphicsItem* it, itemList)
  {
   if(qgraphicsitem_cast<QGraphicsPixmapItem*>(it) != NULL)
   {
    _itemGroup->setRotation(_itemGroup->rotation() - currRotation);
    item = qgraphicsitem_cast<QGraphicsPixmapItem*>(it);
   }
  }
 }
 else
  _itemGroup = new MyGraphicsItemGroup();

 QPixmap pixmap = QPixmap::fromImage(getIcon(iState)->getImage());
 if(item != NULL)
  item->setPixmap(pixmap);
 else
  item = new QGraphicsPixmapItem(pixmap,_itemGroup);
 //item->setPos(getX(), getY());
 if(showToolTip()) item->setToolTip(getToolTip());
 //_itemGroup->addToGroup(item);
 _itemGroup->setPos(((Positionable*)this)->getX(), ((Positionable*)this)->getY());
 //if(showTooltip()) _itemGroup->setToolTip(getTooltip());
 //int degrees = getDegrees() + getIcon()->getRotation();
 currRotation = getIcon(iState)->getRotation()*90;
 if((getDegrees()+ currRotation) != 0)
 {
  //l->item->rotate(l->getDegrees());
  QRectF bnd = _itemGroup->boundingRect();
  QPointF center = bnd.center();
  _itemGroup->setTransformOriginPoint(center);
  _itemGroup->setRotation(item->rotation()+ currRotation);
 }
 _itemGroup->setZValue(getDisplayLevel());
 _itemGroup->update();
 return true;
}
