#include "abstractlogixngtableaction.h"
#include "loggerfactory.h"
#include "vptr.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "defaultlogixngmanager.h"
#include <QMenuBar>
#include <QMenu>
#include "jmenuitem.h"
#include "jeditorpane.h"
#include "fileutil.h"
#include "jfilechooser.h"
#include "borderfactory.h"
#include "abstractlogixngtableaction.h"
#include "logixngtableaction.h"
#include <QScrollArea>
#include "jmriuserpreferencesmanager.h"

/**
 * Swing action to create and register a LogixNG Table.
 * <p>
 Also contains the panes to create, edit, and delete a LogixNG.
 <p>
 * Most of the text used in this GUI is in BeanTableBundle.properties, accessed
 * via tr().
 * <p>
 *
 * @author Dave Duchamp Copyright (C) 2007 (LogixTableAction)
 * @author Pete Cressman Copyright (C) 2009, 2010, 2011 (LogixTableAction)
 * @author Matthew Harris copyright (c) 2009 (LogixTableAction)
 * @author Dave Sand copyright (c) 2017 (LogixTableAction)
 * @author Daniel Bergqvist copyright (c) 2019 (AbstractLogixNGTableEditor)
 * @author Dave Sand copyright (c) 2021 (AbstractLogixNGTableEditor)
 *
 * @param <E> the type of NamedBean supported by this model
 */
// /*public*/  abstract class AbstractLogixNGTableAction<E extends NamedBean> extends AbstractTableAction<E> {


    //private static /*final*/ ResourceBundle rbx = ResourceBundle.getBundle("jmri.jmrit.logixng.LogixNGBundle");

    // Browser Options
    /*static*/ /*final*/ QString AbstractLogixNGTableAction::PRINT_LINE_NUMBERS_OPTION = "jmri.jmrit.logixng.PrintLineNumbers";
    /*static*/ /*final*/ QString AbstractLogixNGTableAction::PRINT_ERROR_HANDLING_OPTION = "jmri.jmrit.logixng.ErrorHandling";
    /*static*/ /*final*/ QString AbstractLogixNGTableAction::PRINT_NOT_CONNECTED_OPTION = "jmri.jmrit.logixng.NotConnectedSockets";
    /*static*/ /*final*/ QString AbstractLogixNGTableAction::PRINT_LOCAL_VARIABLES_OPTION = "jmri.jmrit.logixng.LocalVariables";



    /**
     * Create a AbstractLogixNGTableAction instance.
     *
     * @param s the Action title, not the title of the resulting frame. Perhaps
     *          this should be changed?
     */
    /*public*/  AbstractLogixNGTableAction::AbstractLogixNGTableAction(QString s, QObject* parent)
     : AbstractTableAction(s, parent)
    {
        //super(s);
//        AbstractTableAction::setEnabled(false);
        _systemName->setEnabled(false);
        _sysNameLabel->setEnabled(false);
    }



    // ------------ Methods for LogixNG Table Window ------------

    /**
     * Create the JTable DataModel, along with the changes (overrides of
     * BeanTableDataModel) for the specific case of a LogixNG table.
     */
    //@Override
    /*protected*/ void AbstractLogixNGTableAction::createModel() {
        m = new LNGBeanTableDataModel/*<E>*/(this);// {

    }
//            // overlay the state column with the edit column
            /*static*/ /*public*/  /*final*/ int LNGBeanTableDataModel::ENABLECOL = VALUECOL;
            /*static*/ /*public*/  /*final*/ int LNGBeanTableDataModel::EDITCOL = DELETECOL;
//            /*protected*/ String enabledString = tr("ColumnHeadEnabled");  // NOI18N

           // @Override
            /*public*/  QVariant LNGBeanTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
            {
                if(role== Qt::DisplayRole && orientation == Qt::Horizontal)
                {
                    if (section == EDITCOL) {
                        return tr("Menu");     // This makes it easier to test the table
                    }
                    if (section == ENABLECOL) {
                        return enabledString;
                    }
                }
                return BeanTableDataModel::headerData(section, orientation, role);
            }

            //@Override
            /*public*/  QString LNGBeanTableDataModel::getColumnClass(int col) const {
                if (col == EDITCOL) {
                    return "String";
                }
                if (col == ENABLECOL) {
                    return "Boolean";
                }
                return BeanTableDataModel::getColumnClass(col);
            }

            //@Override
            /*public*/  int LNGBeanTableDataModel::getPreferredWidth(int col) {
                // override default value for SystemName and UserName columns
                if (col == SYSNAMECOL) {
                    return  JTextField(12).getPreferredSize().width();
                }
                if (col == USERNAMECOL) {
                    return  JTextField(17).getPreferredSize().width();
                }
                if (col == EDITCOL) {
                    return  JTextField(12).getPreferredSize().width();
                }
                if (col == ENABLECOL) {
                    return  JTextField(5).getPreferredSize().width();
                }
                return BeanTableDataModel::getPreferredWidth(col);
            }

            //@Override
            /*public*/  Qt::ItemFlags LNGBeanTableDataModel::flags(const QModelIndex &index) const {
                if (index.column() == EDITCOL) {
                    return Qt::ItemIsEnabled | Qt::ItemIsEditable;
                }
                if (index.column() == ENABLECOL) {
                    return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
                }
                return BeanTableDataModel::flags(index);
            }

            //@SuppressWarnings("unchecked")  // Unchecked cast from Object to E
            //@Override
            /*public*/  QVariant LNGBeanTableDataModel::data(const QModelIndex &index, int role) const {
             if(role == Qt::DisplayRole)
             {
                if (index.column() == EDITCOL) {
                    return tr("Select");  // NOI18N
                }
             }
             if(role == Qt::CheckStateRole)
             {
              if (index.column() == ENABLECOL) {
                    NamedBean* x = VPtr<NamedBean>::asPtr( BeanTableDataModel::getValueAt(index.row(), SYSNAMECOL));
                    if (x == nullptr) {
                        return Qt::Unchecked;
                    }
                    return act->isEnabled(x)?Qt::Checked:Qt::Unchecked;
                }
             }
             return BeanTableDataModel::data(index, role);
            }

            //@SuppressWarnings("unchecked")  // Unchecked cast from Object to E
            //@Override
            /*public*/  /*public*/  bool LNGBeanTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
            {

             if(role == Qt::EditRole)
             {
                if (index.column() == EDITCOL) {
                    // set up to edit
                    QString sName = VPtr<NamedBean>::asPtr(BeanTableDataModel::getValueAt(index.row(), SYSNAMECOL))->getSystemName();
                    if (tr("Edit") == (value)) {  // NOI18N
                        act->editPressed(sName);

                    } else if (tr("Browse") == (value)) {  // NOI18N
                        act->conditionalRowNumber = index.row();
                        act->browserPressed(sName);

                    } else if (tr("Copy") == (value)) {  // NOI18N
                        act->copyPressed(sName);

                    } else if (tr("Delete") == (value)) {  // NOI18N
                        act->deletePressed(sName);
                    }
                }
                return true;
             }
             if(role == Qt::CheckStateRole){
                if (index.column() == ENABLECOL) {
                    // alternate
                    NamedBean* x = VPtr<NamedBean>::asPtr(BeanTableDataModel::getValueAt(index.row(), SYSNAMECOL));
                    bool v = act->isEnabled(x);
                    act->setEnabled(x, !v);
                }
                return true;
              }
              BeanTableDataModel::setData(index, value, role);
            }

            /**
             * Delete the bean after all the checking has been done.
             * <p>
             * Deletes the NamedBean.
             *
             * @param bean of the NamedBean to delete
             */
            //@Override
            /*protected*/ void LNGBeanTableDataModel::doDelete(NamedBean* bean) {
                // delete the LogixNG
                act->deleteBean(bean);
            }

            //@Override
            /*protected*/ bool LNGBeanTableDataModel::matchPropertyName(PropertyChangeEvent* e) {
                if (e->getPropertyName() == (enabledString)) {
                    return true;
                }
                return BeanTableDataModel::matchPropertyName(e);
            }

            //@Override
            /*public*/  Manager/*<E>*/* LNGBeanTableDataModel::getManager() {
                return act->getManager();
            }

            //@Override
            /*public*/  NamedBean* LNGBeanTableDataModel::getBySystemName(QString name) const{
                return act->getManager()->getBySystemName(name);
            }

            //@Override
            /*public*/  NamedBean* LNGBeanTableDataModel::getByUserName(QString name) {
                return act->getManager()->getByUserName(name);
            }

            //@Override
            /*protected*/ QString LNGBeanTableDataModel::getMasterClassName() {
                return act->getClassName();
            }

            //@Override
            /*public*/  void LNGBeanTableDataModel::configureTable(JTable* table) {
//                table.setDefaultRenderer(bool.class, new EnablingCheckboxRenderer());
//                table.setDefaultRenderer(JComboBox.class, new jmri.jmrit.symbolicprog.ValueRenderer());
//                table.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
                if (!(qobject_cast<DefaultLogixNGManager*>(getManager()->mself()))) {
                    table->getColumnModel()->getColumn(2)->setMinWidth(0);
                    table->getColumnModel()->getColumn(2)->setMaxWidth(0);
                }
                BeanTableDataModel::configureTable(table);
            }

            /**
             * Replace delete button with comboBox to edit/delete/copy/select NamedBean.
             *
             * @param table name of the NamedBean JTable holding the column
             */
            //@Override
            /*protected*/ void LNGBeanTableDataModel::configDeleteColumn(JTable* table) {
                JComboBox* editCombo = new JComboBox();
                editCombo->addItem(tr("Select"));  // NOI18N
                editCombo->addItem(tr("Edit"));  // NOI18N
                editCombo->addItem(tr("Browser"));  // NOI18N
                editCombo->addItem(tr("Copy"));  // NOI18N
                editCombo->addItem(tr("Delete"));  // NOI18N
                TableColumn* col = table->getColumnModel()->getColumn(BeanTableDataModel::DELETECOL);
//                col->setCellEditor(new DefaultCellEditor(editCombo));
            }

            // Not needed - here for interface compatibility
            //@Override
            /*public*/  void LNGBeanTableDataModel::clickOn(NamedBean* t) {
            }

            //@Override
            /*public*/  QString LNGBeanTableDataModel::getValue(QString s) {
                return "";
            }

            //@Override
            /*protected*/ QString LNGBeanTableDataModel::getBeanType() {
//                 return tr("BeanNameLogix");  // NOI18N
                return tr("LogixNG");  // NOI18N
            }
//        };
//    }

    /**
     * Set title of NamedBean table.
     */
    //@Override
    /*protected*/ void AbstractLogixNGTableAction::setTitle() {
        f->setTitle(tr("LogixNG Table"));
    }

    /**
     * Insert 2 table specific menus.
     * <p>
     * Accounts for the Window and Help menus, which are already added to the
     * menu bar as part of the creation of the JFrame, by adding the new menus 2
     * places earlier unless the table is part of the ListedTableFrame, which
     * adds the Help menu later on.
     *
     * @param f the JFrame of this table
     */
    //@Override
    /*public*/  void AbstractLogixNGTableAction::setMenuBar(BeanTableFrame* f) {
        QMenu* menu = new QMenu(tr("Options"));  // NOI18N
//        menu->setMnemonic(KeyEvent.VK_O);
        QMenuBar* menuBar = f->menuBar();
        int pos = menuBar->children().count() - 1;  // count the number of menus to insert the TableMenus before 'Window' and 'Help'
        int offset = 1;
        log->debug("setMenuBar number of menu items = " + QString::number(pos));  // NOI18N
        for (int i = 0; i <= pos; i++) {
            if (qobject_cast<QMenu*>(menuBar->children().at(i))) {
                if (((QMenu*) menuBar->children().at(i))->title() == (tr("Help"))) {  // NOI18N
                    offset = -1;  // correct for use as part of ListedTableAction where the Help Menu is not yet present
                }
            }
        }

        // Do not include this menu for Module or Table tables
        if (qobject_cast<LogixNGTableAction*>(this)) {
            JMenuItem* r = new JMenuItem(tr("Enable All LogixNGs"),(QObject*)this);  // NOI18N
            connect(r, &JMenuItem::triggered, [=]{
                enableAll(true);
            });
            menu->addAction(r);

            r = new JMenuItem(tr("Disable All LogixNGs"),(QObject*)this);  // NOI18N
            connect(r, &JMenuItem::triggered, [=] {
                enableAll(false);
            });
            menu->addAction(r);

            QObjectList  l =menuBar->children();
            menuBar->insertMenu((QAction*)menuBar->children().at(pos+offset-1), menu/*, pos + offset*/);
            offset++;
        }

        menu = new QMenu(tr("Tools"));  // NOI18N
//        menu.setMnemonic(KeyEvent.VK_T);

        JMenuItem* item = new JMenuItem(tr("Open PickList Tables"),(QObject*)this);  // NOI18N
        connect(item, &JMenuItem::triggered, [=]{
            openPickListTable();
        });
        menu->addAction(item);

        QObjectList  l =menuBar->children();
        if((pos+offset-1)>= l.count())
         offset--;
        menuBar->insertMenu((QAction*)menuBar->children().at(pos+offset-1), menu/*, pos + offset*/); // add this menu to the right of the previous

    }

    /**
     * Open a new Pick List to drag Actions from to form NamedBean.
     */
    /*private*/ void AbstractLogixNGTableAction::openPickListTable() {
        if (_pickTables == nullptr) {
            _pickTables = new PickFrame(tr("Pick Lists"));  // NOI18N
        } else {
            _pickTables->setVisible(true);
        }
        _pickTables->toFront();
    }

    //@Override
    /*protected*/ QString AbstractLogixNGTableAction::helpTarget() {
        return "package.jmri.jmrit.beantable.LogixNGTable";  // NOI18N
    }


    // Current focus variables






    // ------------ Methods for Add bean Window ------------

    /**
     * Respond to the Add button in bean table Creates and/or initialize
     * the Add bean pane.
     *
     * @param e The event heard
     */
    //@Override
    /*protected*/ void AbstractLogixNGTableAction::addPressed(JActionEvent* e) {
        // possible change
        if (!checkFlags(nullptr)) {
            return;
        }
        _showReminder = true;
        // make an Add bean Frame
        if (addLogixNGFrame == nullptr) {
            QString titleKey = getAddTitleKey();
            QString buttonHintKey = getCreateButtonHintKey();
            JPanel* panel5 = makeAddFrame(titleKey, "Add");  // NOI18N
            // Create bean
            create = new JButton(tr("Create"));  // NOI18N
            panel5->layout()->addWidget(create);
            //create.addActionListener(this::createPressed);
            connect(create, &JButton::clicked, [=]{createPressed();});
            create->setToolTip(buttonHintKey);  // NOI18N
        }
        addLogixNGFrame->pack();
        addLogixNGFrame->setVisible(true);
        _autoSystemName->setSelected(false);
        UserPreferencesManager* prefMgr =(JmriUserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
          if(prefMgr)
            _autoSystemName->setSelected(prefMgr->getCheckboxPreferenceState(systemNameAuto, true));
          m->updateNameList();
    }

    // /*protected*/ abstract JPanel makeAddFrame(String titleId, String startMessageId);

    /**
     * Enable/disable fields for data entry when user selects to have system
     * name automatically generated.
     */
    void AbstractLogixNGTableAction::autoSystemName() {
        if (_autoSystemName->isSelected()) {
            _systemName->setEnabled(false);
            _sysNameLabel->setEnabled(false);
        } else {
            _systemName->setEnabled(true);
            _sysNameLabel->setEnabled(true);
        }
    }

    /**
     * Respond to the Cancel button in Add bean window.
     * <p>
 Note: Also get there if the user closes the Add bean window.
     *
     * @param e The event heard
     */
    void AbstractLogixNGTableAction::cancelAddPressed(JActionEvent* e) {
     if(addLogixNGFrame)
     {
        addLogixNGFrame->setVisible(false);
        addLogixNGFrame->dispose();
        addLogixNGFrame = nullptr;
     }
        _inCopyMode = false;
        if (f != nullptr) {
            f->setVisible(true);
        }
    }

    /**
     * Respond to the Copy bean button in Add bean window.
     * <p>
     * Provides a pane to set new properties of the copy.
     *
     * @param sName system name of bean to be copied
     */
    void AbstractLogixNGTableAction::copyPressed(QString sName) {
        if (!checkFlags(sName)) {
            return;
        }

        Runnable* t = new ALNGRunnable(this);
//        {
//            @Override
//            /*public*/  void run() {
//                JOptionPane::showMessageDialog(null, "Copy is not implemented yet.", "Error", JOptionPane::ERROR_MESSAGE);

//                // This may or may not work. It's not tested yet.
//                // Disable for now.
//                if (1==0) {
//                    JPanel panel5 = makeAddFrame("TitleCopyLogixNG", "Copy");    // NOI18N
//                    // Create bean
//                    JButton create = new JButton(tr("ButtonCopy"));  // NOI18N
//                    panel5.add(create);
//                    create.addActionListener((ActionEvent e) -> {
//                        JOptionPane::showMessageDialog(null, "Copy is not implemented yet.", "Error", JOptionPane::ERROR_MESSAGE);
//    //                    copyLogixNGPressed(e);
//                    });
//                    addLogixNGFrame.pack();
//                    addLogixNGFrame.setVisible(true);
//                    _autoSystemName.setSelected(false);
//                    InstanceManager.getOptionalDefault(UserPreferencesManager.class).ifPresent((prefMgr) -> {
//                        _autoSystemName.setSelected(prefMgr->getCheckboxPreferenceState(systemNameAuto, true));
//                    });
//                }
//                _inCopyMode = false;
//            }
//        };
        log->debug(tr("copyPressed started for %1").arg(sName));  // NOI18N
//        javax.swing.SwingUtilities.invokeLater(t);
        _inCopyMode = true;
        _logixNGSysName = sName;
    }


    /**
     * Copy the bean as configured in the Copy set up pane.
     *
     * @param e the event heard
     */
    void AbstractLogixNGTableAction::copyLogixNGPressed(JActionEvent* e) {
/*
        String uName = _addUserName.getText().trim();
        if (uName.length() == 0) {
            uName = null;
        }
        LogixNG targetLogixNG;
        if (_autoSystemName->isSelected()) {
            if (!checkLogixNGUserName(uName)) {
                return;
            }
            targetLogixNG = _logixNG_Manager.createLogixNG(uName);
        } else {
            if (!checkLogixNGSysName()) {
                return;
            }
            String sName = _systemName.getText().trim();
            // check if a LogixNG with this name already exists
            bool createLogix = true;
            targetLogixNG = _logixNG_Manager.getBySystemName(sName);
            if (targetLogixNG != null) {
                int result = JOptionPane::showConfirmDialog(f,
                        tr("ConfirmLogixDuplicate", sName, _logixNGSysName), // NOI18N
                        tr("QuestionTitle"), JOptionPane::YES_NO_OPTION,    // NOI18N
                        JOptionPane::QUESTION_MESSAGE);
                if (JOptionPane::NO_OPTION == result) {
                    return;
                }
                createLogix = false;
                String userName = targetLogixNG.getUserName();
                if (userName != null && userName.length() > 0) {
                    _addUserName.setText(userName);
                    uName = userName;
                }
            } else if (!checkLogixNGUserName(uName)) {
                return;
            }
            if (createLogix) {
                // Create the new LogixNG
                targetLogixNG = _logixNG_Manager.createLogixNG(sName, uName);
                if (targetLogixNG == null) {
                    // should never get here unless there is an assignment conflict
                    log.error("Failure to create LogixNG with System Name: {}", sName);  // NOI18N
                    return;
                }
            } else if (targetLogixNG == null) {
                log.error("Error targetLogix is null!");  // NOI18N
                return;
            } else {
                targetLogixNG.setUserName(uName);
            }
        }
        LogixNG srcLogic = _logixNG_Manager.getBySystemName(_logixNGSysName);
        for (int i = 0; i < srcLogic.getNumConditionals(); i++) {
            String cSysName = srcLogic.getConditionalByNumberOrder(i);
            copyConditionalToLogix(cSysName, srcLogic, targetLogixNG);
        }
        cancelAddPressed(null);
*/
    }

    /**
     * Check and warn if a string is already in use as the user name of a LogixNG.
     *
     * @param uName the suggested name
     * @return true if not in use
     */
    bool AbstractLogixNGTableAction::checkLogixNGUserName(QString uName) {
        // check if a bean with the same user name exists
        if (uName != "" && uName.trimmed().length() > 0) {
            NamedBean* x = getManager()->getByUserName(uName);
            if (x != nullptr) {
                // A bean with this user name already exists
                JOptionPane::showMessageDialog(addLogixNGFrame,
                        tr("A LogixNG with this user name already exists.\nPlease change user name and try again."), tr("Error"), // NOI18N
                        JOptionPane::ERROR_MESSAGE);
                return false;
            }
        }
        return true;
    }

    /**
     * Check validity of bean system name.
     * <p>
     * Fixes name if it doesn't start with "IQ".
     *
     * @return false if name has length &lt; 1 after displaying a dialog
     */
    bool AbstractLogixNGTableAction::checkLogixNGSysName() {
        QString sName = _systemName->text();
        if ((sName.length() < 1)) {
            // Entered system name is blank or too short
            JOptionPane::showMessageDialog(addLogixNGFrame,
                    tr("Invalid system name, or system name not entered.\nPlease enter a valid LogixNG system name (e.g. IQ3) and try again."), tr("Error"), // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            return false;
        }
        if ((sName.length() < 2) || (sName.at(0) != 'I')
                || (sName.at(1) != 'Q')) {
            // System name does not begin with IQ:, prefix IQ: to it
            QString s = sName;
            sName = "IQ" + s;  // NOI18N
        }
        _systemName->setText(sName);
        return true;
    }

    /**
     * Check if another bean editing session is currently open or no system
     * name is provided.
     *
     * @param sName system name of bean to be copied
     * @return true if a new session may be started
     */
    bool AbstractLogixNGTableAction::checkFlags(QString sName) {
        if (_inEditMode) {
            // Already editing a bean, ask for completion of that edit
            JOptionPane::showMessageDialog(nullptr,
                    tr("Cannot edit two LogixNGs at the same time. Please complete edit of LogixNG \"%1\" and try again.").arg(_curNamedBean->getSystemName()),
                    tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            if (_editor != nullptr) {
                _editor->bringToFront();
            }
            return false;
        }

        if (_inCopyMode) {
            // Already editing a bean, ask for completion of that edit
            JOptionPane::showMessageDialog(nullptr,
                    tr("Copy of LogixNG \"%1\" in progress.  Please complete and try again.").arg(_logixNGSysName),
                    tr("Error"), // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            return false;
        }

        if (sName != "") {
            // check if a bean with this name exists
            NamedBean* x = getManager()->getBySystemName(sName);
            if (x == nullptr) {
                // bean does not exist, so cannot be edited
                log->error("No bean with system name: " + sName);
                JOptionPane::showMessageDialog(nullptr,
                        tr("Cannot find a LogixNG with that system name."),
                        tr("Error"), // NOI18N
                        JOptionPane::ERROR_MESSAGE);
                return false;
            }
        }
        return true;
    }

    /**
     * Respond to the Create bean button in Add bean window.
     *
     * @param e The event heard
     */
    void AbstractLogixNGTableAction::createPressed(JActionEvent* e) {
        // possible change
        _showReminder = true;
        QString sName;
        QString uName = _addUserName->text().trimmed();
        if (uName.length() == 0) {
            uName = "";
        }
        if (_autoSystemName->isSelected()) {
            if (!checkLogixNGUserName(uName)) {
                return;
            }
            _curNamedBean = createBean(uName);
            if (_curNamedBean == nullptr) {
                log->error(tr("Failure to create bean with System Name: %1").arg("none"));  // NOI18N
                return;
            }
            sName = _curNamedBean->getSystemName();
        } else {
            if (!checkLogixNGSysName()) {
                return;
            }
            // Get validated system name
            sName = _systemName->text();
            // check if a bean with this name already exists
            NamedBean* x = nullptr;
            try {
                x = getManager()->getBySystemName(sName);
            } catch (Exception* ex) {
                // user input no good
                handleCreateException(sName);
                return;  // without creating
            }
            if (x != nullptr) {
                // bean already exists
                JOptionPane::showMessageDialog(addLogixNGFrame, tr("A LogixNG with this system name already exists.\nPlease change system name and try again."),
                        tr("Error"), // NOI18N
                        JOptionPane::ERROR_MESSAGE);
                return;
            }
            if (!checkLogixNGUserName(uName)) {
                return;
            }
            // Create the new bean
            _curNamedBean = createBean(sName, uName);
            if (_curNamedBean == nullptr) {
                // should never get here unless there is an assignment conflict
                log->error(tr("Failure to create bean with System Name: %1").arg(sName));  // NOI18N
                return;
            }
        }
        cancelAddPressed(nullptr);
        // create the Edit bean Window
        editPressed(sName);
        UserPreferencesManager* prefMgr = (JmriUserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
        if(prefMgr)
        {
            prefMgr->setCheckboxPreferenceState(systemNameAuto, _autoSystemName->isSelected());
        }//);
    }

    void AbstractLogixNGTableAction::handleCreateException(QString sysName) {
        JOptionPane::showMessageDialog(addLogixNGFrame,
                tr("ErrorLogixAddFailed %1").arg(sysName), // NOI18N
                tr("Error"), // NOI18N
                JOptionPane::ERROR_MESSAGE);
    }

    // ------------ Methods for Edit bean Pane ------------

    /**
     * Respond to the Edit button pressed in LogixNG table.
     *
     * @param sName system name of LogixNG to be edited
     */
    void AbstractLogixNGTableAction::editPressed(QString sName) {
        _curNamedBean = getManager()->getBySystemName(sName);
        if (!checkFlags(sName)) {
            return;
        }

        // Create a new bean edit view, add the listener.
        _editor = getEditor(f, m, sName);

        if (_editor == nullptr) return;    // Editor not implemented yet for LogixNG Tables

        _inEditMode = true;
#if 0
        _editor->addEditorEventListener(data);
        {
            QString lgxName = sName;
            data.forEach((key, value) -> {
                if (key.equals("Finish")) {                  // NOI18N
                    _editor = null;
                    _inEditMode = false;
                    f.setVisible(true);
                } else if (key.equals("Delete")) {           // NOI18N
                    _inEditMode = false;
                    deletePressed(value);
                } else if (key.equals("chgUname")) {         // NOI18N
                    E x = getManager().getBySystemName(lgxName);
                    if (x == null) {
                        log.error("Found no logixNG for name {} when changing user name (2)", lgxName);
                        return;
                    }
                    x.setUserName(value);
                    m.fireTableDataChanged();
                }
            });
        });
#endif
       _editor->addEditorEventListener(new AbstractLogixNGTableAction_EventListener(sName, this));
    }

    /**
     * Display reminder to save.
     */
    void AbstractLogixNGTableAction::showSaveReminder() {
        if (_showReminder) {
            if (InstanceManager::getNullableDefault("UserPreferencesManager") != nullptr) {
                ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                        showInfoMessage(tr("Reminder"), tr("<html>Remember to save your %1 information in your Configuration.<br>(choose Store &gt; Store Configuration... from the File menu)</html>").arg(tr("LogixNGTable")), // NOI18N
                                getClassName(),
                                "remindSaveLogix");  // NOI18N
            }
        }
    }

    //@Override
    /*public*/  void AbstractLogixNGTableAction::setMessagePreferencesDetails() {
        QMap<int, QString> options = QMap<int, QString>(/*3*/);
        options.insert(0x00, tr("DeleteAsk"));      // NOI18N
        options.insert(0x01, tr("DeleteNever"));    // NOI18N
        options.insert(0x02, tr("DeleteAlways"));   // NOI18N
        ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setMessageItemDetails(getClassName(),
                "deleteInUse", tr("When Deleting an item that is in use"), &options, 0x00);
    }

    /**
     * Respond to the Delete combo selection bean window delete request.
     *
     * @param sName system name of bean to be deleted
     */
    void AbstractLogixNGTableAction::deletePressed(QString sName) {
        if (!checkFlags(sName)) {
            return;
        }

        /*final*/ NamedBean* x = getManager()->getBySystemName(sName);
        /*final*/ UserPreferencesManager* p;
        p = (UserPreferencesManager*)InstanceManager::getNullableDefault("UserPreferencesManager");

        if (x == nullptr) return;  // This should never happen

        QString message;// = new StringBuilder();
        try {
            getManager()->deleteBean(x, "CanDelete");  // NOI18N
        } catch (PropertyVetoException* e) {
            if (e->getPropertyChangeEvent()->getPropertyName() == ("DoNotDelete")) { // NOI18N
                log->warn(e->getMessage());
                message.append(tr("VetoDeleteBean %1").arg(x->getBeanType(), x->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME), e->getMessage()));
                JOptionPane::showMessageDialog(nullptr, message,
                        tr("QuestionTitle"),
                        JOptionPane::ERROR_MESSAGE);
                return;
            }
            message.append(e->getMessage());
        }
        QList<QString> listenerRefs = QList<QString>();
        getListenerRefsIncludingChildren(x, listenerRefs);
        int listenerRefsCount = listenerRefs.size();
        log->debug(tr("Delete with %1").arg(listenerRefsCount));
        if (p != nullptr && p->getMultipleChoiceOption(getClassName(), "delete") == 0x02 && message.isEmpty()) {
            deleteBean(x);
        } else {
            /*final*/ JDialog* dialog = new JDialog();
            dialog->setTitle(tr("QuestionTitle"));
            dialog->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
            JPanel* container = new JPanel();
            container->setBorder(BorderFactory::createEmptyBorder(10, 10, 10, 10));
            container->setLayout(new QVBoxLayout());//container, BoxLayout.Y_AXIS));

            if (listenerRefsCount > 0) { // warn of listeners attached before delete
                QString prompt = hasChildren(x)
                        ? "DeleteWithChildrenPrompt" : "DeletePrompt";
                JLabel* question = new JLabel(prompt+x->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME));
//                question->setAlignmentX(Component.CENTER_ALIGNMENT);
                container->layout()->addWidget(question);

                QList<QString> listeners = QList<QString>();
                for (QString listenerRef : listenerRefs) {
                    if (!listeners.contains(listenerRef)) {
                        listeners.append(listenerRef);
                    }
                }

                message.append("<br>");
                message.append(tr("ReminderInUse %1").arg(listenerRefsCount));
                message.append("<ul>");
                for (QString listener : listeners) {
                    message.append("<li>");
                    message.append(listener);
                    message.append("</li>");
                }
                message.append("</ul>");

                JEditorPane* pane = new JEditorPane();
                pane->setContentType("text/html");
                pane->setText("<html>" + message + "</html>");
                pane->setEditable(false);
//                JScrollPane jScrollPane = new JScrollPane(pane);
//                container.add(jScrollPane);
                container->layout()->addWidget(pane);
            } else {
                QString prompt = hasChildren(x)
                        ? "Are you sure you want to delete %1 and its children?" : tr("Are you sure you want to delete %1?");
                QString msg = QString(prompt).arg(x->getSystemName());
                JLabel* question = new JLabel(msg);
                question->setAlignmentX(Qt::AlignCenter);
                container->layout()->addWidget(question);
            }

            /*final*/ JCheckBox* remember = new JCheckBox(tr("MessageRememberSetting"));
//            remember->setFont(remember.getFont().deriveFont(10f));
//            remember->setAlignmentX(Qt::AlignCenter);

            JButton* yesButton = new JButton(tr("ButtonYes"));
            JButton* noButton = new JButton(tr("ButtonNo"));
            JPanel* button = new JPanel(new FlowLayout());
//            button->setAlignmentX(Qt::AlignCenter);
            button->layout()->addWidget(yesButton);
            button->layout()->addWidget(noButton);
            container->layout()->addWidget(button);

            connect(noButton, &JButton::clicked, [=] {
                //there is no point in remembering this the user will never be
                //able to delete a bean!
                dialog->dispose();
            });

            connect(yesButton, &JButton::clicked, [=] {
                if (remember->isSelected() && p != nullptr) {
                    p->setMultipleChoiceOption(getClassName(), "delete", 0x02);  // NOI18N
                }
                deleteBean(x);
                dialog->dispose();
            });
            container->layout()->addWidget(remember);
//            container->l.setAlignmentX(Component.CENTER_ALIGNMENT);
//            container.setAlignmentY(Component.CENTER_ALIGNMENT);
            dialog->getContentPane()->layout()->addWidget(container);
            dialog->pack();

            //dialog->getRootPane().setDefaultButton(noButton);
            noButton->setDefault(true);
//            noButton.requestFocusInWindow(); // set default keyboard focus, after pack() before setVisible(true)
//            dialog->getRootPane().registerKeyboardAction(e -> { // escape to exit
//                    dialog->setVisible(false);
//                    dialog->dispose(); },
//                KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), JComponent.WHEN_IN_FOCUSED_WINDOW);

// TODO:           dialog->setLocation((Toolkit.getDefaultToolkit().getScreenSize().width) / 2 - dialog->getWidth() / 2, (Toolkit.getDefaultToolkit().getScreenSize().height) / 2 - dialog->getHeight() / 2);
            dialog->setModal(true);
            dialog->setVisible(true);
        }
    }

    //@Override
    /*public*/  QString AbstractLogixNGTableAction::getClassDescription() {
        return tr("LogixNGTable");        // NOI18N
    }

    //@Override
    /*protected*/ QString AbstractLogixNGTableAction::getClassName() {
        return /*AbstractLogixNGTableAction.class.getName()*/"jmri.jmrit.beantable.AbstractLogixNGTableAction";
    }

// ------------ Methods for Conditional Browser Window ------------
    /**
     * Respond to the Browse button pressed in bean table.
     *
     * @param sName The selected bean system name
     */
    void AbstractLogixNGTableAction::browserPressed(QString sName) {
        // bean was found, create the window
        _curNamedBean = getManager()->getBySystemName(sName);
        getPrintTreeSettings();
        makeBrowserWindow();
    }

    void AbstractLogixNGTableAction::getPrintTreeSettings() {
        // Set options
        UserPreferencesManager* prefMgr = (UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");// .ifPresent((prefMgr) -> {
        if(prefMgr)
        {    _printTreeSettings->_printLineNumbers = prefMgr->getSimplePreferenceState(PRINT_LINE_NUMBERS_OPTION);
            _printTreeSettings->_printErrorHandling = prefMgr->getSimplePreferenceState(PRINT_ERROR_HANDLING_OPTION);
            _printTreeSettings->_printNotConnectedSockets = prefMgr->getSimplePreferenceState(PRINT_NOT_CONNECTED_OPTION);
            _printTreeSettings->_printLocalVariables = prefMgr->getSimplePreferenceState(PRINT_LOCAL_VARIABLES_OPTION);
        }//);
    }

    /**
     * Update text in the browser window.
     */
    void AbstractLogixNGTableAction::updateBrowserText() {
        if (_textContent != nullptr) {
            _textContent->setText(getBeanText((NamedBean*)_curNamedBean));
        }
    }

    /**
     * Create and initialize the conditionalNGs browser window.
     */
    void AbstractLogixNGTableAction::makeBrowserWindow() {
        JmriJFrame* condBrowserFrame = new JmriJFrame(tr("LogixNG/Module Browser"), false, true);   // NOI18N

//        condBrowserFrame.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/  void windowClosed(WindowEvent e) {
//                _textContent = null;
//            }
//        });

        QWidget* contentPane = condBrowserFrame->getContentPane();
        contentPane->setLayout(new QVBoxLayout());//BorderLayout());

        // bean header information
        JPanel* topPanel = new JPanel(new FlowLayout());
        QString tStr = tr("LogixNG:") + " " + _curNamedBean->getSystemName() + "    " // NOI18N
                + _curNamedBean->getUserName() + "    "
                + (isEnabled((NamedBean*)_curNamedBean)
                        ? tr("(Enabled)") // NOI18N
                        : tr("(Disabled)"));  // NOI18N
        topPanel->layout()->addWidget(new JLabel(tStr));
        ((QVBoxLayout*)contentPane->layout())->addWidget(topPanel,0, Qt::AlignTop); //BorderLayout.NORTH);

        // Build the conditionalNGs listing
        _textContent = new JTextArea(this->getBeanText((NamedBean*)_curNamedBean));
        if (browseMonoSpace()) {
            _textContent->setFont(QFont("Monospace",12));//Font.MONOSPACED, Font.PLAIN, 12));
        }
        QScrollArea* scrollPane = new QScrollArea(/*_textContent*/);
        scrollPane->setWidget(_textContent);
        ((QVBoxLayout*)contentPane->layout())->addWidget(scrollPane, 1, Qt::AlignCenter);

        JPanel* bottomPanel = new JPanel();
        bottomPanel->setLayout(new QHBoxLayout());//BorderLayout());
        JButton* helpBrowse = new JButton(tr("Help"));   // NOI18N
        ((QHBoxLayout*)bottomPanel->layout())->addWidget(helpBrowse, 0, Qt::AlignLeft);//BorderLayout.WEST);
        connect(helpBrowse, &JButton::clicked, [=] {
            JOptionPane::showMessageDialog(condBrowserFrame,
                    tr("LogixNG_Browse_HelpText"),   // NOI18N
                    tr("BrowserHelpTitle"),  // NOI18N
                    JOptionPane::INFORMATION_MESSAGE);
        });

        JPanel* settingsPanel = getSettingsPanel();
        ((QHBoxLayout*)bottomPanel->layout())->addWidget(settingsPanel, 0, Qt::AlignCenter);//BorderLayout.CENTER);

        JButton* saveBrowse = new JButton(tr("Save to Text File"));   // NOI18N
        saveBrowse->setToolTip(tr("Save the browser content to a text file"));      // NOI18N
        ((QHBoxLayout*)bottomPanel->layout())->addWidget(saveBrowse, 0, Qt::AlignRight);//BorderLayout.EAST);
        connect(saveBrowse, &JButton::clicked, [=]{
            saveBrowserPressed();
        });
        ((QVBoxLayout*)contentPane->layout())->addWidget(bottomPanel, 0, Qt::AlignBottom);//BorderLayout.SOUTH);

        condBrowserFrame->pack();
        condBrowserFrame->setVisible(true);
    }  // makeBrowserWindow

    JFileChooser* userFileChooser = new JFileChooser(FileUtil::getUserFilesPath());

    /**
     * Save the bean browser window content to a text file.
     */
    void AbstractLogixNGTableAction::saveBrowserPressed() {
        userFileChooser->setApproveButtonText(tr("Save Content"));  // NOI18N
        userFileChooser->setDialogTitle(tr("BrowserSaveDialogTitle"));  // NOI18N
//        userFileChooser->rescanCurrentDirectory();
        // Default to logixNG system name.txt
        userFileChooser->setSelectedFile(new File(_curNamedBean->getSystemName() + ".txt"));  // NOI18N
        int retVal = userFileChooser->showSaveDialog(nullptr);
        if (retVal != JFileChooser::APPROVE_OPTION) {
            log->debug("Save browser content stopped, no file selected");  // NOI18N
            return;  // give up if no file selected or cancel pressed
        }
        File* file = userFileChooser->getSelectedFile();
        log->debug(tr("Save browser content to '%1'").arg(file->toString()));  // NOI18N

        if (file->exists()) {
            QVariantList options = {tr("BrowserSaveDuplicateReplace"),  // NOI18N
                    tr("BrowserSaveDuplicateAppend"),  // NOI18N
                    tr("ButtonCancel")};               // NOI18N
            int selectedOption = JOptionPane::showOptionDialog(nullptr,
                    tr("File \"%1\" already exists, select Append or Replace").arg(file->getName()), // NOI18N
                    tr("Duplicate File"),   // NOI18N
                    JOptionPane::DEFAULT_OPTION,
                    JOptionPane::WARNING_MESSAGE,
                    QIcon(), options, options[0]);
            if (selectedOption == 2 || selectedOption == -1) {
                log->debug("Save browser content stopped, file replace/append cancelled");  // NOI18N
                return;  // Cancel selected or dialog box closed
            }
            if (selectedOption == 0) {
                FileUtil::_delete(file);  // Replace selected
            }
        }

        // Create the file content
        QString tStr = tr("BrowserLogixNG") + " " + _curNamedBean->getSystemName() + "    "  // NOI18N
                + _curNamedBean->getUserName() + "    "
                + (isEnabled((NamedBean*)_curNamedBean)
                        ? tr("BrowserEnabled")    // NOI18N
                        : tr("BrowserDisabled"));  // NOI18N
//        JTextArea textContent = buildConditionalListing();
        JTextArea* textContent = new JTextArea();
        try {
            // Add bean Header inforation first
            FileUtil::appendTextToFile(file, tStr);
            FileUtil::appendTextToFile(file, textContent->getText());
        } catch (IOException* e) {
            log->error(tr("Unable to write browser content to '%1', exception: '%2'").arg(file->toString(), e->getMessage()));  // NOI18N
        }
    }

    /*protected*/ JPanel* AbstractLogixNGTableAction::getSettingsPanel() {
        JPanel* checkBoxPanel = new JPanel();

        JCheckBox* printLineNumbers = new JCheckBox(tr("LogixNG_Browse_PrintLineNumbers"));
        printLineNumbers->setSelected(_printTreeSettings->_printLineNumbers);
        connect(printLineNumbers, &JCheckBox::clicked, [=] {
            if (_printTreeSettings->_printLineNumbers != printLineNumbers->isSelected()) {
                _printTreeSettings->_printLineNumbers = printLineNumbers->isSelected();
                UserPreferencesManager* prefMgr =(UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
                  if(prefMgr) {
                    prefMgr->setSimplePreferenceState(PRINT_LINE_NUMBERS_OPTION, printLineNumbers->isSelected());
                }//);
                updateBrowserText();
            }
        });
        checkBoxPanel->layout()->addWidget(printLineNumbers);

        JCheckBox* printErrorHandling = new JCheckBox(tr("LogixNG_Browse_PrintErrorHandling"));
        printErrorHandling->setSelected(_printTreeSettings->_printErrorHandling);
        connect(printErrorHandling, &JCheckBox::clicked, [=]  {
            if (_printTreeSettings->_printErrorHandling != printErrorHandling->isSelected()) {
                _printTreeSettings->_printErrorHandling = printErrorHandling->isSelected();
                UserPreferencesManager* prefMgr =(UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
                  if(prefMgr) {
                    prefMgr->setSimplePreferenceState(PRINT_ERROR_HANDLING_OPTION, printErrorHandling->isSelected());
                }//);
                updateBrowserText();
            }
        });
        checkBoxPanel->layout()->addWidget(printErrorHandling);

        JCheckBox* printNotConnectedSockets = new JCheckBox(tr("LogixNG_Browse_PrintNotConnectedSocket"));
        printNotConnectedSockets->setSelected(_printTreeSettings->_printNotConnectedSockets);
        connect(printNotConnectedSockets, &JCheckBox::clicked, [=] {
            if (_printTreeSettings->_printNotConnectedSockets != printNotConnectedSockets->isSelected()) {
                _printTreeSettings->_printNotConnectedSockets = printNotConnectedSockets->isSelected();
                updateBrowserText();
                UserPreferencesManager* prefMgr =(UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
                  if(prefMgr) {
                    prefMgr->setSimplePreferenceState(PRINT_NOT_CONNECTED_OPTION, printNotConnectedSockets->isSelected());
                }//);
            }
        });
        checkBoxPanel->layout()->addWidget(printNotConnectedSockets);

        JCheckBox* printLocalVariables = new JCheckBox(tr("Print local variables"));
        printLocalVariables->setSelected(_printTreeSettings->_printLocalVariables);
        connect(printLocalVariables, &JCheckBox::clicked, [=] {
            if (_printTreeSettings->_printLocalVariables != printLocalVariables->isSelected()) {
                _printTreeSettings->_printLocalVariables = printLocalVariables->isSelected();
                updateBrowserText();
                UserPreferencesManager* prefMgr =(UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
                  if(prefMgr) {
                    prefMgr->setSimplePreferenceState(PRINT_LOCAL_VARIABLES_OPTION, printLocalVariables->isSelected());
                }//);
            }
        });
        checkBoxPanel->layout()->addWidget(printLocalVariables);

        return checkBoxPanel;
    }

    /*private*/ /*final*/ /*static*/ Logger* AbstractLogixNGTableAction::log = LoggerFactory::getLogger("AbstractLogixNGTableAction");
