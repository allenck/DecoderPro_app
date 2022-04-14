#ifndef ANDSWING_H
#define ANDSWING_H

#include "abstractdigitalexpressionswing.h"

class AndSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  explicit AndSwing(QObject *parent = nullptr) : AbstractDigitalExpressionSwing(parent) {setObjectName("AndSwing");}
  ~AndSwing() {}
  AndSwing(const AndSwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull */QString systemName, /*@CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}
 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(AndSwing)
#endif // ANDSWING_H
