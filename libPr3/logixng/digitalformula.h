#ifndef DIGITALFORMULA_H
#define DIGITALFORMULA_H

#include "abstractdigitalexpression.h"
#include "femalesocketlistener.h"
#include "expressionnode.h"

class SocketData;
class FemaleGenericExpressionSocket;
class DigitalFormula : public AbstractDigitalExpression, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  DigitalFormula(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user, QObject *parent = nullptr);
  /* This class is public since ExpressionFormulaXml needs to access it. */
  /*public*/ /*static*/ class ExpressionEntry {
      /*private*/ /*final*/ FemaleGenericExpressionSocket* _socket;
      /*private*/ QString _socketSystemName;
   public:
      /*public*/ QString _manager;

      /*public*/ ExpressionEntry(FemaleGenericExpressionSocket* socket, QString socketSystemName, QString manager) {
          _socket = socket;
          _socketSystemName = socketSystemName;
          _manager = manager;
      }
      private:
      /*private*/ ExpressionEntry(FemaleGenericExpressionSocket* socket) {
          this->_socket = socket;
      }
      friend class DigitalFormula;
  };
  /*public*/  /*static*/ class SocketData {
   public:
      /*public*/  /*final*/ QString _socketName;
      /*public*/  /*final*/ QString _socketSystemName;
      /*public*/  /*final*/ QString _manager;

      /*public*/  SocketData(QString socketName, QString socketSystemName, QString manager) {
          _socketName = socketName;
          _socketSystemName = socketSystemName;
          _manager = manager;
      }
  };


  /*public*/  DigitalFormula(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
          QList<SocketData*> expressionSystemNames, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  QString getExpressionSystemName(int index) ;
  /*public*/  QString getExpressionManager(int index);
  /*public*/  /*final*/ void setFormula(QString formula) /*throws ParserException */;
  /*public*/  QString getFormula();
  /*public*/  Category getCategory()override;
  /*public*/  bool evaluate() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  void setChildCount(int count);
  /*public*/  QString getShortDescription(QLocale locale) override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void doSocketOperation(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  void socketNameChanged(FemaleSocket* socket)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* bself() override{return (QObject*)this;}
  QObject* self() override{return (QObject*)this;}

 private:
  static Logger* log;
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ /*final*/ QList<ExpressionEntry*> _expressionEntries = QList<ExpressionEntry*>();
  /*private*/ bool _disableCheckForUnconnectedSocket = false;
  /*private*/ void setExpressionSystemNames(QList<SocketData*> systemNames);
  /*private*/ FemaleGenericExpressionSocket* createFemaleSocket(
          Base* parent, FemaleSocketListener* listener, QString socketName);
  /*private*/ void parseFormula();
  /*private*/ void setNumSockets(int num) ;
  /*private*/ void checkFreeSocket();
  /*private*/ void insertNewSocket(int index);
  /*private*/ void removeSocket(int index);
  /*private*/ void moveSocketDown(int index);

};

#endif // DIGITALFORMULA_H
