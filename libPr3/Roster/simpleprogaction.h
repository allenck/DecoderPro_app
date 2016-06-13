#ifndef SIMPLEPROGACTION_H
#define SIMPLEPROGACTION_H

#include "jmriabstractaction.h"
#include "libPr3_global.h"

class WindowInterface;
class JmriPanel;
class LIBPR3SHARED_EXPORT SimpleProgAction  : public JmriAbstractAction
{
    Q_OBJECT
public:
    explicit SimpleProgAction(QObject *parent = 0);
    /*public*/ SimpleProgAction(QString s, WindowInterface* wi);
    /*public*/ SimpleProgAction(QString s, QIcon i, WindowInterface* wi);
//    /*public*/ SimpleProgAction(QObject* wi);
 ~SimpleProgAction() {}
 SimpleProgAction(const SimpleProgAction& other) : JmriAbstractAction(other.text(), (WindowInterface*)other.parent()) {}
    // never invoked, because we overrode actionPerformed above
    /*public*/ JmriPanel* makePanel();

signals:

public slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
        void init();

};
Q_DECLARE_METATYPE(SimpleProgAction)
#endif // SIMPLEPROGACTION_H
