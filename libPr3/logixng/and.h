#ifndef AND_H
#define AND_H

#include "abstractdigitalexpression.h"
#include "femalesocketlistener.h"

class FemaleDigitalExpressionSocket;
class ExpressionEntry;
class And : public AbstractDigitalExpression, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  Q_INVOKABLE explicit And(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  And(QString sys, QString user, QList<QMap<QString, QString>> expressionSystemNames, QObject* parent=nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /* This class is public  since ExpressionAndXml needs to access it. */
  /*private*/ /*static*/ class ExpressionEntry {
      /*private*/ QString _socketSystemName;
      /*private*/ /*final*/ FemaleDigitalExpressionSocket* _socket;

      /*private*/ ExpressionEntry(FemaleDigitalExpressionSocket* socket, QString socketSystemName) {
          _socketSystemName = socketSystemName;
          _socket = socket;
      }

      /*private*/ ExpressionEntry(FemaleDigitalExpressionSocket* socket) {
          this->_socket = socket;
      }
    friend class And;
  };
  /*public*/  QString getExpressionSystemName(int index);
  /*public*/  Category getCategory() override;
  /*public*/  bool evaluate() /*throws JmriException*/ override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) override;
  /*public*/  void doSocketOperation(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket) override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

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
 private:
  static Logger* log;
  /*private*/ /*final*/ QList<ExpressionEntry*> _expressionEntries = QList<ExpressionEntry*>();
  /*private*/ bool disableCheckForUnconnectedSocket = false;
  Q_INVOKABLE/*private*/ void setExpressionSystemNames(QList<QMap<QString, QString>> systemNames);
  /*private*/ void setNumSockets(int num);
  /*private*/ void checkFreeSocket();
  /*private*/ void insertNewSocket(int index);
  /*private*/ void removeSocket(int index);
  /*private*/ void moveSocketDown(int index);

};

#endif // AND_H
