#ifndef ROSTERENTRYTEST_H
#define ROSTERENTRYTEST_H

#include <QObject>
#include "exceptions.h"
#include "rosterentry.h"

class RosterEntryTest : public QObject
{
 Q_OBJECT
public:
 explicit RosterEntryTest(QObject *parent = nullptr);
    /*public*/ void testCreate();
    /*public*/ void testPartialLoad();
    /*public*/ void testEmptyLoad();
    /*public*/ void testFullLoad();
    /*public*/ void testFromSchemaFile() throw (JDOMException, IOException);
    /*public*/ void testFromDtdFile() throw (JDOMException, IOException);
    /*public*/ void testStoreFunctionLabel();
    /*public*/ void testModifyDateUnparseable();
    /*public*/ void testDateFormatHistoric();
    /*public*/ void testDateFormatISO();
    /*public*/ void testDateFormatTraditional() throw (ParseException);
    /*public*/ void testStoreFunctionLockable();
    /*public*/ void testXmlLoadStore();
    /*public*/ void testXmlFunctionLabelsLoadStore();
    /*public*/ void testEnsureFilenameExistsNew();
    /*public*/ void testEnsureFilenameExistsOld() throw (IOException);
    /*public*/ void testNoAttribute();
    /*public*/ void testOneAttribute();
    /*public*/ void testReplaceAttribute();
    /*public*/ void testNullAttributeValue();
    /*public*/ void testAttributeList();
    /*public*/ void testXmlAttributesLoadStore();
    /*public*/ void testStoreAttribute();
    /*public*/ void setUp();
    /*public*/ void tearDown();

signals:

public slots:
private:
    static Logger* log;
};

class RosterEntryO1   : public      RosterEntry
{
    Q_OBJECT
        //@Override
        protected:
    void warnShortLong(QString s) {
        }
};

#endif // ROSTERENTRYTEST_H
