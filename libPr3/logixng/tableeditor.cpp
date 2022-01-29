#include "tableeditor.h"
#include "instancemanager.h"
#include "loggerfactory.h"

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
    /*public*/ TableEditor::TableEditor(BeanTableDataModel/*<NamedTable>*/* m, QString sName, QObject* parent) : AbstractLogixNGEditor(parent) {
        _tableManager = (NamedTableManager*)InstanceManager::getDefault("NamedTableManager");
        _curTable = _tableManager->getBySystemName(sName);
        makeEditTableWindow();
    }

// ------------ Methods for Edit NamedTable Pane ------------

    /*private*/ JButton* TableEditor::createFileChooser() {
        JButton* selectFileButton = new JButton("..."); // "File" replaced by ...
        selectFileButton->setMaximumSize(selectFileButton->sizeHint());
        selectFileButton.setToolTipText(Bundle.getMessage("TableEdit_FileButtonHint"));  // NOI18N
        selectFileButton.addActionListener((ActionEvent e) -> {
            JFileChooser csvFileChooser = new JFileChooser(FileUtil.getUserFilesPath());
            csvFileChooser.setFileFilter(new FileNameExtensionFilter("CSV files", "csv", "txt")); // NOI18N
            csvFileChooser.rescanCurrentDirectory();
            int retVal = csvFileChooser.showOpenDialog(null);
            // handle selection or cancel
            if (retVal == JFileChooser.APPROVE_OPTION) {
                // set selected file location
                try {
                    editCsvTableName.setText(FileUtil.getPortableFilename(csvFileChooser.getSelectedFile().getCanonicalPath()));
                } catch (java.io.IOException ex) {
                    log.error("exception setting file location: {}", ex);  // NOI18N
                    editCsvTableName.setText("");
                }
            }
        });
        return selectFileButton;
    }


    /**
     * Create and/or initialize the Edit NamedTable pane.
     */
    /*private*/ void TableEditor::makeEditTableWindow() {
        editUserName.setText(_curTable.getUserName());
        // clear conditional table if needed
        if (tableTableModel != null) {
            tableTableModel.fireTableStructureChanged();
        }
        _inEditMode = true;
        if (_editLogixNGFrame == null) {
            if (_curTable.getUserName() != null) {
                _editLogixNGFrame = new JmriJFrame(
                        Bundle.getMessage("TitleEditLogixNG2",
                                _curTable.getSystemName(),   // NOI18N
                                _curTable.getUserName()),    // NOI18N
                        false,
                        false);
            } else {
                _editLogixNGFrame = new JmriJFrame(
                        Bundle.getMessage("TitleEditLogixNG", _curTable.getSystemName()),  // NOI18N
                        false,
                        false);
            }
            _editLogixNGFrame.addHelpMenu(
                    "package.jmri.jmrit.logixng.LogixNGTableTableEditor", true);  // NOI18N
            _editLogixNGFrame.setLocation(100, 30);
            Container contentPane = _editLogixNGFrame.getContentPane();
            contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
            JPanel panel1 = new JPanel();
            panel1.setLayout(new FlowLayout());
            JLabel systemNameLabel = new JLabel(Bundle.getMessage("ColumnSystemName") + ":");  // NOI18N
            panel1.add(systemNameLabel);
            JLabel fixedSystemName = new JLabel(_curTable.getSystemName());
            panel1.add(fixedSystemName);
            contentPane.add(panel1);
            JPanel panel2 = new JPanel();
            panel2.setLayout(new FlowLayout());
            JLabel userNameLabel = new JLabel(Bundle.getMessage("ColumnUserName") + ":");  // NOI18N
            panel2.add(userNameLabel);
            panel2.add(editUserName);
            editUserName.setToolTipText(Bundle.getMessage("LogixNGUserNameHint2"));  // NOI18N
            contentPane.add(panel2);

            boolean isCsvTable = _curTable instanceof DefaultCsvNamedTable;

            JPanel panel3 = new JPanel();
            panel3.setLayout(new FlowLayout());
            JLabel tableTypeLabel = new JLabel(Bundle.getMessage("TableEditor_TableType") + ": ");  // NOI18N
            panel3.add(tableTypeLabel);
            panel3.add(new JLabel(
                    isCsvTable
                            ? Bundle.getMessage("TableEditor_CsvFile")
                            : Bundle.getMessage("TableEditor_UnknownTableType")));
            contentPane.add(panel3);

            if (isCsvTable) {
                JPanel panel4 = new JPanel();
                panel4.setLayout(new FlowLayout());
                JLabel tableFileNameLabel = new JLabel(Bundle.getMessage("TableEditor_FileName") + ": ");  // NOI18N
                panel4.add(tableFileNameLabel);
//                panel4.add(new JLabel(((DefaultCsvNamedTable)_curTable).getFileName()));
                editCsvTableName.setText(((DefaultCsvNamedTable)_curTable).getFileName());
                panel4.add(editCsvTableName);
//                editCsvTableName.setToolTipText(Bundle.getMessage("LogixNGUserNameHint2"));  // NOI18N
                panel4.add(createFileChooser());
                contentPane.add(panel4);
            }


            // add table of Tables
            JPanel pctSpace = new JPanel();
            pctSpace.setLayout(new FlowLayout());
            pctSpace.add(new JLabel("   "));
            contentPane.add(pctSpace);
            JPanel pTitle = new JPanel();
            pTitle.setLayout(new FlowLayout());
//            pTitle.add(new JLabel(Bundle.getMessage("ConditionalNGTableTitle")));  // NOI18N
            contentPane.add(pTitle);
            // initialize table of conditionals
            tableTableModel = new TableTableModel();
            JTable tableTable = new JTable(tableTableModel);
            tableTable.setCellSelectionEnabled(true);
            tableTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
            tableTable.setAutoResizeMode( JTable.AUTO_RESIZE_OFF );
            tableTable.getTableHeader().setReorderingAllowed(false);

            JButton cellRefByIndexButton = new JButton(Bundle.getMessage("TableEditor_CopyToClipboard"));  // NOI18N
            JLabel cellRefByIndexLabel = new JLabel();  // NOI18N
            JTextField cellRefByIndex = new JTextField();
            cellRefByIndex.setEditable(false);
            cellRefByIndexButton.setEnabled(false);

            JButton cellRefByHeaderButton = new JButton(Bundle.getMessage("TableEditor_CopyToClipboard"));  // NOI18N
            JLabel cellRefByHeaderLabel = new JLabel();  // NOI18N
            JTextField cellRefByHeader = new JTextField();
            cellRefByHeader.setEditable(false);
            cellRefByHeaderButton.setEnabled(false);

            java.awt.datatransfer.Clipboard clipboard =
                    Toolkit.getDefaultToolkit().getSystemClipboard();

            cellRefByIndexButton.addActionListener(
                    (evt) -> { clipboard.setContents(new StringSelection(cellRefByIndexLabel.getText()), null);});

            cellRefByHeaderButton.addActionListener(
                    (evt) -> { clipboard.setContents(new StringSelection(cellRefByHeaderLabel.getText()), null);});

            ListSelectionListener selectCellListener = (evt) -> {
                String refByIndex = String.format("{%s[%d,%d]}", _curTable.getDisplayName(), tableTable.getSelectedRow()+1, tableTable.getSelectedColumn()+1);
                cellRefByIndexLabel.setText(refByIndex);  // NOI18N
                cellRefByIndex.setText(ReferenceUtil.getReference(symbolTable, refByIndex));  // NOI18N
                cellRefByIndexButton.setEnabled(true);

                Object rowHeaderObj = _curTable.getCell(tableTable.getSelectedRow()+1, 0);
                Object columnHeaderObj = _curTable.getCell(0, tableTable.getSelectedColumn()+1);
                String rowHeader = rowHeaderObj != null ? rowHeaderObj.toString() : "";
                String columnHeader = columnHeaderObj != null ? columnHeaderObj.toString() : "";
                if (!rowHeader.isEmpty() && !columnHeader.isEmpty()) {
                    cellRefByHeaderButton.setEnabled(true);
                    String refByHeader = String.format("{%s[%s,%s]}", _curTable.getDisplayName(), _curTable.getCell(tableTable.getSelectedRow()+1,0), _curTable.getCell(0,tableTable.getSelectedColumn()+1));
                    cellRefByHeaderLabel.setText(refByHeader);  // NOI18N
                    cellRefByHeader.setText(ReferenceUtil.getReference(symbolTable, refByIndex));  // NOI18N
                } else {
                    cellRefByHeaderButton.setEnabled(false);
                    cellRefByHeaderLabel.setText("");    // NOI18N
                    cellRefByHeader.setText("");        // NOI18N
                }
            };
            tableTable.getSelectionModel().addListSelectionListener(selectCellListener);
            tableTable.getColumnModel().getSelectionModel().addListSelectionListener(selectCellListener);

            ListModel<Object> lm = new RowHeaderListModel();

            JList<Object> rowHeader = new JList<>(lm);
            rowHeader.setFixedCellHeight(
                    tableTable.getRowHeight()
//                    tableTable.getRowHeight() + tableTable.getRowMargin()
//                    + table.getIntercellSpacing().height
            );
            rowHeader.setCellRenderer(new RowHeaderRenderer(tableTable));

            JScrollPane tableTableScrollPane = new JScrollPane(tableTable);
            tableTableScrollPane.setRowHeaderView(rowHeader);
            Dimension dim = tableTable.getPreferredSize();
            dim.height = 450;
            tableTableScrollPane.getViewport().setPreferredSize(dim);
            contentPane.add(tableTableScrollPane);

            JPanel panel4 = new JPanel();
            panel4.setLayout(new FlowLayout());
            panel4.add(cellRefByIndexButton);
            panel4.add(cellRefByIndexLabel);
            panel4.add(cellRefByIndex);
            contentPane.add(panel4);

            JPanel panel5 = new JPanel();
            panel5.setLayout(new FlowLayout());
            panel5.add(cellRefByHeaderButton);
            panel5.add(cellRefByHeaderLabel);
            panel5.add(cellRefByHeader);
            contentPane.add(panel5);

            // add buttons at bottom of window
            JPanel panel6 = new JPanel();
            panel6.setLayout(new FlowLayout());
            // Bottom Buttons - Cancel NamedTable
            JButton cancelButton = new JButton(Bundle.getMessage("ButtonCancel"));  // NOI18N
            panel6.add(cancelButton);
            cancelButton.addActionListener((e) -> {
                finishDone();
            });
//            done.setToolTipText(Bundle.getMessage("CancelButtonHint"));  // NOI18N
            // Bottom Buttons - Ok NamedTable
            JButton okButton = new JButton(Bundle.getMessage("ButtonOK"));  // NOI18N
            panel6.add(okButton);
            okButton.addActionListener((e) -> {
                okPressed(e);
            });
//            done.setToolTipText(Bundle.getMessage("OkButtonHint"));  // NOI18N
            // Delete NamedTable
            JButton delete = new JButton(Bundle.getMessage("ButtonDelete"));  // NOI18N
            panel6.add(delete);
            delete.addActionListener((e) -> {
                deletePressed();
            });
            delete.setToolTipText(Bundle.getMessage("DeleteLogixNGButtonHint"));  // NOI18N
            contentPane.add(panel6);
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
            if (InstanceManager.getNullableDefault(jmri.UserPreferencesManager.class) != null) {
                InstanceManager.getDefault(jmri.UserPreferencesManager.class).
                        showInfoMessage(Bundle.getMessage("ReminderTitle"), // NOI18N
                                Bundle.getMessage("ReminderSaveString", // NOI18N
                                        Bundle.getMessage("MenuItemLogixNGTable")), // NOI18N
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
        QString uName = editUserName.text().trimmed();
        if (!(uName.equals(_curTable.getUserName()))) {
            // user name has changed - check if already in use
            if (uName.length() > 0) {
                NamedTable p = _tableManager.getByUserName(uName);
                if (p != null) {
                    // NamedTable with this user name already exists
                    log.error("Failure to update NamedTable with Duplicate User Name: " // NOI18N
                            + uName);
                    JOptionPane.showMessageDialog(_editLogixNGFrame,
                            Bundle.getMessage("Error6"),
                            Bundle.getMessage("ErrorTitle"), // NOI18N
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }
            }
            // user name is unique, change it
            // user name is unique, change it
            tableData.clear();
            tableData.put("chgUname", uName);  // NOI18N
            fireEditorEvent();
        }
        if (_curTable instanceof DefaultCsvNamedTable) {
            String csvFileName = editCsvTableName.getText().trim();

            try {
                // NamedTable does not exist, create a new NamedTable
                AbstractNamedTable.loadTableFromCSV_File(
                        "IQT1",     // Arbitrary LogixNG table name
//                        InstanceManager.getDefault(NamedTableManager.class).getAutoSystemName(),
                        null, csvFileName, false);
            } catch (java.nio.file.NoSuchFileException ex) {
                log.error("Cannot load table due since the file is not found", ex);
                JOptionPane.showMessageDialog(_editLogixNGFrame,
                        Bundle.getMessage("TableEditor_Error_FileNotFound", csvFileName),
                        Bundle.getMessage("ErrorTitle"), // NOI18N
                        JOptionPane.ERROR_MESSAGE);
                return;
            } catch (IOException ex) {
                log.error("Cannot load table due to I/O error", ex);
                JOptionPane.showMessageDialog(_editLogixNGFrame,
                        ex.getLocalizedMessage(),
                        Bundle.getMessage("ErrorTitle"), // NOI18N
                        JOptionPane.ERROR_MESSAGE);
                return;
            } catch (RuntimeException ex) {
                log.error("Cannot load table due to an error", ex);
                JOptionPane.showMessageDialog(_editLogixNGFrame,
                        ex.getLocalizedMessage(),
                        Bundle.getMessage("ErrorTitle"), // NOI18N
                        JOptionPane.ERROR_MESSAGE);
                return;
            }

            ((DefaultCsvNamedTable)_curTable).setFileName(csvFileName);
        }
        // complete update and activate NamedTable
        finishDone();
    }

    void TableEditor::finishDone() {
        showSaveReminder();
        _inEditMode = false;
        if (_editLogixNGFrame != null) {
            _editLogixNGFrame.setVisible(false);
            _editLogixNGFrame.dispose();
            _editLogixNGFrame = null;
        }
        tableData.clear();
        tableData.put("Finish", _curTable.getSystemName());   // NOI18N
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
        tableData->clear();
        tableData->insert("Delete", _curTable.getSystemName());   // NOI18N
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
            return _curTable->numColumns();
        }

        //@Override
        int TableTableModel::rowCount(const QModelIndex &parent) const {
            return _curTable->numRows();
        }

        //@Override
        QVariant TableTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
         int col = section;
         if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
         {
            QVariant data = _curTable->getCell(0, col+1);
            return data != QVariant() ? data.toString() : "<null>";
         }
         return AbstractTableModel::headerData(section, orientation, role);
        }

        //@Override
        QVariant TableTableModel::data(const QModelIndex &index, int role) const {
         if(role == Qt::DisplayRole)
            return _curTable->getCell(index.row()+1, index.column()+1);
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
            QVariant data = _curTable.getCell(index+1, 0);
            QString padding = "  ";     // Two spaces
            QString str = data != QVariant() ? data.toString().concat(padding) : padding;
            return str.length() < 5 ? str.concat("     ").mid(0, 7) : str;
        }
//    }

//    /*private*/ static final class RowHeaderRenderer extends JLabel implements ListCellRenderer<Object> {

       RowHeaderRenderer::RowHeaderRenderer(JTable* table) {
            JTableHeader* header = table->getTableHeader();
            setOpaque(true);
            setBorder(UIManager.getBorder("TableHeader.cellBorder"));
            setHorizontalAlignment(CENTER);
            setForeground(header.getForeground());
            setBackground(header.getBackground());
            setFont(header.getFont());
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
