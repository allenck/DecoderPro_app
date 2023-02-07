#ifndef ABSTRACTPROVIDINGTURNOUTMANAGERTESTBASE_H
#define ABSTRACTPROVIDINGTURNOUTMANAGERTESTBASE_H
#include "abstractmanagertestbase.h"
#include "providingmanager.h"
#include "assert1.h"
#include "junitappender.h"
#include "turnoutmanager.h"

class Field;
class Class;
class AbstractProvidingTurnoutManagerTestBase : public AbstractManagerTestBase //, public ProvidingManager
{
 Q_OBJECT
 //Q_INTERFACES(ProvidingManager)
public:

    AbstractProvidingTurnoutManagerTestBase(QObject* parent = nullptr);
    /*public*/ void testRegisterDuplicateSystemName(TurnoutManager *m, QString s1, QString s2)
            /*throw (PropertyVetoException, NoSuchFieldException,
            NoSuchFieldException, IllegalArgumentException, IllegalAccessException) */;
public slots:
    /*public*/ void testProvideEmpty() /*throw (IllegalArgumentException)*/;
    /*public*/ void testRegisterDuplicateSystemName() /*throw (PropertyVetoException, NoSuchFieldException,
            NoSuchFieldException, IllegalArgumentException, IllegalAccessException )*/;
private:
    static Logger* log;
protected:
//    /*protected*/ Field getField(Class c, QString fieldName);
    // Manager<E> under test - setUp() loads this
    TurnoutManager* l = nullptr;

};

#endif // ABSTRACTPROVIDINGTURNOUTMANAGERTESTBASE_H
