#ifndef MALEDIGITALBOOLEANACTIONSOCKET_H
#define MALEDIGITALBOOLEANACTIONSOCKET_H
#include "malesocket.h"
#include "digitalbooleanactionbean.h"
/**
 * A LogixNG male DigitalBooleanActionBean socket.
 */
/*public*/ /*interface*/ class MaleDigitalBooleanActionSocket
        : public MaleSocket, public DigitalBooleanActionBean {

};
Q_DECLARE_INTERFACE(DigitalBooleanActionBean, "DigitalBooleanActionBean")
#endif // MALEDIGITALBOOLEANACTIONSOCKET_H
