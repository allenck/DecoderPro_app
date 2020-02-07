#ifndef USBDCS240SYSTEMCONNECTIONMEMO_H
#define USBDCS240SYSTEMCONNECTIONMEMO_H
#include "pr3systemconnectionmemo.h"

class UsbDcs240SystemConnectionMemo : public PR3SystemConnectionMemo
{
 Q_OBJECT
public:
 UsbDcs240SystemConnectionMemo(QObject* parent = nullptr);
};

#endif // USBDCS240SYSTEMCONNECTIONMEMO_H
