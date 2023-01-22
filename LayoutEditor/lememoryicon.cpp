#include "lememoryicon.h"
#include "instancemanager.h"
#include <QAction>
#include <QMenu>
#include "layouteditor.h"
#include <QMessageBox>
#include "imageicon.h"
#include <QSignalMapper>
#include "layouteditor.h"
#include "joptionpane.h"
#include "colorutil.h"

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

/*protected*/ void LEMemoryIcon::addRosterToIcon(RosterEntry* roster)
{
 QVariantList options = {"Facing West",
             "Facing East",
             "Do Not Add"};
         int n = JOptionPane::showOptionDialog(this, // TODO I18N
                 "Would you like to assign loco "
                 + roster->titleString() + " to this location",
                 "Assign Loco",
                 JOptionPane::YES_NO_CANCEL_OPTION,
                 JOptionPane::QUESTION_MESSAGE,
                 QIcon(),
                 options,
                 options[2]);
         if (n == 2) {
             return;
         }
         flipRosterIcon = (n == 0);
         if (VPtr<RosterEntry>::asPtr(getValue()) == roster) {
             //No change in the loco but a change in direction facing might have occurred
             updateIconFromRosterVal(roster);
         } else {
             setValue(VPtr<RosterEntry>::asQVariant(roster));
         }
 }

/*protected*/ QVariant LEMemoryIcon::getValue() {
        if (getMemory() == nullptr) {
            return QVariant();
        }
        return getMemory()->getValue();
}

/*protected*/ void LEMemoryIcon::setValue(QVariant val) {
    getMemory()->setValue(val);
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
