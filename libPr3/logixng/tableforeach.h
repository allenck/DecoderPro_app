#ifndef TABLEFOREACH_H
#define TABLEFOREACH_H

#include "abstractdigitalaction.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "namedtable.h"
#include "expressionnode.h"
#include "namedbeanaddressing.h"
#include "tableroworcolumn.h"
#include "femaledigitalactionsocket.h"
#include "femalesocketlistener.h"
class TableForEach : public AbstractDigitalAction, public FemaleSocketListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener VetoableChangeListener)

 public:
  TableForEach(QString sys, QString user, QObject* parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/;
  /*public*/  Category* getCategory();
  /*public*/  void execute() /*throws JmriException */;
  /*public*/  void setTable(/*@Nonnull*/ QString tableName);
  /*public*/  void setAddressing(NamedBeanAddressing addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing getAddressing();
  /*public*/  void setTable(/*@Nonnull*/ NamedBeanHandle<NamedTable*> handle);
  /*public*/  void setTable(/*@Nonnull*/ NamedTable* turnout);
  /*public*/  void removeTable();
  /*public*/  NamedBeanHandle<NamedTable*>* getTable();
  /*public*/  void setTableReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getTableReference();
  /*public*/  void setTableLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getTableLocalVariable();
  /*public*/  void setTableFormula(/*@Nonnull*/ QString formula) /*throws ParserException */;
  /*public*/  QString getTableFormula();
  /*public*/  TableRowOrColumn* getRowOrColumn();
  /*public*/  void setRowOrColumn(/*@Nonnull*/ TableRowOrColumn::TYPE tableRowOrColumn);
  /*public*/  void setRowOrColumnAddressing(NamedBeanAddressing addressing) /*throws ParserException*/ ;
  /*public*/  QString getRowOrColumnName();
  /*public*/  void setRowOrColumnName(/*@Nonnull*/ QString rowOrColumnName);
  /*public*/  void setRowOrColumnReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getRowOrColumnReference() ;
  /*public*/  void setRowOrColumnLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getRowOrColumnLocalVariable();
  /*public*/  void setRowOrColumnFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getRowOrColumnFormula();
  /*public*/ QString getLocalVariableName();
  /*public*/  void setLocalVariableName(QString localVariableName) ;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount() override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket) override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  FemaleDigitalActionSocket* getSocket();
  /*public*/  QString getSocketSystemName();
  /*public*/  void setSocketSystemName(QString systemName) ;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* self() override{return (QObject*)this;}

  QString getSystemName() const override{return AbstractNamedBean::getSystemName();}
  QString getComment()  override{return AbstractNamedBean::getComment();}
  void setUserName(QString name) override{AbstractNamedBean::setUserName(name);}
//  bool isSocketOperatioAllowed(int index, FemaleSocketOperation::TYPES oper) {return AbstractBase::isSocketOperationAllowed(index,oper);}
//   void doSocketOperation() {AbstractBase::doSocketOperation();}
 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException */override;

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<NamedTable*>* _tableHandle = nullptr;
  /*private*/ QString _tableReference = "";
  /*private*/ QString _tableLocalVariable = "";
  /*private*/ QString _tableFormula = "";
  /*private*/ ExpressionNode* _tableExpressionNode;
  /*private*/ NamedBeanAddressing::TYPE _rowOrColumnAddressing = NamedBeanAddressing::Direct;
  /*private*/ TableRowOrColumn::TYPE _tableRowOrColumn = TableRowOrColumn::Row;
  /*private*/ QString _rowOrColumnName = "";
  /*private*/ QString _rowOrColumnReference = "";
  /*private*/ QString _rowOrColumnLocalVariable = "";
  /*private*/ QString _rowOrColumnFormula = "";
  /*private*/ ExpressionNode* _rowOrColumnExpressionNode;
  /*private*/ QString _variableName = "";
  /*private*/ QString _socketSystemName;
  /*private*/ /*final*/ FemaleDigitalActionSocket* _socket;
  /*private*/ QString getNewRowOrColumnName() /*throws JmriException*/;
  /*private*/ void parseTableFormula() /*throws ParserException*/;
  /*private*/ void parseRowOrColumnFormula() /*throws ParserException*/;

};

#endif // TABLEFOREACH_H
