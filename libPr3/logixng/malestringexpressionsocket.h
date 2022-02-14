#ifndef MALESTRINGEXPRESSIONSOCKET_H
#define MALESTRINGEXPRESSIONSOCKET_H
#include "malesocket.h"
#include "stringexpressionbean.h"

/**
 * A LogixNG male StringExpressionBean socket.
 */
/*public*/ /*interface*/class MaleStringExpressionSocket
        : public MaleSocket, public StringExpressionBean {
Q_INTERFACES(MaleSocket StringExpressionBean)
 public:
    /**
     * {@inheritDoc}
     * <P>
     * This method must ensure that the value is not a Double.NaN, negative
     * infinity or positive infinity. If that is the case, it must throw an
     * IllegalArgumentException before checking if an error has occured.
     */
    //@Override
    /*public*/ virtual QString evaluate() /*throws JmriException*/=0;

};
Q_DECLARE_INTERFACE(MaleStringExpressionSocket, "MaleStringExpressionSocket")
#endif // MALESTRINGEXPRESSIONSOCKET_H
