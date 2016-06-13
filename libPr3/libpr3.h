#ifndef LIBPR3_H
#define LIBPR3_H

#include "libPr3_global.h"
#include <usb.h>
#include "lnportcontroller.h"

#define PR3_ERROR -1
#define PACKET_LEN 8
#define STR_BUFF 256
#define PR3_MAX_DEV 1
#define CMD_RESET 0x00
#define USB_OUT_EP 0x03	/* USB output endpoint */
#define USB_INP_EP 0x83 /* USB Input endpoint */

#define USB_TIMEOUT 20
#define PR3MODE 0x00
#define MS100MODE 0x01

/* globals for datatransfer */
struct pr3_dev {
    unsigned char data_in[PACKET_LEN+1];
    unsigned char data_out[PACKET_LEN+1];
    struct usb_dev_handle *device_handle;
    int DevNo;
};

class LIBPR3SHARED_EXPORT LibPr3
{
public:
 LibPr3(QObject *parent = 0);
 int openDevice();
 bool status();

private:
 void init_usb(void);
 /* Keep these globals for now */
 unsigned char *data_in, *data_out;
 /* variables for usb */
 struct usb_bus *bus, *busses;
 struct usb_device *dev;
 struct pr3_dev pr3d[PR3_MAX_DEV];

 pr3_dev *CurrDev;
 int takeover_device(usb_dev_handle * udev, int interface);
 long SetCurrentDevice(long deviceno);
 int ReadPR3Data(void);
 int WritePR3Data(unsigned char cmd);


};

#endif // LIBPR3_H
