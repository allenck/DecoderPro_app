#include "oblocktablepanel.h"
#include "loggerfactory.h"
#include "portaltablemodel.h"
#include "signaltablemodel.h"
#include "blockportaltablemodel.h"
#include "tableframes.h"
#include "oblocktablemodel.h"
#include "tablerowsorter.h"
#include "rowsorterutil.h"
#include "jtable.h"
#include "tablecolumnmodel.h"
#include "xtablecolumnmodel.h"
#include "jtogglebutton.h"
#include "jtabbedpane.h"
#include "borderlayout.h"
#include "QScrollArea"
#include "jbutton.h"
#include "tablecolumn.h"
/**
 * GUI for tabbed OBlock editing since 2020. Based on AudioTablePanel.
 * OBlock parts adapted from {@link jmri.jmrit.beantable.oblock.TableFrames}
 * Which interface will be presented is user settable in Display prefs.
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Matthew Harris copyright (c) 2009
 * @author Egbert Broerse copyright (c) 2020
 */
///*public*/ class OBlockTablePanel extends JPanel {


/*private*/ /*static*/ /*final*/ int OBlockTablePanel::bottomStrutWidth = 20;

//@SuppressWarnings("OverridableMethodCallInConstructor")
/*public*/ OBlockTablePanel::OBlockTablePanel(OBlockTableModel* oblocks,
                        PortalTableModel* portals,
                        SignalTableModel* _signals,
                        BlockPortalTableModel* blockportals,
                        TableFrames* tf,
                        QString helpTarget,
                        QWidget *parent) : JPanel(parent){

    //super(); // required? nothing set
    setMinimumSize(600, 400);

    _tf = tf;

    log->debug("Building tables");

    // OBlock Table
    oblockDataModel = oblocks;
    TableRowSorter/*<OBlockTableModel>*/* sorter = new TableRowSorter(oblockDataModel);
    // use NamedBean's built-in Comparator interface for sorting the system name column
    RowSorterUtil::setSortOrder(sorter, OBlockTableModel::SYSNAMECOL, SortOrder::ASCENDING);
    oblockTable = makeJTable("OBlockTableAction", oblockDataModel, sorter); // use our own
    // style table, check overlap with configureWarrantTable done next
    oblockTable->setDefaultEditor("JButton", new ButtonEditor());
    oblockTable->setDefaultRenderer("JButton", new ButtonRenderer());
    oblockTable->getColumnModel()->getColumn(OBlockTableModel::UNITSCOL)->setCellRenderer(
            new ToggleButtonRenderer(tr("cm"), tr("in")));
    oblockTable->getColumnModel()->getColumn(OBlockTableModel::UNITSCOL)->setCellEditor(
            new ToggleButtonEditor(tr("cm"), tr("in")));
    oblocks->configCurveColumn(oblockTable); // use real combo
    oblockTable->getColumnModel()->getColumn(OBlockTableModel::REPORT_CURRENTCOL)->setCellRenderer(
            new ToggleButtonRenderer(tr("Current"), tr("Last")));
    oblockTable->getColumnModel()->getColumn(OBlockTableModel::REPORT_CURRENTCOL)->setCellEditor(
            new ToggleButtonEditor(tr("Current"), tr("Last")));
    oblocks->configSpeedColumn(oblockTable); // use real combo
    oblockTable->getColumnModel()->getColumn(OBlockTableModel::PERMISSIONCOL)->setCellRenderer(
            new ToggleButtonRenderer(tr("Permissive"), tr("Absolute")));
    oblockTable->getColumnModel()->getColumn(OBlockTableModel::PERMISSIONCOL)->setCellEditor(
            new ToggleButtonEditor(tr("Permissive"), tr("Absolute")));
    // Use XTableColumnModel so we can control which columns are visible
    XTableColumnModel* tcm = new XTableColumnModel(oblockTable);
    oblockTable->setColumnModel(tcm);
//        oblockTable->getTableHeader()->setReorderingAllowed(true); // makeJTable not used for oblockTable
    oblockTable->createDefaultColumnsFromModel();
    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::REPORTERCOL), false); // doesn't hide them?
    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::REPORT_CURRENTCOL), false);
    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::PERMISSIONCOL), false);
    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::WARRANTCOL), false);
    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::ERR_SENSORCOL), false);
    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::CURVECOL), false);
//    oblockTable->setColumnHidden(OBlockTableModel::REPORTERCOL, true);
//    oblockTable->setColumnHidden(OBlockTableModel::REPORT_CURRENTCOL, true);
//    oblockTable->setColumnHidden(OBlockTableModel::PERMISSIONCOL, true);
//    oblockTable->setColumnHidden(OBlockTableModel::WARRANTCOL, true);
//    oblockTable->setColumnHidden(OBlockTableModel::ERR_SENSORCOL, true);
//    oblockTable->setColumnHidden(OBlockTableModel::CURVECOL, true);
    for (int i = 0; i < ((DefaultTableColumnModel*)tcm)->getColumnCount(); i++) {
        int width = oblockDataModel->getPreferredWidth(i);
        tcm->getColumn(i)->setPreferredWidth(width);
    }
    //oblockTable->doLayout();
    oblockDataModel->addHeaderListener(oblockTable); // HeaderListeners not set up for the other 3 small tables
//        oblockTable->setPreferredScrollableViewportSize(QSize(550, 300)); // a wide table
    //oblockDataScroll = new JScrollPane(oblockTable);

    // Portal Table
    portalDataModel = portals;
    TableRowSorter/*<PortalTableModel>*/* portalsorter = new TableRowSorter(portalDataModel);
    RowSorterUtil::setSortOrder(portalsorter, PortalTableModel::NAME_COLUMN, SortOrder::ASCENDING);
    portalTable = makeJTable("Portal", portalDataModel, portalsorter);
    // style table
    portalTable->setDefaultEditor("JButton", new ButtonEditor());
    portalTable->setDefaultRenderer("JButton", new ButtonRenderer());
    portalTable->doLayout();
    //portalTable->setColumnModel(new XTableColumnModel());
    portalTable->createDefaultColumnsFromModel();
    for (int i = 0; i < portalDataModel->getColumnCount(); i++) {
        int width = portalDataModel->getPreferredWidth(i);
        portalTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
//        portalDataScroll = new JScrollPane(portalTable);

    // Signal Table
    signalDataModel = _signals;
    TableRowSorter/*<SignalTableModel>*/* sigsorter = new TableRowSorter(signalDataModel);
    RowSorterUtil::setSortOrder(sigsorter, SignalTableModel::NAME_COLUMN, SortOrder::ASCENDING);
    signalTable = makeJTable("Signals", signalDataModel, sigsorter);
    // style table
    signalTable->setDefaultEditor("JButton", new ButtonEditor());
    signalTable->setDefaultRenderer("JButton", new ButtonRenderer());
    signalTable->getColumnModel()->getColumn(SignalTableModel::UNITSCOL)->setCellRenderer(
            new ToggleButtonRenderer(tr("cm"), tr("in")));
    signalTable->getColumnModel()->getColumn(SignalTableModel::UNITSCOL)->setCellEditor(
            new ToggleButtonEditor(tr("cm"), tr("in")));
    signalTable->doLayout();
    //signalTable->setColumnModel(new XTableColumnModel());
    signalTable->createDefaultColumnsFromModel();
    for (int i = 0; i < signalDataModel->getColumnCount(); i++) {
        int width = SignalTableModel::getPreferredWidth(i);
        signalTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
//        signalDataScroll = new JScrollPane(signalTable);

    // Block-Portal Xreference table
    blockportalDataModel = blockportals; // cross-reference (not editable)
    //sorter = new TableRowSorter<>(blockportalDataModel);
    RowSorterUtil::setSortOrder(sorter, BlockPortalTableModel::BLOCK_NAME_COLUMN, SortOrder::ASCENDING);
    blockportalTable = makeJTable("Block-Portal X-ref", blockportalDataModel, sorter); // cannot directly access
    // style table
    blockportalTable->setDefaultRenderer("String", new ValueRenderer());
    blockportalTable->doLayout();
    //blockportalTable->setColumnModel(new XTableColumnModel());
    blockportalTable->createDefaultColumnsFromModel();
    for (int i = 0; i < blockportalDataModel->getColumnCount(); i++) {
        int width = blockportalDataModel->getPreferredWidth(i);
        blockportalTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
//        blockportalDataScroll = new JScrollPane(blockportalTable);

    // configure items for GUI
    configureWarrantTable(oblockTable); // only class to extend BeanTableDataModel
    //oblockDataModel.configEditColumn(oblockTable);
    for (int i = 0; i < oblockTable->getColumnCount(); i++) {
        // copied from TableFrames#makeOBlockTable() l729 as it needs table so can't copy to oblockDataModel
        int width = oblockDataModel->getPreferredWidth(i);
        oblockTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
    oblockDataModel->persistTable(oblockTable); // only oblockDataModel contains this method

    configureWarrantTable(signalTable);
    // pathDataModel.configEditColumn(pathTable);
    //oblockDataModel.persistTable(signalTable);

    configureWarrantTable(portalTable);
    // portalDataModel.configEditColumn(portalTable);
    //oblockDataModel.persistTable(portalTable);

    configureWarrantTable(blockportalTable);
    // portalDataModel.configEditColumn(blockportalTable);
    //oblockDataModel.persistTable(blockportalTable);

    // add more changeListeners for table (example load, created) to update tables?

    // general GUI config
    //resize(600, 400);
    QHBoxLayout* thisLayout;
    this->setLayout(thisLayout = new QHBoxLayout());

    // install the four items in GUI as tabs
    oblockTabs = new JTabbedPane(this);
    oblockTabs->setMinimumSize(600,400);
    oblockTabs->setMinimumWidth(1000);

//    QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    sizePolicy.setHorizontalStretch(1);
//    sizePolicy.setVerticalStretch(1);
//    sizePolicy.setHeightForWidth(oblockTabs->sizePolicy().hasHeightForWidth());
//    oblockTabs->setSizePolicy(sizePolicy);
    oblockTabs->addTab(tr("OBlocks"), /*oblockDataScroll*/oblockTable);
    oblockTabs->addTab(tr("Portals"), /*portalDataScroll*/portalTable);
    oblockTabs->addTab(tr("Signals"), /*signalDataScroll*/signalTable);
    oblockTabs->addTab(tr("Block-Portal Cross Reference"), /*blockportalDataScroll*/blockportalTable);
    // turnouts not on a tab: via Edit button in Path Edit pane (or a Tables submenu)

    thisLayout-> addWidget(oblockTabs, 1);//BorderLayout::Center);
    log->debug("tabs complete");

    bottomBox = Box::createHorizontalBox();
    bottomBox->layout()-> addWidget(Box::createHorizontalGlue()); // stays at end of box
    bottomBoxIndex = 0;

    thisLayout-> addWidget(bottomBox, 0, Qt::AlignBottom);// BorderLayout::South);

    // add extras, if desired by subclass
    extras();

    log->debug("bottomBox complete");
    // set preferred scrolling options
    /*oblockDataScroll*/blockportalTable->setHorizontalScrollBarPolicy(/*JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS*/Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    /*portalDataScroll*/portalTable->setHorizontalScrollBarPolicy(/*JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS*/Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    /*signalDataScroll*/signalTable->setHorizontalScrollBarPolicy(/*JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS*/Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    /*blockportalDataScroll*/blockportalTable->setVerticalScrollBarPolicy(/*JScrollPane.VERTICAL_SCROLLBAR_ALWAYS*/Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    adjustSize();
}

/**
 * Hook to allow sub-types to install more items in GUI
 */
void OBlockTablePanel::extras() {
}

/*protected*/ QWidget* OBlockTablePanel::getBottomBox() {
    return bottomBox;
}

/*public*/ QMenu* OBlockTablePanel::getPrintItem() { // copied from AudioTablePanel
    log->debug("OBLOCK TABBED getPrintItem() called");
    return _tf->getPrintMenuItems(oblockTable, portalTable, signalTable, blockportalTable);
}

/*public*/ QMenu* OBlockTablePanel::getOptionMenu() {
    log->debug("OBLOCK TABBED getOptionMenu() called");
    return _tf->getOptionMenu();
}

/*public*/ QMenu* OBlockTablePanel::getTablesMenu() {
    log->debug("OBLOCK TABBED getTablesMenu() called");
    return _tf->getTablesMenu();
}

/**
 * Add a component to the bottom box. Takes care of organising glue, struts
 * etc
 *
 * @param comp {@link Component} to add
 */
/*protected*/ void OBlockTablePanel::addToBottomBox(QWidget* comp) {
    bottomBox->layout()->addWidget(Box::createHorizontalStrut(bottomStrutWidth)/*, bottomBoxIndex*/);
    ++bottomBoxIndex;
    bottomBox->layout()->addWidget(comp/*, bottomBoxIndex*/);
    ++bottomBoxIndex;
}

/*public*/ void OBlockTablePanel::dispose() {
    if (oblockDataModel != nullptr) {
        oblockDataModel->stopPersistingTable(oblockTable);
        oblockDataModel->dispose();
    }
    oblockDataModel = nullptr;
    oblockTable = nullptr;
//        oblockDataScroll = nullptr;

    //if (portalDataModel != null) {
        // portalDataModel.stopPersistingTable(portalTable);
        // portalDataModel.dispose();
    //}
    portalDataModel = nullptr;
    portalTable = nullptr;
//        portalDataScroll = null;

    //if (signalDataModel != null) {
        // signalDataModel.stopPersistingTable(signalTable);
        // signalDataModel.dispose();
    //}
    signalDataModel = nullptr;
    signalTable = nullptr;
//        signalDataScroll = null;

    //if (blockportalDataModel != null) {
        // blockportalDataModel.stopPersistingTable(blockportalTable);
        // blockportalDataModel.dispose();
    //}
    blockportalDataModel = nullptr;
    blockportalTable = nullptr;
//        blockportalDataScroll = nullptr;
}

/**
 * Create and configure a new table using the given model and row sorter.
 *
 * @param name   the name of the table
 * @param model  the data model for the table
 * @param sorter the row sorter for the table; if null, the table will not
 *               be sortable
 * @return the table
 * @throws NullPointerException if name or model is null
 */
/*public*/ JTable* OBlockTablePanel::makeJTable(/*@Nonnull*/ QString name, /*@Nonnull*/ TableModel* model, /*@CheckForNull*/ RowSorter/*<? extends TableModel>*/* sorter) {
//        Objects.requireNonNull(name, "the table name must be nonnull " + name);
//        Objects.requireNonNull(model, "the table model must be nonnull " + name);
    JTable* table = this->configureJTable(name, new JTable(model), sorter);
    table->setMinimumSize(500, 300);
    //model.addHeaderListener(table);
    return table;
}
#if 1
/**
 * Configure a new table using the given model and row sorter.
 *
 * @param table  the table to configure
 * @param name   the table name
 * @param sorter the row sorter for the table; if null, the table will not
 *               be sortable
 * @return the table
 * @throws NullPointerException if table or the table name is null
 */
/*protected*/ JTable* OBlockTablePanel::configureJTable(/*@Nonnull*/ QString name, /*@Nonnull*/ JTable* table, /*@CheckForNull*/ RowSorter/*<? extends TableModel>*/* sorter) {
//        Objects.requireNonNull(table, "the table must be nonnull");
//        Objects.requireNonNull(name, "the table name must be nonnull");
    table->setRowSorter(sorter);
    table->setName(name);
    //table.getTableHeader()->setReorderingAllowed(true); // already assigned per table above
    //table->setColumnModel(new XTableColumnModel());
    //table.createDefaultColumnsFromModel();
    return table;
}

/**
 * Configure a table to have our standard rows and columns.
 * This also persists the table user interface state.
 * Adapted from {@link BeanTableDataModel} for tables 1-4, EBR 2020
 *
 * @param table {@link JTable} to configure
 */
/*public*/ void OBlockTablePanel::configureWarrantTable(JTable* table) {
    // ignore Property columns
    table->setDefaultRenderer("JButton", new ButtonRenderer());
    table->setDefaultEditor("JButton", new ButtonEditor());
    table->setDefaultRenderer("JToggleButton", new ToggleButtonRenderer(tr("cm"), tr("in"))); // overrides
    table->setDefaultEditor("JToggleButton", new ToggleButtonEditor(tr("cm"), tr("in")));
    table->setDefaultRenderer("JRadioButton", new ToggleButtonRenderer(tr("Current"), tr("Last"))); // overrides
    table->setDefaultEditor("JRadioButton", new ToggleButtonEditor(tr("Current"), tr("Last")));
    table->setDefaultRenderer("JCheckBox", new ToggleButtonRenderer(tr("Permissive"), tr("Absolute")));
    table->setDefaultEditor("JCheckBox", new ToggleButtonEditor(tr("Permissive"), tr("Absolute")));
#if 0
    table->setDefaultEditor("OBlockTableModel::SpeedComboBoxPanel", new OBlockTableModel::SpeedComboBoxPanel());
    table->setDefaultRenderer("OBlockTableModel::SpeedComboBoxPanel", new OBlockTableModel::SpeedComboBoxPanel());
    table->setDefaultEditor("OBlockTableModel::CurveComboBoxPanel", new OBlockTableModel::CurveComboBoxPanel());
    table->setDefaultRenderer("OBlockTableModel::CurveComboBoxPanel", new OBlockTableModel::CurveComboBoxPanel());
#endif
    // allow reordering of the columns
    //table.getTableHeader()->setReorderingAllowed(true);
    // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
    table->setAutoResizeMode(JTable::AUTO_RESIZE_OFF);
    table->setRowHeight(TableFrames::ROW_HEIGHT);
    // resize columns per table
//        table.doLayout();
    // resize columns as requested (for OBlocks tabbed: throws java.lang.IllegalArgumentException: "Identifier not found")
//        for (int i = 0; i < table->getColumnCount(); i++) {
//            int width = table->getColumn(i).getPreferredWidth();
//            table->getColumnModel()->getColumn(i)->setPreferredWidth(width);
//        }
}
#endif
/*private*/ /*static*/ /*final*/ Logger* OBlockTablePanel::log = LoggerFactory::getLogger("OBlockTablePanel");
