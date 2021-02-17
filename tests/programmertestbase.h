#ifndef PROGRAMMERTESTBASE_H
#define PROGRAMMERTESTBASE_H

#include <QObject>
#include "programmer.h"

class ProgrammerTestBase : public QObject
{
    Q_OBJECT
public:
    explicit ProgrammerTestBase(QObject *parent = nullptr);
    /*public*/ virtual void testCtor();
    /*public*/ virtual void testDefault();
    /*public*/ virtual void testGetCanRead();
    /*public*/ virtual void testGetCanWrite();
    /*public*/ virtual void testGetCanReadAddress();
    /*public*/ virtual void testGetCanWriteAddress();
    /*public*/ virtual void testSetGetMode();
    /*public*/ virtual void testSetModeNull();
    /*public*/ virtual void testGetWriteConfirmMode();
    /*public*/ virtual void testWriteCVNullListener() throw (ProgrammerException);
    /*abstract*/ virtual /*public*/ void setUp() {}
    /*abstract*/ virtual /*public*/ void tearDown() {}

signals:

public slots:

protected:
    /*protected*/ Programmer* programmer;

};

#endif // PROGRAMMERTESTBASE_H
