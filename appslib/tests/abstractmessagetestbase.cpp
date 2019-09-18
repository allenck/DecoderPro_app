#include "abstractmessagetestbase.h"
#include "assert1.h"


AbstractMessageTestBase::AbstractMessageTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * Base tests for messages implementing the jmri.jmrix.Message interface.
 *
 * @author Paul Bender Copyright (C) 2017
 */
//abstract /*public*/ class AbstractMessageTestBase {


//@Before
/// *abstract*/ /*public*/ void setUp();

//@Test
/*public*/ void AbstractMessageTestBase::testCtor() {
    Assert::assertNotNull("exists",m);
}

//@Test
/*public*/ void AbstractMessageTestBase::testToString() {
    Assert::assertNotNull("toString has result",m->toString());
}

//@Test
/*public*/ void AbstractMessageTestBase::testToMonitorString() {
    Assert::assertNotNull("toMonitorString has result",m->toMonitorString());
}
