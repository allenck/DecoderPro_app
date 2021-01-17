#include "signalheadicon.h"
#include "instancemanager.h"
#include "editor.h"
#include "signalheadmanager.h"
#include "abstractsignalheadmanager.h"
#include "singleturnoutsignalhead.h"
#include "doubleturnoutsignalhead.h"
#include "virtualsignalhead.h"
#include "blockbossframe.h"
//#include "picklistmodel.h"
//#include "signalheaditempanel.h"
#include "Throttle/throttleslistpanel.h"
#include "picklistmodel.h"
#include "signalheaditempanel.h"
#include "itempalette.h"

//SignalHeadIcon::SignalHeadIcon(QObject *parent) :
//    PositionableIcon(parent)
//{
//}
/**
 * An icon to display a status of a SignalHead.
 * <P>
 * SignalHeads are located via the SignalHeadManager, which in turn is located
 * via the InstanceManager.
 *
 * @see jmri.SignalHeadManager
 * @see jmri.InstanceManager
 * @author Bob Jacobsen Copyright (C) 2001, 2002
 * @version $Revision: 22576 $
 */

///*public*/ class SignalHeadIcon extends PositionableIcon implements java.beans.PropertyChangeListener {



/*public*/ SignalHeadIcon::SignalHeadIcon(Editor* editor, Positionable *parent) : PositionableIcon(editor, parent)
{
 //super(editor);
 log = new Logger("SignalHeadIcon");
 log->setDebugEnabled(false);
 litButtonGroup = NULL;
 clickMode = 3;
 litMode = false;
 namedHead = NULL;
 _icon = true;
 _text = false;
 setLevel(Editor::SIGNALS);

 pcs = new PropertyChangeSupport(this);
}

/*public*/ Positionable* SignalHeadIcon::deepClone()
{
 SignalHeadIcon* pos = new SignalHeadIcon(_editor);
 return finishClone((Positionable*)pos);
}

/*public*/ Positionable* SignalHeadIcon::finishClone(Positionable* p)
{
 SignalHeadIcon* pos = (SignalHeadIcon*)p;
 pos->setSignalHead(getNamedSignalHead()->getName());
 //Enumeration <QString> e = _iconMap.keys();
 QMapIterator<QString, NamedIcon*> e(*_iconMap);
 while (e.hasNext())
 {
  e.next();
  QString key = e.key();
  pos->setIcon(key, _iconMap->value(key));
 }
 pos->setClickMode(getClickMode());
 pos->setLitMode(getLitMode());
    return PositionableIcon::finishClone((Positionable*)pos);
}

/**
 * Attached a signalhead element to this display item
 * @param sh Specific SignalHead object
 */
/*public*/ void SignalHeadIcon::setSignalHead(NamedBeanHandle<SignalHead*>* sh)
{
 if (namedHead != NULL)
 {
  getSignalHead()->removePropertyChangeListener((PropertyChangeListener*)this);
//  AbstractSignalHead* sh = (AbstractSignalHead*)getSignalHead();
//  disconnect(sh, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 namedHead = sh;
 if (namedHead != NULL)
 {
  _iconMap = new QMap<QString, NamedIcon*>();
  SignalHead* signalHead = getSignalHead();
  setObjectName(signalHead->getSystemName());
  if(qobject_cast<SingleTurnoutSignalHead*>(signalHead)!=NULL)
  _validKey = ((SingleTurnoutSignalHead*)signalHead)->getValidStateNames();
  else
  if(qobject_cast<DoubleTurnoutSignalHead*>(signalHead)!=NULL)
   _validKey = ((DoubleTurnoutSignalHead*)signalHead)->getValidStateNames();
  else
  if(qobject_cast<VirtualSignalHead*>(signalHead)!=NULL)
   _validKey = ((VirtualSignalHead*)signalHead)->getValidStateNames();
  else
   _validKey = getSignalHead()->getValidStateNames();

  displayState(headState());
  getSignalHead()->addPropertyChangeListener((PropertyChangeListener*)this);
  DefaultSignalHead* head = (DefaultSignalHead*)getSignalHead();
//  connect(head->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //connect(head, SIGNAL(propertyChange(QString,QVariant,QVariant)), this, SLOT(propertyChange(QString,QVariant,QVariant)));
  setToolTip(head->getDisplayName());
 }

}

 /**
 * Taken from the layout editor
 * Attached a numbered element to this display item
 * @param pName Used as a system/user name to lookup the SignalHead object
 */
/*public*/ void SignalHeadIcon::setSignalHead(QString pName)
{
 SignalHead* mHead = (SignalHead*)((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(pName);
 if (mHead == NULL) mHead = (SignalHead*)((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getByUserName(pName);
 if (mHead == NULL) log->warn("did not find a SignalHead named "+pName);
 else
 {
  setSignalHead(new NamedBeanHandle <SignalHead*>(pName, mHead));
 }
}

/*public*/ NamedBeanHandle <SignalHead*>* SignalHeadIcon::getNamedSignalHead()
{
 return namedHead;
}

/*public*/ SignalHead* SignalHeadIcon::getSignalHead()
{
 if (namedHead==NULL)
     return NULL;
 return namedHead->getBean();
}

/*public*/ NamedBean* SignalHeadIcon::getNamedBean()
{
 return (NamedBean*)getSignalHead();
}

/**
* Check that device supports the state
* valid state names returned by the bean are localized
*/
/*private*/ bool SignalHeadIcon::isValidState(QString key)
{
 if (key==NULL)
 {
  return false;
 }
 if (key==(tr("Dark"))
              || key==(tr("Held")) )
 {
  if (log->isDebugEnabled()) log->debug(key+" is a valid state. ");
  return true;
 }
 for (int i=0; i<_validKey.count(); i++)
 {
  if (key==(_validKey.at(i)))
  {
      if (log->isDebugEnabled()) log->debug(key+" is a valid state. ");
      return true;
  }
 }
 if (log->isDebugEnabled()) log->debug(key+" is NOT a valid state. ");
 return false;
}

/**
* Place icon by its bean state name key found in jmri.NamedBeanBundle.properties
* Place icon by its localized bean state name
*/
/*public*/ void SignalHeadIcon::setIcon(QString state, NamedIcon* icon)
{
 if (log->isDebugEnabled()) log->debug("setIcon for "+state);
 if (isValidState(state))
 {
  _iconMap->insert(state, icon);
  displayState(headState());
 }
}

/**
 * Get current appearance of the head
 * @return An appearance variable from a SignalHead, e.g. SignalHead.RED
 */
/*public*/ int SignalHeadIcon::headState()
{
 if (getSignalHead()==NULL) return 0;
 else return getSignalHead()->getAppearance();
}

// update icon as state of turnout changes
/*public*/ void SignalHeadIcon::propertyChange(PropertyChangeEvent* e)
{
// if (log->isDebugEnabled() && (getSignalHead()->getSystemName() == "LH15" ||getSignalHead()->getSystemName() == "LH1")) log->debug(getSignalHead()->getSystemName() + " property change: "+e->getPropertyName() +" current state: " + QString::number(headState()) + " oldValue: " + e->getOldValue().toString() + " newValue: " + e->getNewValue().toString());
 if(e->getPropertyName() == "flash")
 {
  if(e->getNewValue().toBool())
  {
   displayState(headState());
  }
  else
  {
   displayState(0);
  }
  updateScene();
  return;
 }
 displayState(headState());
//    _editor->getTargetPanel().repaint();
 //_editor->addToTarget((Positionable*)this);
  updateScene();
}

/*public*/ QString SignalHeadIcon::getNameString()
{
 QString name;
 if (namedHead == NULL) name = tr("<Not connected>");
 else if (getSignalHead()->getUserName()!="")
  name = getSignalHead()->getUserName();
     //name = getSignalHead().getUserName()+" ("+getSignalHead().getSystemName()+")";
 else
  name = getSignalHead()->getSystemName();
 return name;
}


/**
 * Pop-up just displays the name
 */
/*public*/ bool SignalHeadIcon::showPopUp(QMenu* popup)
{
 if (isEditable())
 {
  // add menu to select action on click
  QMenu* clickMenu = new QMenu(tr("When Clicked"));
  //QButtonGroup* clickButtonGroup = new QButtonGroup();
  QAction* changeAspectAct;
  changeAspectAct = new QAction(tr("Change Aspect"),this);
  changeAspectAct->setCheckable(true);
//    r->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) { setClickMode(3); }
//    });
  connect(changeAspectAct,SIGNAL(toggled(bool)),this, SLOT(on_changeAspectAct_toggled3(bool)));

  //clickButtonGroup->layout()->addWidget(r);
  if (clickMode == 3)  changeAspectAct->setChecked(true);
  else changeAspectAct->setChecked(false);
  clickMenu->addAction(changeAspectAct);

  QAction* cycle3AspectsAct = new QAction(tr("Cycle 3 Aspects"), this);
  cycle3AspectsAct->setCheckable(true);
//    r->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) { setClickMode(0); }
//    });
  //clickButtonGroup->addAc(changeAspectAct);
  if (clickMode == 0)  cycle3AspectsAct->setChecked(true);
  else cycle3AspectsAct->setChecked(false);
  clickMenu->addAction(cycle3AspectsAct);
  connect(cycle3AspectsAct, SIGNAL(toggled(bool)), this, SLOT(on_cycle3AspectsAct_toggled(bool)));

  QAction* alternateLitAct = new QAction(tr("Alternate Lit"),this);
  alternateLitAct->setCheckable(true);
//    r->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) { setClickMode(1); }
//    });
  //clickButtonGroup->layout()->addWidget(alternateLitAct);
  if (clickMode == 1)  alternateLitAct->setChecked(true);
  else alternateLitAct->setChecked(false);
  clickMenu->addAction(alternateLitAct);
  connect(alternateLitAct, SIGNAL(toggled(bool)), this, SLOT(on_alternateLitAct_toggled(bool)));

  QAction* alternateHeldAct = new QAction(tr("Alternate Held"),this);
  alternateHeldAct->setCheckable(true);
//    r->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) { setClickMode(2); }
//    });
//    clickButtonGroup->layout()->addWidget(r);
  if (clickMode == 2)  alternateHeldAct->setChecked(true);
  else alternateHeldAct->setChecked(false);
  clickMenu->addAction(alternateHeldAct);
  connect(alternateHeldAct, SIGNAL(toggled(bool)), this, SLOT(on_alternateHeldAct_toggled(bool)));
  popup->addMenu(clickMenu);


  // add menu to select handling of lit parameter
  QMenu* litMenu = new QMenu(tr("When Not Lit"));
  //litButtonGroup = new ButtonGroup();
  QAction* showAppearanceAct = new QAction(tr("Show Appearance"), this);
  showAppearanceAct->setCheckable(true);
  //showAppearanceAct->setIconTextGap(10);
//    r->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) { setLitMode(false); }
//    });
//    litButtonGroup->layout()->addWidget(r);
  if (!litMode)  showAppearanceAct->setChecked(true);
  else showAppearanceAct->setChecked(false);
  litMenu->addAction(showAppearanceAct);
  connect(showAppearanceAct, SIGNAL(toggled(bool)), this, SLOT(on_showAppearanceAct_toggled(bool)));

  QAction* showDarkIconAct = new QAction(tr("Show Dark Icon"),this);
  showDarkIconAct->setCheckable(true);
  //r.setIconTextGap(10);
//    r->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) { setLitMode(true); }
//    });
//    litButtonGroup->layout()->addWidget(r);
  if (litMode)  showDarkIconAct->setChecked(true);
  else showDarkIconAct->setChecked(false);
  litMenu->addAction(showDarkIconAct);
  popup->addMenu(litMenu);
  connect(showDarkIconAct, SIGNAL(toggled(bool)), this, SLOT(on_showDarkIconAct_toggled(bool)));

//    popup->layout()->addWidget(new AbstractAction(tr("Edit Logic")) {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            jmri.jmrit.blockboss.BlockBossFrame f = new jmri.jmrit.blockboss.BlockBossFrame();
//            String name = getNameString();
//            f.setTitle(java.text.MessageFormat.format(tr("SignalLogic"), name));
//            f.setSignal(name);
//            f.setVisible(true);
//        }
//    });
  QAction* editLogicAction = new QAction(tr("Edit logic"), this);
  connect(editLogicAction, SIGNAL(triggered()), this, SLOT(on_editLogicAction_triggered()));
  popup->addAction(editLogicAction);
  return true;
 }
 return false;
}
void SignalHeadIcon::on_changeAspectAct_toggled3(bool bState)
{
 if(bState)
  setClickMode(3);
}
void SignalHeadIcon::on_cycle3AspectsAct_toggled(bool bState)
{
 if(bState)
  setClickMode(0);
}
void SignalHeadIcon::on_alternateLitAct_toggled(bool bState)
{
 if(bState)
  setClickMode(1);
}
void SignalHeadIcon::on_alternateHeldAct_toggled(bool bState)
{
 if(bState)
  setClickMode(2);
}
void SignalHeadIcon::on_showAppearanceAct_toggled(bool bState)
{
 if(bState)
   setLitMode(false);
}
void SignalHeadIcon::on_showDarkIconAct_toggled(bool bState)
{
 if(bState)
  setLitMode(true);
}
void SignalHeadIcon::on_editLogicAction_triggered()
{
 BlockBossFrame* f = new BlockBossFrame();
 QString name = getNameString();
 f->setWindowTitle(tr("SignalLogic %1").arg(name));
 f->setSignal(name);
 f->setVisible(true);
}

/*************** popup AbstractAction.actionPerformed method overrides ************/
#if 0 // not needed since scaling and rotating is done by QT's QGraphicsScene
/*protected*/ void SignalHeadIcon::rotateOrthogonal()
{
 PositionableIcon::rotateOrthogonal();
 displayState(headState());
}
/*public*/ void SignalHeadIcon::setScale(double s)
{
 PositionableIcon::setScale(s);
 displayState(headState());
}

/*public*/ void SignalHeadIcon::rotate(int deg)
{
 PositionableIcon::rotate(deg);
 displayState(headState());
}
#endif
/**
 * Drive the current state of the display from the state of the
 * underlying SignalHead object.
 * <UL>
 * <LI>If the signal is held, display that.
 * <LI>If set to monitor the status of the lit parameter
 *     and lit is false, show the dark icon ("dark", when
 *     set as an explicit appearance, is displayed anyway)
 * <LI>Show the icon corresponding to one of the seven appearances.
 * </UL>
 */
/*public*/ void SignalHeadIcon::displayState(int state)
{
 updateSize();
 if (getSignalHead() == NULL)
 {
  if (log->isDebugEnabled())log->debug("Display state "+QString::number(state)+", disconnected");
  return;
 }
 else
 {
  QString appearance = getSignalHead()->getAppearanceName(state);
  if (log->isDebugEnabled()) log->debug("Display state "+QString::number(state)+" for "+getNameString() + " "+appearance);
  if (getSignalHead()->getHeld())
  {
   if (isText()) PositionableIcon::setText(tr("<held>"));
   if (isIcon())
   {
    PositionableIcon::setIcon(_iconMap->value(tr("Held")));
     //_editor->addToTarget((Positionable*)this);
    updateScene();
   }
   return;
  }
  //else if (getLitMode() && !getSignalHead()->getLit())
  else if (getLitMode() && !getSignalHead()->getLit())
  {
   if (isText()) PositionableIcon::setText(tr("<dark>"));
   if (isIcon())
   {
    PositionableIcon::setIcon(_iconMap->value(tr("Dark")));
     //_editor->addToTarget((Positionable*)this);
    updateScene();
   }
   return;
  }

 }
 if (isText())
 {
  PositionableIcon::setText(getSignalHead()->getAppearanceName(state));
 }
 if (isIcon())
 {
  NamedIcon* icon =_iconMap->value(getSignalHead()->getAppearanceName(state));
  if (icon!=NULL)
  {
   PositionableIcon::setIcon(icon);
   //_editor->addToTarget((Positionable*)this);
   updateScene();
  }
 }
 return;
}

// called by ControlPanelEditor:
/*public*/ bool SignalHeadIcon::setEditItemMenu(QMenu* popup)
{
 QString txt = tr("Edit %1 Icon").arg( tr("Signal Head"));
//    popup->add(new AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                editItem();
//            }
//        });
 QAction* editAction = new QAction(txt, this);
 popup->addAction(editAction);
 connect(editAction, SIGNAL(triggered()), this, SLOT(editItem()));
 return true;
}

// called by ControlPanelEditor:
/*protected*/ void SignalHeadIcon::editItem() // [slot]
{
 makePaletteFrame(tr("Edit %1 Icon").arg( tr("Signal Head")));
 QWidget* centralWidget = new QWidget;
 QVBoxLayout* paletteFrameLayout = new QVBoxLayout;
 centralWidget->setLayout(paletteFrameLayout);
 _paletteFrame->setCentralWidget(centralWidget);
 _itemPanel = new SignalHeadItemPanel(_paletteFrame, "SignalHead", getFamily(), PickListModel::signalHeadPickModelInstance(), _editor);
//    ActionListener updateAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateItem();
//        }
//    };
    //ActionListener* updateAction = new ActionListener();
 MyActionListener* updateAction = new MyActionListener(this);

 // _iconMap keys with local names - Let SignalHeadItemPanel figure this out
 // duplicate _iconMap map with unscaled and unrotated icons
 QMap<QString, NamedIcon*>* map = new QMap<QString, NamedIcon*>();
 QMapIterator<QString, NamedIcon*> it(*_iconMap);
 while (it.hasNext())
 {
  //QHash<QString, NamedIcon*> entry =
  it.next();
  NamedIcon* oldIcon = it.value();
  NamedIcon* newIcon = cloneIcon(oldIcon, this);
  newIcon->rotate(0, this);
  newIcon->scale(1.0, this);
  newIcon->setRotation(4, this);
  map->insert(it.key(), newIcon);
 }
 _itemPanel->init(updateAction, map);
 _itemPanel->setSelection(getSignalHead());
 paletteFrameLayout->addWidget(_itemPanel);
 _paletteFrame->pack();
 _paletteFrame->setVisible(true);
}

void SignalHeadIcon::updateItem()
{
 _saveMap = _iconMap; 	// setSignalHead() clears _iconMap.  we need a copy for setIcons()
 setSignalHead(_itemPanel->getTableSelection()->getSystemName());
 setFamily(_itemPanel->getFamilyName());
 QMap<QString, NamedIcon*>* map1 = _itemPanel->getIconMap();
 if (map1!=NULL)
 {
  // map1 may be keyed with NamedBean names.  Convert to local name keys.
  // However perhaps keys are local - See above
  QMap<QString, NamedIcon*>* map2 = new QMap<QString, NamedIcon*>();
  QMapIterator<QString, NamedIcon*> it(* map1);
  while (it.hasNext())
  {
   /*         Entry<String, NamedIcon> entry =*/ it.next();
   map2->insert(ItemPalette::convertText(it.key()), it.value());
  }
  setIcons(map2);
 }   // otherwise retain current map
 displayState(((AbstractSignalHead*)getSignalHead())->getAppearance());
//        jmri.jmrit.catalog->ImageIndexEditor.checkImageIndex();
 _paletteFrame->dispose();
 _paletteFrame = NULL;
// _itemPanel->dispose();
// _itemPanel = NULL;
 invalidate();
}

/*public*/ bool SignalHeadIcon::setEditIconMenu(QMenu* popup)
{
 QAction* editAction = new QAction(tr("Edit Signal Head icon"),this);
 connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));
 popup->addAction(editAction);
 return true;
}

/*protected*/ void SignalHeadIcon::edit()
{
 makeIconEditorFrame(this, "Signal Head", true, NULL);
 _iconEditor->setPickList(PickListModel::signalHeadPickModelInstance());
 QStringListIterator e(_iconMap->keys());
 int i=0;
 while (e.hasNext())
 {
  QString key = e.next();
  _iconEditor->setIcon(i++, key, new NamedIcon(_iconMap->value(key)));
 }
 _iconEditor->makeIconPanel(false);

//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateSignal();
//        }
//    };
 AddIconActionListener* addIconAction = new AddIconActionListener(this);
 _iconEditor->complete(addIconAction, true, false, true);
 _iconEditor->setSelection(getSignalHead());
}

/**
 * replace the icons in _iconMap with those from map, but
 * preserve the scale and rotation.
*/
/*private*/ void SignalHeadIcon::setIcons(QMap<QString, NamedIcon*>* map)
{
 QMap<QString, NamedIcon*>* tempMap = new QMap<QString, NamedIcon*>();
 QMapIterator<QString, NamedIcon*> it(*map);
 while (it.hasNext())
 {
 /*       Entry<String, NamedIcon> entry =*/ it.next();
  QString name = it.key();
  NamedIcon* icon = it.value();
  NamedIcon* oldIcon = _saveMap->value(name);	// setSignalHead() has cleared _iconMap
  if (log->isDebugEnabled()) log->debug("key= "+it.key()+", localKey= "+name+", newIcon= "+icon->getName()+", oldIcon= "+oldIcon->getName());
  if (oldIcon!=NULL)
  {
   icon->setLoad(oldIcon->getDegrees(), oldIcon->getScale(), this);
   icon->setRotation(oldIcon->getRotation(), this);
  }
  tempMap->insert(name, icon);
 }
 _iconMap = tempMap;
}

void SignalHeadIcon::updateSignal()
{
 _saveMap = _iconMap; 	// setSignalHead() clears _iconMap.  we need a copy for setIcons()
 setSignalHead(_iconEditor->getTableSelection()->getDisplayName());
 setIcons(_iconEditor->getIconMap());
 displayState(headState());
 _iconEditorFrame->dispose();
 _iconEditorFrame = NULL;
 _iconEditor = NULL;
 invalidate();
}


/**
 * What to do on click? 0 means
 * sequence through aspects; 1 means
 * alternate the "lit" aspect; 2 means
 * alternate the "held" aspect.
 */
//protected int clickMode = 3;

/*public*/ void SignalHeadIcon::setClickMode(int mode) {
    clickMode = mode;
}
/*public*/ int SignalHeadIcon::getClickMode() {
    return clickMode;
}

/**
 * How to handle lit vs not lit?
 * <P>
 * False means ignore (always show R/Y/G/etc appearance on screen);
 * True means show "dark" if lit is set false.
 * <P>
 * Note that setting the appearance "DARK" explicitly
 * will show the dark icon regardless of how this is set.
 */

/*public*/ void SignalHeadIcon::setLitMode(bool mode)
{
 litMode = mode;
}
/*public*/ bool SignalHeadIcon::getLitMode()
{
 return litMode;
}

/**
 * Change the SignalHead state when the icon is clicked.
 * Note that this change may not be permanent if there is
 * logic controlling the signal head.
 * @param e
 */
/*public*/ void SignalHeadIcon::doMouseClicked(QGraphicsSceneMouseEvent* e)
{
 if (!_editor->getFlag(Editor::OPTION_CONTROLS, isControlling())) return;
 performMouseClicked(e);
}

/**
 * This was added in so that the layout editor can handle the mouseclicked when zoomed in
*/
/*public*/ void SignalHeadIcon::performMouseClicked(QGraphicsSceneMouseEvent* e)
{
 //if (e->isMetaDown() || e->isAltDown() ) return;
 if((e->modifiers()&Qt::MetaModifier) != 0 || (e->modifiers()&Qt::AltModifier) !=0)
  return;
 if (getSignalHead()==NULL)
 {
  log->error("No turnout connection, can't process click");
  return;
 }
 switch (clickMode)
 {
  case 0 :
  {
   switch (getSignalHead()->getAppearance())
   {
    case SignalHead::RED:
    case SignalHead::FLASHRED:
        getSignalHead()->setAppearance(SignalHead::YELLOW);
     //newAppearance = SignalHead::YELLOW;
        break;
    case SignalHead::YELLOW:
    case SignalHead::FLASHYELLOW:
        getSignalHead()->setAppearance(SignalHead::GREEN);
       //newAppearance = SignalHead::GREEN;
        break;
    case SignalHead::GREEN:
    case SignalHead::FLASHGREEN:
        getSignalHead()->setAppearance(SignalHead::RED);
       //newAppearance = SignalHead::RED;
        break;
    default:
     getSignalHead()->setAppearance(SignalHead::RED);
       //newAppearance = SignalHead::RED;
        break;
   }
   return;
 }
 case 1 :
  getSignalHead()->setLit(!getSignalHead()->getLit());
  return;
 case 2 :
  getSignalHead()->setHeld(!getSignalHead()->getHeld());
 return;
 case 3:
 {
  SignalHead* sh = getSignalHead();
  QVector<int> states = sh->getValidStates();
  int state = sh->getAppearance();
  for (int i = 0; i < states.length(); i++) {
//  if (log.isDebugEnabled()) log.debug("state= "+state+" states["+i+"]= "+states[i]);
      if (state == states[i]) {
          i++;
          if (i >= states.length()) {
              i = 0;
          }
          state = states[i];
          break;
      }
  }
  sh->setAppearance(state);
  if (log->isDebugEnabled()) {
      log->debug("Set state= " + state);
  }
  return;
 }
 default:
  log->error("Click in mode "+QString::number(clickMode));
 }
}

//private static boolean warned = false;

/*public*/ void SignalHeadIcon::dispose()
{
 if (getSignalHead()!=NULL)
 {
  getSignalHead()->removePropertyChangeListener((PropertyChangeListener*)this);
//  DefaultSignalHead* head = (DefaultSignalHead*)getSignalHead();
//  disconnect(head, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 namedHead = NULL;
 _iconMap = NULL;
 PositionableIcon::dispose();
}

void SignalHeadIcon::addPropertyChangeListener(PropertyChangeListener * /*l*/)
{
 //pcs->addPropertyChangeListener(l);

}
void SignalHeadIcon::removePropertyChangeListener(PropertyChangeListener */*l*/)
{
 //pcs->removePropertyChangeListener(l);
}
