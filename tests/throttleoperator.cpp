#include "throttleoperator.h"
#include "addresspanel.h"
#include "throttlewindow.h"
#include "jtogglebutton.h"

/*
 *  Helper class for operating the Throttle Frame.
 *
 *  @author Paul Bender Copyright (C) 2018
 */
///*public*/ class ThrottleOperator extends JFrameOperator {

/*public*/ ThrottleOperator::ThrottleOperator() : JFrameOperator(tr("Throttle"))
{
     //this(tr("ThrottleTitle"));
}

/*public*/ ThrottleOperator::ThrottleOperator(QString title) : JFrameOperator(title)
{
     //super(title);
}

// Address Panel Operations
/*public*/ JInternalFrameOperator* ThrottleOperator::getAddressPanelOperator(){
    return new JInternalFrameOperator(this,tr("Address Panel"));
}

/*private*/ AddressPanel* ThrottleOperator::getAddressPanel(){
//AddressPanel* ap = (AddressPanel*) findSubComponent(
//     new ComponentChooser() {
//               @Override
//               /*public*/ boolean checkComponent(Component c) {
//     if (c instanceof AddressPanel )
//   return true;
//     else return false;
//        }
//               @Override
//        /*public*/ String getDescription() {
//     return "Find AddressSelector";
//        }
//});
 AddressPanel* ap = nullptr;
 //QList<AddressPanel*> list = throttleWindow.
 if(qobject_cast<ThrottleWindow*>(getFrame()))
 {
  throttleWindow = (ThrottleWindow*)getFrame();
  ap = ((ThrottleWindow*)getFrame())->addressPanel;
 }
return ap;
}

// type the address value.
/*public*/ void ThrottleOperator::typeAddressValue(int address){
 JInternalFrameOperator* ifo = getAddressPanelOperator();
 JTextFieldOperator* jtfo = new JTextFieldOperator(ifo); // only one text field in the address panel.
 jtfo->typeText(QString::number(address));
}

// get the address value.
/*public*/ DccLocoAddress* ThrottleOperator::getAddressValue(){
 AddressPanel* ap = getAddressPanel();
 return ap->getCurrentAddress();
}

// get the consist address value.
/*public*/ DccLocoAddress* ThrottleOperator::getConsistAddressValue(){
 AddressPanel* ap = getAddressPanel();
 return ap->getConsistAddress();
}

// set the address value.
/*public*/ void ThrottleOperator::setAddressValue(DccLocoAddress* addr){
 AddressPanel* ap = getAddressPanel();
 ap->setCurrentAddress(addr);
}

// get the consist address value.
/*public*/ Throttle* ThrottleOperator::getAttachedThrottle(){
 AddressPanel* ap = getAddressPanel();
 return ap->getThrottle();
}

/*public*/ void ThrottleOperator::pushSetButton(){
     (new JButtonOperator(this,tr("Set")))->push();
}

/*public*/ bool ThrottleOperator::setButtonEnabled(){
     return (new JButtonOperator(this,tr("Set")))->isEnabled();
}

/*public*/ void ThrottleOperator::pushDispatchButton(){
     (new JButtonOperator(this,tr("Dispatch")))->push();
}
/*public*/ void ThrottleOperator::pushReleaseButton(){
     (new JButtonOperator(this,tr("Release")))->push();
}

/*public*/ bool ThrottleOperator::releaseButtonEnabled(){
     return (new JButtonOperator(this,tr("Release")))->isEnabled();
}

/*public*/ bool ThrottleOperator::dispatchButtonEnabled(){
     return (new JButtonOperator(this,tr("ButtonDispatch")))->isEnabled();
}

/*public*/ void ThrottleOperator::answerStealQuestion(bool steal){
     JDialogOperator* jdo = new JDialogOperator(tr("Steal Throttle"));
     if(steal) {
        (new JButtonOperator(jdo,tr("Yes")))->doClick();
     } else {
        (new JButtonOperator(jdo,tr("No")))->doClick();
     }
}

 /*public*/ void ThrottleOperator::answerShareQuestion(bool share){
     JDialogOperator* jdo = new JDialogOperator(tr("Share Throttle"));
     if(share) {
        (new JButtonOperator(jdo,tr("Yes")))->doClick();
     } else {
        (new JButtonOperator(jdo,tr("ButtonNo")))->doClick();
     }
 }

 // Steal / Share / Cancel dialogue operators
 /*public*/ void ThrottleOperator::answerStealShareQuestionSteal(){
     JDialogOperator* jdo = new JDialogOperator(tr("StealShareRequestTitle"));
     (new JButtonOperator(jdo,tr("StealButton")))->doClick();
 }

 /*public*/ void ThrottleOperator::answerStealShareQuestionShare(){
     JDialogOperator* jdo = new JDialogOperator(tr("StealShareRequestTitle"));
     (new JButtonOperator(jdo,tr("Share")))->doClick();
 }

 /*public*/ void ThrottleOperator::answerStealShareQuestionCancel(){
     JDialogOperator* jdo = new JDialogOperator(tr("StealShareRequestTitle"));
     (new JButtonOperator(jdo,tr("Cancel")))->doClick();
 }

// Function panel operations
/*public*/ JInternalFrameOperator* ThrottleOperator::getFunctionPanelOperator(){
    return new JInternalFrameOperator(this, tr("Function Panel"));
}

/*public*/ void ThrottleOperator::pushFunctionButton(QString function){
     (new JButtonOperator(getFunctionPanelOperator(),function))->push();
}

/*public*/ void ThrottleOperator::pushAlt1Button(){
#if 0
JToggleButton* alt1Button = (JToggleButton*) findSubComponent(
     new ComponentChooser() {
               @Override
               /*public*/ boolean checkComponent(Component c) {
     if (c instanceof JToggleButton ) {
   if(((JToggleButton)c).getText().equals("*")){
      return true;
   } else {
                           return false;
                        }
     } else {
return false;
                   }
        }
               @Override
        /*public*/ String getDescription() {
     return "Find Function Button";
        }
});
JemmyUtil.enterClickAndLeave(alt1Button);
#endif
}

/*public*/ void ThrottleOperator::pushAlt2Button(){
#if 0
JToggleButton alt1Button = (JToggleButton) findSubComponent(
     new ComponentChooser() {
               @Override
               /*public*/ boolean checkComponent(Component c) {
     if (c instanceof JToggleButton ) {
   if(((JToggleButton)c).getText().equals("#")){
      return true;
   } else {
                           return false;
                        }
     } else {
return false;
                   }
        }
               @Override
        /*public*/ String getDescription() {
     return "Find Function Button";
        }
});
JemmyUtil.enterClickAndLeave(alt1Button);
#endif
}

/*public*/ FunctionButton* ThrottleOperator::getFunctionButton(int function){
#if 0
FunctionButton retval = (FunctionButton) findSubComponent(
     new ComponentChooser() {
               @Override
               /*public*/ boolean checkComponent(Component c) {
     if (c instanceof FunctionButton ) {
   if(((FunctionButton)c).getIdentity()==function){
      return true;
   } else {
                           return false;
                        }
     } else {
return false;
                   }
        }
               @Override
        /*public*/ String getDescription() {
     return "Find Function Button";
        }
});
     return retval;
#endif
}

/*public*/ void ThrottleOperator::openFunctionPopupMenu(int function)
{
     FunctionButton* fb = getFunctionButton(function);
     JToggleButtonOperator* jbo = new JToggleButtonOperator(fb);
     jbo->clickForPopup();
     JPopupMenuOperator* jpmo = new JPopupMenuOperator();
  jpmo->pushMenuNoBlock(tr("Properties"));
}

/*public*/ void ThrottleOperator::toggleFunctionMomentary(int function){
  openFunctionPopupMenu(function);
     JDialogOperator* jdo = new JDialogOperator(tr("Edit Function Button"));
     (new JCheckBoxOperator(jdo,tr("Lockable")))->doClick();
     (new JButtonOperator(jdo,tr("Ok")))->doClick();

}

// Control (Speed and Direction) panel operations
/*public*/ JInternalFrameOperator* ThrottleOperator::getControlPanelOperator(){
    return new JInternalFrameOperator(this,
      tr("Control Panel"));
}

/*public*/ void ThrottleOperator::pushStopButton(){
     (new JButtonOperator(getControlPanelOperator(),tr("Stop")))->push();
}

/*public*/ void ThrottleOperator::pushEStopButton(){
     (new JButtonOperator(getControlPanelOperator(),tr("ButtonStop")))->push();
}

/*public*/ void ThrottleOperator::pushIdleButton(){
     (new JButtonOperator(getControlPanelOperator(),tr("ButtonIdle")))->push();
}

/*public*/ void ThrottleOperator::pushForwardButton(){
     (new JRadioButtonOperator(getControlPanelOperator(), tr("ButtonForward")))->push();
}

/*public*/ void ThrottleOperator::pushReverseButton(){
     (new JRadioButtonOperator(getControlPanelOperator(), tr("ButtonReverse")))->push();
}

/*public*/ int ThrottleOperator::getSpeedSliderValue(){
     return (new JSliderOperator(getControlPanelOperator()))->getValue();
}

/*public*/ void ThrottleOperator::setSpeedSlider(int i){
     (new JSliderOperator(getControlPanelOperator()))->setValue(i);
}

/*public*/ void ThrottleOperator::slideSpeedSlider(int i){
     (new JSliderOperator(getControlPanelOperator()))->scrollToValue(i);
}

/*public*/ void ThrottleOperator::speedSliderMaximum(){
     (new JSliderOperator(getControlPanelOperator()))->scrollToMaximum();
}

/*public*/ void ThrottleOperator::speedSliderMinimum(){
     (new JSliderOperator(getControlPanelOperator()))->scrollToMinimum();
}

/*public*/ void ThrottleOperator::openControlPanelPopupMenu(){
  JInternalFrameOperator* jifo  = getControlPanelOperator();
  jifo->clickForPopup();
  JPopupMenuOperator* jpmo = new JPopupMenuOperator();
  jpmo->pushMenuNoBlock(tr("ControlPanelProperties"));
}

/*public*/ void ThrottleOperator::setSpeedStepDisplay(){
  openControlPanelPopupMenu();
     JDialogOperator* jdo = new JDialogOperator(tr("Edit Speed Control Panel"));
     (new JRadioButtonOperator(jdo,tr("ButtonDisplaySpeedSteps")))->doClick();
     (new JButtonOperator(jdo,tr("Ok")))->doClick();

}

/*public*/ void ThrottleOperator::setSpeedSpinner(int i){
     (new JSpinnerOperator(getControlPanelOperator()))->setValue(i);
}

/*public*/ void ThrottleOperator::speedSpinnerMaximum(){
     (new JSpinnerOperator(getControlPanelOperator()))->scrollToMaximum();
}

/*public*/ void ThrottleOperator::speedSpinnerMinimum(){
     (new JSpinnerOperator(getControlPanelOperator()))->scrollToMinimum();
}

/*public*/ void ThrottleOperator::requestClose()
{
 throttleWindow->close();
}
