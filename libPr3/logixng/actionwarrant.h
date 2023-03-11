#ifndef ACTIONWARRANT_H
#define ACTIONWARRANT_H

#include "abstractdigitalaction.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "expressionnode.h"
#include "vetoablechangelistener.h"

class Warrant;
class ActionWarrant : public AbstractDigitalAction, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES(VetoableChangeListener)
public:
    class DirectOperation
    {
       public:
        enum TYPE {None, AllocateWarrantRoute, DeallocateWarrant,  SetRouteTurnouts, AutoRunTrain, ManuallyRunTrain,
                  ControlAutoTrain, SetTrainId, SetTrainName};
        static QString toString(TYPE t)
        {
            switch(t)
            {
            case None: return "";
            case AllocateWarrantRoute: return tr("Allocate Warrant Route");
            case DeallocateWarrant: return tr("Deallocate Warrant");
            case SetRouteTurnouts: return tr("Set Route Turnouts");
            case AutoRunTrain: return tr("Run Auto Train");
            case ManuallyRunTrain: return tr("Manually Run Train");
            case ControlAutoTrain: return tr("Control Auto Train");
            case SetTrainId: return tr("Set Train ID");
            case SetTrainName: return tr("Set Train Name");
                default:
                    return "";
            }
        }
        static QList<TYPE> values() {
            return {None, AllocateWarrantRoute, DeallocateWarrant,  SetRouteTurnouts, AutoRunTrain, ManuallyRunTrain,
                        ControlAutoTrain, SetTrainId, SetTrainName};
        }
        static TYPE valueOf(QString s)
        {
           if(s == tr("")) return None;
           if(s == tr("Allocate Warrant Route")) return AllocateWarrantRoute;
           if(s == tr("Deallocate Warrant")) return DeallocateWarrant;
           if(s == tr("Set Route Turnouts")) return SetRouteTurnouts ;
           if(s == tr("Run Auto Train")) return AutoRunTrain;
           if(s == tr("Manually Run Train")) return ManuallyRunTrain;
           if(s == tr("Control Auto Train")) return ControlAutoTrain;
           if(s == tr("Set Train ID")) return SetTrainId;
           if(s == tr("Set Train Name")) return SetTrainName;
           throw new IllegalArgumentException(s);
        }

    };
    class ControlAutoTrain
    {
    public:
        enum TYPE {Halt, Resume, Abort};
        static QString toString(TYPE t)
        {
            switch(t)
            {
            case Halt: return tr("Halt");
            case Resume: return tr("Resume");

            case Abort: return tr("Abort");
            }
            throw new IllegalArgumentException();
        }
        static QList<TYPE> values() {
            return {Halt, Resume, Abort};
        }
        static TYPE valueOf(QString s)
        {
            if(s == tr("Halt")) return Halt;
            if(s == tr("Resume")) return Resume;
            if(s == tr("Abort")) return Abort;
            throw new IllegalArgumentException(s);
        }
    };

    ActionWarrant(QString sys, QString user, QObject *parent = nullptr);
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/override;
    /*public*/ void setWarrant(/*@Nonnull*/ QString warrantName);
    /*public*/ void setWarrant(/*@Nonnull*/ Warrant* warrant);
    /*public*/ void setWarrant(/*@Nonnull*/ NamedBeanHandle<Warrant*>* handle);
    /*public*/ void removeWarrant() ;
    /*public*/ NamedBeanHandle<Warrant*>* getWarrant();
    /*public*/ void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
    /*public*/ NamedBeanAddressing::TYPE getAddressing();
    /*public*/ void setReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getReference();
    /*public*/ void setLocalVariable(/*@Nonnull*/ QString localVariable) ;
    /*public*/ QString getLocalVariable() ;
    /*public*/ void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getFormula() ;
    /*public*/ void setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getOperationAddressing();
    /*public*/ void setOperationDirect(DirectOperation::TYPE state);
    /*public*/ DirectOperation::TYPE getOperationDirect();
    /*public*/ void setOperationReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getOperationReference();
    /*public*/ void setOperationLocalVariable(/*@Nonnull*/ QString localVariable) ;
    /*public*/ QString getOperationLocalVariable();
    /*public*/ void setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException */;
    /*public*/ QString getOperFormula();
    /*public*/ void setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
    /*public*/ NamedBeanAddressing::TYPE getDataAddressing();
    /*public*/ void setDataReference(/*@Nonnull*/ QString reference);
    /*public*/ QString getDataReference();
    /*public*/ void setDataLocalVariable(/*@Nonnull*/ QString localVariable) ;
    /*public*/ QString getDataLocalVariable();
    /*public*/ void setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
    /*public*/ QString getDataFormula();
    /*public*/ void setTrainIdName(/*@Nonnull*/ QString trainIdName) ;
    /*public*/ QString getTrainIdName();
    /*public*/ void setControlAutoTrain(ControlAutoTrain::TYPE controlAutoTrain);
    /*public*/ ControlAutoTrain::TYPE getControlAutoTrain();
    /*public*/ Category getCategory()override;
    /*public*/ void execute() /*throws JmriException*/override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
    /*public*/ int getChildCount() override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale) override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe()override;
    /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) override;

    QObject* bself() override {return this;}

    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener)override{
     AbstractNamedBean::addPropertyChangeListener(listener);
    }
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
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;


private:
    static Logger* log;
    /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
    /*private*/ NamedBeanHandle<Warrant*>* _warrantHandle =nullptr;
    /*private*/ QString _reference = "";
    /*private*/ QString _localVariable = "";
    /*private*/ QString _formula = "";
    /*private*/ ExpressionNode* _expressionNode;

    /*private*/ NamedBeanAddressing::TYPE _operationAddressing = NamedBeanAddressing::Direct;
    /*private*/ DirectOperation::TYPE _operationDirect = DirectOperation::AllocateWarrantRoute;
    /*private*/ QString _operationReference = "";
    /*private*/ QString _operationLocalVariable = "";
    /*private*/ QString _operationFormula = "";
    /*private*/ ExpressionNode* _operationExpressionNode;

    /*private*/ NamedBeanAddressing::TYPE _dataAddressing = NamedBeanAddressing::Direct;
    /*private*/ QString _dataReference = "";
    /*private*/ QString _dataLocalVariable = "";
    /*private*/ QString _dataFormula = "";
    /*private*/ ExpressionNode* _dataExpressionNode;

    /*private*/ QString _trainIdName = "";
    /*private*/ ControlAutoTrain::TYPE _controlAutoTrain = ControlAutoTrain::Halt;
    /*private*/ void parseFormula() /*throws ParserException*/;
    /*private*/ void parseOperFormula() /*throws ParserException*/;
    /*private*/ void parseDataFormula() /*throws ParserException*/;
    /*private*/ QString getNewOper() /*throws JmriException*/;
    /*private*/ QString getNewData() /*throws JmriException*/ ;
    /*private*/ QString getLongDataDescription(QLocale locale, QString bundleKey, QString namedBean, QString value);    /*public*/ void setup() override;

};

#endif // ACTIONWARRANT_H
