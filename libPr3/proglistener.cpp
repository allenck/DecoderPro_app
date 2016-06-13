#include "proglistener.h"

ProgListener::ProgListener(QObject *parent) :
    QObject(parent)
{
}
/** Receive a callback at the end of a programming operation.
 *
 * @param value  Value from a read operation, or value written on a write
 * @param status Denotes the completion code. Note that this is a
 *                    bitwise combination of the various status coded defined
 *                    in this interface.
 */
void ProgListener::programmingOpReply(int value, int status) {}

