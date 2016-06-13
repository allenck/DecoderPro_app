#ifndef RENAMEROSTERGROUPACTION_H
#define RENAMEROSTERGROUPACTION_H

#include "jmriabstractaction.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT RenameRosterGroupAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit RenameRosterGroupAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE RenameRosterGroupAction(QString s, WindowInterface* wi);
 /*public*/ Q_INVOKABLE RenameRosterGroupAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Q_INVOKABLE RenameRosterGroupAction(QString s, QWidget* who);
 ~RenameRosterGroupAction() {}
 RenameRosterGroupAction(const RenameRosterGroupAction&) : JmriAbstractAction() {}
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ Q_INVOKABLE void actionPerformed(ActionEvent* event = 0);

private:
 QWidget* _who;
 void common();
};
Q_DECLARE_METATYPE(RenameRosterGroupAction)
#endif // RENAMEROSTERGROUPACTION_H
