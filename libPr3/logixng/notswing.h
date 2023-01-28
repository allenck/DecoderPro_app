#ifndef NOTSWING_H
#define NOTSWING_H

#include "abstractdigitalexpressionswing.h"

class NotSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit NotSwing(QObject *parent = nullptr);
  ~NotSwing() {}
  NotSwing(const NotSwing&) : AbstractDigitalExpressionSwing() {}
 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}

};
Q_DECLARE_METATYPE(NotSwing)
#endif // NOTSWING_H
