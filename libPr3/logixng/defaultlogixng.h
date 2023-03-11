#ifndef DEFAULTLOGIXNG_H
#define DEFAULTLOGIXNG_H

#include <abstractnamedbean.h>
#include "logixng.h"
#include "instancemanager.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalng.h"

class Category;
class ConditionalNG_Entry;
class DefaultLogixNG : public AbstractNamedBean, public LogixNG
{
 Q_OBJECT
 Q_INTERFACES(LogixNG)
 public:
  explicit DefaultLogixNG(QString sys, QString user, QObject *parent = nullptr);
  ~DefaultLogixNG() {}
  DefaultLogixNG(const DefaultLogixNG&) : LogixNG() {}
  /*public*/ Base* getParent() const override;
  /*public*/ void setParent(Base* parent) override;
  /*public*/ QString getBeanType() override;
  /*public*/ void setState(int s) /*throw (JmriException)*/ override;
  /*public*/ int getState() override;
  /*public*/ QString getShortDescription(QLocale locale)override;
  /*public*/ QString getLongDescription(QLocale locale)override;
  /*public*/ FemaleSocket* getChild(int index) /*throw (IllegalArgumentException, UnsupportedOperationException)*/ override;
  /*public*/ int getChildCount()override;
  /*public*/ Category getCategory() override;
  /*final*/ /*public*/ void setup() override;
  /*public*/ void setEnabled(bool enable) override;
  /*public*/ bool isEnabled()override;

  /*public*/ QList<NamedBeanUsageReport*>* getUsageReport(NamedBean* bean) override;
  /*public*/ void getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;
  /*public*/ void getListenerRefsIncludingChildren(QList<QString> list)override;
  /*public*/ QString getSystemName() const override {return AbstractNamedBean::getSystemName();}
  /*public*/ QString getUserName() const override {return AbstractNamedBean::getUserName();}
  /*public*/ QString getConditionalNG_SystemName(int index)override;
  /*public*/ void setConditionalNG_SystemName(int index, QString systemName)override;
  /*public*/ int getNumConditionalNGs() override;
  /*public*/ void swapConditionalNG(int nextInOrder, int row)override;
  /*public*/ DefaultConditionalNG *getConditionalNG(int order)override;
  /*public*/ bool addConditionalNG(DefaultConditionalNG *conditionalNG) override;
  /*public*/ DefaultConditionalNG *getConditionalNG(QString systemName) override;
  /*public*/ DefaultConditionalNG* getConditionalNGByUserName(QString userName)override;
  /*public*/ void deleteConditionalNG(ConditionalNG* conditionalNG) override;
  /*public*/ bool isActive()override;
  /*public*/ void execute()override;
  /*public*/ void execute(bool allowRunDelayed)override;
  /*public*/ ConditionalNG* getConditionalNG()override;
  /*public*/ LogixNG* getLogixNG() override;
  /*public*/ /*final*/ Base* getRoot()override;
  /*public*/ bool setParentForAllChildren(QList<QString>* errors) override;
  /*public*/ void registerListeners()override;
  /*public*/ void unregisterListeners()override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          PrintWriter* writer,
          QString indent,
          int* lineNumber)override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          int* lineNumber)override;
  /*public*/ void printTree(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString indent,
          QString currentIndent,
          int* lineNumber)override;
  /*public*/ Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames)override;
  /*public*/ Base* deepCopyChildren(Base* original, QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;

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
  /*public*/ /*default*/ virtual bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/  /*default*/ virtual void doSocketOperation(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/ virtual QString toString() override {return getLongDescription(QLocale());}
  /*public*/ virtual void dispose() override {AbstractNamedBean::dispose();}
  void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

 private:
  /*private*/ /*final*/ LogixNG_Manager* _manager = (DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");
  /*private*/ bool _enabled = false;
  /*private*/ /*final*/ QList<ConditionalNG_Entry*> _conditionalNG_Entries =  QList<ConditionalNG_Entry*>();
  static Logger* log;

 protected:
  /*protected*/ void printTreeRow(
          PrintTreeSettings* settings,
          QLocale locale,
          PrintWriter* writer,
          QString currentIndent,
          int* lineNumber);

};

/*private*/ /*static*/ class ConditionalNG_Entry {
    /*private*/ QString _systemName;
    /*private*/ DefaultConditionalNG* _conditionalNG;

    /*private*/ ConditionalNG_Entry(DefaultConditionalNG* conditionalNG, QString systemName) {

        _systemName = systemName;
        _conditionalNG = conditionalNG;
    }

    /*private*/ ConditionalNG_Entry(DefaultConditionalNG* conditionalNG) {
        this->_conditionalNG = conditionalNG;
    }

    /*private*/ ConditionalNG_Entry(QString systemName) {
        this->_systemName = systemName;
    }
public:
    //@Override
    /*public*/ QString toString() {
        QString sb = QString("ConditionalNG_Entry: name =");
        sb.append(_systemName);
        sb.append(", cdl = ");
        sb.append(_conditionalNG == nullptr ? "----" : _conditionalNG->AbstractNamedBean::getDisplayName());
        return sb/*.toString()*/;
    }
  friend class DefaultLogixNG;
};

//Q_DECLARE_METATYPE(DefaultLogixNG)
#endif // DEFAULTLOGIXNG_H
