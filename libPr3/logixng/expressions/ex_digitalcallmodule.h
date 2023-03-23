#ifndef EX_DIGITALCALLMODULE_H
#define EX_DIGITALCALLMODULE_H

#include "../abstractdigitalexpression.h"
#include "../module.h"
#include "namedbeanhandle.h"
#include "vetoablechangelistener.h"

class DefaultSymbolTable;
namespace Expressions
{
 class DigitalCallModule : public AbstractDigitalExpression, public VetoableChangeListener
 {
   Q_OBJECT
   Q_INTERFACES(VetoableChangeListener)
  public:
   DigitalCallModule(QString sys, QString user, QObject* parent = nullptr);
   /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames)override;
   /*public*/  void setModule(/*@Nonnull*/ QString memoryName);
   /*public*/  void setModule(/*@Nonnull*/ NamedBeanHandle<Module*>* handle);
   /*public*/  void setModule(/*@Nonnull*/ Module* module);
   /*public*/  void removeModule();
   /*public*/  NamedBeanHandle<Module*>* getModule();
   /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;
   /*public*/  Category getCategory()override;
   /*public*/  void returnSymbols(DefaultSymbolTable* symbolTable, QSet<Module::ParameterData *> symbolDefinitions) /*throws JmriException*/ ;
   /*public*/  bool evaluate() /*throws JmriException*/override;
   /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
   /*public*/  int getChildCount()override;
   /*public*/  QString getShortDescription(QLocale locale)override;
   /*public*/  QString getLongDescription(QLocale locale)override;
   /*public*/  void setup()override;
   /*public*/  void registerListenersForThisClass()override;
   /*public*/  void unregisterListenersForThisClass()override;
   /*public*/  void disposeMe()override;
   /*public*/  void addParameter(
           QString name,
           SymbolTable::InitialValueType::TYPES initialValueType,
           QString initialValueData,
           ReturnValueType::TYPES returnValueType,
           QString returnValueData);
   /*public*/  QList<Module::ParameterData*>* getParameterData();
   /*public*/ QString getClass() const override
   {
       return "jmri.jmrit.logixng.expressions.DigitalCallModule";
   }


   QObject* self() override {return this;}
   QObject* bself() override {return this;}

   /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
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
   void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

  private:
   static Logger* log;
   /*private*/ NamedBeanHandle<Module*>* _moduleHandle=nullptr;
   /*private*/ QSet<SymbolTable::VariableData *> dataSet(QList<Module::ParameterData *> *list);
   /*final*/ QList<Module::ParameterData*>* _parameterData = new QList<Module::ParameterData*>();

 };
}

#endif // EX_DIGITALCALLMODULE_H
