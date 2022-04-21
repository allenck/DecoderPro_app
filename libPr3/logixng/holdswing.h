#ifndef HOLDSWING_H
#define HOLDSWING_H

#include "abstractdigitalexpressionswing.h"

class HoldSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit HoldSwing(QObject *parent = nullptr) ;
  ~HoldSwing() {}
  HoldSwing(const HoldSwing&) : AbstractDigitalExpressionSwing(){}

  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull */QString systemName, /*@CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return (QObject*)this;}
 private:

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(HoldSwing)
#endif // HOLDSWING_H
