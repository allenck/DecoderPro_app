#include "warranttableframe.h"
#include "nxframe.h"
#include <QComboBox>
#include "warranttablemodel.h"
#include "QSortFilterProxyModel"
#include "xtablecolumnmodel.h"
#include "jtable.h"
#include "tablecolumn.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include "jtextfield.h"
#include "flowlayout.h"
#include <QMenu>
#include <QMenuBar>
#include "abstractaction.h"
#include "savemenu.h"
#include "warranttableaction.h"
#include "jdialog.h"
#include "warrant.h"
#include "blockorder.h"
#include <QMessageBox>
#include "pushbuttondelegate.h"
#include <QSignalMapper>
#include "loggerfactory.h"
#include "opath.h"
#include "oblock.h"
#include "blockorder.h"

//WarrantTableFrame::WarrantTableFrame(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
/**
 * The WarrantTableFrame lists the existing Warrants and has controls to set their routes,
 * train IDs launch them and control their running (halt, resume, abort. etc.
 *
 *  The WarrantTableFrame also can initiate NX (eNtry/eXit) warrants
 * <P>
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author  Pete Cressman  Copyright (C) 2009, 2010
 */

///*public*/ class WarrantTableFrame extends jmri.util.JmriJFrame implements MouseListener
//{
///*private*/ static final long serialVersionUID = 8994208663637783635L;
/*static final*/ QString WarrantTableFrame::halt = tr("Halt");
/*static final*/ QString WarrantTableFrame::resume = tr("Resume");
/*static final*/ QString WarrantTableFrame::abort = tr("Abort");
/*static final*/ QString WarrantTableFrame::retry = tr("Retry");
/*static final*/ QStringList WarrantTableFrame::controls = QStringList() << WarrantTableFrame::halt << WarrantTableFrame::resume << WarrantTableFrame::retry << WarrantTableFrame::abort;

/*public*/ /*static*/ int WarrantTableFrame::_maxHistorySize = 30;
/*private*/ /*static*/ WarrantTableFrame* WarrantTableFrame::_instance = NULL;


/**
 * Get the default instance of a Warrant table window.
 *
 * @return the default instance; creating it if necessary
 */
/*public*/ /*static*/ WarrantTableFrame* WarrantTableFrame::getDefault() {
    WarrantTableFrame* instance = (WarrantTableFrame*)InstanceManager::getOptionalDefault("WarrantTableFrame");
    if(instance == nullptr)
    {
        WarrantTableFrame* newInstance = (WarrantTableFrame*)InstanceManager::setDefault("WarrantTableFrame", new WarrantTableFrame());
        try {
            newInstance->initComponents();
        } catch (Exception ex) {
            log->error("Unable to initilize Warrant Table Frame", ex);
        }
        return newInstance;
    }//);
    instance->setVisible(true);
    return instance;
}

/*protected*/ WarrantTableModel* WarrantTableFrame::getModel() {
    return _model;
}

/*private*/ WarrantTableFrame::WarrantTableFrame(QWidget *parent) :
  JmriJFrame(false,true, parent)
{
 //super(false, true);
 log = new Logger("WarrantTableFrame");
 _startWarrant = new JTextField(30);
 _endWarrant = new JTextField(30);
 _status = new JTextField(90);
 _statusHistory = QStringList();

 setTitle(tr("WarrantTable"));
 _model = new WarrantTableModel(this);
 _model->init();
 //Casts at getTableCellEditorComponent() now fails with 3.0 ??
 JTable* table = new JTable(_model);
 table->setObjectName("WarrantTable");
 //ComboBoxCellEditor comboEd;
 //try {   // following might fail due to a missing method on Mac Classic
     //TableSorter sorter = new jmri.util.com.sun.TableSorter(_model);
  QSortFilterProxyModel* sorter = new QSortFilterProxyModel;
  sorter->setSourceModel(_model);
//  table = jmri.util.JTableUtil.sortableDataModel(sorter);
//  sorter.setTableHeader(table.getTableHeader());
//  comboEd = new ComboBoxCellEditor(new QComboBox*(), sorter);
//  // set model last so later casts will work
//  ((jmri.util.com.sun.TableSorter)table.getModel()).setTableModel(_model);
// } catch (Throwable e) { // NoSuchMethodError, NoClassDefFoundError and others on early JVMs
//  log.error("WarrantTable: Unexpected error: "+e);
//  table = new JTable(_model);
//  comboEd = new ComboBoxCellEditor(new QComboBox*());
// }
 // Use XTableColumnModel so we can control which columns are visible
 XTableColumnModel* tcm = new XTableColumnModel(table);
 table->setColumnModel(tcm);
// table->getTableHeader().setReorderingAllowed(true);
 table->createDefaultColumnsFromModel();
 _model->addHeaderListener(table);
 //_model->configureTable(table);
 _model->_table = table;
 //_model->updateNameList();
// table.setDefaultRenderer(Boolean.class, new ButtonRenderer());
// table.setDefaultRenderer(JComboBox.class, new jmri.jmrit.symbolicprog.ValueRenderer());
// table.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
// JComboBox <String> box = new QComboBox*(controls);
// box.setFont(new Font(NULL, Font.PLAIN, 12));
// table.getColumnModel().getColumn(WarrantTableModel.CONTROL_COLUMN).setCellEditor(new DefaultCellEditor(box));
 _model->setColumnToHoldDelegate(table, WarrantTableModel::CONTROL_COLUMN, new ControlBoxCellEditor(controls, this));
// table.getColumnModel().getColumn(WarrantTableModel::WarrantTableModel.ROUTE_COLUMN).setCellEditor(comboEd);
 _model->setColumnToHoldDelegate(table, WarrantTableModel::ROUTE_COLUMN, new RouteBoxCellEditor(this));
// table.getColumnModel().getColumn(WarrantTableModel.ALLOCATE_COLUMN).setCellEditor(new ButtonEditor(new QPushButton()));
// table.getColumnModel().getColumn(WarrantTableModel.ALLOCATE_COLUMN).setCellRenderer(new ButtonRenderer());
 _model->setColumnToHoldButton(table, WarrantTableModel::ALLOCATE_COLUMN);
// table.getColumnModel().getColumn(WarrantTableModel.DEALLOC_COLUMN).setCellEditor(new ButtonEditor(new QPushButton()));
// table.getColumnModel().getColumn(WarrantTableModel.DEALLOC_COLUMN).setCellRenderer(new ButtonRenderer());
 _model->setColumnToHoldButton(table, WarrantTableModel::DEALLOC_COLUMN);
// table.getColumnModel().getColumn(WarrantTableModel.SET_COLUMN).setCellEditor(new ButtonEditor(new QPushButton()));
// table.getColumnModel().getColumn(WarrantTableModel.SET_COLUMN).setCellRenderer(new ButtonRenderer());
 _model->setColumnToHoldButton(table, WarrantTableModel::SET_COLUMN);
 // table.getColumnModel().getColumn(WarrantTableModel.AUTO_RUN_COLUMN).setCellEditor(new ButtonEditor(new QPushButton()));
// table.getColumnModel().getColumn(WarrantTableModel.AUTO_RUN_COLUMN).setCellRenderer(new ButtonRenderer());
 _model->setColumnToHoldButton(table, WarrantTableModel::AUTO_RUN_COLUMN);
// table.getColumnModel().getColumn(WarrantTableModel.MANUAL_RUN_COLUMN).setCellEditor(new ButtonEditor(new QPushButton()));
// table.getColumnModel().getColumn(WarrantTableModel.MANUAL_RUN_COLUMN).setCellRenderer(new ButtonRenderer());
 _model->setColumnToHoldButton(table, WarrantTableModel::MANUAL_RUN_COLUMN);
// table.getColumnModel().getColumn(WarrantTableModel.EDIT_COLUMN).setCellEditor(new ButtonEditor(new QPushButton()));
// table.getColumnModel().getColumn(WarrantTableModel.EDIT_COLUMN).setCellRenderer(new ButtonRenderer());
 _model->setColumnToHoldButton(table, WarrantTableModel::EDIT_COLUMN);
// table.getColumnModel().getColumn(WarrantTableModel.DELETE_COLUMN).setCellEditor(new ButtonEditor(new QPushButton()));
// table.getColumnModel().getColumn(WarrantTableModel.DELETE_COLUMN).setCellRenderer(new ButtonRenderer());
 _model->setColumnToHoldButton(table, WarrantTableModel::DELETE_COLUMN);

 //table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
 for (int i=0; i<_model->columnCount(QModelIndex()); i++)
 {
  int width = _model->getPreferredWidth(i);
  table->getColumnModel()->getColumn(i)->setPreferredWidth(width);
 }
// for ( int i = 0; i < _model->rowCount(QModelIndex()); ++i )
// {
//  table->openPersistentEditor( _model->index(i, WarrantTableModel::ALLOCATE_COLUMN, QModelIndex()) );
//  table->openPersistentEditor( _model->index(i, WarrantTableModel::DEALLOC_COLUMN, QModelIndex()) );
//  table->openPersistentEditor( _model->index(i, WarrantTableModel::SET_COLUMN, QModelIndex()) );
//  table->openPersistentEditor( _model->index(i, WarrantTableModel::AUTO_RUN_COLUMN, QModelIndex()) );
//  table->openPersistentEditor( _model->index(i, WarrantTableModel::MANUAL_RUN_COLUMN, QModelIndex()) );
//  table->openPersistentEditor( _model->index(i, WarrantTableModel::EDIT_COLUMN, QModelIndex()) );
//  table->openPersistentEditor( _model->index(i, WarrantTableModel::DELETE_COLUMN, QModelIndex()) );
// }
 //_model->setPersistentButtons();
 _rowHeight = /*box.getPreferredSize().height;*/ table->getRowHeight();
// table->setRowHeight(_rowHeight);
 table->setDragEnabled(true);
// table.setTransferHandler(new jmri.util.DnDTableExportHandler());
 //_tablePane = new JScrollPane(table);

 connect(_model, SIGNAL(buttonClicked(QModelIndex*,QString)), _model, SLOT(on_buttonClicked(QModelIndex*,QString)));

 QWidget* tablePanel = new QWidget();
 //tablePanel.setLayout(new BoxLayout(tablePanel, BoxLayout.Y_AXIS));
 QVBoxLayout* tablePanelLayout = new QVBoxLayout(tablePanel);
 //tablePanelLayout->addWidget(Box.createVerticalGlue());
 QLabel* title = new QLabel(tr("Warrant List"));
 tablePanelLayout->addWidget(title);
 tablePanelLayout->addWidget(table);

 QWidget* bottom = new QWidget();
 bottom->setLayout(new QVBoxLayout);
 QWidget* panel = new QWidget();
 QHBoxLayout* panelLayout = new QHBoxLayout(panel);
 QPushButton* nxButton = new QPushButton(tr("Create NX Warrant"));
// nxButton.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent e) {
//         nxAction();
//     }
// });
 connect(nxButton, SIGNAL(clicked()), this, SLOT(on_nxButtonClicked()));
 panelLayout->addWidget(nxButton);
// panelLayout->addWidget(Box.createGlue());
 panelLayout->addWidget(new QLabel("status"));
// _status.addMouseListener(this);
// _status.setBackground(Color.white);
 QFont f = _status->font();
 //_status.setFont(jmri.util.FontUtil.deriveFont(_status.getFont(),java.awt.Font.BOLD));
 f.setBold(true);
 _status->setFont(f);
 _status->setEnabled(false);
 setStatusText(BLANK.mid(0,90), QColor(), false);
 _status->setColumns(90);
 panelLayout->addWidget(_status);
 QPushButton* haltAllButton = new QPushButton(tr("Halt All Trains"));
// haltAllButton.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent e) {
//         haltAllAction();
//     }
// });
 connect(haltAllButton, SIGNAL(clicked()), this, SLOT(haltAllAction()));
 haltAllButton->setStyleSheet(QString("QPushButton { color: red);"));
 //panelLayout->addWidget(Box.createGlue());
 panelLayout->addWidget(haltAllButton);
 bottom->layout()->addWidget(panel);///
 tablePanelLayout->addWidget(bottom);

// addWindowListener(new java.awt.event.WindowAdapter() {
//     //@Override
//         /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//             dispose();
//         }
//     });
 addWindowListener(new WTWindowListener(this));
 QMenuBar* menuBar = new QMenuBar();
 QMenu* fileMenu = new QMenu(tr("File"));
 fileMenu->addMenu(new SaveMenu());
 menuBar->addMenu(fileMenu);
 QMenu* warrantMenu = new QMenu(tr("Warrants"));
 QAction* act;
 warrantMenu->addAction(act = new AbstractAction(tr("Concatenate Warrants"),this));
// {
//     /*private*/ static final long serialVersionUID = 8994208663637773635L;
//     /*public*/ void actionPerformed(ActionEvent e) {
//         concatMenuAction();
//     }
// });
   connect(act, SIGNAL(triggered()), this, SLOT(concatMenuAction()));
 warrantMenu->addAction(new WarrantTableAction(tr("Create New Warrant"),this));
 warrantMenu->addAction((QAction*)WarrantTableAction::_trackerTable);
 warrantMenu->addAction(act =new AbstractAction(tr("Create NX Warrant"),this));
// {
//     /*private*/ static final long serialVersionUID = -4129760191508866189L;

//     /*public*/ void actionPerformed(ActionEvent e) {
//         nxAction();
//     }
// });
   connect(act, SIGNAL(triggered()), this, SLOT(on_nxButtonClicked()));
 warrantMenu->addAction(WarrantTableAction::getDefault()->makeLogMenu());
 menuBar->addMenu(warrantMenu);
 setMenuBar(menuBar);
 addHelpMenu("package.jmri.jmrit.logix.WarrantTable", true);

 //getContentPane().add(tablePanel);
 QWidget* centralWidget = new QWidget();
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
 setCentralWidget(centralWidget);
 centralWidgetLayout->addWidget(tablePanel);
//        setLocation(50,0);
 adjustSize();
}

/*protected*/ void WarrantTableFrame::scrollTable() {
// JScrollBar bar = _tablePane.getVerticalScrollBar();
// bar.setValue(bar.getMaximum());

}
void WarrantTableFrame::on_nxButtonClicked()
{
 WarrantTableFrame::nxAction();
}

/*protected*/ /*static*/ void WarrantTableFrame::nxAction() {
    NXFrame* nxFrame = NXFrame::getInstance();
    if (nxFrame->_controlPanel==NULL) {
        nxFrame->init();
    }
    nxFrame->setVisible(true);
}

/*private*/ void WarrantTableFrame::haltAllAction() {
    _model->haltAllTrains();
}

/*protected*/ void WarrantTableFrame::concatMenuAction() {
    _concatDialog = new JDialog(this, tr("ConcatWarrants"), false);
    QWidget* mainPanel = new QWidget();
    mainPanel->setLayout(new /*BorderLayout(5,5)*/QVBoxLayout);
    QWidget* panel = new QWidget();
    panel->setLayout(new QVBoxLayout);//(panel, BoxLayout.Y_AXIS));
//        panelLayout->addWidget(Box.createVerticalStrut(WarrantTableAction.STRUT_SIZE));
    QWidget* pp = new QWidget();
    pp->setLayout(new FlowLayout());
    pp->layout()->addWidget(new QLabel("A:"));
    pp->layout()->addWidget(_startWarrant);
    _startWarrant->setDragEnabled(true);
//    _startWarrant.setTransferHandler(new DnDStringImportHandler());
    panel->layout()->addWidget(pp);
    pp = new QWidget();
    pp->setLayout(new FlowLayout());
    pp->layout()->addWidget(new QLabel("B:"));
    pp->layout()->addWidget(_endWarrant);
    _endWarrant->setDragEnabled(true);
//    _endWarrant.setTransferHandler(new DnDStringImportHandler());
    panel->layout()->addWidget(pp);
    QPushButton* concatButton = new QPushButton(tr("Concatenate"));
//    concatButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            concatenate();
//        }
//    });
    connect(concatButton, SIGNAL(clicked()), this, SLOT(concatenate()));
//        panelLayout->addWidget(Box.createVerticalStrut(WarrantTableAction.STRUT_SIZE));
    panel->layout()->addWidget(concatButton); //, Box.CENTER_ALIGNMENT);
//        panelLayout->addWidget(Box.createVerticalStrut(WarrantTableAction.STRUT_SIZE));

    mainPanel->layout()->addWidget(panel);
    //_concatDialog.getContentPane().add(mainPanel);
    QVBoxLayout* dialogLayout = new QVBoxLayout(_concatDialog);
    dialogLayout->addWidget(mainPanel);

//    _concatDialog->setLocation(getLocation().x+50, getLocation().y+150);
    _concatDialog->adjustSize();
    _concatDialog->setVisible(true);
}
/*private*/ void WarrantTableFrame::concatenate() {
    /*
    WarrantManager manager = InstanceManager.getDefault(jmri.jmrit.logix.WarrantManager.class);
    Warrant* startW = manager.getWarrant(_startWarrant.getText().trim());
    Warrant* endW = manager.getWarrant(_endWarrant.getText().trim());
    */
    Warrant* startW = _model->getWarrant(_startWarrant->text().trimmed());
    Warrant* endW = _model->getWarrant(_endWarrant->text().trimmed());
    if (startW==NULL || endW==NULL) {
        showWarning("BadWarrantNames");
        return;
    }
    BlockOrder* last = startW->getLastOrder();
    BlockOrder* next = endW->getfirstOrder();
    if (last==NULL || next==NULL) {
        showWarning("EmptyRoutes");
        return;
    }
    if (last->getPathName()!=(next->getPathName()) || last->getBlock()!=(next->getBlock())) {
        showWarning("RoutesDontMatch");
        return;
    }
    CreateWarrantFrame* f = new CreateWarrantFrame();
    try {
        f->initComponents();
        f->concatenate(startW, endW);
    } catch (Exception ex ) { log->error("error making CreateWarrantFrame", ex);}
    f->setVisible(true);
    if (_concatDialog!=NULL) {
        _concatDialog->close();
    }
}

/*public*/ void WarrantTableFrame::showWarning(QString msg) {
//    JOptionPane.showMessageDialog(this, tr(msg, _startWarrant.getText(),_endWarrant.getText()),
//            tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
 QMessageBox::warning(this, tr("Warning"), msg);
}

/************************* Table ****************************************/
#if 0
static /*public*/ class ComboBoxCellEditor extends DefaultCellEditor
{
    /**
     *
     */
    /*private*/ static final long serialVersionUID = 3035798240606397980L;
    TableSorter _sorter;

    ComboBoxCellEditor(JComboBox <String> comboBox) {
        super(comboBox);
        comboBox.setFont(new Font(NULL, Font.PLAIN, 12));
    }
    ComboBoxCellEditor(JComboBox <String> comboBox, TableSorter sorter) {
        super(comboBox);
        comboBox.setFont(new Font(NULL, Font.PLAIN, 12));
        _sorter = sorter;
    }
    //@Override
    /*public*/ Component getTableCellEditorComponent(JTable table, Object value,
                                     boolean isSelected, int r, int column)
    {
        jmri.util.com.sun.TableSorter m = ((jmri.util.com.sun.TableSorter)table.getModel());
        WarrantTableModel model = (WarrantTableModel)m.getTableModel();

        // If table has been sorted, table row no longer is the same as array index
        int row =r;
        if (_sorter!=NULL) {
            row = _sorter.modelIndex(row);
        }
        Warrant* warrant = model.getWarrantAt(row);
        //@SuppressWarnings("unchecked")
        QComboBox* comboBox = (QComboBox*)getComponent();
        if (warrant == NULL) {
            log.warn("getWarrantAt row= " + row + " Warrant* is NULL!");
            return comboBox;
        }
        comboBox.removeAllItems();
        List <BlockOrder> orders = warrant.getBlockOrders();
        for (int i=0; i<orders.size(); i++) {
            BlockOrder order = orders.get(i);
            comboBox.addItem(order.getBlock().getDisplayName()+": - "+order.getPath().getName());
        }
        return comboBox;
    }
}
#endif
/**
 * Return error message if warrant cannot be run.
 * @param w warrant
 * @return NULL if warrant is started
 */
/*public*/ QString WarrantTableFrame::runTrain(Warrant* w, int mode) {
    QString msg = NULL;
    if (w->getRunMode() != mode) {
        msg = w->getRunModeMessage();
        setStatusText(msg, QColor(Qt::red), false);
        return msg;
    }
    msg = w->setRoute(0, NULL);
    setStatusText(msg, WarrantTableModel::myGold, false);
    if (msg!=NULL) {
        setStatusText(msg, QColor(Qt::red), false);
        return msg;
    }
    msg = w->setRunMode(Warrant::MODE_RUN, NULL, NULL, NULL, w->getRunBlind());
    if (msg!=NULL) {
        setStatusText(msg, QColor(Qt::red), false);
        return msg;
    }
    msg = w->checkStartBlock(Warrant::MODE_RUN);  // notify first block occupied by this train
    setStatusText(msg, WarrantTableModel::myGold, false);
    // From here on messages are status information, not abort info
    msg = w->checkRoute();   // notify about occupation ahead
    if (msg!=NULL) {
        setStatusText(msg, WarrantTableModel::myGreen, false);
    }
    return NULL;
}

/*public*/ void WarrantTableFrame::mouseClicked(QMouseEvent* /*event*/) {
    QMenu*  popup = new QMenu();
    for (int i=_statusHistory.size()-1; i>=0; i--) {
//        popup->add(_statusHistory.at(i));
    }
    //popup.show(_status, 0, 0);
    popup->exec(QCursor::pos());
}

/*public*/ void WarrantTableFrame::mousePressed(QMouseEvent* /*event*/) {}
/*public*/ void WarrantTableFrame::mouseEntered(QMouseEvent* /*event*/) {}
/*public*/ void WarrantTableFrame::mouseExited(QMouseEvent* /*event*/) {}
/*public*/ void WarrantTableFrame::mouseReleased(QMouseEvent* /*event*/) {}

void WarrantTableFrame::setStatusText(QString msg, QColor c, bool save)
{
/*      if (WarrantTableModel.myGold==(c)) {
        _status.setBackground(Color.lightGray);
    } else if (Color.red==(c)) {
        _status.setBackground(Color.white);
    } else {
        _status.setBackground(Color.white);
    }*/
    _status->setForeground(c);
    _status->setText(msg);
    if (save && msg!=NULL && msg.length()>0) {
        WarrantTableAction::getDefault()->writetoLog(msg);
        _statusHistory.append(msg);
        while (_statusHistory.size()>_maxHistorySize) {
            _statusHistory.removeAt(0);
        }
    }

}
/*static*/ QString WarrantTableFrame::BLANK = "        "
                                              "                                                                                         ";
/*public*/ QString WarrantTableFrame::getClassName()
{
 return "jmri.jmrit.logix.WarrantTableFrame";
}


QWidget* RouteBoxCellEditor::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
 WarrantTableModel* model = frame->getModel();
 JComboBox* comboBox = new JComboBox();
 Warrant* warrant = nullptr;
 if (model != nullptr) {
     warrant = model->getWarrantAt(index.row());
 }
 if (warrant == nullptr) {
     frame->log->warn(tr("getWarrantAt row= %1, Warrant is null!").arg(index.row()));
     //return getComponent();
     return comboBox;
 }
 QList<BlockOrder*>* orders = warrant->getBlockOrders();
 for (int i = 0; i < orders->size(); i++) {
     BlockOrder* order = orders->at(i);
     comboBox->addItem(order->getBlock()->getDisplayName() + ": - " + order->getPath()->getName());
 }
 return comboBox;
}

/*private*/ /*final*/ /*static*/ Logger* WarrantTableFrame::log = LoggerFactory::getLogger("WarrantTableFrame");
