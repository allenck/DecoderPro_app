#ifndef PROFILEMANAGERTEST_H
#define PROFILEMANAGERTEST_H

#include <QObject>
#include "temporaryfolder.h"


class ProfileManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit ProfileManagerTest(QObject *parent = nullptr);
    /*public*/ void testCTor();
    /*public*/ void testSetActiveProfile_Profile() throw (IOException);
    /*public*/ void testSetActiveProfile_String() throw (IOException);
    /*public*/ void setUp();
    /*public*/ void tearDown();

signals:

public slots:
private:
    //@Rule
    /*public*/ TemporaryFolder* folder;// = new TemporaryFolder();

};

#endif // PROFILEMANAGERTEST_H
