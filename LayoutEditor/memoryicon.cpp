#include "memoryicon.h"
#include "layouteditor.h"
#include "defaultprogrammermanager.h"
#include "inputdialog.h"
#include "abstractmemory.h"
#include <QMessageBox>
#include <QColor>
#include "imageicon.h"
#include "lnthrottlemanager.h"
#include "picklistmodel.h"
#include "iconadder.h"

//MemoryIcon::MemoryIcon(QObject *parent) //:
//    //PositionalbleLabel(parent)
//{
//}
/**
 * An icon to display a status of a Memory.<P>
 * <P>
 * The value of the memory can't be changed with this icon.
 *<P>
 * @author Bob Jacobsen  Copyright (c) 2004
 * @version $Revision: 22320 $
 */

// NOTE:
// the original Java class for this class is named "jmri.jmrit.display.MemoryIcon" which
// duplicates "jmri.jmrit.layouteditor.MemoryIcon" which would result in two classes
// with the same name, so this one is renamed "DisplayMemoryIcon" ACK

///*public*/ class MemoryIcon extends PositionableLabel implements java.beans.PropertyChangeListener/*, DropTargetListener*/ {


/*public*/ MemoryIcon::MemoryIcon(QString s, Editor* editor, QObject *parent)
 :    PositionableLabel(s, editor, (Positionable*)parent)
{
    //super(s, editor);
 log = new Logger("DisplayMemoryIcon");
 defaultIcon = NULL;
 map = NULL;
 namedMemory = NULL;
 _itemGroup = NULL;
 memory = NULL;
 _icon = false;
 selectable = false;
 re = NULL;
 flipRosterIcon = false;
 updateBlockValue = false;
    resetDefaultIcon();
    //setIcon(defaultIcon);
    _namedIcon=defaultIcon;
    //updateSize();
    //By default all memory is left justified
    initAfter();
    _popupUtil->setJustification(LEFT);
//    this.setTransferHandler(new TransferHandler());
}

/*public*/ MemoryIcon::MemoryIcon(NamedIcon* s, Editor* editor, QObject *parent):
    PositionableLabel(s,editor,(Positionable*)parent)
{
 //super(s, editor);
 log = new Logger("DisplayMemoryIcon");
 defaultIcon = NULL;
 map = NULL;
 namedMemory = NULL;
 _itemGroup = NULL;
 memory = NULL;
 _icon = true;
 selectable = false;
 re= NULL;
 flipRosterIcon = false;
 updateBlockValue = false;
    //setDisplayLevel(Editor::LABELS);
 _displayLevel = Editor::LABELS;
 defaultIcon = s;
    //updateSize();
 if(_popupUtil == nullptr)
  initAfter();
 _popupUtil->setJustification(LEFT);
//    log->debug("MemoryIcon ctor= "+MemoryIcon.class.getName());
//    this.setTransferHandler(new TransferHandler());
}

/*public*/ Positionable* MemoryIcon::deepClone()
{
 MemoryIcon* pos = new MemoryIcon("", _editor);
 return finishClone((Positionable*)pos);
}

/*public*/ Positionable* MemoryIcon::finishClone(Positionable* p)
{
 MemoryIcon* pos = (MemoryIcon*)p;
 pos->setMemory(namedMemory->getName());
 pos->setOriginalLocation(getOriginalX(), getOriginalY());
 if (map!=NULL)
 {
  //java.util.Iterator<QString> iterator = map.keySet().iterator();
  QMapIterator<QString, NamedIcon*> iterator(*map);
  while (iterator.hasNext())
  {
   iterator.next();
   QString key = iterator.key();
   QString url = iterator.value()->getName();
   pos->addKeyAndIcon(NamedIcon::getIconByName(url), key);
  }
 }
 //return super.finishClone(pos);
 return PositionableLabel::finishClone((Positionable*)pos);
}

/*public*/ void MemoryIcon::resetDefaultIcon() {
    defaultIcon = new NamedIcon(":/resources/icons/misc/X-red.gif",
                        "resources/icons/misc/X-red.gif");
}

/*public*/ void MemoryIcon::setDefaultIcon(NamedIcon* n) {
    defaultIcon = n;
}

/*public*/ NamedIcon* MemoryIcon::getDefaultIcon() {
    return defaultIcon;
}

/*private*/ void MemoryIcon::setMap()
{
 if (map==NULL) map = new QMap<QString, NamedIcon*>();
}

/**
 * Attach a named Memory to this display item
  * @param pName Used as a system/user name to lookup the Memory object
 */
/*public*/ void MemoryIcon::setMemory(QString pName)
{
 if (InstanceManager::getNullableDefault("MemoryManager") != nullptr) {
     try {
         Memory* memory = InstanceManager::memoryManagerInstance()->provideMemory(pName);
         setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, memory));
     } catch (IllegalArgumentException e) {
         log->error(tr("Memory '#1' not available, icon won't see changes").arg(pName));
     }
 } else {
     log->error("No MemoryManager for this protocol, icon won't see changes");
 }
 updateSize();
}

void MemoryIcon::on_propertyChange(QString sType, QVariant /*sOld*/, QVariant sNew)
{
 if(sType == "value" && sNew.type() == QVariant::DateTime)
 {
  //qDebug() <<tr("property change %1 %2 %3").arg(sType).arg(sOld.toString()).arg(sNew.toString());
  QString text = sNew.toDateTime().toString("hh:mm AP");
  setText(text);
  _editor->addToTarget((Positionable*)this);
 }
 else
  log->debug("unhandled property change " + getNameString() + "type=" + sNew.typeName());
}

/**
 * Attached a named Memory to this display item
 * @param m The Memory object
 */
/*public*/ void MemoryIcon::setMemory(NamedBeanHandle<Memory*>* m)
{
 if (namedMemory != NULL)
 {
  getMemory()->removePropertyChangeListener((PropertyChangeListener*)this);
 }
 namedMemory = m;
 if (namedMemory != NULL)
 {
  getMemory()->addPropertyChangeListener((PropertyChangeListener*)this, namedMemory->getName(), "Memory Icon");
  displayState();
  setName(namedMemory->getName());
 }
}

/*public*/ NamedBeanHandle<Memory*>* MemoryIcon::getNamedMemory()
{ return namedMemory; }

/*public*/ Memory* MemoryIcon::getMemory()
{
 if (namedMemory==NULL)
 {
  return NULL;
 }
 return namedMemory->getBean();
}

/*public*/ NamedBean* MemoryIcon::getNamedBean(){
    return getMemory();
}

/*public*/ QMap<QString, NamedIcon*>* MemoryIcon::getMap() { return map; }
// display icons

/*public*/ void MemoryIcon::addKeyAndIcon(NamedIcon* icon, QString keyValue)
{
 if (map == NULL) setMap(); // initialize if needed
  map->insert(keyValue, icon);
    // drop size cache
    //height = -1;
    //width = -1;
 displayState(); // in case changed
}

// update icon as state of Memory changes
/*public*/ void MemoryIcon::propertyChange(PropertyChangeEvent* e)
{
 if (log->isDebugEnabled()) log->debug("property change: "
                                     +e->getPropertyName()
                                     +" is now "+e->getNewValue().toString());
 if (e->getPropertyName()==("value"))
 {
  displayState();
 }
 //if(e->getSource() instanceof jmri.Throttle)
 if(qobject_cast<Throttle*>(e->getSource())!= NULL)
 {
  if(e->getPropertyName()==("IsForward")){
      bool boo = e->getNewValue().toBool();
      if(boo)
          flipIcon(NamedIcon::NOFLIP);
      else
          flipIcon(NamedIcon::HORIZONTALFLIP);
  }
 }
 on_propertyChange(e->getPropertyName(), e->getOldValue(), e->getNewValue());
}

/*public*/ QString MemoryIcon::getNameString() {
    QString name;
    if (namedMemory == NULL) name = tr("Not Connected");
    else if (getMemory()->getUserName()!=NULL)
        name = getMemory()->getUserName()+" ("+getMemory()->getSystemName()+")";
    else
        name = getMemory()->getSystemName();
    return name;
}

/*public*/ void MemoryIcon::setSelectable(bool b) {selectable = b;}
/*public*/ bool MemoryIcon::isSelectable() { return selectable;}

/*public*/ bool MemoryIcon::showPopUp(QMenu* popup)
{
 if (isEditable() && selectable)
 {
  popup->addSeparator();

  QSignalMapper* mapper = new QSignalMapper();
  QListIterator<QString> iterator( map->keys());
  while (iterator.hasNext())
  {
   QString key = iterator.next();
   //String value = ((NamedIcon)map.get(key)).getName();
   AbstractAction* act;
   popup->addAction(act =new AbstractAction(key,this));
   mapper->setMapping(act, key);
   connect(act, SIGNAL(triggered()), mapper, SLOT(map()));
//   {
//       /**
//        *
//        */
//       private static final long serialVersionUID = 8228751338976484794L;

//       public void actionPerformed(ActionEvent e) {
//           String key = e.getActionCommand();
//           setValue(key);
//       }
//   });
  }
  connect(mapper, SIGNAL(mapped(QString)), this, SLOT(on_act_triggered(QString)));
  return true;
 }  // end of selectable
 if (re != NULL)
 {
  popup->addAction(new AbstractAction(tr("Open Throttle"),this));
//     {
//         /**
//          *
//          */
//         private static final long serialVersionUID = -1747046428922716090L;

//         public void actionPerformed(ActionEvent e) {
//             ThrottleFrame tf = ThrottleFrameManager.instance().createThrottleFrame();
//             tf.toFront();
//             tf.getAddressPanel().setRosterEntry(re);
//         }
//     });
#if 0
     //don't like the idea of refering specifically to the layout block manager for this, but it has to be done if we are to allow the panel editor to also assign trains to block, when used with a layouteditor
     if ((InstanceManager::sectionManagerInstance()->getSystemNameList().size()) > 0 && ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getBlockWithMemoryAssigned(getMemory()) != NULL)
     {
   DispatcherFrame df = InstanceManager::getDefault("DispatcherFrame");
         if (df != null) {
             ActiveTrain* at = df.getActiveTrainForRoster(re);
             if (at != NULL) {
                 popup->addAction(new AbstractAction(tr("MenuTerminateTrain")));
//                 {
//                     /**
//                      *
//                      */
//                     private static final long serialVersionUID = 7567050494629070812L;

//                     public void actionPerformed(ActionEvent e) {
//                         df.terminateActiveTrain(at);
//                     }
//                 });
                 popup->addAction(new AbstractAction(Bundle.tr("MenuAllocateExtra")));
//                 {
//                     /**
//                      *
//                      */
//                     private static final long serialVersionUID = 1179666702674214743L;

//                     public void actionPerformed(ActionEvent e) {
//                         //Just brings up the standard allocate extra frame, this could be expanded in the future
//                         //As a point and click operation.
//                         df.allocateExtraSection(e, at);
//                     }
//                 });
                 if (at.getStatus() == ActiveTrain::DONE)
                 {
                     popup->addAction(new AbstractAction(tr("MenuRestartTrain")));
//                     {
//                         /**
//                          *
//                          */
//                         private static final long serialVersionUID = -6796040644749115017L;

//                         public void actionPerformed(ActionEvent e) {
//                             at.allocateAFresh();
//                         }
//                     });
                 }
             }
             else
             {
                 popup->addAction(new AbstractAction(tr("MenuNewTrain")));
//                 {
//                     /**
//                      *
//                      */
//                     private static final long serialVersionUID = -5264943430258540552L;

//                     public void actionPerformed(ActionEvent e) {
//                         if (!df.getNewTrainActive()) {
//                             df.getActiveTrainFrame().initiateTrain(e, re, jmri.InstanceManager.getDefault(jmri.jmrit.display.layoutEditor.LayoutBlockManager.class).getBlockWithMemoryAssigned(getMemory()).getBlock());
//                             df.setNewTrainActive(true);
//                         } else {
//                             df.getActiveTrainFrame().showActivateFrame(re);
//                         }
//                     }

//                 });
             }

         }

     }

     return true;
#endif
 }
 return false;
    return false;
}

void MemoryIcon::on_act_triggered(QString key)
{
 setValue(key);
}

/**
* Text edits cannot be done to Memory text - override
*/
/*public*/ bool MemoryIcon::setTextEditMenu(QMenu* popup)
{
//    popup.add(new AbstractAction(Bundle.getMessage("EditMemoryValue")) {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            editMemoryValue();
//        }
//    });

 QAction* editMemoryValueAction = new QAction(tr("Edit Memory Value"),this);
 popup->addAction(editMemoryValueAction);
 connect(editMemoryValueAction, SIGNAL(triggered()), this, SLOT(on_editMemoryValueAction_triggered()));
 return true;
}
void MemoryIcon::on_editMemoryValueAction_triggered()
{
 QVariant pVal = ((AbstractMemory*)getMemory())->getValue();
 InputDialog dlg(tr("Edit Current Memory Value"), pVal.toString(), NULL, this);
 if(dlg.exec() == QDialog::Accepted)
 {
  QString rslt = dlg.value();
  ((AbstractMemory*)getMemory())->setValue(QVariant::fromValue(rslt));
 }
}

/*protected*/ void MemoryIcon::flipIcon(int flip)
{
 _namedIcon->flip(flip/*, this*/);
 updateSize();
 repaint(); // ??
}

/**
 * Drive the current state of the display from the state of the
 * Memory.
 */
/*public*/ void MemoryIcon::displayState()
{
 if (log->isDebugEnabled()) log->debug("displayState");
 if (namedMemory == NULL)
 {  // use default if not connected yet
  setIcon(defaultIcon);
  updateSize();
  return;
 }

 if(re!=NULL)
 {
  InstanceManager::throttleManagerInstance()->removeListener(re->getDccLocoAddress(), (PropertyChangeListener*)this);
  re=NULL;
 }
 QVariant key = ((AbstractMemory*)getMemory())->getValue();
 displayState(key);
}
/*protected*/ void MemoryIcon::displayState(QVariant key)
{
 if (key != QVariant())
 {
  if (map == NULL)
  {
   QVariant val = key;
   // no map, attempt to show object directly
   //if (val instanceof jmri.jmrit.roster.RosterEntry)
   //if(qobject_cast<RosterEntry*>(val)!=NULL)
   RosterEntry* roster = VPtr<RosterEntry>::asPtr( val);
   if(roster != NULL)
   {
    val = updateIconFromRosterVal(roster);
    flipRosterIcon = false;
    if(val.isNull())
     return;
   }
   //if (val instanceof QString)
//   if(qobject_cast<QString*>(val)!=NULL)
//   {
//    QString str = *(QString*)val;
//    setText(str);
//    if (log->isDebugEnabled()) log->debug("QString str= \""+str+"\" str.trim().length()= "+str.trimmed().length()+
//                                                    ", maxWidth()= "+maxWidth()+", maxHeight()= "+maxHeight());
//                /*  MemoryIconTest says empty strings should show blank */
//    if (str.trimmed().length()==0)
//    {
//     if (getBackground() == (_editor->getScene()->backgroundBrush().color()))
//     {
//      _saveColor = getPopupUtility()->getBackground();
//      if(_editor->getScene()->backgroundBrush().color() == (QColor(Qt::white)))
//      {
//       getPopupUtility()->setBackgroundColor(QColor(Qt::gray));
//      }
//      else
//      {
//       getPopupUtility()->setBackgroundColor(QColor(Qt::white));
//      }
//     }
//    }
//    else
//    {
//     if (_saveColor.isValid())
//     {
//      getPopupUtility()->setBackgroundColor(_saveColor);
//      _saveColor = QColor();
//     }
//    }
//    setIcon(NULL);
//    _icon = false;
//    _text = true;
//   }
   ImageIcon* icon = VPtr<ImageIcon>::asPtr(val);

   if(val.canConvert<QString>())
   {
    QString str = val.toString();
    setText(str);
   }
   else
   {
    //if (val instanceof javax.swing.ImageIcon)
    //if(qobject_cast<ImageIcon*>(val) != NULL)
    if(icon != NULL)
    {
     setIcon((NamedIcon*)icon);
     setText(NULL);
     _icon = true;
     _text = false;
    }

//   else
//   if (val instanceof Number)
//   {
//    setText(val.toString());
//    setIcon(NULL);
//    _icon = false;
//    _text = true;
//   }
   else log->warn("can't display current value of "+namedMemory->getName()+ ", val= "+val.toString()+" of Class "+val.typeName());
   }
  }
  else
  {
   // map exists, use it
   QString sKey = key.toString();
   NamedIcon* newicon = map->value(sKey);
   if (newicon!=NULL)
   {
    setText(NULL);
    PositionableLabel::setIcon(newicon);
   }
   else
   {
    // no match, use default
    setIcon(defaultIcon);
    setText(NULL);
    _icon = true;
    _text = false;
   }
  }
 }
 else
 {
  if (log->isDebugEnabled()) log->debug("memory NULL");
  setIcon(defaultIcon);
  setText(NULL);
  _icon = true;
  _text = false;
 }
 updateSize();
}

/*protected*/ QVariant MemoryIcon::updateIconFromRosterVal(RosterEntry* roster)
{
 re=roster;
// ImageIcon icon = InstanceManager::rosterIconFactoryInstance().getIcon(roster);
// if(icon.getIconWidth()==-1 || icon.getIconHeight()==-1)
// {
//  //the IconPath is still at default so no icon set
//  return roster->titleQString();
// }
// else
 {
  NamedIcon* rosterIcon = new NamedIcon(roster->getIconPath(), roster->getIconPath());
  _text = false;
  _icon = true;
  updateIcon(rosterIcon);

  if(flipRosterIcon)
  {
   flipIcon(NamedIcon::HORIZONTALFLIP);
  }
  InstanceManager::throttleManagerInstance()->attachListener(re->getDccLocoAddress(), (PropertyChangeListener*)this);
  QVariant isForward = ((LnThrottleManager*) InstanceManager::throttleManagerInstance())->getThrottleInfo(re->getDccLocoAddress(), "IsForward");
  if(isForward.isValid())
  {
   if(!isForward.toBool())
    flipIcon(NamedIcon::HORIZONTALFLIP);
  }
  return QVariant();
 }
}

/*public*/ void MemoryIcon::updateSize()
{
 if (_popupUtil->getFixedWidth()==0)
 {
  //setSize(maxWidth(), maxHeight());
  switch (_popupUtil->getJustification())
  {
    case LEFT :     Positionable::setLocation(getOriginalX(), getOriginalY());
                    break;
    case RIGHT :    Positionable::setLocation(getOriginalX()-maxWidth(), getOriginalY());
                    break;
    case CENTRE :   Positionable::setLocation(getOriginalX()-(maxWidth()/2), getOriginalY());
                    break;
  }
  setSize(maxWidth(), maxHeight());
 }
 else
 {
  PositionableLabel::updateSize();
  if(_icon)
  {
   _namedIcon->reduceTo(maxWidthTrue(), maxHeightTrue(), 0.2);
  }
 }
 //_editor->addToTarget((Positionable*)this);
 updateScene();
 if(getGroupName() != "")
  _itemGroup->setName(getGroupName());
}


/*public*/ void MemoryIcon::setOriginalLocation(int x, int y)
{
 originalX=x;
 originalY=y;
 //updateSize();
}

/*public*/ int MemoryIcon::getOriginalX()
{
 return originalX;
}

/*public*/ int MemoryIcon::getOriginalY()
{
 return originalY;
}

/*public*/ void MemoryIcon::setLocation(int x, int y)
{
 if(_popupUtil->getFixedWidth()==0)
 {
  setOriginalLocation(x,y);
 }
 else
 {
  Positionable::setLocation(x,y);
 }
 //JLabel::setLocation(x,y);
 updateScene();
}
#if 1
/*public*/ bool MemoryIcon::setEditIconMenu(QMenu* popup)
{
 QString txt = tr("Edit %1 Item").arg("Memory");

//        popup.add(new AbstractAction(txt) {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    edit();
//                }
//            });
 QAction* editAction = new QAction(txt, this);
 connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));
 popup->addAction(editAction);
 return true;
}

/*protected*/ void MemoryIcon::edit()
{
 makeIconEditorFrame(this, "Memory", true, NULL);
 _iconEditor->setPickList(PickListModel::memoryPickModelInstance());
//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            editMemory();
//        }
//    };
 AddIconActionListener*  addIconAction = new AddIconActionListener(this);
 _iconEditor->complete(addIconAction, false, true, true);
 _iconEditor->setSelection(getMemory());
}
void MemoryIcon::editMemory() {
 setMemory(_iconEditor->getTableSelection()->getDisplayName());
 updateSize();
//    _iconEditorFrame->dispose();
 _iconEditorFrame = NULL;
 _iconEditor = NULL;
 //invalidate();
 update();
}

MemoryIcon::AddIconActionListener::AddIconActionListener(MemoryIcon *parent)
{
 this->parent = parent;
}

void MemoryIcon::AddIconActionListener::actionPerformed(JActionEvent */*e*/)
{
 parent->editMemory();
}

/*public*/ void MemoryIcon::dispose() {
    getMemory()->removePropertyChangeListener((PropertyChangeListener*)this);
//    AbstractNamedBean* bean = (AbstractNamedBean*)getMemory();
//    disconnect(bean, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    namedMemory = NULL;
    if(re!=NULL){
        InstanceManager::throttleManagerInstance()->removeListener(re->getDccLocoAddress(), (PropertyChangeListener*)this);
        re=NULL;
    }
    PositionableLabel::dispose();
}

///*public*/ void doMouseClicked(MouseEvent e) {
//    if (e.getClickCount() == 2) { // double click?
//        editMemoryValue();
//    }
//}

/*protected*/ void MemoryIcon::editMemoryValue(){
//    JTextField* newMemory = new JTextField(20);
//    if (getMemory()->getValue()!=NULL)
//        newMemory->setText(getMemory()->getValue().toString());
//    Object[] options = {"Cancel", "OK", newMemory};
//    int retval = JOptionPane.showOptionDialog(this,
//                                              "Edit Current Memory Value", namedMemory.getName(),
//                                              0, JOptionPane.INFORMATION_MESSAGE, NULL,
//                                              options, options[2] );
    InputDialog* dlg = new InputDialog(tr("Edit Current Memory Value"),getMemory()->getValue().toString(), NULL);
//    if (retval != 1) return;
//    setValue(newMemory.getText());
    if(dlg->exec() == QDialog::Accepted)
    {
     setValue(dlg->value());
    }
    updateSize();
}

#endif
/*public*/ void MemoryIcon::updateBlockValueOnChange(bool boo){
    updateBlockValue = boo;
}

/*public*/ bool MemoryIcon::updateBlockValueOnChange()
{
    return updateBlockValue;
}


/*protected*/ void MemoryIcon::addRosterToIcon(RosterEntry* roster)
{

//     Object[] options = {"Facing West",
//                    "Facing East",
//                    "Do Not Add"};
//     QList<QObject> options;
//     options << (QObject)"Facing West" << "Facing East" << "Do Not Add";
//        int n = JOptionPane.showOptionDialog(this,
//            "Would you like to assign loco "
//            +  roster.titleQString() + " to this location",
//            "Assign Loco",
//            JOptionPane.YES_NO_CANCEL_OPTION,
//            JOptionPane.QUESTION_MESSAGE,
//            NULL,
//            options,
//            options[2]);
 int n = QMessageBox::question(getEditor(), tr("Assign Loco"), tr("Would you like to assign loco ")
                                               +  roster->titleString() + tr(" to this location"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(n==QMessageBox::Cancel)
            return;
        flipRosterIcon = false;
        if(n==QMessageBox::No)
        {
            flipRosterIcon = true;
        }
        RosterEntry* re = VPtr<RosterEntry>::asPtr(getMemory()->getValue());
        if(re == roster)
        {
            //No change in the loco but a change in direction facing might have occured
             updateIconFromRosterVal(roster);
        } else {
            setValue(VPtr<RosterEntry>::asQVariant(roster));
        }
    }

    /*protected*/ void MemoryIcon::setValue(QVariant val)
    {
        getMemory()->setValue(val);
    }

/*public*/ QString MemoryIcon::getGroupName()
{
 return "DisplayMemoryIcon";
}

#if 0
    class TransferHandler extends javax.swing.TransferHandler {

        //@Override
        /*public*/ boolean canImport(JComponent c, DataFlavor[] transferFlavors) {
            for (DataFlavor flavor : transferFlavors) {
                if (RosterEntrySelection.rosterEntryFlavor.equals(flavor)) {
                    return true;
                }
            }
            return false;
        }

        //@Override
        /*public*/ boolean importData(JComponent c, Transferable t) {
            try {
                ArrayList<RosterEntry> REs = RosterEntrySelection.getRosterEntries(t);
                for (RosterEntry roster : REs) {
                    addRosterToMemory(roster);
                }
            } catch(java.awt.datatransfer.UnsupportedFlavorException e){
                log->error(e);
            } catch (java.io.IOException e){
                log->error(e);
            }
            return true;
        }

    }
#endif
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(MemoryIcon.class.getName());
//}
