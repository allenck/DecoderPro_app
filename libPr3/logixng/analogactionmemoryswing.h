#ifndef ANALOGACTIONMEMORYSWING_H
#define ANALOGACTIONMEMORYSWING_H

#include "abstractanalogactionswing.h"

class BeanSelectPanel;
class AnalogActionMemorySwing : public AbstractAnalogActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit AnalogActionMemorySwing(QObject *parent = nullptr)
   : AbstractAnalogActionSwing(parent) { setObjectName("AnalogActionMemorySwing");}
  ~AnalogActionMemorySwing() {}
  AnalogActionMemorySwing(const AnalogActionMemorySwing&) : AbstractAnalogActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}

 private:
  /*private*/ BeanSelectPanel/*<Memory>*/* memoryBeanPanel;

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(AnalogActionMemorySwing)
#endif // ANALOGACTIONMEMORYSWING_H
