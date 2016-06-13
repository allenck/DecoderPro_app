#ifndef DELETEROSTERGROUPACTION_H
#define DELETEROSTERGROUPACTION_H

#include "jmriabstractaction.h"
#include "libPr3_global.h"

class JmriPanel;
class WindowInterface;
class LIBPR3SHARED_EXPORT DeleteRosterGroupAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit DeleteRosterGroupAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE DeleteRosterGroupAction(QString s, WindowInterface* wi);
 /*public*/ Q_INVOKABLE DeleteRosterGroupAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ DeleteRosterGroupAction(QString s, QWidget* who);
 ~DeleteRosterGroupAction() {}
 DeleteRosterGroupAction(const DeleteRosterGroupAction& other) : JmriAbstractAction(other.text(), (WindowInterface*)other.parent()) {}
 /*public*/ Q_INVOKABLE JmriPanel* makePanel();

signals:

public slots:
 /*public*/ Q_INVOKABLE void actionPerformed(ActionEvent* event = 0);

private:
 QWidget* _who;
 void common();
 bool userOK(QString entry);


};
Q_DECLARE_METATYPE(DeleteRosterGroupAction)
#endif // DELETEROSTERGROUPACTION_H
