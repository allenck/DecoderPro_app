#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <QObject>
#include "exceptions.h"
#include <QSet>
#include "printwriter.h"
#include <QMetaEnum>
class Stack;
class VariableData;

/**
 * A symbol table
 *
 * @author Daniel Bergqvist 2020
 */
/*public*/ /*interface*/ class SymbolTable  : public QObject{
 Q_OBJECT
 public:
    /*public*/ /*interface*/class Symbol  : public QObject{
      //Q_OBJECT
     public:
      Symbol(QObject* parent = nullptr) : QObject(parent) {}
        /**
         * The name of the symbol
         * @return the name
         */
        /*public*/ virtual QString getName()=0;

        /**
         * The index on the stack for this symbol
         * @return the index
         */
        /*public*/ virtual int getIndex()=0;

    }; // Symbol

    /**
     * An enum that defines the types of initial value.
     */
    /*public*/ /*enum*/class InitialValueType  : public QObject{
      //Q_OBJECT
    public:
        enum TYPES {None, Integer, FloatingNumber, String, LocalVariable, Memory, Reference, Formula};
//        Q_ENUM(TYPES)
    //        None(Bundle.getMessage("InitialValueType_None")),
    //        Integer(Bundle.getMessage("InitialValueType_Integer")),
    //        FloatingNumber(Bundle.getMessage("InitialValueType_FloatingNumber")),
    //        String(Bundle.getMessage("InitialValueType_String")),
    //        LocalVariable(Bundle.getMessage("InitialValueType_LocalVariable")),
    //        Memory(Bundle.getMessage("InitialValueType_Memory")),
    //        Reference(Bundle.getMessage("InitialValueType_Reference")),
    //        Formula(Bundle.getMessage("InitialValueType_Formula"));
    private:
        /*private*/ /*final*/ QString _descr;
        TYPES t;
        QMap<QString, TYPES> map = {
         {tr("None"), None}, {tr("Integer"), Integer}, {tr("Floating number"), FloatingNumber}, {tr("String"), String},
         {tr("Local variable"), LocalVariable}, {tr("Memory"), Memory}, {tr("Reference"), Reference}, {tr("Formula"), Formula}
        };
        /*private*/ InitialValueType(QString descr) {
            _descr = descr;
            t=map.value(descr);
        }
    public:
        //@Override
        /*public*/ static QString toString(TYPES t) {
           switch(t)
           {
            case None:
              return tr("None");
           case Integer:
            return tr("Integer");
           case FloatingNumber:
            return tr("FloatigNumber");
           case String:
            return tr("String");
           case LocalVariable:
            return tr("Local variable");
           case Memory:
            return tr("Memory");
           case Reference:
            return tr("Reference");
           case Formula:
            return tr("Formula");
           default:
            return "??";
           }
        }
     /*public*/ static TYPES toType(QString s)
        {
         QMap<QString, TYPES> map = {
          {tr("None"), None}, {tr("Integer"), Integer}, {tr("Floating number"), FloatingNumber}, {tr("String"), String},
          {tr("Local variable"), LocalVariable}, {tr("Memory"), Memory}, {tr("Reference"), Reference}, {tr("Formula"), Formula}
         };
         return map.value(s);
        }
        /*public*/ static QList<TYPES> values()
        {
         return QList<TYPES>{None, Integer, FloatingNumber, String, LocalVariable, Memory, Reference, Formula};
        }
  }; // InitiaValueType


    /**
     * Data for a variable.
     */
    /*public*/ /*static*/ class VariableData : public QObject {
    //Q_OBJECT
        public:
        /*public*/ QString _name;
        /*public*/ InitialValueType::TYPES _initalValueType = InitialValueType::None;
        /*public*/ QString _initialValueData;

        /*public*/ VariableData(
                QString name,
                InitialValueType::TYPES initalValueType,
                QString initialValueData) {

            _name = name;
            _initalValueType = initalValueType;
            _initialValueData = initialValueData;
        }

    /*public*/ VariableData(VariableData* variableData) {
        _name = variableData->_name;
        _initalValueType = variableData->_initalValueType;
        _initialValueData = variableData->_initialValueData;
    }

    /**
     * The name of the variable
     * @return the name
     */
    /*public*/ QString getName() {
        return _name;
    }

    /*public*/ InitialValueType::TYPES getInitalValueType() {
        return _initalValueType;
    }

    /*public*/ QString getInitialValueData() {
        return _initialValueData;
    }
 }; // VariableData
    SymbolTable(QObject* parent = nullptr) : QObject(parent) {}
  /**
   * The definition of the symbol
   */


  /**
     * The list of symbols in the table
     * @return the symbols
     */
    /*public*/ virtual QMap<QString, Symbol*> getSymbols()=0;

    /**
     * The list of symbols and their values in the table
     * @return the name of the symbols and their values
     */
    /*public*/ virtual QMap<QString, QVariant> getSymbolValues()=0;

    /**
     * Get the value of a symbol
     * @param name the name
     * @return the value
     */
    /*public*/ virtual QVariant getValue(QString name)=0;

    /**
     * Is the symbol in the symbol table?
     * @param name the name
     * @return true if the symbol exists, false otherwise
     */
    /*public*/ virtual bool hasValue(QString name)=0;

    /**
     * Set the value of a symbol
     * @param name the name
     * @param value the value
     */
    /*public*/ virtual void setValue(QString name, QVariant value)=0;

    /**
     * Add new symbols to the symbol table
     * @param symbolDefinitions the definitions of the new symbols
     * @throws JmriException if an exception is thrown
     */
    /*public*/ virtual void createSymbols(/*Collection<? extends VariableData>*/ QSet<VariableData*> symbolDefinitions)
            /*throw (JmriException)*/=0;

    /**
     * Add new symbols to the symbol table.
     * This method is used for parameters, when new symbols might be created
     * that uses symbols from a previous symbol table.
     *
     * @param symbolTable the symbol table to get existing symbols from
     * @param symbolDefinitions the definitions of the new symbols
     * @throws JmriException if an exception is thrown
     */
    /*public*/ virtual void createSymbols(
            SymbolTable* symbolTable,
            /*Collection<? extends VariableData>*/QSet<VariableData*> symbolDefinitions)
            /*throw (JmriException)*/=0;

    /**
     * Removes symbols from the symbol table
     * @param symbolDefinitions the definitions of the symbols to be removed
     * @throws JmriException if an exception is thrown
     */
    /*public*/ virtual void removeSymbols(/*Collection<? extends VariableData>*/QSet<VariableData*> symbolDefinitions)
            /*throw (JmriException)*/=0;

    /**
     * Print the symbol table on a stream
     * @param stream the stream
     */
    /*public*/ virtual void printSymbolTable(PrintWriter* stream)=0;

    /**
     * Validates the name of a symbol
     * @param name the name
     * @return true if the name is valid, false otherwise
     */
    /*public*/ static bool validateName(QString name) {
        if (name.isEmpty()) return false;
        if (!/*Character.isLetter(*/name.at(0).isLetter()) return false;
        for (int i=0; i < name.length(); i++) {
            if (!name.at(i).isLetterOrNumber() && (name.at(i) != '_')) {
                return false;
            }
        }
        return true;
    }

    /**
     * Get the stack.
     * This method is only used internally by DefaultSymbolTable.
     *
     * @return the stack
     */
    /*public*/ virtual Stack* getStack()=0;




      /*public*/ /*static*/ class SymbolNotFound : public IllegalArgumentException {
       public:
          /*public*/ SymbolNotFound(QString message) :  IllegalArgumentException(message){
              //super(message);
          }
      }; // SymbolNotFound


};  //SymbolTable

Q_DECLARE_INTERFACE(SymbolTable, "SymbolTable")
#endif // SYMBOLTABLE_H
