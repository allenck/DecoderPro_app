#ifndef INTERNALMETERMANAGER_H
#define INTERNALMETERMANAGER_H
#include "abstractmetermanager.h"

class InternalSystemConnectionMemo;
class InternalMeterManager : public AbstractMeterManager
{
  Q_OBJECT
 public:
  InternalMeterManager(InternalSystemConnectionMemo* memo, QObject* parent = nullptr);
  /*public*/ SystemConnectionMemo* getMemo() override;
  /*public*/ QString getNamedBeanClass() const override {return "jmri.jmrix.internal.InternalMeterManager";}

  QObject* mself() override{return (QObject*)this;}

  /*public*/ NamedBean* getBySystemName(QString name) override{return AbstractManager::getBySystemName(name);}
  /*public*/ NamedBean* getByUserName(QString name) override{return AbstractManager::getByUserName(name);}

  QObject* vself() override { return (QObject*)this;}
  QObject* pself() override{return (QObject*)this;}

};

#endif // INTERNALMETERMANAGER_H
