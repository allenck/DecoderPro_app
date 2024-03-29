#ifndef STRINGFORMULA_H
#define STRINGFORMULA_H

#include "abstractstringexpression.h"
#include "femalesocketlistener.h"
#include "expressionnode.h"
#include "femalesocketoperation.h"
#include "femalegenericexpressionsocket.h"


class FemaleGenericExpressionSocket;
class ExpressionEntry;
class SocketData;
class StringFormula : public AbstractStringExpression, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
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
  explicit StringFormula(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user, QObject *parent = nullptr);
  /*public*/  StringFormula(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
          QList<SocketData*> expressionSystemNames, QObject* parent =nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/ QString getExpressionSystemName(int index);
  /*public*/  QString getExpressionManager(int index);
  /*public*/  /*final*/ void setFormula(QString formula) /*throws ParserException*/ ;
  /*public*/  QString getFormula();
  /*public*/  Category getCategory()override;
  /*public*/  QString evaluate() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  void setChildCount(int count);
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale) override;
  /*public*/  bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void doSocketOperation(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  void socketNameChanged(FemaleSocket* socket)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /* This class is public  since ExpressionFormulaXml needs to access it. */
  /*public*/  /*static*/ class ExpressionEntry {
      /*private*/ /*final*/ FemaleGenericExpressionSocket* _socket;
      /*private*/ QString _socketSystemName;
      /*public*/  QString _manager;
      public:
      /*public*/  ExpressionEntry(FemaleGenericExpressionSocket* socket, QString socketSystemName, QString manager) {
          _socket = socket;
          _socketSystemName = socketSystemName;
          _manager = manager;
      }

      /*private*/ ExpressionEntry(FemaleGenericExpressionSocket* socket) {
          this->_socket = socket;
      }
    friend class StringFormula;
  };
    /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.expressions.StringFormula";}


  QObject* bself() override{return (QObject*)this;}

  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
   AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
  }
  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                    QString name, QString listenerRef) override {
   AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
  }
  /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
  /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
  /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
  /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
  /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
   return AbstractNamedBean::getPropertyChangeListenersByReference(name);
  }
  void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

 private:
  static Logger* log;
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ /*final*/ QList<ExpressionEntry*> _expressionEntries = QList<ExpressionEntry*>();
  /*private*/ FemaleGenericExpressionSocket* createFemaleSocket(
          Base* parent, FemaleSocketListener* listener, QString socketName);
  /*private*/ void parseFormula() ;
  /*private*/ void setNumSockets(int num);
  /*private*/ void checkFreeSocket();
  /*private*/ bool _disableCheckForUnconnectedSocket = false;
  /*private*/ void setExpressionSystemNames(QList<SocketData*> systemNames);
  /*private*/ void insertNewSocket(int index);
  /*private*/ void removeSocket(int index);
  /*private*/ void moveSocketDown(int index);

};

#endif // STRINGFORMULA_H
