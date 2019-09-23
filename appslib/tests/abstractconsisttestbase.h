#ifndef ABSTRACTCONSISTTESTBASE_H
#define ABSTRACTCONSISTTESTBASE_H

#include <QObject>
#include "exceptions.h"

class Consist;
class AbstractConsistTestBase : public QObject
{
    Q_OBJECT
public:
    explicit AbstractConsistTestBase(QObject *parent = nullptr);
    virtual /*public*/ void setUp() =0;  // should set the consist under test to c.
    //@After
    virtual /*public*/ void tearDown() = 0; // should clean up the consist c.
    /*@Test*/ /*public*/ void testCtor();
    /*public*/ void checkDisposeMethod();
    /*@Test*/ /*public*/ void testGetConsistType();
    /*@Test*/ /*public*/ void testSetConsistTypeAdvanced();
    /*@Test*/ /*public*/ void testSetConsistTypeCS();
    /*@Test*/ /*public*/ void checkAddressAllowedGood();
    /*@Test*/ /*public*/ void checkAddressAllowedBad();
    /*@Test*/ /*public*/ void checkSizeLimitAdvanced();
    /*@Test*/ /*public*/ void checkContainsAdvanced();
    /*@Test*/ /*public*/ void checkGetLocoDirectionAdvanced();
    /*@Test*/ /*public*/ void checkGetSetLocoRosterIDAdvanced() throw (IOException,FileNotFoundException);
    /*@Test*/ /*public*/ void checkRemoveWithGetRosterIDAdvanced() throw (IOException,FileNotFoundException);
    /*@Test*/ /*public*/ void checkAddRemoveWithRosterUpdateAdvanced() throw (IOException, FileNotFoundException);

signals:

public slots:
protected:
    /*protected*/ Consist* c = nullptr;

};

#endif // ABSTRACTCONSISTTESTBASE_H
