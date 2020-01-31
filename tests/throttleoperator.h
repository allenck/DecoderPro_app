#ifndef THROTTLEOPERATOR_H
#define THROTTLEOPERATOR_H
#include "jframeoperator.h"

class DccLocoAddress;
class FunctionButton;
class JTextFieldOperator;
class Throttle;
class JInternalFrameOperator;
class ThrottleWindow;
class AddressPanel;
class ThrottleOperator : public JFrameOperator
{
 Q_OBJECT
public:
 ThrottleOperator();
 /*public*/ ThrottleOperator(QString title);
 /*public*/ JInternalFrameOperator* getAddressPanelOperator();
 /*public*/ void typeAddressValue(int address);
 /*public*/ DccLocoAddress* getAddressValue();
 /*public*/ DccLocoAddress* getConsistAddressValue();
 /*public*/ void setAddressValue(DccLocoAddress* addr);
 /*public*/ Throttle* getAttachedThrottle();
 /*public*/ void pushSetButton();
 /*public*/ bool setButtonEnabled();
 /*public*/ void pushDispatchButton();
 /*public*/ void pushReleaseButton();
 /*public*/ bool releaseButtonEnabled();
 /*public*/ bool dispatchButtonEnabled();
 /*public*/ void answerStealQuestion(bool steal);
  /*public*/ void answerShareQuestion(bool share);
  /*public*/ void answerStealShareQuestionSteal();
  /*public*/ void answerStealShareQuestionShare();
  /*public*/ void answerStealShareQuestionCancel();
 /*public*/ JInternalFrameOperator* getFunctionPanelOperator();
 /*public*/ void pushFunctionButton(QString function);
 /*public*/ void pushAlt1Button();
 /*public*/ void pushAlt2Button();
 /*public*/ FunctionButton* getFunctionButton(int function);
 /*public*/ void openFunctionPopupMenu(int function);
 /*public*/ void toggleFunctionMomentary(int function);
 /*public*/ JInternalFrameOperator* getControlPanelOperator();
 /*public*/ void pushStopButton();
 /*public*/ void pushEStopButton();
 /*public*/ void pushIdleButton();
 /*public*/ void pushForwardButton();
 /*public*/ void pushReverseButton();
 /*public*/ int getSpeedSliderValue();
 /*public*/ void setSpeedSlider(int i);
 /*public*/ void slideSpeedSlider(int i);
 /*public*/ void speedSliderMaximum();
 /*public*/ void speedSliderMinimum();
 /*public*/ void openControlPanelPopupMenu();
 /*public*/ void setSpeedStepDisplay();
 /*public*/ void setSpeedSpinner(int i);
 /*public*/ void speedSpinnerMaximum();
 /*public*/ void speedSpinnerMinimum();
 /*public*/ void requestClose();

private:
 ThrottleWindow* throttleWindow = nullptr;
 /*private*/ AddressPanel* getAddressPanel();

};

#endif // THROTTLEOPERATOR_H
