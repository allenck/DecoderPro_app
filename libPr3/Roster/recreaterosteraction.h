#ifndef RECREATEROSTERACTION_H
#define RECREATEROSTERACTION_H
#include "jmriabstractaction.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT RecreateRosterAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit RecreateRosterAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE RecreateRosterAction(QString s, WindowInterface* wi);
 /*public*/ Q_INVOKABLE RecreateRosterAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Q_INVOKABLE RecreateRosterAction(QString s, QObject *parent);
 ~RecreateRosterAction() {}
 RecreateRosterAction(const RecreateRosterAction& other) : JmriAbstractAction(other.text(), other.icon(), (WindowInterface*)other.parent()) {}
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
  void common();
};
Q_DECLARE_METATYPE(RecreateRosterAction)
#endif // RECREATEROSTERACTION_H
