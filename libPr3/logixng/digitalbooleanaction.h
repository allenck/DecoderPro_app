#ifndef DIGITALBOOLEANACTION_H
#define DIGITALBOOLEANACTION_H
#include "base.h"

/**
 * A LogixNG logix emulator action.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class  DigitalBooleanAction :  public Base {

    /**
     * Execute this DigitalActionBean.
     *
     * @param hasChangedToTrue true if the expression has changed to true, false otherwise
     * @param hasChangedToFalse true if the expression has changed to false, false otherwise
     * @throws JmriException when an exception occurs
     */
    /*public*/ virtual void execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/=0;

};
Q_DECLARE_INTERFACE(DigitalBooleanAction, "DigitalBooleanAction")
#endif // DIGITALBOOLEANACTION_H
