#ifndef WITHROTTLECREATIONACTION_H
#define WITHROTTLECREATIONACTION_H
#include "jmriabstractaction.h"

class UserInterface;
class WiThrottleCreationAction : public JmriAbstractAction
{
public:
 WiThrottleCreationAction(QObject* parent);
 /*public*/ WiThrottleCreationAction(QString s, WindowInterface* wi);
 /*public*/ WiThrottleCreationAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ WiThrottleCreationAction(QString name, QObject* parent);

public slots:
 void actionPerformed(ActionEvent* e = 0);

private:
 static UserInterface* UI;


};

#endif // WITHROTTLECREATIONACTION_H
