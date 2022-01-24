#include "proglistener.h"
#include <QMetaEnum>

//ProgListener::ProgListener(QObject *parent) :
//    QObject(parent)
//{
//}
/** Receive a callback at the end of a programming operation.
 *
 * @param value  Value from a read operation, or value written on a write
 * @param status Denotes the completion code. Note that this is a
 *                    bitwise combination of the various status coded defined
 *                    in this interface.
 */
//void ProgListener::programmingOpReply(int value, int status) {}

QString ProgListener::statusString(ProgListener::status type)
{
// const QMetaObject &mo = ProgListener::staticMetaObject;
// int index = mo.indexOfEnumerator("status");
// QMetaEnum metaEnum = mo.enumerator(index);
// return metaEnum.valueToKey(type);
 switch(type)
 {
  case 0:
   return "OK";
  case 1:
   return "UnknownError";
  case 2:
   return "NoLocoDetected";
 case 4:
  return "ProgrammerBusy";
 case 8:
  return "NotImplemented";
 case 0x10:
  return "UserAborted";
  case 0x20:
    return "NoAck";
 case 0x40:
  return "ConfirmFailed";
 case 0x80:
  return "FailedTimeout";
 case 0x100:
  return "ProgrammingShort";
 case 0x200:
  return "SequenceError";
 case 0x400:
  return "CommError";
 }
}
