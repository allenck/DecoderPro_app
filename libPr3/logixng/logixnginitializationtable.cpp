#include "logixnginitializationtable.h"
#include <QMenu>
#include <QMenuBar>
#include "jtable.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "beanselectpanel.h"
#include "defaultlogixngmanager.h"
#include "joptionpane.h"

/**
 * Table for LogixNG initialization.
 *
 * @author Daniel Bergqvist Copyright (C) 2021
 */
// /*public*/  class LogixNGInitializationTable extends JmriJFrame {

/*private*/ /*static*/ /*final*/ int LogixNGInitializationTable::panelWidth700 = 700;
/*private*/ /*static*/ /*final*/ int LogixNGInitializationTable::panelHeight500 = 500;



//@Override
/*public*/  void LogixNGInitializationTable::initComponents() {
    JmriJFrame::initComponents();
    setWindowTitle(tr("LogixNG Initialization Table "));
    // build menu
   QMenuBar* menuBar = new QMenuBar();
   setMenuBar(menuBar);
   addHelpMenu("package.jmri.jmrit.logixng.LogixNGInitializationTable", true); // NOI18N

    QWidget* contentPane = this->getContentPane();
    contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

    _initTableModel = new InitializationTableModel(this);
    JTable* conditionalTable = new JTable(_initTableModel);
    conditionalTable->setRowSelectionAllowed(false);
    TableColumnModel* conditionalColumnModel = conditionalTable
            ->getColumnModel();
    TableColumn* sNameColumn = conditionalColumnModel
            ->getColumn(InitializationTableModel::SYSTEM_NAME_COLUMN);
    sNameColumn->setResizable(true);
    sNameColumn->setMinWidth(100);
    sNameColumn->setPreferredWidth(130);
    TableColumn* uNameColumn = conditionalColumnModel
            ->getColumn(InitializationTableModel::USER_NAME_COLUMN);
    uNameColumn->setResizable(true);
    uNameColumn->setMinWidth(210);
    uNameColumn->setPreferredWidth(260);
    TableColumn* buttonDeleteColumn = conditionalColumnModel
            ->getColumn(InitializationTableModel::BUTTON_DELETE_COLUMN);
    TableColumn* buttonMoveUpColumn = conditionalColumnModel
            ->getColumn(InitializationTableModel::BUTTON_MOVE_UP_COLUMN);
    TableColumn* buttonMoveDownColumn = conditionalColumnModel
            ->getColumn(InitializationTableModel::BUTTON_MOVE_DOWN_COLUMN);

    // install button renderer and editor
    ButtonRenderer* buttonRenderer = new ButtonRenderer();
    conditionalTable->setDefaultRenderer("JButton", buttonRenderer);
//    TableCellEditor* buttonEditor = new ButtonEditor(new JButton());
    conditionalTable->setDefaultEditor("JButton", /*buttonEditor*/new PushButtonDelegate());
    JButton* testButton = new JButton("XXXXXXXXXX");  // NOI18N
    conditionalTable->setRowHeight(testButton->sizeHint().height());
    buttonDeleteColumn->setMinWidth(testButton->sizeHint().width());
    buttonDeleteColumn->setMaxWidth(testButton->sizeHint().width());
    buttonDeleteColumn->setResizable(false);
    buttonMoveUpColumn->setMinWidth(testButton->sizeHint().width());
    buttonMoveUpColumn->setMaxWidth(testButton->sizeHint().width());
    buttonMoveUpColumn->setResizable(false);
    buttonMoveDownColumn->setMinWidth(testButton->sizeHint().width());
    buttonMoveDownColumn->setMaxWidth(testButton->sizeHint().width());
    buttonMoveDownColumn->setResizable(false);

//    JScrollPane conditionalTableScrollPane = new JScrollPane(conditionalTable);
//    Dimension dim = conditionalTable.getPreferredSize();
//    dim.height = 450;
//    conditionalTableScrollPane.getViewport().setPreferredSize(dim);
    ((QVBoxLayout*)contentPane->layout())->addWidget(/*conditionalTableScrollPane*/conditionalTable, 1);

    // set up message
    JPanel* panel3 = new JPanel();
    panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));

    contentPane->layout()->addWidget(panel3);

    // set up create and cancel buttons
    JPanel* panel5 = new JPanel();
    panel5->setLayout(new FlowLayout());

    // Add LogixNG
    BeanSelectPanel/*<LogixNG>*/* logixNG_SelectPanel =
            new BeanSelectPanel((AbstractManager*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->mself(), nullptr);

    panel5->layout()->addWidget(logixNG_SelectPanel);
    JButton* addLogixNG = new JButton(tr("Add initialization LogixNG"));    // NOI18N
    panel5->layout()->addWidget(addLogixNG);
    connect(addLogixNG, &JButton::clicked, [=]{
     if(logixNG_SelectPanel->getNamedBean()){
        LogixNG* logixNG = (LogixNG*)logixNG_SelectPanel->getNamedBean()->self();
        if (logixNG == nullptr) {
            JOptionPane::showMessageDialog(this,
                    tr("No LogixNG is selected"),
                    tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        }
        for (LogixNG* l : _initManager->getList()) {
            if (logixNG == l) {
                JOptionPane::showMessageDialog(this,
                        tr("The LogixNG is already in the initialization table"),
                        tr("Error"),
                        JOptionPane::ERROR_MESSAGE);
                return;
            }
        }
        _initManager->add(logixNG);
        _initTableModel->fireTableStructureChanged();
      }
     });
    contentPane->layout()->addWidget(panel5);

    pack();

    initMinimumSize(QSize(panelWidth700, panelHeight500));
}

/*public*/  void LogixNGInitializationTable::initMinimumSize(QSize dimension) {
    setMinimumSize(dimension);
    pack();
    setVisible(true);
}

// ------------ Table Models ------------

/**
 * Table model for ConditionalNGs in the Edit LogixNG pane.
 */
///*private*/ final class InitializationTableModel extends AbstractTableModel {

//    /*public*/  static final int SYSTEM_NAME_COLUMN = 0;
//    /*public*/  static final int USER_NAME_COLUMN = SYSTEM_NAME_COLUMN + 1;
//    /*public*/  static final int BUTTON_DELETE_COLUMN = USER_NAME_COLUMN + 1;
//    /*public*/  static final int BUTTON_MOVE_UP_COLUMN = BUTTON_DELETE_COLUMN + 1;
//    /*public*/  static final int BUTTON_MOVE_DOWN_COLUMN = BUTTON_MOVE_UP_COLUMN + 1;
//    /*public*/  static final int NUM_COLUMNS = BUTTON_MOVE_DOWN_COLUMN + 1;

//    /*private*/ final List<LogixNG> _logixNGs;


    /*public*/  InitializationTableModel::InitializationTableModel(LogixNGInitializationTable* frame, QObject* parent) : AbstractTableModel(parent){
        //super();
 setObjectName("InitializationTableModel");
 this->frame = frame;
        _logixNGs = frame->_initManager->getList();
    }

    //@Override
    /*public*/  /*Class<?>*/QString InitializationTableModel::getColumnClass(int c) const{
        if ((c == BUTTON_DELETE_COLUMN) || (c == BUTTON_MOVE_UP_COLUMN) || (c == BUTTON_MOVE_DOWN_COLUMN)) {
            return "JButton";
        }
        return "String";
    }

    //@Override
    /*public*/  int InitializationTableModel::columnCount(const QModelIndex&) const {
        return NUM_COLUMNS;
    }

    //@Override
    /*public*/  int InitializationTableModel::rowCount(const QModelIndex&) const {
        return _logixNGs.size();
    }

    //@Override
    /*public*/  Qt::ItemFlags InitializationTableModel::flags(const QModelIndex &index) const {
        if ((index.column() == BUTTON_DELETE_COLUMN) || (index.column() == BUTTON_MOVE_UP_COLUMN) || (index.column() == BUTTON_MOVE_DOWN_COLUMN))
         return Qt::ItemIsEnabled | Qt::ItemIsEditable;
        return Qt::ItemIsEnabled;
    }

    //@Override
    /*public*/  QVariant InitializationTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
     if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
     {
        switch (section) {
            case SYSTEM_NAME_COLUMN:
                return tr("System Name");  // NOI18N
            case USER_NAME_COLUMN:
                return tr("User Name");  // NOI18N
            case BUTTON_DELETE_COLUMN:
            case BUTTON_MOVE_UP_COLUMN:
            case BUTTON_MOVE_DOWN_COLUMN:
                return ""; // no label
            default:
                throw new IllegalArgumentException("Unknown column");
        }
     }
     return AbstractTableModel::headerData(section, orientation, role);
    }

    //@Override
    /*public*/  QVariant InitializationTableModel::data(const QModelIndex &index, int role) const {
     if(role == Qt::DisplayRole)
     {
      int row = index.row();
        if (row > _logixNGs.size()) {
            return QVariant();
        }
        switch (index.column()) {
            case SYSTEM_NAME_COLUMN:
                return _logixNGs.at(row)->NamedBean::getSystemName();
            case USER_NAME_COLUMN:
                return _logixNGs.at(row)->NamedBean::getUserName();
            case BUTTON_DELETE_COLUMN:
                return tr("Delete");  // NOI18N
            case BUTTON_MOVE_UP_COLUMN:
                return tr("Move Up");  // NOI18N
            case BUTTON_MOVE_DOWN_COLUMN:
                return tr("Move Down");  // NOI18N
            default:
                throw new IllegalArgumentException("Unknown column");
        }
     }
     return AbstractTableModel::data(index, role);
    }

    /*private*/ void InitializationTableModel::deleteLogixNG(int row) {
        frame->_initManager->_delete(row);
        fireTableRowsDeleted(row, row);
    }

    /*private*/ void InitializationTableModel::moveUp(int row) {
        frame->_initManager->moveUp(row);
        fireTableRowsDeleted(row, row);
    }

    /*private*/ void InitializationTableModel::moveDown(int row) {
        frame->_initManager->moveDown(row);
        fireTableRowsDeleted(row, row);
    }

    //@Override
    /*public*/  bool InitializationTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
     int row = index.row();
     if(role == Qt::EditRole){
        if (row > _logixNGs.size()) {
            return false;
        }
        switch (index.column()) {
            case SYSTEM_NAME_COLUMN:
                throw new IllegalArgumentException("System name cannot be changed");
            case USER_NAME_COLUMN:
                throw new IllegalArgumentException("User name cannot be changed");
            case BUTTON_DELETE_COLUMN:
                deleteLogixNG(row);
                break;
            case BUTTON_MOVE_UP_COLUMN:
                moveUp(row);
                break;
            case BUTTON_MOVE_DOWN_COLUMN:
                moveDown(row);
                break;
            default:
                throw new IllegalArgumentException("Unknown column");
        }
        return true;
    }
    return false;
  }
