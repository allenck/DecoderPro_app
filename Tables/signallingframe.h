#ifndef SIGNALLINGFRAME_H
#define SIGNALLINGFRAME_H
#include "../LayoutEditor/jmrijframe.h"
#include <QPushButton>
#include "exceptions.h"

class SignallingPanel;
class SignalMast;
class SignallingFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit SignallingFrame(QWidget *parent = 0);
    /*public*/ void initComponents(SignalMast* source, SignalMast* dest) throw (Exception);
 /*public*/ QString getClassName();

signals:

public slots:
private:
    QPushButton sendButton;
    SignallingPanel* sigPanel;


};

#endif // SIGNALLINGFRAME_H
