#include "abstractportcontrollertestbase.h"
#include "abstractportcontroller.h"

AbstractPortControllerTestBase::AbstractPortControllerTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * @author Bob Jacobsen Copyright (C) 2015
 */
///*public*/ abstract class AbstractPortControllerTestBase {

//@Test
/*public*/ void AbstractPortControllerTestBase::testisDirtyNotNPE() {
    apc->isDirty();
}

// from here down is testing infrastructure

//@Before
/*public*/ void AbstractPortControllerTestBase::setUp() {
    apc = new AbstractPortControllerScaffold();
}

//@After
/*public*/ void AbstractPortControllerTestBase::tearDown(){
   apc = nullptr;
}



