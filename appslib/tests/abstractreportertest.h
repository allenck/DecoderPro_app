#ifndef ABSTRACTREPORTERTEST_H
#define ABSTRACTREPORTERTEST_H

#include <QObject>
#include "propertychangelistener.h"

class Reporter;
class AbstractReporterTest : public QObject
{
    Q_OBJECT
public:
    explicit AbstractReporterTest(QObject *parent = nullptr);
    virtual /*protected*/ QVariant generateObjectToReport()=0;
    /*public*/ void testCtor();
    /*public*/ void testReport();
    /*public*/ void testGetBeanType();
    /*public*/ void testPropertyChange();
    virtual /*public*/ void setUp()=0;
    virtual /*public*/ void tearDown() =0;
signals:

public slots:
private:
protected:
    // concrete classes should create r in setUp and remove in tearDown
    /*protected*/ Reporter* r = nullptr;
    /*protected*/ bool currentReportSeen = false;
    /*protected*/ bool lastReportSeen = false;

    friend class TestReporterListener;
};

/*public*/ class TestReporterListener : public PropertyChangeListener {
    Q_OBJECT
    AbstractReporterTest* test;
public:
    TestReporterListener(AbstractReporterTest* test) {this->test = test;}
public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e){
        if (e->getPropertyName()==("currentReport")) {
            test->currentReportSeen = true;
        } else if (e->getPropertyName()==("lastReport")) {
            test->lastReportSeen = true;
        }
    }
};

#endif // ABSTRACTREPORTERTEST_H
