#ifndef DEFAULTMALEANALOGACTIONSOCKETTEST_H
#define DEFAULTMALEANALOGACTIONSOCKETTEST_H

#include "malesockettestbase.h"
#include <QObject>
#include "abstractanalogaction.h"
#include "jmriexception.h"
#include "runtimeexception.h"

class DefaultMaleAnalogActionSocketTest : public MaleSocketTestBase
{
 public:
  explicit DefaultMaleAnalogActionSocketTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp()override;
  Q_INVOKABLE /*public*/  void tearDown()override;

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testSetValue() /*throws JmriException*/;

 protected:
  /*protected*/ QString getNewSystemName()override;

};

/**
 * This action is different from AnalogActionMemory and is used to test the
 * male socket.
 */
/*private*/ class MyAnalogAction : public AbstractAnalogAction {

    JmriException* je = nullptr;
    RuntimeException* re = nullptr;
    double _value = 0.0;
    bool _vetoChange = false;
 public:
    MyAnalogAction(QString sysName) : AbstractAnalogAction(sysName, "") {
        //super(sysName, null);
    }
    QObject* bself() override {return (QObject*)this;}
 protected:
    //@Override
    /*protected*/ void registerListenersForThisClass() override{
        // Do nothing
    }

    //@Override
    /*protected*/ void unregisterListenersForThisClass() override{
        // Do nothing
    }

    //@Override
    /*protected*/ void disposeMe() override{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  QString getShortDescription(QLocale locale) override{
        return "My short description";
    }

    //@Override
    /*public*/  QString getLongDescription(QLocale locale) override{
        return "My long description";
    }

    //@Override
    /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int getChildCount() override{
        return 0;
    }

    //@Override
    /*public*/  Category* getCategory()override {
        return Category::COMMON;
    }

    //@Override
    /*public*/  void setup() override{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  void setValue(double value) /*throws JmriException*/ override{
        if (je != nullptr) throw je;
        if (re != nullptr) throw re;
        _value = value;
    }

    //@Override
    /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException */override{
        if (_vetoChange) throw new PropertyVetoException("Veto change", evt);
    }

    //@Override
    /*public*/  Base* getDeepCopy(QMap<QString, QString> map, QMap<QString, QString>map1) /*throws JmriException*/override {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Base* deepCopyChildren(Base* base, QMap<QString, QString> map, QMap<QString, QString> map1) /*throws JmriException*/override {
        throw new UnsupportedOperationException("Not supported");
    }
    friend class DefaultMaleAnalogActionSocketTest;
};
#endif // DEFAULTMALEANALOGACTIONSOCKETTEST_H
