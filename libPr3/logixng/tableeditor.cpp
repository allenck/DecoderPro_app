#include "tableeditor.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "fileutil.h"
#include "jfilechooser.h"
#include "filenameextensionfilter.h"
#include "defaultcsvnamedtable.h"
#include "jtable.h"
#include "defaultlistselectionmodel.h"
#include "listmodel.h"
#include "userpreferencesmanager.h"
#include "defaultclipboard.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "referenceutil.h"
#include "joptionpane.h"
#include "runtimeexception.h"
#include "defaultnamedtablemanager.h"

/**
 * Editor for LogixNG Tables
 *
 * @author Dave Duchamp Copyright (C) 2007  (ConditionalListEdit)
 * @author Pete Cressman Copyright (C) 2009, 2010, 2011  (ConditionalListEdit)
 * @author Matthew Harris copyright (c) 2009  (ConditionalListEdit)
 * @author Dave Sand copyright (c) 2017  (ConditionalListEdit)
 * @author Daniel Bergqvist (c) 2019
 */
//    /*public*/ final class TableEditor implements AbstractLogixNGEditor<NamedTable> {




    /**
     * Create a new ConditionalNG List View editor.
     *
     * @param m the bean table model
     * @param sName name of the NamedTable being edited
     */
    /*public*/ TableEditor::TableEditor(BeanTableDataModel/*<NamedTable>*/* m, QString sName, QObject* parent)
      : QObject(parent) {
        _tableManager = (DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager");
        _curTable = (AbstractNamedTable*)_tableManager->getBySystemName(sName)->self();
        makeEditTableWindow();
    }

// ------------ Methods for Edit NamedTable Pane ------------

    /*private*/ JButton* TableEditor::createFileChooser() {
        JButton* selectFileButton = new JButton("..."); // "File" replaced by ...
        selectFileButton->setMaximumSize(selectFileButton->sizeHint());
        selectFileButton->setToolTip(tr("Click to select a file from disk"));  // NOI18N
        connect(selectFileButton, &JButton::clicked, [=]{
            JFileChooser* csvFileChooser = new JFileChooser(FileUtil::getUserFilesPath());
            csvFileChooser->setFileFilter("CSV files(*.csv, *.txt");//"//new FileNameExtensionFilter("CSV files", "csv", "txt")); // NOI18N
//            csvFileChooser->rescanCurrentDirectory();
            int retVal = csvFileChooser->showOpenDialog(nullptr);
            // handle selection or cancel
            if (retVal == JFileChooser::APPROVE_OPTION) {
                // set selected file location
                try {
                    editCsvTableName->setText(FileUtil::getPortableFilename(csvFileChooser->getSelectedFile()->getCanonicalPath()));
                } catch (IOException* ex) {
                    log->error(tr("exception setting file location: %1").arg( ex->getMessage()));  // NOI18N
                    editCsvTableName->setText("");
                }
            }
        });
        return selectFileButton;
    }


    /**
     * Create and/or initialize the Edit NamedTable pane.
     */
    /*private*/ void TableEditor::makeEditTableWindow() {
        editUserName->setText(_curTable->getUserName());
        // clear conditional table if needed
        if (tableTableModel != nullptr) {
            tableTableModel->fireTableStructureChanged();
        }
        _inEditMode = true;
        if (_editLogixNGFrame == nullptr) {
            if (_curTable->getUserName() != nullptr) {
                _editLogixNGFrame = new JmriJFrame(
                        tr("Edit LogixNG %1 - %2").arg(
                                _curTable->getSystemName(),   // NOI18N
                                _curTable->getUserName()),    // NOI18N
                        false,
                        false);
            } else {
                _editLogixNGFrame = new JmriJFrame(
                        tr("Edit LogixNG %1").arg(_curTable->getSystemName()),  // NOI18N
                        false,
                        false);
            }
            _editLogixNGFrame->addHelpMenu(
                    "package.jmri.jmrit.logixng.LogixNGTableTableEditor", true);  // NOI18N
            _editLogixNGFrame->setLocation(100, 30);
            QWidget* contentPane = _editLogixNGFrame->getContentPane();
            contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));
            JPanel* panel1 = new JPanel();
            panel1->setLayout(new FlowLayout());
            JLabel* systemNameLabel = new JLabel(tr("SystemName") + ":");  // NOI18N
            panel1->layout()->addWidget(systemNameLabel);
            JLabel* fixedSystemName = new JLabel(_curTable->getSystemName());
            panel1->layout()->addWidget(fixedSystemName);
            contentPane->layout()->addWidget(panel1);
            JPanel* panel2 = new JPanel();
            panel2->setLayout(new FlowLayout());
            JLabel* userNameLabel = new JLabel(tr("UserName") + ":");  // NOI18N
            panel2->layout()->addWidget(userNameLabel);
            panel2->layout()->addWidget(editUserName);
            editUserName->setToolTip(tr("Enter new user name for LogixNG, e.g. Signal 2 Control"));  // NOI18N
            contentPane->layout()->addWidget(panel2);

            bool isCsvTable = qobject_cast<DefaultCsvNamedTable*>(_curTable);

            JPanel* panel3 = new JPanel();
            panel3->setLayout(new FlowLayout());
            JLabel* tableTypeLabel = new JLabel(tr("Table type") + ": ");  // NOI18N
            panel3->layout()->addWidget(tableTypeLabel);
            panel3->layout()->addWidget(new JLabel(
                    isCsvTable
                            ? tr("CSV table")
                            : tr("Unknown table type")));
            contentPane->layout()->addWidget(panel3);

            if (isCsvTable) {
                JPanel* panel4 = new JPanel();
                panel4->setLayout(new FlowLayout());
                JLabel* tableFileNameLabel = new JLabel(tr("FileName") + ": ");  // NOI18N
                panel4->layout()->addWidget(tableFileNameLabel);
//                panel4->layout()->addWidget(new JLabel(((DefaultCsvNamedTable)_curTable).getFileName()));
                editCsvTableName->setText(((DefaultCsvNamedTable*)_curTable)->getFileName());
                panel4->layout()->addWidget(editCsvTableName);
//                editCsvTableName->setToolTipText(Bundle.getMessage("LogixNGUserNameHint2"));  // NOI18N
                panel4->layout()->addWidget(createFileChooser());
                contentPane->layout()->addWidget(panel4);
            }


            // add table of Tables
            JPanel* pctSpace = new JPanel();
            pctSpace->setLayout(new FlowLayout());
            pctSpace->layout()->addWidget(new JLabel("   "));
            contentPane->layout()->addWidget(pctSpace);
            JPanel* pTitle = new JPanel();
            pTitle->setLayout(new FlowLayout());
//            pTitle->layout()->addWidget(new JLabel(Bundle.getMessage("ConditionalNGTableTitle")));  // NOI18N
            contentPane->layout()->addWidget(pTitle);
            // initialize table of conditionals
            tableTableModel = new TableTableModel(this);
            JTable* tableTable = new JTable(tableTableModel);
// TODO:            tableTable->setSelectionMode(ListSelectionModel::SINGLE_SELECTION);
            tableTable->setAutoResizeMode( JTable::AUTO_RESIZE_OFF );
// TODO:            tableTable->getTableHeader()->setReorderingAllowed(false);

            JButton* cellRefByIndexButton = new JButton(tr("Copy to clipboard"));  // NOI18N
            JLabel* cellRefByIndexLabel = new JLabel();  // NOI18N
            JTextField* cellRefByIndex = new JTextField();
            cellRefByIndex->setEditable(false);
            cellRefByIndexButton->setEnabled(false);

            JButton* cellRefByHeaderButton = new JButton(tr("Copy to clipboard"));  // NOI18N
            JLabel* cellRefByHeaderLabel = new JLabel();  // NOI18N
            JTextField* cellRefByHeader = new JTextField();
            cellRefByHeader->setEditable(false);
            cellRefByHeaderButton->setEnabled(false);
#if 0 //TODO
            Clipboard* clipboard =
                    Toolkit.getDefaultToolkit().getSystemClipboard();

            connect(cellRefByIndexButton, &JButton::clicked, [=] { clipboard->setContents(new StringSelection(cellRefByIndexLabel.getText()), null);});

            connect(cellRefByHeaderButton, &JButton::clicked, [=]{ clipboard->setContents(new StringSelection(cellRefByHeaderLabel.getText()), null);});
#endif
            ListSelectionListener* selectCellListener = new TEListSelectionListener(tableTable,
                                                                                    cellRefByIndexLabel,
                                                                                    cellRefByIndex,
                                                                                    cellRefByIndexButton,
                                                                                    cellRefByHeaderButton,
                                                                                    cellRefByHeaderLabel,
                                                                                    cellRefByHeader,
                                                                                    this);
//                {
//                QString refByIndex = QString("{%1[%2,%3]}").arg(_curTable->getDisplayName()).arg(tableTable->getSelectedRow()+1, tableTable->getSelectedColumn()+1);
//                cellRefByIndexLabel->setText(refByIndex);  // NOI18N
//                cellRefByIndex->setText(ReferenceUtil.getReference(symbolTable, refByIndex));  // NOI18N
//                cellRefByIndexButton->setEnabled(true);

//                QVariant rowHeaderObj = _curTable.getCell(tableTable.getSelectedRow()+1, 0);
//                QVariant columnHeaderObj = _curTable.getCell(0, tableTable.getSelectedColumn()+1);
//                QString rowHeader = rowHeaderObj != null ? rowHeaderObj.toString() : "";
//                QString columnHeader = columnHeaderObj != null ? columnHeaderObj.toString() : "";
//                if (!rowHeader.isEmpty() && !columnHeader.isEmpty()) {
//                    cellRefByHeaderButton->setEnabled(true);
//                    String refByHeader = String.format("{%s[%s,%s]}", _curTable.getDisplayName(), _curTable.getCell(tableTable.getSelectedRow()+1,0), _curTable.getCell(0,tableTable.getSelectedColumn()+1));
//                    cellRefByHeaderLabel->setText(refByHeader);  // NOI18N
//                    cellRefByHeader->setText(ReferenceUtil.getReference(symbolTable, refByIndex));  // NOI18N
//                } else {
//                    cellRefByHeaderButton->setEnabled(false);
//                    cellRefByHeaderLabel->setText("");    // NOI18N
//                    cellRefByHeader->setText("");        // NOI18N
//                }
//            };
            tableTable->getSelectionModel()->addListSelectionListener(selectCellListener);
            tableTable->getColumnModel()->getSelectionModel()->addListSelectionListener(selectCellListener);

            ListModel/*<Object>*/* lm = new RowHeaderListModel(this);

            JList/*<Object>*/* rowHeader = new JList(lm);
#if 0 //TODO:
            rowHeader->setFixedCellHeight(
                    tableTable->getRowHeight()
//                    tableTable.getRowHeight() + tableTable.getRowMargin()
//                    + table.getIntercellSpacing().height
            );

            rowHeader->setCellRenderer(new RowHeaderRenderer(tableTable));
#endif
//            JScrollPane tableTableScrollPane = new JScrollPane(tableTable);
//            tableTableScrollPane->setRowHeaderView(rowHeader);
            QSize dim = tableTable->sizeHint();
            dim.setHeight(450);
//            tableTableScrollPane.getViewport()->setPreferredSize(dim);
            contentPane->layout()->addWidget(/*tableTableScrollPane*/tableTable);

            JPanel* panel4 = new JPanel();
            panel4->setLayout(new FlowLayout());
            panel4->layout()->addWidget(cellRefByIndexButton);
            panel4->layout()->addWidget(cellRefByIndexLabel);
            panel4->layout()->addWidget(cellRefByIndex);
            contentPane->layout()->addWidget(panel4);

            JPanel* panel5 = new JPanel();
            panel5->setLayout(new FlowLayout());
            panel5->layout()->addWidget(cellRefByHeaderButton);
            panel5->layout()->addWidget(cellRefByHeaderLabel);
            panel5->layout()->addWidget(cellRefByHeader);
            contentPane->layout()->addWidget(panel5);

            // add buttons at bottom of window
            JPanel* panel6 = new JPanel();
            panel6->setLayout(new FlowLayout());
            // Bottom Buttons - Cancel NamedTable
            JButton* cancelButton = new JButton(tr("Cancel"));  // NOI18N
            panel6->layout()->addWidget(cancelButton);
            connect(cancelButton, &JButton::clicked, [=] {
                finishDone();
            });
//            done->setToolTipText(Bundle.getMessage("CancelButtonHint"));  // NOI18N
            // Bottom Buttons - Ok NamedTable
            JButton* okButton = new JButton(tr("OK"));  // NOI18N
            panel6->layout()->addWidget(okButton);
            connect(okButton, &JButton::clicked, [=] {
                okPressed(/*e*/);
            });
//            done->setToolTipText(Bundle.getMessage("OkButtonHint"));  // NOI18N
            // Delete NamedTable
            JButton* _delete = new JButton(tr("Delete"));  // NOI18N
            panel6->layout()->addWidget(_delete);
            connect(_delete, &JButton::clicked, [=] {
                deletePressed();
            });
            _delete->setToolTip(tr("Press to delete this LogixNG and all its ConditionalNGs"));  // NOI18N
            contentPane->layout()->addWidget(panel6);
        }
#if 0 // TODO:
        _editLogixNGFrame.addWindowListener(new java.awt.event.WindowAdapter() {
            @Override
            public void windowClosing(java.awt.event.WindowEvent e) {
                if (_inEditMode) {
                    okPressed(null);
                } else {
                    finishDone();
                }
            }
        });
#endif
        _editLogixNGFrame->pack();
        _editLogixNGFrame->setVisible(true);
    }
/*public*/ void TEListSelectionListener::valueChanged(ListSelectionEvent(*))
{
    QString refByIndex = QString("{%1[%2,%3]}").arg(editor->_curTable->getDisplayName()).arg(_tableTable->getSelectedRow()+1,
                                                                      _tableTable->getSelectedColumn()+1);
    cellRefByIndexLabel->setText(refByIndex);  // NOI18N
    cellRefByIndex->setText(ReferenceUtil::getReference(editor->symbolTable, refByIndex));  // NOI18N
    cellRefByIndexButton->setEnabled(true);

    QVariant rowHeaderObj = editor->_curTable->getCell(_tableTable->getSelectedRow()+1, 0);
    QVariant columnHeaderObj = editor->_curTable->getCell(0, _tableTable->getSelectedColumn()+1);
    QString rowHeader = rowHeaderObj != "" ? rowHeaderObj.toString() : "";
    QString columnHeader = columnHeaderObj != "" ? columnHeaderObj.toString() : "";
    if (!rowHeader.isEmpty() && !columnHeader.isEmpty()) {
        cellRefByHeaderButton->setEnabled(true);
        QString refByHeader = QString("{%1[%2,%3]}").arg(editor->_curTable->getDisplayName(),
                                                        editor->_curTable->getCell(_tableTable->getSelectedRow()+1,0).toString(),
                                                         editor->_curTable->getCell(0,_tableTable->getSelectedColumn()+1).toString());
        cellRefByHeaderLabel->setText(refByHeader);  // NOI18N
        cellRefByHeader->setText(ReferenceUtil::getReference(editor->symbolTable, refByIndex));  // NOI18N
    } else {
        cellRefByHeaderButton->setEnabled(false);
        cellRefByHeaderLabel->setText("");    // NOI18N
        cellRefByHeader->setText("");        // NOI18N
    }
};

    //@Override
    /*public*/ void TableEditor::bringToFront() {
        if (_editLogixNGFrame != nullptr) {
            _editLogixNGFrame->setVisible(true);
        }
    }

    /**
     * Display reminder to save.
     */
    void TableEditor::showSaveReminder() {
     if (_showReminder) {
      if (InstanceManager::getNullableDefault("UserPreferencesManager") != nullptr)
      {
          ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                  showInfoMessage(tr("Reminder"), // NOI18N
                          tr("<html>Remember to save your %1 information in your Configuration.<br>(choose Store &gt; Store Configuration... from the File menu)</html>").arg(
                                  tr("LogixNGTable")), // NOI18N
                          getClassName(),
                          "remindSaveLogixNG"); // NOI18N
      }
     }
    }

    /**
     * Respond to the Ok button in the Edit NamedTable window.
     * <p>
     * Note: We also get here if the Edit NamedTable window is dismissed, or if the
     * Add button is pressed in the LogixNG Table with an active Edit NamedTable
     * window.
     *
     * @param e The event heard
     */
    /*private*/ void TableEditor::okPressed(JActionEvent* e) {
//        if (checkEditConditionalNG()) {
//            return;
//        }
        // Check if the User Name has been changed
        QString uName = editUserName->text().trimmed();
        if (!(uName ==(_curTable->getUserName()))) {
            // user name has changed - check if already in use
            if (uName.length() > 0) {
                NamedTable* p = (NamedTable*)_tableManager->getByUserName(uName)->self();
                if (p != nullptr) {
                    // NamedTable with this user name already exists
                    log->error("Failure to update NamedTable with Duplicate User Name: " // NOI18N
                            + uName);
                    JOptionPane::showMessageDialog(_editLogixNGFrame,
                            tr("Error6"),
                            tr("Error"), // NOI18N
                            JOptionPane::ERROR_MESSAGE);
                    return;
                }
            }
            // user name is unique, change it
            // user name is unique, change it
            tableData.clear();
            tableData.insert("chgUname", uName);  // NOI18N
            fireEditorEvent();
        }
        if ( qobject_cast<DefaultCsvNamedTable*>(_curTable)) {
            QString csvFileName = editCsvTableName->text().trimmed();

            try {
                // NamedTable does not exist, create a new NamedTable
                AbstractNamedTable::loadTableFromCSV_File(
                        "IQT1",     // Arbitrary LogixNG table name
//                        InstanceManager.getDefault(NamedTableManager.class).getAutoSystemName(),
                        nullptr, csvFileName, false);
            } catch (FileNotFoundException* ex) {
                log->error("Cannot load table due since the file is not found", ex);
                JOptionPane::showMessageDialog(_editLogixNGFrame,
                        tr("File not found: %1").arg(csvFileName),
                        tr("Error"), // NOI18N
                        JOptionPane::ERROR_MESSAGE);
                return;
            } catch (IOException* ex) {
                log->error("Cannot load table due to I/O error", ex);
                JOptionPane::showMessageDialog(_editLogixNGFrame,
                        ex->getLocalizedMessage(),
                        tr("Error"), // NOI18N
                        JOptionPane::ERROR_MESSAGE);
                return;
            } catch (RuntimeException* ex) {
                log->error("Cannot load table due to an error", ex);
                JOptionPane::showMessageDialog(_editLogixNGFrame,
                        ex->getLocalizedMessage(),
                        tr("Error"), // NOI18N
                        JOptionPane::ERROR_MESSAGE);
                return;
            }

            ((DefaultCsvNamedTable*)_curTable)->setFileName(csvFileName);
        }
        // complete update and activate NamedTable
        finishDone();
    }

    void TableEditor::finishDone() {
        showSaveReminder();
        _inEditMode = false;
        if (_editLogixNGFrame != nullptr) {
            _editLogixNGFrame->setVisible(false);
            _editLogixNGFrame->dispose();
            _editLogixNGFrame = nullptr;
        }
        tableData.clear();
        tableData.insert("Finish", _curTable->getSystemName());   // NOI18N
        fireEditorEvent();
    }

    /**
     * Respond to the Delete button in the Edit NamedTable window.
     */
    void TableEditor::deletePressed() {
/*
        if (!checkConditionalNGReferences(_curLogixNG.getSystemName())) {
            return;
        }
*/
        _showReminder = true;
        tableData.clear();
        tableData.insert("Delete", _curTable->getSystemName());   // NOI18N
        fireEditorEvent();
        finishDone();
    }

    // ------------ Table Models ------------

    /**
     * Table model for Tables in the Edit NamedTable pane.
     */
//    /*public*/ /*final*/ class TableTableModel extends AbstractTableModel {

        //@Override
        int TableTableModel::columnCount(const QModelIndex &parent) const {
            return editor->_curTable->numColumns();
        }

        //@Override
        int TableTableModel::rowCount(const QModelIndex &parent) const {
            return editor->_curTable->numRows();
        }

        //@Override
        QVariant TableTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
         int col = section;
         if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
         {
            QVariant data = editor->_curTable->getCell(0, col+1);
            return data != QVariant() ? data.toString() : "<null>";
         }
         return AbstractTableModel::headerData(section, orientation, role);
        }

        //@Override
        QVariant TableTableModel::data(const QModelIndex &index, int role) const {
         if(role == Qt::DisplayRole)
            return editor->_curTable->getCell(index.row()+1, index.column()+1);
         return AbstractTableModel::data(index, role);
        }
//    }

//    /*private*/ class RowHeaderListModel : public AbstractListModel/*<Object>*/ {
//          Q_OBJECT
//         public:
        //@Override
        /*public*/ int RowHeaderListModel::getSize() const{
            return editor->_curTable->numRows();
        }

        //@Override
        /*public*/ QVariant RowHeaderListModel::getElementAt(int index) const{
            // Ensure the header has at least five characters and ensure
            // there are at least two spaces at the end since the last letter
            // doesn't fully fit at the row.
            QVariant data = editor->_curTable->getCell(index+1, 0);
            QString padding = "  ";     // Two spaces
            QString str = data != QVariant() ? data.toString()+(padding) : padding;
            return str.length() < 5 ? str +QString("     ").mid(0, 7) : str;
        }
//    }

//    /*private*/ static final class RowHeaderRenderer extends JLabel implements ListCellRenderer<Object> {

       RowHeaderRenderer::RowHeaderRenderer(JTable* table) {
#if 0 // TODOL
            JTableHeader* header = table->getTableHeader();
            setOpaque(true);
            setBorder(UIManager.getBorder("TableHeader.cellBorder"));
            setHorizontalAlignment(CENTER);
            setForeground(header.getForeground());
            setBackground(header.getBackground());
            setFont(header.getFont());
#endif
        }

        //@Override
        /*public*/ QWidget* RowHeaderRenderer::getListCellRendererComponent(JList* list, QVariant value,
                int index, bool isSelected, bool cellHasFocus) {
            setText((value == QVariant()) ? "" : value.toString());
            return this;
        }
//    }

    /*protected*/ QString TableEditor::getClassName() {
        return /*TableEditor.class.getName()*/"jmri.jmrit.logixng.tools.TableEditor";
    }


    // ------------ NamedTable Notifications ------------
    // The Table views support some direct changes to the parent logix.
    // This custom event is used to notify the parent NamedTable that changes are requested.
    // When the event occurs, the parent NamedTable can retrieve the necessary information
    // to carry out the actions.
    //
    // 1) Notify the calling NamedTable that the NamedTable user name has been changed.
    // 2) Notify the calling NamedTable that the table view is closing
    // 3) Notify the calling NamedTable that it is to be deleted
    /**
     * Create a custom listener event.
     */
    /*public*/ /*interface*/class  TableEventListener : public EventListener {
     public:
        virtual void tableEventOccurred()=0;
    };



    /**
     * Add a listener.
     *
     * @param listener The recipient
     */
    //@Override
    /*public*/ void TableEditor::addEditorEventListener(EditorEventListener* listener) {
        listenerList.append(listener);
    }

    /**
     * Remove a listener -- not used.
     *
     * @param listener The recipient
     */
    //@Override
    /*public*/ void TableEditor::removeEditorEventListener(EditorEventListener* listener) {
        listenerList.removeOne(listener);
    }

    /**
     * Notify the listeners to check for new data.
     */
    /*private*/ void TableEditor::fireEditorEvent() {
        for (EditorEventListener* l : listenerList) {
            l->editorEventOccurred(tableData);
        }
    }


    /*private*/ /*final*/ /*static*/ Logger* TableEditor::log = LoggerFactory::getLogger("TableEditor");
