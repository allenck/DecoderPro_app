#ifndef ACTIONLOCALVARIABLE_H
#define ACTIONLOCALVARIABLE_H

#include "abstractdigitalaction.h"
#include "vetoablechangelistener.h"
#include "namedbeanhandle.h"
#include "memory.h"

class ExpressionNode;
class VariableOperation;
class ActionLocalVariable : public AbstractDigitalAction, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:
  /*public*/  /*enum*/class VariableOperation {
   public:
//      SetToNull(Bundle.getMessage("ActionLocalVariable_VariableOperation_SetToNull")),
//      SetToString(Bundle.getMessage("ActionLocalVariable_VariableOperation_SetToString")),
//      CopyVariableToVariable(Bundle.getMessage("ActionLocalVariable_VariableOperation_CopyVariableToVariable")),
//      CopyMemoryToVariable(Bundle.getMessage("ActionLocalVariable_VariableOperation_CopyMemoryToVariable")),
//      CopyTableCellToVariable(Bundle.getMessage("ActionLocalVariable_VariableOperation_CopyTableCellToVariable")),
//      CalculateFormula(Bundle.getMessage("ActionLocalVariable_VariableOperation_CalculateFormula"));
    enum TYPE {SetToNull, SetToString, CopyVariableToVariable, CopyMemoryToVariable, CopyTableCellToVariable, CalculateFormula};

//      /*private*/ final String _text;

//      /*private*/ VariableOperation(String text) {
//          this._text = text;
//      }

      //@Override
      /*public*/static  QString toString(TYPE t) {
          switch(t)
          {
          case SetToNull: return tr("Null");
           case SetToString: return tr("Constant");
           case CopyVariableToVariable: return tr("Variable");
           case CopyMemoryToVariable: return tr("Memory");
           case CopyTableCellToVariable: return tr("Table");
          case CalculateFormula: return tr("Formula");
          }
          throw new IllegalArgumentException();
      }
    /*public*/static TYPE valueOf(QString s)
    {
     if(s ==tr("Null")) return SetToNull;
     if(s ==tr("Constant")) return  SetToString;
     if(s ==tr("Variable")) return CopyVariableToVariable;
     if(s ==tr("Memory")) return CopyMemoryToVariable;
     if(s ==tr("Table")) return CopyTableCellToVariable;
     if(s ==tr("Formula")) return CalculateFormula;

     throw new IllegalArgumentException();

    }
  };

  ActionLocalVariable(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/override;
  /*public*/  void setLocalVariable(QString variableName) ;
  /*public*/  QString getLocalVariable();
  /*public*/  void setMemory(/*@Nonnull*/ QString memoryName) ;
  /*public*/  void setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle);
  /*public*/  void setMemory(/*CheckForNull*/ Memory* memory);
  /*public*/  void removeMemory();
  /*public*/  NamedBeanHandle<Memory*>* getMemory() ;
  /*public*/  void setVariableOperation(VariableOperation::TYPE variableOperation) /*throws ParserException*/;
  /*public*/  ActionLocalVariable::VariableOperation::TYPE getVariableOperation();
  /*public*/  void setOtherTableCell(/*@Nonnull*/ QString tableCell);
  /*public*/  QString getOtherTableCell() ;
  /*public*/  static QString convertTableReference(QString string, bool toReference);
  /*public*/  void setOtherLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getOtherLocalVariable() ;
  /*public*/  void setConstantValue(QString constantValue);
  /*public*/  QString getConstantValue() ;
  /*public*/  void setFormula(QString formula) /*throws ParserException*/;
  /*public*/  QString getFormula() ;
  /*public*/  void setListenToMemory(bool listenToMemory);
  /*public*/  bool getListenToMemory() ;
  /*public*/  Category* getCategory() override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount() override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale) override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

  QObject* pself() override {return (QObject*)this;}

 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;
  /*public*/  void propertyChange(PropertyChangeEvent* evt) override;

 private:
  static Logger* log;
  /*private*/ QString _localVariable;
  /*private*/ NamedBeanHandle<Memory*>* _memoryHandle = nullptr;
  /*private*/ VariableOperation::TYPE _variableOperation = VariableOperation::SetToString;
  /*private*/ QString _constantValue = "";
  /*private*/ QString _otherTableCell = "";
  /*private*/ QString _otherLocalVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ bool _listenToMemory = true;
//    /*private*/ boolean _listenToMemory = false;
  /*private*/ void parseFormula() /*throws ParserException*/;

};

#endif // ACTIONLOCALVARIABLE_H
