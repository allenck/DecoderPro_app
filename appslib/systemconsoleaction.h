#ifndef SYSTEMCONSOLEACTION_H
#define SYSTEMCONSOLEACTION_H

#include "jmriabstractaction.h"
#include "appslib_global.h"

class WindowInterface;
class APPSLIBSHARED_EXPORT SystemConsoleAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 explicit SystemConsoleAction(QObject *parent =0);
 /*public*/  SystemConsoleAction(QString s, WindowInterface* wi);
 /*public*/  SystemConsoleAction(QString s, QIcon i, WindowInterface* wi);
 ~SystemConsoleAction() {}
 SystemConsoleAction(const SystemConsoleAction&) : JmriAbstractAction() {}

 QObject* pself() override{return (QObject*)this;}
signals:

public slots:
 /*public*/  void actionPerformed(JActionEvent* e = 0)override;

private:
 void common();
};
Q_DECLARE_METATYPE(SystemConsoleAction)
#endif // SYSTEMCONSOLEACTION_H
