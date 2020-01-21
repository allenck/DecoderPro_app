#ifndef SIGNALMASTREPEATERJFRAME_H
#define SIGNALMASTREPEATERJFRAME_H
#include "jmrijframe.h"

class SignalMastRepeaterPanel;
class SignalMastRepeaterJFrame : public JmriJFrame
{
    Q_OBJECT

public:
    SignalMastRepeaterJFrame(QWidget* parent = 0);
    /*public*/ QString getClassName();

private:
    SignalMastRepeaterPanel* sigMastPanel;// = null;
};

#endif // SIGNALMASTREPEATERJFRAME_H
