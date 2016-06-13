#ifndef SIMPLETURNOUTCTRLACTION_H
#define SIMPLETURNOUTCTRLACTION_H

#include "jmriabstractaction.h"
#include "appslib_global.h"

class JmriPanel;
class WindowInterface;
class APPSLIBSHARED_EXPORT SimpleTurnoutCtrlAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 explicit SimpleTurnoutCtrlAction(QObject *parent = 0);
 /*public*/ SimpleTurnoutCtrlAction(QString s, WindowInterface* wi) ;
 /*public*/ SimpleTurnoutCtrlAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ SimpleTurnoutCtrlAction(QString s, QObject *parent) ;
 ///*public*/ SimpleTurnoutCtrlAction(QObject *parent);
 ~SimpleTurnoutCtrlAction() {}
 SimpleTurnoutCtrlAction(const SimpleTurnoutCtrlAction& other) : JmriAbstractAction(other.text(), (QObject*)other.parent()) {}
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();

};
Q_DECLARE_METATYPE(SimpleTurnoutCtrlAction)
#endif // SIMPLETURNOUTCTRLACTION_H
