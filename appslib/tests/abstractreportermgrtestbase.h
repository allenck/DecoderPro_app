#ifndef ABSTRACTREPORTERMGRTESTBASE_H
#define ABSTRACTREPORTERMGRTESTBASE_H
#include "propertychangelistener.h"
#include "abstractprovidingreportermanagertestbase.h"

class AbstractReporterMgrTestBase : public AbstractProvidingReporterManagerTestBase
{
 Q_OBJECT
public:
 AbstractReporterMgrTestBase();
 /*abstract*/ virtual /*public*/ void setUp() =0;    	// load l with actual object; create scaffolds as needed, tag @Before

 /*abstract*/ virtual /*public*/ QString getSystemName(QString i) =0;

 static /*protected*/ bool listenerResult;// = false;
public slots:
 /*public*/ void testCreate();
 /*public*/ void testDispose();
 /*public*/ void testProvideName();
 /*public*/ void testReporterProvideReporter();
 /*public*/ void testProvideFailure();
 /*public*/ void testReporterGetBySystemName();
 /*public*/ void testReporterGetByUserName();
 /*public*/ void testReporterGetByDisplayName();
 /*public*/ void testReporterProvideByNumber();
 /*public*/ void testDefaultSystemName();
 /*public*/ void testSingleObject();
 /*public*/ void testMisses();
 /*public*/ void testUpperLower();
 /*public*/ void testRename();

protected:
 /**
  * Max number of Reporters supported.  Override to return 1 if
  * only 1 can be created, for example
  */
 /*protected*/ virtual int maxN() { return 100; }
 /*protected*/ QString getNameToTest1();
 /*protected*/ QString getNameToTest2();

 friend class ListenO6;
};

/*protected*/ class ListenO6 : public PropertyChangeListener {
Q_OBJECT
 AbstractReporterMgrTestBase* base;
public:
 ListenO6(AbstractReporterMgrTestBase* base) { this->base = base;}
public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e);
};

#endif // ABSTRACTREPORTERMGRTESTBASE_H
