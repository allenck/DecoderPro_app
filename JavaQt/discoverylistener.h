#ifndef DISCOVERYLISTENER_H
#define DISCOVERYLISTENER_H
#include <QVector>
class RemoteDevice;
class DeviceClass;
class ServiceRecord;
/*public*/ /*interface*/class  DiscoveryListener {
 enum DISCOVER
 {
   INQUIRY_COMPLETED = 0,
   INQUIRY_TERMINATED = 5,
   INQUIRY_ERROR = 7,
   SERVICE_SEARCH_COMPLETED = 1,
   SERVICE_SEARCH_TERMINATED = 2,
   SERVICE_SEARCH_ERROR = 3,
   SERVICE_SEARCH_NO_RECORDS = 4,
   SERVICE_SEARCH_DEVICE_NOT_REACHABLE = 6
};
   virtual /*public*/ void deviceDiscovered(RemoteDevice* rd, DeviceClass* dc){}

   virtual /*public*/ void servicesDiscovered(int i, QVector<ServiceRecord*> srs){}

   virtual /*public*/ void serviceSearchCompleted(int i, int i1)  {}

   virtual /*public*/ void inquiryCompleted(int i) {}
 friend class LocoNetBluetoothAdapter;
};

#endif // DISCOVERYLISTENER_H
