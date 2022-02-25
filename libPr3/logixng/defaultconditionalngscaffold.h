#ifndef DEFAULTCONDITIONALNGSCAFFOLD_H
#define DEFAULTCONDITIONALNGSCAFFOLD_H
#include "defaultconditionalng.h"

class DefaultConditionalNGScaffold : public DefaultConditionalNG
{
  Q_OBJECT
 public:
  /*public*/ DefaultConditionalNGScaffold(QString sys, QString user, QObject* parent = nullptr);
  /*public*/ DefaultConditionalNGScaffold(QString sys, QString user, int threadID, QObject* parent = nullptr);

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

  QString getUserName() const override {return AbstractNamedBean::getUserName();}
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) override
  {
   AbstractBase::getUsageDetail(level, bean, report, cdl);
  }

};

#endif // DEFAULTCONDITIONALNGSCAFFOLD_H
