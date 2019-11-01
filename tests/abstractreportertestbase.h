#ifndef ABSTRACTREPORTERTESTBASE_H
#define ABSTRACTREPORTERTESTBASE_H

#include <QObject>
#include "propertychangelistener.h"

class Reporter;
class AbstractReporterTestBase : public QObject
{
 Q_OBJECT
public:
 explicit AbstractReporterTestBase(QObject *parent = nullptr);
 virtual /*public*/ void setUp()=0;
 virtual /*public*/ void tearDown() = 0;

public slots:
 /*public*/ void testCtor();
 /*public*/ void testReport();
 /*public*/ void testGetBeanType();
 /*public*/ void testPropertyChange();


private:
 /*protected*/ bool currentReportSeen = false;
 /*protected*/ bool lastReportSeen = false;
 // concrete classes should create r in setUp and remove in tearDown
 /*protected*/ Reporter* r = nullptr;


protected:
 virtual /*protected*/ QVariant generateObjectToReport() =0;

signals:

public slots:
 friend class LnReporterTest;
 friend class TestReporterListenerO1;
};
/*public*/ class TestReporterListenerO1 : public PropertyChangeListener
{
 Q_OBJECT
 AbstractReporterTestBase* base;
public:
 TestReporterListenerO1(AbstractReporterTestBase* base) { this->base = base;}
public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e);
};

#endif // ABSTRACTREPORTERTESTBASE_H
