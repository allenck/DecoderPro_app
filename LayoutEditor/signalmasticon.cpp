#include "signalmasticon.h"
#include "signalmast.h"
#include "namedbean.h"
#include "namedbeanhandle.h"
#include "editor.h"
#include "instancemanager.h"
#include "signalmastmanager.h"
#include "defaultsignalappearancemap.h"
#include <QMessageBox>
#include "defaultsignalmastmanager.h"
#include "abstractsignalmast.h"
#include "fileutil.h"
#include "abstractsignalmast.h"
#include "defaultsignalsystem.h"
#include "../Tables/signallingsourceaction.h"
#include "signalmastitempanel.h"
#include "picklistmodel.h"
#include "tableitempanel.h"
#include "joptionpane.h"

SignalMastIcon::SignalMastIcon(QWidget* parent) :
    PositionableIcon()
{
}
/**
 * An icon to display a status of a SignalMast.
 * <P>
 * For now, this is done via text.
 *
 * @see jmri.SignalMastManager
 * @see jmri.InstanceManager
 * @author Bob Jacobsen Copyright (C) 2009
 * @version $Revision: 22320 $
 */

///*public*/ class SignalMastIcon extends PositionableIcon implements java.beans.PropertyChangeListener {

/*public*/ SignalMastIcon::SignalMastIcon(Editor* editor, Positionable* parent) : PositionableIcon(editor, parent)
{
    // super ctor call to make sure this is an icon label
    //super(editor);
    log = new Logger("SignalMastIcon");
    debug = log->isDebugEnabled();
    _useIconSet = "default";
    clickMode = 0;
    litMode = false;
    namedMast = nullptr;
    _displayLevel = Editor::SIGNALS;

    _control = true;
}


/*public*/ void SignalMastIcon::setShowAutoText(bool state) {
    _text = state;
    _icon = !_text;
}

/*public*/ Positionable* SignalMastIcon::deepClone() {
    SignalMastIcon* pos = new SignalMastIcon(_editor);
    return finishClone((Positionable*)pos);
}

/*public*/ Positionable* SignalMastIcon::finishClone(Positionable* p) {
    SignalMastIcon* pos = (SignalMastIcon*)p;
    pos->setSignalMast(getPName());
//    pos->_iconMap = cloneMap(_iconMap, (PositionableLabel*)pos);
    pos->setClickMode(getClickMode());
    pos->setLitMode(getLitMode());
    pos->useIconSet(useIconSet());
    return PositionableIcon::finishClone((Positionable*)pos);
}

/**
 * Attached a signalmast element to this display item
 * @param sh Specific SignalMast handle
 */
/*public*/ void SignalMastIcon::setSignalMast(NamedBeanHandle<SignalMast*>* sh)
{
 if (namedMast != nullptr)
 {
  getSignalMast()->removePropertyChangeListener((PropertyChangeListener*)this);
 }
 namedMast = sh;
 if (namedMast != nullptr) {
     getIcons();
     displayState(mastState());
     getSignalMast()->addPropertyChangeListener((PropertyChangeListener*)this, namedMast->getName(), "SignalMast Icon");
 }
}

 /**
 * Taken from the layout editor
 * Attached a numbered element to this display item
 * @param pName Used as a system/user name to lookup the SignalMast object
 */
/*public*/ void SignalMastIcon::setSignalMast(QString pName) {
    this->pName = pName;
    SignalMast* mMast = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(pName);
    if (mMast == NULL) log->warn("did not find a SignalMast named "+pName);
    else {
        namedMast = new NamedBeanHandle<SignalMast*>(pName, mMast);
        getIcons();
        displayState(mastState());
        mMast->addPropertyChangeListener((PropertyChangeListener*)this);
//        AbstractSignalMast* aMast =  (AbstractSignalMast*)mMast;
//        connect(aMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    }
}


/*private*/ void SignalMastIcon::getIcons() {
    _iconMap = new QMap<QString, NamedIcon*>();
#if 1
    QListIterator<QString> e(getSignalMast()->getAppearanceMap()->getAspects());
    bool error = false;
    while (e.hasNext()) {
        QString aspect = e.next();
        error = loadIcons(aspect);
    }
    if(error){
//        JOptionPane.showMessageDialog(_editor.getTargetFrame(),
//            java.text.MessageFormat.format(Bundle.getMessage("SignalMastIconLoadError"),
//            new Object[]{mMast.getDisplayName()}),
//            Bundle.getMessage("SignalMastIconLoadErrorTitle"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(0, tr("Error with Icons"), tr("Not all states will be shown on the panel\nCheck console output for details"));
    }
    //Add in specific appearances for dark and held
    loadIcons("$dark");
    loadIcons("$held");
#endif
}

/*private*/ bool SignalMastIcon::loadIcons(QString aspect)
{
 QString s =((DefaultSignalAppearanceMap*) getSignalMast()->getAppearanceMap())->getImageLink(aspect, _useIconSet);
 if(s==(""))
 {
  if(aspect.startsWith("$"))
   log->debug("No icon found for specific appearance " + aspect);
  else
   log->error("No icon found for appearance " + aspect);
  return true;
 }
 else
 {
  if(!s.contains("preference:"))
        s = s.mid(s.indexOf("resources"));
  if(s.startsWith("resources"))  // TODO: make this configurable
     s = FileUtil::getProgramPath()+s;
  NamedIcon* n;
  try
  {
   n = new NamedIcon(s, s);
  } catch (NullPointerException e)
  {
      JOptionPane::showMessageDialog(nullptr, tr("Unable to load %1 icon\n%2\nfor Signal Mast %3").arg(aspect).arg(s, getNameString()), tr("Error with Icons"), JOptionPane::ERROR_MESSAGE);
      log->error(tr("Unable to load %1 icon\n%2\nfor Signal Mast %3").arg(aspect).arg(s).arg(getNameString()));
      return true;
  }
  _iconMap->insert(aspect, n);
  if(_rotate!=0)
  {
   n->rotate(_rotate, this);
  }
  if (_scale!=1.0)
  {
   n->scale(_scale, this);
  }
 }
 return false;
}


/*public*/ NamedBeanHandle<SignalMast*>* SignalMastIcon::getNamedSignalMast()
{
 return namedMast;
}

/*public*/ SignalMast* SignalMastIcon::getSignalMast(){
    if (namedMast==NULL)
        return nullptr;
    return namedMast->getBean();
}

/*public*/ NamedBean* SignalMastIcon::getNamedBean(){
    return getSignalMast();
}

/**
 * Get current appearance of the mast
 * @return An aspect from the SignalMast
 */
/*public*/ QString SignalMastIcon::mastState() {
    if (getSignalMast()==nullptr) return "<empty>";
    else return getSignalMast()->getAspect();
}

// update icon as state of turnout changes
/*public*/ void SignalMastIcon::propertyChange(PropertyChangeEvent* e) {
    if (debug) log->debug("property change: "+e->getPropertyName()
                                        +" current state: "+mastState());
    displayState(mastState());
//    _editor->getTargetPanel().repaint();
}

/*public*/ QString SignalMastIcon::getPName() { return pName; }

/*public*/ QString SignalMastIcon::getNameString() {
 QString name;
 if (getSignalMast() == nullptr) {
     name = tr("<Not connected>");
 } else {
     name = getSignalMast()->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
 }
 return name;
}

/**
 * Pop-up just displays the name
 */
/*public*/ bool SignalMastIcon::showPopUp(QMenu* popup)
{
 if (isEditable())
 {
  QMenu* clickMenu = new QMenu(tr("When Clicked"));
  //QButtonGroup* clickButtonGroup = new QButtonGroup();
//        JRadioButtonMenuItem r;
//        r = new JRadioButtonMenuItem(tr("Change Aspect"));
//        r.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) { setClickMode(0); }
//        });
//        clickButtonGroup.add(r);
  QAction* changeAspectAct = new QAction(tr("Change Aspect"), this);
  changeAspectAct->setCheckable(true);
  if (clickMode == 0)  changeAspectAct->setChecked(true);
  else changeAspectAct->setChecked(false);
  clickMenu->addAction(changeAspectAct);
  connect(changeAspectAct, SIGNAL(toggled(bool)), this, SLOT(setClickMode0()));

//        r = new JRadioButtonMenuItem(Bundle.getMessage("AlternateLit"));
//        r.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) { setClickMode(1); }
//        });
//        clickButtonGroup.add(r);
  QAction* alternateLitAct = new QAction(tr("Alternate Lit"), this);
  alternateLitAct->setCheckable(true);
  if (clickMode == 1)  alternateLitAct->setChecked(true);
  else alternateLitAct->setChecked(false);
  clickMenu->addAction(alternateLitAct);
  connect(alternateLitAct, SIGNAL(toggled(bool)), this, SLOT(setClickMode1()));
//        r = new JRadioButtonMenuItem(Bundle.getMessage("AlternateHeld"));
//        r.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) { setClickMode(2); }
//        });
//        clickButtonGroup.add(r);
  QAction* alternateHeldAct = new QAction(tr("Alternate Held"), this);
  alternateHeldAct->setCheckable(true);
  if (clickMode == 2)  alternateHeldAct->setChecked(true);
  else alternateHeldAct->setChecked(false);
  clickMenu->addAction(alternateHeldAct);
  connect(alternateHeldAct, SIGNAL(toggled(bool)), this, SLOT(setClickMode2()));
  popup->addMenu(clickMenu);

  // add menu to select handling of lit parameter
  QMenu* litMenu = new QMenu(tr("When Not Lit"));
  litButtonGroup = new QActionGroup(this);
  QAction* r = new QAction(tr("ShowAppearance"), this);
  r->setCheckable(true);
  //r.setIconTextGap(10);
//        r.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                setLitMode(false);
//                displayState(mastState());
//            }
//        });
  connect(r, SIGNAL(triggered(bool)), this, SLOT(onWhenNotLit()));
  litButtonGroup->addAction(r);
  if (!litMode) {
      r->setChecked(true);
  } else {
      r->setChecked(false);
  }
  litMenu->addAction(r);
  r = new QAction(tr("Show Dark Icon"),this);
  r->setCheckable(true);
  //r.setIconTextGap(10);
//        r.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                setLitMode(true);
//                displayState(mastState());
//            }
//        });
  litButtonGroup->addAction(r);
  if (litMode) {
      r->setChecked(true);
  } else {
      r->setChecked(false);
  }
  litMenu->addAction(r);
  popup->addMenu(litMenu);

  if(getSignalMast()->getSignalSystem()!=nullptr)
  {
   QStringListIterator en  (getSignalMast()->getSignalSystem()->getImageTypeList());
   if(en.hasNext())
   {
    QMenu* iconSetMenu = new QMenu(tr("Use SignalMast Icon Set"));
    QSignalMapper* iconTypeGroup = new QSignalMapper();
    setImageTypeList(iconTypeGroup, iconSetMenu, "default");
    while (en.hasNext())
    {
     setImageTypeList(iconTypeGroup, iconSetMenu, en.next());
    }
    popup->addMenu(iconSetMenu);
    connect(iconTypeGroup, SIGNAL(mapped(QString)), this, SLOT(useIconSet(QString)));
   }
  }
  popup->addAction(new SignallingSourceAction(tr("Signal Mast Logic"), getSignalMast()));
  QMenu* aspect = new QMenu(tr("Change Aspect"));
  QVector <QString> aspects = getSignalMast()->getValidAspects();
  QSignalMapper* mapper = new QSignalMapper();
  for (int i=0; i<aspects.size(); i++)
  {
      /*final*/ int index = i;
//            aspect.add(new AbstractAction(aspects.elementAt(index)){
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    mMast.setAspect(aspects.elementAt(index));
//                }
//            });
      QAction* aspectAct = new QAction(aspects.at(i), this);
      mapper->setMapping(aspectAct, index);
      connect(aspectAct, SIGNAL(triggered()), mapper, SLOT(map()));
      aspect->addAction(aspectAct);
  }
  popup->addMenu(aspect);
  connect(mapper, SIGNAL(mapped(int)), this, SLOT(setAspect(int)));
 }
 else
 {
  QMenu* aspect = new QMenu(tr("Change Aspect"));
  /*final*/ QVector <QString> aspects = getSignalMast()->getValidAspects();
  QSignalMapper* mapper = new QSignalMapper();
  for (int i=0; i<aspects.size(); i++)
  {
   /*final*/ int index = i;
//            popup.add(new AbstractAction(aspects.elementAt(index)){
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    mMast->setAspect(aspects.elementAt(index));
//                }
//            });
     QAction* aspectAct = new QAction(aspects.at(i), this);
     mapper->setMapping(aspectAct, index);
     connect(aspectAct, SIGNAL(triggered()), mapper, SLOT(map()));
     aspect->addAction(aspectAct);

  }
  popup->addMenu(aspect);
  connect(mapper, SIGNAL(mapped(int)), this, SLOT(setAspect(int)));
 }
 return true;
}
void SignalMastIcon::setAspect(int i)
{
 QVector <QString> aspects = getSignalMast()->getValidAspects();
 getSignalMast()->setAspect(aspects.at(i));
}
void SignalMastIcon::setClickMode0()
{
 setClickMode(0);
}
void SignalMastIcon::setClickMode1()
{
 setClickMode(1);
}
void SignalMastIcon::setClickMode2()
{
 setClickMode(2);
}
void SignalMastIcon::onWhenNotLit()
{
 setLitMode(false);
 displayState(mastState());
}

void SignalMastIcon::onShowDarkIcon()
{
 setLitMode(true);
 displayState(mastState());
}

/*private*/ void SignalMastIcon::setImageTypeList(QSignalMapper* iconTypeGroup, QMenu* iconSetMenu, /*final*/ QString item){
//    JRadioButtonMenuItem im;
//    im = new JRadioButtonMenuItem(item);
//    im.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) { useIconSet(item); }
//    });
    QAction* im = new QAction(item, this);
    im->setCheckable(true);
    iconTypeGroup->setMapping(im,item);
    if (_useIconSet==(item)) im->setChecked(true);
    else im->setChecked(false);
    iconSetMenu->addAction(im);
    connect(im, SIGNAL(toggled(bool)), iconTypeGroup, SLOT(map()));
}

/*public*/ bool SignalMastIcon::setRotateOrthogonalMenu(QMenu* /*popup*/){
    return false;
}


/*public*/ bool SignalMastIcon::setEditItemMenu(QMenu* popup) {
    QString txt = tr("Edit %1 Icon").arg(tr("Signal Mast"));
    QAction* editAction = new QAction("Edit",this);
    connect(editAction, SIGNAL(triggered()), this, SLOT(editItem()));
//    popup.add(new AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                editItem();
//            }
//        });
    popup->addAction(editAction);
    return true;
}

/*protected*/ void SignalMastIcon::editItem()
{
 makePaletteFrame(tr("Edit %1 Item").arg("Signal Mast"));
 _itemPanel = new SignalMastItemPanel(_paletteFrame, "SignalMast", getFamily(), PickListModel::signalMastPickModelInstance(), _editor);
//    ActionListener updateAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateItem();
//        }
//    };
 SMIAddIconActionListener* updateAction = new SMIAddIconActionListener(this);
    // _iconMap keys with local names - Let SignalHeadItemPanel figure this out
#if 1 // TODO:
 _itemPanel->init(updateAction, _iconMap);
#endif
 _itemPanel->setSelection(getSignalMast());
 _paletteFrame->layout()->addWidget(_itemPanel);
 _paletteFrame->pack();
 _paletteFrame->setVisible(true);
}

void SignalMastIcon::updateItem() {
    setSignalMast(_itemPanel->getTableSelection()->getSystemName());
    setFamily(_itemPanel->getFamilyName());
    _paletteFrame->dispose();
    _paletteFrame = nullptr;
//    _itemPanel->dispose();
//    _itemPanel = nullptr;
    invalidate();
}

/**
 * Change the SignalMast aspect when the icon is clicked.
 * @param e
 */
/*public*/ void SignalMastIcon::doMouseClicked(QGraphicsSceneMouseEvent* e) {
    if (!_editor->getFlag(Editor::OPTION_CONTROLS, isControlling())) return;
    performMouseClicked(e);
}

    /**
 * This was added in so that the layout editor can handle the mouseclicked when zoomed in
*/
/*public*/ void SignalMastIcon::performMouseClicked(QGraphicsSceneMouseEvent* e)
{
 //if (e.isMetaDown() || e.isAltDown() ) return;
    if((e->modifiers() & Qt::MetaModifier) != 0 || (e->modifiers() & Qt::AltModifier) != 0) return;
 if (getSignalMast()==nullptr)
 {
  log->error("No turnout connection, can't process click");
  return;
 }
 switch (clickMode)
 {
  case 0 :
  {
   QVector <QString> aspects = ((AbstractSignalMast*)getSignalMast())->getValidAspects();
   if(aspects.count() <1)
   {
    log->warn(tr("no valid aspects for mast %1").arg(getSignalMast()->getDisplayName()));
    return;
   }
   int idx = aspects.indexOf(((AbstractSignalMast*)getSignalMast())->getAspect()) + 1;
   if (idx >= aspects.size())
   {
    idx = 0;
   }
   getSignalMast()->setAspect(aspects.at(idx));
   displayState(mastState());
  }
  return;
 case 1 :
    ((AbstractSignalMast*)getSignalMast())->setLit(! ((AbstractSignalMast*)getSignalMast())->getLit());
    return;
 case 2 :
    ((AbstractSignalMast*)getSignalMast())->setHeld(! ((AbstractSignalMast*)getSignalMast())->getHeld());
    return;
 default:
    log->error("Click in mode "+clickMode);
 }
}


/*public*/ void SignalMastIcon::useIconSet(QString icon){
    if (icon==nullptr){
        icon = "default";
    }
    if(_useIconSet==(icon)){
        return;
    }
    //clear the old icon map out.
    _iconMap=nullptr;
    _useIconSet = icon;
    getIcons();
    displayState(mastState());
//    _editor->getTargetPanel().repaint();
}

/*public*/ QString SignalMastIcon::useIconSet() { return _useIconSet; }

/**
 * Set display of ClipBoard copied or duplicated mast
 */
/*public*/ void SignalMastIcon::displayState(int /*s*/) {
    displayState(mastState());
}

/**
 * Drive the current state of the display from the state of the
 * underlying SignalMast object.
 */
/*public*/ void SignalMastIcon::displayState(QString state)
{
 updateSize();
 if (debug)
 {
  if (getSignalMast() == nullptr)
  {
   log->debug("Display state "+state+", disconnected");
  }
  else
  {
   log->debug("Display state "+state+" for "+getSignalMast()->getSystemName());
  }
 }
 if (isText())
 {
  if (((AbstractSignalMast*)getSignalMast())->getHeld()) {
      if (isText()) PositionableIcon::setText(tr("<held>"));
      return;
  }
  else if (getLitMode() && !((AbstractSignalMast*)getSignalMast())->getLit()){
      PositionableIcon::setText(tr("<dark>"));
      return;
  }
  PositionableIcon::setText(state);
 }
 if (isIcon())
 {
  if ((state !="" ) && (getSignalMast()!=nullptr))
  {
   QString s = getSignalMast()->getAppearanceMap()->getImageLink(state, _useIconSet);
   if (getSignalMast()->getHeld() && (getSignalMast()->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::HELD)!=nullptr))
   {
    s = getSignalMast()->getAppearanceMap()->getImageLink("$held", _useIconSet);
   }
   else if((getSignalMast()->getLit()) && (getSignalMast()->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DARK)!=nullptr))
   {
    s = getSignalMast()->getAppearanceMap()->getImageLink("$dark", _useIconSet);
   }
   if(s==(""))
   {
    /*We have no appearance to set, therefore we will exit at this point.
    This can be considered normal if we are requesting an appearance
    that is not support or configured, such as dark or held */
    return;
   }
   if(!s.contains("preference:"))
    s = s.mid(s.indexOf("resources"));
   if(s.startsWith("resources"))
     s= FileUtil::getProgramPath()+s; // TODO: make configurable
    // tiny global cache, due to number of icons
   if (_iconMap==nullptr) getIcons();
   NamedIcon* n = _iconMap->value(state);
   PositionableIcon::setIcon(n);
   _editor->addToTarget(this);
   updateSize();
   setSize(n->getIconWidth(), n->getIconHeight());
  }
 }
 else
 {
  PositionableIcon::setIcon(nullptr);
 }
 return;
}

/*public*/ bool SignalMastIcon::setEditIconMenu(QMenu* /*popup*/) {
    return false;
}

/*protected*/ void SignalMastIcon::rotateOrthogonal() {
    PositionableIcon::rotateOrthogonal();
    // bug fix, must repaint icons that have same width and height
    displayState(mastState());
//    repaint();
}

/*public*/ void SignalMastIcon::rotate(int deg){
    PositionableIcon::rotate(deg);
    if (getSignalMast()!=nullptr) {
        displayState(mastState());
    }
}

/*public*/ void SignalMastIcon::setScale(double s) {
    PositionableIcon::setScale(s);
    if (getSignalMast()!=nullptr) {
        displayState(mastState());
    }
}


/*public*/ void SignalMastIcon::setClickMode(int mode) {
    clickMode = mode;
}
/*public*/ int SignalMastIcon::getClickMode() {
    return clickMode;
}

/**
 * How to handle lit vs not lit?
 * <P>
 * False means ignore (always show R/Y/G/etc appearance on screen);
 * True means show DefaultSignalAppearanceMap.DARK if lit is set false.
 * <P>
 * Note that setting the appearance "DefaultSignalAppearanceMap.DARK" explicitly
 * will show the dark icon regardless of how this is set.
 */

/*public*/ void SignalMastIcon::setLitMode(bool mode) {
    litMode = mode;
}
/*public*/ bool SignalMastIcon::getLitMode() {
    return litMode;
}

/*public*/ void SignalMastIcon::dispose() {
    getSignalMast()->removePropertyChangeListener((PropertyChangeListener*)this);
//    AbstractSignalMast* aMast =  (AbstractSignalMast*)mMast;
//    disconnect(aMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    PositionableIcon::dispose();
}

/*public*/ bool SignalMastIcon::updateScene() // TODO: this function not in Java
{
 QGraphicsPixmapItem* item = nullptr;
 if(_itemGroup != nullptr)
 {
  QList<QGraphicsItem*> itemList = _itemGroup->childItems();
  foreach(QGraphicsItem* it, itemList)
  {
   if(qgraphicsitem_cast<QGraphicsPixmapItem*>(it) != nullptr)
   {
    _itemGroup->setRotation(_itemGroup->rotation() - currRotation);
    item = qgraphicsitem_cast<QGraphicsPixmapItem*>(it);
   }
  }
 }
 else
  _itemGroup = new MyGraphicsItemGroup();
 _itemGroup->setName("signaMastIcon");


 QString aspect = getSignalMast()->getAspect();
 QPixmap pixmap = QPixmap::fromImage(getIcon(aspect)->getImage());
 if(item != nullptr)
  item->setPixmap(pixmap);
 else
  item = new QGraphicsPixmapItem(pixmap,_itemGroup);
 //item->setPos(getX(), getY());
 if(showToolTip()) item->setToolTip(getToolTip());
 //_itemGroup->addToGroup(item);
 _itemGroup->setPos(((Positionable*)this)->getX(), ((Positionable*)this)->getY());
 //if(showTooltip()) _itemGroup->setToolTip(getTooltip());
 //int degrees = getDegrees() + getIcon()->getRotation();
 currRotation = getIcon(aspect)->getRotation()*90;
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
