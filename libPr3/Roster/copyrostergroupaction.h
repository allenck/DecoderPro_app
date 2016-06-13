#ifndef COPYROSTERGROUPACTION_H
#define COPYROSTERGROUPACTION_H

#include "jmriabstractaction.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT CopyRosterGroupAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit CopyRosterGroupAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE CopyRosterGroupAction(QString s, WindowInterface* wi);
 /*public*/ Q_INVOKABLE CopyRosterGroupAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Q_INVOKABLE CopyRosterGroupAction(QString s, QWidget* who);
 ~CopyRosterGroupAction() {}
 CopyRosterGroupAction(const CopyRosterGroupAction&) : JmriAbstractAction() {}
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ Q_INVOKABLE void actionPerformed(ActionEvent* event = 0);

private:
 void common();
 QWidget* _who;

};
Q_DECLARE_METATYPE(CopyRosterGroupAction)
#endif // COPYROSTERGROUPACTION_H
