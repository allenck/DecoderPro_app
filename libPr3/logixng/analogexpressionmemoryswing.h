#ifndef ANALOGEXPRESSIONMEMORYSWING_H
#define ANALOGEXPRESSIONMEMORYSWING_H

#include "beanselectpanel.h"
#include "abstractanalogexpressionswing.h"

class AnalogExpressionMemorySwing : public AbstractAnalogExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE AnalogExpressionMemorySwing(QObject* parent = nullptr)
   : AbstractAnalogExpressionSwing(parent) {setObjectName("AnalogExpressionMemorySwing");}
  ~AnalogExpressionMemorySwing() {}
  AnalogExpressionMemorySwing(const AnalogExpressionMemorySwing&) : AbstractAnalogExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}
 private:
  /*private*/ BeanSelectPanel/*<Memory>*/* memoryBeanPanel;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(AnalogExpressionMemorySwing)
#endif // ANALOGEXPRESSIONMEMORYSWING_H
