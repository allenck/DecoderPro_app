#ifndef RESTARTACTION_H
#define RESTARTACTION_H
#include "jmriabstractaction.h"

class RestartAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 RestartAction(QObject* parent = 0);
 ~RestartAction() {}
 RestartAction(const RestartAction&) : JmriAbstractAction() {}
 /*public*/ RestartAction(QString s, WindowInterface* wi);
 /*public*/ RestartAction(QString s, QIcon i, WindowInterface* wi) ;
 /*public*/ JmriPanel* makePanel();

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory.getLogger(RestartAction.class.getName());

};
Q_DECLARE_METATYPE(RestartAction)
#endif // RESTARTACTION_H
