#ifndef ROSTERTEST_H
#define ROSTERTEST_H

#include <QObject>
#include "../temporaryfolder.h"
#include "exceptions.h"
#include "roster.h"

class RosterTest : public QObject
{
    Q_OBJECT
public:
    explicit RosterTest(QObject *parent = nullptr);
    /*public*/ void setUp();
    /*public*/ void tearDown();
    /*public*/ TemporaryFolder* folder;// = new TemporaryFolder();

public slots:
    //@Rule
    /*public*/ void testDirty();
    /*public*/ void testAdd();
    /*public*/ void testDontAddNullEntriesLater();
    /*public*/ void testDontAddNullEntriesFirst();
    /*public*/ void testAddrSearch();
    /*public*/ void testGetByDccAddress();
    /*public*/ void testSearchList();
    /*public*/ void testComboBox();
    /*public*/ void testBackupFile() throw (Exception);
    /*public*/ void testReadWrite() throw (Exception);
    /*public*/ void testAttributeAccess() throw (Exception);
    /*public*/ void testAttributeValueAccess() throw (Exception);
    /*public*/ void testAttributeList() throw (Exception);
    /*public*/ void testDefaultLocation();
    /*public*/ void testProfileOnePointForward();
    /*public*/ void testProfileTwoPointForward();
    /*public*/ void testProfileOnePointReverse();
    /*public*/ void testProfileTwoPointReverse();
    /*public*/ void testProfileTwoPointForwardGetThrottleSetting();
    /*public*/ void testProfileTwoPointReverseGetThrottleSetting();

signals:

public slots:
};

class RTRoster : public Roster
{
    Q_OBJECT
    File* rosterDir;
public:
    RTRoster(File* rosterDir) {this->rosterDir = rosterDir;}
    /*public*/ QString backupFileName(QString name) const;
//    {
//        return (new File(rosterDir, "rosterBackupTest"))->getAbsolutePath();
//    }
};

#endif // ROSTERTEST_H
