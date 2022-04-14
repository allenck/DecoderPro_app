#ifndef DIGITALMANYSWING_H
#define DIGITALMANYSWING_H

#include "abstractdigitalactionswing.h"

class DigitalManySwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DigitalManySwing(QObject *parent = nullptr) : AbstractDigitalActionSwing(parent){setObjectName("DigitalManySwing");}
  ~DigitalManySwing() {}
  DigitalManySwing(const DigitalManySwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}
 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(DigitalManySwing)
#endif // DIGITALMANYSWING_H
