#ifndef ROSTERENTRYPANETEST_H
#define ROSTERENTRYPANETEST_H

#include <QObject>
#include <QtXml>
#include "rosterentry.h"

class RosterEntryO2;
class RosterEntryPaneTest : public QObject
{
    Q_OBJECT
public:
    explicit RosterEntryPaneTest(QObject *parent = nullptr);
    /*public*/ void setUp();
    /*public*/ void tearDown();
public slots:
    /*public*/ void testCreate();
    /*public*/ void testGuiChanged1();
    /*public*/ void testGuiChanged2();
    /*public*/ void testGuiChanged3();
    /*public*/ void testGuiChanged4();
    /*public*/ void testGuiChanged5();
    /*public*/ void testNotDuplicate();
    /*public*/ void testIsDuplicate();
    /*public*/ void testRenamedDuplicate();

signals:

public slots:
private:
    // statics for test objects
    QDomElement eOld;// = null;
    QDomElement eNew;// = null;
    RosterEntryO2* rOld = nullptr;
    RosterEntryO2* rNew = nullptr;
    QDomDocument doc;
    static Logger* log;
};

class RosterEntryO2 : public RosterEntry
{
  Q_OBJECT
public:
    RosterEntryO2(QObject* parent =0) : RosterEntry(parent){}
    RosterEntryO2(QDomElement e, QObject* parent =0) : RosterEntry(e, parent){}
protected:
    void warnShortLong(QString s);
};

#endif // ROSTERENTRYPANETEST_H
