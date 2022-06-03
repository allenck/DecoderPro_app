#include "logixngeditor.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultlogixngmanager.h"
#include "jtable.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "borderfactory.h"
#include "jmriuserpreferencesmanager.h"
#include "defaultlogixng.h"
#include "joptionpane.h"
#include "defaultconditionalngmanager.h"
#include "atomicboolean.h"
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include "conditionalngeditor.h"
#include "conditionalngdebugger.h"
#include "defaultlogixngpreferences.h"
#include "logixng_thread.h"
#include "defaultfemaledigitalactionsocket.h"
#include "jeditorpane.h"
#include <QScrollArea>
#include "pushbuttondelegate.h"
#include "editthreadsdialog.h"

/**
 * Editor for LogixNG
 *
 * @author Dave Duchamp Copyright (C) 2007  (ConditionalListEdit)
 * @author Pete Cressman Copyright (C) 2009, 2010, 2011  (ConditionalListEdit)
 * @author Matthew Harris copyright (c) 2009  (ConditionalListEdit)
 * @author Dave Sand copyright (c) 2017  (ConditionalListEdit)
 * @author Daniel Bergqvist (c) 2019
 * @author Dave Sand (c) 2021
 */
///*public*/  /*final*/ class LogixNGEditor implements AbstractLogixNGEditor<LogixNG> {



    /**
     * Create a new ConditionalNG List View editor.
     *
     * @param f the bean table frame
     * @param m the bean table model
     * @param sName name of the LogixNG being edited
     */
    /*public*/  LogixNGEditor::LogixNGEditor(BeanTableFrame/*<LogixNG>*/* f, BeanTableDataModel/*<LogixNG>*/* m, QString sName, QObject* parent) : QObject(parent) {
        setObjectName("LogixNGEditor");
        this->beanTableFrame = f;
        this->beanTableDataModel = m;
        _logixNG_Manager = (DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");
        _curLogixNG =(DefaultLogixNG*) _logixNG_Manager->getBySystemName(sName)->self();
//       beanTableDataModel->updateNameList();
//       beanTableDataModel->fireTableDataChanged();
        beanTableDataModel->init();
        makeEditLogixNGWindow();
    }

#if 1
    // ------------ Methods for Edit LogixNG Pane ------------

    /**
     * Create and/or initialize the Edit LogixNG pane.
     */
    void LogixNGEditor::makeEditLogixNGWindow() {
        editUserName->setText(_curLogixNG->getUserName());
        // clear conditional table if needed
        if (_conditionalNGTableModel != nullptr) {
            _conditionalNGTableModel->fireTableStructureChanged();
        }
        _inEditMode = true;
        if (_editLogixNGFrame == nullptr) {
            if (_curLogixNG->getUserName() != "") {
                _editLogixNGFrame = new JmriJFrame(
                        tr("Edit LogixNG %1 - %2").arg(
                                _curLogixNG->getSystemName(),   // NOI18N
                                _curLogixNG->getUserName()),    // NOI18N
                        false,
                        false);
            } else {
                _editLogixNGFrame = new JmriJFrame(
                        tr("Edit LogixNG %1").arg(_curLogixNG->getSystemName()),  // NOI18N
                        false,
                        false);
            }
            _editLogixNGFrame->addHelpMenu(
                    "package.jmri.jmrit.logixng.LogixNGTableEditor", true);  // NOI18N
            _editLogixNGFrame->setLocation(100, 30);
            QWidget* contentPane = _editLogixNGFrame->getContentPane();
            contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));
            JPanel* panel1 = new JPanel();
            panel1->setLayout(new FlowLayout());
            JLabel* systemNameLabel = new JLabel(tr("SystemName") + ":");  // NOI18N
            panel1->layout()->addWidget(systemNameLabel);
            JLabel* fixedSystemName = new JLabel(_curLogixNG->getSystemName());
            panel1->layout()->addWidget(fixedSystemName);
            contentPane->layout()->addWidget(panel1);
            JPanel* panel2 = new JPanel();
            panel2->setLayout(new FlowLayout());
            JLabel* userNameLabel = new JLabel(tr("UserName") + ":");  // NOI18N
            panel2->layout()->addWidget(userNameLabel);
            panel2->layout()->addWidget(editUserName);
            editUserName->setToolTip(tr("Enter new user name for LogixNG, e.g. Signal 2 Control"));  // NOI18N
            contentPane->layout()->addWidget(panel2);
            // add table of ConditionalNGs
            JPanel* pctSpace = new JPanel();
            pctSpace->setLayout(new FlowLayout());
            pctSpace->layout()->addWidget(new JLabel("   "));
            contentPane->layout()->addWidget(pctSpace);
            JPanel* pTitle = new JPanel();
            pTitle->setLayout(new FlowLayout());
            pTitle->layout()->addWidget(new JLabel(tr("ConditionalNGs (in Order of Calculation)")));  // NOI18N
            contentPane->layout()->addWidget(pTitle);
            // initialize table of conditionals
            _conditionalNGTableModel = new ConditionalNGTableModel(this);
            JTable* conditionalTable = new JTable(_conditionalNGTableModel);
            conditionalTable->setRowSelectionAllowed(false);
            TableColumnModel* conditionalColumnModel = conditionalTable
                    ->getColumnModel();
            TableColumn* sNameColumn = conditionalColumnModel
                    ->getColumn(ConditionalNGTableModel::SNAME_COLUMN);
            sNameColumn->setResizable(true);
            sNameColumn->setMinWidth(100);
            sNameColumn->setPreferredWidth(130);
            TableColumn* uNameColumn = conditionalColumnModel
                    ->getColumn(ConditionalNGTableModel::UNAME_COLUMN);
            uNameColumn->setResizable(true);
            uNameColumn->setMinWidth(210);
            uNameColumn->setPreferredWidth(260);
            TableColumn* threadColumn = conditionalColumnModel
                    ->getColumn(ConditionalNGTableModel::THREAD_COLUMN);
            threadColumn->setResizable(true);
            threadColumn->setMinWidth(210);
            threadColumn->setPreferredWidth(260);
            TableColumn* buttonColumn = conditionalColumnModel
                    ->getColumn(ConditionalNGTableModel::BUTTON_COLUMN);
            TableColumn* buttonDeleteColumn = conditionalColumnModel
                    ->getColumn(ConditionalNGTableModel::BUTTON_DELETE_COLUMN);
            TableColumn* buttonEditThreadsColumn = conditionalColumnModel
                    ->getColumn(ConditionalNGTableModel::BUTTON_EDIT_THREADS_COLUMN);

            // install button renderer and editor
            ButtonRenderer* buttonRenderer = new ButtonRenderer();
            conditionalTable->setDefaultRenderer("JButton", buttonRenderer);
//            TableCellEditor* buttonEditor = new ButtonEditor(new JButton());
//            conditionalTable->setDefaultEditor("JButton", buttonEditor);
            JButton* testButton = new JButton("XXXXXX");  // NOI18N
            JButton* testButton2 = new JButton("XXXXXXXXXX");  // NOI18N
            conditionalTable->setRowHeight(testButton->sizeHint().height());
            buttonColumn->setMinWidth(testButton->sizeHint().width());
            buttonColumn->setMaxWidth(testButton->sizeHint().width());
            buttonColumn->setResizable(false);
            buttonDeleteColumn->setMinWidth(testButton->sizeHint().width());
            buttonDeleteColumn->setMaxWidth(testButton->sizeHint().width());
            buttonDeleteColumn->setResizable(false);
            buttonEditThreadsColumn->setMinWidth(testButton2->sizeHint().width());
            buttonEditThreadsColumn->setMaxWidth(testButton2->sizeHint().width());
            buttonEditThreadsColumn->setResizable(false);

            conditionalTable->setItemDelegateForColumn(ConditionalNGTableModel::BUTTON_COLUMN, new PushButtonDelegate());
            conditionalTable->setItemDelegateForColumn(ConditionalNGTableModel::BUTTON_DELETE_COLUMN, new PushButtonDelegate());
            conditionalTable->setItemDelegateForColumn(ConditionalNGTableModel::BUTTON_EDIT_THREADS_COLUMN, new PushButtonDelegate());
            conditionalTable->setItemDelegateForColumn(ConditionalNGTableModel::BUTTON_DEBUG_COLUMN, new PushButtonDelegate());
//            JScrollPane conditionalTableScrollPane = new JScrollPane(conditionalTable);
//            Dimension dim = conditionalTable->getPreferredSize();
//            dim.height = 450;
//            conditionalTableScrollPane->getViewport()->setPreferredSize(dim);
            ((QVBoxLayout*)contentPane->layout())->addWidget(/*conditionalTableScrollPane*/conditionalTable,1);

            _showStartupThreadsCheckBox = new JCheckBox(tr("Show startup thread"));
            contentPane->layout()->addWidget(_showStartupThreadsCheckBox);
            connect(_showStartupThreadsCheckBox, &JCheckBox::clicked, [=] {
                _conditionalNGTableModel->setShowStartupThreads(
                        _showStartupThreadsCheckBox->isSelected());
            });

            // add message area between table and buttons
            JPanel* panel4 = new JPanel();
            panel4->setLayout(new QVBoxLayout());//panel4, BoxLayout.Y_AXIS));
            JPanel* panel41 = new JPanel();
            panel41->setLayout(new FlowLayout());
            panel41->layout()->addWidget(status);
            panel4->layout()->addWidget(panel41);
            JPanel* panel42 = new JPanel();
            panel42->setLayout(new FlowLayout());
            // ConditionalNG panel buttons - New ConditionalNG
            JButton* newConditionalNGButton = new JButton(tr("New ConditionalNG"));  // NOI18N
            panel42->layout()->addWidget(newConditionalNGButton);
            connect(newConditionalNGButton, &JButton::clicked, [=] {
                newConditionalNGPressed(/*e*/);
            });
            newConditionalNGButton->setToolTip(tr("Press for window to create a new ConditionalNG"));  // NOI18N
            // ConditionalNG panel buttons - Reorder
            JButton* reorderButton = new JButton(tr("Reorder"));  // NOI18N
            panel42->layout()->addWidget(reorderButton);
            connect(reorderButton, &JButton::clicked, [=] {
                reorderPressed(/*e*/);
            });
            reorderButton->setToolTip(tr("Press then click in right column in order desired (disabled while type is Mixed)"));  // NOI18N
            // ConditionalNG panel buttons - Calculate
            JButton* executeButton = new JButton(tr("Execute"));  // NOI18N
            panel42->layout()->addWidget(executeButton);
            connect(executeButton, &JButton::clicked, [=] {
                executePressed(/*e*/);
            });
            executeButton->setToolTip(tr("Press to execute all the ConditionalNGs"));  // NOI18N
            panel4->layout()->addWidget(panel42);
            Border* panel4Border = BorderFactory::createEtchedBorder();
            panel4->setBorder(panel4Border);
            contentPane->layout()->addWidget(panel4);
            // add buttons at bottom of window
            JPanel* panel5 = new JPanel();
            panel5->setLayout(new FlowLayout());
            // Bottom Buttons - Done LogixNG
            JButton* done = new JButton(tr("Done"));  // NOI18N
            panel5->layout()->addWidget(done);
            connect(done, &JButton::clicked, [=] {
                donePressed(/*e*/);
            });
            done->setToolTip(tr("Press to save any user name changes and return to Logix Table"));  // NOI18N
            // Delete LogixNG
            JButton* _delete = new JButton(tr("Delete"));  // NOI18N
            panel5->layout()->addWidget(_delete);
            connect(_delete, &JButton::clicked, [=] {
                deletePressed();
            });
            _delete->setToolTip(tr("Press to delete this LogixNG and all its ConditionalNGs"));  // NOI18N
            contentPane->layout()->addWidget(panel5);
        }

//        _editLogixNGFrame.addWindowListener(new event.WindowAdapter() {
//            //@Override
//            /*public*/  void windowClosing(event.WindowEvent e) {
//                if (_inEditMode) {
//                    donePressed(null);
//                } else {
//                    finishDone();
//                }
//            }
//        });
        _editLogixNGFrame->addWindowListener(new LogixNGEditor_windowListener(this));

        _editLogixNGFrame->pack();
        _editLogixNGFrame->setVisible(true);
    }

    //@Override
    /*public*/  void LogixNGEditor::bringToFront() {
        if (_editLogixNGFrame != nullptr) {
            _editLogixNGFrame->setVisible(true);
        }
    }

    /**
     * Display reminder to save.
     */
    void LogixNGEditor::showSaveReminder() {
        if (_showReminder) {
            if (InstanceManager::getNullableDefault("UserPreferencesManager") != nullptr) {
                ((JmriUserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                        showInfoMessage(tr("Reminder"), // NOI18N
                                tr("html>Remember to save your %1 information in your Configuration.<br>(choose Store &gt; Store Configuration... from the File menu)</html>").arg(// NOI18N
                                        tr("LogixNGs")), // NOI18N
                                getClassName(),
                                "remindSaveLogixNG"); // NOI18N
            }
        }
    }

    /**
     * Respond to the Reorder Button in the Edit LogixNG pane.
     *
     * @param e The event heard
     */
    void LogixNGEditor::reorderPressed(JActionEvent* e) {
        if (checkEditConditionalNG()) {
            return;
        }
        // Check if reorder is reasonable
        _showReminder = true;
        _nextInOrder = 0;
        _inReorderMode = true;
        status->setText(tr("Please press First, then Next, Next, ... in desired order."));  // NOI18N
        _conditionalNGTableModel->fireTableDataChanged();
    }

    /**
     * Respond to the First/Next (Delete) Button in the Edit LogixNG window.
     *
     * @param row index of the row to put as next in line (instead of the one
     *            that was supposed to be next)
     */
    void LogixNGEditor::swapConditionalNG(int row) {
        _curLogixNG->swapConditionalNG(_nextInOrder, row);
        _nextInOrder++;
        if (_nextInOrder >= _numConditionalNGs) {
            _inReorderMode = false;
        }
        //status->setText("");
        _conditionalNGTableModel->fireTableDataChanged();
    }

    /**
     * Responds to the Execute Button in the Edit LogixNG window.
     *
     * @param e The event heard
     */
    void LogixNGEditor::executePressed(JActionEvent* e) {
        if (checkEditConditionalNG()) {
            return;
        }
        // are there ConditionalNGs to execute?
        if (_numConditionalNGs > 0) {
            // There are conditionals to calculate
            for (int i = 0; i < _numConditionalNGs; i++) {
                ConditionalNG* c = _curLogixNG->getConditionalNG(i);
                if (c == nullptr) {
                    log->error("Invalid conditional system name when executing"); // NOI18N
                } else {
                    c->execute();
                }
            }
            // force the table to update
//            conditionalNGTableModel.fireTableDataChanged();
        }
    }

    /**
     * Respond to the Done button in the Edit LogixNG window.
     * <p>
     * Note: We also get here if the Edit LogixNG window is dismissed, or if the
     * Add button is pressed in the Logic Table with an active Edit LogixNG
     * window.
     *
     * @param e The event heard
     */
    void LogixNGEditor::donePressed(JActionEvent* e) {
        if (checkEditConditionalNG()) {
            return;
        }
        // Check if the User Name has been changed
        QString uName = editUserName->text().trimmed();
        if ((uName != (_curLogixNG->getUserName()))) {
            // user name has changed - check if already in use
            if (uName.length() > 0) {
                //LogixNG* p = (DefaultLogixNG*)_logixNG_Manager->getByUserName(uName)->self();
            NamedBean* nb = _logixNG_Manager->getByUserName(uName);
            LogixNG* p = nullptr;
            if(nb)
             p = (DefaultLogixNG*)nb->self();
             if (p != nullptr) {
                    // LogixNG with this user name already exists
                    log->error("Failure to update LogixNG with Duplicate User Name: " // NOI18N
                            + uName);
                    JOptionPane::showMessageDialog(_editLogixNGFrame,
                            tr("New user name is already in use. Cannot update this Logix.\nPlease change user name and try again."),
                            tr("Error"), // NOI18N
                            JOptionPane::ERROR_MESSAGE);
                    return;
                }
            }
            // user name is unique, change it
            // user name is unique, change it
            logixNG_Data.clear();
            logixNG_Data.insert("chgUname", uName);  // NOI18N
            fireEditorEvent();
        }
        // complete update and activate LogixNG
        finishDone();
    }

    void LogixNGEditor::finishDone() {
        showSaveReminder();
        _inEditMode = false;
        if (_editLogixNGFrame != nullptr) {
            _editLogixNGFrame->setVisible(false);
            _editLogixNGFrame->dispose();
            _editLogixNGFrame = nullptr;
        }
        logixNG_Data.clear();
        logixNG_Data.insert("Finish", _curLogixNG->getSystemName());   // NOI18N
        fireEditorEvent();
    }

    /**
     * Respond to the Delete button in the Edit LogixNG window.
     */
    void LogixNGEditor::deletePressed() {
        if (checkEditConditionalNG()) {
            return;
        }

        _showReminder = true;
        logixNG_Data.clear();
        logixNG_Data.insert("Delete", _curLogixNG->getSystemName());   // NOI18N
        fireEditorEvent();
        finishDone();
    }

    /**
     * Respond to the New ConditionalNG Button in Edit LogixNG Window.
     *
     * @param e The event heard
     */
    void LogixNGEditor::newConditionalNGPressed(JActionEvent* e) {
        if (checkEditConditionalNG()) {
            return;
        }

        // make an Add Item Frame
        if (showAddLogixNGFrame()) {
            if (_systemName->text().isEmpty() && _autoSystemName->isSelected()) {
                _systemName->setText(((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->AbstractManager::getAutoSystemName());
            }

            // Create ConditionalNG
            _curConditionalNG = ((DefaultConditionalNGManager*)
                    InstanceManager::getDefault("ConditionalNG_Manager"))
                            ->createConditionalNG(_curLogixNG, _systemName->text(), _addUserName->text());

            if (_curConditionalNG == nullptr) {
                // should never get here unless there is an assignment conflict
                log->error("Failure to create ConditionalNG"); // NOI18N
                return;
            }
            // add to LogixNG at the end of the calculate order
            _conditionalNGTableModel->fireTableRowsInserted(_numConditionalNGs, _numConditionalNGs);
            _conditionalRowNumber = _numConditionalNGs;
            _numConditionalNGs++;
            _showReminder = true;
            makeEditConditionalNGWindow();
        }
    }

    /**
     * Create or edit action/expression dialog.
     */
    /*private*/ bool LogixNGEditor::showAddLogixNGFrame() {

        AtomicBoolean* result = new AtomicBoolean(false);

        JDialog* dialog  = new JDialog(
                _editLogixNGFrame,
                tr("Add ConditionalNG"),
                true);
//        frame.addHelpMenu(
//                "package.jmri.jmrit.logixng.tools.swing.ConditionalNGAddEdit", true);     // NOI18N
        QWidget* contentPanel = dialog->getContentPane();
        contentPanel->setLayout(new QVBoxLayout());//contentPanel, BoxLayout.Y_AXIS));

        JPanel* p;
        p = new JPanel();
//        p->setLayout(new FlowLayout());
        GridBagLayout* pLayout;
        p->setLayout(pLayout = new GridBagLayout());
        GridBagConstraints c = GridBagConstraints();
        c.gridwidth = 1;
        c.gridheight = 1;
        c.gridx = 0;
        c.gridy = 0;
        c.anchor = GridBagConstraints::EAST;
        pLayout->addWidget(_sysNameLabel, c);
        c.gridy = 1;
        pLayout->addWidget(_userNameLabel, c);
        c.gridx = 1;
        c.gridy = 0;
        c.anchor = GridBagConstraints::WEST;
        c.weightx = 1.0;
        c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
        pLayout->addWidget(_systemName, c);
        c.gridy = 1;
        pLayout->addWidget(_addUserName, c);
        c.gridx = 2;
        c.gridy = 1;
        c.anchor = GridBagConstraints::WEST;
        c.weightx = 1.0;
        c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
        c.gridy = 0;
        pLayout->addWidget(_autoSystemName, c);

        _systemName->setText("");
        _systemName->setEnabled(true);
        _addUserName->setText("");

        _addUserName->setToolTip(tr("Enter user name for new LogixNG, e.g. Signal 2 Control"));    // NOI18N
//        _addUserName->setToolTipText("LogixNGUserNameHint");    // NOI18N
        _systemName->setToolTip(tr("Enter system name for new LogixNG, e.g. IQ13"));   // NOI18N
//        _systemName->setToolTipText("LogixNGSystemNameHint");   // NOI18N
        contentPanel->layout()->addWidget(p);
        // set up message
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));
        JPanel* panel31 = new JPanel(new FlowLayout());
//        panel31->setLayout(new FlowLayout());
        JPanel* panel32 = new JPanel(new FlowLayout());
        JLabel* message1 = new JLabel(tr("Please enter system name and user name, then"));  // NOI18N
        panel31->layout()->addWidget(message1);
        JLabel* message2 = new JLabel(tr("click [Create]."));  // NOI18N
        panel32->layout()->addWidget(message2);

        // set up create and cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());

        // Get panel for the item
        panel3->layout()->addWidget(panel31);
        panel3->layout()->addWidget(panel32);
        contentPanel->layout()->addWidget(panel3);

        // Cancel
        JButton* cancel = new JButton(tr("Cancel"));    // NOI18N
        panel5->layout()->addWidget(cancel);
        connect(cancel, &JButton::clicked, [=] {
            dialog->dispose();
        });
//        cancel->setToolTipText(Bundle->getMessage("CancelLogixButtonHint"));      // NOI18N
        cancel->setToolTip("Press to return to Logix Table without any changes");      // NOI18N

        JButton* create = new JButton(tr("Create"));  // NOI18N
        connect(create, &JButton::clicked, [=]{
            JmriUserPreferencesManager* prefMgr = (JmriUserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
            if(prefMgr){
                prefMgr->setCheckboxPreferenceState(systemNameAuto, _autoSystemName->isSelected());
            }
           // });
            result->set(true);
            dialog->dispose();
        });
        create->setToolTip(tr("Press to create"));  // NOI18N

        panel5->layout()->addWidget(create);

//        dialog.addWindowListener(new event.WindowAdapter() {
//            //@Override
//            /*public*/  void windowClosing(event.WindowEvent e) {
//                dialog.dispose();
//            }
//        });

        contentPanel->layout()->addWidget(panel5);

        connect(_autoSystemName, &JCheckBox::clicked, [=]{
            autoSystemName();
        });
//        addLogixNGFrame->setLocationRelativeTo(component);
        dialog->resize(400, 400);
        dialog->pack();
        dialog->setLocationRelativeTo(nullptr);

        _autoSystemName->setSelected(true);
        JmriUserPreferencesManager* prefMgr = (JmriUserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager"); //.ifPresent((prefMgr) -> {
        if(prefMgr)
        {
        _autoSystemName->setSelected(prefMgr->getCheckboxPreferenceState(systemNameAuto, true));
        }//);

        dialog->setVisible(true);
        dialog->exec();

        return result->get();
    }

    /**
     * Enable/disable fields for data entry when user selects to have system
     * name automatically generated.
     */
    void LogixNGEditor::autoSystemName() {
        if (_autoSystemName->isSelected()) {
            _systemName->setEnabled(false);
            _sysNameLabel->setEnabled(false);
        } else {
            _systemName->setEnabled(true);
            _sysNameLabel->setEnabled(true);
        }
    }

    // ============ Edit Conditional Window and Methods ============

    /**
     * Create and/or initialize the Edit Conditional window.
     * <p>
     * Note: you can get here via the New Conditional button
     * (newConditionalPressed) or via an Edit button in the Conditional table of
     * the Edit Logix window.
     */
    void LogixNGEditor::makeEditConditionalNGWindow() {
        // Create a new LogixNG edit view, add the listener.
        _treeEdit = new ConditionalNGEditor(_curConditionalNG);
        _treeEdit->initComponents();
        _treeEdit->setVisible(true);
        _inEditConditionalNGMode = true;
        _editConditionalNGFrame = _treeEdit;
        _editConditionalNGFrame->addHelpMenu(
                "package.jmri.jmrit.logixng.ConditionalNGEditor", true);  // NOI18N

        /*final*/ LogixNGEditor* logixNGEditor = this;
        _treeEdit->addLogixNGEventListener(new LogixNGEventListenerImpl(logixNGEditor));
        _treeEdit->resize(600, 400);
        _treeEdit->pack();
    }

    /**
     * Create and/or initialize the Edit Conditional window.
     * <p>
     * Note: you can get here via the New Conditional button
     * (newConditionalPressed) or via an Edit button in the Conditional table of
     * the Edit Logix window.
     */
    void LogixNGEditor::makeDebugConditionalNGWindow() {
        // Create a new LogixNG edit view, add the listener.
        _debugger = new ConditionalNGDebugger(_curConditionalNG);
        _debugger->initComponents();
        _debugger->setVisible(true);
        _inEditConditionalNGMode = true;
        _editConditionalNGFrame = _debugger;

        /*final*/ LogixNGEditor* logixNGEditor = this;
        _debugger->addLogixNGEventListener(new LogixNG_DebuggerEventListenerImpl(logixNGEditor));
    }

    // ------------ Methods for Edit ConditionalNG Pane ------------

    /**
     * Respond to Edit Button in the ConditionalNG table of the Edit LogixNG Window.
     *
     * @param rx index (row number) of ConditionalNG to be edited
     */
    void LogixNGEditor::editConditionalNGPressed(int rx) {
        if (checkEditConditionalNG()) {
            return;
        }
        // get ConditionalNG to edit
        _curConditionalNG = _curLogixNG->getConditionalNG(rx);
        if (_curConditionalNG == nullptr) {
            log->error("Attempted edit of non-existant conditional.");  // NOI18N
            return;
        }
        _conditionalRowNumber = rx;
        // get action variables
        makeEditConditionalNGWindow();
    }

    /**
     * Respond to Edit Button in the ConditionalNG table of the Edit LogixNG Window.
     *
     * @param rx index (row number) of ConditionalNG to be edited
     */
    void LogixNGEditor::debugConditionalNGPressed(int rx) {
        if (checkEditConditionalNG()) {
            return;
        }
        // get ConditionalNG to edit
        _curConditionalNG = _curLogixNG->getConditionalNG(rx);
        if (_curConditionalNG == nullptr) {
            log->error("Attempted edit of non-existant conditional.");  // NOI18N
            return;
        }
        _conditionalRowNumber = rx;
        // get action variables
        makeDebugConditionalNGWindow();
    }

    /**
     * Check if edit of a conditional is in progress.
     *
     * @return true if this is the case, after showing dialog to user
     */
    /*private*/ bool LogixNGEditor::checkEditConditionalNG() {
        if (_inEditConditionalNGMode) {
            // Already editing a ConditionalNG, ask for completion of that edit
            JOptionPane::showMessageDialog(_editConditionalNGFrame,
                    tr("Edit ConditionalNG(s) %1 in progress. Please complete edit of any ConditionalNGs and try again.").arg(_curConditionalNG->AbstractNamedBean::getSystemName()), // NOI18N
                    tr("Error"), // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            _editConditionalNGFrame->setVisible(true);
            return true;
        }
        return false;
    }

    bool LogixNGEditor::checkConditionalNGUserName(QString uName, LogixNG* logixNG) {
        if ((uName != "") && ((uName != ("")))) {
            for (int i=0; i < logixNG->getNumConditionalNGs(); i++) {
                ConditionalNG* p = logixNG->getConditionalNG(i);
                if (uName == (p->NamedBean::getUserName())) {
                    // ConditionalNG with this user name already exists
                    log->error("Failure to update ConditionalNG with Duplicate User Name: " // NOI18N
                            + uName);
                    JOptionPane::showMessageDialog(_editConditionalNGFrame,
                           tr("New user name is already in use. Cannot update this Conditional.\nPlease change user name and try again."),    // NOI18N
                            tr("Error"), // NOI18N
                            JOptionPane::ERROR_MESSAGE);
                    return false;
                }
            }
        } // else return false;
        return true;
    }

    /**
     * Check form of ConditionalNG systemName.
     *
     * @param sName system name of bean to be checked
     * @return false if sName is empty string or null
     */
    bool LogixNGEditor::checkConditionalNGSystemName(QString sName) {
        if ((sName != "") && ((sName!=("")))) {
            ConditionalNG* p = _curLogixNG->getConditionalNG(sName);
            if (p != nullptr) {
                return false;
            }
        } else {
            return false;
        }
        return true;
    }

    // ------------ Table Models ------------

    /**
     * Table model for ConditionalNGs in the Edit LogixNG pane.
     */
//    /*public*/  /*final*/ class ConditionalNGTableModel extends AbstractTableModel
//            implements PropertyChangeListener {

//        /*private*/ bool _showStartupThreads;


        /*public*/  ConditionalNGTableModel::ConditionalNGTableModel(QObject* parent) : AbstractTableModel(parent){
            //super();
            setObjectName("ConditionalNGTableModel");
            editor = (LogixNGEditor*)parent;
            updateConditionalNGListeners();
        }

        /*synchronized*/ void ConditionalNGTableModel::updateConditionalNGListeners() {
            // first, remove listeners from the individual objects
            ConditionalNG* c;
            editor->_numConditionalNGs = editor->_curLogixNG->getNumConditionalNGs();
            for (int i = 0; i < editor->_numConditionalNGs; i++) {
                // if object has been deleted, it's not here; ignore it
                c = editor->_curLogixNG->getConditionalNG(i);
                if (c != nullptr) {
                    c->NamedBean::removePropertyChangeListener(this);
                }
            }
            // and add them back in
            for (int i = 0; i < editor->_numConditionalNGs; i++) {
                c = editor->_curLogixNG->getConditionalNG(i);
                if (c != nullptr) {
                    c->NamedBean::addPropertyChangeListener(this);
                }
            }
        }

        /*public*/  void ConditionalNGTableModel::setShowStartupThreads(bool showStartupThreads) {
            _showStartupThreads = showStartupThreads;
            fireTableRowsUpdated(0, editor->_curLogixNG->getNumConditionalNGs()-1);
        }

        //@Override
        /*public*/  void ConditionalNGTableModel::propertyChange(PropertyChangeEvent* e) {
            if (e->getPropertyName() == ("length")) {  // NOI18N
                // a new NamedBean is available in the manager
                updateConditionalNGListeners();
                fireTableDataChanged();
            } else if (matchPropertyName(e)) {
                // a value changed.
                fireTableDataChanged();
            }
        }

        /**
         * Check if this property event is announcing a change this table should
         * display.
         * <p>
         * Note that events will come both from the NamedBeans and from the
         * manager.
         *
         * @param e the event heard
         * @return true if a change in State or Appearance was heard
         */
        bool ConditionalNGTableModel::matchPropertyName(PropertyChangeEvent* e) {
            return (e->getPropertyName().contains("UserName") ||      // NOI18N
                    e->getPropertyName().contains("Thread"));  // NOI18N
        }

        //@Override
        /*public*/  /*Class<?>*/QString ConditionalNGTableModel::getColumnClass(int c) const{
            if ((c == BUTTON_COLUMN)
                    || (c == BUTTON_DEBUG_COLUMN)
                    || (c == BUTTON_DELETE_COLUMN)
                    || (c == BUTTON_EDIT_THREADS_COLUMN)) {
                return "JButton";
            }
            return "String";
        }

        //@Override
        /*public*/  int ConditionalNGTableModel::columnCount(const QModelIndex &parent) const {
            return NUM_COLUMNS;
        }

        //@Override
        /*public*/  int ConditionalNGTableModel::rowCount(const QModelIndex &parent) const  {
            return (editor->_numConditionalNGs);
        }

        //@Override
        /*public*/  Qt::ItemFlags ConditionalNGTableModel::flags(const QModelIndex &index) const {
         int c= index.column();
         int r = index.row();
            if (!editor->_inReorderMode) {
                return ((c == UNAME_COLUMN)
                        || (c == BUTTON_COLUMN)
                        || ((c == BUTTON_DEBUG_COLUMN) && ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger())
                        || (c == BUTTON_DELETE_COLUMN)
                        || (c == BUTTON_EDIT_THREADS_COLUMN))?Qt::ItemIsEditable | Qt::ItemIsEnabled : Qt::ItemIsEnabled;
            } else if (c == BUTTON_COLUMN) {
                if (r >= editor->_nextInOrder) {
                    return (Qt::ItemIsEditable | Qt::ItemIsEnabled);
                }
            }
            return (Qt::ItemIsEnabled);
        }

        //@Override
        /*public*/  QVariant ConditionalNGTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
         if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
         {
            switch (section) {
                case SNAME_COLUMN:
                    return tr("SystemName");  // NOI18N
                case UNAME_COLUMN:
                    return tr("UserName");  // NOI18N
                case THREAD_COLUMN:
                    return tr("Thread");  // NOI18N
                case BUTTON_COLUMN:
                    return ""; // no label
                case BUTTON_DEBUG_COLUMN:
                    return ""; // no label
                case BUTTON_DELETE_COLUMN:
                    return ""; // no label
                case BUTTON_EDIT_THREADS_COLUMN:
                    return ""; // no label
                default:
                    throw new IllegalArgumentException("Unknown column");
            }
         }
         return QVariant();
        }

        //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "DB_DUPLICATE_SWITCH_CLAUSES",
        //        justification = "better to keep cases in column order rather than to combine")
        /*public*/  int ConditionalNGTableModel::getPreferredWidth(int col) {
            switch (col) {
                case SNAME_COLUMN:
                    return JTextField(6).getPreferredSize().width();
                case UNAME_COLUMN:
                    return JTextField(17).getPreferredSize().width();
                case THREAD_COLUMN:
                    return JTextField(10).getPreferredSize().width();
                case BUTTON_COLUMN:
                    return JTextField(6).getPreferredSize().width();
                case BUTTON_DEBUG_COLUMN:
                    return JTextField(6).getPreferredSize().width();
                case BUTTON_DELETE_COLUMN:
                    return JTextField(6).getPreferredSize().width();
                case BUTTON_EDIT_THREADS_COLUMN:
                    return JTextField(12).getPreferredSize().width();
                default:
                    throw new IllegalArgumentException("Unknown column");
            }
        }

        //@Override
        /*public*/  QVariant ConditionalNGTableModel::data(const QModelIndex &index, int role) const {
         if(role == Qt::DisplayRole)
         {
          int col = index.column();
          int r = index.row();
            int rx = r;
            if ((rx > editor->_numConditionalNGs) || (editor->_curLogixNG == nullptr)) {
                return QVariant();
            }
            switch (col) {
                case BUTTON_COLUMN:
                    if (!editor->_inReorderMode) {
                        return tr("Edit");  // NOI18N
                    } else if (editor->_nextInOrder == 0) {
                        return tr("First");  // NOI18N
                    } else if (editor->_nextInOrder <= r) {
                        return tr("Next");  // NOI18N
                    } else {
                        return /*Integer.toString*/(rx + 1);
                    }
                case BUTTON_DEBUG_COLUMN:
                    return tr("Debug");  // NOI18N
                case BUTTON_DELETE_COLUMN:
                    return tr("Delete");  // NOI18N
                case BUTTON_EDIT_THREADS_COLUMN:
                    return tr("Edit threads");  // NOI18N
                case SNAME_COLUMN:
                    return editor->_curLogixNG->getConditionalNG(rx)->AbstractNamedBean::getSystemName();
                case UNAME_COLUMN: {
                    //log.debug("ConditionalNGTableModel: {}", _curLogixNG->getConditionalNGByNumberOrder(rx));  // NOI18N
                    DefaultConditionalNG* c = editor->_curLogixNG->getConditionalNG(rx);
                    if (c != nullptr) {
                        return c->AbstractNamedBean::getUserName();
                    }
                    return "";
                }
                case THREAD_COLUMN:
                    if (_showStartupThreads) {
                        return LogixNG_Thread::getThread(
                                editor->_curLogixNG->getConditionalNG(r)->getStartupThreadId())
                                ->getThreadName();
                    } else {
                        return editor->_curLogixNG->getConditionalNG(r)->getCurrentThread()->getThreadName();
                    }
                default:
                    throw new IllegalArgumentException("Unknown column");
            }
         }
         return QVariant();
        }

        /*private*/ void ConditionalNGTableModel::buttomColumnClicked(int row, int col) {
            if (editor->_inReorderMode) {
                editor->swapConditionalNG(row);
            } else {
                // Use separate Runnable so window is created on top
//                class WindowMaker implements Runnable {

//                    int row;

//                    WindowMaker(int r) {
//                        row = r;
//                    }

//                    //@Override
//                    /*public*/  void run() {
                        editor->editConditionalNGPressed(row);
//                    }
                }
//                WindowMaker t = new WindowMaker(row);
//                javax.swing.SwingUtilities.invokeLater(t);
//            }
        }

        /*private*/ void ConditionalNGTableModel::buttomDebugClicked(int row, int col) {
            if (editor->_inReorderMode) {
                editor->swapConditionalNG(row);
            } else {
                // Use separate Runnable so window is created on top
//                class WindowMaker implements Runnable {

//                    int row;

//                    WindowMaker(int r) {
//                        row = r;
//                    }

//                    //@Override
//                    /*public*/  void run() {
                        editor->debugConditionalNGPressed(row);
//                    }
//                }
//                WindowMaker t = new WindowMaker(row);
//                javax.swing.SwingUtilities.invokeLater(t);
            }
        }

        /*private*/ void ConditionalNGTableModel::deleteConditionalNG(int row) {
            LogixNGEditor_DeleteBeanWorker* worker = new LogixNGEditor_DeleteBeanWorker(editor->_curLogixNG->getConditionalNG(row), row, editor);
            worker->execute();
        }

        /*private*/ void ConditionalNGTableModel::changeUserName(QVariant value, int row) {
            QString uName =  value.toString();
            ConditionalNG* cn =  editor->_curLogixNG->getConditionalNGByUserName(uName);
            if (cn == nullptr) {
                DefaultConditionalNG* cdl =  editor->_curLogixNG->getConditionalNG(row);
                cdl->AbstractNamedBean::setUserName(uName.trimmed()); // N11N
                fireTableRowsUpdated(row, row);
            } else {
                // Duplicate user name
                if (cn !=  editor->_curLogixNG->getConditionalNG(row)) {
                    messageDuplicateConditionalNGUserName(cn->NamedBean::getSystemName());
                }
            }
        }

        //@Override
        /*public*/  bool ConditionalNGTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
         int row = index.row();
         int col = index.column();
         if(role == Qt::EditRole)
         {
            if ((row >  editor->_numConditionalNGs) || ( editor->_curLogixNG == nullptr)) {
                return false;
            }
            switch (col) {
                case BUTTON_COLUMN:
                    buttomColumnClicked(row, col);
                    break;
                case BUTTON_DEBUG_COLUMN:
                    buttomDebugClicked(row, col);
                    break;
                case BUTTON_DELETE_COLUMN:
                    deleteConditionalNG(row);
                    break;
                case BUTTON_EDIT_THREADS_COLUMN:
                {
                    EditThreadsDialog* dialog = new EditThreadsDialog(editor->_curLogixNG->getConditionalNG(row));
                    dialog->showDialog();
                    break;
                }
                case SNAME_COLUMN:
                    throw new IllegalArgumentException("System name cannot be changed");
                case UNAME_COLUMN: {
                    changeUserName(value, row);
                    break;
                }
                default:
                    throw new IllegalArgumentException("Unknown column");
            }
            return true;
        }
        return false;
    }

    /**
     * Send a duplicate Conditional user name message for Edit Logix pane.
     *
     * @param svName proposed name that duplicates an existing name
     */
    void ConditionalNGTableModel::messageDuplicateConditionalNGUserName(QString svName) {
        JOptionPane::showMessageDialog(nullptr,
                tr("Duplicate user name error. Entered user name is already in use by Conditional \"%1\".\nPlease enter a different user name from others in this table.").arg(svName),
                tr("Error"), // NOI18N
                JOptionPane::ERROR_MESSAGE);
    }

    /*protected*/ QString LogixNGEditor::getClassName() {
        return "jmri.jmrit.logixng.tools.swing.LogixNGEditor";
    }


    // ------------ LogixNG Notifications ------------
    // The ConditionalNG views support some direct changes to the parent logix.
    // This custom event is used to notify the parent LogixNG that changes are requested.
    // When the event occurs, the parent LogixNG can retrieve the necessary information
    // to carry out the actions.
    //
    // 1) Notify the calling LogixNG that the LogixNG user name has been changed.
    // 2) Notify the calling LogixNG that the conditional view is closing
    // 3) Notify the calling LogixNG that it is to be deleted
//    /**
//     * Create a custom listener event.
//     */
//    /*public*/  interface LogixNGEventListener extends EventListener {

//        void logixNGEventOccurred();
//    }

//    /**
//     * Maintain a list of listeners -- normally only one.
//     */
//    List<EditorEventListener> listenerList = new ArrayList<>();

//    /**
//     * This contains a list of commands to be processed by the listener
//     * recipient.
//     */
//    /*private*/ HashMap<String, String> logixNG_Data = new HashMap<>();

    /**
     * Add a listener.
     *
     * @param listener The recipient
     */
    //@Override
    /*public*/  void LogixNGEditor::addEditorEventListener(EditorEventListener* listener) {
        listenerList.append(listener);
    }

    /**
     * Remove a listener -- not used.
     *
     * @param listener The recipient
     */
    //@Override
    /*public*/  void LogixNGEditor::removeEditorEventListener(EditorEventListener* listener) {
        listenerList.removeOne(listener);
    }

    /**
     * Notify the listeners to check for new data.
     */
    /*private*/ void LogixNGEditor::fireEditorEvent() {
        for (EditorEventListener* l : listenerList) {
            l->editorEventOccurred(logixNG_Data);
        }
    }



//    /*private*/ class LogixNGEventListenerImpl implements ConditionalNGEditor.ConditionalNGEventListener {

//        /*private*/ /*final*/ LogixNGEditor _logixNGEditor;

//        /*public*/  LogixNGEventListenerImpl(LogixNGEditor logixNGEditor) {
//            this._logixNGEditor = logixNGEditor;
//        }

//        //@Override
//        /*public*/  void conditionalNGEventOccurred() {
//            String lgxName = _curLogixNG->getSystemName();
//            _treeEdit.logixNGData.forEach((key, value) -> {
//                if (key.equals("Finish")) {                  // NOI18N
//                    _treeEdit = null;
//                    _inEditConditionalNGMode = false;
//                    _logixNGEditor.bringToFront();
//                } else if (key.equals("Delete")) {           // NOI18N
//                    deletePressed();
//                } else if (key.equals("chgUname")) {         // NOI18N
//                    LogixNG x = _logixNG_Manager->getBySystemName(lgxName);
//                    if (x == null) {
//                        log.error("Found no logixNG for name {} when changing user name (2)", lgxName);
//                        return;
//                    }
//                    x->setUserName(value);
//                    beanTableDataModel.fireTableDataChanged();
//                }
//            });
//        }
//    }


//    /*private*/ class LogixNG_DebuggerEventListenerImpl
//            implements ConditionalNGDebugger.ConditionalNGEventListener {

//        /*private*/ /*final*/ LogixNGEditor _logixNGEditor;

//        /*public*/  LogixNG_DebuggerEventListenerImpl::LogixNG_DebuggerEventListenerImpl(LogixNGEditor* logixNGEditor) {
//            this->_logixNGEditor = logixNGEditor;
//        }

//        //@Override
//        /*public*/  void conditionalNGEventOccurred() {
//            String lgxName = _curLogixNG->getSystemName();
//            _debugger.logixNGData.forEach((key, value) -> {
//                if (key.equals("Finish")) {                  // NOI18N
//                    _debugger = null;
//                    _inEditConditionalNGMode = false;
//                    _logixNGEditor.bringToFront();
//                } else if (key.equals("Delete")) {           // NOI18N
//                    deletePressed();
//                } else if (key.equals("chgUname")) {         // NOI18N
//                    LogixNG x = _logixNG_Manager->getBySystemName(lgxName);
//                    if (x == null) {
//                        log.error("Found no logixNG for name {} when changing user name (2)", lgxName);
//                        return;
//                    }
//                    x->setUserName(value);
//                    beanTableDataModel.fireTableDataChanged();
//                }
//            });
//        }
//    }


    // This class is copied from BeanTableDataModel
//    /*private*/ class DeleteBeanWorker extends SwingWorker<Void, Void> {

//        /*private*/ /*final*/ ConditionalNG _conditionalNG;
//        /*private*/ /*final*/ int _row;
//        bool _hasDeleted = false;

        /*public*/  LogixNGEditor_DeleteBeanWorker::LogixNGEditor_DeleteBeanWorker(ConditionalNG* conditionalNG, int row, LogixNGEditor* editor) {
            _conditionalNG = conditionalNG;
            _row = row;
            this->editor = editor;
        }

        /*public*/  int LogixNGEditor_DeleteBeanWorker::getDisplayDeleteMsg() {
            return ((JmriUserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->getMultipleChoiceOption("jmri.jmrit.logixng.tools.swing.TreeEditor", "deleteInUse");
        }

        /*public*/  void LogixNGEditor_DeleteBeanWorker::setDisplayDeleteMsg(int boo) {
            ((JmriUserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setMultipleChoiceOption("jmri.jmrit.logixng.tools.swing.TreeEditor", "deleteInUse", boo);
        }

        /*public*/  void LogixNGEditor_DeleteBeanWorker::doDelete() {
            try {
                ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->deleteBean(_conditionalNG, "DoDelete");  // NOI18N
                editor->_conditionalNGTableModel->fireTableRowsDeleted(_row, _row);
                editor->_numConditionalNGs--;
                editor->_showReminder = true;
                _hasDeleted = true;
            } catch (PropertyVetoException* e) {
                //At this stage the DoDelete shouldn't fail, as we have already done a can delete, which would trigger a veto
                editor->log->error(e->getMessage());
            }
        }

        /**
         * {@inheritDoc}
         */
        //@Override
        /*public*/  void LogixNGEditor_DeleteBeanWorker::doInBackground() {
            _conditionalNG->getFemaleSocket()->unregisterListeners();

            QString message;// = new StringBuilder();
            try {
                ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->deleteBean(_conditionalNG, "CanDelete");  // NOI18N
            } catch (PropertyVetoException* e) {
                if (e->getPropertyChangeEvent()->getPropertyName() == ("DoNotDelete")) { // NOI18N
                    editor->log->warn(e->getMessage());
                    message.append(tr("%1 %2 Can not be deleted\n%3").arg(_conditionalNG->getBeanType(), _conditionalNG->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME), e->getMessage()));
                    JOptionPane::showMessageDialog(nullptr, message/*.toString()*/,
                            tr("Warning"),
                            JOptionPane::ERROR_MESSAGE);
                    return /*nullptr*/;
                }
                message.append(e->getMessage());
            }
            QList<QString> listenerRefs = QList<QString>();
            _conditionalNG->getListenerRefsIncludingChildren(listenerRefs);
            int listenerRefsCount = listenerRefs.size();
            editor->log->debug(tr("Delete with %1").arg(listenerRefsCount));
            if (getDisplayDeleteMsg() == 0x02 && message.isEmpty()) {
                doDelete();
            } else {
                /*final*/ JDialog* dialog = new JDialog();
                dialog->setTitle(tr("Warning"));
                dialog->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
                JPanel* container = new JPanel();
                container->setLayout(new QVBoxLayout());//container, BoxLayout.Y_AXIS));
                container->setBorder(BorderFactory::createEmptyBorder(10, 10, 10, 10));

                if (listenerRefsCount > 0) { // warn of listeners attached before delete
                    QString prompt = _conditionalNG->getFemaleSocket()->isConnected()
                            ? "DeleteWithChildrenPrompt" : "DeletePrompt";
                    JLabel* question = new JLabel(QString(prompt).arg(_conditionalNG->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME)));
                    question->setAlignmentX(/*Component.CENTER_ALIGNMENT*/Qt::AlignCenter);
                    container->layout()->addWidget(question);

                    QList<QString> listeners = QList<QString>();
                    for (QString listenerRef : listenerRefs) {
                        if (!listeners.contains(listenerRef)) {
                            listeners.append(listenerRef);
                        }
                    }

                    message.append("<br>");
                    message.append(tr("It is in use by %1 other objects including.").arg(listenerRefsCount));
                    message.append("<ul>");
                    for (QString listener : listeners) {
                        message.append("<li>");
                        message.append(listener);
                        message.append("</li>");
                    }
                    message.append("</ul>");

                    JEditorPane* pane = new JEditorPane();
                    pane->setContentType("text/html");
                    pane->setText("<html>" + message/*.toString()*/ + "</html>");
                    pane->setEditable(false);
                    QScrollArea* jScrollPane = new QScrollArea(/*pane*/);
                    jScrollPane->setWidget(pane);
                    container->layout()->addWidget(jScrollPane);
                } else {
                    QString prompt = _conditionalNG->getFemaleSocket()->isConnected()
                            ? "DeleteWithChildrenPrompt" : "DeletePrompt";
                    QString msg = QString(prompt).arg(_conditionalNG->NamedBean::getSystemName());
                    JLabel* question = new JLabel(msg);
                    question->setAlignmentX(/*Component.CENTER_ALIGNMENT*/Qt::AlignCenter);
                    container->layout()->addWidget(question);
                }

                /*final*/ JCheckBox* remember = new JCheckBox(tr("Remember this setting for next time?"));
                //remember->setFont(remember->getFont().deriveFont(10f));
                QFont f = remember->font();
                f.setPixelSize(10);
                remember->setFont(f);
//                remember->setAlignmentX(/*Component.CENTER_ALIGNMENT*/Qt::AlignCenter);

                JButton* yesButton = new JButton(tr("Yes"));
                JButton* noButton = new JButton(tr("No"));
                JPanel* button = new JPanel(new FlowLayout());
//                button->setAlignmentX(Component.CENTER_ALIGNMENT);
                button->layout()->addWidget(yesButton);
                button->layout()->addWidget(noButton);
                container->layout()->addWidget(button);

                connect(noButton, &JButton::clicked, [=] {
                    //there is no point in remembering this the user will never be
                    //able to delete a bean!
                    dialog->dispose();
                });

                connect(yesButton, &JButton::clicked, [=] {
                    if (remember->isSelected()) {
                        setDisplayDeleteMsg(0x02);
                    }
                    doDelete();
                    dialog->dispose();
                });
                container->layout()->addWidget(remember);
//                container->setAlignmentX(Component.CENTER_ALIGNMENT);
//                container->setAlignmentY(Component.CENTER_ALIGNMENT);
                dialog->getContentPane()->layout()->addWidget(container);
                dialog->pack();
#if 0
                dialog->getRootPane()->setDefaultButton(noButton);
                noButton.requestFocusInWindow(); // set default keyboard focus, after pack() before setVisible(true)
                dialog->getRootPane().registerKeyboardAction(e -> { // escape to exit
                        dialog->setVisible(false);
                        dialog.dispose(); },
                    KeyStroke->getKeyStroke(KeyEvent.VK_ESCAPE, 0), JComponent.WHEN_IN_FOCUSED_WINDOW);
#endif
// todo                dialog->setLocation((Toolkit->getDefaultToolkit()->getScreenSize().width()) / 2 - dialog->getWidth() / 2, (Toolkit->getDefaultToolkit()->getScreenSize().height) / 2 - dialog->getHeight() / 2);
                dialog->setModal(true);
                dialog->setVisible(true);
            }
            if (!_hasDeleted && _conditionalNG->getFemaleSocket()->isActive()) _conditionalNG->getFemaleSocket()->registerListeners();
            return /*nullptr*/;
        }

        /**
         * {@inheritDoc} Minimal implementation to catch and log errors
         */
        //@Override
        /*protected*/ void LogixNGEditor_DeleteBeanWorker::done() {
            try {
                 get();  // called to get errors
            } catch (InterruptedException/* | java.util.concurrent.ExecutionException*/* e) {
                editor->log->error("Exception while deleting bean", e);
            }
        }
//    }
#endif

    /*private*/ /*final*/ /*static*/ Logger* LogixNGEditor::log = LoggerFactory::getLogger("LogixNGEditor");
