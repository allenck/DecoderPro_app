#ifndef TRUESWING_H
#define TRUESWING_H

#include "abstractdigitalexpressionswing.h"

class TrueSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit TrueSwing(QObject *parent = nullptr) : AbstractDigitalExpressionSwing(parent) {setObjectName("TrueSwing");}
  ~TrueSwing() {}
  TrueSwing(const TrueSwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return(QObject*)this;}
 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(TrueSwing)
#endif // TRUESWING_H
