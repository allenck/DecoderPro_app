#include "logixngmoduletableaction.h"
#include "module.h"
#include "defaultmodulemanager.h"
#include "instancemanager.h"
#include "moduleeditor.h"
#include "stringwriter.h"
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include "loggerfactory.h"
#include "vptr.h"
#include "defaultfemalesocketmanager.h"

/**
 * Swing action to create and register a LogixNG Table.
 * <p>
 Also contains the panes to create, edit, and delete a LogixNG.
 <p>
 * Most of the text used in this GUI is in BeanTableBundle.properties, accessed
 * via Bundle.getMessage().
 * <p>
 *
 * @author Dave Duchamp Copyright (C) 2007 (LogixTableAction)
 * @author Pete Cressman Copyright (C) 2009, 2010, 2011 (LogixTableAction)
 * @author Matthew Harris copyright (c) 2009 (LogixTableAction)
 * @author Dave Sand copyright (c) 2017 (LogixTableAction)
 * @author Daniel Bergqvist copyright (c) 2019
 * @author Dave Sand copyright (c) 2021
 */
///*public*/  class LogixNGModuleTableAction extends AbstractLogixNGTableAction<jmri.jmrit.logixng.Module> {


    /**
     * Create a LogixNGTableAction instance.
     *
     * @param s the Action title, not the title of the resulting frame. Perhaps
     *          this should be changed?
     */
    /*public*/  LogixNGModuleTableAction::LogixNGModuleTableAction(QString s, QObject *parent) : AbstractLogixNGTableAction(s, parent) {
        //super(s);
        setObjectName("LogixNGModuleTableAction");
        _systemName->setEnabled(false);
        _sysNameLabel->setEnabled(false);

    }

    /**
     * Create a LogixNGTableAction instance with default title.
     */
    /*public*/  LogixNGModuleTableAction::LogixNGModuleTableAction(QObject *parent) : AbstractLogixNGTableAction(tr("LogixNGModule Table"), parent){
        //this(Bundle.getMessage("TitleLogixNGModuleTable"));
      setObjectName("LogixNGModuleTableAction");
    }

    //@Override
    /*protected*/ void LogixNGModuleTableAction::setTitle() {
        f->setTitle(tr("LogixNG ModuleTable"));
    }

    //@Override
    /*public*/  QString LogixNGModuleTableAction::getClassDescription() {
        return tr("LogixNG ModuleTable");        // NOI18N
    }

    //@Override
    /*protected*/ AbstractLogixNGEditor/*<Module>*/* LogixNGModuleTableAction::getEditor(BeanTableFrame/*<Module>*/* f, BeanTableDataModel/*<Module>*/* m, QString sName) {
        ModuleEditor* editor = new ModuleEditor(f, m, sName);
        editor->initComponents();
        return editor;
    }

    //@Override
    /*protected*/ Manager/*<Module>*/* LogixNGModuleTableAction::getManager() {
        return (DefaultModuleManager*)InstanceManager::getDefault("ModuleManager");
    }

    //@Override
    /*protected*/ void LogixNGModuleTableAction::enableAll(bool enable) {
        // Not used by the module table
    }

    //@Override
    /*protected*/ void LogixNGModuleTableAction::setEnabled(/*Module*/NamedBean* bean, bool enable) {
        // Not used by the module table
    }

    //@Override
    /*protected*/ bool LogixNGModuleTableAction::isEnabled(/*Module*/NamedBean* bean) {
        return true;
    }

    //@Override
    /*protected*/ /*Module*/NamedBean* LogixNGModuleTableAction::createBean(QString userName) {
        /*Module*/NamedBean* module = ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))
         ->createModule(userName, VPtr<FemaleSocketManager::SocketType>::asPtr(_femaleSocketType->getItemAt(_femaleSocketType->getSelectedIndex())));
        return module;
    }

    //@Override
    /*protected*/ /*Module*/NamedBean* LogixNGModuleTableAction::createBean(QString systemName, QString userName) {
        /*Module*/NamedBean* module = ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))
                ->createModule(systemName, userName,
                       VPtr<FemaleSocketManager::SocketType>::asPtr( _femaleSocketType->getItemAt(_femaleSocketType->getSelectedIndex())));
        return module;
    }

    //@Override
    /*protected*/ void LogixNGModuleTableAction::deleteBean(/*Module*/NamedBean* bean) {
        try {
            ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->deleteBean(bean, "DoDelete");
        } catch (PropertyVetoException* e) {
            //At this stage the DoDelete shouldn't fail, as we have already done a can delete, which would trigger a veto
            log->error(e->getMessage());
        }
    }

    //@Override
    /*protected*/ QString LogixNGModuleTableAction::getBeanText(NamedBean *bean) {
        StringWriter* writer = new StringWriter();
        int mutableInt = 0;
        ((AbstractBase*)_curNamedBean->self())->printTree(_printTreeSettings, new PrintWriter(writer), "    ", &mutableInt);
        return writer->toString();
    }

    //@Override
    /*protected*/ QString LogixNGModuleTableAction::getAddTitleKey() {
        return "Add LogixNG Module";
    }

    //@Override
    /*protected*/ QString LogixNGModuleTableAction::getCreateButtonHintKey() {
        return "Press to create a new LogixNG Module";
    }

    //@Override
    /*protected*/ QString LogixNGModuleTableAction::helpTarget() {
        return "package.jmri.jmrit.beantable.LogixNGModuleTable";  // NOI18N
    }

    /**
     * Create or copy bean frame.
     *
     * @param titleId   property key to fetch as title of the frame (using Bundle)
     * @param startMessageId part 1 of property key to fetch as user instruction on
     *                  pane, either 1 or 2 is added to form the whole key
     * @return the button JPanel
     */
    //@Override
    /*protected*/ JPanel* LogixNGModuleTableAction::makeAddFrame(QString titleId, QString startMessageId) {
        addLogixNGFrame = new JmriJFrame(/*Bundle.getMessage*/(titleId));
        addLogixNGFrame->addHelpMenu(
                "package.jmri.jmrit.beantable.LogixNGModuleTable", true);     // NOI18N
        addLogixNGFrame->setLocation(50, 30);
        JPanel* contentPane = addLogixNGFrame->getContentPane();
        contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

        QList<FemaleSocketManager::SocketType*> list
                = QList<FemaleSocketManager::SocketType*> {((DefaultFemaleSocketManager*)InstanceManager::getDefault("FemaleSocketManager"))->getSocketTypes().values()};
//        Collections.sort(list, (FemaleSocketManager.SocketType o1, FemaleSocketManager.SocketType o2) -> o1.getDescr().compareTo(o2.getDescr()));

        _femaleSocketType->clear();
        for (FemaleSocketManager::SocketType* socketType : list) {
            _femaleSocketType->addItem(socketType->getName(), VPtr<FemaleSocketManager::SocketType>::asQVariant(socketType));
            if ("DefaultFemaleDigitalActionSocket" == (socketType->getName())) {
                _femaleSocketType->setSelectedItem(VPtr<FemaleSocketManager::SocketType>::asQVariant(socketType));
            }
        }

        JPanel* p;
        p = new JPanel();
        //p->setLayout(new FlowLayout());
        GridBagLayout* pLayout;
        p->setLayout(pLayout = new GridBagLayout());
        GridBagConstraints c = GridBagConstraints();
        c.gridwidth = 1;
        c.gridheight = 1;
        c.gridx = 0;
        c.gridy = 0;
        c.anchor = GridBagConstraints::EAST;
        pLayout->addWidget(_sysNameLabel, c);
        _sysNameLabel->setLabelFor(_systemName);
        c.gridy = 1;
        pLayout->addWidget(_userNameLabel, c);
        _userNameLabel->setLabelFor(_addUserName);
        c.gridy = 2;
        pLayout->addWidget(new JLabel(tr("Socket type:")), c);
        c.gridx = 1;
        c.gridy = 0;
        c.anchor = GridBagConstraints::WEST;
        c.weightx = 1.0;
        c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
        pLayout->addWidget(_systemName, c);
        c.gridy = 1;
        pLayout->addWidget(_addUserName, c);
        c.gridy = 2;
        c.gridwidth = 2;
        pLayout->addWidget(_femaleSocketType, c);
        c.gridx = 2;
        c.gridy = 1;
        c.anchor = GridBagConstraints::WEST;
        c.weightx = 1.0;
        c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
        c.gridy = 0;
        pLayout->addWidget(_autoSystemName, c);
        _addUserName->setToolTip(tr("Enter user name for new LogixNG, e.g. Signal 2 Control"));    // NOI18N
        _systemName->setToolTip(tr("Enter user name for new LogixNG, e.g. Signal 2 Control"));   // NOI18N
        contentPane->layout()->addWidget(p);
        // set up message
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));
        JPanel* panel31 = new JPanel();
        panel31->setLayout(new FlowLayout());
        JLabel* message1 = new JLabel(startMessageId==tr("Add")? tr("Please enter system name and user name, then"): tr("Please enter System Name and User Name\n"));  // NOI18N
        panel31->layout()->addWidget(message1);
        JPanel* panel32 = new JPanel(new FlowLayout());
        JLabel* message2 = new JLabel(startMessageId==tr("Add")? tr("click [Create]."): tr("of target LogixNG Table, then click [Copy]"));  // NOI18N
        panel32->layout()->addWidget(message2);
        panel3->layout()->addWidget(panel31);
        panel3->layout()->addWidget(panel32);
        contentPane->layout()->addWidget(panel3);

        // set up create and cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());
        // Cancel
        JButton* cancel = new JButton(tr("Cancel"));    // NOI18N
        panel5->layout()->addWidget(cancel);
        connect(cancel, &JButton::clicked, [=] {cancelAddPressed();});
        cancel->setToolTip(tr("Press to return to Logix Table without any changes"));      // NOI18N

        addLogixNGFrame->addWindowListener(new LogixNGModuleTableAction_WindowListener(this));
//        {
//            //@Override
//            /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
//                cancelAddPressed(null);
//            }
//        });
        contentPane->layout()->addWidget(panel5);

        connect(_autoSystemName, &JCheckBox::clicked, [=] {
            autoSystemName();
        });
        return panel5;
    }

    //@Override
    /*protected*/ void LogixNGModuleTableAction::getListenerRefsIncludingChildren(/*Module*/NamedBean* module, QList<QString> list) {
        ((Module*)module->self())->getListenerRefsIncludingChildren(list);
    }

    //@Override
    /*protected*/ bool LogixNGModuleTableAction::hasChildren(NamedBean* module) {
        return ((Module*)module->self())->getRootSocket()->isConnected();
    }

    /*private*/ /*final*/ /*static*/ Logger* LogixNGModuleTableAction::log = LoggerFactory::getLogger("LogixNGModuleTableAction");
