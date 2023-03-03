#ifndef ACTIONOBLOCK_H
#define ACTIONOBLOCK_H

#include "abstractdigitalaction.h"
#include "vetoablechangelistener.h"
#include "namedbeanhandle.h"
#include "oblock.h"
#include "namedbeanaddressing.h"

class ExpressionNode;
class ActionOBlock : public AbstractDigitalAction, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(VetoableChangeListener)
public:
    ActionOBlock(QString sys, QString user, QObject *parent = nullptr);
    class DirectOperation
    {
    public:
        enum TYPE {Deallocate, SetValue, SetError, ClearError, SetOutOfService, ClearOutOfService};
        static QString toString(TYPE t)
        {
            switch (t) {
            case Deallocate: return tr("Deallocate Block");
            case SetValue: return tr("Set Block Value");
            case SetError: return tr("Set Block Error");
            case ClearError: return tr("Clear Block Error");
            case SetOutOfService: return tr("Set Block OutOfService");
            case ClearOutOfService: return tr("Clear Block OutOfService");
            }
        }
        static TYPE valueOf(QString s)
        {
          if(s== tr("Deallocate Block")) return Deallocate;
          if(s == tr("Set Block Value")) return SetValue;
          if(s == tr("Set Block Error")) return SetError;
          if(s == tr("Clear Block Error")) return ClearError;
          if(s == tr("Set Block OutOfService")) return SetOutOfService;
          if(s == tr("Clear Block OutOfService")) return ClearOutOfService;
          throw new IllegalArgumentException("invalid DirectOperation");
        }
        static QList<TYPE> values() {return {Deallocate, SetValue, SetError, ClearError, SetOutOfService, ClearOutOfService};}
    };
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/override;
    /*public*/ void setOBlock(/*@Nonnull*/ QString oblockName);
    /*public*/ void setOBlock(/*@Nonnull*/ OBlock* oblock) ;
    /*public*/ void setOBlock(/*@Nonnull*/ NamedBeanHandle<OBlock*>* handle) ;
    /*public*/ void removeOBlock();
    /*public*/ NamedBeanHandle<OBlock*>* getOBlock();
    /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getAddressing() ;
    /*public*/ void setReference(/*@Nonnull*/ QString reference) ;
    /*public*/ QString getReference() ;
    /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getLocalVariable();
    /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getFormula();
    /*public*/ void setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getOperationAddressing();
    /*public*/ void setOperationDirect(DirectOperation::TYPE state);
    /*public*/ DirectOperation::TYPE getOperationDirect();
    /*public*/ void setOperationReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getOperationReference();
    /*public*/ void setOperationLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getOperationLocalVariable() ;
    /*public*/ void setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getOperationFormula();
    /*public*/ void setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getDataAddressing();
    /*public*/ void setDataReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getDataReference() ;
    /*public*/ void setDataLocalVariable(/*@Nonnull*/ QString localVariable);
    /*public*/ QString getDataLocalVariable();
    /*public*/ void setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ ;
    /*public*/ QString getDataFormula();
    /*public*/ void setOBlockValue(/*@Nonnull*/ QString value);
    /*public*/ QString getOBlockValue();
    /*public*/ Category getCategory()override;
    /*public*/ void execute() /*throws JmriException*/override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass() override;
    /*public*/ void unregisterListenersForThisClass() override;
    /*public*/ void disposeMe() override;
    /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
     AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
    }
    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                      QString name, QString listenerRef) override {
     AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
    }
    /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
//    /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
    /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
    /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
    /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
     return AbstractNamedBean::getPropertyChangeListenersByReference(name);
    }
public slots:
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;

private:
    static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<OBlock*>* _oblockHandle = nullptr;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode;

    /*private*/ NamedBeanAddressing::TYPE _operationAddressing = NamedBeanAddressing::Direct;
    /*private*/ DirectOperation::TYPE _operationDirect = DirectOperation::Deallocate;
    /*private*/ QString _operationReference = "";
    /*private*/ QString _operationLocalVariable = "";
    /*private*/ QString _operationFormula = "";
    /*private*/ ExpressionNode* _operationExpressionNode;

    /*private*/ NamedBeanAddressing::TYPE _dataAddressing = NamedBeanAddressing::Direct;
    /*private*/ QString _dataReference = "";
    /*private*/ QString _dataLocalVariable = "";
    /*private*/ QString _dataFormula = "";
    /*private*/ ExpressionNode* _dataExpressionNode;

    /*private*/ QString _oblockValue = "";
    /*private*/ void parseFormula() /*throws ParserException*/;
    /*private*/ void parseOperationFormula() /*throws ParserException*/;
    /*private*/ void parseDataFormula() /*throws ParserException*/;
    /*private*/ QString getNewOperation() /*throws JmriException */;
    /*private*/ QString getNewData(ConditionalNG* conditionalNG) /*throws JmriException*/;

};

#endif // ACTIONOBLOCK_H
