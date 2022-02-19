#ifndef DIGITALACTION_H
#define DIGITALACTION_H
#include "base.h"
/**
 * A LogixNG digitalaction.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class  DigitalAction : public virtual Base   {

    Q_INTERFACES(Base)
 public:
    /**
     * Execute this DigitalActionBean.
     *
     * @throws JmriException when an exception occurs
     */
    /*public*/ virtual void execute() /*throws JmriException*/=0;

};
Q_DECLARE_INTERFACE(DigitalAction, "DigitalAction")
#endif // DIGITALACTION_H
