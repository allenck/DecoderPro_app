#ifndef ANALOGMANYSWING_H
#define ANALOGMANYSWING_H

#include "abstractanalogactionswing.h"

class AnalogManySwing : public AbstractAnalogActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit AnalogManySwing(QObject *parent = nullptr) : AbstractAnalogActionSwing(parent){setObjectName("AnalogManySwing");}
  ~AnalogManySwing() {}
  AnalogManySwing(const AnalogManySwing&) : AbstractAnalogActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(AnalogManySwing);

#endif // ANALOGMANYSWING_H
