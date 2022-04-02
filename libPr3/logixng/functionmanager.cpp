#include "functionmanager.h"
#include "functionfactory.h"
#include "constant.h"
#include "function.h"
#include "runtimeexception.h"
#include "stringfunctions.h"
#include "clockfunctions.h"
#include "mathfunctions.h"
#include "convertfunctions.h"

/**
 * Manager for LogixNG formula functions.
 *
 * @author Daniel Bergqvist   Copyright (C) 2020
 */
///*public*/  class FunctionManager implements jmri.InstanceManagerAutoDefault {



    /*public*/  FunctionManager::FunctionManager(QObject* parent) : QObject(parent){
     setObjectName("FunctionManager");
        //for (FunctionFactory* actionFactory : ServiceLoader::load("FunctionFactory"))
        QList<FunctionFactory*> list = {new StringFunctions(), new ClockFunctions() , new MathFunctions(), new ConvertFunctions()};
        foreach (FunctionFactory* actionFactory, list)
        {
            //actionFactory.getConstants().forEach((constant) -> {
         foreach(Constant* constant, actionFactory->getConstants())
         {
                if (_constants.contains(constant->getName()))
                {
                    throw new RuntimeException("Constant " + constant->getName() + " is already registered. Class: " + constant->metaObject()->className());
                }
//                System.err.format("Add constant %s, %s%n", constant.getName(), constant.getClass().getName());
                _constants.insert(constant->getName(), constant);
         }//);
         //actionFactory->getFunctions().forEach((function) -> {
         foreach(Function* function, actionFactory->getFunctions())
         {
             if (_functions.contains(function->getName())) {
                 throw new RuntimeException("Function " + function->getName() + " is already registered. Class: " + function->self()->metaObject()->className());
             }
//                System.err.format("Add function %s, %s%n", function.getName(), function.getClass().getName());
             _functions.insert(function->getName(), function);
         }//);
        }
    }

    /*public*/  QMap<QString, Function*> FunctionManager::getFunctions() {
        return/* Collections.unmodifiableMap*/QMap<QString, Function*>(_functions);
    }

    /*public*/  Function* FunctionManager::get(QString name) {
        return _functions.value(name);
    }

    /*public*/  Function* FunctionManager::put(QString name, Function* function) {
         _functions.insert(name, function);
             return function;
    }

    /*public*/  Constant* FunctionManager::getConstant(QString name) {
        return _constants.value(name);
    }

    /*public*/  void FunctionManager::put(QString name, Constant* constant) {
        _constants.insert(name, constant);
    }
