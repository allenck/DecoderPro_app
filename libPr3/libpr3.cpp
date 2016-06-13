#include "libpr3.h"
#include <QDebug>
#include "loconetmessage.h"
#include "lnpacketizer.h"

/* set debug to 0 to not print excess info */
int DEBUG = 1;
#define DIGITRAX_VENDOR_ID 1240
#define DIGITRAX_PRODUCT_ID 65406

/*
 * USB permissions
 *
 * create a file, 91_pr3.rules, in /etc/udev/rules.d with this data:
 *SUBSYSTEMS=="usb",  ATTRS{idVendor}=="4d8", ATTRS{idProduct}=="ff7e", MODE="0660", GROUP="adm", SYMLINK+="k80551", DRIVERS=="usb"
 */


LibPr3::LibPr3(QObject *parent)
{
 init_usb();
}

void LibPr3::init_usb(void)
{
 static int Done = 0;	/* Only need to do this once */
 if (!Done)
 {
  usb_init();
  usb_find_busses();
  usb_find_devices();
  busses = usb_get_busses();
  Done = 1;
 }
}
/* If device is owned by some kernel driver, try to disconnect it and claim the device*/
int LibPr3::takeover_device(usb_dev_handle * udev, int interface)
{
 char driver_name[STR_BUFF];

 memset(driver_name, 0, STR_BUFF);
 int ret = PR3_ERROR;

 Q_ASSERT(udev != NULL);
 ret = usb_get_driver_np(udev, interface, driver_name, sizeof(driver_name));
 if (ret == 0)
 {
  if (DEBUG)
   qDebug()<< QString("Got driver name: %1").arg( driver_name);
   if (0 > usb_detach_kernel_driver_np(udev, interface))
   {
    if (DEBUG)
     qDebug()<< QString("Disconnect OS driver: %1").arg( usb_strerror());
   }
   else if (DEBUG)
    qDebug()<< QString("Disconnected OS driver: %1").arg( usb_strerror());
  }
  else if (DEBUG)
   qDebug()<< QString( "Get driver name: - %1").arg( usb_strerror());

  /* claim interface */
  if (usb_claim_interface(udev, interface) < 0)
  {
   if (DEBUG)
    qDebug()<<QString("Claim interface error: %1").arg( usb_strerror());
   return PR3_ERROR;
  }
  else
   usb_set_altinterface(udev, interface);
  usb_set_configuration(udev, 1);

  if (DEBUG)
  {
   qDebug()<< QString("Found interface %1\n").arg( interface);
   qDebug()<< "Took over the device\n";
  }
  return 0;
}

int LibPr3::openDevice()
{
 /* start looping through the devices to find the correct one */
 for (bus = busses; bus; bus = bus->next)
 {
  for (dev = bus->devices; dev; dev = dev->next)
  {
//   qDebug()<< QString("id vendor %1 idProduct %2").arg(dev->descriptor.idVendor).arg(dev->descriptor.idProduct);
   if ((dev->descriptor.idVendor == DIGITRAX_VENDOR_ID) &&
                (dev->descriptor.idProduct == DIGITRAX_PRODUCT_ID))
   {
    CurrDev = &pr3d[0];
    CurrDev->device_handle = usb_open(dev);
    if (DEBUG)
    {
     qDebug()<< QString("PR3 Device Found @ Address %1 Vendor 0x0%2 Product ID 0x0%3").arg(dev->filename).arg( dev->descriptor.idVendor,0,16).arg(dev->descriptor.idProduct,0,16);
     qDebug()<< QString(" numConfigurations: %1").arg(dev->descriptor.bNumConfigurations);
    }
    if (takeover_device(CurrDev->device_handle, 1) < 0)
    {
     if (DEBUG)
      qDebug()<< "Can not take over the device from the OS driver\n";
     usb_close(CurrDev->device_handle);   /* close usb if we fail */
     return PR3_ERROR;  /* throw PR3_ERROR to show that OpenDevice failed */
    }
    else
    {
     CurrDev->DevNo = 0 + 1; /* Mark as open and valid */
     SetCurrentDevice(0);
//     memset(CurrDev->data_out,0,PACKET_LEN);	/* Write cmd 0, read data */

//     LnPacketizer* packets = new LnPacketizer();
//     packets->connectPort(this);

//     // set mode
//     LocoNetMessage* msg = new LocoNetMessage( 6 ) ;
//     msg->setOpCode( 0xD3 );
//     msg->setElement( 1, 0x10 );
//     msg->setElement( 2, 1 );  // set PR2
//     msg->setElement( 3, 0 );
//     msg->setElement( 4, 0 );
//     packets->sendLocoNetMessage(msg);
//     WritePR3Data(0xD3);
//     if (ReadPR3Data() == 0)
//      return 0;		/* This function should return board address */
//     else
//      return PR3_ERROR;
    }
   }
  }
 }
 if (DEBUG)
  qDebug()<< "Could not find Digitrax Pr3";
 return PR3_ERROR;
}
/* New function in version 2 of Velleman DLL, should return deviceno if OK */
long LibPr3::SetCurrentDevice(long deviceno)
{
 if (deviceno >= 0 && deviceno < PR3_MAX_DEV)
 {
  if (pr3d[deviceno].DevNo != 0)
  {
   CurrDev  = &pr3d[deviceno];
   data_in  = CurrDev->data_in;
   data_out = CurrDev->data_out;
   return deviceno;
  }
 }
 return PR3_ERROR;
}

/* Actual read of data from the device endpoint, retry 3 times if not responding ok */
int LibPr3::ReadPR3Data(void)
{
 int read_status = 0, i = 0;

 if (CurrDev->DevNo == 0) return PR3_ERROR;

 for(i=0; i < 3; i++)
 {
  read_status = usb_interrupt_read(CurrDev->device_handle, USB_INP_EP, (char *)CurrDev->data_in, PACKET_LEN, USB_TIMEOUT);
  if ((read_status == PACKET_LEN) && (CurrDev->data_in[1] == CurrDev->DevNo )) return 0;
  if (DEBUG)
   qDebug()<< "Read retry\n";
 }
 return PR3_ERROR;
}

/* Actual write of data to the device endpont, retry 3 times if not responding correctly */
int LibPr3::WritePR3Data(unsigned char cmd)
{
 int write_status = 0, i = 0;

 if (CurrDev->DevNo == 0) return PR3_ERROR;

 CurrDev->data_out[0] = cmd;
 for(i=0; i < 3; i++)
 {
  write_status = usb_interrupt_write(CurrDev->device_handle, USB_OUT_EP, (char *)CurrDev->data_out, PACKET_LEN, USB_TIMEOUT);
  if (write_status == PACKET_LEN) return 0;
  if (DEBUG)
   qDebug()<< "Write retry\n";
 }
 return PR3_ERROR;
}
bool LibPr3::status()
{
  return true;
}
