#ifndef DEFAULTMALEDIGITALBOOLEANACTIONSOCKETTEST_H
#define DEFAULTMALEDIGITALBOOLEANACTIONSOCKETTEST_H

#include "malesockettestbase.h"
#include <QObject>
#include "abstractdigitalbooleanaction.h"
#include "runtimeexception.h"
#include "jmriexception.h"
#include "defaultmaledigitalbooleanactionsocket.h"

class DefaultMaleDigitalBooleanActionSocketTest : public MaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultMaleDigitalBooleanActionSocketTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testEvaluate() /*throws JmriException*/;
  /*public*/  void testVetoableChange();
  /*public*/  void testCompareSystemNameSuffix();

 private:

 protected:
  /*protected*/ QString getNewSystemName();

};
/**
 * This action is different from MyStringAction and is used to test the
 * male socket.
 */
/*private*/ class MyDigitalBooleanAction : public AbstractDigitalBooleanAction {
 Q_OBJECT
    JmriException* je = nullptr;
    RuntimeException* re = nullptr;
    bool _hasChangedToTrue = false;
    bool _hasChangedToFalse = false;
    bool _vetoChange = false;
 public:
    MyDigitalBooleanAction(QString sysName) : AbstractDigitalBooleanAction(sysName, "") {
        //super(sysName, null);
    }
    QObject* bself() override{return (QObject*)this;}
    void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

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
 public:
    //@Override
    /*public*/  QString getShortDescription(QLocale /*locale*/)override {
        return "My short description";
    }

    //@Override
    /*public*/  QString getLongDescription(QLocale /*locale*/)override {
        return "My long description";
    }

    //@Override
    /*public*/  FemaleSocket* getChild(int /*index*/) /*throws IllegalArgumentException, UnsupportedOperationException*/ override{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int getChildCount()override {
        return 0;
    }

    //@Override
    /*public*/  Category getCategory() override{
        return Category::OTHER;
    }

    //@Override
    /*public*/  void setup()override {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  void execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/ override{
        if (je != nullptr) throw je;
        if (re != nullptr) throw re;
       _hasChangedToTrue = hasChangedToTrue;
       _hasChangedToFalse = hasChangedToFalse;
    }

    //@Override
    /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/override {
        if (_vetoChange) throw new PropertyVetoException("Veto change", evt);
    }

    //@Override
    /*public*/  Base* getDeepCopy(QMap<QString, QString>* /*map*/, QMap<QString, QString>* /*map1*/) /*throws JmriException*/ override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Base* deepCopyChildren(Base* /*base*/, QMap<QString, QString>* /*map*/, QMap<QString, QString>* /*map1*/) /*throws JmriException*/ override{
        throw new UnsupportedOperationException("Not supported");
    }
    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef) override{
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
    friend class DefaultMaleDigitalBooleanActionSocketTest;
};
#endif // DEFAULTMALEDIGITALBOOLEANACTIONSOCKETTEST_H
