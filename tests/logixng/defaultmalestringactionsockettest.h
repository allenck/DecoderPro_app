#ifndef DEFAULTMALESTRINGACTIONSOCKETTEST_H
#define DEFAULTMALESTRINGACTIONSOCKETTEST_H

#include "malesockettestbase.h"
#include "abstractstringaction.h"
#include "jmriexception.h"
#include "runtimeexception.h"

class DefaultMaleStringActionSocketTest : public MaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultMaleStringActionSocketTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp()override;
  Q_INVOKABLE /*public*/  void tearDown()override;

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testEvaluate() /*throws JmriException*/;

 protected:
  /*protected*/  QString getNewSystemName()override;

};

/**
 * This action is different from MyAnalogAction and is used to test the male socket.
 */
/*private*/ class MyStringAction : public AbstractStringAction {
Q_OBJECT
    JmriException* je = nullptr;
    RuntimeException* re = nullptr;
    QString _value = "";
    bool _vetoChange = false;
public:
    MyStringAction(QString sysName) : AbstractStringAction(sysName, "") {
        //super(sysName, null);
    }
    QObject* bself() override{return(QObject*)this;}
    QObject* self() override{return(QObject*)this;}
 protected:
    //@Override
    /*protected*/  void registerListenersForThisClass() {
        // Do nothing
    }

    //@Override
    /*protected*/  void unregisterListenersForThisClass() {
        // Do nothing
    }

    //@Override
    /*protected*/  void disposeMe() {
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
    /*public*/  void setValue(QString value) /*throws JmriException*/ {
        if (je != nullptr) throw je;
        if (re != nullptr) throw re;
        _value = value;
    }

    //@Override
    /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ {
        if (_vetoChange) throw new PropertyVetoException("Veto change", evt);
    }

    //@Override
    /*public*/  Base* getDeepCopy(QMap<QString, QString> map, QMap<QString, QString> map1) /*throws JmriException*/ {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Base* deepCopyChildren(Base* base, QMap<QString, QString> map, QMap<QString, QString> map1) /*throws JmriException*/ {
        throw new UnsupportedOperationException("Not supported");
    }
 friend class DefaultMaleStringActionSocketTest;
};
#endif // DEFAULTMALESTRINGACTIONSOCKETTEST_H
