#ifndef SIGNALLINGSOURCEFRAME_H
#define SIGNALLINGSOURCEFRAME_H
#include "../LayoutEditor/jmrijframe.h"
#include <QPushButton>
#include "exceptions.h"

class SignalMast;
class SignallingSourcePanel;
class SignallingSourceFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit SignallingSourceFrame(QWidget *parent = 0);
    /*public*/ void initComponents(SignalMast* source) throw (Exception);
 /*public*/ QString getClassName();

signals:

public slots:
private:
    QPushButton* sendButton;
    SignallingSourcePanel* sigPanel;


};

#endif // SIGNALLINGSOURCEFRAME_H
