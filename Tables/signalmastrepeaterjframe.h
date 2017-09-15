#ifndef SIGNALMASTREPEATERJFRAME_H
#define SIGNALMASTREPEATERJFRAME_H
#include "jmrijframe.h"

class SignalMastRepeaterPanel;
class SignalMastRepeaterJFrame : public JmriJFrame
{
    Q_OBJECT

public:
    SignalMastRepeaterJFrame(QWidget* parent = 0);
private:
    SignalMastRepeaterPanel* sigMastPanel;// = null;
};

#endif // SIGNALMASTREPEATERJFRAME_H
