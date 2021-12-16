#include "positionableicontest.h"
#include "editorscaffold.h"
PositionableIconTest::PositionableIconTest()
{

}
/**
 * Test simple functioning of PositionableIcon
 *
 * @author Paul Bender Copyright (C) 2016
 */
// /*public*/ class PositionableIconTest extends PositionableTestBase {

    //@Test
    /*public*/ void PositionableIconTest::testCtor() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        Assert::assertNotNull("PositionableIcon Constructor", p->self(), __FILE__,  __LINE__);
    }

    //@Before
    //@Override
    /*public*/ void PositionableIconTest::setUp() {
        PositionableTestBase::setUp();
        //if (!GraphicsEnvironment.isHeadless()) {
            editor = new EditorScaffold();
            p = new PositionableIcon(editor, nullptr);
        //}
    }
