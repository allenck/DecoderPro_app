#ifndef THROTTLECREATIONACTION_H
#define THROTTLECREATIONACTION_H

#include "jmriabstractaction.h"
#include "libPr3_global.h"

class JmriPanel;
class WindowInterface;
class LIBPR3SHARED_EXPORT ThrottleCreationAction : public JmriAbstractAction
{
    Q_OBJECT
public:
    explicit ThrottleCreationAction(QObject *parent = 0);
    /*public*/ ThrottleCreationAction(QString s, WindowInterface* wi);
    /*public*/ ThrottleCreationAction(QString s, QIcon i, WindowInterface* wi);
 ~ThrottleCreationAction() {}
 ThrottleCreationAction(const ThrottleCreationAction& other) : JmriAbstractAction(other.text(), (QObject*)other.parent()) {}
//    /*public*/ ThrottleCreationAction(QString s);
    /*public*/ JmriPanel* makePanel();

signals:

public slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);

};
Q_DECLARE_METATYPE(ThrottleCreationAction)
#endif // THROTTLECREATIONACTION_H
