#include "cabsignaltablemodeltest.h"
#include "assert1.h"
#include "junitutil.h"
#include "cabsignaltablemodel.h"
#include "junitappender.h"

CabSignalTableModelTest::CabSignalTableModelTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test simple functioning of CabSignalTableModel
 *
 * @author Paul Bender Copyright (C) 2019
 * @author Steve Young Copyright (c) 2019
 */
///*public*/ class CabSignalTableModelTest {


    //@Test
    /*public*/ void CabSignalTableModelTest::testCtor() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        CabSignalTableModel* model = new CabSignalTableModel(5,CabSignalTableModel::MAX_COLUMN);
        Assert::assertNotNull("exists", model, __FILE__, __LINE__);
    }

    /*public*/ void CabSignalTableModelTest::testColumns() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        CabSignalTableModel* t = new CabSignalTableModel(5,CabSignalTableModel::MAX_COLUMN);

        Assert::assertEquals("column count",CabSignalTableModel::MAX_COLUMN,t->getColumnCount(), __FILE__, __LINE__);
        Assert::assertEquals("default row count",0,t->getRowCount(), __FILE__, __LINE__);

        Assert::assertTrue(t->getColumnName(CabSignalTableModel::LOCO_ID_COLUMN).contains("loco"), __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnName(CabSignalTableModel::CURRENT_BLOCK).contains("loco"), __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnName(CabSignalTableModel::BLOCK_DIR).contains("block"), __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnName(CabSignalTableModel::REVERSE_BLOCK_DIR_BUTTON_COLUMN).contains("block"), __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnName(CabSignalTableModel::NEXT_BLOCK).contains("next bl"), __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnName(CabSignalTableModel::NEXT_SIGNAL).contains("next sig"), __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnName(CabSignalTableModel::NEXT_ASPECT).contains("next as"), __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnName(CabSignalTableModel::SEND_CABSIG_COLUMN).contains("signal data"), __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnName(999).contains("unknown"), __FILE__, __LINE__);

        Assert::assertTrue(CabSignalTableModel::getPreferredWidth( CabSignalTableModel::LOCO_ID_COLUMN)> 0, __FILE__, __LINE__);
        Assert::assertTrue(CabSignalTableModel::getPreferredWidth( CabSignalTableModel::CURRENT_BLOCK)> 0, __FILE__, __LINE__);
        Assert::assertTrue(CabSignalTableModel::getPreferredWidth( CabSignalTableModel::BLOCK_DIR)> 0, __FILE__, __LINE__);
        Assert::assertTrue(CabSignalTableModel::getPreferredWidth( CabSignalTableModel::REVERSE_BLOCK_DIR_BUTTON_COLUMN)> 0, __FILE__, __LINE__);
        Assert::assertTrue(CabSignalTableModel::getPreferredWidth( CabSignalTableModel::NEXT_BLOCK)> 0, __FILE__, __LINE__);
        Assert::assertTrue(CabSignalTableModel::getPreferredWidth( CabSignalTableModel::NEXT_SIGNAL)> 0, __FILE__, __LINE__);
        Assert::assertTrue(CabSignalTableModel::getPreferredWidth( CabSignalTableModel::NEXT_ASPECT)> 0, __FILE__, __LINE__);
        Assert::assertTrue(CabSignalTableModel::getPreferredWidth( CabSignalTableModel::SEND_CABSIG_COLUMN)> 0, __FILE__, __LINE__);
        Assert::assertTrue(CabSignalTableModel::getPreferredWidth(999)> 0, __FILE__, __LINE__);
        JUnitAppender::assertErrorMessageStartsWith("no width found col 999", __FILE__, __LINE__);

        Assert::assertTrue(t->getColumnClass(CabSignalTableModel::LOCO_ID_COLUMN) == "LocoAddress" , __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnClass(CabSignalTableModel::CURRENT_BLOCK) == "String" , __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnClass(CabSignalTableModel::BLOCK_DIR) == "String" , __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnClass(CabSignalTableModel::REVERSE_BLOCK_DIR_BUTTON_COLUMN) == "JButton" , __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnClass(CabSignalTableModel::NEXT_BLOCK) == "String" , __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnClass(CabSignalTableModel::NEXT_SIGNAL) == "String" , __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnClass(CabSignalTableModel::NEXT_ASPECT) == "String" , __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnClass(CabSignalTableModel::SEND_CABSIG_COLUMN) == "Boolean" , __FILE__, __LINE__);
        Assert::assertTrue(t->getColumnClass(999) == nullptr , __FILE__, __LINE__);
        JUnitAppender::assertErrorMessageStartsWith("no column class", __FILE__, __LINE__);

        t->dispose();
        t = nullptr;
    }

    //@Before
    /*public*/ void CabSignalTableModelTest::setUp() {
        JUnitUtil::setUp();

    }

    //@After
    /*public*/ void CabSignalTableModelTest::tearDown() {
        JUnitUtil::tearDown();
    }
