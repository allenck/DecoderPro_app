#include "lememoryicon.h"
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
#include "dispatcherframe.h"
#include "activetrain.h"
#include "activatetrainframe.h"
#include "layouteditor.h"

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


/*public*/ LEMemoryIcon::LEMemoryIcon(QString s, LayoutEditor* panel, QObject* parent)
 : MemoryIcon(s, panel, parent)
{
 //super(s, panel);
 log = new Logger("MemoryIcon");

 log->debug(tr("MemoryIcon ctor= ") + this->metaObject()->className());
 lBlock = NULL;
 setBackground(panel->getBackgroundColor());
}

/*public*/ void LEMemoryIcon::setText(QString text)
{
 if (text==NULL || text.length()==0)
 {
  LEMemoryIcon::setText(defaultText);
 }
 else
 {
  LEMemoryIcon::setText(text);
 }
}


/*public*/ LayoutBlock* LEMemoryIcon::getLayoutBlock(){
    return lBlock;
}

/*public*/ void LEMemoryIcon::setLayoutBlock(LayoutBlock* lb)
{
 lBlock = lb;
}

/*public*/ void LEMemoryIcon::displayState()
{
 if(log->isDebugEnabled()) log->debug("displayState()");

 if (getMemory() == NULL) {  // use default if not connected yet
     setText(defaultText);
     updateSize();
     return;
 }
 if (re != NULL) {
     InstanceManager::throttleManagerInstance()->removeListener(re->getDccLocoAddress(), (PropertyChangeListener*)this);
     re = NULL;
 }
 QVariant key = getMemory()->getValue();
 if (key != QVariant())
 {
  if (map == NULL)
  {
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
            LEMemoryIcon::setIcon(newicon);
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



//JCheckBoxMenuItem  updateBlockItem = new JCheckBoxMenuItem("Update Block Details");

/*public*/ bool LEMemoryIcon::showPopUp(QMenu* popup)
{
 if (isEditable())
 {
     popup->addAction(updateBlockItem);
     updateBlockItem->setCheckable(true);
     updateBlockItem->setChecked(updateBlockValueOnChange());
//     updateBlockItem.addActionListener((java.awt.event.ActionEvent e) -> {
//         updateBlockValueOnChange(updateBlockItem.isSelected());
//     });
     connect(updateBlockItem, SIGNAL(triggered(bool)), this, SLOT(on_updateBlockItemAction_toggled(bool)));
 }  // end of selectable
 return LEMemoryIcon::showPopUp(popup);
}

void LEMemoryIcon::on_updateBlockItemAction_toggled(bool bState)
{
 updateBlockValueOnChange(bState);
}

//@Override
/*public*/ void LEMemoryIcon::setMemory(QString pName)
{
 LEMemoryIcon::setMemory(pName);
 //lBlock = InstanceManager::layoutBlockManagerInstance().getBlockWithMemoryAssigned(getMemory());
 lBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getBlockWithMemoryAssigned(getMemory());
}


//@Override
/*protected*/ void LEMemoryIcon::setValue(QVariant obj)
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

/*protected*/ void LEMemoryIcon::addRosterToIcon(RosterEntry* roster)
{
 //if(!jmri.InstanceManager.layoutBlockManagerInstance().isAdvancedRoutingEnabled() || lBlock==NULL){
 LayoutEditor* myLayoutEditor = qobject_cast<LayoutEditor*>(LEMemoryIcon::getEditor());

 if(myLayoutEditor->layoutBlockManager->isAdvancedRoutingEnabled() || lBlock==NULL)
 {
  LEMemoryIcon::addRosterToIcon(roster);
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
 int n = QMessageBox::question(LEMemoryIcon::getEditor(), tr("Assign Loco"), tr("Would you like to assign loco ")
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
  updateIconFromRosterVal(roster);
 }
 else
 {
  setValue(VPtr<RosterEntry>::asQVariant(roster));
 }
}

// update icon as state of Memory changes
 /*public*/ void LEMemoryIcon::propertyChange(PropertyChangeEvent* e)
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
