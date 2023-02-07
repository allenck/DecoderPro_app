#ifndef DEFAULTMALEANALOGACTIONSOCKETTEST_H
#define DEFAULTMALEANALOGACTIONSOCKETTEST_H

#include "malesockettestbase.h"
#include <QObject>
#include "abstractanalogaction.h"
#include "jmriexception.h"
#include "runtimeexception.h"

class DefaultMaleAnalogActionSocketTest : public MaleSocketTestBase
{
  Q_OBJECT
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
     setObjectName("MyAnalogAction");
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
    /*public*/  Category getCategory()override {
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
    /*public*/  Base* getDeepCopy(QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/override {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Base* deepCopyChildren(Base* base, QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/override {
        throw new UnsupportedOperationException("Not supported");
    }
    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
     AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
    }
    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                      QString name, QString listenerRef) override {
     AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
    }
    /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
    ///*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
    /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
    /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
    /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
     return AbstractNamedBean::getPropertyChangeListenersByReference(name);
    }
    friend class DefaultMaleAnalogActionSocketTest;
};
#endif // DEFAULTMALEANALOGACTIONSOCKETTEST_H
