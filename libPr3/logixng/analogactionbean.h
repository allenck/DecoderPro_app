#ifndef ANALOGACTIONBEAN_H
#define ANALOGACTIONBEAN_H
#include "namedbean.h"
#include "analogaction.h"

/**
 * A LogixNG analog action bean.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class AnalogActionBean : NamedBean, AnalogAction {
 Q_OBJECT
  Q_INTERFACES(AnalogAction)
};

#endif // ANALOGACTIONBEAN_H
