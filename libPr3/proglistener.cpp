#include "proglistener.h"
#include <QMetaEnum>

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

QString ProgListener::statusString(ProgListener::status type)
{
 const QMetaObject &mo = ProgListener::staticMetaObject;
 int index = mo.indexOfEnumerator("status");
 QMetaEnum metaEnum = mo.enumerator(index);
 return metaEnum.valueToKey(type);
}
