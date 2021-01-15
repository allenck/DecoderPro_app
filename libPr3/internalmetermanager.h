#ifndef INTERNALMETERMANAGER_H
#define INTERNALMETERMANAGER_H
#include "abstractmetermanager.h"

class InternalSystemConnectionMemo;
class InternalMeterManager : public AbstractMeterManager
{
  Q_OBJECT
 public:
  InternalMeterManager(InternalSystemConnectionMemo* memo, QObject* parent = nullptr);
  /*public*/ SystemConnectionMemo* getMemo() const override;
  /*public*/ QString getNamedBeanClass() const override {return "jmri.jmrix.internal.InternalMeterManager";}
  //QObject* self() {return (QObject*)this;}
};

#endif // INTERNALMETERMANAGER_H
