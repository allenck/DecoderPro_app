#ifndef MALEDIGITALBOOLEANACTIONSOCKET_H
#define MALEDIGITALBOOLEANACTIONSOCKET_H
#include "malesocket.h"
#include "digitalbooleanactionbean.h"
/**
 * A LogixNG male DigitalBooleanActionBean socket.
 */
/*public*/ /*interface*/ class MaleDigitalBooleanActionSocket
        : public virtual MaleSocket, public DigitalBooleanActionBean {

};
Q_DECLARE_INTERFACE(MaleDigitalBooleanActionSocket, "MaleDigitalBooleanActionSocket")
#endif // MALEDIGITALBOOLEANACTIONSOCKET_H
