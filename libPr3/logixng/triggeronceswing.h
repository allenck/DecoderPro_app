#ifndef TRIGGERONCESWING_H
#define TRIGGERONCESWING_H

#include "abstractdigitalexpressionswing.h"

class TriggerOnceSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit TriggerOnceSwing(QObject *parent = nullptr) {}
  ~TriggerOnceSwing() {}
  TriggerOnceSwing(const TriggerOnceSwing&){}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return this;}

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(TriggerOnceSwing);
#endif // TRIGGERONCESWING_H
