#ifndef CONSISTTOOLACTION_H
#define CONSISTTOOLACTION_H

#include "jmriabstractaction.h"
#include "appslib_global.h"

class JmriPanel;
class WindowInterface;
class APPSLIBSHARED_EXPORT ConsistToolAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit ConsistToolAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE ConsistToolAction(QString s, WindowInterface* wi);
 /*public*/ Q_INVOKABLE ConsistToolAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Q_INVOKABLE ConsistToolAction(QString s, QObject *parent);
 ~ConsistToolAction() {}
 ConsistToolAction(const ConsistToolAction& other) : JmriAbstractAction(other.text(), other.parent()) {}
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ Q_INVOKABLE void actionPerformed(ActionEvent* e = 0);

private:
 void common();
};
 Q_DECLARE_METATYPE(ConsistToolAction)

#endif // CONSISTTOOLACTION_H
