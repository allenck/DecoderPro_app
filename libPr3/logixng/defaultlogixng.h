#ifndef DEFAULTLOGIXNG_H
#define DEFAULTLOGIXNG_H

#include <abstractnamedbean.h>
#include "logixng.h"
#include "instancemanager.h"
#include "logixng_manager.h"
#include "conditionalng.h"

class Category;
class ConditionalNG_Entry;
class DefaultLogixNG : public AbstractNamedBean, public LogixNG
{
 Q_OBJECT
 Q_INTERFACES(LogixNG)
 public:
  explicit DefaultLogixNG(QString sys, QString user, QObject *parent = nullptr);
  ~DefaultLogixNG() {}
  DefaultLogixNG(const DefaultLogixNG&) : AbstractNamedBean() {}
  /*public*/ Base* getParent() override;
  /*public*/ void setParent(Base* parent) override;
  /*public*/ QString getBeanType() override;
  /*public*/ void setState(int s) throw (JmriException) override;
  /*public*/ int getState() override;
  /*public*/ QString getShortDescription(QLocale locale)override;
  /*public*/ QString getLongDescription(QLocale locale)override;
  /*public*/ FemaleSocket* getChild(int index) throw (IllegalArgumentException, UnsupportedOperationException) override;
  /*public*/ int getChildCount()override;
  /*public*/ Category* getCategory() override;
  /*final*/ /*public*/ void setup() override;
  /*public*/ void setEnabled(bool enable) override;
  /*public*/ bool isEnabled()override;

  /*public*/ QList<NamedBeanUsageReport*> getUsageReport(NamedBean* bean) override;
  /*public*/ void getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl);
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl);
  /*public*/ void getListenerRefsIncludingChildren(QList<QString> list)override;

 private:
  /*private*/ /*final*/ LogixNG_Manager* _manager = (LogixNG_Manager*)InstanceManager::getDefault("LogixNG_Manager");
  /*private*/ bool _enabled = false;
  /*private*/ /*final*/ QList<ConditionalNG_Entry*> _conditionalNG_Entries =  QList<ConditionalNG_Entry*>();
  static Logger* log;
};

/*private*/ /*static*/ class ConditionalNG_Entry {
    /*private*/ QString _systemName;
    /*private*/ ConditionalNG* _conditionalNG;

    /*private*/ ConditionalNG_Entry(ConditionalNG* conditionalNG, QString systemName) {
        _systemName = systemName;
        _conditionalNG = conditionalNG;
    }

    /*private*/ ConditionalNG_Entry(ConditionalNG* conditionalNG) {
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
        sb.append(_conditionalNG == nullptr ? "----" : _conditionalNG->getDisplayName());
        return sb/*.toString()*/;
    }
  friend class DefaultLogixNG;
};

Q_DECLARE_METATYPE(DefaultLogixNG)
#endif // DEFAULTLOGIXNG_H