#ifndef WITHROTTLECREATIONACTION_H
#define WITHROTTLECREATIONACTION_H
#include "jmriabstractaction.h"

class UserInterface;
class WiThrottleCreationAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 WiThrottleCreationAction(QObject* parent =0 );
 /*public*/ WiThrottleCreationAction(QString s, WindowInterface* wi);
 /*public*/ WiThrottleCreationAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ WiThrottleCreationAction(QString name, QObject* parent);
 ~WiThrottleCreationAction() {}
 WiThrottleCreationAction(const WiThrottleCreationAction&) : JmriAbstractAction() {}
 /*public*/ JmriPanel* makePanel();

public slots:
 void actionPerformed(ActionEvent* e = 0);

private:
 static UserInterface* UI;
};
Q_DECLARE_METATYPE(WiThrottleCreationAction)
#endif // WITHROTTLECREATIONACTION_H
