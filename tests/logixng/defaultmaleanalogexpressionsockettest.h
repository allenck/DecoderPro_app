#ifndef DEFAULTMALEANALOGEXPRESSIONSOCKETTEST_H
#define DEFAULTMALEANALOGEXPRESSIONSOCKETTEST_H

#include "malesockettestbase.h"
#include "abstractanalogexpression.h"
#include "runtimeexception.h"
#include "jmriexception.h"

class MyAnalogExpression;
class DefaultMaleAnalogExpressionSocketTest : public MaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultMaleAnalogExpressionSocketTest(QObject *parent = nullptr) : MaleSocketTestBase(parent){}
  Q_INVOKABLE /*public*/  void setUp()override;
  Q_INVOKABLE /*public*/  void tearDown()override;

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testEvaluate() /*throws JmriException*/;
  /*public*/  void testEvaluateErrors();
  /*public*/  void testVetoableChange();
  /*public*/  void testCompareSystemNameSuffix();


 protected:
  /*protected*/ QString getNewSystemName()override;

};

/**
 * This action is different from AnalogExpressionMemory and is used to test the
 * male socket.
 */
/*private*/ class MyAnalogExpression : public AbstractAnalogExpression {
    Q_OBJECT

    JmriException* je = nullptr;
    RuntimeException* re = nullptr;
    double result = 0.0;
    bool _vetoChange = false;
 public:
    MyAnalogExpression(QString sysName) : AbstractAnalogExpression(sysName, "")
    {
     //super(sysName, null);
    }
    QObject* self() override {return (QObject*)this;}
    QObject* bself() override {return (QObject*)this;}

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
    /*public*/  double evaluate() /*throws JmriException*/ {
        if (je != nullptr) throw je;
        if (re != nullptr) throw re;
        return result;
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
    friend class DefaultMaleAnalogExpressionSocketTest;
};
#endif // DEFAULTMALEANALOGEXPRESSIONSOCKETTEST_H