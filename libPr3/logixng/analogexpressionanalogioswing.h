#ifndef ANALOGEXPRESSIONANALOGIOSWING_H
#define ANALOGEXPRESSIONANALOGIOSWING_H

#include "abstractanalogexpressionswing.h"
#include "beanselectpanel.h"
#include "analogio.h"

class AnalogExpressionAnalogIOSwing : public AbstractAnalogExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit AnalogExpressionAnalogIOSwing(QObject *parent = nullptr)
   : AbstractAnalogExpressionSwing(parent) {setObjectName("AnalogExpressionAnalogIOSwing");}
  ~AnalogExpressionAnalogIOSwing(){}
  AnalogExpressionAnalogIOSwing(const AnalogExpressionAnalogIOSwing&) : AbstractAnalogExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}

 private:
  /*private*/ BeanSelectPanel/*<AnalogIO*>*/* analogIOBeanPanel;


 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(AnalogExpressionAnalogIOSwing)
#endif // ANALOGEXPRESSIONANALOGIOSWING_H
