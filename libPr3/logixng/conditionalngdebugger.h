#ifndef CONDITIONALNGDEBUGGER_H
#define CONDITIONALNGDEBUGGER_H

#include <jmrijframe.h>
#include "instancemanager.h"
#include "jmenuitem.h"
#include "treepane.h"
#include "debugger.h"
#include "abstractdebuggermalesocket.h"
#include "jlabel.h"
#include "debuggersymboltablemodel.h"
#include "conditionalng.h"
#include "propertychangelistener.h"
#include "eventlistener.h"
#include <QMenu>
#include "actionlistener.h"
#include "threadingutil.h"
#include "symboltable.h"


class AtomicBoolean;
//class ConditionalNGEventListener;
class ConditionalNGDebugger : public JmriJFrame, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 public:
  ConditionalNGDebugger(ConditionalNG* conditionalNG, QWidget* parent = nullptr);
  /*public*/  void initMinimumSize(QSize dimension);
  /*public*/  void windowClosed(QCloseEvent* e);
  /*public*/  /*interface*/ class ConditionalNGEventListener : public EventListener {

     /*public*/ virtual  void conditionalNGEventOccurred()=0;
   friend class ConditionalNGDebugger;
  };
  /*public*/  void addLogixNGEventListener(ConditionalNGEventListener* listener);

 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;

 private:
  static Logger* log;
  /*private*/ static /*final*/const int panelWidth = 700;
  /*private*/ static /*final*/const int panelHeight = 500;

  /*private*/ /*final*/ Debugger* _debugger = (Debugger*)InstanceManager::getDefault("Debugger");
  /*private*/ /*final*/ TreePane* _treePane;
  /*private*/ /*final*/ JMenuItem* _runItem;
  /*private*/ /*final*/ JMenuItem* _stepOverItem;
  /*private*/ /*final*/ JMenuItem* _stepIntoItem;
  /*private*/ AbstractDebuggerMaleSocket* _currentMaleSocket;
  /*private*/ /*static*/ enum class State {
      None,
      Before,
      After,
  };
  /*private*/ State _currentState = State::None;
  /*private*/ bool _run = false;
  /*private*/ MaleSocket* _rootSocket;
  /*private*/ /*final*/ JLabel* _actionExpressionInfoLabel = new JLabel();

  /*private*/ /*final*/ QObject* _lock = new QObject();
  /*private*/ bool _continue = false;

  /*private*/ /*final*/ DebuggerSymbolTableModel* _symbolTableModel;

  /**
   * Maintain a list of listeners -- normally only one.
   */
  /*private*/ /*final*/ QList<ConditionalNGEventListener*> listenerList = QList<ConditionalNGEventListener*>();

  /**
   * This contains a list of commands to be processed by the listener
   * recipient.
   */
  /*final*/ QMap<QString, QString> logixNGData = QMap<QString, QString>();
  /*private*/ void doStepOver();
  /*private*/ void doStepInto();
  /*private*/ void doRun();
  void fireLogixNGEvent();

 protected:
  /*protected*/ /*final*/ ConditionalNG* _conditionalNG;
 friend class PopupMenu;
 friend class CDRun1;
 friend class CDRun2;
};

 /*protected*/ class PopupMenu : QMenu , public ActionListener {
  Q_OBJECT
   Q_INTERFACES(ActionListener)
     /*private*/ static /*final*/ QString ACTION_COMMAND_BREAKPOINT_BEFORE;// = "breakpoint_before";
     /*private*/ static /*final*/ QString ACTION_COMMAND_BREAKPOINT_AFTER;// = "breakpoint_after";
 //        /*private*/ static /*final*/ String ACTION_COMMAND_EXPAND_TREE = "expandTree";

     /*private*/ /*final*/ JTree* _tree;
     /*private*/ FemaleSocket* _currentFemaleSocket;
     /*private*/ TreePath* _currentPath;

     /*private*/ JMenuItem* menuItemBreakpointBefore;
     /*private*/ JMenuItem* menuItemBreakpointAfter;
 //        /*private*/ JMenuItem menuItemExpandTree;
   ConditionalNGDebugger* debugger;
 public:
     PopupMenu(ConditionalNGDebugger* debugger) ;
     QObject* self() override {return (QObject*)this;}
     /*private*/ void init() ;

  private:
     /*private*/ void showPopup(int x, int y, FemaleSocket* femaleSocket, TreePath* path);
     /*public*/  void actionPerformed(JActionEvent* e = nullptr) ;
     friend class TreePane;

 };

Q_DECLARE_INTERFACE(ConditionalNGDebugger::ConditionalNGEventListener, "ConditionalNGEventListener")
class CDRun1 : public ThreadAction
{
  Q_OBJECT
  ConditionalNGDebugger* cb;
  AtomicBoolean* enableMenuItems;
 public:
  CDRun1(AtomicBoolean* enableMenuItem, ConditionalNGDebugger* cb) {
   this->cb = cb;
   this->enableMenuItems = enableMenuItems;
  }
 public slots:
  void run();
};

class CDRun2 : public ThreadAction
{
  Q_OBJECT
  ConditionalNGDebugger* cb;
  AtomicBoolean* enableMenuItems;
  QString infStr;
  QMap<QString, Symbol*>symbols;
 public:
  CDRun2(AtomicBoolean* enableMenuItem, QString infStr, QMap<QString, Symbol*>symbols, ConditionalNGDebugger* cb) {
   this->cb = cb;
   this->enableMenuItems = enableMenuItems;
   this->infStr = infStr;
   this->symbols = symbols;
  }
 public slots:
  void run();
};

#endif // CONDITIONALNGDEBUGGER_H
