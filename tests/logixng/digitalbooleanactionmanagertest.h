#ifndef DIGITALBOOLEANACTIONMANAGERTEST_H
#define DIGITALBOOLEANACTIONMANAGERTEST_H

#include <abstractmanagertestbase.h>
#include <QObject>
#include "abstractbase.h"
#include "digitalbooleanactionbean.h"

class MyAction02;
class DigitalBooleanActionManager;
class DigitalBooleanActionManagerTest : public AbstractManagerTestBase
{
  Q_OBJECT
 public:
  explicit DigitalBooleanActionManagerTest(QObject *parent = nullptr) : AbstractManagerTestBase(parent){}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();


 public slots:
  /*public*/  void testRegisterAction();
  /*public*/  void testGetBeanTypeHandled();
  /*public*/  void testInstance();

 private:
  /*private*/ DigitalBooleanActionManager* _m;

};

/*private*/ /*static*/ class MyAction02 : public  AbstractBase,  public DigitalBooleanActionBean {
Q_OBJECT
  Q_INTERFACES(DigitalBooleanActionBean)
 public:
    /*public*/  MyAction02(QString sys) /*throws BadSystemNameException*/ : AbstractBase(sys){
        //super(sys);
    }
QObject* self() override{ return (QObject*)this;}
QObject* bself() override{ return (QObject*)this;}
void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

 protected:
    //@Override
    /*protected*/ void registerListenersForThisClass() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*protected*/ void unregisterListenersForThisClass() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*protected*/ void disposeMe() {
        throw new UnsupportedOperationException("Not supported");
    }
 public:
    //@Override
    /*public*/  void setState(int s) /*throws JmriException*/ {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  int getState() override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  QString getBeanType() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  QString getShortDescription(QLocale locale)override {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  QString getLongDescription(QLocale locale) override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Base* getParent() const override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void setParent(Base* parent)override {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  int getChildCount() override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Category getCategory() override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void setup() override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/ override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Base* getDeepCopy(QMap<QString, QString>* map,QMap<QString, QString>* map1) /*throws JmriException*/override {
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
/*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
/*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
/*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
/*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
/*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
 return AbstractNamedBean::getPropertyChangeListenersByReference(name);
}
};

#endif // DIGITALBOOLEANACTIONMANAGERTEST_H
