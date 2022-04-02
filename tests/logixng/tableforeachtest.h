#ifndef TABLEFOREACHTEST_H
#define TABLEFOREACHTEST_H

#include "abstractdigitalactiontestbase.h"
#include "abstractdigitalaction.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "defaultconditionalng.h"

class MyAction04;
class DefaultConditionalNG;
class TableForEach;
class DefaultLogixNG;
class TableForEachTest : public AbstractDigitalActionTestBase
{
  Q_OBJECT
 public:
  TableForEachTest() : AbstractDigitalActionTestBase() {}
  /*public*/  ConditionalNG* getConditionalNG()override;
  /*public*/  LogixNG* getLogixNG()override;
  /*public*/  MaleSocket* getConnectableChild()override;
  /*public*/  QString getExpectedPrintedTree()override;
  /*public*/  QString getExpectedPrintedTreeFromRoot()override;
  /*public*/  NamedBean* createNewBean(QString systemName);
  /*public*/  bool addNewSocket()override;

  Q_INVOKABLE /*public*/  void setUp() /*throws SocketAlreadyConnectedException*/;
  Q_INVOKABLE /*public*/  void tearDown();


 public slots:
  /*public*/  void testCtor();
//  /*public*/  void testCtorAndSetup2();
//  /*public*/  void testCtorAndSetup3();
  /*public*/  void testGetChild();
  /*public*/  void testCategory();
  /*public*/  void testDescription();
  /*public*/  void testExecute() /*throws IOException */;
  /*public*/  void testIsActive();
  /*public*/  void testMaleSocketIsActive();

 private:
  LogixNG* _logixNG;
  ConditionalNG* _conditionalNG;
  TableForEach* _tableForEach;
  MaleSocket* _maleSocket;
  /*private*/ /*final*/ QList<QString> _cells = QList<QString>();


};

/*private*/ class MyAction04 : public AbstractDigitalAction {
 QList<QString> _cells;
 Q_OBJECT
 public:
    /*public*/  MyAction04(QString sys, QString user, QList<QString> _cells) /*throws BadUserNameException, BadSystemNameException*/: AbstractDigitalAction(sys, user) {
        //super(sys, user);
     this->_cells = _cells;
    }
 protected:
    //@Override
    /*protected*/ void registerListenersForThisClass() {
        // Do nothing
    }

    //@Override
    /*protected*/ void unregisterListenersForThisClass() {
        // Do nothing
    }

    //@Override
    /*protected*/ void disposeMe() {
        // Do nothing
    }
public:
    //@Override
    /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException */{
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames.value(AbstractNamedBean::getSystemName());
        QString userName = userNames.value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        MyAction04* copy = new MyAction04(sysName, userName, _cells);
        copy->setComment(getComment());
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    //@Override
    /*public*/  QString getShortDescription(QLocale locale) {
        return "MyAction";
    }

    //@Override
    /*public*/  QString getLongDescription(QLocale locale) {
        return "MyAction";
    }

    //@Override
    /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  int getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  Category* getCategory() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void setup() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void execute() /*throws JmriException*/ {
        SymbolTable* symbolTable = this->getConditionalNG()->getSymbolTable();
        _cells.append(symbolTable->getValue("MyVariable").toString());
    }

};
#endif // TABLEFOREACHTEST_H
