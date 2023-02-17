#ifndef MALEDIGITALEXPRESSIONSOCKET_H
#define MALEDIGITALEXPRESSIONSOCKET_H
#include "malesocket.h"
#include "digitalexpressionbean.h"

/**
 * A LogixNG male DigitalExpressionBean socket.
 */
/*public*/ /*interface*/class MaleDigitalExpressionSocket
        :  public DigitalExpressionBean, public virtual MaleSocket {
  //Q_OBJECT
 public:
  Q_INTERFACES(DigitalExpressionBean MaleSocket )
    /**
     * {@inheritDoc}
     * <P>
     * This method must ensure that the value is not a Double.NaN, negative
     * infinity or positive infinity. If that is the case, it must throw an
     * IllegalArgumentException before checking if an error has occured.
     */
    //@Override
    /*public*/ virtual bool evaluate() /*throws JmriException*/=0;

    /**
     * Get the last result of the evaluation.
     * @return the last result
     */
    /*public*/ virtual bool getLastResult()=0 ;

};
Q_DECLARE_INTERFACE(MaleDigitalExpressionSocket, "MaleDigitalExpressionSocket")
#endif // MALEDIGITALEXPRESSIONSOCKET_H
