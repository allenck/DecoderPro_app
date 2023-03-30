#ifndef MALEDIGITALACTIONSOCKET_H
#define MALEDIGITALACTIONSOCKET_H
#include "malesocket.h"
#include "digitalactionbean.h"

/**
 * A LogixNG male DigitalActionBean socket.
 */
/*public*/ /*interface*/class MaleDigitalActionSocket : public virtual MaleSocket, public DigitalActionBean {

  Q_INTERFACES(MaleSocket DigitalActionBean)
 public:
    /**
     * {@inheritDoc}
     * <P>
     * This method must ensure that the value is not a Double.NaN, negative
     * infinity or positive infinity. If that is the case, it must throw an
     * IllegalArgumentException before checking if an error has occured.
     */
    //@Override
    /*public*/ virtual void execute() /*throws JmriException*/=0;
    /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.MaleDigitalActionSocket";}

};
Q_DECLARE_INTERFACE(MaleDigitalActionSocket, "MaleDigitalActionSocket")

#endif // MALEDIGITALACTIONSOCKET_H
