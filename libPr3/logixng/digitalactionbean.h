#ifndef DIGITALACTIONBEAN_H
#define DIGITALACTIONBEAN_H
#include "namedbean.h"
#include "digitalaction.h"

/**
 * A LogixNG digital action bean.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class  DigitalActionBean : public DigitalAction {
 //Q_OBJECT
  Q_INTERFACES(DigitalAction)
 public:
  //DigitalActionBean(QString name, QObject* parent = nullptr) : NamedBean(name, parent){}
};
Q_DECLARE_INTERFACE(DigitalActionBean, "DigitalActionBean")
#endif // DIGITALACTIONBEAN_H
