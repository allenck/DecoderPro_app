#include "multisensoricon.h"
#include "editor.h"
#include "namedicon.h"
#include "instancemanager.h"
#include "abstractsensor.h"
#include "picklistmodel.h"
#include "jmrijframe.h"
#include <QMessageBox>
#include "namedbean.h"
#include "multisensoriconadder.h"
#include "multisensoritempanel.h"

//MultiSensorIcon::MultiSensorIcon(QObject *parent) :
//    PositionableLabel(parent)
//{
//}
/**
 * An icon to display a status of set of Sensors.
 *<P>
 * Each sensor has an associated image.  Normally, only one
 * sensor will be active at a time, and in that case the
 * associated image will be shown.  If more than one is active,
 * one of the corresponding images will be shown, but which one is
 * not guaranteed.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2007
 * @version $Revision: 22576 $
 */

///*public*/ class MultiSensorIcon extends PositionableLabel implements java.beans.PropertyChangeListener {

    /*public*/ MultiSensorIcon::MultiSensorIcon(Editor* editor, QObject *parent): PositionableLabel(new NamedIcon("program:resources/icons/smallschematics/tracksegments/circuit-error.gif",  "program:/resources/icons/smallschematics/tracksegments/circuit-error.gif"), editor, (Positionable*)parent)
{
        // super ctor call to make sure this is an icon label
        //super(new NamedIcon("resources/icons/smallschematics/tracksegments/circuit-error.gif",
//                            "resources/icons/smallschematics/tracksegments/circuit-error.gif"), editor);
 updown = false;
 entries = new QList<MultiSensorIcon::Entry*>();
 displaying = -1;
 setLevel(Editor::SENSORS);

 // display icons
 inactiveName = "program:resources/icons/USS/plate/levers/l-inactive.gif";
 inactive = new NamedIcon(inactiveName, inactiveName);
 inconsistentName = "program:resources/icons/USS/plate/levers/l-inconsistent.gif";
 inconsistent = new NamedIcon(inconsistentName, inconsistentName);
 unknownName = "program:resources/icons/USS/plate/levers/l-unknown.gif";
 unknown = new NamedIcon(unknownName, unknownName);
 log = new Logger("MultiSensorIcon");

 _control = true;
 displayState();
 setPopupUtility(NULL);
}
MultiSensorIconEntry::MultiSensorIconEntry(NamedIcon *icon, NamedBeanHandle<Sensor *> *namedSensor)
{
 this->icon = icon;
 this->namedSensor = namedSensor;
}
    // if not updown, is rightleft
/*public*/ void MultiSensorIcon::setUpDown(bool b) { updown = b; }
/*public*/ bool MultiSensorIcon::getUpDown() { return updown; }


/*public*/ Positionable* MultiSensorIcon::deepClone() {
    MultiSensorIcon* pos = new MultiSensorIcon(_editor);
    return finishClone((Positionable*)pos);
}

/*public*/ Positionable* MultiSensorIcon::finishClone(Positionable* p) {
    MultiSensorIcon* pos = (MultiSensorIcon*)p;
    pos->setInactiveIcon(cloneIcon(getInactiveIcon(), pos));
    pos->setInconsistentIcon(cloneIcon(getInconsistentIcon(), pos));
    pos->setUnknownIcon(cloneIcon(getUnknownIcon(), pos));
    for (int i=0; i<entries->size(); i++) {
        pos->addEntry(getSensorName(i), cloneIcon(getSensorIcon(i), pos));
    }
    return PositionableLabel::finishClone((Positionable*)pos);
}

/*public*/ void MultiSensorIcon::addEntry(NamedBeanHandle<Sensor*>* sensor, NamedIcon* icon) {
    if (sensor != NULL) {
        if (log->isDebugEnabled()) log->debug("addEntry: sensor= "+sensor->getName());
        /*MultiSensorIcon::*/Entry* e = new /*MultiSensorIcon::*/Entry(icon,sensor);
        sensor->getBean()->addPropertyChangeListener((PropertyChangeListener*)this, sensor->getName(), "MultiSensor Icon");
        e->namedSensor = sensor;
        e->icon = icon;
        entries->append(e);
        displayState();
    } else {
        log->error("Sensor not available, icon won't see changes");
    }
}

/*public*/ void MultiSensorIcon::addEntry(QString pName, NamedIcon* icon)
{
 NamedBeanHandle<Sensor*>* sensor;
 if (InstanceManager::sensorManagerInstance()!=NULL)
 {
  sensor = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(pName));
 }
 else
 {
  log->error("No SensorManager for this protocol, icon won't see changes");
 }
 addEntry(sensor, icon);
}

/*public*/ int MultiSensorIcon::getNumEntries() { return entries->size(); }

/*public*/ QList<Sensor*> MultiSensorIcon::getSensors() {
    QList<Sensor*> list = QList<Sensor*>();//new ArrayList<>(getNumEntries());
    for (Entry* handle : *entries) {
        list.append(handle->namedSensor->getBean());
    }
    return list;
}

/*public*/ QString MultiSensorIcon::getSensorName(int i) {
    return entries->at(i)->namedSensor->getName();
}
/*public*/ NamedIcon* MultiSensorIcon::getSensorIcon(int i) {
    return entries->at(i)->icon;
}
/*public*/ QString MultiSensorIcon::getFamily() {
    return _iconFamily;
}
/*public*/ void MultiSensorIcon::setFamily(QString family)
{
 _iconFamily = family;
}

/*public*/ NamedIcon* MultiSensorIcon::getInactiveIcon() { return inactive; }
/*public*/ void MultiSensorIcon::setInactiveIcon(NamedIcon* i)
{
 inactive = i;
}

/*public*/ NamedIcon* MultiSensorIcon::getInconsistentIcon() { return inconsistent; }
/*public*/ void MultiSensorIcon::setInconsistentIcon(NamedIcon* i)
{
 inconsistent = i;
}

/*public*/ NamedIcon* MultiSensorIcon::getUnknownIcon() { return unknown; }
/*public*/ void MultiSensorIcon::setUnknownIcon(NamedIcon* i)
{
 unknown = i;
}

// update icon as state of turnout changes
/*public*/ void MultiSensorIcon::propertyChange(PropertyChangeEvent* e)
{
 if (log->isDebugEnabled())
 {
  QString prop = e->getPropertyName();
  Sensor* sen = (Sensor*)e->getSource();
  if (log->isDebugEnabled()) log->debug("property change("+prop+") Sensor state= "+
              QString::number(((AbstractSensor*)sen)->getKnownState())+" - old= "+e->getOldValue().toString()+", New= "+e->getNewValue().toString());
 }
 if (e->getPropertyName()==("KnownState"))
 {
  displayState();
  //_editor.repaint();
  //_editor->addToTarget((Positionable*)this);
  updateScene();
  _itemGroup->setName("MultiSensorItem");
 }
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*public*/ QString MultiSensorIcon::getNameString()
{
  QString name = "";
  if ((entries == NULL) || (entries->size() < 1))
      name = tr("<Not connected>");
  else
  {
   name = entries->at(0)->namedSensor->getName();
   for (int i = 1; i<entries->size(); i++) {
       name += ","+entries->at(i)->namedSensor->getName();
   }
  }
  return name;
}

/******** popup AbstractAction.actionPerformed method overrides *********/

/*protected*/ void MultiSensorIcon::rotateOrthogonal()
{
 for (int i = 0; i<entries->size(); i++)
 {
  NamedIcon* icon = entries->at(i)->icon;
  icon->setRotation(icon->getRotation()+1, this);
 }
 inactive->setRotation(inactive->getRotation()+1, this);
 unknown->setRotation(unknown->getRotation()+1, this);
 inconsistent->setRotation(inconsistent->getRotation()+1, this);
 displayState();
 // bug fix, must repaint icons that have same width and height
 //repaint();
 //_editor->addToTarget((Positionable*)this);
 updateScene();
}


/*public*/ void MultiSensorIcon::setScale(double s) {
    for (int i = 0; i<entries->size(); i++) {
        NamedIcon* icon = entries->at(i)->icon;
        icon->scale(s, this);
    }
    inactive->scale(s, this);
    unknown->scale(s, this);
    inconsistent->scale(s, this);
    displayState();
}

/*public*/ void MultiSensorIcon::rotate(int deg) {
    for (int i = 0; i<entries->size(); i++) {
        NamedIcon* icon = entries->at(i)->icon;
        icon->rotate(deg, this);
    }
    inactive->rotate(deg, this);
    unknown->rotate(deg, this);
    inconsistent->rotate(deg, this);
    displayState();
}

/*public*/ bool MultiSensorIcon::setEditItemMenu(QMenu* popup) // Called by ControlPanelEditor
{
    //QString txt = java.text.MessageFormat.format(Bundle.getMessage("EditItem"), Bundle.getMessage("MultiSensor"));
 QString txt = tr("Edit %1 Icon").arg(tr("MultiSensor"));
//    popup.add(new javax.swing.AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                editItem();
//            }
//        });
 QAction* act = new QAction(txt, this);
 popup->addAction(act);
 connect(act, SIGNAL(triggered()), this, SLOT(editItem()));
 return true;
}


/*protected*/ void MultiSensorIcon::editItem()
{
#if 1
 makePaletteFrame(tr("Edit %1 Item").arg(tr("MultiSensor")));
 _itemPanel = new MultiSensorItemPanel(_paletteFrame, "MultiSensor", _iconFamily,
                                PickListModel::multiSensorPickModelInstance(), _editor);
//    ActionListener updateAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateItem();
//        }
//    };
 UIActionListener* updateAction = new UIActionListener(this);
 //connect(updateAction, SIGNAL(triggered()), this, SLOT(updateItem()));
 // duplicate _iconMap map with unscaled and unrotated icons
 QMap<QString, NamedIcon*>* map = new QMap<QString, NamedIcon*>();
 map->insert("SensorStateInactive", inactive);
 map->insert("BeanStateInconsistent", inconsistent);
 map->insert("BeanStateUnknown", unknown);
 for (int i = 0; i<entries->size(); i++)
 {
  map->insert(MultiSensorItemPanel::POSITION.at(i), entries->at(i)->icon);
 }
 _itemPanel->init(updateAction, map);
 for (int i = 0; i<entries->size(); i++)
 {
  _itemPanel->setSelection(entries->at(i)->namedSensor->getBean());
 }
 _itemPanel->setUpDown(getUpDown());
 _paletteFrame->layout()->addWidget(_itemPanel);
 _paletteFrame->pack();
 _paletteFrame->setVisible(true);
#endif
}

void MultiSensorIcon::updateItem()
{
#if 1
 QMap <QString, NamedIcon*>* iconMap = _itemPanel->getIconMap();
 QVector<NamedBean*> selections = _itemPanel->getTableSelections();
 QVector<int> positions = _itemPanel->getPositions();
 if (selections.isEmpty()) {
//        JOptionPane.showMessageDialog(_paletteFrame,
//                java.text.MessageFormat.format(
//                    ItemPalette.rbp.getString("NeedPosition"), positions.length),
//                    Bundle.getMessage("warnTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(_paletteFrame, tr("Warning"), tr("Multisensor needs %1 positions.  Select more rows from the table.").arg(positions.length()));
     return;
 }
 if (iconMap!=NULL)
 {
  setInactiveIcon(new NamedIcon(iconMap->value("SensorStateInactive")));
  setInconsistentIcon(new NamedIcon(iconMap->value("BeanStateInconsistent")));
  setUnknownIcon(new NamedIcon(iconMap->value("BeanStateUnknown")));
 }
 else
 {
  return;
 }
 entries = new QList<Entry*>();//selections->size());
 for (int i=0; i<selections.size(); i++)
 {
  addEntry(selections.at(i)->getDisplayName(), new NamedIcon(iconMap->value(MultiSensorItemPanel::POSITION.at(i))));
 }
 _iconFamily = _itemPanel->getFamilyName();
 _itemPanel->clearSelections();
 setUpDown(_itemPanel->getUpDown());
//        jmri.jmrit.catalog->ImageIndexEditor.checkImageIndex();
 finishItemUpdate(_paletteFrame, _itemPanel);

#endif
}

/*public*/ bool MultiSensorIcon::setEditIconMenu(QMenu* popup)
{
    //QString txt = java.text.MessageFormat.format(Bundle.getMessage("EditItem"), Bundle.getMessage("MultiSensor"));
 QString txt = tr("Edit %1 Icon").arg(tr("MultiSensor"));
//    popup.add(new AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                edit();
//            }
//        });
 QAction* act = new QAction(txt, this);
 popup->addAction(act);
 connect(act, SIGNAL(triggered()), this, SLOT(edit()));
 return true;
}
/*protected*/ void MultiSensorIcon::edit() {
#if 1
 MultiSensorIconAdder* iconEditor = new MultiSensorIconAdder("MultiSensor");
 makeIconEditorFrame(this, "MultiSensor", false, iconEditor);
 _iconEditor->setPickList(PickListModel::sensorPickModelInstance());
 _iconEditor->setIcon(2, "SensorStateInactive", inactive);
 _iconEditor->setIcon(0, "BeanStateInconsistent", inconsistent);
 _iconEditor->setIcon(1, "BeanStateUnknown", unknown);
 ((MultiSensorIconAdder*)_iconEditor)->setMultiIcon(entries);
 _iconEditor->makeIconPanel(false);

//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateSensor();
//        }
//    };
 MSIAddIconActionListener* addIconAction = new MSIAddIconActionListener(this);
 //connect(addIconAction, SIGNAL(triggered()), this, SLOT(updateSensor()));
 iconEditor->complete(addIconAction, true, true, true);
#else
    AddPanelIconDialog* dlg = new AddPanelIconDialog("MultiSensor", _editor->pos(), _editor);
    dlg->setMultisensorIcon(this);
    dlg->setVisible(true);
#endif
}

void MultiSensorIcon::updateSensor()
{
#if 1
 MultiSensorIconAdder* iconEditor = (MultiSensorIconAdder*)_iconEditor;
 setInactiveIcon(((IconAdder*)iconEditor)->getIcon("SensorStateInactive"));
 setInconsistentIcon(((IconAdder*)iconEditor)->getIcon("BeanStateInconsistent"));
 setUnknownIcon(((IconAdder*)iconEditor)->getIcon("BeanStateUnknown"));
 for (int i = 0; i<entries->size(); i++)
 {
  entries->at(i)->namedSensor->getBean()->removePropertyChangeListener((PropertyChangeListener*)this);
 }
 int numPositions = iconEditor->getNumIcons();
 entries = new QList<Entry*>();//(numPositions);
 for (int i=3; i<numPositions; i++)
 {
  NamedIcon* icon = iconEditor->getIcon(i);
  NamedBeanHandle<Sensor*>* namedSensor = iconEditor->getSensor(i);
  addEntry(namedSensor, icon);
 }
 setUpDown(iconEditor->getUpDown());
 _iconEditorFrame->dispose();
 _iconEditorFrame = NULL;
 _iconEditor = NULL;
#endif
//    invalidate();
}
/************* end popup action methods ****************/


/**
 * Drive the current state of the display from the state of the
 * turnout.
 */
/*public*/ void MultiSensorIcon::displayState()
{
 updateSize();

 // run the entries
 bool foundActive = false;

 for (int i = 0; i<entries->size(); i++)
 {
  /*MultiSensorIcon*/Entry* e = entries->at(i);

  int state = Sensor::INCONSISTENT;
  if(e->namedSensor != NULL)
   state = ((AbstractSensor*)e->namedSensor->getBean())->getKnownState();

  switch (state)
  {
  case Sensor::ACTIVE:
   if (isText()) PositionableLabel::setText(tr("Active"));
   if (isIcon()) PositionableLabel::setIcon(e->icon);
   foundActive = true;
   displaying = i;
   break;  // look at the next ones too
  case Sensor::UNKNOWN:
   if (isText()) PositionableLabel::setText(tr("UnKnown"));
   if (isIcon()) PositionableLabel::setIcon(unknown);
   return;  // this trumps all others
  case Sensor::INCONSISTENT:
   if (isText()) PositionableLabel::setText(tr("Inconsistent"));
   if (isIcon()) PositionableLabel::setIcon(inconsistent);
   break;
  default:
   break;
  }
 }
 // loop has gotten to here
 if (foundActive) return;  // set active
 // only case left is all inactive
 if (isText()) PositionableLabel::setText(tr("Inactive"));
 if (isIcon()) PositionableLabel::setIcon(inactive);
 return;
}

// Use largest size. If icons are not same size,
// this can result in drawing artifacts.
/*public*/ int MultiSensorIcon::maxHeight() {
    int size = qMax(
                    ((inactive!=NULL) ? inactive->getIconHeight() : 0),
            qMax((unknown!=NULL) ? unknown->getIconHeight() : 0,
                    (inconsistent!=NULL) ? inconsistent->getIconHeight() : 0)
        );
    if (entries != NULL) {
        for (int i = 0; i<entries->size(); i++)
            size = qMax(size, entries->at(i)->icon->getIconHeight());
    }
    return size;
}

// Use largest size. If icons are not same size,
// this can result in drawing artifacts.
/*public*/ int MultiSensorIcon::maxWidth() {
    int size = qMax(
                    ((inactive!=NULL) ? inactive->getIconWidth() : 0),
            qMax((unknown!=NULL) ? unknown->getIconWidth() : 0,
                    (inconsistent!=NULL) ? inconsistent->getIconWidth() : 0)
        );
    if (entries != NULL) {
        for (int i = 0; i<entries->size(); i++)
            size = qMax(size, entries->at(i)->icon->getIconWidth());
    }
    return size;
}

/*public*/ void MultiSensorIcon::performMouseClicked(QGraphicsSceneMouseEvent* /*e*/, int xx, int yy) {
    if (log->isDebugEnabled()) log->debug(tr("performMouseClicked: buttonLive= ")+(buttonLive()?"true":"false")+", click from ("+
             QString::number(xx)+", "+QString::number(yy)+") displaying="+QString::number(displaying));
    if (!buttonLive()) return;
    if (entries == NULL || entries->size() < 1) return;

    // find if we want to increment or decrement
    bool dec = false;
    if (updown) {
        if ((yy-((Positionable*)this)->getY()) > maxHeight()/2) dec = true;
    } else {
        if ((xx-((Positionable*)this)->getX()) < maxWidth()/2) dec = true;
    }

    // get new index
    int next;
    if (dec) {
        next = displaying-1;
    } else {
        next = displaying+1;
    }
    if (next < 0) next = 0;
    if (next >= entries->size()) next = entries->size()-1;

    int drop = displaying;
    if (log->isDebugEnabled()) log->debug(tr("dec= ")+(dec?"true":"false")+" displaying="+QString::number(displaying)+" next= "+QString::number(next) );
    try {
        ((AbstractSensor*)entries->at(next)->namedSensor->getBean())->setKnownState(Sensor::ACTIVE);
        if (drop >= 0 && drop != next) ((AbstractSensor*)entries->at(drop)->namedSensor->getBean())->setKnownState(Sensor::INACTIVE);
    } catch (JmriException ex) {
        log->error("Click failed to set sensor: "+ex.getMessage());
    }
}

bool MultiSensorIcon::buttonLive() {
    if (!_editor->getFlag(Editor::OPTION_CONTROLS, isControlling())) return false;
    return true;
}

/*public*/ void MultiSensorIcon::doMouseClicked(QGraphicsSceneMouseEvent* e)
{
 //if ( !e.isAltDown() &&  !e.isMetaDown() )
 if(((e->modifiers() ^ Qt::AltModifier) == Qt::AltModifier) && ((e->modifiers() ^ Qt::MetaModifier)==Qt::MetaModifier) )
 {
  performMouseClicked(e, e->lastPos().x(), e->lastPos().y() );
 }
}

/*public*/ void MultiSensorIcon::dispose()
{
#if 0
 // remove listeners
 for (int i = 0; i<entries->size(); i++)
 {
  entries->at(i)->namedSensor->getBean()
            ->removePropertyChangeListener(this);
 }
#endif
    PositionableLabel::dispose();
}

/*public*/ QString MultiSensorIcon::getGroupName()
{
 return "MultiSensorItem";
}
