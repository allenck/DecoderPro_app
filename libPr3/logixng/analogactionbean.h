#ifndef ANALOGACTIONBEAN_H
#define ANALOGACTIONBEAN_H
#include "namedbean.h"
#include "analogaction.h"

/**
 * A LogixNG analog action bean.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class AnalogActionBean : public NamedBean, public AnalogAction {
 //Q_OBJECT
  Q_INTERFACES(NamedBean AnalogAction)
 public:
  //AnalogActionBean(QString name, QObject* parent = nullptr) : NamedBean(name, parent) {}
};
Q_DECLARE_INTERFACE(AnalogActionBean, "AnalogActionBean")
#endif // ANALOGACTIONBEAN_H
