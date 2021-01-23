#include "lncvdevice.h"


/**
 * A class to hold LocoNet LNCV device identity information.
 * See jmri.jmrix.loconet.lnsvf2.Sv2DiscoverPane
 *
 * @author B. Milhaupt 2020
 * @author Egbert Broerse 2020
 */
///*public*/ class LncvDevice {

/*public*/ LncvDevice::LncvDevice(int productID, int address, int lastCv, int lastVal, QString deviceName, QString rosterName, int swVersion) {
    this->artNum = productID;
    this->deviceAddress = address;
    cvNum = lastCv;
    cvValue = lastVal;
    this->deviceName = deviceName;
    this->rosterEntryName = rosterName;
    this->swVersion = swVersion;
}

/*public*/ int LncvDevice::getProductID() {return artNum;}
/*public*/ int LncvDevice::getDestAddr() {return deviceAddress;}
/*public*/ QString LncvDevice::getDeviceName() {return deviceName;}
/*public*/ QString LncvDevice::getRosterName() {return rosterEntryName;}
/*public*/ int LncvDevice::getSwVersion() {return swVersion;}

/**
 * Set the table view of the device's destination address.
 * This routine does _not_ program the device's destination address.
 *
 * @param destAddr device destination address
 */
/*public*/ void LncvDevice::setDestAddr(int destAddr) {this->deviceAddress = destAddr;}
/*public*/ void LncvDevice::setDevName(QString s) {deviceName = s;}
/*public*/ void LncvDevice::setRosterName(QString s) {rosterEntryName = s;}
/*public*/ void LncvDevice::setSwVersion(int version) {swVersion = version;}
/*public*/ DecoderFile* LncvDevice::getDecoderFile() {
    return decoderFile;
}
/*public*/ void LncvDevice::setDecoderFile(DecoderFile* f) {
    decoderFile = f;
}

/*public*/ RosterEntry* LncvDevice::getRosterEntry() {
    return rosterEntry;
}
/*public*/ void LncvDevice::setRosterEntry(RosterEntry* e) {
    rosterEntry = e;
    setRosterName(e->getId()); // is a name (String)
}

// optional: remember last used CV
/*public*/ int LncvDevice::getCvNum() {
    return cvNum;
}
/*public*/ void LncvDevice::setCvNum(int num) {
    cvNum = num;
}
/*public*/ int LncvDevice::getCvValue() {
    return cvValue;
}
/*public*/ void LncvDevice::setCvValue(int val) {
    cvValue = val;
}

///*private*/ /*final*/ static Logger log = LoggerFactory.getLogger(LncvDevice.class);
