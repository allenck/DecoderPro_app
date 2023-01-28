#include "ex_digitalcallmodule.h"
#include "loggerfactory.h"
#include "../defaultdigitalexpressionmanager.h"
#include "instancemanager.h"
#include "../defaultmodulemanager.h"
#include "../namedbeanhandlemanager.h"
#include "../defaultsymboltable.h"
#include "vptr.h"
#include "../defaultmemorymanager.h"

/**
 * This expression evaluates a module.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
namespace Expressions
{
// /*public*/  class DigitalCallModule extends AbstractDigitalExpression implements VetoableChangeListener {

 /*public*/  DigitalCallModule::DigitalCallModule(QString sys, QString user, QObject* parent)
  : AbstractDigitalExpression(sys, user, parent) /*throws BadUserNameException, BadSystemNameException*/
 {
     //super(sys, user);
 }

 //@Override
 /*public*/  Base* DigitalCallModule::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) {
     DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
     QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
     QString userName = systemNames->value(AbstractNamedBean::getSystemName());
     if (sysName == "") sysName = manager->getAutoSystemName();
     DigitalCallModule* copy = new DigitalCallModule(sysName, userName);
     if (_moduleHandle != nullptr) copy->setModule(_moduleHandle);
     for (Module::ParameterData* data : *_parameterData) {
         copy->addParameter(
                 data->getName(),
                 data->getInitalValueType(),
                 data->getInitialValueData(),
                 data->getReturnValueType(),
                 data->getReturnValueData());
     }
     return manager->registerExpression(copy);
 }

 /*public*/  void DigitalCallModule::setModule(/*@Nonnull*/ QString memoryName) {
     assertListenersAreNotRegistered(log, "setModule");
     Module* memory = ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->getModule(memoryName);
     if (memory != nullptr) {
         setModule(memory);
     } else {
         removeModule();
         log->error(tr("memory \"%1\" is not found").arg(memoryName));
     }
 }

 /*public*/  void DigitalCallModule::setModule(/*@Nonnull*/ NamedBeanHandle<Module*>* handle) {
     assertListenersAreNotRegistered(log, "setModule");
     _moduleHandle = handle;
     ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
 }

 /*public*/  void DigitalCallModule::setModule(/*@Nonnull*/ Module* module) {
     assertListenersAreNotRegistered(log, "setModule");
     setModule(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
             ->getNamedBeanHandle(module->getDisplayName(), module));
 }

 /*public*/  void DigitalCallModule::removeModule() {
     assertListenersAreNotRegistered(log, "setModule");
     if (_moduleHandle != nullptr) {
         ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
         _moduleHandle = nullptr;
     }
 }

 /*public*/  NamedBeanHandle<Module*>* DigitalCallModule::getModule() {
     return _moduleHandle;
 }

 //@Override
 /*public*/  void DigitalCallModule::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
     if ("CanDelete" == (evt->getPropertyName())) { // No I18N
         if (VPtr<Module>::VPtr::asPtr(evt->getOldValue())) {
             if (VPtr<Module>::VPtr::asPtr(evt->getOldValue())->equals(getModule()->getBean()->self())) {
                 PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                 throw new PropertyVetoException(tr("Module is in use by CallModule action \"%1\"").arg(getDisplayName()), e); // NOI18N
             }
         }
     } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
         if (VPtr<Module>::VPtr::asPtr(evt->getOldValue())) {
             if (VPtr<Module>::VPtr::asPtr(evt->getOldValue())->equals(getModule()->getBean()->self())) {
                 removeModule();
             }
         }
     }
 }

 /** {@inheritDoc} */
 //@Override
 /*public*/  Category DigitalCallModule::getCategory() {
     return Category::OTHER;
 }

 /**
  * Return the symbols
  * @param symbolTable the symbol table
  * @param symbolDefinitions list of symbols to return
  * @throws jmri.JmriException if an exception occurs
  */
 /*public*/  void DigitalCallModule::returnSymbols(
         DefaultSymbolTable* symbolTable, QSet<Module::ParameterData*> symbolDefinitions)
         /*throws JmriException*/ {

     for (Module::ParameterData* parameter : symbolDefinitions) {
         QVariant returnValue = symbolTable->getValue(parameter->getName());

         switch (parameter->getReturnValueType()) {
             case ReturnValueType::None:
                 break;

             case ReturnValueType::LocalVariable:
                 symbolTable->getPrevSymbolTable()
                         ->setValue(parameter->getReturnValueData(), returnValue);
                 break;

             case ReturnValueType::Memory:
             {
                 Memory* m = (Memory*)((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getNamedBean(parameter->getReturnValueData())->self();
                 if (m != nullptr) m->setValue(returnValue);
                 break;
             }
             default:
                 log->error(tr("definition.returnValueType has invalid value: %1").arg(ReturnValueType::getDescr(parameter->getReturnValueType())));
                 throw new IllegalArgumentException("definition._returnValueType has invalid value: " + ReturnValueType::getDescr(parameter->getReturnValueType()));
         }
     }
 }

 /** {@inheritDoc} */
 //@Override
 /*public*/  bool DigitalCallModule::evaluate() /*throws JmriException*/ {
     if (_moduleHandle == nullptr) return false;

     Module* module = _moduleHandle->getBean();

     ConditionalNG* oldConditionalNG = getConditionalNG();
     module->setCurrentConditionalNG(getConditionalNG());

     FemaleSocket* femaleSocket = module->getRootSocket();

     if (! (qobject_cast<FemaleDigitalExpressionSocket*>(femaleSocket->bself()))) {
         log->error("module.rootSocket is not a FemaleDigitalExpressionSocket");
         return false;
     }

     ConditionalNG* conditionalNG = getConditionalNG();

     int currentStackPos = conditionalNG->getStack()->getCount();

     DefaultSymbolTable* newSymbolTable = new DefaultSymbolTable(conditionalNG);
     newSymbolTable->createSymbols(conditionalNG->getSymbolTable(), dataSet(_parameterData));
     newSymbolTable->createSymbols(module->getLocalVariables());
     conditionalNG->setSymbolTable(newSymbolTable);

     bool result = ((FemaleDigitalExpressionSocket*)femaleSocket->bself())->evaluate();

     returnSymbols(newSymbolTable, QSet<Module::ParameterData*>(_parameterData->begin(), _parameterData->end()));

     conditionalNG->getStack()->setCount(currentStackPos);

     conditionalNG->setSymbolTable(newSymbolTable->getPrevSymbolTable());

     module->setCurrentConditionalNG(oldConditionalNG);

     return result;
 }

 /*private*/ QSet<VariableData*> DigitalCallModule::dataSet(QList<Module::ParameterData*>* list)
 {
  QSet<VariableData*> set = QSet<VariableData*>();
  for(Module::ParameterData* p : *list)
   set.insert((VariableData*)p);
  return set;
 }

 //@Override
 /*public*/  FemaleSocket* DigitalCallModule::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
     throw new UnsupportedOperationException("Not supported.");
 }

 //@Override
 /*public*/  int DigitalCallModule::getChildCount() {
     return 0;
 }

 //@Override
 /*public*/  QString DigitalCallModule::getShortDescription(QLocale locale) {
     return tr(/*locale,*/ "Call Module");
 }

 //@Override
 /*public*/  QString DigitalCallModule::getLongDescription(QLocale locale) {
     QString moduleName;
     if (_moduleHandle != nullptr) {
         moduleName = _moduleHandle->getBean()->getDisplayName();
     } else {
         moduleName = tr(/*locale,*/ "Not Selected");
     }

     return tr(/*locale,*/ "Call module: %1").arg(moduleName);
 }

 /** {@inheritDoc} */
 //@Override
 /*public*/  void DigitalCallModule::setup() {
     // Do nothing
 }

 /** {@inheritDoc} */
 //@Override
 /*public*/  void DigitalCallModule::registerListenersForThisClass() {
     // A module never listen on beans
 }

 /** {@inheritDoc} */
 //@Override
 /*public*/  void DigitalCallModule::unregisterListenersForThisClass() {
     // A module never listen on beans
 }

 /** {@inheritDoc} */
 //@Override
 /*public*/  void DigitalCallModule::disposeMe() {
     removeModule();
 }

 /*public*/  void DigitalCallModule::addParameter(
         QString name,
         InitialValueType::TYPES initialValueType,
         QString initialValueData,
         ReturnValueType::TYPES returnValueType,
         QString returnValueData) {

     _parameterData->append(
             new Module::ParameterData(
                     name,
                     initialValueType,
                     initialValueData,
                     returnValueType,
                     returnValueData));
 }

//    /*public*/  void removeParameter(String name) {
//        _parameterData.remove(name);
//    }

 /*public*/  QList<Module::ParameterData*> *DigitalCallModule::getParameterData() {
     return _parameterData;
 }


 /*private*/ /*final*/ /*static*/ Logger* DigitalCallModule::log = LoggerFactory::getLogger("DigitalCallModule");
}
