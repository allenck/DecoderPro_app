#ifndef ANALOGEXPRESSIONMEMORYSWING_H
#define ANALOGEXPRESSIONMEMORYSWING_H

#include "beanselectpanel.h"
#include "abstractanalogexpressionswing.h"

class AnalogExpressionMemorySwing : public AbstractAnalogExpressionSwing
{
  Q_OBJECT
 public:
  AnalogExpressionMemorySwing(QObject* parent = nullptr) : AbstractAnalogExpressionSwing(parent) {};
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object);
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

 private:
  /*private*/ BeanSelectPanel/*<Memory>*/* memoryBeanPanel;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};

#endif // ANALOGEXPRESSIONMEMORYSWING_H
