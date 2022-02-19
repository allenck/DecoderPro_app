#ifndef DEFAULTSYMBOLTABLE_H
#define DEFAULTSYMBOLTABLE_H

#include "symboltable.h"
#include <QObject>
#include "conditionalng.h"
#include "recursivedescentparser.h"
#include "module.h"
#include "variable.h"

class Logger;
class DefaultSymbolTable : /*public QObject,*/ public SymbolTable
{
  Q_OBJECT
  Q_INTERFACES(SymbolTable)
 public:
  DefaultSymbolTable(QObject* parent = nullptr);
  /*public*/  DefaultSymbolTable(ConditionalNG* currentConditionalNG, QObject *parent=nullptr);
  /*public*/  DefaultSymbolTable(SymbolTable* prevSymbolTable, QObject* parent = nullptr);
  /*public*/  QMap<QString, Symbol*> getSymbols() override;
  /*public*/  SymbolTable* getPrevSymbolTable();
  /*public*/  QMap<QString, QVariant> getSymbolValues()override;
  /*public*/  QVariant getValue(QString name)override;
  /*public*/  bool hasValue(QString name)override;
  /*public*/  void setValue(QString name, QVariant value)override;
  /*public*/  void printSymbolTable(PrintWriter* stream)override;
  /*private*/ RecursiveDescentParser* createParser() /*throws ParserException*/;
  /*public*/  void createSymbols(/*Collection<? extends */QSet<VariableData*> symbolDefinitions) /*throws JmriException*/override;
  /*public*/  void createSymbols(SymbolTable* symbolTable,
                                 /*Collection<? extends*/ QSet<VariableData*> symbolDefinitions)
                                 /*throws JmriException*/override;
  /*public*/  void removeSymbols(QSet<VariableData*> symbolDefinitions) /*throws JmriException*/override;
  /*public*/  Stack* getStack()override;

 private:
  static Logger* log;
  /*private*/ /*final*/ SymbolTable* _prevSymbolTable;
  /*private*/ /*final*/ Stack* _stack;
  /*private*/ /*final*/ int _firstSymbolIndex;
  /*private*/ /*final*/ QMap<QString, Symbol*> _symbols = QMap<QString, Symbol*>();

public:

/*public*/  /*static*/ class DefaultSymbol : public Symbol {

    /*private*/ /*final*/ QString _name;
    /*private*/ /*final*/ int _index;
public:
  /*public*/  DefaultSymbol(QString name, int index) {
      _name = name;
      _index = index;
  }

  /** {@inheritDoc} */
  //@Override
  /*public*/  QString getName() {
      return _name;
  }

  /** {@inheritDoc} */
  //@Override
  /*public*/  int getIndex() {
      return _index;
  }
};

/*public*/  /*static*/  class DefaultParameter : public Module::Parameter {

    /*private*/ QString _name;
    /*private*/ bool _isInput;
    /*private*/ bool _isOutput;
public:
    /*public*/  DefaultParameter(QString name, bool isInput, bool isOutput) {
        _name = name;
        _isInput = isInput;
        _isOutput = isOutput;
    }

    /*public*/  DefaultParameter(Parameter* parameter) {
        _name = parameter->getName();
        _isInput = parameter->isInput();
        _isOutput = parameter->isOutput();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString getName() override{
        return _name;
    }

    /*public*/  void setName(QString name) {
        _name = name;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool isInput()override {
        return _isInput;
    }

    /*public*/  void setIsInput(bool value) {
        _isInput = value;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool isOutput() override{
        return _isOutput;
    }

    /*public*/  void setIsOutput(bool value) {
        _isOutput = value;
    }
 };
};
#endif // DEFAULTSYMBOLTABLE_H
