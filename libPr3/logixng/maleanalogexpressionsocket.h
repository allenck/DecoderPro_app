#ifndef MALEANALOGEXPRESSIONSOCKET_H
#define MALEANALOGEXPRESSIONSOCKET_H
#include "malesocket.h"
#include "Analogexpressionbean.h"
/**
 * A LogixNG male AnalogExpressionBean socket.
 */
/*public*/ /*interface*/class  MaleAnalogExpressionSocket :  public AnalogExpressionBean, public MaleSocket {
  Q_INTERFACES(AnalogExpressionBean MaleSocket)
 public:
    /**
     * {@inheritDoc}
     * <P>
     * This method must ensure that the result is not a Double.NaN, negative
     * infinity or positive infinity. If that is the case, it must throw an
     * IllegalArgumentException before checking if an error has occured.
     * <P>
     * If the socket is not enabled, the method returns the value 0.0f.
     * <P>
     * If an error occurs and are handled, the method returns the value 0.0f.
     * @throws JmriException when an exception occurs
     * @throws IllegalArgumentException if the result a Double.NaN, negative
     * infinity or positive infinity
     */
    //@Override
    /*public*/ virtual double evaluate() /*throws JmriException*/=0;

};
Q_DECLARE_INTERFACE(MaleAnalogExpressionSocket, "MaleAnalogExpressionSocket")
#endif // MALEANALOGEXPRESSIONSOCKET_H
