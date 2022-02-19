#ifndef MALESTRINGACTIONSOCKET_H
#define MALESTRINGACTIONSOCKET_H
#include "malesocket.h"
#include "stringactionbean.h"
/**
 * A LogixNG male StringActionBean socket.
 */
/*public*/ class MaleStringActionSocket
        : public virtual MaleSocket, public StringActionBean {
public:
  Q_INTERFACES(MaleSocket StringActionBean)
    /**
     * {@inheritDoc}
     * <P>
     * This method must ensure that the value is not a Double.NaN, negative
     * infinity or positive infinity. If that is the case, it must throw an
     * IllegalArgumentException before checking if an error has occured.
     */
    //@Override
    /*public*/ virtual void setValue(/*@Nonnull*/ QString value) /*throws JmriException*/=0;

};
Q_DECLARE_INTERFACE(MaleStringActionSocket, "MaleStringActionSocket")
#endif // MALESTRINGACTIONSOCKET_H
