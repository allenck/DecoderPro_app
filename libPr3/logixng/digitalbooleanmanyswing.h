#ifndef DIGITALBOOLEANMANYSWING_H
#define DIGITALBOOLEANMANYSWING_H

#include "abstractbooleanactionswing.h"

class DigitalBooleanManySwing : public AbstractBooleanActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DigitalBooleanManySwing(QObject *parent = nullptr)
   : AbstractBooleanActionSwing(parent) {setObjectName("DigitalBooleanManySwing");}
  ~DigitalBooleanManySwing() {}
  DigitalBooleanManySwing(const DigitalBooleanManySwing&) : AbstractBooleanActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

 QObject* sself() override {return (QObject*)this;}
 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(DigitalBooleanManySwing)
#endif // DIGITALBOOLEANMANYSWING_H
