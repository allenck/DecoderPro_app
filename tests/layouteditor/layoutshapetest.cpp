#include "layoutshapetest.h"
#include "junitutil.h"
#include "layoutshape.h"
#include "layouteditor.h"
#include "assert1.h"
#include "mathutil.h"

LayoutShapeTest::LayoutShapeTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test simple functioning of LayoutShape
 *
 * @author	George Warner Copyright (C) 2019
 */
///*public*/ class LayoutShapeTest {

    /*private*/ /*static*/ LayoutEditor* LayoutShapeTest::layoutEditor = nullptr;

    //@Test
    /*public*/ void LayoutShapeTest::testNew() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        Assert::assertNotNull("LayoutEditor exists", layoutEditor, __FILE__, __LINE__);
        Assert::assertNotNull("LayoutShape not null", ls, __FILE__, __LINE__);
        Assert::assertEquals("ls.getNumberPoints() equals 4", 4, ls->getNumberPoints(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LayoutShapeTest::testToString() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        Assert::assertNotNull("LayoutEditor exists", layoutEditor, __FILE__, __LINE__);
        Assert::assertNotNull("LayoutShape not null", ls, __FILE__, __LINE__);

        QString lsString = ls->toString();
        Assert::assertNotNull("lsString not null", lsString, __FILE__, __LINE__);
        Assert::assertEquals("LayoutShape Yard Fence", lsString, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LayoutShapeTest::testGetDisplayName() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        Assert::assertNotNull("LayoutEditor exists", layoutEditor, __FILE__, __LINE__);
        Assert::assertNotNull("LayoutShape not null", ls, __FILE__, __LINE__);

        Assert::assertEquals("Shape Yard Fence", ls->getDisplayName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LayoutShapeTest::testGetType() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        Assert::assertNotNull("LayoutEditor exists", layoutEditor, __FILE__, __LINE__);
        Assert::assertNotNull("LayoutShape not null", ls, __FILE__, __LINE__);
#if 0
        Assert::assertTrue("ls.getType() is eOpen", ls->getType() == LayoutShapeType::eOpen, __FILE__, __LINE__);
#endif
}
#if 0
    //@Test
    /*public*/ void LayoutShapeTest::testSetType() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        Assert::assertNotNull("LayoutEditor exists", layoutEditor, __FILE__, __LINE__);
        Assert::assertNotNull("LayoutShape not null", ls, __FILE__, __LINE__);

// compiler won't let us pass invalid type (yay!)
//        ls.setType(LayoutTurnout.NONE); // invalid type
//        jmri.util.JUnitAppender.assertErrorMessage("Invalid Shape Type 0");
        ls->setType(LayoutShapeType::eOpen);
        Assert::assertTrue("ls.getType() is eOpen", ls->getType() == LayoutShapeType::eOpen, __FILE__, __LINE__);

        ls->setType(LayoutShapeType::eClosed);
        Assert::assertTrue("ls.getType() is eClosed", ls->getType() == LayoutShapeType::eClosed, __FILE__, __LINE__);

        ls->setType(LayoutShapeType::eFilled);
        Assert::assertTrue("ls.getType() is eFilled", ls->getType() == LayoutShapeType::eFilled, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LayoutShapeTest::testGetBounds() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        Assert::assertNotNull("LayoutEditor exists", layoutEditor, __FILE__, __LINE__);
        Assert::assertNotNull("LayoutShape not null", ls, __FILE__, __LINE__);

        Assert::assertEquals("ls.getBounds() equals...",
                QRectF(50.0, 100.0, 50.0, 50.0),
                ls->getBounds(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LayoutShapeTest::testSetCoordsCenter() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless(), __FILE__, __LINE__);
        Assert::assertNotNull("LayoutEditor exists", layoutEditor, __FILE__, __LINE__);
        Assert::assertNotNull("LayoutShape not null", ls, __FILE__, __LINE__);
        Assert::assertEquals("ls.getNumberPoints() equals 4", 4, ls->getNumberPoints(), __FILE__, __LINE__);

        QPointF newCenterPoint = QPointF(75.0, 150.0);
        ls->setCoordsCenter(newCenterPoint);
        Assert::assertEquals("ls.getCoordsCenter equals...", newCenterPoint, ls->getCoordsCenter(), __FILE__, __LINE__);

        QList<LayoutShapePoint*> lspoints = ls->getPoints();

        Assert::assertEquals("ls.getPoint(0) equals...", QPointF(50.0, 125.0), lspoints.at(0)->getPoint(), __FILE__, __LINE__);
        Assert::assertEquals("ls.getPoint(1) equals...", QPointF(100.0, 125.0), lspoints.at(1)->getPoint(), __FILE__, __LINE__);
        Assert::assertEquals("ls.getPoint(2) equals...", QPointF(100.0, 175.0), lspoints.at(2)->getPoint(), __FILE__, __LINE__);
        Assert::assertEquals("ls.getPoint(3) equals...", QPointF(50.0, 175.0), lspoints.at(3)->getPoint(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LayoutShapeTest::testScaleCoords() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        Assert::assertNotNull("LayoutEditor exists", layoutEditor, __FILE__, __LINE__);
        Assert::assertNotNull("LayoutShape not null", ls, __FILE__, __LINE__);

        ls->scaleCoords(1.5F, 2.5F);
        Assert::assertEquals("ls.getCoordsCenter ",
                QPointF(112.5, 312.5), ls->getCoordsCenter(), __FILE__, __LINE__);

        QList<LayoutShapePoint*> lspoints = ls->getPoints();

        Assert::assertEquals("ls.getPoint(0) equals...", QPointF(75.0, 250.0), lspoints.at(0)->getPoint(), __FILE__, __LINE__);
        Assert::assertEquals("ls.getPoint(1) equals...", QPointF(150.0, 250.0), lspoints.at(1)->getPoint(), __FILE__, __LINE__);
        Assert::assertEquals("ls.getPoint(2) equals...", QPointF(150.0, 375.0), lspoints.at(2)->getPoint(), __FILE__, __LINE__);
        Assert::assertEquals("ls.getPoint(3) equals...", QPointF(75.0, 375.0), lspoints.at(3)->getPoint(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LayoutShapeTest::testTranslateCoords() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        Assert::assertNotNull("LayoutEditor exists", layoutEditor, __FILE__, __LINE__);
        Assert::assertNotNull("LayoutShape not null", ls, __FILE__, __LINE__);

        ls->translateCoords(15.5F, 25.5F);
        Assert::assertEquals("ls.getCoordsCenter ",
                QPointF(90.5, 150.5), ls->getCoordsCenter(), __FILE__, __LINE__);


        QList<LayoutShapePoint*> lspoints = ls->getPoints();

        Assert::assertEquals("ls.getPoint(0) equals...", QPointF(65.5, 125.5), lspoints.at(0)->getPoint(), __FILE__, __LINE__);
        Assert::assertEquals("ls.getPoint(1) equals...", QPointF(115.5, 125.5), lspoints.at(1)->getPoint(), __FILE__, __LINE__);
        Assert::assertEquals("ls.getPoint(2) equals...", QPointF(115.5, 175.5), lspoints.at(2)->getPoint(), __FILE__, __LINE__);
        Assert::assertEquals("ls.getPoint(3) equals...", QPointF(65.5, 175.5), lspoints.at(3)->getPoint(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LayoutShapeTest::testFindHitPointType() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        Assert::assertNotNull("LayoutEditor exists", layoutEditor, __FILE__, __LINE__);
        Assert::assertNotNull("LayoutShape not null", ls, __FILE__, __LINE__);

        // First: miss
        int hitType = ls->findHitPointType(MathUtil::zeroPoint2D, true);
        Assert::assertTrue("ls->findHitPointType equals NONE", hitType == LayoutTrack::NONE, __FILE__, __LINE__);

        // now try hit getCoordsLeft -> SHAPE_CENTER
        hitType = ls->findHitPointType(ls->getCoordsCenter(), true);
        Assert::assertEquals("ls->findHitPointType equals SHAPE_CENTER", LayoutTrack::SHAPE_CENTER, hitType, __FILE__, __LINE__);
        ///Assert::assertTrue("ls->findHitPointType equals SHAPE_CENTER", hitType == LayoutTrack.SHAPE_CENTER);


        QList<LayoutShapePoint*> lspoints = ls->getPoints();

        hitType = ls->findHitPointType(lspoints.at(0)->getPoint(), true);
        Assert::assertEquals("ls->findHitPointType(point[0]) equals SHAPE_POINT_OFFSET_MIN", LayoutTrack::SHAPE_POINT_OFFSET_MIN, hitType, __FILE__, __LINE__);

        hitType = ls->findHitPointType(lspoints.at(1)->getPoint(), true);
        Assert::assertEquals("ls->findHitPointType(point[1]) equals SHAPE_POINT_OFFSET_MIN + 1", LayoutTrack::SHAPE_POINT_OFFSET_MIN + 1, hitType, __FILE__, __LINE__);

        hitType = ls->findHitPointType(lspoints.at(2)->getPoint(), true);
        Assert::assertEquals("ls->findHitPointType(point[2]) equals SHAPE_POINT_OFFSET_MIN + 2", LayoutTrack::SHAPE_POINT_OFFSET_MIN + 2, hitType, __FILE__, __LINE__);

        hitType = ls->findHitPointType(lspoints.at(3)->getPoint(), true);
        Assert::assertEquals("ls->findHitPointType(point[3]) equals SHAPE_POINT_OFFSET_MIN + 3", LayoutTrack::SHAPE_POINT_OFFSET_MIN + 3, hitType, __FILE__, __LINE__);
    }
#endif
    // from here down is testing infrastructure
    //@BeforeClass
    /*public*/ /*static*/ void LayoutShapeTest::beforeClass() {
        JUnitUtil::setUp();
//        if (!GraphicsEnvironment.isHeadless()) {
            JUnitUtil::resetProfileManager();
            layoutEditor = new LayoutEditor();
//        }
    }

    //@AfterClass
    /*public*/ /*static*/ void LayoutShapeTest::afterClass() {
        if (layoutEditor != nullptr) {
            JUnitUtil::dispose(layoutEditor);
            layoutEditor = nullptr;
        }
        JUnitUtil::tearDown();
    }

    //@Before
    /*public*/ void LayoutShapeTest::setUp() {
        JUnitUtil::resetProfileManager();
//        if (!GraphicsEnvironment.isHeadless()) {
            ls = new LayoutShape("Yard Fence", QPointF(50.0, 100.0), layoutEditor);
            ls->addPoint(QPointF(100.0, 100.0));
            ls->addPoint(QPointF(100.0, 150.0));
            ls->addPoint(QPointF(50.0, 150.0));
//        }
    }

    //@After
    /*public*/ void LayoutShapeTest::tearDown() {
        if (ls != nullptr) {
            ls->remove();
            ls->dispose();
            ls = nullptr;
        }
    }
    ///*private*/ final static Logger log = LoggerFactory.getLogger(LayoutShapeTest.class);

