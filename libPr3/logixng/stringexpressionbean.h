#ifndef STRINGEXPRESSIONBEAN_H
#define STRINGEXPRESSIONBEAN_H

#include "namedbean.h"
#include "stringexpression.h"

/**
 * StringExpressionBean is a StringExpression that also implements NamedBean.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class StringExpressionBean : public NamedBean, public StringExpression {
    Q_INTERFACES(NamedBean StringExpression)
 public:
};
Q_DECLARE_INTERFACE(StringExpressionBean, "StringExpressionBean")
#endif // STRINGEXPRESSIONBEAN_H
