#include "conditionalngdebugger.h"
#include "loggerfactory.h"
#include "treepane.h"
#include "femaledigitalactionsocket.h"
#include "jpanel.h"
#include "borderfactory.h"
#include <QMenuBar>
#include <QScrollArea>
#include "jtable.h"
#include <QSplitter>
#include "threadingutil.h"
#include "treemodellistener.h"
#include "treemodelevent.h"
#include "abstractdebuggermalesocket.h"
#include "logixng_thread.h"
#include "femalesocket.h"
#include "atomicboolean.h"

/**
 * Editor of ConditionalNG
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class ConditionalNGDebugger extends JmriJFrame implements PropertyChangeListener {



    /**
     * Construct a ConditionalEditor.
     *
     * @param conditionalNG the ConditionalNG to be edited
     */
    /*public*/  ConditionalNGDebugger::ConditionalNGDebugger(/*@Nonnull*/ ConditionalNG* conditionalNG, QWidget* parent) : JmriJFrame(parent){

        _conditionalNG = conditionalNG;

        _treePane = new TreePane((AbstractFemaleSocket*)conditionalNG->getFemaleSocket());
#if 0 // TODO:
        _treePane->initComponents(FemaleSocket* femaleSocket/*, JPanel* panel*/)  {

            if (femaleSocket->isConnected()) {
                MaleSocket* maleSocket = femaleSocket->getConnectedSocket();
                AbstractDebuggerMaleSocket* debugMaleSocket =
                        (AbstractDebuggerMaleSocket*) maleSocket->find("AbstractDebuggerMaleSocket");
                if (debugMaleSocket == nullptr) throw new RuntimeException("AbstractDebuggerMaleSocket is not found");
                bool breakpointBefore = debugMaleSocket->getBreakpointBefore();
                bool breakpointAfter = debugMaleSocket->getBreakpointAfter();
                if (breakpointBefore || breakpointAfter) {
                    JPanel* newPanel = new JPanel(new FlowLayout());
                    newPanel->setBorder(BorderFactory::createMatteBorder(
                            breakpointBefore ? 5 : 1,
                            5,
                            breakpointAfter ? 5 : 1,
                            1, Qt::red));
                    newPanel->layout()->addWidget(panel);
                    panel = newPanel;
                }
            }
            if (_currentMaleSocket != nullptr) {
                Base* parent = _currentMaleSocket->getParent();
                while ((parent != nullptr) && (!(qobject_cast<FemaleSocket*>(parent->self())))) {
                    parent = parent->getParent();
                }
                if (parent == femaleSocket) {
                    JPanel* newPanel = new JPanel();
                    switch (_currentState) {
                        case State::Before:
                            newPanel->setBorder(BorderFactory::createMatteBorder(8, 5, 1, 1, Qt::black));
                            break;
                        case State::After:
                            newPanel->setBorder(BorderFactory::createMatteBorder(1, 5, 8, 1, Qt::black));
                            break;
                        default:
                            // Return without adding a border
                            return panel;
                    }
                    newPanel->layout()->addWidget(panel);
                    return newPanel;
                }
            }
            return panel;
        });
#endif
        // build menu
        QMenuBar* menuBar = new QMenuBar();

        QMenu* fileMenu = new QMenu(tr("File"));
        JMenuItem* closeWindowItem = new JMenuItem(tr("Close Window"),this);
        connect(closeWindowItem, &JMenuItem::triggered, [=] {
            dispose();
        });
        fileMenu->addAction(closeWindowItem);
        menuBar->addMenu(fileMenu);

        QMenu* debugMenu = new QMenu(tr("Debug"));

        _runItem = new JMenuItem(tr("Run"), this);
        connect(_runItem, &JMenuItem::triggered, [=] { doRun(); });
//        _runItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F7, ActionEvent.CTRL_MASK));
        _runItem->setEnabled(false);
        debugMenu->addAction(_runItem);

        _stepOverItem = new JMenuItem(tr("StepOver"),this);
        connect(_stepOverItem, &JMenuItem::triggered, [=] { doStepOver(); });
//        _stepOverItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F7, ActionEvent.SHIFT_MASK));
        _stepOverItem->setEnabled(false);
        debugMenu->addAction(_stepOverItem);

        _stepIntoItem = new JMenuItem(tr("StepInto"),this);
        connect(_stepIntoItem, &JMenuItem::triggered, [=] { doStepInto(); });
//        _stepIntoItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F7, 0));
        _stepIntoItem->setEnabled(false);
        debugMenu->addAction(_stepIntoItem);

        menuBar->addMenu(debugMenu);

        setMenuBar(menuBar);
//        addHelpMenu("package.jmri.jmrit.operations.Operations_Settings", true); // NOI18N

        if (_conditionalNG->NamedBean::getUserName() == "") {
            setTitle(tr("Edit ConditionalNG %1").arg(_conditionalNG->NamedBean::getSystemName()));
        } else {
            setTitle(tr("Edit ConditionalNG %1 - %2").arg(_conditionalNG->NamedBean::getSystemName(), _conditionalNG->NamedBean::getUserName()));
        }


        JPanel* actionExpressionInfo = new JPanel(new QVBoxLayout());
        actionExpressionInfo->layout()->addWidget(_actionExpressionInfoLabel);
        QScrollArea* actionExpressionInfoScrollPane = new QScrollArea(/*actionExpressionInfo*/);
        actionExpressionInfoScrollPane->setWidget(actionExpressionInfo);
        actionExpressionInfoScrollPane->resize(QSize(400, 200));


        JPanel* symbolPanel = new JPanel(new QVBoxLayout());
        QScrollArea* variableScrollPane = new QScrollArea(/*symbolPanel*/);
        variableScrollPane->setWidget(symbolPanel);
        JTable* table = new JTable();
        _symbolTableModel = new DebuggerSymbolTableModel(_conditionalNG);
        table->setModel(_symbolTableModel);
        //JScrollPane scrollpane = new JScrollPane(table);
        /*scrollpane*/table->resize(QSize(400, 200));
        ((QVBoxLayout*)symbolPanel->layout())->addWidget(/*scrollpane*/table,1, Qt::AlignCenter); //BorderLayout.CENTER);


        QSplitter* variableSplitPane = new QSplitter(/*JSplitPane.VERTICAL_SPLIT*/Qt::Vertical);//,
//                           actionExpressionInfoScrollPane, variableScrollPane);
        variableSplitPane->addWidget(actionExpressionInfoScrollPane);
        variableSplitPane->addWidget(variableScrollPane);
//        variableSplitPane.setOneTouchExpandable(true);
//        variableSplitPane->setDividerLocation(50);


        JPanel* watchPanel = new JPanel(new QVBoxLayout());
        QScrollArea* watchScrollPane = new QScrollArea(/*watchPanel*/);
        watchScrollPane->setWidget(watchPanel);

        QSplitter* watchSplitPane = new QSplitter(/*JSplitPane.VERTICAL_SPLIT*/Qt::Vertical);//,
//                           variableSplitPane, watchScrollPane);
        watchSplitPane->addWidget(variableSplitPane);
        watchSplitPane->addWidget(watchScrollPane);
//        watchSplitPane.setOneTouchExpandable(true);
//        watchSplitPane.setDividerLocation(150);

        // Provide minimum sizes for the two components in the split pane
        QSize minimumWatchSize = QSize(100, 150);
        variableScrollPane->setMinimumSize(minimumWatchSize);
        watchScrollPane->setMinimumSize(minimumWatchSize);

        QSplitter* mainSplitPane = new QSplitter(Qt::Horizontal);// JSplitPane.HORIZONTAL_SPLIT,
//                           _treePane, watchSplitPane);
        mainSplitPane->addWidget(_treePane);
        mainSplitPane->addWidget(watchSplitPane);
//        mainSplitPane.setOneTouchExpandable(true);
//        mainSplitPane.setDividerLocation(150);

        // Provide minimum sizes for the two components in the split pane
        QSize minimumMainSize = QSize(100, 50);
        _treePane->setMinimumSize(minimumMainSize);
        watchSplitPane->setMinimumSize(minimumMainSize);

        // add panels
        getContentPane()->setLayout(new QVBoxLayout());//getContentPane(), BoxLayout.Y_AXIS));
        getContentPane()->layout()->addWidget(mainSplitPane);

        initMinimumSize(QSize(panelWidth, panelHeight));

        _debugger->addPropertyChangeListener(this);
        _debugger->setBreak(true);
        _debugger->activateDebugger(conditionalNG);

        PopupMenu* popup = new PopupMenu(this);
        popup->init();
    }

    /*private*/ void ConditionalNGDebugger::doStepOver() {
        AbstractDebuggerMaleSocket* maleSocket = _currentMaleSocket;
        if ((_currentState == State::After) && (_rootSocket == _currentMaleSocket)) {
            _run = false;
            _runItem->setEnabled(false);
        }
        _currentMaleSocket->setStepInto(false);
        _currentMaleSocket = nullptr;
        _currentState = State::None;
        _stepOverItem->setEnabled(false);
        _stepIntoItem->setEnabled(false);
        _treePane->updateTree(maleSocket);
        /*synchronized(_lock)*/ {
            _continue = true;
// TODO:           _lock->notify();
        }
    }

    /*private*/ void ConditionalNGDebugger::doStepInto() {
        AbstractDebuggerMaleSocket* maleSocket = _currentMaleSocket;
        if ((_currentState == State::After) && (_rootSocket == _currentMaleSocket)) {
            _run = false;
            _runItem->setEnabled(false);
        }
        _currentMaleSocket->setStepInto(true);
        _currentMaleSocket = nullptr;
        _currentState = State::None;
        _stepOverItem->setEnabled(false);
        _stepIntoItem->setEnabled(false);
        _treePane->updateTree(maleSocket);
        /*synchronized(_lock)*/ {
            _continue = true;
//            _lock->notify();
        }
    }

    /*private*/ void ConditionalNGDebugger::doRun() {
        _run = true;

        if (_currentMaleSocket != nullptr) {
            AbstractDebuggerMaleSocket* maleSocket = _currentMaleSocket;
            if ((_currentState == State::After) && (_rootSocket == _currentMaleSocket)) {
                _run = false;
                _runItem->setEnabled(false);
            }
            _currentMaleSocket->setStepInto(false);
            _currentMaleSocket = nullptr;
            _currentState = State::None;
            _stepOverItem->setEnabled(false);
            _stepIntoItem->setEnabled(false);
            _treePane->updateTree(maleSocket);
            /*synchronized(_lock)*/ {
//                _continue = true;
//                _lock->notify();
            }
        }
    }

    /*public*/  void ConditionalNGDebugger::initMinimumSize(QSize dimension) {
        setMinimumSize(dimension);
        pack();
        setVisible(true);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ConditionalNGDebugger::windowClosed(QCloseEvent* /*e*/) {
        doRun();    // Ensure the ConditionalNG is not waiting for us
        _debugger->removePropertyChangeListener(this);
        _debugger->deActivateDebugger();
        logixNGData.clear();
        logixNGData.insert("Finish", _conditionalNG->NamedBean::getSystemName());  // NOI18N
        fireLogixNGEvent();
    }

    /*public*/  void ConditionalNGDebugger::addLogixNGEventListener(ConditionalNGEventListener* listener) {
        listenerList.append(listener);
    }

    /**
     * Notify the listeners to check for new data.
     */
    void ConditionalNGDebugger::fireLogixNGEvent() {
        for (ConditionalNGEventListener* l : listenerList) {
            l->conditionalNGEventOccurred();
        }
    }

    //@Override
    /*public*/  void ConditionalNGDebugger::propertyChange(PropertyChangeEvent* evt) {
        if (Debugger::STEP_BEFORE == (evt->getPropertyName())
                || Debugger::STEP_AFTER == (evt->getPropertyName())) {

            QString infoString = "";
            _currentMaleSocket = VPtr<AbstractDebuggerMaleSocket>::asPtr( evt->getNewValue());
            if (_rootSocket == nullptr) _rootSocket = _currentMaleSocket;

//            System.out.format("propertyChange: %s, %s, run: %b, currentState: %s, BP before: %b, BP after: %b%n", evt.getPropertyName(), ((MaleSocket)evt.getNewValue()).getLongDescription(), _run, _currentState.name(), _currentMaleSocket.getBreakpointBefore(), _currentMaleSocket.getBreakpointAfter());
//            System.out.format("propertyChange: current: %s, root: %s%n", _currentMaleSocket, _rootSocket);

            //std::atomic<bool> enableMenuItems(true);
            AtomicBoolean* enableMenuItems = new AtomicBoolean(true);

            if(evt->getPropertyName() == Debugger::STEP_BEFORE)
            {
                    if (!_run || _currentMaleSocket->getBreakpointBefore()) {
                        _currentState = State::Before;
                    } else {
                        _currentState = State::None;
                    }
                    infoString = _currentMaleSocket->getBeforeInfo();
            }
            else if(evt->getPropertyName() ==  Debugger::STEP_AFTER)
            {
                    if (!_run || _currentMaleSocket->getBreakpointAfter()) {
                        _currentState = State::After;
                    } else {
                        if (_rootSocket == _currentMaleSocket) {
                            _run = false;
#if 0// TODO:
                            ThreadingUtil::runOnGUIEventually([=] () {
                                _runItem->setEnabled(false);
                                _stepOverItem->setEnabled(false);
                                _stepIntoItem->setEnabled(false);
                                enableMenuItems=(false);
                            });
#else
             ThreadingUtil::runOnGUIEventually(new CDRun1(enableMenuItems, this));
#endif
                        }
                        _currentState = State::None;
                    }
                    infoString = _currentMaleSocket->getAfterInfo();
            }
            else
                    _currentState = State::None;


            QMap<QString, Symbol*> symbols =
                    _conditionalNG->getSymbolTable()->getSymbols();

            QString infStr = infoString;
#if 0
            ThreadingUtil::runOnGUIEventually([=]() {
                if (enableMenuItems()) {
                    _runItem->setEnabled(true);
                    _stepOverItem->setEnabled(true);
                    _stepIntoItem->setEnabled(true);
                }
                _actionExpressionInfoLabel->setText(infStr);
                _treePane->updateTree(_currentMaleSocket);
                _symbolTableModel->update(symbols);
            });
#else
             ThreadingUtil::runOnGUIEventually( new CDRun2(enableMenuItems, infStr, symbols,this));
#endif

//            System.out.format("propertyChange middle: %s, %s, run: %b, currentState: %s%n", evt.getPropertyName(), ((MaleSocket)evt.getNewValue()).getLongDescription(), _run, _currentState.name());

            if (_currentState != State::None) {
                try {
                    /*synchronized(_lock)*/ {
                        _continue = false;
// TODO:                       while (!_continue) _lock->wait();
                    }
                } catch (InterruptedException e) {
                    log->error(tr("LogixNG thread was interrupted: %1").arg(_conditionalNG->getCurrentThread()->getThreadName()));
                    QThread::currentThread()->quit();
                }
            }

//            System.out.format("propertyChange done: %s, %s, run: %b, currentState: %s%n", evt.getPropertyName(), ((MaleSocket)evt.getNewValue()).getLongDescription(), _run, _currentState.name());
        }
    }
void CDRun1::run()
{
 cb->_runItem->setEnabled(false);
 cb->_stepOverItem->setEnabled(false);
 cb->_stepIntoItem->setEnabled(false);
 enableMenuItems->set(false);
}

void CDRun2::run()
{
 if (enableMenuItems) {
     cb->_runItem->setEnabled(true);
     cb->_stepOverItem->setEnabled(true);
     cb->_stepIntoItem->setEnabled(true);
 }
 cb->_actionExpressionInfoLabel->setText(infStr);
 cb->_treePane->updateTree(cb->_currentMaleSocket);
 cb->_symbolTableModel->update(symbols);
}
//    /*public*/  interface ConditionalNGEventListener extends EventListener {

//        /*public*/  void conditionalNGEventOccurred();
//    }


//    /*private*/ /*static*/ enum State {
//        None,
//        Before,
//        After,
//    }


//    /*protected*/ class PopupMenu : QMenu , public JActionListener {

        /*private*/ /*static*/ /*final*/ QString PopupMenu::ACTION_COMMAND_BREAKPOINT_BEFORE = "breakpoint_before";
        /*private*/ /*static*/ /*final*/ QString PopupMenu::ACTION_COMMAND_BREAKPOINT_AFTER = "breakpoint_after";
//        /*private*/ static /*final*/ String ACTION_COMMAND_EXPAND_TREE = "expandTree";

//        /*private*/ /*final*/ JTree _tree;
//        /*private*/ FemaleSocket _currentFemaleSocket;
//        /*private*/ TreePath _currentPath;

//        /*private*/ JMenuItem menuItemBreakpointBefore;
//        /*private*/ JMenuItem menuItemBreakpointAfter;
////        /*private*/ JMenuItem menuItemExpandTree;

        PopupMenu::PopupMenu(ConditionalNGDebugger* debugger) {
         this->debugger = debugger;
            if (debugger->_treePane->_tree == nullptr) throw new IllegalArgumentException("_tree is null");
            _tree = debugger->_treePane->_tree;

        }

        /*private*/ void PopupMenu::init() {
            menuItemBreakpointBefore = new JMenuItem(tr("Breakpoint before"),this);
            connect(menuItemBreakpointBefore, &JMenuItem::triggered, [=]{actionPerformed(new JActionEvent(menuItemBreakpointBefore));});
            menuItemBreakpointBefore->setActionCommand(ACTION_COMMAND_BREAKPOINT_BEFORE);
            addAction(menuItemBreakpointBefore);
            addSeparator();
            menuItemBreakpointAfter = new JMenuItem(tr("Breakpoint after"),this);
            connect(menuItemBreakpointAfter, &JMenuItem::triggered, [=]{actionPerformed(new JActionEvent(menuItemBreakpointAfter));});
            menuItemBreakpointAfter->setActionCommand(ACTION_COMMAND_BREAKPOINT_AFTER);
            addAction(menuItemBreakpointAfter);
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
#if 0 // TODO:
            _tree.addMouseListener(
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
                                        FemaleSocket femaleSocket = (FemaleSocket) path.getLastPathComponent();
                                        _tree.getLocationOnScreen();
                                        _tree.getX();
                                        showPopup(e.getX(), e.getY(), femaleSocket, path);
                                    }
                                }
                            }
                        }
                    }
            );
#endif
        }

        /*private*/ void PopupMenu::showPopup(int x, int y, FemaleSocket* femaleSocket, TreePath* path) {
            _currentFemaleSocket = femaleSocket;
            _currentPath = path;

            bool isConnected = femaleSocket->isConnected();

            menuItemBreakpointBefore->setEnabled(isConnected);
            menuItemBreakpointAfter->setEnabled(isConnected);

            //show(_tree, x, y);
            exec(QCursor::pos());
        }

        //@Override
        /*public*/  void PopupMenu::actionPerformed(JActionEvent* e)
        {
         if (e->getActionCommand() == ACTION_COMMAND_BREAKPOINT_BEFORE)
         {
          MaleSocket* maleSocket1 = _currentFemaleSocket->getConnectedSocket();
          AbstractDebuggerMaleSocket* debugMaleSocket1 =
                            (AbstractDebuggerMaleSocket*) maleSocket1->find("AbstractDebuggerMaleSocket")->bself();
          if (debugMaleSocket1 == nullptr) throw new RuntimeException("AbstractDebuggerMaleSocket is not found");
          // Invert breakpoint setting
          debugMaleSocket1->setBreakpointBefore(!debugMaleSocket1->getBreakpointBefore());
          for (TreeModelListener* l : debugger->_treePane->femaleSocketTreeModel->listeners) {
              QVector<QObject*>* ol= new QVector<QObject*>();
              foreach (QObject* o, *_currentPath->getPath()) ol->append(o);
              TreeModelEvent* tme = new TreeModelEvent(
                      _currentFemaleSocket->bself(),
//                      _currentPath->getPath(); //this list doesn' need tp be pointer!
                 ol
              );
              l->treeNodesChanged(tme);
          }
//          debugger->_treePane->_tree/*->updateUI()*/;
         }
            else if(e->getActionCommand() ==ACTION_COMMAND_BREAKPOINT_AFTER)
            {
                    MaleSocket* maleSocket2 = _currentFemaleSocket->getConnectedSocket();
                    AbstractDebuggerMaleSocket* debugMaleSocket2 =
                            (AbstractDebuggerMaleSocket*) maleSocket2->find("AbstractDebuggerMaleSocket")->bself();
                    if (debugMaleSocket2 == nullptr) throw new RuntimeException("AbstractDebuggerMaleSocket is not found");
                    // Invert breakpoint setting
                    debugMaleSocket2->setBreakpointAfter(!debugMaleSocket2->getBreakpointAfter());
                    for (TreeModelListener* l : debugger->_treePane->femaleSocketTreeModel->listeners) {
                     QVector<QObject*>* ol= new QVector<QObject*>();
                     foreach (QObject* o, *_currentPath->getPath()) ol->append(o);TreeModelEvent* tme = new TreeModelEvent(
                                _currentFemaleSocket->bself(),
//                                _currentPath->getPath()
                        ol
                        );
                        l->treeNodesChanged(tme);
                    }
//                    _treePane->_tree/*.updateUI()*/;
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
//                default:
                    // Do nothing
            }
        }
//    };


    /*private*/ /*final*/ /*static*/ Logger* ConditionalNGDebugger::log = LoggerFactory::getLogger("ConditionalNGDebugger");
