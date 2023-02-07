#ifndef ANALOGMANY_H
#define ANALOGMANY_H
#include "abstractanalogaction.h"
#include "femalesocketlistener.h"
#include "femaleanalogactionsocket.h"

class AnalogMany : public AbstractAnalogAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  AnalogMany(QString sys, QString user, QObject* parent = nullptr);
  /*public*/  AnalogMany(QString sys, QString user, QList<QMap<QString, QString>> actionSystemNames, QObject* parent=nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override ;
  /*public*/  QString getActionSystemName(int index);
  /*public*/  void setup()override;
  /*public*/  Category getCategory() override;
  /*public*/  void setValue(double value) /*throws JmriException */override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void doSocketOperation(int index, FemaleSocketOperation::TYPES oper) override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;


  QObject* bself() override{return (QObject*)this;}
  QObject* self() override{return (QObject*)this;}

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
  /*private*/ /*static*/ class ActionEntry {
      /*private*/ QString _socketSystemName;
      /*private*/ /*final*/ FemaleAnalogActionSocket* _socket;

      /*private*/ ActionEntry(FemaleAnalogActionSocket* socket, QString socketSystemName) {
          _socketSystemName = socketSystemName;
          _socket = socket;
      }

      /*private*/ ActionEntry(FemaleAnalogActionSocket* socket) {
          this->_socket = socket;
      }
    friend class AnalogMany;
  };
  /*private*/ /*final*/ QList<ActionEntry*> _actionEntries = QList<ActionEntry*>();
  /*private*/ bool disableCheckForUnconnectedSocket = false;
  /*private*/ void setNumSockets(int num);
  /*private*/ void checkFreeSocket();
  /*private*/ void setActionSystemNames(QList<QMap<QString, QString>> systemNames);
  /*private*/ void insertNewSocket(int index);
  /*private*/ void removeSocket(int index);
  /*private*/ void moveSocketDown(int index);

};

#endif // ANALOGMANY_H
