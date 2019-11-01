#ifndef PROFILETEST_H
#define PROFILETEST_H

#include <QObject>
#include "exceptions.h"

class TemporaryFolder;
class ProfileTest : public QObject
{
    Q_OBJECT
public:
    explicit ProfileTest(QObject *parent = nullptr);
    /*public*/ static void setUpClass() ;
    /*public*/ static void tearDownClass();
    Q_INVOKABLE/*public*/ void setUp();
    Q_INVOKABLE/*public*/ void tearDown();
public slots:
    /*public*/ void testProfileWithExtension();
    /*public*/ void testSave() throw (IOException);
    /*public*/ void testGetName();
    /*public*/ void testSetName();
    /*public*/ void testGetId();
    /*public*/ void testGetPath();
    /*public*/ void testToString();
    /*public*/ void testHashCode();
    /*public*/ void testEquals();
    /*public*/ void testIsComplete();
    /*public*/ void testGetUniqueId();
    /*public*/ void testContainsProfile();
    /*public*/ void testInProfile();
    /*public*/ void testIsProfile();
    /*public*/ void testCompareTo();

signals:

public slots:
private:
    /*public*/ TemporaryFolder* folder;// = new TemporaryFolder();

};

#endif // PROFILETEST_H
