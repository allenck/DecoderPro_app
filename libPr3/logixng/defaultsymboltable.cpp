#include "defaultsymboltable.h"
#include "loggerfactory.h"
#include "defaultstack.h"
#include "memory.h"
#include "defaultmemorymanager.h"
#include "instancemanager.h"
#include "referenceutil.h"
#include "localvariableexpressionvariable.h"

/**
 * The default implementation of a NamedTable
 *
 * @author Daniel Bergqvist 2020
 */
// /*public*/  class DefaultSymbolTable implements SymbolTable {



    /**
     * Create a new instance of DefaultSymbolTable with no previous symbol table.
     */
    /*public*/  DefaultSymbolTable::DefaultSymbolTable(QObject *parent) : SymbolTable(parent){
     setObjectName("DefaultSymbolTable");
        _prevSymbolTable = nullptr;
        _stack = new DefaultStack();
        _firstSymbolIndex = _stack->getCount();
    }

    /**
     * Create a new instance of DefaultSymbolTable with previous symbol table
     * and the stack from a ConditionalNG.
     * @param currentConditionalNG the ConditionalNG
     */
    /*public*/  DefaultSymbolTable::DefaultSymbolTable(ConditionalNG* currentConditionalNG, QObject *parent): SymbolTable( parent) {
        _prevSymbolTable = currentConditionalNG->getSymbolTable();
        _stack = currentConditionalNG->getStack();
        _firstSymbolIndex = _stack->getCount();
    }

    /**
     * Create a new instance of DefaultSymbolTable from a previous symbol table
     * and a stack.
     * @param prevSymbolTable the previous symbol table
     */
    /*public*/  DefaultSymbolTable::DefaultSymbolTable(SymbolTable* prevSymbolTable, QObject *parent) : SymbolTable( parent){
        _prevSymbolTable = nullptr;
        //_symbols.putAll(prevSymbolTable->getSymbols());
        QMapIterator<QString, Symbol*> iter(prevSymbolTable->getSymbols());
        while(iter.hasNext())
        {
         iter.next();
         _symbols.insert(iter.key(), iter.value());
        }
        _stack = new DefaultStack();
        for (int i=0; i < prevSymbolTable->getStack()->getCount(); i++) {
            _stack->setValueAtIndex(i, prevSymbolTable->getStack()->getValueAtIndex(i));
        }
        _firstSymbolIndex = _stack->getCount();
    }

    /**
     * Get the previous symbol table
     * @return the symbol table
     */
    /*public*/  SymbolTable* DefaultSymbolTable::getPrevSymbolTable() {
        return _prevSymbolTable;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QMap<QString, Symbol *> DefaultSymbolTable::getSymbols() {
        //return Collections.unmodifiableMap(_symbols);
         return QMap<QString, Symbol*>(_symbols);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QMap<QString, QVariant> DefaultSymbolTable::getSymbolValues() {
        QMap<QString, QVariant> symbolValues = QMap<QString, QVariant>();
        for (Symbol* symbol : _symbols.values()) {
            QVariant value = _stack->getValueAtIndex(_firstSymbolIndex + symbol->getIndex());
            symbolValues.insert(symbol->getName(), value);
        }
        return QMap<QString, QVariant>(symbolValues);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QVariant DefaultSymbolTable::getValue(QString name) {
        Symbol* symbol = _symbols.value(name);
        if (symbol == nullptr) {
            throw new SymbolNotFound(QString("Symbol '%1' does not exist in symbol table").arg(name));
        }
        return _stack->getValueAtIndex(_firstSymbolIndex + symbol->getIndex());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultSymbolTable::hasValue(QString name) {
        return _symbols.contains(name);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultSymbolTable::setValue(QString name, QVariant value) {
        if (_symbols.value(name) == nullptr)
         throw new IllegalArgumentException("The symbol "+name+" does not exist in the symbol table");
        _stack->setValueAtIndex(_firstSymbolIndex + _symbols.value(name)->getIndex(), value);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultSymbolTable::printSymbolTable(PrintWriter* stream) {
#if 0 // TODO:
        stream->format("printSymbolTable:%n");
        //for (Map.Entry<String, Symbol> entry : _symbols.entrySet()) {
         QMapIterator<QString, Symbol*> entry(_symbols);
         while(entry.hasNext())
         {
          entry.next();
            stream->format("Key: %s, Name: %s, Index: %d, Value: %s%n",
                    entry.key(),
                    entry.value()->getName(),
                    entry.value()->getIndex(),
                    _stack->getValueAtIndex(_firstSymbolIndex + entry.value()->getIndex()));
        }
        stream->format("printSymbolTable done%n");
#endif
    }

    /*private*/ RecursiveDescentParser* DefaultSymbolTable::createParser() /*throws ParserException */{
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        for (Symbol* symbol : getSymbols().values()) {
            variables.insert(symbol->getName(),
                    new LocalVariableExpressionVariable(symbol->getName()));
        }

        return new RecursiveDescentParser(variables);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultSymbolTable::createSymbols(/*Collection<? extends SymbolTable.*/QSet<VariableData*> symbolDefinitions) /*throws JmriException*/ {
        createSymbols(this, symbolDefinitions);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultSymbolTable::createSymbols(SymbolTable* symbolTable,
            /*Collection<? extends SymbolTable.*/QSet<VariableData*> symbolDefinitions)
            /*throws JmriException */{

        for (VariableData* variable : symbolDefinitions) {
            Symbol* symbol = new DefaultSymbol(variable->getName(), _stack->getCount() - _firstSymbolIndex);
            QVariant initialValue = QVariant();

            if (_symbols.contains(symbol->getName())) {
                throw new IllegalArgumentException("Symbol table already contains the variable " + symbol->getName());
            }

            switch (variable->getInitalValueType()) {
                case InitialValueType::None:
                    break;

                case InitialValueType::Integer:
                    initialValue = /*Long.parseLong*/(variable->getInitialValueData());
                    break;

                case InitialValueType::FloatingNumber:
                    initialValue = /*Double.parseDouble*/(variable->getInitialValueData());
                    break;

                case InitialValueType::String:
                    initialValue = variable->getInitialValueData();
                    break;

                case InitialValueType::LocalVariable:
                    initialValue = symbolTable->getValue(variable->getInitialValueData());
//                    initialValue = _prevSymbolTable.getValue(variable->getInitialValueData());
                    break;

                case InitialValueType::Memory:
                {
                    Memory* m = (Memory*)((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getNamedBean(variable->getInitialValueData())->self();
                    if (m != nullptr) initialValue = m->getValue();
                    break;
                }
                case InitialValueType::Reference:
                    if (ReferenceUtil::isReference(variable->getInitialValueData())) {
                        initialValue = ReferenceUtil::getReference(
                                symbolTable, variable->getInitialValueData());
                    } else {
                        log->error(tr("\"%1\" is not a reference").arg(variable->getInitialValueData()));
                    }
                    break;

                case InitialValueType::Formula:
                {
                    RecursiveDescentParser* parser = createParser();
                    ExpressionNode* expressionNode = parser->parseExpression(
                            variable->getInitialValueData());
                    initialValue = expressionNode->calculate(symbolTable);
                    break;
                }
                default:
                    log->error(tr("definition._initalValueType has invalid value: %1").arg(InitialValueType::toString(variable->getInitalValueType())));
                    throw new IllegalArgumentException("definition._initalValueType has invalid value: " + InitialValueType::toString(variable->getInitalValueType()));
            }

//            System.out.format("Add symbol: %s = %s%n", symbol.getName(), initialValue);

            _stack->push(initialValue);
            _symbols.insert(symbol->getName(), symbol);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultSymbolTable::removeSymbols(/*Collection<? extends SymbolTable.*/QSet<VariableData*> symbolDefinitions) /*throws JmriException */{
        //symbolDefinitions.forEach((parameter) -> {
        foreach(VariableData* parameter, symbolDefinitions){
            _symbols.remove(parameter->getName());
        }//);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Stack* DefaultSymbolTable::getStack() {
        return _stack;
    }

#if 0
//    /*public*/  static class DefaultSymbol : public Symbol {

//        private final String _name;
//        private final int _index;

        /*public*/  DefaultSymbol::DefaultSymbol(String name, int index) {
            _name = name;
            _index = index;
        }

        /** {@inheritDoc} */
        //@Override
        /*public*/  QString DefaultSymbol::getName() {
            return _name;
        }

        /** {@inheritDoc} */
        //@Override
        /*public*/  int DefaultSymbol::getIndex() {
            return _index;
        }

//    }


    /*public*/  static class DefaultParameter implements Parameter {

        private String _name;
        private boolean _isInput;
        private boolean _isOutput;

        /*public*/  DefaultParameter(String name, boolean isInput, boolean isOutput) {
            _name = name;
            _isInput = isInput;
            _isOutput = isOutput;
        }

        /*public*/  DefaultParameter(Parameter parameter) {
            _name = parameter.getName();
            _isInput = parameter.isInput();
            _isOutput = parameter.isOutput();
        }

        /** {@inheritDoc} */
        @Override
        /*public*/  String getName() {
            return _name;
        }

        /*public*/  void setName(String name) {
            _name = name;
        }

        /** {@inheritDoc} */
        @Override
        /*public*/  boolean isInput() {
            return _isInput;
        }

        /*public*/  void setIsInput(boolean value) {
            _isInput = value;
        }

        /** {@inheritDoc} */
        @Override
        /*public*/  boolean isOutput() {
            return _isOutput;
        }

        /*public*/  void setIsOutput(boolean value) {
            _isOutput = value;
        }

    }
#endif

    /*private*/ /*final*/ Logger* DefaultSymbolTable::log = LoggerFactory::getLogger("DefaultSymbolTable");

