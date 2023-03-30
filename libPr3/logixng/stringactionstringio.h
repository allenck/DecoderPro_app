#ifndef STRINGACTIONSTRINGIO_H
#define STRINGACTIONSTRINGIO_H

#include "abstractstringaction.h"
#include "namedbeanhandle.h"
#include "vetoablechangelistener.h"

class StringIO;
class StringActionStringIO : public AbstractStringAction, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(VetoableChangeListener)
public:
    StringActionStringIO(QString sys, QString user, QObject *parent = nullptr);
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames)override;
    /*public*/ void setStringIO(/*@Nonnull*/ QString stringIOName) ;
    /*public*/ void setStringIO(/*@Nonnull*/ NamedBeanHandle<StringIO *> *handle) ;
    /*public*/ void setStringIO(/*@Nonnull*/ StringIO* stringIO);
    /*public*/ void removeStringIO();
    /*public*/ NamedBeanHandle<StringIO*>* getStringIO() ;
    /*public*/ void setValue(QString value) /*throws JmriException*/override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
    /*public*/ int getChildCount()override;
    /*public*/ Category getCategory()override;
    /*public*/ QString getShortDescription(QLocale locale) override;
    /*public*/ QString getLongDescription(QLocale locale) override;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe() override;
    /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) override;
    /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.actions.StringActionStringIO";}


    QObject* bself() override {return this;}
    QObject* self() override {return this;}


    ///*public*/  void propertyChange(PropertyChangeEvent* evt)override;
    ///*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;
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
    void addPropertyChangeListener(PropertyChangeListener* l) override {
        AbstractNamedBean::addPropertyChangeListener(l);
    }


public slots:
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ override;


private:
    static Logger* log;
    /*private*/ NamedBeanHandle<StringIO*>* _stringIOHandle = nullptr;

};

#endif // STRINGACTIONSTRINGIO_H
