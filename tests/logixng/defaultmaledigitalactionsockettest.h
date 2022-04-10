#ifndef DEFAULTMALEDIGITALACTIONSOCKETTEST_H
#define DEFAULTMALEDIGITALACTIONSOCKETTEST_H

#include "malesockettestbase.h"
#include "runtimeexception.h"
#include "jmriexception.h"
#include "abstractdigitalaction.h"

class MyDigitalAction;
class DefaultMaleDigitalActionSocketTest : public MaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultMaleDigitalActionSocketTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp()override;
  Q_INVOKABLE /*public*/  void tearDown()override;

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testExecute() /*throws JmriException*/;
  /*public*/  void testVetoableChange();
  /*public*/  void testCompareSystemNameSuffix();

 protected:
  /*protected*/ QString getNewSystemName()override;

};
/**
 * This action is different from MyStringAction and is used to test the
 * male socket.
 */
/*private*/ class MyDigitalAction : public AbstractDigitalAction {
    Q_OBJECT
    JmriException* je = nullptr;
    RuntimeException* re = nullptr;
    bool _hasExecuted = false;
    bool _vetoChange = false;
 public:
    MyDigitalAction(QString sysName) : AbstractDigitalAction(sysName, ""){
        //super(sysName, null);
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
        throw new UnsupportedOperationException("Not supported.");
    }
public:
    //@Override
    /*public*/  QString getShortDescription(QLocale locale) {
        return "My short description";
    }

    //@Override
    /*public*/  QString getLongDescription(QLocale locale) {
        return "My long description";
    }

    //@Override
    /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  Category* getCategory() {
        return Category::COMMON;
    }

    //@Override
    /*public*/  void setup() {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  void execute() /*throws JmriException*/ {
        if (je != nullptr) throw je;
        if (re != nullptr) throw re;
        _hasExecuted = true;
    }

    //@Override
    /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ {
        if (_vetoChange) throw new PropertyVetoException("Veto change", evt);
    }

    //@Override
    /*public*/  Base* getDeepCopy(QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/ override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Base* deepCopyChildren(Base* base, QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/ override{
        throw new UnsupportedOperationException("Not supported");
    }
 friend class DefaultMaleDigitalActionSocketTest;
};
#endif // DEFAULTMALEDIGITALACTIONSOCKETTEST_H
