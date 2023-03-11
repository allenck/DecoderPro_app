#ifndef ACTIONLIGHTINTENSITY_H
#define ACTIONLIGHTINTENSITY_H

#include "abstractdigitalaction.h"
#include "femalesocketlistener.h"
#include "logixng/femaleanalogexpressionsocket.h"
#include "logixng/namedbeanaddressing.h"
#include "variablelight.h"
#include "vetoablechangelistener.h"

class FemaleAnalogExpressionSocket;
class ExpressionNode;
class ActionLightIntensity : public AbstractDigitalAction, public FemaleSocketListener, public VetoableChangeListener
{
    Q_OBJECT
Q_INTERFACES(FemaleSocketListener VetoableChangeListener)
public:
    explicit ActionLightIntensity(QString sys, QString user, QObject *parent = nullptr);
    /*public*/ static const /*final*/ int INTENSITY_SOCKET = 0;
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/ override;
    /*public*/ void setLight(/*@Nonnull*/ QString lightName) ;
    /*public*/ void setLight(/*@Nonnull*/ NamedBeanHandle<VariableLight*>* handle);
    /*public*/ void setLight(/*@Nonnull*/ VariableLight* light);
    /*public*/ void removeLight() ;
    /*public*/ NamedBeanHandle<VariableLight*>* getLight();
    /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getAddressing();
    /*public*/ void setReference(/*@Nonnull*/ QString reference) ;
    /*public*/ QString getReference();
    /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getLocalVariable() ;
    /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getFormula() ;
    /*public*/ Category getCategory()override;
    /*public*/ void execute() /*throws JmriException*/override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
    /*public*/ int getChildCount() override;
    /*public*/ void connected(FemaleSocket* socket) override;
    /*public*/ void disconnected(FemaleSocket* socket) override;
    /*public*/ QString getShortDescription(QLocale locale) override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ FemaleAnalogExpressionSocket* getIntensitySocket();
    /*public*/ QString getIntensitySocketSystemName();
    /*public*/ void setIntensitySystemName(QString systemName);
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe()override;

    QObject* bself() override {return this;}

    void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

    /*public*/ void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef) override{
        AbstractNamedBean::addPropertyChangeListener(listener, name, listenerRef);
    }
    /*public*/ void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                              QString name, QString listenerRef) override{
        AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
    }
    /*public*/ void updateListenerRef(/*@Nonnull*/ PropertyChangeListener* l, QString newName) override{
        AbstractNamedBean::updateListenerRef(l,newName);
    }
    /*public*/ int getNumPropertyChangeListeners() override{
        return AbstractNamedBean::getNumPropertyChangeListeners();
    }
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name) override
    {
       return AbstractNamedBean::getPropertyChangeListenersByReference(name);
    }
    /*public*/ virtual QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l)override{
        return AbstractNamedBean::getListenerRef(l);
    }
//    /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override{
//        return AbstractNamedBean::vetoableChange(evt);
//    }

public slots:
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;


private:
    static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<VariableLight*>* _lightHandle =nullptr;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode;

    /*private*/ QString _intensitySocketSystemName;
    /*private*/ /*final*/ FemaleAnalogExpressionSocket* _intensitySocket;
    /*private*/ void parseFormula() /*throws ParserException*/;

};

#endif // ACTIONLIGHTINTENSITY_H
