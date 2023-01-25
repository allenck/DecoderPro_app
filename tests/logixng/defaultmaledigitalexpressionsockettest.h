#ifndef DEFAULTMALEDIGITALEXPRESSIONSOCKETTEST_H
#define DEFAULTMALEDIGITALEXPRESSIONSOCKETTEST_H

#include "malesockettestbase.h"
#include <QObject>
#include "abstractdigitalexpression.h"
#include "runtimeexception.h"
#include "jmriexception.h"

class DefaultMaleDigitalExpressionSocketTest : public MaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultMaleDigitalExpressionSocketTest(QObject *parent = nullptr) : MaleSocketTestBase(parent){}
  Q_INVOKABLE /*public*/  void setUp() override;
  Q_INVOKABLE /*public*/  void tearDown()override;

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testEvaluate();
  /*public*/  void testVetoableChange();
  /*public*/  void testCompareSystemNameSuffix();

 private:

 protected:
  /*protected*/ QString getNewSystemName()override;

};

/**
 * This action is different from action And and is used to test the
 * male socket.
 */
/*private*/ class MyDigitalExpression : public AbstractDigitalExpression {

    JmriException* je = nullptr;
    RuntimeException* re = nullptr;
    bool result = false;
    bool _vetoChange = false;
public:
    MyDigitalExpression(QString sysName) : AbstractDigitalExpression(sysName,""){
        //super(sysName, null);
    }

    QObject* self() override {return (QObject*)this;}
    QObject* bself() override {return (QObject*)this;}

 protected:
    //@Override
    /*protected*/ void registerListenersForThisClass() override{
        // Do nothing
    }

    //@Override
    /*protected*/ void unregisterListenersForThisClass()override {
        // Do nothing
    }

    //@Override
    /*protected*/ void disposeMe() override{
        throw new UnsupportedOperationException("Not supported.");
    }
public:
    //@Override
    /*public*/  QString getShortDescription(QLocale locale) override{
        return "My short description";
    }

    //@Override
    /*public*/  QString getLongDescription(QLocale locale)override {
        return "My long description";
    }

    //@Override
    /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int getChildCount() override{
        return 0;
    }

    //@Override
    /*public*/  Category getCategory() override{
        return Category::COMMON;
    }

    //@Override
    /*public*/  void setup() override{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  bool evaluate() /*throws JmriException*/ override{
        if (je != nullptr) throw je;
        if (re != nullptr) throw re;
        return result;
    }

    //@Override
    /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ override{
        if (_vetoChange) throw new PropertyVetoException("Veto change", evt);
    }

    //@Override
    /*public*/  Base* getDeepCopy(QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/ override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Base* deepCopyChildren(Base* base, QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/override {
        throw new UnsupportedOperationException("Not supported");
    }
    friend class DefaultMaleDigitalExpressionSocketTest;
};
#endif // DEFAULTMALEDIGITALEXPRESSIONSOCKETTEST_H
