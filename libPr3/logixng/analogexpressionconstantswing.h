#ifndef ANALOGEXPRESSIONCONSTANTSWING_H
#define ANALOGEXPRESSIONCONSTANTSWING_H

#include "abstractanalogexpressionswing.h"

class AnalogExpressionConstantSwing : public AbstractAnalogExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit AnalogExpressionConstantSwing(QObject *parent = nullptr): AbstractAnalogExpressionSwing(parent) {}
  ~AnalogExpressionConstantSwing() {setObjectName("AnalogExpressionConstantSwing");}
  AnalogExpressionConstantSwing(const AnalogExpressionConstantSwing&) : AbstractAnalogExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}

 private:
  /*private*/ JTextField* _constant;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(AnalogExpressionConstantSwing)
#endif // ANALOGEXPRESSIONCONSTANTSWING_H
