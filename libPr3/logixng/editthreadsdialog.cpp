#include "editthreadsdialog.h"
#include "logixng_thread.h"
#include "defaultconditionalng.h"
#include "jdialog.h"
#include <QBoxLayout>
#include "jlabel.h"
#include "jtable.h"
#include "jtextfield.h"
#include "joptionpane.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "jpanel.h"

/**
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/  class EditThreadsDialog {



    /*public*/  EditThreadsDialog::EditThreadsDialog(ConditionalNG* conditionalNG,QObject *parent) : QObject(parent) {
        // Ensure that the predefined threads exist
        LogixNG_Thread::getThread(LogixNG_Thread::DEFAULT_LOGIXNG_THREAD);
        LogixNG_Thread::getThread(LogixNG_Thread::DEFAULT_LOGIXNG_DEBUG_THREAD);

        _conditionalNG = conditionalNG;
        _newStartupThread = LogixNG_Thread::getThread(_conditionalNG->getStartupThreadId());
    }

    /*public*/  void EditThreadsDialog::showDialog() {

        _editThreadsDialog  = new JDialog(
                (JDialog*)nullptr,
                tr("Edit threads"),
                true);


        QWidget* contentPane = _editThreadsDialog->getContentPane();
        contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

        _startupThreadNameLabel = new JLabel(tr(
                "Startup thread: %1").arg(
                _newStartupThread->getThreadName()));
        contentPane->layout()->addWidget(_startupThreadNameLabel);

        _threadTableModel = new ThreadTableModel(this);
        JTable* conditionalTable = new JTable(_threadTableModel);
        conditionalTable->setRowSelectionAllowed(false);
        TableColumnModel* conditionalColumnModel = conditionalTable
                ->getColumnModel();
        TableColumn* sNameColumn = conditionalColumnModel
                ->getColumn(ThreadTableModel::THREAD_ID_COLUMN);
        sNameColumn->setResizable(true);
        sNameColumn->setMinWidth(100);
        sNameColumn->setPreferredWidth(130);
        TableColumn* uNameColumn = conditionalColumnModel
                ->getColumn(ThreadTableModel::THREAD_NAME_COLUMN);
        uNameColumn->setResizable(true);
        uNameColumn->setMinWidth(210);
        uNameColumn->setPreferredWidth(260);
        TableColumn* buttonColumn = conditionalColumnModel
                ->getColumn(ThreadTableModel::BUTTON_SELECT_THREAD_COLUMN);
        TableColumn* buttonDeleteColumn = conditionalColumnModel
                ->getColumn(ThreadTableModel::BUTTON_DELETE_COLUMN);

        // install button renderer and editor
//        ButtonRenderer buttonRenderer = new ButtonRenderer();
//        conditionalTable.setDefaultRenderer(JButton.class, buttonRenderer);
        conditionalTable->setItemDelegateForColumn(ThreadTableModel::BUTTON_DELETE_COLUMN,new PushButtonDelegate() );
        conditionalTable->setItemDelegateForColumn(ThreadTableModel::BUTTON_SELECT_THREAD_COLUMN,new PushButtonDelegate() );//        TableCellEditor buttonEditor = new ButtonEditor(new JButton());
//        conditionalTable.setDefaultEditor(JButton.class, buttonEditor);
        JButton* testButton = new JButton("XXXXXX");  // NOI18N
        conditionalTable->setRowHeight(testButton->sizeHint().height());
        buttonColumn->setMinWidth(testButton->sizeHint().width());
        buttonColumn->setMaxWidth(testButton->sizeHint().width());
        buttonColumn->setResizable(false);
        buttonDeleteColumn->setMinWidth(testButton->sizeHint().width());
        buttonDeleteColumn->setMaxWidth(testButton->sizeHint().width());
        buttonDeleteColumn->setResizable(false);

//        JScrollPane conditionalTableScrollPane = new JScrollPane(conditionalTable);
//        Dimension dim = conditionalTable.getPreferredSize();
//        dim.height = 450;
//        conditionalTableScrollPane.getViewport().setPreferredSize(dim);
        ((QVBoxLayout*)contentPane->layout())->addWidget(/*conditionalTableScrollPane*/conditionalTable,1);

        // set up message
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));

        contentPane->layout()->addWidget(panel3);

        // set up create and cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());

        // Add thread
        JButton* addThread = new JButton(tr("Add thread"));    // NOI18N
        panel5->layout()->addWidget(addThread);
        connect(addThread, &JButton::clicked, [=] {
            QString newName = "";
            if (! LogixNG_Thread::validateNewThreadName(newName)) {
                JOptionPane::showMessageDialog(nullptr,
                        tr("There is already a thread with the name \"%1\"").arg(newName),
                        tr("Error"),
                        JOptionPane::ERROR_MESSAGE);
                return;
            }
            LogixNG_Thread* thread = LogixNG_Thread::createNewThread(newName);
            int row = _threadTableModel->_threads.size();
            _threadTableModel->_threads.append(thread);
            _threadTableModel->fireTableRowsInserted(row, row);
        });
//        addThread.setToolTipText(Bundle.getMessage("CancelLogixButtonHint"));      // NOI18N

        // Cancel
        JButton* cancel = new JButton(tr("Cancel"));    // NOI18N
        panel5->layout()->addWidget(cancel);
        connect(cancel, &JButton::clicked, [=] {
            abortPressed();
        });
//        cancel.setToolTipText(Bundle.getMessage("CancelLogixButtonHint"));      // NOI18N

        // OK
        JButton* ok = new JButton(tr("OK"));    // NOI18N
        panel5->layout()->addWidget(ok);
        connect(ok, &JButton::clicked, [=]  {
            okPressed();
        });
//        ok.setToolTipText(Bundle.getMessage("OKLogixButtonHint"));      // NOI18N

//        _editThreadsDialog.addWindowListener(new java.awt.event.WindowAdapter() {
//            //@Override
//            /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
//                abortPressed();
//            }
//        });
/*
        _create = new JButton(Bundle.getMessage("ButtonCreate"));  // NOI18N
        panel5.add(_create);
        _create.addActionListener((ActionEvent e) -> {
            cancelAddPressed(null);

            SwingConfiguratorInterface swingConfiguratorInterface =
                    _swingConfiguratorComboBox.getItemAt(_swingConfiguratorComboBox.getSelectedIndex());
//            System.err.format("swingConfiguratorInterface: %s%n", swingConfiguratorInterface.getClass().getName());
            createAddFrame(femaleSocket, path, swingConfiguratorInterface);
        });
*/
        contentPane->layout()->addWidget(panel5);

//        addLogixNGFrame.setLocationRelativeTo(component);
        _editThreadsDialog->setLocationRelativeTo(nullptr);
        _editThreadsDialog->pack();
        _editThreadsDialog->setVisible(true);
        _editThreadsDialog->exec();
    }

    /*private*/ void EditThreadsDialog::abortPressed() {
        _editThreadsDialog->setVisible(false);
        _editThreadsDialog->dispose();
        _editThreadsDialog = nullptr;
    }

    /*private*/ void EditThreadsDialog::okPressed() {
        _editThreadsDialog->setVisible(false);
        _editThreadsDialog->dispose();
        _editThreadsDialog = nullptr;
        _conditionalNG->setStartupThreadId(_newStartupThread->getThreadId());
    }









    // ------------ Table Models ------------

    /**
     * Table model for ConditionalNGs in the Edit LogixNG pane.
//     */
//    /*private*/ final class ThreadTableModel extends AbstractTableModel {

//        /*public*/  static final int THREAD_ID_COLUMN = 0;
//        /*public*/  static final int THREAD_NAME_COLUMN = THREAD_ID_COLUMN + 1;
//        /*public*/  static final int BUTTON_SELECT_THREAD_COLUMN = THREAD_NAME_COLUMN + 1;
//        /*public*/  static final int BUTTON_DELETE_COLUMN = BUTTON_SELECT_THREAD_COLUMN + 1;
//        /*public*/  static final int NUM_COLUMNS = BUTTON_DELETE_COLUMN + 1;

//        /*private*/ final java.util.List<LogixNG_Thread> _threads;


        /*public*/  ThreadTableModel::ThreadTableModel(EditThreadsDialog *dlg) : AbstractTableModel() {
            //super();
            this->dlg = dlg;
            _threads = QList<LogixNG_Thread*>(LogixNG_Thread::getThreads().toList());
        }

        //@Override
        /*public*/  QString ThreadTableModel::getColumnClass(int c) const{
            if ((c == BUTTON_SELECT_THREAD_COLUMN) || (c == BUTTON_DELETE_COLUMN)) {
                return "JButton";
            } else if (c == THREAD_ID_COLUMN) {
                return "Integer";
            }
            return "String";
        }

        //@Override
        /*public*/  int ThreadTableModel::columnCount(const QModelIndex&) const  {
            return NUM_COLUMNS;
        }

        //@Override
        /*public*/  int ThreadTableModel::rowCount(const QModelIndex&) const {
            return _threads.size();
        }

        //@Override
        /*public*/  Qt::ItemFlags ThreadTableModel::flags(const QModelIndex& index) const {
            int c = index.column();
            int r = index.row();
            if ((c == THREAD_NAME_COLUMN) || (c == BUTTON_SELECT_THREAD_COLUMN)) {
                return Qt::ItemIsEditable | Qt::ItemIsEnabled;
            }
            return ((c == BUTTON_DELETE_COLUMN) && (! _threads.at(r)->getThreadInUse()))?Qt::ItemIsEditable | Qt::ItemIsEnabled:Qt::ItemIsEnabled;
        }

        //@Override
        /*public*/  QVariant ThreadTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
           if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
           {
            switch (section) {
                case THREAD_ID_COLUMN:
                    return tr("System Name");  // NOI18N
                case THREAD_NAME_COLUMN:
                    return tr("User Name");  // NOI18N
                case BUTTON_SELECT_THREAD_COLUMN:
                    return ""; // no label
                case BUTTON_DELETE_COLUMN:
                    return ""; // no label
                default:
                    throw new IllegalArgumentException("Unknown column");
            }
           }
           return  QVariant();
        }

//        @edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "DB_DUPLICATE_SWITCH_CLAUSES",
//                justification = "better to keep cases in column order rather than to combine")
        /*public*/  int ThreadTableModel::getPreferredWidth(int col) {
            switch (col) {
                case THREAD_ID_COLUMN:
                    return JTextField(6).getPreferredSize().width();
                case THREAD_NAME_COLUMN:
                    return  JTextField(17).getPreferredSize().width();
                case BUTTON_SELECT_THREAD_COLUMN:
                    return  JTextField(6).getPreferredSize().width();
                case BUTTON_DELETE_COLUMN:
                    return  JTextField(6).getPreferredSize().width();
                default:
                    throw new IllegalArgumentException("Unknown column");
            }
        }

        //@Override
        /*public*/  QVariant ThreadTableModel::data(const QModelIndex &index, int role) const {
         if(role == Qt::DisplayRole){
            if (index.row() > _threads.size()) {
                return QVariant();
            }
            switch (index.column()) {
                case BUTTON_SELECT_THREAD_COLUMN:
                    return tr("Select thread");  // NOI18N
                case BUTTON_DELETE_COLUMN:
                    return tr("Delete");  // NOI18N
                case THREAD_ID_COLUMN:
                    return _threads.at(index.row())->getThreadId();
                case THREAD_NAME_COLUMN: {
                    return _threads.at(index.row())->getThreadName();
                }
                default:
                    throw new IllegalArgumentException("Unknown column");
            }
         }
         return  QVariant();
        }

        /*private*/ void ThreadTableModel::deleteThread(int row) {
            LogixNG_Thread* thread = _threads.at(row);
            LogixNG_Thread::deleteThread(thread);
            fireTableRowsDeleted(row, row);
        }

        /*private*/ void ThreadTableModel::changeThreadName(QVariant value, int row) {
            QString name = value.toString();
            LogixNG_Thread* thread = _threads.at(row);
            if (thread->getThreadName() != (name)) {
                if (! LogixNG_Thread::validateNewThreadName(name)) {
                    JOptionPane::showMessageDialog(nullptr,
                            tr("There is already a thread with the name \"%1\"").arg(name),
                            tr("Errore"),
                            JOptionPane::ERROR_MESSAGE);
                    return;
                }
                thread->setThreadName(name);
                fireTableRowsUpdated(row, row);
            }
        }

        //@Override
        /*public*/  bool ThreadTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
         if(role == Qt::EditRole){
          int row = index.row();
            if (row > _threads.size()) {
                return false;
            }
            switch (index.column()) {
                case BUTTON_SELECT_THREAD_COLUMN:
                    dlg->_newStartupThread = _threads.at(row);
                    dlg->_startupThreadNameLabel->setText(tr(
                            "Startup thread: %1").arg(
                            dlg->_newStartupThread->getThreadName()));
                    break;
                case BUTTON_DELETE_COLUMN:
                    deleteThread(row);
                    break;
                case THREAD_ID_COLUMN:
                    throw new IllegalArgumentException("Thread ID cannot be changed");
                case THREAD_NAME_COLUMN: {
                    changeThreadName(value, row);
                    break;
                }
                default:
                    throw new IllegalArgumentException("Unknown column");
            }
            return  true;
        }
         return false;
      }
