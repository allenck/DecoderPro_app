#include "memoryicon.h"
#include "instancemanager.h"
#include <QAction>
#include <QMenu>
#include "layouteditor.h"
#include <QMessageBox>
#include "imageicon.h"
#include "abstractmemory.h"
#include <QSignalMapper>
#include "rostericonfactory.h"
#include "path.h"

//MemoryIcon::MemoryIcon(QObject *parent) :
//    DisplayMemoryIcon(parent)
//{
//}
// This is the same name as display.MemoryIcon, but a very
// separate class. That's not good. Unfortunately, it's too
// hard to disentangle that now because it's resident in the
// panel file that have been written out, so we just annote
// the fact.
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="NM_SAME_SIMPLE_NAME_AS_SUPERCLASS")
//public class MemoryIcon extends jmri.jmrit.display.MemoryIcon {


/*public*/ MemoryIcon::MemoryIcon(QString s, Editor* panel, QObject* parent)
 : DisplayMemoryIcon(s, panel, parent)
{
 //super(s, panel);
 QString instring = s;
 log = new Logger("MemoryIcon");

 log->debug(tr("MemoryIcon ctor= ") + this->metaObject()->className());
 lBlock = NULL;
 setBackground(panel->getBackgroundColor());

}
/*public*/ MemoryIcon::MemoryIcon(NamedIcon* s, Editor* editor, QObject* parent): DisplayMemoryIcon(s,editor,parent)
{
 //super(s, editor);
 log = new Logger("MemoryIcon");
 lBlock = NULL;

 //setDisplayLevel(Editor::LABELS);
 _displayLevel = Editor::LABELS;
 defaultIcon = s;
 //updateSize();
 _popupUtil->setJustification(LEFT);
 log->debug("MemoryIcon ctor= MemoryIcon");
//    this.setTransferHandler(new TransferHandler());
}

/*public*/ void MemoryIcon::setText(QString text)
{
 if (text==NULL || text.length()==0)
 {
  DisplayMemoryIcon::setText(defaultText);
 }
 else
 {
  DisplayMemoryIcon::setText(text);
 }
}


/*public*/ LayoutBlock* MemoryIcon::getLayoutBlock(){
    return lBlock;
}

/*public*/ void MemoryIcon::setLayoutBlock(LayoutBlock* lb)
{
 lBlock = lb;
}

/*public*/ void MemoryIcon::displayState()
{
 if(log->isDebugEnabled()) log->debug("displayState()");

 if (namedMemory == NULL) {  // use default if not connected yet
     setIcon(defaultIcon);
     updateSize();
     return;
 }
 if (re != NULL) {
     InstanceManager::throttleManagerInstance()->removeListener(re->getDccLocoAddress(), (PropertyChangeListener*)this);
     re = NULL;
 }
 QVariant key = getMemory()->getValue();
 displayState(key);
}

/*protected*/ void MemoryIcon::displayState(QVariant key)
{
 if(log->isDebugEnabled()) log->debug(tr("displayState(%1)").arg(key.toString()));
if (key != QVariant()) {
    if (map == NULL) {
        QVariant val = key;
        // no map, attempt to show object directly
        //if (val instanceof jmri.jmrit.roster.RosterEntry)
        if(VPtr<RosterEntry>::asPtr(val)!= NULL)
        {
            RosterEntry* roster = VPtr<RosterEntry>::asPtr(val);
            val = updateIconFromRosterVal(roster);
            flipRosterIcon = false;
            if (val == QVariant()) {
                return;
            }
        }
        //if (val instanceof String)
        if(val.toString() != "")        {
            QString str = val.toString();
            _icon = false;
            _text = true;
            setText(str);
            updateIcon(NULL);
            if (log->isDebugEnabled()) {
                log->debug("String str= \"" + str + "\" str.trim().length()= " + str.trimmed().length());
                log->debug("  maxWidth()= " + QString::number(maxWidth()) + ", maxHeight()= " + QString::number(maxHeight()));
                log->debug(tr("  getBackground(): %1").arg(ColorUtil::colorToColorName(getBackground())));
                log->debug(tr("  _editor.getTargetPanel().getBackground(): %1").arg(ColorUtil::colorToColorName( _editor->getTargetPanel()->backgroundBrush().color())));
//                log->debug(tr("  setAttributes to getPopupUtility(%1) with").arg(getPopupUtility()));
//                log->debug(tr("     hasBackground() %1").arg(getPopupUtility()->hasBackground()));
//                log->debug(tr("     getBackground() ^1").arg(ColorUtil::colorToColorName(getPopupUtility()->getBackground())));
//                log->debug(tr("    on editor %1").arg(_editor));
            }
//            _editor->setAttributes(getPopupUtility(), this, true);
        }
        //else if (val instanceof javax.swing.ImageIcon)
        else if(VPtr<ImageIcon>::asPtr(val) != NULL)
        {
            _icon = true;
            _text = false;
            setIcon(VPtr<NamedIcon>::asPtr(val));
            setText(NULL);
        }
//        else if (val instanceof Number) { // see string
//            _icon = false;
//            _text = true;
//            setText(val.toString());
//            setIcon(NULL);
//        }
        else {
            log->warn("can't display current value of " + getNameString()
                    + ", val= " + val.toString() + " of Class " + /*val.getClass().getName()*/val.typeName());
        }
    } else {
        // map exists, use it
        NamedIcon* newicon = map->value(key.toString());
        if (newicon != NULL) {

            setText(NULL);
            DisplayMemoryIcon::setIcon(newicon);
        } else {
            // no match, use default
            _icon = true;
            _text = false;
            setIcon(defaultIcon);
            setText(NULL);
        }
    }
 }
 else
 {
  if (log->isDebugEnabled()) {
      log->debug("object NULL");
  }
  _icon = true;
  _text = false;
  setIcon(defaultIcon);
  setText(NULL);
 }
updateSize();
}


//@Override
/*public*/ void MemoryIcon::updateSize() {
    if (_popupUtil->getFixedWidth() == 0) {
        //setSize(maxWidth(), maxHeight());
        switch (_popupUtil->getJustification()) {
            case LEFT:
                DisplayMemoryIcon::setLocation(getOriginalX(), getOriginalY());
                break;
            case RIGHT:
                DisplayMemoryIcon::setLocation(getOriginalX() - maxWidth(), getOriginalY());
                break;
            case CENTRE:
                DisplayMemoryIcon::setLocation(getOriginalX() - (maxWidth() / 2), getOriginalY());
                break;
            default:
                log->warn(tr("Unhandled justification code: %1").arg(_popupUtil->getJustification()));
                break;
        }
        setSize(maxWidth(), maxHeight());
    } else {
        DisplayMemoryIcon::updateSize();
        if (_icon && _namedIcon != nullptr) {
            _namedIcon->reduceTo(maxWidthTrue(), maxHeightTrue(), 0.2);
        }
    }
}


/*public*/ void MemoryIcon::setOriginalLocation(int x, int y) {
    originalX = x;
    originalY = y;
    updateSize();
}

/*public*/ int MemoryIcon::getOriginalX() {
    return originalX;
}

/*public*/ int MemoryIcon::getOriginalY() {
    return originalY;
}

//@Override
/*public*/ void MemoryIcon::setLocation(int x, int y) {
    if (_popupUtil->getFixedWidth() == 0) {
        setOriginalLocation(x, y);
    } else {
        DisplayMemoryIcon::setLocation(x, y);
    }
}

//@Override
/*public*/ bool MemoryIcon::setEditIconMenu(QMenu* popup) {
    QString txt = tr("Edit %1 Icon...").arg(tr("Memory"));
    AbstractAction* act;
    popup->addAction(act = new AbstractAction(txt, this));//
//    {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            edit();
//        }
//    });
//    return true;
      connect(act, SIGNAL(triggered(bool)), this, SLOT(edit()));
}

//@Override
/*protected*/ void MemoryIcon::edit() {
    makeIconEditorFrame(this, "Memory", true, nullptr);
    _iconEditor->setPickList(PickListModel::memoryPickModelInstance());
//    ActionListener addIconAction = (ActionEvent a) -> {
//        editMemory();
//    };
    MIActionListener* addIconAction = new MIActionListener(this);
    _iconEditor->complete(addIconAction, false, true, true);
    _iconEditor->setSelection(getMemory());
}

void MemoryIcon::editMemory() {
    setMemory(_iconEditor->getTableSelection()->getDisplayName());
    updateSize();
    _iconEditorFrame->dispose();
    _iconEditorFrame = nullptr;
    _iconEditor = nullptr;
    update();
}

/*protected*/ QVariant MemoryIcon::updateIconFromRosterVal(RosterEntry* roster)
{
    re = roster;
    ImageIcon* icon = ((RosterIconFactory*)InstanceManager::getDefault("RosterIconFactory"))->getIcon(roster);
    if (icon == NULL || icon->getIconWidth() == -1 || icon->getIconHeight() == -1) {
        //the IconPath is still at default so no icon set
        return roster->titleString();
    } else {
        NamedIcon* rosterIcon = new NamedIcon(roster->getIconPath(), roster->getIconPath());
        _text = false;
        _icon = true;
        updateIcon(rosterIcon);

        if (flipRosterIcon) {
            flipIcon(NamedIcon::HORIZONTALFLIP);
        }
        InstanceManager::throttleManagerInstance()->attachListener(re->getDccLocoAddress(), (PropertyChangeListener*)this);
        QVariant isForward = InstanceManager::throttleManagerInstance()->getThrottleInfo(re->getDccLocoAddress(), "IsForward");
        if (isForward != QVariant()) {
            if (! isForward.toBool()) {
                flipIcon(NamedIcon::HORIZONTALFLIP);
            }
        }
    }
    return QVariant();
}

//JCheckBoxMenuItem  updateBlockItem = new JCheckBoxMenuItem("Update Block Details");

#if 1
//@Override
/*public*/ bool MemoryIcon::showPopUp(QMenu* popup)
{
 if (isEditable())
 {
  QAction* updateBlockItemAction = new QAction("Update Block Details", this);
  updateBlockItemAction->setCheckable(true);
  popup->addAction(updateBlockItemAction);
  updateBlockItemAction->setChecked(updateBlockValueOnChange());
//        updateBlockItemAction.addActionListener(new ActionListener(){
//            public void actionPerformed(java.awt.event.ActionEvent e) {
//                updateBlockValueOnChange(updateBlockItem.isSelected());
//            }
//        });
  connect(updateBlockItemAction, SIGNAL(toggled(bool)), this, SLOT(on_updateBlockItemAction_toggled(bool)));
 }  // end of selectable
 return DisplayMemoryIcon::showPopUp(popup);
}
#else
/*public*/ bool MemoryIcon::showPopUp(QMenu* popup)
{
 if (isEditable() && selectable)
 {
  popup->addSeparator();

  QSignalMapper mapper;
  QListIterator<QString> iterator( map->keys());
  while (iterator.hasNext())
  {
   QString key = iterator.next();
   //String value = ((NamedIcon)map.get(key)).getName();
   AbstractAction* act;
   popup->addAction(act =new AbstractAction(key,this));
   mapper.setMapping(act, key);
   connect(act, SIGNAL(triggered()), &mapper, SLOT(map()));
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
  connect(&mapper, SIGNAL(mapped(QString)), this, SLOT(on_act_triggered(QString)));
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
         if (df != NULL) {
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
}
#endif

void MemoryIcon::on_updateBlockItemAction_toggled(bool bState)
{
 updateBlockValueOnChange(bState);
}

///*public*/ void MemoryIcon::setMemory(QString pName)
//{
// DisplayMemoryIcon::setMemory(pName);
// //lBlock = InstanceManager::layoutBlockManagerInstance().getBlockWithMemoryAssigned(getMemory());
// LayoutEditor* LayoutEditor = qobject_cast<LayoutEditor*>(DisplayMemoryIcon::getEditor());
// if(myLayoutEditor != NULL)
// lBlock = myLayoutEditor->layoutBlockManager->getBlockWithMemoryAssigned(getMemory());
//}
/**
 * Attached a named Memory to this display item
 *
 * @param pName Used as a system/user name to lookup the Memory object
 */
/*public*/ void MemoryIcon::setMemory(QString pName)
{
 if (InstanceManager::memoryManagerInstance() != NULL)
 {
  Memory* memory = InstanceManager::memoryManagerInstance()->
             provideMemory(pName);
  if (memory != NULL)
  {
   setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, memory));
  }
  else
  {
   log->error("Memory '" + pName + "' not available, icon won't see changes");
  }
 }
 else
 {
  log->error("No MemoryManager for this protocol, icon won't see changes");
 }
 updateSize();
}

/**
 * Attached a named Memory to this display item
 *
 * @param m The Memory object
 */
/*public*/ void MemoryIcon::setMemory(NamedBeanHandle<Memory*>* m)
{
 if (namedMemory != NULL)
 {
  getMemory()->removePropertyChangeListener((PropertyChangeListener*)this);
  disconnect(getMemory()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 namedMemory = m;
 if (namedMemory != NULL)
 {
  getMemory()->addPropertyChangeListener((PropertyChangeListener*)this, namedMemory->getName(), "Memory Icon");
  connect(getMemory()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  displayState();
  setName(namedMemory->getName());
 }
}

/*public*/ NamedBeanHandle<Memory*>* MemoryIcon::getNamedMemory() {
    return namedMemory;
}

/*public*/ Memory* MemoryIcon::getMemory()
{
 if (namedMemory == NULL) {
     return NULL;
 }
 return namedMemory->getBean();
}

/*public*/ NamedBean* MemoryIcon::getNamedBean()
{
 return getMemory();
}

/*public*/ QString MemoryIcon::getNameString()
{
 QString name;
 if (namedMemory == NULL)
 {
  name = tr("Not Connected");
 } else if (getMemory()->getUserName() != NULL)
 {
  name = getMemory()->getUserName() + " (" + getMemory()->getSystemName() + ")";
 }
 else
 {
  name = getMemory()->getSystemName();
 }
 return name;
}

//@Override
/*protected*/ void MemoryIcon::setValue(QVariant obj)
{
 if(updateBlockValue && lBlock!=NULL)
 {
   lBlock->getBlock()->setValue(obj);
 }
 else
 {
  getMemory()->setValue(obj);
  updateSize();
 }
}

/*protected*/ void MemoryIcon::addRosterToMemory(RosterEntry* roster)
{
 //if(!jmri.InstanceManager.layoutBlockManagerInstance().isAdvancedRoutingEnabled() || lBlock==NULL){
 LayoutEditor* myLayoutEditor = qobject_cast<LayoutEditor*>(DisplayMemoryIcon::getEditor());

 if(myLayoutEditor->layoutBlockManager->isAdvancedRoutingEnabled() || lBlock==NULL)
 {
  DisplayMemoryIcon::addRosterToMemory(roster);
  return;
 }

 int paths = lBlock->getNumberOfThroughPaths();
 Block* srcBlock=NULL;
 Block* desBlock=NULL;
 for(int i = 0; i<paths; i++)
 {
  if(lBlock->isThroughPathActive(i))
  {
   srcBlock = lBlock->getThroughPathSource(i);
   desBlock = lBlock->getThroughPathDestination(i);
   break;
  }
 }
 int dirA;
 int dirB;
 if(srcBlock!=NULL && desBlock!=NULL)
 {
  dirA = lBlock->getNeighbourDirection(srcBlock);
  dirB = lBlock->getNeighbourDirection(desBlock);
 }
 else
 {
  dirA = Path::EAST;
  dirB = Path::WEST;
 }

// QList<QObject*> options;
// options << "Facing "+Path::decodeDirection(dirB) << "Facing "+Path::decodeDirection(dirA) << "Do Not Add";
// int n = JOptionPane.showOptionDialog(this,
//        "Would you like to assign loco "
//        +  roster.titleString() + " to this location",
//        "Assign Loco",
//        JOptionPane.YES_NO_CANCEL_OPTION,
//        JOptionPane.QUESTION_MESSAGE,
//        NULL,
//        options,
//        options[2]);
 int n = QMessageBox::question(DisplayMemoryIcon::getEditor(), tr("Assign Loco"), tr("Would you like to assign loco ")
                                 +  roster->titleString() + tr(" to this location"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
 if(n==QMessageBox::Cancel)
        return;
 if(n==QMessageBox::Yes)
 {
  flipRosterIcon = true;
  if(updateBlockValue)
   lBlock->getBlock()->setDirection(dirB);
 }
 else
 {
  flipRosterIcon = false;
  if(updateBlockValue)
    lBlock->getBlock()->setDirection(dirA);
 }
 if(getMemory()->getValue()==VPtr<RosterEntry>::asQVariant(roster))
 {
  //No change in the loco but a change in direction facing might have occured
  updateMemoryFromRosterVal(roster);
 }
 else
 {
  setValue(VPtr<RosterEntry>::asQVariant(roster));
 }
}

// update icon as state of Memory changes
 /*public*/ void MemoryIcon::propertyChange(PropertyChangeEvent* e)
{
  if (log->isDebugEnabled())
  {
   log->debug("property change: "
           + e->getPropertyName()
           + " is now " + e->getNewValue().toString());
  }
  if (e->getPropertyName()==("value"))
  {
   displayState();
  }
  //if (e->getSource() instanceof jmri.Throttle)
  if(qobject_cast<Throttle*>(e->getSource()) != NULL)
  {
   if (e->getPropertyName()==("IsForward"))
   {
    bool boo =  e->getNewValue().toBool();
    if (boo)
    {
     flipIcon(NamedIcon::NOFLIP);
    } else
    {
     flipIcon(NamedIcon::HORIZONTALFLIP);
    }
   }
  }
 }
#if 0
/*public*/ bool MemoryIcon::updateScene()
{
 QGraphicsPixmapItem* item = NULL;
 QGraphicsTextItem* itemText = NULL;
 QGraphicsRectItem* rItem = NULL;
 if(_itemGroup != NULL)
 {
  QList<QGraphicsItem*> l = _itemGroup->childItems();
  foreach(QGraphicsItem* it, l)
  {
   if(qgraphicsitem_cast<QGraphicsPixmapItem*>(it) != NULL)
    item = qgraphicsitem_cast<QGraphicsPixmapItem*>(it);
   if(qgraphicsitem_cast<QGraphicsTextItem*>(it) != NULL)
    itemText = qgraphicsitem_cast<QGraphicsTextItem*>(it);
   if(qgraphicsitem_cast<QGraphicsRectItem*>(it) != NULL)
    rItem = qgraphicsitem_cast<QGraphicsRectItem*>(it);

   //_itemGroup->removeFromGroup(item);
  }
 }
 else
   _itemGroup = new QGraphicsItemGroup;

 if(isIcon())
 {
  QPixmap pixmap = QPixmap::fromImage(getIcon()->getImage());
  //QGraphicsPixmapItem* item = g2->addPixmap(pixmap);
  if(item != NULL)
   item->setPixmap(pixmap);
  else
   item = new QGraphicsPixmapItem(pixmap, _itemGroup);
  item->setPos(getX(), getY());
  if(pixmap.isNull())
   qDebug() << "No pixmap";
  //_itemGroup->addToGroup(item);
 }
 else
 {
  if(itemText != NULL)
   itemText->setPlainText(getText());
  else
   itemText = new QGraphicsTextItem(getText());
  itemText->setFont(getFont());
  itemText->setDefaultTextColor(getForeground());
  //itemText->setPos(getX(), getY());
//  if(isOpaque())
  {
   QRectF ir = itemText->boundingRect();
   int margin = getPopupUtility()->getMargin();
   QRectF r = QRectF(ir.x()-margin,ir.y()-margin,ir.right()+margin*2,ir.bottom()+margin*2);
   if(rItem != NULL)
    rItem->setRect(r);
   else
    rItem = new QGraphicsRectItem(r,_itemGroup);
   //rItem->setPos(getX(), getY());
   if(isOpaque())
    rItem->setBrush( QBrush(getBackground()));
   if(getPopupUtility()->getBorderSize() == 0)
    rItem->setPen(Qt::NoPen);
   else
    rItem->setPen(QPen(QBrush(getPopupUtility()->getBorderColor()), getPopupUtility()->getBorderSize()));
  }

  _itemGroup->addToGroup(itemText);
  _itemGroup->setPos(getX(), getY());
 }

 //_itemGroup->setPos(getX(), getY());
 if(showTooltip()) _itemGroup->setToolTip(getTooltip());
 if(getDegrees() != 0)
 {
  //m->item->rotate(l->getDegrees());
  QPointF center = itemText->boundingRect().center();
  _itemGroup->setTransformOriginPoint(center);
  _itemGroup->setRotation( getDegrees());
 }
 _itemGroup->setZValue(getDisplayLevel());
 _itemGroup->update();
 return true;
}
#endif
/*public*/ QString MemoryIcon::getGroupName()
{
 return "MemoryIcon";
}
