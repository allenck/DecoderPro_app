#ifndef DIGITALBOOLEANACTIONBEAN_H
#define DIGITALBOOLEANACTIONBEAN_H
#include "namedbean.h"
#include "digitalbooleanaction.h"

/**
 * A LogixNG logix emulator action bean.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class DigitalBooleanActionBean : public NamedBean, DigitalBooleanAction {

  //Q_OBJECT
  Q_INTERFACES(NamedBean DigitalBooleanAction)
 public:
  //DigitalBooleanActionBean(QString name, QObject* parent) : NamedBean(name, parent) {}
};
Q_DECLARE_INTERFACE(DigitalBooleanActionBean, "DigitalBooleanActionBean")
#endif // DIGITALBOOLEANACTIONBEAN_H
