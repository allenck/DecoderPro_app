#ifndef STRINGACTIONBEAN_H
#define STRINGACTIONBEAN_H
#include "namedbean.h"
#include "stringaction.h"

/**
 * A LogixNG string action.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
/*public*/ class StringActionBean : public NamedBean, public StringAction {
  Q_INTERFACES(NamedBean StringAction)
 public:
};
Q_DECLARE_INTERFACE(StringActionBean, "StringActionBean")
#endif // STRINGACTIONBEAN_H
