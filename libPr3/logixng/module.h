#ifndef MODULE_H
#define MODULE_H
#include "base.h"
#include "namedbean.h"
#include "femalesocketmanager.h"
#include <QSet>
#include "symboltable.h"

/**
 * An enum that defines the types of initial value.
 */
/*public*/ /*enum*/class ReturnValueType  : public QObject{
  Q_OBJECT
 public:
    enum TYPES
    { None, LocalVariable, Memory};
//        None(Bundle.getMessage("ReturnValueType_None")),
//        LocalVariable(Bundle.getMessage("ReturnValueType_LocalVariable")),
//        Memory(Bundle.getMessage("ReturnValueType_Memory"));

//       /*private*/ /*final*/ QString _descr;

//       /*private*/ ReturnValueType(QString descr) {
//           _descr = descr;
//       }

    /*public*/ static QString getDescr(TYPES t) {
        //return _descr;
     switch (t) {
     case None:
      return tr("");
     case LocalVariable:
      return tr("Local Variable");
     case Memory:
      return tr("Memory");
     }
    }
 };


/**
 * Represent a LogixNG module.
 * A module is similar to a ConditionalNG, except that it can be used by
 * both ConditionalNGs and modules.
 *
 * @author Daniel Bergqvist Copyright (C) 2020
 */
/*public*/ /*interface*/class Module : public virtual Base, public virtual NamedBean {
    Q_INTERFACES(Base NamedBean)
 public:
  /**
   * The definition of a parameter.
   */
  /*public*/  /*interface*/class Parameter {
   public:
      /**
       * The name of the parameter
       * @return the name
       */
      /*public*/ virtual QString getName()=0;

      /**
       * Answer whenether or not the parameter is input to the module.
       * @return true if the parameter is input, false otherwise
       */
      /*public*/ virtual bool isInput()=0;

      /**
       * Answer whenether or not the parameter is output to the module.
       * @return true if the parameter is output, false otherwise
       */
      /*public*/ virtual bool isOutput()=0;

  }; // end Parameter
//    public void setRootSocketType(FemaleSocketManager.SocketType socketType);

    /*public*/ virtual FemaleSocketManager::SocketType* getRootSocketType()=0;

    /*public*/ virtual FemaleSocket* getRootSocket()=0;

    /*public*/ virtual void setCurrentConditionalNG(ConditionalNG* conditionalNG)=0;

    /*public*/ virtual void addParameter(QString name, bool isInput, bool isOutput)=0;

    /*public*/ virtual void addParameter(Parameter* parameter)=0;

//    public void removeParameter(String name);

    /*public*/virtual void addLocalVariable(
            QString name,
            SymbolTable::InitialValueType::TYPES initialValueType,
            QString initialValueData)=0;

//    public void removeLocalVariable(String name);

    /*public*/ virtual QSet<Parameter*> getParameters()=0;

    /*public*/ virtual QSet<SymbolTable::VariableData*> getLocalVariables()=0;


    /**
     * Data for a parameter.
     */
    /*public*/ /*static*/ class ParameterData : public SymbolTable::VariableData
    {
     public:
        /*public*/ ReturnValueType::TYPES _returnValueType = ReturnValueType::TYPES::None;
        /*public*/ QString _returnValueData;


        /*public*/ ParameterData(
                QString name,
                SymbolTable::InitialValueType::TYPES initalValueType,
                QString initialValueData,
                ReturnValueType::TYPES returnValueType,
                QString returnValueData) : SymbolTable::VariableData(name, initalValueType, initialValueData){

            //super(name, initalValueType, initialValueData);

            _returnValueType = returnValueType;
            _returnValueData = returnValueData;
        }

        /*public*/ ParameterData(ParameterData* data) : SymbolTable::VariableData(data->_name, data->_initalValueType, data->_initialValueData){
            //super(data._name, data._initalValueType, data._initialValueData);
            _returnValueType = data->_returnValueType;
            _returnValueData = data->_returnValueData;
        }

        /*public*/ ReturnValueType::TYPES getReturnValueType() {
            return _returnValueType;
        }

        /*public*/ QString getReturnValueData() {
            return _returnValueData;
        }

  };

  virtual QObject* bself() =0;

};
Q_DECLARE_INTERFACE(Module, "Module")
#endif // MODULE_H
