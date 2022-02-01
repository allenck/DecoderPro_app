#include "treeeditor.h"
#include "loggerfactory.h"
#include "jmenuitem.h"
#include <QMenuBar>
#include <QMenu>
#include "clipboardeditor.h"
#include "logixng_thread.h"
#include "jmenuitem.h"
#include "conditionalng.h"
#include "threadingutil.h"
#include "femalesocketoperation.h"
#include "clipboard.h"
#include "logixng_manager.h"
#include "joptionpane.h"
#include "swingtools.h"
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include "itemlistener.h"
#include "box.h"
#include "treepath.h"
#include "treemodellistener.h"
#include "treemodel.h"
#include "treepane.h"
#include "editcommentdialog.h"
#include "functionshelpdialog.h"
#include "userpreferencesmanager.h"
#include "symboltable.h"
#include "localvariabletablemodel.h"
/**
 * Base class for LogixNG editors
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/  class TreeEditor extends TreeViewer {


    /**
     * Construct a TreeEditor.
     *
     * @param femaleRootSocket         the root of the tree
     * @param enableClipboard          should clipboard be enabled on the menu?
     * @param enableRootRemoveCutCopy  should the popup menu items remove,
     *                                 cut and copy be enabled or disabled?
     * @param enableRootPopup          should the popup menu be disabled for root?
     * @param enableExecuteEvaluate    should the popup menu show execute/evaluate?
     */
    /*public*/  TreeEditor::TreeEditor(/*@Nonnull*/ FemaleSocket* femaleRootSocket,
            EnableClipboard enableClipboard,
            EnableRootRemoveCutCopy enableRootRemoveCutCopy,
            EnableRootPopup enableRootPopup,
            EnableExecuteEvaluate enableExecuteEvaluate, QWidget *parent) : TreeViewer(femaleRootSocket, parent){

        //super(femaleRootSocket);
        _enableClipboard = enableClipboard == EnableClipboard::EnableClipboard;
        _disableRootRemoveCutCopy = enableRootRemoveCutCopy == EnableRootRemoveCutCopy::DisableRootRemoveCutCopy;
        _disableRootPopup = enableRootPopup == EnableRootPopup::DisableRootPopup;
        _enableExecuteEvaluate = enableExecuteEvaluate == EnableExecuteEvaluate::EnableExecuteEvaluate;
    }
    /*public*/ int TreeEditor::SwingConfiguratorInterfaceComparator::compare(SwingConfiguratorInterface* o1, SwingConfiguratorInterface* o2) {
         //return ((Comparable<QVariant>*)o1)->compareTo(o2);
      return (o1->toString()).compare(o2->toString());
     }


    //@Override
    /*final*/ /*public*/  void TreeEditor::initComponents() {
        JmriJFrame::initComponents();

        // The menu is created in parent class TreeViewer
        QMenuBar* menuBar = this->menuBar();

        QMenu* toolsMenu = new QMenu(tr("Tools"));
        if (_enableClipboard) {
            JMenuItem* openClipboardItem = new JMenuItem(tr("OpenClipboard"),this);
            connect(openClipboardItem, &JMenuItem::triggered, [=] {
                openClipboard();
            });
            toolsMenu->addAction(openClipboardItem);
        }
        menuBar->addMenu(toolsMenu);


        TreeEditor::PopupMenu* popup = new TreeEditor::PopupMenu(this);
        popup->init();
/*
        // The JTree can get big, so allow it to scroll
        JScrollPane scrollpane = new JScrollPane(tree);

        // create panel
        JPanel* pPanel = new JPanel();
        pPanel.setLayout(new BoxLayout(pPanel, BoxLayout.Y_AXIS));

        // Display it all in a window and make the window appear
        pPanel.add(scrollpane, "Center");

        // add panels
        getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
        getContentPane().add(pPanel);

//        initMinimumSize(new Dimension(panelWidth700, panelHeight500));
*/
    }
class TEClipboardListener : public ClipboardEventListener
{
  Q_OBJECT
  TreeEditor* te;
 public:
  TEClipboardListener(TreeEditor* te)
  {
   //_clipboardEditor->clipboardData.forEach((key, value) -> {
   foreach(QString key, te->_clipboardEditor->clipboardData){
       if (key == ("Finish")) {                  // NOI18N
           te->_clipboardEditor = nullptr;
       }
   }
  }
  QObject* self() override {return (QObject*)this;}
};

    /*final*/ /*public*/  void TreeEditor::openClipboard() {
        if (_clipboardEditor == nullptr) {
            _clipboardEditor = new ClipboardEditor();
            /*_clipboardEditor->*/initComponents();
            /*_clipboardEditor->*/setVisible(true);

            _clipboardEditor->addClipboardEventListener(new TEClipboardListener(this));
//             //);
//            });

        } else {
            JmriJFrame::setVisible(true);
        }
    }


    /**
     * Run the thread action on either the ConditionalNG thread or the
     * GUI thread.
     * If the conditionalNG is not null, run it on the conditionalNG thread.
     * If the conditionalNG is null, run it on the GUI thread.
     * The conditionalNG is null when editing the clipboard or a module.
     * @param conditionalNG the conditionalNG or null if no conditionalNG
     * @param ta the thread action
     */
    /*private*/ void TreeEditor::runOnConditionalNGThreadOrGUIThreadEventually(
            ConditionalNG* conditionalNG, ThreadAction* ta) {

        if (conditionalNG != nullptr) {
            LogixNG_Thread* thread = conditionalNG->getCurrentThread();
            thread->runOnLogixNGEventually(ta);
        } else {
            // Run the thread action on the GUI thread. And we already are on the GUI thread.
            ta->run();
        }
    }


    /**
     * Respond to the Add menu choice in the popup menu.
     *
     * @param femaleSocket the female socket
     * @param path the path to the item the user has clicked on
     */
    /*final*/ /*protected*/ void TreeEditor::renameSocketPressed(FemaleSocket* femaleSocket, TreePath* path) {
        _renameSocketDialog  = new JDialog(
                this,
                tr("Rename socket %1").arg(
                        femaleSocket->getLongDescription()),
                true);
//        _renameSocketDialog.addHelpMenu(
//                "package.jmri.jmrit.logixng.tools.swing.ConditionalNGAddEdit", true);     // NOI18N
        _renameSocketDialog->setLocation(50, 30);
        QWidget* contentPanel = _renameSocketDialog->getContentPane();
        contentPanel->setLayout(new QVBoxLayout());//contentPanel, BoxLayout.Y_AXIS));

        JPanel* p;
        GridBagLayout* pLayout;
        p = new JPanel();
//        p.setLayout(new FlowLayout());
        p->setLayout(pLayout = new GridBagLayout());
        GridBagConstraints c =  GridBagConstraints();
        c.gridwidth = 1;
        c.gridheight = 1;
        c.gridx = 0;
        c.gridy = 0;
        c.anchor = GridBagConstraints::EAST;
        pLayout->addWidget(_renameSocketLabel, c);
        c.gridx = 1;
        c.gridy = 0;
        c.anchor = GridBagConstraints::WEST;
        c.weightx = 1.0;
        c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
        pLayout->addWidget(_socketNameTextField, c);
        _socketNameTextField->setText(femaleSocket->getName());

        contentPanel->layout()->addWidget(p);

        // set up create and cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());
        // Cancel
        JButton* cancel = new JButton(tr("Cancel"));    // NOI18N
        panel5->layout()->addWidget(cancel);
        connect(cancel, &JButton::clicked, [=] {
            cancelRenameSocketPressed(nullptr);
        });
//        cancel->setToolTip(Bundle.getMessage("Press to return to Logix Table without any changes"));      // NOI18N
        cancel->setToolTip("Press to return to Logix Table without any changes");      // NOI18N
#if 0 // TODO
        _renameSocketDialog.addWindowListener(new java.awt.event.WindowAdapter() {
            //@Override
            /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
                cancelRenameSocketPressed(null);
            }
        });
#endif
        _create = new JButton(tr("OK"));  // NOI18N
        panel5->layout()->addWidget(_create);
        connect(_create, &JButton::clicked, [=] {
            if (femaleSocket->validateName(_socketNameTextField->text())) {
                femaleSocket->setName(_socketNameTextField->text());
                cancelRenameSocketPressed(nullptr);
                for (TreeModelListener* l : _treePane->femaleSocketTreeModel->listeners) {
                    TreeModelEvent* tme = new TreeModelEvent(
                            femaleSocket->self(),
                            path->getPath()
                    );
                    l->treeNodesChanged(tme);
                }
//                _treePane._tree.updateUI();
            } else {
                JOptionPane::showMessageDialog(nullptr,
                        tr("The socket name \"%1\" is not valid").arg(_socketNameTextField->text()),
                        tr("Error"),
                        JOptionPane::ERROR_MESSAGE);
            }
        });

        contentPanel->layout()->addWidget(panel5);

//        _renameSocketDialog.setLocationRelativeTo(component);
        _renameSocketDialog->setLocationRelativeTo(nullptr);
        _renameSocketDialog->pack();
        _renameSocketDialog->setVisible(true);
    }


    /**
     * Respond to the Add menu choice in the popup menu.
     *
     * @param femaleSocket the female socket
     * @param path the path to the item the user has clicked on
     */
    /*final*/ /*protected*/ void TreeEditor::addPressed(FemaleSocket* femaleSocket, TreePath* path) {

        QMap<Category*, QList</*Class<? extends Base>*/Base*> > connectableClasses =
                femaleSocket->getConnectableClasses();

        _categoryComboBox->clear();
        QList<Category*> list = QList<Category*>(connectableClasses.keys());
// TODO:       Collections.sort(list);
        for (Category* item : list) {
            _categoryComboBox->addItem(VPtr<Category>::asQVariant(item));
        }
//  TODO:      JComboBoxUtil.setupComboBoxMaxRows(_categoryComboBox);

        for (ItemListener* l : _categoryComboBox->getItemListeners()) {
            _categoryComboBox->removeItemListener(l);
        }

        connect(_categoryComboBox, &JComboBox::itemStateChanged, [=] {
            Category* category = VPtr<Category>::asPtr(_categoryComboBox->getItemAt(_categoryComboBox->getSelectedIndex()));
            _swingConfiguratorComboBox->clear();
            QList</*Class<? extends Base>*/Base*> classes = connectableClasses.value(category);
            if (!classes.isEmpty()) {
                for (/*Class<? extends Base>*/Base* clazz : classes) {
                    SwingConfiguratorInterface* sci = SwingTools::getSwingConfiguratorForClass((Class*)clazz);
                    if (sci != nullptr) {
                        _swingConfiguratorComboBox->addItem(VPtr<SwingConfiguratorInterface>::asQVariant(sci));
                    } else {
                        log->error(tr("Class %1 has no swing configurator interface").arg(clazz->self()->metaObject()->className()));
                    }
                }
// TODO:                JComboBoxUtil.setupComboBoxMaxRows(_swingConfiguratorComboBox);
            }
        });

        // Ensure the type combo box gets updated
        _categoryComboBox->setSelectedIndex(-1);
        if (_categoryComboBox->getItemCount() > 0) {
            _categoryComboBox->setSelectedIndex(0);
        }


        _selectItemTypeDialog  = new JDialog(
                this,
                tr( "Add %1").arg(femaleSocket->getLongDescription()),
                true);
//        selectItemTypeFrame.addHelpMenu(
//                "package.jmri.jmrit.logixng.tools.swing.ConditionalNGAddEdit", true);     // NOI18N
        _selectItemTypeDialog->setLocation(50, 30);
        QWidget* contentPanel = _selectItemTypeDialog->getContentPane();
        contentPanel->setLayout(new QVBoxLayout());//contentPanel, BoxLayout.Y_AXIS));

        JPanel* p;
        p = new JPanel();
//        p.setLayout(new FlowLayout());
        GridBagLayout* pLayout;
        p->setLayout(pLayout = new GridBagLayout());
        GridBagConstraints c =  GridBagConstraints();
        c.gridwidth = 1;
        c.gridheight = 1;
        c.gridx = 0;
        c.gridy = 0;
        c.anchor = GridBagConstraints::EAST;
        pLayout->addWidget(_categoryLabel, c);
        c.gridy = 1;
        pLayout->addWidget(_typeLabel, c);
        c.gridx = 1;
        c.gridy = 0;
        c.anchor = GridBagConstraints::WEST;
        c.weightx = 1.0;
        c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
        pLayout->addWidget(_categoryComboBox, c);
        c.gridy = 1;
        pLayout->addWidget(_swingConfiguratorComboBox, c);

        _categoryComboBox->setToolTip(tr("Select the category"));    // NOI18N
        _swingConfiguratorComboBox->setToolTip(tr("Select the type of item"));   // NOI18N
        contentPanel->layout()->addWidget(p);
        // set up message
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));

        contentPanel->layout()->addWidget(panel3);

        // set up create and cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());
        // Cancel
        JButton* cancel = new JButton(tr("Cancel"));    // NOI18N
        panel5->layout()->addWidget(cancel);
        connect(cancel, &JButton::clicked, [=] {
            cancelAddPressed(nullptr);
        });
//        cancel->setToolTip(Bundle.getMessage("Press to return to Logix Table without any changes"));      // NOI18N
        cancel->setToolTip("Press to return to Logix Table without any changes");      // NOI18N
#if 0
        _selectItemTypeDialog.addWindowListener(new java.awt.event.WindowAdapter() {
            //@Override
            /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
                cancelAddPressed(null);
            }
        });
#endif
        _create = new JButton(tr("Create"));  // NOI18N
        panel5->layout()->addWidget(_create);
        connect(_create, &JButton::clicked, [=] {
            cancelAddPressed(nullptr);

            SwingConfiguratorInterface* swingConfiguratorInterface =
                    VPtr<SwingConfiguratorInterface>::asPtr(_swingConfiguratorComboBox->getItemAt(_swingConfiguratorComboBox->getSelectedIndex()));
//            System.err.format("swingConfiguratorInterface: %s%n", swingConfiguratorInterface.getClass().getName());
            createAddFrame(femaleSocket, path, swingConfiguratorInterface);
        });

        contentPanel->layout()->addWidget(panel5);

        connect(_autoSystemName, &JButton::clicked, [=] {
            autoSystemName();
        });
//        addLogixNGFrame.setLocationRelativeTo(component);
        _selectItemTypeDialog->setLocationRelativeTo(nullptr);
        _selectItemTypeDialog->pack();
        _selectItemTypeDialog->setVisible(true);
    }

    /**
     * Respond to the Add menu choice in the popup menu.
     *
     * @param femaleSocket the female socket
     * @param swingConfiguratorInterface the swing configurator used to configure the new class
     * @param path the path to the item the user has clicked on
     */
    /*final*/ /*protected*/ void TreeEditor::createAddFrame(FemaleSocket* femaleSocket, TreePath* path,
            SwingConfiguratorInterface* swingConfiguratorInterface) {
        // possible change
        _showReminder = true;
        // make an Add Item Frame
        if (_addItemDialog == nullptr) {
            //MutableObject<QString> commentStr = new MutableObject<>();
         QString commentStr = QString();
            _addSwingConfiguratorInterface = swingConfiguratorInterface;
            // Create item
            _create = new JButton(tr("Create"));  // NOI18N
#if 0
            connect(_create, &JButton::clicked, [=] {
                _treePane->_femaleRootSocket->unregisterListeners();

                runOnConditionalNGThreadOrGUIThreadEventually(
                        _treePane->_femaleRootSocket->getConditionalNG(),
                        () -> {

                    QList<String> errorMessages = QList<String>();

                    bool isValid = true;

                    if (!_prefs.getShowSystemUserNames()
                            || (_systemName->text().isEmpty() && _autoSystemName.isSelected())) {
                        _systemName.setText(_addSwingConfiguratorInterface.getAutoSystemName());
                    }

                    if (_addSwingConfiguratorInterface.getManager()
                            .validSystemNameFormat(_systemName->text()) != Manager.NameValidity.VALID) {
                        isValid = false;
                        errorMessages.add(Bundle.getMessage("InvalidSystemName", _systemName->text()));
                    }

                    isValid &= _addSwingConfiguratorInterface.validate(errorMessages);

                    if (isValid) {
                        MaleSocket socket;
                        if (_addUserName->text().isEmpty()) {
                            socket = _addSwingConfiguratorInterface.createNewObject(_systemName->text(), null);
                        } else {
                            socket = _addSwingConfiguratorInterface.createNewObject(_systemName->text(), _addUserName->text());
                        }
                        _addSwingConfiguratorInterfaceMaleSocket.updateObject(socket);
    //                    for (Map.Entry<SwingConfiguratorInterface, Base> entry : _swingConfiguratorInterfaceList) {
    //                        entry.getKey().updateObject(entry.getValue());
    //                    }
                        socket.setComment(commentStr.getValue());
                        try {
                            femaleSocket->connect(socket);
                        } catch (SocketAlreadyConnectedException ex) {
                            throw new RuntimeException(ex);
                        }

                        femaleSocket->forEntireTree((Base b) -> {
                            b.addPropertyChangeListener(_treePane);
                        });

                        ThreadingUtil.runOnGUIEventually(() -> {
                            _addSwingConfiguratorInterface.dispose();
                            _addItemDialog.dispose();
                            _addItemDialog = null;

                            for (TreeModelListener l : _treePane.femaleSocketTreeModel.listeners) {
                                TreeModelEvent tme = new TreeModelEvent(
                                        femaleSocket,
                                        path.getPath()
                                );
                                l.treeNodesChanged(tme);
                            }
                            _treePane._tree.expandPath(path);
                            _treePane._tree.updateUI();

                            InstanceManager.getOptionalDefault(UserPreferencesManager.class).ifPresent((prefMgr) -> {
                                prefMgr.setCheckboxPreferenceState(_systemNameAuto, _autoSystemName.isSelected());
                            });
                        });
                    } else {
                        StringBuilder errorMsg = new StringBuilder();
                        for (String s : errorMessages) {
                            if (errorMsg.length() > 0) errorMsg.append("<br>");
                            errorMsg.append(s);
                        }
                        JOptionPane.showMessageDialog(null,
                                Bundle.getMessage("ValidateErrorMessage", errorMsg),
                                Bundle.getMessage("ValidateErrorTitle"),
                                JOptionPane.ERROR_MESSAGE);
                    }
                    ThreadingUtil.runOnGUIEventually(() -> {
                        if (_treePane._femaleRootSocket.isActive()) {
                            _treePane._femaleRootSocket.registerListeners();
                        }
                    });

                });
            });
#endif
            _create->setToolTip(tr("Press to create"));  // NOI18N

            if (_addSwingConfiguratorInterface != nullptr) {
                makeAddEditFrame(true, femaleSocket, _create, commentStr);
            }
        }
    }

    /**
     * Respond to the Edit menu choice in the popup menu.
     *
     * @param femaleSocket the female socket
     * @param path the path to the item the user has clicked on
     */
    /*final*/ /*protected*/ void TreeEditor::editPressed(FemaleSocket* femaleSocket, TreePath* path) {
        // possible change
        _showReminder = true;
        // make an Edit Frame
        if (_editActionExpressionDialog == nullptr) {
            Base* object = femaleSocket->getConnectedSocket()->getObject();
            //MutableObject<String> commentStr = new MutableObject<>(object.getComment());
            QString commentStr = QString();
            // Edit ConditionalNG
            _edit = new JButton(tr("OK"));  // NOI18N
#if 0
            connect(_edit, &JButton::clicked, [=] {

                runOnConditionalNGThreadOrGUIThreadEventually(
                        _treePane._femaleRootSocket.getConditionalNG(),
                        () -> {

                    List<String> errorMessages = new ArrayList<>();

                    bool isValid = true;

                    if (_editSwingConfiguratorInterface.getManager() != null) {
                        if (_editSwingConfiguratorInterface.getManager()
                                .validSystemNameFormat(_systemName->text()) != Manager.NameValidity.VALID) {
                            isValid = false;
                            errorMessages.add(Bundle.getMessage("InvalidSystemName", _systemName->text()));
                        }
                    } else {
                        log.debug("_editSwingConfiguratorInterface.getManager() returns null");
                    }

                    isValid &= _editSwingConfiguratorInterface.validate(errorMessages);

                    if (isValid) {
                        ThreadingUtil.runOnGUIEventually(() -> {
                            femaleSocket->unregisterListeners();

//                            Base object = femaleSocket->getConnectedSocket().getObject();
                            if (_addUserName->text().isEmpty()) {
                                ((NamedBean)object).setUserName(null);
                            } else {
                                ((NamedBean)object).setUserName(_addUserName->text());
                            }
                            ((NamedBean)object).setComment(commentStr.getValue());
                            for (Map.Entry<SwingConfiguratorInterface, Base> entry : _swingConfiguratorInterfaceList) {
                                entry.getKey().updateObject(entry.getValue());
                                entry.getKey().dispose();
                            }
                            for (TreeModelListener l : _treePane.femaleSocketTreeModel.listeners) {
                                TreeModelEvent tme = new TreeModelEvent(
                                        femaleSocket,
                                        path.getPath()
                                );
                                l.treeNodesChanged(tme);
                            }
                            _editActionExpressionDialog.dispose();
                            _editActionExpressionDialog = null;
                            _treePane._tree.updateUI();

//                            if (femaleSocket->isActive()) femaleSocket->registerListeners();
                            if (_treePane._femaleRootSocket.isActive()) {
                                _treePane._femaleRootSocket.registerListeners();
                            }
                        });
                    } else {
                        StringBuilder errorMsg = new StringBuilder();
                        for (String s : errorMessages) {
                            if (errorMsg.length() > 0) errorMsg.append("<br>");
                            errorMsg.append(s);
                        }
                        ThreadingUtil.runOnGUIEventually(() -> {
                            JOptionPane.showMessageDialog(null,
                                    Bundle.getMessage("ValidateErrorMessage", errorMsg),
                                    Bundle.getMessage("ValidateErrorTitle"),
                                    JOptionPane.ERROR_MESSAGE);
                        });
                    }

                });
            });
#endif
            _edit->setToolTip(tr("Press to save"));  // NOI18N

            makeAddEditFrame(false, femaleSocket, _edit, commentStr);
        }
    }

    /**
     * Create or edit action/expression dialog.
     *
     * @param addOrEdit true if add, false if edit
     * @param femaleSocket the female socket to which we want to add something
     * @param button a button to add to the dialog
     * @param commentStr the new comment
     */
    /*final*/ /*protected*/ void TreeEditor::makeAddEditFrame(
            bool addOrEdit,
            FemaleSocket* femaleSocket,
            JButton* button,
            /*MutableObject<String>*/QString commentStr) {

        JDialog* frame  = new JDialog(
                this,
                addOrEdit ? tr("Add %1").arg("EditMaleSocketDialogTitle"):
                        femaleSocket->getLongDescription(),
                true);
//        frame.addHelpMenu(
//                "package.jmri.jmrit.logixng.tools.swing.ConditionalNGAddEdit", true);     // NOI18N
        QWidget* contentPanel = frame->getContentPane();
        contentPanel->setLayout(new QVBoxLayout());//contentPanel, BoxLayout.Y_AXIS));

        JPanel* p;
        p = new JPanel();
//        p.setLayout(new FlowLayout());
        GridBagLayout* pLayout;
        p->setLayout(pLayout = new GridBagLayout());
        GridBagConstraints c = GridBagConstraints();
        c.gridwidth = 1;
        c.gridheight = 1;
        if (_prefs->getShowSystemUserNames()) {
            c.gridx = 0;
            c.gridy = 0;
            c.anchor = GridBagConstraints::EAST;
            pLayout->addWidget(_sysNameLabel, c);
            c.gridy = 1;
            pLayout->addWidget(_userNameLabel, c);
            c.gridy = 2;
            c.gridx = 1;
            c.gridy = 0;
            c.anchor = GridBagConstraints::WEST;
            c.weightx = 1.0;
            c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
            pLayout->addWidget(_systemName, c);
            c.gridy = 1;
            pLayout->addWidget(_addUserName, c);
            if (!femaleSocket->isConnected()) {
                c.gridx = 2;
                c.gridy = 1;
                c.anchor = GridBagConstraints::WEST;
                c.weightx = 1.0;
                c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
                c.gridy = 0;
                pLayout->addWidget(_autoSystemName, c);
            }

            if (addOrEdit) {
                _systemName->setToolTip(tr("Enter system name, e.g. %1").arg(
                        _addSwingConfiguratorInterface->getExampleSystemName()));
                _addUserName->setToolTip(tr("Enter user name, e.g. Signal 2 Control"));
            }
        } else {
            c.gridx = 0;
            c.gridy = 0;
        }
        contentPanel->layout()->addWidget(p);

        if (femaleSocket->isConnected()) {
            _systemName->setText(femaleSocket->getConnectedSocket()->getSystemName());
            _systemName->setEnabled(false);
            _addUserName->setText(femaleSocket->getConnectedSocket()->getUserName());
        } else {
            _systemName->setText("");
            _systemName->setEnabled(true);
            _addUserName->setText("");
        }

        // set up message
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));

        // set up create and cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());

        Base* object = nullptr;

        // Get panel for the item
        _swingConfiguratorInterfaceList.clear();
        QList<JPanel*> panels = QList<JPanel*>();
        if (femaleSocket->isConnected()) {
            object = femaleSocket->getConnectedSocket();
            while (qobject_cast<MaleSocket*>(object->self())) {
                SwingConfiguratorInterface* swi =
                        SwingTools::getSwingConfiguratorForClass((Class*)object->self());
                panels.append(swi->getConfigPanel(object, panel5));
                QMap<SwingConfiguratorInterface*, Base*> entry;
                entry.insert(swi, object);
                _swingConfiguratorInterfaceList.append(entry);
                object = ((MaleSocket*)object->self())->getObject();
            }
            if (object != nullptr) {
                _editSwingConfiguratorInterface =
                        SwingTools::getSwingConfiguratorForClass((Class*)object);
                panels.append(_editSwingConfiguratorInterface->getConfigPanel(object, panel5));
                QMap<SwingConfiguratorInterface*, Base*> entry;
                entry.insert(_editSwingConfiguratorInterface, object);

                _swingConfiguratorInterfaceList.append(entry);
            } else {
                // 'object' should be an action or expression but is null
                JPanel* panel = new JPanel();
                panel->layout()->addWidget(new JLabel("Error: femaleSocket->getConnectedSocket().getObject().getObject()....getObject() doesn't return a non MaleSocket"));
                panels.append(panel);
                log->error("femaleSocket->getConnectedSocket().getObject().getObject()....getObject() doesn't return a non MaleSocket");
            }
        } else {
            /*Class<? extends MaleSocket>*/QString maleSocketClass =
                    _addSwingConfiguratorInterface->getManager()->getMaleSocketClass();
#if 0
            _addSwingConfiguratorInterfaceMaleSocket =
                    SwingTools::getSwingConfiguratorForClass(maleSocketClass);
#endif
            panels.append(_addSwingConfiguratorInterfaceMaleSocket->getConfigPanel(panel5));

            panels.append(_addSwingConfiguratorInterface->getConfigPanel(panel5));
        }
        JPanel* panel34 = new JPanel();
        panel34->setLayout(new QVBoxLayout());//panel34, BoxLayout.Y_AXIS));
        for (int i = panels.size()-1; i >= 0; i--) {
            JPanel* panel = panels.at(i);
            //if (panel->getComponentCount() > 0)
            if(panel->children().count()>0)
            {
                panel34->layout()->addWidget(Box::createVerticalStrut(30));
                panel34->layout()->addWidget(panel);
            }
        }
        panel3->layout()->addWidget(panel34);
        contentPanel->layout()->addWidget(panel3);

        // Edit comment
        JButton* editComment = new JButton(tr("EditComment"));    // NOI18N
        panel5->layout()->addWidget(editComment);
        QString comment = object != nullptr ? object->getComment() : "";
        connect(editComment, &JButton::clicked, [=] {
         EditCommentDialog* dlg = new EditCommentDialog();
//            commentStr= dlg->showDialog(comment);
        });

        // Function help
        JButton* showFunctionHelp = new JButton(tr("FunctionHelp"));    // NOI18N
        panel5->layout()->addWidget(showFunctionHelp);
        connect(showFunctionHelp, &JButton::clicked, [=] {
            ((FunctionsHelpDialog*)InstanceManager::getDefault("FunctionsHelpDialog"))->showDialog();
        });
//        showFunctionHelp->setToolTip("FunctionHelpButtonHint");      // NOI18N

        // Cancel
        JButton* cancel = new JButton(tr("Cancel"));    // NOI18N
        panel5->layout()->addWidget(cancel);
        connect(cancel, &JButton::clicked, [=] {
            if (!femaleSocket->isConnected()) {
                cancelCreateItem(nullptr);
            } else {
                cancelEditPressed(nullptr);
            }
        });
//        cancel->setToolTip(Bundle.getMessage("Press to return to Logix Table without any changes"));      // NOI18N
        cancel->setToolTip("Press to return to Logix Table without any changes");      // NOI18N

        panel5->layout()->addWidget(button);
#if 0
        frame.addWindowListener(new java.awt.event.WindowAdapter() {
            //@Override
            /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
                if (addOrEdit) {
                    cancelCreateItem(null);
                } else {
                    cancelEditPressed(null);
                }
            }
        });
#endif
        contentPanel->layout()->addWidget(panel5);

        connect(_autoSystemName, &JButton::clicked, [=] {
            autoSystemName();
        });
//        addLogixNGFrame.setLocationRelativeTo(component);
        frame->pack();
        frame->setLocationRelativeTo(nullptr);

        if (addOrEdit) {
            _addItemDialog = frame;
        } else {
            _editActionExpressionDialog = frame;
        }

        _autoSystemName->setSelected(true);
        UserPreferencesManager* prefMgr =((UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager"));
        if(prefMgr)
        {
            _autoSystemName->setSelected(prefMgr->getCheckboxPreferenceState(_systemNameAuto, true));
        }//);

        frame->setVisible(true);
    }

    /**
     * Respond to the Local Variables menu choice in the popup menu.
     *
     * @param femaleSocket the female socket
     * @param path the path to the item the user has clicked on
     */
    /*final*/ /*protected*/ void TreeEditor::editLocalVariables(FemaleSocket* femaleSocket, TreePath* path) {
        // possible change
        _showReminder = true;
        // make an Edit Frame
        if (_editLocalVariablesDialog == nullptr) {
            MaleSocket* maleSocket = femaleSocket->getConnectedSocket();

            // Edit ConditionalNG
            _edit = new JButton(tr("OK"));  // NOI18N
            connect(_edit, &JButton::clicked, [=] {
                QList<QString> errorMessages = QList<QString>();
                bool hasErrors = false;
                for (VariableData v : _localVariableTableModel->getVariables()) {
                    if (v.getName().isEmpty()) {
                        errorMessages.add(Bundle.getMessage("VariableNameIsEmpty", v.getName()));
                        hasErrors = true;
                    }
                    if (! SymbolTable.validateName(v.getName())) {
                        errorMessages.add(Bundle.getMessage("VariableNameIsNotValid", v.getName()));
                        hasErrors = true;
                    }
                }

                if (hasErrors) {
                    StringBuilder errorMsg = new StringBuilder();
                    for (String s : errorMessages) {
                        if (errorMsg.length() > 0) errorMsg.append("<br>");
                        errorMsg.append(s);
                    }
                    JOptionPane.showMessageDialog(null,
                            Bundle.getMessage("ValidateErrorMessage", errorMsg),
                            Bundle.getMessage("ValidateErrorTitle"),
                            JOptionPane.ERROR_MESSAGE);

                } else {
                    _treePane._femaleRootSocket.unregisterListeners();

                    runOnConditionalNGThreadOrGUIThreadEventually(
                            _treePane._femaleRootSocket.getConditionalNG(),
                            () -> {

                        maleSocket.clearLocalVariables();
                        for (SymbolTable.VariableData variableData : _localVariableTableModel.getVariables()) {
                            maleSocket.addLocalVariable(variableData);
                        }

                        ThreadingUtil.runOnGUIEventually(() -> {
                            _editLocalVariablesDialog.dispose();
                            _editLocalVariablesDialog = null;
                            if (_treePane._femaleRootSocket.isActive()) {
                                _treePane._femaleRootSocket.registerListeners();
                            }
                            for (TreeModelListener l : _treePane.femaleSocketTreeModel.listeners) {
                                TreeModelEvent tme = new TreeModelEvent(
                                        femaleSocket,
                                        path.getPath()
                                );
                                l.treeNodesChanged(tme);
                            }
                            _treePane._tree.updateUI();
                        });
                    });
                }
            });
//            _edit->setToolTip(Bundle.getMessage("EditButtonHint"));  // NOI18N

//            makeAddEditFrame(false, femaleSocket, _editSwingConfiguratorInterface, _edit);  // NOI18N

            _editLocalVariablesDialog = new JDialog(
                    this,
                    Bundle.getMessage(
                            "EditLocalVariablesDialogTitle",
                            femaleSocket->getLongDescription()),
                    true);
    //        frame.addHelpMenu(
    //                "package.jmri.jmrit.logixng.tools.swing.ConditionalNGAddEdit", true);     // NOI18N
            Container contentPanel = _editLocalVariablesDialog.getContentPane();
            contentPanel.setLayout(new BoxLayout(contentPanel, BoxLayout.Y_AXIS));

            JPanel* tablePanel = new JPanel();
            JTable table = new JTable();
            _localVariableTableModel = new LocalVariableTableModel(maleSocket);
            table.setModel(_localVariableTableModel);
            table.setDefaultRenderer(InitialValueType.class,
                    new LocalVariableTableModel.TypeCellRenderer());
            table.setDefaultEditor(InitialValueType.class,
                    new LocalVariableTableModel.TypeCellEditor());
            table.setDefaultRenderer(LocalVariableTableModel.Menu.class,
                    new LocalVariableTableModel.MenuCellRenderer());
            table.setDefaultEditor(LocalVariableTableModel.Menu.class,
                    new LocalVariableTableModel.MenuCellEditor(table, _localVariableTableModel));
            _localVariableTableModel.setColumnForMenu(table);
            JScrollPane scrollpane = new JScrollPane(table);
            scrollpane.setPreferredSize(new Dimension(400, 200));
            tablePanel.add(scrollpane, BorderLayout.CENTER);
            contentPanel->layout()->addWidget(tablePanel);

            // set up create and cancel buttons
            JPanel* buttonPanel = new JPanel();
            buttonPanel.setLayout(new FlowLayout());

            // Function help
            JButton* showFunctionHelp = new JButton(tr("FunctionHelp"));    // NOI18N
            buttonPanel.add(showFunctionHelp);
            showFunctionHelpLayout->addWidgetActionListener((ActionEvent e) -> {
                InstanceManager.getDefault(FunctionsHelpDialog.class).showDialog();
            });
//            showFunctionHelp->setToolTip("FunctionHelpButtonHint");      // NOI18N

            // Add local variable
            JButton* add = new JButton(Bundle.getMessage("TableAddVariable"));
            buttonPanel.add(add);
            add.addActionListener((ActionEvent e) -> {
                _localVariableTableModel.add();
            });

            // Cancel
            JButton* cancel = new JButton(tr("Cancel"));    // NOI18N
            buttonPanel.add(cancel);
            connect(cancel, &JButton::clicked, [=] {
                _editLocalVariablesDialog.setVisible(false);
                _editLocalVariablesDialog.dispose();
                _editLocalVariablesDialog = null;
            });
    //        cancel->setToolTip(Bundle.getMessage("Press to return to Logix Table without any changes"));      // NOI18N
            cancel->setToolTip("Press to return to Logix Table without any changes");      // NOI18N

            buttonPanel.add(_edit);

            _editLocalVariablesDialog.addWindowListener(new java.awt.event.WindowAdapter() {
                //@Override
                /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
                    _editLocalVariablesDialog.setVisible(false);
                    _editLocalVariablesDialog.dispose();
                    _editLocalVariablesDialog = null;
                }
            });

            contentPanel->layout()->addWidget(buttonPanel);

            connect(_autoSystemName, &JButton::clicked, [=] {
                autoSystemName();
            });
    //        addLogixNGFrame.setLocationRelativeTo(component);
            _editLocalVariablesDialog.pack();
            _editLocalVariablesDialog.setLocationRelativeTo(null);

            _editLocalVariablesDialog.setVisible(true);
        }
    }

    /**
     * Respond to the Change user name menu choice in the popup menu.
     *
     * @param femaleSocket the female socket
     * @param path the path to the item the user has clicked on
     */
    /*final*/ /*protected*/ void TreeEditor::changeUsername(FemaleSocket* femaleSocket, TreePath* path) {
        // possible change
        _showReminder = true;
        // make an Edit Frame
        if (_changeUsernameDialog == null) {
            MaleSocket maleSocket = femaleSocket->getConnectedSocket();

            // Edit ConditionalNG
            _edit = new JButton(tr("OK"));  // NOI18N
            _edit.addActionListener((ActionEvent e) -> {

                bool hasErrors = false;
                if (hasErrors) {
                    String errorMsg = "";
                    JOptionPane.showMessageDialog(null,
                            Bundle.getMessage("ValidateErrorMessage", errorMsg),
                            Bundle.getMessage("ValidateErrorTitle"),
                            JOptionPane.ERROR_MESSAGE);

                } else {
                    _treePane._femaleRootSocket.unregisterListeners();

                    runOnConditionalNGThreadOrGUIThreadEventually(
                            _treePane._femaleRootSocket.getConditionalNG(),
                            () -> {

                        String username = _usernameField->text();
                        if (username.equals("")) username = null;

                        // Only change user name if it's changed
                        if (((username == null) && (maleSocket.getUserName() != null))
                                || ((username != null) && !username.equals(maleSocket.getUserName()))) {

                            if (username != null) {
                                NamedBean nB = maleSocket.getManager().getByUserName(username);
                                if (nB != null) {
                                    String uname = username;
                                    ThreadingUtil.runOnGUIEventually(() -> {
                                        log.error("User name is not unique {}", uname);
                                        String msg = Bundle.getMessage("WarningUserName", new Object[]{("" + uname)});
                                        JOptionPane.showMessageDialog(null, msg,
                                                Bundle.getMessage("WarningTitle"),
                                                JOptionPane.ERROR_MESSAGE);
                                    });
                                    username = null;
                                }
                            }

                            maleSocket.setUserName(username);

                            MaleSocket m = maleSocket;
                            while (! (m instanceof NamedBean)) m = (MaleSocket) m.getObject();

                            NamedBeanHandleManager nbMan = InstanceManager.getDefault(NamedBeanHandleManager.class);
                            if (nbMan.inUse(maleSocket.getSystemName(), (NamedBean)m)) {
                                String msg = Bundle.getMessage("UpdateToUserName", new Object[]{maleSocket.getManager().getBeanTypeHandled(), username, maleSocket.getSystemName()});
                                int optionPane = JOptionPane.showConfirmDialog(null,
                                        msg, Bundle.getMessage("UpdateToUserNameTitle"),
                                        JOptionPane.YES_NO_OPTION);
                                if (optionPane == JOptionPane.YES_OPTION) {
                                    //This will update the bean reference from the systemName to the userName
                                    try {
                                        nbMan.updateBeanFromSystemToUser((NamedBean)m);
                                    } catch (JmriException ex) {
                                        //We should never get an exception here as we already check that the username is not valid
                                        log.error("Impossible exception setting user name", ex);
                                    }
                                }
                            }
                        }

                        ThreadingUtil.runOnGUIEventually(() -> {
                            if (_treePane._femaleRootSocket.isActive()) {
                                _treePane._femaleRootSocket.registerListeners();
                            }
                            _changeUsernameDialog.dispose();
                            _changeUsernameDialog = null;
                            for (TreeModelListener l : _treePane.femaleSocketTreeModel.listeners) {
                                TreeModelEvent tme = new TreeModelEvent(
                                        femaleSocket,
                                        path.getPath()
                                );
                                l.treeNodesChanged(tme);
                            }
                            _treePane._tree.updateUI();
                        });
                    });
                }
            });
//            _edit->setToolTip(Bundle.getMessage("EditButtonHint"));  // NOI18N

//            makeAddEditFrame(false, femaleSocket, _editSwingConfiguratorInterface, _edit);  // NOI18N

            _changeUsernameDialog = new JDialog(
                    this,
                    Bundle.getMessage(
                            "EditLocalVariablesDialogTitle",
                            femaleSocket->getLongDescription()),
                    true);
    //        frame.addHelpMenu(
    //                "package.jmri.jmrit.logixng.tools.swing.ConditionalNGAddEdit", true);     // NOI18N
            Container contentPanel = _changeUsernameDialog.getContentPane();
            contentPanel.setLayout(new BoxLayout(contentPanel, BoxLayout.Y_AXIS));

//            JPanel* tablePanel = new JPanel();

            JLabel usernameLabel = new JLabel("Username");
            _usernameField.setText(maleSocket.getUserName());

            contentPanel->layout()->addWidget(usernameLabel);
            contentPanel->layout()->addWidget(_usernameField);

            // set up create and cancel buttons
            JPanel* buttonPanel = new JPanel();
            buttonPanel.setLayout(new FlowLayout());

            // Cancel
            JButton* cancel = new JButton(tr("Cancel"));    // NOI18N
            buttonPanel.add(cancel);
            connect(cancel, &JButton::clicked, [=] {
                _changeUsernameDialog.setVisible(false);
                _changeUsernameDialog.dispose();
                _changeUsernameDialog = null;
            });
    //        cancel->setToolTip(Bundle.getMessage("Press to return to Logix Table without any changes"));      // NOI18N
            cancel->setToolTip("Press to return to Logix Table without any changes");      // NOI18N

            buttonPanel.add(_edit);

            _changeUsernameDialog.addWindowListener(new java.awt.event.WindowAdapter() {
                //@Override
                /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
                    _changeUsernameDialog.setVisible(false);
                    _changeUsernameDialog.dispose();
                    _changeUsernameDialog = null;
                }
            });

            contentPanel->layout()->addWidget(buttonPanel);

            connect(_autoSystemName, &JButton::clicked, [=] {
                autoSystemName();
            });
    //        addLogixNGFrame.setLocationRelativeTo(component);
            _changeUsernameDialog->pack();
            _changeUsernameDialog->setLocationRelativeTo(nullptr);

            _changeUsernameDialog->setVisible(true);
        }
    }

    /**
     * Enable/disable fields for data entry when user selects to have system
     * name automatically generated.
     */
    /*final*/ /*protected*/ void TreeEditor::autoSystemName() {
        if (_autoSystemName->isSelected()) {
            _systemName->setEnabled(false);
            _sysNameLabel->setEnabled(false);
        } else {
            _systemName->setEnabled(true);
            _sysNameLabel->setEnabled(true);
        }
    }

    /**
     * Respond to the Cancel button in Rename socket window.
     * <p>
     * Note: Also get there if the user closes the Rename socket window.
     *
     * @param e The event heard
     */
    /*final*/ /*protected*/ void TreeEditor::cancelRenameSocketPressed(JActionEvent* e) {
        _renameSocketDialog->setVisible(false);
        _renameSocketDialog->dispose();
        _renameSocketDialog = nullptr;
        this->setVisible(true);
    }

    /**
     * Respond to the Cancel button in Add ConditionalNG window.
     * <p>
     * Note: Also get there if the user closes the Add ConditionalNG window.
     *
     * @param e The event heard
     */
    /*final*/ /*protected*/ void TreeEditor::cancelAddPressed(JActionEvent* e) {
        _selectItemTypeDialog->setVisible(false);
        _selectItemTypeDialog->dispose();
        _selectItemTypeDialog = nullptr;
//        _inCopyMode = false;
        this->setVisible(true);
    }

    /**
     * Respond to the Cancel button in Add ConditionalNG window.
     * <p>
     * Note: Also get there if the user closes the Add ConditionalNG window.
     *
     * @param e The event heard
     */
    /*final*/ /*protected*/ void TreeEditor::cancelCreateItem(JActionEvent* e) {
        _addItemDialog.setVisible(false);
        _addSwingConfiguratorInterface->dispose();
        _addItemDialog->dispose();
        _addItemDialog = nullptr;
//        _inCopyMode = false;
        this->setVisible(true);
    }


    /**
     * Respond to the Cancel button in Add ConditionalNG window.
     * <p>
     * Note: Also get there if the user closes the Add ConditionalNG window.
     *
     * @param e The event heard
     */
    /*final*/ /*protected*/ void TreeEditor::cancelEditPressed(JActionEvent* e) {
        _editActionExpressionDialog->setVisible(false);
//        _editSwingConfiguratorInterface.dispose();
        QMapIterator<SwingConfiguratorInterface*, Base*> entry (_swingConfiguratorInterfaceList);
        while(entry.hasNext()){
         entry.next();
            entry.key()->dispose();
//            entry.getKey().updateObject(entry.getValue());
//        for (SwingConfiguratorInterface swi : _swingConfiguratorInterfaceList) {
//            swi.dispose();
        }
        _editActionExpressionDialog->dispose();
        _editActionExpressionDialog = null;
//        _inCopyMode = false;
        this.setVisible(true);
    }


    /*protected*/ void TreeEditor::executeEvaluate(SwingConfiguratorInterface* swi, MaleSocket* maleSocket) {
        swi->executeEvaluate(maleSocket);
    }



 //   /*private*/ static /*final*/ class SortedComboBoxModel<E> extends DefaultComboBoxModel<E> {

//        /*private*/ /*final*/ Comparator<E> comparator;

        /*
         *  Create an empty model that will use the specified Comparator
         */
//        /*public*/  TreeEditor::SortedComboBoxModel::SortedComboBoxModel(/*@Nonnull*/ Comparator/*<E>*/* comparator) {
//            //super();
//            this->comparator = comparator;
//        }

        //@Override
        /*public*/  void TreeEditor::SortedComboBoxModel::addElement(QString element) {
            insertElementAt(element, 0);
        }

        //@SuppressWarnings("unchecked")
        //@Override
        /*public*/  void TreeEditor::SortedComboBoxModel::insertElementAt(QString element, int index) {
            int size = getSize();

            //  Determine where to insert element to keep model in sorted order
            int i = 0;
            for (; i < size; i++) {
                QVariant o = getElementAt(i);

                if (comparator->compare(o, element) > 0) {
                    break;
                }
            }

            DefaultComboBoxModel::insertElementAt(element, i);

            //  Select an element when it is added to the beginning of the model
            if (i == 0 && element != nullptr) {
                setSelectedItem(element);
            }
        }
//    };


//    /*protected*/ class PopupMenu : QMenu //implements ActionListener {

        /*private*/ /*static*/ /*final*/ QString TreeEditor::PopupMenu::ACTION_COMMAND_RENAME_SOCKET = "rename_socket";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_ADD = "add";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_REMOVE = "remove";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_EDIT = "edit";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_CUT = "cut";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_COPY = "copy";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_PASTE = "paste";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_ENABLE = "enable";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_DISABLE = "disable";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_LOCK = "lock";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_UNLOCK = "unlock";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_LOCAL_VARIABLES = "local_variables";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_CHANGE_USERNAME = "change_username";
        /*private*/ /*static*/ /*final*/QString TreeEditor::PopupMenu::ACTION_COMMAND_EXECUTE_EVALUATE = "execute_evaluate";
//        /*private*/ static final String ACTION_COMMAND_EXPAND_TREE = "expandTree";



        TreeEditor::PopupMenu::PopupMenu(TreeEditor* editor) {
         this->editor = editor;
            if (editor->_treePane->_tree == nullptr) throw new IllegalArgumentException("_tree is null");
            _tree = editor->_treePane->_tree;
        }

        /*private*/ void TreeEditor::PopupMenu::init() {
            menuItemRenameSocket = new JMenuItem(tr("Rename Socket"),this);
            connect(menuItemRenameSocket, &JMenuItem::triggered, [=]{actionPerformed();});
            menuItemRenameSocket->setActionCommand(ACTION_COMMAND_RENAME_SOCKET);
            addAction(menuItemRenameSocket);
            addSeparator();
            menuItemAdd = new JMenuItem(tr("Add"),this);
            connect(menuItemAdd, &JMenuItem::triggered, [=]{actionPerformed();});
            menuItemAdd->setActionCommand(ACTION_COMMAND_ADD);
            addAction(menuItemAdd);
            addSeparator();
            menuItemEdit = new JMenuItem(tr("Edit"), this);
            connect(menuItemEdit, &JMenuItem::triggered, [=]{actionPerformed();});
            menuItemEdit->setActionCommand(ACTION_COMMAND_EDIT);
            addAction(menuItemEdit);
            menuItemRemove = new JMenuItem(tr("Remove"),this);
            connect(menuItemRemove, &JMenuItem::triggered, [=]{actionPerformed();});
            menuItemRemove->setActionCommand(ACTION_COMMAND_REMOVE);
            addAction(menuItemRemove);
            addSeparator();
            menuItemCut = new JMenuItem(tr("Cut"),this);
            connect(menuItemCut, &JMenuItem::triggered, [=]{actionPerformed();});
            menuItemCut->setActionCommand(ACTION_COMMAND_CUT);
            addAction(menuItemCut);
            menuItemCopy = new JMenuItem(tr("Copy"),this);
            connect(menuItemCopy, &JMenuItem::triggered, [=]{actionPerformed();});
            menuItemCopy->setActionCommand(ACTION_COMMAND_COPY);
            addAction(menuItemCopy);
            menuItemPaste = new JMenuItem(tr("Paste"),this);
            connect(menuItemPaste, &JMenuItem::triggered, [=]{actionPerformed();});
            menuItemPaste->setActionCommand(ACTION_COMMAND_PASTE);
            addAction(menuItemPaste);
            addSeparator();

            for (FemaleSocketOperation::TYPES oper : FemaleSocketOperation::values()) {
                JMenuItem* menuItem = new JMenuItem(FemaleSocketOperation::toString(oper),this);
                connect(menuItem, &JMenuItem::triggered, [=]{actionPerformed();});
                menuItem->setActionCommand(FemaleSocketOperation::TYPES::toString(oper));
                addAction(menuItem);
                menuItemFemaleSocketOperation.insert(oper, menuItem);
            }

            addSeparator();
            menuItemEnable = new JMenuItem(tr("Enable"),this);
            connect(menuItemEnable, &JMenuItem::triggered, [=]{actionPerformed();});
            menuItemEnable->setActionCommand(ACTION_COMMAND_ENABLE);
            addAction(menuItemEnable);
            menuItemDisable = new JMenuItem(tr("Disable"),this);
            connect(menuItemDisable, &JMenuItem::triggered, [=]{actionPerformed();});
            menuItemDisable->setActionCommand(ACTION_COMMAND_DISABLE);
            addAction(menuItemDisable);
            menuItemLock = new JMenuItem(tr("Lock"),this);
            connect(menuItemLock, &JMenuItem::triggered, [=]{actionPerformed();});
            menuItemLock->setActionCommand(ACTION_COMMAND_LOCK);
            addAction(menuItemLock);
            menuItemUnlock = new JMenuItem(tr("Unlock"),this);
            connect(menuItemUnlock, &JMenuItem::triggered, [=]{actionPerformed();});
            menuItemUnlock->setActionCommand(ACTION_COMMAND_UNLOCK);
            addAction(menuItemUnlock);

            addSeparator();
            menuItemLocalVariables = new JMenuItem(tr("Local Variables"),this);
            menuItemLocalVariables->addActionListener(this);
            menuItemLocalVariables->setActionCommand(ACTION_COMMAND_LOCAL_VARIABLES);
            addAction(menuItemLocalVariables);

            addSeparator();
            menuItemChangeUsername = new JMenuItem(tr("Change Username"), this);
            menuItemChangeUsername->addActionListener(this);
            menuItemChangeUsername->setActionCommand(ACTION_COMMAND_CHANGE_USERNAME);
            add(menuItemChangeUsername);

            if (editor->_enableExecuteEvaluate) {
                addSeparator();
                menuItemExecuteEvaluate = new JMenuItem(this);  // The text is set later
                menuItemExecuteEvaluate->addActionListener(this);
                menuItemExecuteEvaluate->setActionCommand(ACTION_COMMAND_EXECUTE_EVALUATE);
                addAction(menuItemExecuteEvaluate);
            }
/*
            addSeparator();
            menuItemExpandTree = new JMenuItem(Bundle.getMessage("PopupMenuExpandTree"));
            menuItemExpandTree.addActionListener(this);
            menuItemExpandTree.setActionCommand(ACTION_COMMAND_EXPAND_TREE);
            add(menuItemExpandTree);
*/
//            setOpaque(true);
//            setLightWeightPopupEnabled(true);

            /*final*/ PopupMenu* popupMenu = this;
#if 1 // TODO:
            _tree->addMouseListener(
                    new MouseAdapter() {

                        // On Windows, the popup is opened on mousePressed,
                        // on some other OS, the popup is opened on mouseReleased

                        //@Override
                        /*public*/  void mousePressed(MouseEvent e) {
                            openPopupMenu(e);
                        }

                        //@Override
                        /*public*/  void mouseReleased(MouseEvent e) {
                            openPopupMenu(e);
                        }

                        /*private*/ void openPopupMenu(MouseEvent e) {
                            if (e.isPopupTrigger() && !popupMenu.isVisible()) {
                                // Get the row the user has clicked on
                                TreePath path = _tree.getClosestPathForLocation(e.getX(), e.getY());
                                if (path != null) {
                                    // Check that the user has clicked on a row.
                                    Rectangle rect = _tree.getPathBounds(path);
                                    if ((e.getY() >= rect.y) && (e.getY() <= rect.y + rect.height)) {
                                        // Select the row the user clicked on
                                        _tree.setSelectionPath(path);

                                        FemaleSocket femaleSocket = (FemaleSocket) path.getLastPathComponent();
                                        showPopup(e.getX(), e.getY(), femaleSocket, path);
                                    }
                                }
                            }
                        }
                    }
   #endif
            );
        }

        /*private*/ void TreeEditor::PopupMenu::showPopup(int x, int y, FemaleSocket* femaleSocket, TreePath* path) {
            _currentFemaleSocket = femaleSocket;
            _currentPath = path;

            Clipboard* clipboard = ((LogixNG_Manager*)InstanceManager::getDefault("LogixNG_Manager"))->getClipboard();

            MaleSocket* topItem = clipboard->getTopItem();

            bool isConnected = femaleSocket->isConnected();
            bool canConnectFromClipboard =
                    topItem != nullptr
                    && femaleSocket->isCompatible(topItem)
                    && !femaleSocket->isAncestor(topItem);

            if (editor->_disableRootPopup
                    && (_currentFemaleSocket == editor->_treePane->_femaleRootSocket)) {
                JOptionPane::showMessageDialog(nullptr,
                        tr("The root item has no popup menu"),
                        tr("Information"),
                        JOptionPane::ERROR_MESSAGE);
                return;
            }
            bool disableForRoot = editor->_disableRootRemoveCutCopy
                    && (_currentFemaleSocket == editor->_treePane->_femaleRootSocket);

            bool isLocked = isConnected && femaleSocket->getConnectedSocket()->isLocked();

            Base* parent = femaleSocket->getParent();
            while ((parent != nullptr) && !(qobject_cast<MaleSocket*>(parent->self()))) {
                parent = parent->getParent();
            }
            bool parentIsLocked = (parent != nullptr) && ((MaleSocket*)parent->self())->isLocked();

            menuItemAdd->setEnabled(!isConnected && !parentIsLocked);
            menuItemRemove->setEnabled(isConnected && !isLocked && !parentIsLocked && !disableForRoot);
            menuItemEdit->setEnabled(isConnected && !isLocked);
            menuItemCut->setEnabled(isConnected && !isLocked && !parentIsLocked && !disableForRoot);
            menuItemCopy->setEnabled(isConnected && !disableForRoot);
            menuItemPaste->setEnabled(!isConnected && !parentIsLocked && canConnectFromClipboard);

            if (isConnected && !disableForRoot) {
                menuItemEnable->setEnabled(!femaleSocket->getConnectedSocket()->isEnabled() && !isLocked);
                menuItemDisable->setEnabled(femaleSocket->getConnectedSocket()->isEnabled() && !isLocked);
            } else {
                menuItemEnable->setEnabled(false);
                menuItemDisable->setEnabled(false);
            }

            for (FemaleSocketOperation::TYPES oper : FemaleSocketOperation::values()) {
                JMenuItem menuItem = menuItemFemaleSocketOperation.get(oper);
                menuItem.setEnabled(femaleSocket->isSocketOperationAllowed(oper) && !parentIsLocked);
            }

            std::atomic<bool> isAnyLocked (false);
            std::atomic<bool> isAnyUnlocked(false);

            _currentfemaleSocket->forEntireTree((item) -> {
                if (item instanceof MaleSocket) {
                    isAnyLocked.set(isAnyLocked.get() || ((MaleSocket)item).isLocked());
                    isAnyUnlocked.set(isAnyUnlocked.get() || !((MaleSocket)item).isLocked());
                }
            });
            menuItemLock->setEnabled(isAnyUnlocked);
            menuItemUnlock->setEnabled(isAnyLocked);

            menuItemLocalVariables->setEnabled(femaleSocket->isConnected() && !isLocked);

            menuItemChangeUsername->setEnabled(femaleSocket->isConnected() && !isLocked);

            if (editor->_enableExecuteEvaluate) {
                menuItemExecuteEvaluate->setEnabled(femaleSocket->isConnected());

                if (femaleSocket->isConnected()) {
                    Base* object = _currentFemaleSocket->getConnectedSocket();
                    if (object == nullptr) throw new NullPointerException("object is null");
                    while (qobject_cast<MaleSocket*>(object->self())) {
                        object = ((MaleSocket*)object->self())->getObject();
                    }
                    menuItemExecuteEvaluate->setText(
                            SwingTools::getSwingConfiguratorForClass(QString(object->self()->metaObject()->className()))
                                    ->getExecuteEvaluateMenuText());
                }
            }

            //show(_tree, x, y);
            exec(QCursor::pos());
        }

        /**
         * Asks the user if edit a system node.
         * @return true if not edit system node, else return false
         */
        /*private*/ bool TreeEditor::PopupMenu::abortEditAboutSystem(Base* b) {
            int result = JOptionPane::showConfirmDialog(
                    this,
                    tr("This node is owned and maintained by the system. Do you want to change it?"),
                    b->getLongDescription(),
                    JOptionPane::YES_NO_OPTION);

            return result == JOptionPane::NO_OPTION;
        }

        //@Override
        /*public*/  void TreeEditor::PopupMenu::actionPerformed(JActionEvent* e) {
            Base* parent = _currentFemaleSocket->getParent();
            while ((parent != nullptr) && !qobject_cast<MaleSocket*>(_currentFemaleSocket->getParent()->self())) {
                parent = parent->getParent();
            }
            bool parentIsSystem = (parent != nullptr) && ((MaleSocket*)parent->self())->isSystem();
            bool itemIsSystem = (_currentFemaleSocket->isConnected())
                    && _currentFemaleSocket->getConnectedSocket()->isSystem();

            switch (e.getActionCommand()) {
                case ACTION_COMMAND_RENAME_SOCKET:
                    if (parentIsSystem && abortEditAboutSystem(_currentfemaleSocket->getParent())) break;
                    renameSocketPressed(_currentFemaleSocket, _currentPath);
                    break;

                case ACTION_COMMAND_ADD:
                    if (parentIsSystem && abortEditAboutSystem(_currentfemaleSocket->getParent())) break;
                    addPressed(_currentFemaleSocket, _currentPath);
                    break;

                case ACTION_COMMAND_EDIT:
                    if (itemIsSystem && abortEditAboutSystem(_currentfemaleSocket->getConnectedSocket())) break;
                    editPressed(_currentFemaleSocket, _currentPath);
                    break;

                case ACTION_COMMAND_REMOVE:
                    if ((parentIsSystem || itemIsSystem) && abortEditAboutSystem(_currentfemaleSocket->getConnectedSocket())) break;
                    DeleteBeanWorker worker = new DeleteBeanWorker(_currentFemaleSocket, _currentPath);
                    worker.execute();
                    break;

                case ACTION_COMMAND_CUT:
                    if ((parentIsSystem || itemIsSystem) && abortEditAboutSystem(_currentfemaleSocket->getConnectedSocket())) break;

                    if (_currentfemaleSocket->isConnected()) {
                        _treePane._femaleRootSocket.unregisterListeners();

                        runOnConditionalNGThreadOrGUIThreadEventually(
                                _treePane._femaleRootSocket.getConditionalNG(),
                                () -> {
                            Clipboard clipboard =
                                    InstanceManager.getDefault(LogixNG_Manager.class).getClipboard();
                            List<String> errors = new ArrayList<>();
                            MaleSocket maleSocket = _currentfemaleSocket->getConnectedSocket();
                            _currentfemaleSocket->disconnect();
                            if (!clipboard.add(maleSocket, errors)) {
                                JOptionPane.showMessageDialog(this,
                                        String.join("<br>", errors),
                                        Bundle.getMessage("TitleError"),
                                        JOptionPane.ERROR_MESSAGE);
                            }
                            ThreadingUtil.runOnGUIEventually(() -> {
                                _treePane._femaleRootSocket.registerListeners();
                                _treePane.updateTree(_currentFemaleSocket, _currentPath.getPath());
                            });
                        });
                   } else {
                        log.error("_currentFemaleSocket is not connected");
                    }
                    break;

                case ACTION_COMMAND_COPY:
                    if ((parentIsSystem || itemIsSystem) && abortEditAboutSystem(_currentfemaleSocket->getConnectedSocket())) break;

                    if (_currentfemaleSocket->isConnected()) {
                        _treePane._femaleRootSocket.unregisterListeners();

                        runOnConditionalNGThreadOrGUIThreadEventually(
                                _treePane._femaleRootSocket.getConditionalNG(),
                                () -> {
                            Clipboard clipboard =
                                    InstanceManager.getDefault(LogixNG_Manager.class).getClipboard();
                            Map<String, String> systemNames = new HashMap<>();
                            Map<String, String> userNames = new HashMap<>();
                            try {
                                List<String> errors = new ArrayList<>();
                                if (!clipboard.add(
                                        (MaleSocket) _currentfemaleSocket->getConnectedSocket().getDeepCopy(systemNames, userNames),
                                        errors)) {
                                    JOptionPane.showMessageDialog(this,
                                            String.join("<br>", errors),
                                            Bundle.getMessage("TitleError"),
                                            JOptionPane.ERROR_MESSAGE);
                                }
                            } catch (JmriException ex) {
                                log.error("getDeepCopy thrown exception: {}", ex, ex);
                                ThreadingUtil.runOnGUIEventually(() -> {
                                    JOptionPane.showMessageDialog(null,
                                            "An exception has occured: "+ex.getMessage(),
                                            "An error has occured",
                                            JOptionPane.ERROR_MESSAGE);
                                });
                            }
                        });

                        _treePane._femaleRootSocket.registerListeners();
                    } else {
                        log.error("_currentFemaleSocket is not connected");
                    }
                    break;

                case ACTION_COMMAND_PASTE:
                    if (parentIsSystem && abortEditAboutSystem(_currentfemaleSocket->getParent())) break;

                    if (! _currentfemaleSocket->isConnected()) {
                        _treePane._femaleRootSocket.unregisterListeners();

                        runOnConditionalNGThreadOrGUIThreadEventually(
                                _treePane._femaleRootSocket.getConditionalNG(),
                                () -> {
                            Clipboard clipboard =
                                    InstanceManager.getDefault(LogixNG_Manager.class).getClipboard();
                            try {
                                _currentfemaleSocket->connect(clipboard.fetchTopItem());
                                List<String> errors = new ArrayList<>();
                                if (!_currentfemaleSocket->setParentForAllChildren(errors)) {
                                    JOptionPane.showMessageDialog(this,
                                            String.join("<br>", errors),
                                            Bundle.getMessage("TitleError"),
                                            JOptionPane.ERROR_MESSAGE);
                                }
                            } catch (SocketAlreadyConnectedException ex) {
                                log.error("item cannot be connected", ex);
                            }
                            ThreadingUtil.runOnGUIEventually(() -> {
                                _treePane._femaleRootSocket.registerListeners();
                                _treePane.updateTree(_currentFemaleSocket, _currentPath.getPath());
                            });
                        });
                    } else {
                        log.error("_currentFemaleSocket is connected");
                    }
                    break;

                case ACTION_COMMAND_ENABLE:
                    if (itemIsSystem && abortEditAboutSystem(_currentfemaleSocket->getConnectedSocket())) break;

                    _currentfemaleSocket->getConnectedSocket().setEnabled(true);
                    runOnConditionalNGThreadOrGUIThreadEventually(
                            _treePane._femaleRootSocket.getConditionalNG(),
                            () -> {
                        ThreadingUtil.runOnGUIEventually(() -> {
                            _treePane._femaleRootSocket.unregisterListeners();
                            _treePane.updateTree(_currentFemaleSocket, _currentPath.getPath());
                            _treePane._femaleRootSocket.registerListeners();
                        });
                    });
                    break;

                case ACTION_COMMAND_DISABLE:
                    if (itemIsSystem && abortEditAboutSystem(_currentfemaleSocket->getConnectedSocket())) break;

                    _currentfemaleSocket->getConnectedSocket().setEnabled(false);
                    runOnConditionalNGThreadOrGUIThreadEventually(
                            _treePane._femaleRootSocket.getConditionalNG(),
                            () -> {
                        ThreadingUtil.runOnGUIEventually(() -> {
                            _treePane._femaleRootSocket.unregisterListeners();
                            _treePane.updateTree(_currentFemaleSocket, _currentPath.getPath());
                            _treePane._femaleRootSocket.registerListeners();
                        });
                    });
                    break;

                case ACTION_COMMAND_LOCK:
                    if (itemIsSystem && abortEditAboutSystem(_currentfemaleSocket->getConnectedSocket())) break;

                    _currentfemaleSocket->forEntireTree((item) -> {
                        if (item instanceof MaleSocket) {
                            ((MaleSocket)item).setLocked(true);
                        }
                    });
                    _treePane.updateTree(_currentFemaleSocket, _currentPath.getPath());
                    break;

                case ACTION_COMMAND_UNLOCK:
                    if (itemIsSystem && abortEditAboutSystem(_currentfemaleSocket->getConnectedSocket())) break;

                    _currentfemaleSocket->forEntireTree((item) -> {
                        if (item instanceof MaleSocket) {
                            ((MaleSocket)item).setLocked(false);
                        }
                    });
                    _treePane.updateTree(_currentFemaleSocket, _currentPath.getPath());
                    break;

                case ACTION_COMMAND_LOCAL_VARIABLES:
                    if (itemIsSystem && abortEditAboutSystem(_currentfemaleSocket->getConnectedSocket())) break;
                    editLocalVariables(_currentFemaleSocket, _currentPath);
                    break;

                case ACTION_COMMAND_CHANGE_USERNAME:
                    if (itemIsSystem && abortEditAboutSystem(_currentfemaleSocket->getConnectedSocket())) break;
                    changeUsername(_currentFemaleSocket, _currentPath);
                    break;

                case ACTION_COMMAND_EXECUTE_EVALUATE:
                    Base object = _currentfemaleSocket->getConnectedSocket();
                    if (object == null) throw new NullPointerException("object is null");
                    while (object instanceof MaleSocket) {
                        object = ((MaleSocket)object).getObject();
                    }
                    SwingConfiguratorInterface swi =
                            SwingTools.getSwingConfiguratorForClass(object.getClass());
                    executeEvaluate(swi, _currentfemaleSocket->getConnectedSocket());
                    break;

/*
                case ACTION_COMMAND_EXPAND_TREE:
                    // jtree expand sub tree
                    // https://stackoverflow.com/questions/15210979/how-do-i-auto-expand-a-jtree-when-setting-a-new-treemodel
                    // https://www.tutorialspoint.com/how-to-expand-jtree-row-to-display-all-the-nodes-and-child-nodes-in-java
                    // To expand all rows, do this:
                    for (int i = 0; i < tree.getRowCount(); i++) {
                        tree.expandRow(i);
                    }

                    tree.expandPath(_currentPath);
                    tree.updateUI();
                    break;
*/
                default:
                    // Check if the action is a female socket operation
                    if (! checkFemaleSocketOperation(_currentFemaleSocket, parentIsSystem, itemIsSystem, e.getActionCommand())) {
                        log.error("e.getActionCommand() returns unknown value {}", e.getActionCommand());
                    }
            }
        }

        /*private*/ bool checkFemaleSocketOperation(
                FemaleSocket femaleSocket,
                bool parentIsSystem,
                bool itemIsSystem,
                String command) {

            for (FemaleSocketOperation oper : FemaleSocketOperation.values()) {
                if (oper.name().equals(command)) {
                    if ((parentIsSystem || itemIsSystem) && abortEditAboutSystem(femaleSocket->getParent())) return true;
                    femaleSocket->doSocketOperation(oper);
                    return true;
                }
            }
            return false;
        }
    }


    // This class is copied from BeanTableDataModel
    /*private*/ class DeleteBeanWorker extends SwingWorker<Void, Void> {

        /*private*/ final FemaleSocket _currentFemaleSocket;
        /*private*/ final TreePath _currentPath;
        MaleSocket _maleSocket;

        /*public*/  DeleteBeanWorker(FemaleSocket currentFemaleSocket, TreePath currentPath) {
            _currentFemaleSocket = currentFemaleSocket;
            _currentPath = currentPath;
            _maleSocket = _currentfemaleSocket->getConnectedSocket();
        }

        /*public*/  int getDisplayDeleteMsg() {
            return InstanceManager.getDefault(UserPreferencesManager.class).getMultipleChoiceOption(TreeEditor.class.getName(), "deleteInUse");
        }

        /*public*/  void setDisplayDeleteMsg(int boo) {
            InstanceManager.getDefault(UserPreferencesManager.class).setMultipleChoiceOption(TreeEditor.class.getName(), "deleteInUse", boo);
        }

        /*public*/  void doDelete() {
            try {
                _currentfemaleSocket->disconnect();

                _maleSocket.getManager().deleteBean(_maleSocket, "DoDelete");
            } catch (PropertyVetoException e) {
                //At this stage the DoDelete shouldn't fail, as we have already done a can delete, which would trigger a veto
                log.error(e.getMessage());
            }
        }

        /**
         * {@inheritDoc}
         */
        //@Override
        /*public*/  Void doInBackground() {
            _treePane._femaleRootSocket.unregisterListeners();

            StringBuilder message = new StringBuilder();
            try {
                _maleSocket.getManager().deleteBean(_maleSocket, "CanDelete");  // NOI18N
            } catch (PropertyVetoException e) {
                if (e.getPropertyChangeEvent().getPropertyName().equals("DoNotDelete")) { // NOI18N
                    log.warn(e.getMessage());
                    message.append(Bundle.getMessage(
                            "VetoDeleteBean",
                            ((NamedBean)_maleSocket.getObject()).getBeanType(),
                            ((NamedBean)_maleSocket.getObject()).getDisplayName(
                                    NamedBean.DisplayOptions.USERNAME_SYSTEMNAME),
                            e.getMessage()));
                    JOptionPane.showMessageDialog(null, message.toString(),
                            Bundle.getMessage("WarningTitle"),
                            JOptionPane.ERROR_MESSAGE);
                    return null;
                }
                message.append(e.getMessage());
            }
            List<String> listenerRefs = new ArrayList<>();
            _maleSocket.getListenerRefsIncludingChildren(listenerRefs);
            int count = listenerRefs.size();
            log.debug("Delete with {}", count);
            if (getDisplayDeleteMsg() == 0x02 && message.toString().isEmpty()) {
                doDelete();
            } else {
                final JDialog dialog = new JDialog();
                dialog.setTitle(Bundle.getMessage("WarningTitle"));
                dialog.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                JPanel* container = new JPanel();
                container.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
                container.setLayout(new BoxLayout(container, BoxLayout.Y_AXIS));
                if (count > 0) { // warn of listeners attached before delete

                    String prompt = _maleSocket.getChildCount() > 0 ? "DeleteWithChildrenPrompt" : "DeletePrompt";
                    JLabel question = new JLabel(Bundle.getMessage(
                            prompt,
                            ((NamedBean)_maleSocket.getObject())
                                    .getDisplayName(NamedBean.DisplayOptions.USERNAME_SYSTEMNAME)));
                    question.setAlignmentX(Component.CENTER_ALIGNMENT);
                    container.add(question);

                    ArrayList<String> tempListenerRefs = new ArrayList<>();

                    tempListenerRefs.addAll(listenerRefs);

                    if (tempListenerRefs.size() > 0) {
                        ArrayList<String> listeners = new ArrayList<>();
                        for (int i = 0; i < tempListenerRefs.size(); i++) {
                            if (!listeners.contains(tempListenerRefs.get(i))) {
                                listeners.add(tempListenerRefs.get(i));
                            }
                        }

                        message.append("<br>");
                        message.append(Bundle.getMessage("ReminderInUse", count));
                        message.append("<ul>");
                        for (int i = 0; i < listeners.size(); i++) {
                            message.append("<li>");
                            message.append(listeners.get(i));
                            message.append("</li>");
                        }
                        message.append("</ul>");

                        JEditorPane pane = new JEditorPane();
                        pane.setContentType("text/html");
                        pane.setText("<html>" + message.toString() + "</html>");
                        pane.setEditable(false);
                        JScrollPane jScrollPane = new JScrollPane(pane);
                        container.add(jScrollPane);
                    }
                } else {
                    String prompt = _maleSocket.getChildCount() > 0 ? "DeleteWithChildrenPrompt" : "DeletePrompt";
                    String msg = MessageFormat.format(Bundle.getMessage(prompt),
                            new Object[]{_maleSocket.getSystemName()});
                    JLabel question = new JLabel(msg);
                    question.setAlignmentX(Component.CENTER_ALIGNMENT);
                    container.add(question);
                }

                final JCheckBox remember = new JCheckBox(Bundle.getMessage("MessageRememberSetting"));
                remember.setFont(remember.getFont().deriveFont(10f));
                remember.setAlignmentX(Component.CENTER_ALIGNMENT);

                JButton* yesButton = new JButton(tr("Yes"));
                JButton* noButton = new JButton(tr("No"));
                JPanel* button = new JPanel();
                button.setAlignmentX(Component.CENTER_ALIGNMENT);
                button.add(yesButton);
                button.add(noButton);
                container.add(button);

                noButton.addActionListener((ActionEvent e) -> {
                    //there is no point in remembering this the user will never be
                    //able to delete a bean!
                    dialog.dispose();
                });

                yesButton.addActionListener((ActionEvent e) -> {
                    if (remember.isSelected()) {
                        setDisplayDeleteMsg(0x02);
                    }
                    doDelete();
                    dialog.dispose();
                });
                container.add(remember);
                container.setAlignmentX(Component.CENTER_ALIGNMENT);
                container.setAlignmentY(Component.CENTER_ALIGNMENT);
                dialog.getContentPane().add(container);
                dialog.pack();
                dialog.setLocation(
                        (Toolkit.getDefaultToolkit().getScreenSize().width) / 2 - dialog.getWidth() / 2,
                        (Toolkit.getDefaultToolkit().getScreenSize().height) / 2 - dialog.getHeight() / 2);
                dialog.setModal(true);
                dialog.setVisible(true);
            }
            if (_treePane._femaleRootSocket.isActive()) {
                _treePane._femaleRootSocket.registerListeners();
            }
            return null;
        }

        /**
         * {@inheritDoc} Minimal implementation to catch and log errors
         */
        //@Override
        /*protected*/ void done() {
            try {
                get();  // called to get errors
            } catch (InterruptedException | java.util.concurrent.ExecutionException e) {
                log.error("Exception while deleting bean", e);
            }
            _treePane.updateTree(_currentFemaleSocket, _currentPath.getPath());
        }
    }



    /*private*/ /*final*/ /*static*/ Logger TreeEditor::log =LoggerFactory::getLogger("TreeEditor");
