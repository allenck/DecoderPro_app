#include "lncvdevices.h"
#include "loggerfactory.h"
#include "lncvdevice.h"

/**
 * Based on Lnsvf2Devices by B. Milhaupt
 * @author Egbert Broerse 2020
 */
///*public*/ class LncvDevices {


/*public*/ LncvDevices::LncvDevices(QObject *parent) : QObject(parent){
    deviceList = QList<LncvDevice*>();
}

/*public*/ void LncvDevices::addDevice(LncvDevice* d) {
    if (!deviceExists(d)) {
        deviceList.append(d);
        log->debug(tr("added device with prod %1, addr %2").arg(
           d->getProductID()).arg(d->getDestAddr()));
    } else {
        log->debug(tr("device already in list: prod %1, addr %2").arg(
           d->getProductID()).arg(d->getDestAddr()));
    }
}

/*public*/ void LncvDevices::removeAllDevices() {
    deviceList.clear();
}

/**
 * Get index of device with matching Mfg, ProdID, Num and
 * Device Address.
 * Where a deviceToBeFound parameter is -1, that parameter is not compared.
 *
 * @param deviceToBeFound Device we try to find in known LNCV devices list
 * @return index of found device, else -1 if matching device not found
 */
/*public*/ int LncvDevices::isDeviceExistant(LncvDevice* deviceToBeFound) {
    log->debug(tr("Looking for a known LNCV device which matches characteristics: article %1, addr %2.").arg(
            deviceToBeFound->getProductID()).arg(
            deviceToBeFound->getDestAddr()));
    for (int i = 0; i < deviceList.size(); ++i) {
        LncvDevice* dev = deviceList.at(i);
        log->trace(tr("Comparing against known device: article %1, addr %2.").arg(
                dev->getProductID()).arg(
                deviceToBeFound->getDestAddr()));
        if ((deviceToBeFound->getProductID() == -1) ||
                (dev->getProductID() == deviceToBeFound->getProductID())) {
            if ((deviceToBeFound->getDestAddr() == -1) ||
                    (dev->getDestAddr() == deviceToBeFound->getDestAddr())) {
                log->debug(tr("Match Found! Searched device matched against known device: article %1, addr %2").arg(
                   dev->getProductID()).arg(dev->getDestAddr()));
                return i;
            }
        }
    }
    log->debug(tr("No matching known device was found!"));
    return -1;
}

/*public*/ bool LncvDevices::deviceExists(LncvDevice* d) {
    int i = isDeviceExistant(d);
    log->debug(tr("deviceExists found %1").arg(i));
    return (i >= 0);
}

/*public*/ LncvDevice* LncvDevices::getDevice(int index) {
    return deviceList.at(index);
}

/*public*/ QVector<LncvDevice*> LncvDevices::getDevices() {
//    LncvDevice[] d = {};
//    return deviceList.toArray(d);
 return deviceList.toVector();
}

/*public*/ int LncvDevices::size() {
    return deviceList.size();
}

/*public*/ void LncvDevices::addPropertyChangeListener(PropertyChangeListener* l){
 pcs->addPropertyChangeListener(l);
}

/*public*/ void LncvDevices::removePropertyChangeListener(PropertyChangeListener*l)
{
 pcs->removePropertyChangeListener(l);
}

/*private*/ /*final*/ /*static*/ Logger* LncvDevices::log = LoggerFactory::getLogger("LncvDevices");
