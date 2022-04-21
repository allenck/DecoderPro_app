#ifndef OR_H
#define OR_H
#include "femalesocketlistener.h"
#include "abstractdigitalexpression.h"
#include "femaledigitalexpressionsocket.h"
#include "abstractfemalesocket.h"

class Or : public AbstractDigitalExpression, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  Or(QString sys, QString user, QObject* parent= nullptr);
  /*public*/  Or(QString sys, QString user, QList<QMap<QString, QString>> expressionSystemNames, QObject* parent=nullptr);

  /* This class is public  since ExpressionOrXml needs to access it. */
  /*private*/ /*static*/ class ExpressionEntry {
      /*private*/ QString _socketSystemName;
      /*private*/ /*final*/ FemaleDigitalExpressionSocket* _socket;

      /*private*/ ExpressionEntry(FemaleDigitalExpressionSocket* socket, QString socketSystemName) {
          _socketSystemName = socketSystemName;
          _socket = (FemaleDigitalExpressionSocket*)socket->bself();
      }

      /*private*/ ExpressionEntry(FemaleDigitalExpressionSocket* socket) {
          this->_socket = (FemaleDigitalExpressionSocket*)socket->bself();
      }
    friend class Or;
  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  QString getExpressionSystemName(int index);
  /*public*/  Category* getCategory() override;
  /*public*/  bool evaluate() /*throws JmriException*/override;
  /*public*/  AbstractFemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void doSocketOperation(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void connected(FemaleSocket* socket) override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}
 private:
  static Logger* log;
  /*private*/ /*final*/ QList<ExpressionEntry*> _expressionEntries = QList<ExpressionEntry*>();
  /*private*/ bool disableCheckForUnconnectedSocket = false;
  /*private*/ void setExpressionSystemNames(QList<QMap<QString, QString>> systemNames);
  /*private*/ void setNumSockets(int num) ;
  /*private*/ void checkFreeSocket();
  /*private*/ void insertNewSocket(int index) ;
  /*private*/ void removeSocket(int index);
  /*private*/ void moveSocketDown(int index);

};

#endif // OR_H
