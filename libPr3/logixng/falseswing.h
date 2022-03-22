#ifndef FALSESWING_H
#define FALSESWING_H

#include "abstractdigitalactionswing.h"

class FalseSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT

 public:
  Q_INVOKABLE FalseSwing(QObject* parent= nullptr) : AbstractDigitalActionSwing(parent) {setObjectName("FalseSwing");}
  ~FalseSwing() {}
  FalseSwing(const FalseSwing&) : AbstractDigitalActionSwing(){}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;


  QObject* sself() override {return (QObject*)this;}

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(FalseSwing)
#endif // FALSESWING_H
