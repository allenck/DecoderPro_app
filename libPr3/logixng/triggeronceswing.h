#ifndef TRIGGERONCESWING_H
#define TRIGGERONCESWING_H

#include "abstractdigitalexpressionswing.h"

class TriggerOnceSwing : public AbstractDigitalExpressionSwing
{
 public:
  explicit TriggerOnceSwing(QObject *parent = nullptr);
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};

#endif // TRIGGERONCESWING_H
