#include "abstractreportertestbase.h"
#include "assert1.h"
#include "reporter.h"
#include "rfid/reportervariant.h"
#include "abstractreporter.h"

AbstractReporterTestBase::AbstractReporterTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * Tests for the Reporter class
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 *
 * @author Matthew Harris Copyright (C) 2011
 * @author Paul Bender Copyright (C) 2018
 */
// abstract /*public*/ class AbstractReporterTestBase {


    // concrete classes should generate an appropriate report.
    //abstract /*protected*/ QVariant generateObjectToReport();

    //@Test
    /*public*/ void AbstractReporterTestBase::testCtor() {
        // Check that it is not a null object
        Assert::assertNotNull("Created Reporter not null", r->self(), __FILE__, __LINE__);
        // Check that CurrentReport and LastReport return a null object
        Assert::assertNull("CurrentReport at initialisation is 'null'", r->getCurrentReport(), __FILE__, __LINE__);
        Assert::assertNull("LastReport at initialisation is 'null'", r->getLastReport(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterTestBase::testReport() {
        // Report a String
        r->setReport(generateObjectToReport());
        // Check that both CurrentReport and LastReport are not null
        Assert::assertNotNull("CurrentReport Object exists", r->getCurrentReport(), __FILE__, __LINE__);
        Assert::assertNotNull("LastReport Object exists", r->getLastReport(), __FILE__, __LINE__);
        // Check the value of both CurrentReport and LastReport
        Assert::assertEquals("CurrentReport equals LastReport",r->getLastReport(), r->getCurrentReport(), __FILE__, __LINE__);

        // Nothing to report now
        r->setReport(QVariant());
        // Check that CurrentReport returns a null value, but LastReport returns the reported String
        Assert::assertNull("After null report, CurrentReport is null", r->getCurrentReport(), __FILE__, __LINE__);
        Assert::assertNotNull("After null report, LastReport String is not null",r->getLastReport(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterTestBase::testGetBeanType(){
         Assert::assertEquals("bean type",((AbstractReporter*)r->self())->getBeanType(),tr("Reporter"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterTestBase::testPropertyChange() {
        currentReportSeen = false;
        lastReportSeen = false;
       ((AbstractNamedBean*)r->self())->addPropertyChangeListener(new TestReporterListenerO1(this));
        // Report a String
        ((AbstractReporter*)r->self())->setReport(generateObjectToReport());
        // Check that both CurrentReport and LastReport were seen
        Assert::assertTrue("CurrentReport seen", currentReportSeen, __FILE__, __LINE__);
        Assert::assertTrue("LastReport seen", lastReportSeen, __FILE__, __LINE__);

        // Nothing to report now
        currentReportSeen = false;
        lastReportSeen = false;
        r->setReport(QVariant());
        // Check that CurrentReport was seen
        Assert::assertTrue("CurrentReport seen after null", currentReportSeen, __FILE__, __LINE__);
        // Check that LastReport was not seen (no change on null)
        Assert::assertFalse("LastReport seen after null", lastReportSeen, __FILE__, __LINE__);
    }

    //@Override
    /*public*/ void TestReporterListenerO1::propertyChange(PropertyChangeEvent* e){
        if (e->getPropertyName()==("currentReport")) {
            base->currentReportSeen = true;
        } else if (e->getPropertyName() == ("lastReport")) {
            base->lastReportSeen = true;
        }
    }
    //@Before
    //abstract /*public*/ void setUp();

    //@After
    //abstract /*public*/ void tearDown();

