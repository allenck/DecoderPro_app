#ifndef USBDCS52SYSTEMCONNECTIONMEMO_H
#define USBDCS52SYSTEMCONNECTIONMEMO_H
#include "pr3systemconnectionmemo.h"

class UsbDcs52SystemConnectionMemo : public PR3SystemConnectionMemo
{
 Q_OBJECT
public:
 UsbDcs52SystemConnectionMemo(QObject *parent = nullptr);
};

#endif // USBDCS52SYSTEMCONNECTIONMEMO_H
