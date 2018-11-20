#ifndef ADDSIGNALMASTJFRAME_H
#define ADDSIGNALMASTJFRAME_H
#include "jmrijframe.h"

class SignalMast;
class AddSignalMastPanel;
class AddSignalMastJFrame : public JmriJFrame
{
public:
    AddSignalMastJFrame(QWidget*parent = 0);
    /*public*/ AddSignalMastJFrame(SignalMast* mast, QWidget* parent = 0);
    /*public*/ void refresh();

private:
    AddSignalMastPanel* sigMastPanel = nullptr;

};

#endif // ADDSIGNALMASTJFRAME_H
