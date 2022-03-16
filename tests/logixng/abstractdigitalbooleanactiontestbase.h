#ifndef ABSTRACTDIGITALBOOLEANACTIONTESTBASE_H
#define ABSTRACTDIGITALBOOLEANACTIONTESTBASE_H
#include "abstractbasetestbase.h"


class AbstractDigitalBooleanActionTestBase : public AbstractBaseTestBase
{
  Q_OBJECT
 public:
  AbstractDigitalBooleanActionTestBase(QObject* parent = nullptr) : AbstractBaseTestBase(parent) {}
  /*public*/  /*abstract*/virtual NamedBean* createNewBean(QString systemName)=0;

 public slots:
  /*public*/  void testBadSystemName();
  /*public*/  void testGetBeanType();

};

#endif // ABSTRACTDIGITALBOOLEANACTIONTESTBASE_H
