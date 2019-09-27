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
public slots:
    /*public*/ void testCtor();
    /*public*/ void checkDisposeMethod();
    /*public*/ void testGetConsistType();
    /*public*/ void testSetConsistTypeAdvanced();
    /*public*/ void testSetConsistTypeCS();
    /*public*/ void checkAddressAllowedGood();
    /*public*/ void checkAddressAllowedBad();
    /*public*/ void checkSizeLimitAdvanced();
    /*public*/ void checkContainsAdvanced();
    /*public*/ void checkGetLocoDirectionAdvanced();
    /*public*/ void checkGetSetLocoRosterIDAdvanced() throw (IOException,FileNotFoundException);
    /*public*/ void checkRemoveWithGetRosterIDAdvanced() throw (IOException,FileNotFoundException);
    /*public*/ void checkAddRemoveWithRosterUpdateAdvanced() throw (IOException, FileNotFoundException);

signals:

public slots:
protected:
    /*protected*/ Consist* c = nullptr;

};

#endif // ABSTRACTCONSISTTESTBASE_H
