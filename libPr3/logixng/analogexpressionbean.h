#ifndef ANALOGEXPRESSIONBEAN_H
#define ANALOGEXPRESSIONBEAN_H
#include "namedbean.h"
#include "analogexpression.h"
/**
 * AnalogExpressionBean is a AnalogExpression that also implements NamedBean.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class AnalogExpressionBean : public virtual NamedBean, public AnalogExpression {
  //Q_OBJECT
  Q_INTERFACES(NamedBean AnalogExpression)
 public:
  //AnalogExpressionBean(QString name, QObject* parent = nullptr) : NamedBean(name, parent){}
};
Q_DECLARE_INTERFACE(AnalogExpressionBean, "AnalogExpressionBean")
#endif // ANALOGEXPRESSIONBEAN_H