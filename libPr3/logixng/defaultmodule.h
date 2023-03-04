#ifndef DEFAULTMODULE_H
#define DEFAULTMODULE_H

#include "abstractbase.h"
#include "femalesocketmanager.h"
#include "module.h"
#include "femalesocketlistener.h"
#include "symboltable.h"

class VariableData;
class Parameter;
class DefaultModule : public AbstractBase, public Module, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(Module FemaleSocketListener)
 public:
  explicit DefaultModule(QString sys, QString user, FemaleSocketManager::SocketType* socketType,QObject *parent = nullptr);
  /*public*/  void setCurrentConditionalNG(ConditionalNG* conditionalNG)override;
  /*public*/  ConditionalNG* getConditionalNG()override;
  /*public*/  Base* getParent() const override;
  /*public*/  void setParent(Base* parent) override;
  /*public*/  QString getBeanType()override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  Category getCategory()override;
  /*public*/  void printTree(
          PrintTreeSettings* settings,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int* lineNumber) override;
  /*public*/  void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          /*MutableInt*/int* lineNumber)override;
  /*public*/  void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          QString currentIndent,
          /*MutableInt*/int* lineNumber)override;
  /*public*/  FemaleSocketManager::SocketType* getRootSocketType()override;
  /*public*/  FemaleSocket* getRootSocket()override;
  /*public*/  void addParameter(QString name, bool isInput, bool isOutput)override;
  /*public*/  void addParameter(Module::Parameter* parameter)override;
  /*public*/  void addLocalVariable(
          QString name,
          SymbolTable::InitialValueType::TYPES initialValueType,
          QString initialValueData)override;
  /*public*/  QSet<Parameter*> getParameters()override;
  /*public*/  QSet<SymbolTable::VariableData *> getLocalVariables()override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  void setSocketSystemName(QString systemName);
  /*public*/  QString getSocketSystemName();
  /*final*/ /*public*/  void setup() override;
  /*final*/ /*public*/  void disposeMe()override;
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames)override;
  /*public*/  QList<NamedBeanUsageReport*>* getUsageReport(NamedBean* bean)override;
  /*public*/  void getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

  QObject* self() override{return (QObject*)this;}
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

 private:
  /*private*/ /*final*/ FemaleSocketManager::SocketType* _rootSocketType;
  /*private*/ /*final*/ FemaleSocket* _femaleRootSocket;
  /*private*/ QString _socketSystemName = "";
  /*private*/ /*final*/ QSet<Parameter*> _parameters = QSet<Parameter*>();
  /*private*/ /*final*/ QSet<SymbolTable::VariableData*> _localVariables = QSet<SymbolTable::VariableData*>();
  /*private*/ /*final*/ QMap<QThread*, ConditionalNG*> _currentConditionalNG = QMap<QThread*, ConditionalNG*>();
  static Logger* log;

 protected:
  /*protected*/ void registerListenersForThisClass()override;
  /*protected*/ void unregisterListenersForThisClass()override;

};

#endif // DEFAULTMODULE_H
