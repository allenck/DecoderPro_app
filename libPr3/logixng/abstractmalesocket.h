#ifndef ABSTRACTMALESOCKET_H
#define ABSTRACTMALESOCKET_H

#include <QObject>
#include "malesocket.h"
#include "basemanager.h"
#include "symboltable.h"
#include "runtimeexception.h"
#include "jmriexception.h"
#include "abstractnamedbean.h"

class AbstractMaleSocket :  public /*QObject*/AbstractNamedBean, public virtual MaleSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleSocket)
 public:
  explicit AbstractMaleSocket(BaseManager/*<NamedBean*>*//*<? extends NamedBean>*/* manager, Base* object, QObject *parent = nullptr);
  /*public*/ /*final*/ Base* getObject() override;
  /*public*/ /*final*/ Base* getRoot() override;
  /*public*/ bool isLocked()override;
  /*public*/ void setLocked(bool locked)override;
  /*public*/ bool isSystem()override;
  /*public*/ void setSystem(bool system) override;
  /*public*/ /*final*/ Category* getCategory() override;
  /*public*/ /*final*/ FemaleSocket* getChild(int index) /*throw (IllegalArgumentException, UnsupportedOperationException)*/ override;
  /*public*/ /*final*/ int getChildCount()override;
  /*public*/ /*final*/ QString getShortDescription(QLocale locale) override;
  /*public*/ /*final*/ QString getLongDescription(QLocale locale) override;
  /*public*/ /*final*/ QString getUserName() const override;
  /*public*/ /*final*/ void setUserName(QString s) throw (NamedBean::BadUserNameException)override;
  /*public*/ /*final*/ QString getSystemName() const override;
  /*public*/ /*final*/ void addPropertyChangeListener(PropertyChangeListener* l, QString name, QString listenerRef)override;
  /*public*/ /*final*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* l, QString name, QString listenerRef) override;
  /*public*/ /*final*/ void addPropertyChangeListener(PropertyChangeListener* l)override;
  /*public*/ /*final*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* l) override;
  /*public*/ /*final*/ void removePropertyChangeListener(PropertyChangeListener* l) override;
  /*public*/ /*final*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* l)override;
  /*public*/ /*final*/ void updateListenerRef(PropertyChangeListener* l, QString newName)override;
  /*public*/ /*final*/ void vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException)override;
  /*public*/ /*final*/ QString getListenerRef(PropertyChangeListener* l)override;
  /*public*/ /*final*/ QList<QString> getListenerRefs()override;
  /*public*/ /*final*/ int getNumPropertyChangeListeners()override;
  /*public*/ /*final*/ /*synchronized*/ QVector<PropertyChangeListener*> getPropertyChangeListeners() const override;
  /*public*/ /*final*/ /*synchronized*/ QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName)override;
  /*public*/ /*final*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(QString name)override;
  /*public*/ QString getComment()override;
  /*public*/ void setComment(QString comment)override;
  /*public*/ bool getListen()override;
  /*public*/ void setListen(bool listen)override;
  /*public*/ bool getCatchAbortExecution()override;
  /*public*/ void setCatchAbortExecution(bool catchAbortExecution)override;
  /*public*/ void addLocalVariable(QString name,
          InitialValueType::TYPES initialValueType,
          QString initialValueData)override;
  /*public*/ void addLocalVariable(VariableData* variableData)override;
  /*public*/ void clearLocalVariables()override;
  /*public*/ QSet<VariableData*> getLocalVariables() override;
  /*public*/ Base* getParent() const override;
  /*public*/ void setParent(Base* parent)override;
  /*public*/ /*final*/ ConditionalNG* getConditionalNG()override;
  /*public*/ /*final*/ LogixNG* getLogixNG()override;
  /*public*/ /*final*/ bool setParentForAllChildren(QList<QString> errors)override;
  /*public*/ /*final*/ void registerListeners()override;
  /*public*/ /*final*/ void unregisterListeners()override;
  /*public*/ /*final*/ bool isActive()override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int* lineNumber)override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int* lineNumber) override;
  /*public*/ void printTree(PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          QString currentIndent,
          /*MutableInt*/int *lineNumber)override;
  /*public*/ void getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override;
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override;
  /*public*/ BaseManager/*<NamedBean*>*//*<? extends NamedBean>*/* getManager()override;
  /*public*/ /*final*/ Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames)
          /*throw (JmriException)*/override;
  /*public*/ /*final*/ Base* deepCopyChildren(Base* original, QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throw (JmriException)*/;
  /*public*/ /*final*/ void dispose()override;
  /*public*/ ErrorHandlingType::TYPES getErrorHandlingType()override;
  /*public*/ void setErrorHandlingType(ErrorHandlingType::TYPES errorHandlingType)override;
  /*public*/ void handleError(Base* item, QString message, JmriException *e, Logger* log) /*throw (JmriException)*/;
  /*public*/ void handleError(
          Base* item,
          QString message,
          QList<QString> messageList,
          JmriException* e,
          Logger* log)
          /*throw (JmriException)*/;
  /*public*/ void handleError(Base* item, QString message, RuntimeException* e, Logger* log) /*throw (JmriException)*/;
  /*public*/ void getListenerRefsIncludingChildren(QList<QString> list)override;
  /*public*/ QString toString()override;

  QObject* bself() override {return (QObject*)this;}

 signals:

 private:
  static Logger* log;
  /*private*/ /*final*/ Base* _object=nullptr;
  /*private*/ bool _locked = false;
  /*private*/ bool _system = false;
  /*private*/ /*final*/ BaseManager/*<NamedBean*><? extends NamedBean>*/* _manager;
  /*private*/ Base* _parent = nullptr;
  /*private*/ ErrorHandlingType::TYPES _errorHandlingType = ErrorHandlingType::Default;
  /*private*/ bool _catchAbortExecution;
  /*private*/ bool _listen = true;     // By default, actions and expressions listen

 protected:
  /*protected*/ /*final*/ QSet<VariableData*> _localVariables = QSet<VariableData*>();
  /*abstract*/virtual /*protected*/ void registerListenersForThisClass()=0;
  /*protected*/ void printTreeRow(PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString currentIndent,
          /*MutableInt*/int *lineNumber);
  /*protected*/ void printLocalVariable(PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString currentIndent,
          /*MutableInt*/int *lineNumber,
          VariableData* localVariable);
  /*abstract*/ /*protected*/virtual void unregisterListenersForThisClass()=0;
  /*abstract*/ /*protected*/ virtual void disposeMe()=0;
};



#endif // ABSTRACTMALESOCKET_H
