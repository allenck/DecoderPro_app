#ifndef DIGITALACTIONBEAN_H
#define DIGITALACTIONBEAN_H
#include "namedbean.h"
#include "digitalaction.h"
#include "abstractbase.h"
/**
 * A LogixNG digital action bean.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class  DigitalActionBean : public virtual NamedBean, public DigitalAction {
  //Q_OBJECT
  Q_INTERFACES(NamedBean DigitalAction)
 public:
  //DigitalActionBean(QString name, QObject* parent = nullptr) : AbstractBase(name, parent){}
};
Q_DECLARE_INTERFACE(DigitalActionBean, "DigitalActionBean")
#endif // DIGITALACTIONBEAN_H
