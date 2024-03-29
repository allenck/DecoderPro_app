#ifndef INTERNALANALOGIOMANAGER_H
#define INTERNALANALOGIOMANAGER_H
#include "abstractanalogiomanager.h"

class InternalSystemConnectionMemo;
class InternalAnalogIOManager : public AbstractAnalogIOManager
{
  Q_OBJECT
 public:
  InternalAnalogIOManager(InternalSystemConnectionMemo* memo, QObject* parent = nullptr);

  /*public*/ SystemConnectionMemo* getMemo()override;

  QObject* pself() override {return (QObject*)this;}
  QObject* vself() override {return (QObject*)this;}
  QObject* mself() override {return (QObject*)this;}
  QObject* self() override {return this;}

  void addPropertyChangeListener(PropertyChangeListener* l) override {PropertyChangeSupport::addPropertyChangeListener(l);}

};

#endif // INTERNALANALOGIOMANAGER_H
