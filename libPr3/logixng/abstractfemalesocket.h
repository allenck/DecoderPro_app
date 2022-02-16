#ifndef ABSTRACTFEMALESOCKET_H
#define ABSTRACTFEMALESOCKET_H

#include <QObject>
#include "femalesocketlistener.h"
#include "socketalreadyconnectedexception.h"
#include "swingpropertychangesupport.h"
#include "base.h"
#include "femalesocket.h"
#include "abstractbase.h"

class AbstractFemaleSocket : public QObject, public FemaleSocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocket)
 public:
  /*public*/ AbstractFemaleSocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObject = nullptr);
  /*public*/ void setEnableListeners(bool enable)override;
  /*public*/ bool getEnableListeners()override;
  /*public*/ Base* getParent() const override;
  /*public*/ void setParent(/*@Nonnull*/ Base* parent)override;
  /*public*/ bool setParentForAllChildren(QList<QString> errors)override;
  /*public*/ void _connect(MaleSocket* socket) /*throw (SocketAlreadyConnectedException)*/override;
  /*public*/ void _disconnect()override;
  /*public*/ MaleSocket* getConnectedSocket()override;
  /*public*/ bool isConnected()override;
  /*public*/ /*final*/ bool validateName(QString name, bool ignoreDuplicateErrors)override;
  /*public*/ void setName(QString name, bool ignoreDuplicateErrors)override;
  /*public*/ QString getName()override;
  /*abstract*/ virtual /*public*/ void disposeMe()=0;
  /*public*/ /*final*/ void dispose()override;
  /*public*/ void registerListeners()override;
  /*public*/ void unregisterListeners() override;
  /*public*/ /*final*/ bool isActive()override;
  /*public*/ Category::TYPE getCategory() override;
  /*public*/ FemaleSocket* getChild(int index)/*throw (IllegalArgumentException, UnsupportedOperationException)*/ override;
  /*public*/ int getChildCount() override;
  /*public*/ QString getUserName() const override;
  /*public*/ void setUserName(QString s) /*throw (NamedBean::BadUserNameException)*/override;
  /*public*/ QString getComment()override;
  /*public*/ void setComment(QString s)override;
  /*public*/ QString getSystemName() const override;
  /*public*/ /*final*/ ConditionalNG* getConditionalNG()override;
  /*public*/ /*final*/ LogixNG*getLogixNG()override;
  /*public*/ /*final*/ Base* getRoot()override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int*  lineNumber)override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int*  lineNumber)override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          QString currentIndent,
          /*MutableInt*/int*  lineNumber)override;
  /*public*/ void getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override;
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override;
  /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener)override;
  /*public*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener)override;
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners()const override;
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName) override;
  /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener)override;
  /*public*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener)override;
  /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener, QString name, QString listenerRef)override;
  /*public*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener, QString name, QString listenerRef)override;
  /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName)override;
  /*public*/ void vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException) override;
  /*public*/ QString getListenerRef(PropertyChangeListener* l) override;
  /*public*/ QList<QString> getListenerRefs()override;
  /*public*/ int getNumPropertyChangeListeners()override;
  /*public*/ QList<PropertyChangeListener*> getPropertyChangeListenersByReference(QString name)override;
  /*public*/ void forEntireTree(RunnableWithBase* r)override;
  /*public*/ Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throw (JmriException)*/ override;
  /*public*/ Base* deepCopyChildren(Base* original, QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throw (JmriException)*/  override;
  /*public*/ void getListenerRefsIncludingChildren(QList<QString> list) override;

  QObject* self() override {return (QObject*)this;}
 signals:

 private:
  static Logger* log;
  /*private*/ Base* _parent = nullptr;
  /*private*/ MaleSocket* _socket = nullptr;
  /*private*/ QString _name = nullptr;
  /*private*/ bool _listenersAreRegistered = false;
  bool _enableListeners = true;
  /*private*/ /*final*/ SwingPropertyChangeSupport* pcs = new SwingPropertyChangeSupport(this, nullptr);

 protected:
  /*protected*/ /*final*/ FemaleSocketListener* _listener;
  /*protected*/ void registerListenersForThisClass();
  /*protected*/ void unregisterListenersForThisClass() ;
  /*protected*/ void printTreeRow(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString currentIndent,
          /*MutableInt*/int  lineNumber);

};

#endif // ABSTRACTFEMALESOCKET_H
