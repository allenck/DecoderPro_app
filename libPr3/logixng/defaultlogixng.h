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
  /*public*/ Base* getParent()const override;
  /*public*/ void setParent(Base* parent) override;
  /*public*/ QString getBeanType() override;
  /*public*/ void setState(int s) /*throw (JmriException)*/ override;
  /*public*/ int getState() override;
  /*public*/ QString getShortDescription(QLocale locale)override;
  /*public*/ QString getLongDescription(QLocale locale)override;
  /*public*/ FemaleSocket* getChild(int index) /*throw (IllegalArgumentException, UnsupportedOperationException)*/ override;
  /*public*/ int getChildCount()override;
  /*public*/ Category* getCategory() override;
  /*final*/ /*public*/ void setup() override;
  /*public*/ void setEnabled(bool enable) override;
  /*public*/ bool isEnabled()override;

  /*public*/ QList<NamedBeanUsageReport*> getUsageReport(NamedBean* bean) override;
  /*public*/ void getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl);
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl);
  /*public*/ void getListenerRefsIncludingChildren(QList<QString> list)override;
  /*public*/ QString getSystemName() const override {return AbstractNamedBean::getSystemName();}
  /*public*/ QString getUserName() const override {return AbstractNamedBean::getUserName();}
  /*public*/ QString getConditionalNG_SystemName(int index)override;
  /*public*/ void setConditionalNG_SystemName(int index, QString systemName)override;
  /*public*/ int getNumConditionalNGs() override;
  /*public*/ void swapConditionalNG(int nextInOrder, int row)override;
  /*public*/ ConditionalNG* getConditionalNG(int order)override;
  /*public*/ bool addConditionalNG(DefaultConditionalNG *conditionalNG) override;
  /*public*/ ConditionalNG* getConditionalNG(QString systemName) override;
  /*public*/ ConditionalNG* getConditionalNGByUserName(QString userName)override;
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
