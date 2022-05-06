#include "logixngtableaction.h"
#include "logixngeditor.h"
#include "loggerfactory.h"
#include "gridbaglayout.h"
#include "defaultlogixngmanager.h"
#include "defaultlogixng.h"

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
///*public*/  class LogixNGTableAction extends AbstractLogixNGTableAction<LogixNG> {

    /**
     * Create a LogixNGTableAction instance.
     *
     * @param s the Action title, not the title of the resulting frame. Perhaps
     *          this should be changed?
     */
    /*public*/  LogixNGTableAction::LogixNGTableAction(QString s, QObject* parent) : AbstractLogixNGTableAction(s, parent){
        //super(s);
        setObjectName("LogixNGTableAction");
    }

    /**
     * Create a LogixNGTableAction instance with default title.
     */
    /*public*/  LogixNGTableAction::LogixNGTableAction(QObject* parent) : AbstractLogixNGTableAction(tr("LogixNG Table"), parent){
        //this(Bundle.getMessage("TitleLogixNGTable"));
        setObjectName("LogixNGTableAction");
    }

    //@Override
    /*protected*/ AbstractLogixNGEditor/*<LogixNG>*/* LogixNGTableAction::getEditor(BeanTableFrame/*<LogixNG>*/* f, BeanTableDataModel/*<LogixNG>*/* m, QString sName) {
        return new LogixNGEditor(f, m, sName);
    }

    //@Override
    /*protected*/ Manager/*<LogixNG>*/* LogixNGTableAction::getManager() {
        return (AbstractManager*)(DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");
    }

    //@Override
    /*protected*/ void LogixNGTableAction::setEnabled(NamedBean* logixNG, bool enable) {
        ((LogixNG*)logixNG->self())->setEnabled(enable);
    }

    //@Override
    /*protected*/ bool LogixNGTableAction::isEnabled(NamedBean* logixNG) {
        return ((LogixNG*)logixNG->self())->isEnabled();
    }

    //@Override
    /*protected*/ void LogixNGTableAction::enableAll(bool enable) {
        for (NamedBean* x : getManager()->getNamedBeanSet()) {
            ((LogixNG*)x->self())->setEnabled(enable);
        }
        m->fireTableDataChanged();
    }

    //@Override
    /*protected*/ NamedBean* LogixNGTableAction::createBean(QString userName) {
        LogixNG* logixNG = (DefaultLogixNG*) ((DefaultLogixNGManager*)
                InstanceManager::getDefault("LogixNG_Manager"))
                        ->createLogixNG(userName);
        logixNG->setEnabled(true);
        return logixNG;
    }

    //@Override
    /*protected*/ NamedBean* LogixNGTableAction::createBean(QString systemName, QString userName) {
        LogixNG* logixNG =(DefaultLogixNG*) ((DefaultLogixNGManager*)
                InstanceManager::getDefault("LogixNG_Manager"))
                        ->createLogixNG(systemName, userName);
        logixNG->setEnabled(true);
        return (NamedBean*)logixNG;
    }

    //@Override
    /*public*/  void LogixNGTableAction::deleteBean(NamedBean* logixNG) {
        ((LogixNG*)logixNG->self())->setEnabled(false);
        try {
            ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->deleteBean(logixNG, "DoDelete");
        } catch (PropertyVetoException* e) {
            //At this stage the DoDelete shouldn't fail, as we have already done a can delete, which would trigger a veto
            log->error(e->getMessage());
        }
    }

    //@Override
    /*protected*/ QString LogixNGTableAction::getBeanText(NamedBean* e) {
        QString writer;// = new StringWriter();
#if 1
        int mutableInt =0;
        ((DefaultLogixNG*)_curNamedBean->self())->printTree(_printTreeSettings, new PrintWriter(writer), "    ", &mutableInt);
#endif
        return writer;
    }

    //@Override
    /*protected*/ QString LogixNGTableAction::getAddTitleKey() {
        return "Add LogixNG";
    }

    //@Override
    /*protected*/ QString LogixNGTableAction::getCreateButtonHintKey() {
        return "Press to create a new LogixNG";
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
    /*protected*/ JPanel* LogixNGTableAction::makeAddFrame(QString titleId, QString startMessageId) {
        addLogixNGFrame = new JmriJFrame(/*Bundle.getMessage*/(titleId));
        addLogixNGFrame->addHelpMenu(
                "package.jmri.jmrit.beantable.LogixNGTable", true);     // NOI18N
        addLogixNGFrame->setLocation(50, 30);
        QWidget* contentPane = addLogixNGFrame->getContentPane();
        contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

        JPanel* p;
        p = new JPanel();
        //p->setLayout(new FlowLayout());
        GridBagLayout* pLayout;
        p->setLayout(pLayout =new GridBagLayout());
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
        _addUserName->setToolTip(tr("Enter user name for new LogixNG, e.g. Signal 2 Control"));    // NOI18N
        _systemName->setToolTip(tr("Enter system name for new LogixNG, e.g. IQ13"));   // NOI18N
        contentPane->layout()->addWidget(p);
        // set up message
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));
        JPanel* panel31 = new JPanel();
        panel31->setLayout(new FlowLayout());
        JLabel* message1 = new JLabel((startMessageId== "Add")?tr("Please enter system name and user name, then"):tr("Please enter System Name and User Name\n"));  // NOI18N
        panel31->layout()->addWidget(message1);
        JPanel* panel32 = new JPanel(new FlowLayout());
        JLabel* message2 = new JLabel((startMessageId== "Add")?tr("click [Create], then add ConditionalNG."):tr("of target LogixNG, then click [Copy]"));
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
        connect(cancel, &JButton::clicked, [=]{cancelAddPressed();});
        cancel->setToolTip(tr("Press to return to LogixNG Table without any changes"));      // NOI18N

//        addLogixNGFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//            //@Override
//            /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
//                cancelAddPressed(null);
//            }
//        });
         addLogixNGFrame->addWindowListener(new LNGTE_windowListener(this));
        contentPane->layout()->addWidget(panel5);

        connect(_autoSystemName, &JCheckBox::clicked, [=] {
            autoSystemName();
        });
        return panel5;
    }

    //@Override
    /*protected*/ void LogixNGTableAction::getListenerRefsIncludingChildren(NamedBean* logixNG,QList<QString> list) {
        ((DefaultLogixNG*)logixNG->self())->getListenerRefsIncludingChildren(list);
    }

    //@Override
    /*protected*/ bool LogixNGTableAction::hasChildren(NamedBean* logixNG) {
        return ((DefaultLogixNG*)logixNG->self())->getNumConditionalNGs() > 0;
    }

/*public*/ QString LogixNGTableAction::getClassDescription() {return  "LogixNG";}

/*private*/ /*final*/ /*static*/ Logger* LogixNGTableAction::log = LoggerFactory::getLogger("LogixNGTableAction");
