#ifndef PROFILEMANAGERTEST_H
#define PROFILEMANAGERTEST_H

#include <QObject>
#include "temporaryfolder.h"


class ProfileManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit ProfileManagerTest(QObject *parent = nullptr);
    Q_INVOKABLE/*public*/ void setUp();
    Q_INVOKABLE/*public*/ void tearDown();
public slots:
    /*public*/ void testCTor();
    /*public*/ void testSetActiveProfile_Profile() throw (IOException);
    /*public*/ void testSetActiveProfile_String() throw (IOException);

signals:

public slots:
private:
    //@Rule
    /*public*/ TemporaryFolder* folder;// = new TemporaryFolder();

};

#endif // PROFILEMANAGERTEST_H
