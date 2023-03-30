#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include "abstractdigitalaction.h"
#include "femalesocketlistener.h"

class FemaleStringExpressionSocket;
class WebBrowser : public AbstractDigitalAction, public FemaleSocketListener
{
    Q_OBJECT
    Q_INTERFACES(FemaleSocketListener)
public:
    WebBrowser(QString sys, QString user, QObject *parent = nullptr);
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/override;
    /*public*/ Category getCategory()override;
    /*public*/ void execute() /*throws JmriException*/ override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
    /*public*/ int getChildCount()override;
    /*public*/ void connected(FemaleSocket* socket);
    /*public*/ void disconnected(FemaleSocket* socket);
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ FemaleStringExpressionSocket* getStringExpressionSocket();
    /*public*/ QString getStringExpressionSocketSystemName() ;
    /*public*/ void setStringExpressionSocketSystemName(QString systemName);
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass() override;
    /*public*/ void disposeMe() override;
    /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.tools.debugger.WebBrowser";}

    QObject* bself() override {return this;}

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
    void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

private:
    static Logger* log;
    /*private*/ QString _urlExpressionSocketSystemName;
    /*private*/ /*final*/ FemaleStringExpressionSocket* _urlExpressionSocket;

};

#endif // WEBBROWSER_H
