#ifndef EX_DIGITALCALLMODULE_H
#define EX_DIGITALCALLMODULE_H

#include "../abstractdigitalaction.h"
#include "../module.h"
#include "namedbeanhandle.h"
#include "vetoablechangelistener.h"

class DefaultSymbolTable;
namespace Actions
{
 class DigitalCallModule : public AbstractDigitalAction, public VetoableChangeListener
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
   /*public*/  void execute() /*throws JmriException*/override;
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
           InitialValueType::TYPES initialValueType,
           QString initialValueData,
           ReturnValueType::TYPES returnValueType,
           QString returnValueData);
   /*public*/  QList<Module::ParameterData*>* getParameterData();


   QObject* self() override {return this;}
   QObject* bself() override {return this;}

  private:
   static Logger* log;
   /*private*/ NamedBeanHandle<Module*>* _moduleHandle;
   /*private*/ /*final*/ QList<Module::ParameterData*>* _parameterData = new QList<Module::ParameterData*>();
   /*private*/ QSet<VariableData*> dataSet(QList<Module::ParameterData *> *list);


 };
}

#endif // EX_DIGITALCALLMODULE_H
