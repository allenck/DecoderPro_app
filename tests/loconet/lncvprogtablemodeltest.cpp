#include "lncvprogtablemodeltest.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "assert1.h"
#include "jtable.h"
#include "tablecolumn.h"
#include "loconetsystemconnectionmemo.h"
#include "rosterconfigmanager.h"
#include "lncvprogpane.h"
#include "loconet/loconetinterfacescaffold.h"

LncvProgTableModelTest::LncvProgTableModelTest(QObject *parent) : QObject(parent)
{

}
//class LncvProgTableModelTest {


    //@Test
    /*public*/ void LncvProgTableModelTest::testCTor() {
        Assert::assertNotNull("LncvProg model exists", lptm, __FILE__, __LINE__);
    }

    //@Test
    void LncvProgTableModelTest::testInitTable() {
        JTable* table = new JTable(lptm);
        lptm->initTable(table); // one would expect 8 but is 15
        Assert::assertEquals("IDColumn width", 15, table->getColumn("#")->getMaxWidth(), __FILE__, __LINE__);
    }

    //@Test
    void LncvProgTableModelTest::testGetColumnName() {
        lptm->initTable(new JTable(lptm));
        Assert::assertEquals("IDColumn name", "#", lptm->getColumnName(0), __FILE__, __LINE__);
    }

    //@Test
    void LncvProgTableModelTest::testGetColumnClass() {
        Assert::assertEquals("VALUE_COLUMN class", "Integer", lptm->getColumnClass(LncvProgTableModel::VALUE_COLUMN), __FILE__, __LINE__);
        Assert::assertEquals("OPENPRGMRBUTTONCOLUMN class", "JButton", lptm->getColumnClass(LncvProgTableModel::OPENPRGMRBUTTONCOLUMN), __FILE__, __LINE__);
    }

    //@Test
    void LncvProgTableModelTest::tastIsCellEditable() {
        Assert::assertEquals("OPENPRGMRBUTTONCOLUMN is editable", true, lptm->isCellEditable(0, LncvProgTableModel::OPENPRGMRBUTTONCOLUMN), __FILE__, __LINE__);
        Assert::assertEquals("VALUE_COLUMN is not editable", false, lptm->isCellEditable(0, LncvProgTableModel::VALUE_COLUMN), __FILE__, __LINE__);
    }

    //@Test
    void LncvProgTableModelTest::testGetColumnCount() {
        Assert::assertEquals("ProgTable column count", 8, lptm->getColumnCount(), __FILE__, __LINE__);
    }

    //@Test
    void LncvProgTableModelTest::testGetSetValueAt() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        LncvDevicesManager* lcdm = new LncvDevicesManager(memo);
        memo->setLncvDevicesManager(lcdm);
        InstanceManager::setDefault("RosterConfigManager", new RosterConfigManager());
        Assert::assertEquals("LncvDeviceManager List empty", 0, lcdm->getDeviceCount(), __FILE__, __LINE__);
        lcdm->message(new LocoNetMessage(QVector<int>{0xE5, 0x0F, 0x05, 0x49, 0x4B, 0x1F, 0x11, 0x29, 0x13, 0x00, 0x00, 0x08, 0x00, 0x00, 0x4D}));
        // should add 1 row to table
        Assert::assertEquals("getValue in cell 0,COUNT_COLUMN", 1, lptm->getValueAt(0, LncvProgTableModel::COUNT_COLUMN), __FILE__, __LINE__);
        Assert::assertEquals("getValue in cell 0,VALUE_COLUMN", 136, lptm->getValueAt(0, LncvProgTableModel::VALUE_COLUMN), __FILE__, __LINE__);
        Assert::assertEquals("getValue in cell 0,ARTICLE_COLUMN", 5033, lptm->getValueAt(0, LncvProgTableModel::ARTICLE_COLUMN), __FILE__, __LINE__);
        Assert::assertEquals("getValue in cell 0,DEVICENAMECOLUMN", "", lptm->getValueAt(0, LncvProgTableModel::DEVICENAMECOLUMN), __FILE__, __LINE__);
        Assert::assertEquals("getValue in cell 0,OPENPRGMRBUTTONCOLUMN", tr("No Match in Roster"), lptm->getValueAt(0, LncvProgTableModel::OPENPRGMRBUTTONCOLUMN).toString(), __FILE__, __LINE__);
        lptm->setValueAt(5,0, LncvProgTableModel::OPENPRGMRBUTTONCOLUMN); // click should see na action
    }

//    //@Test
//    void openPaneOpsProgFrame() {
//    }

    //@BeforeEach
    /*public*/ void LncvProgTableModelTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::initRosterConfigManager();
        memo = new LocoNetSystemConnectionMemo();
        InstanceManager::setDefault("LocoNetSystemConnectionMemo", memo);
        memo->setLnTrafficController(new LocoNetInterfaceScaffold(memo));
        lptm = new LncvProgTableModel(new LncvProgPane(), memo);
    }

    //@AfterEach
    /*public*/ void LncvProgTableModelTest::tearDown() {
        memo = nullptr;
        JUnitUtil::tearDown();
    }
