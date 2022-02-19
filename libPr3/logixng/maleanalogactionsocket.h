#ifndef MALEANALOGACTIONSOCKET_H
#define MALEANALOGACTIONSOCKET_H
#include "malesocket.h"
#include "analogactionbean.h"
/**
 * A LogixNG male AnalogActionBean socket.
 */
/*public*/ /*interface*/class MaleAnalogActionSocket : public AnalogActionBean, public virtual MaleSocket  {
Q_INTERFACES(AnalogActionBean MaleSocket )
 public:
 // MaleAnalogActionSocket(QString name, QObject* parent = nullptr) : QObject( parent) {}
    /**
     * {@inheritDoc}
     * <P>
     * This method must ensure that the value is not a Double.NaN, negative
     * infinity or positive infinity. If that is the case, it must throw an
     * IllegalArgumentException before checking if an error has occured.
     */
    //@Override
    /*public*/  void setValue(double value) override/*throws JmriException*/=0;

};
Q_DECLARE_INTERFACE(MaleAnalogActionSocket, "MaleAnalogActionSocket")
#endif // MALEANALOGACTIONSOCKET_H
