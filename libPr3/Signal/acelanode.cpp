#include "acelanode.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "acelasystemconnectionmemo.h"
#include "acelamessage.h"
#include "acelareply.h"
#include "acelatrafficcontroller.h"
#include "jmriexception.h"

/**
 *
 * Models an Acela node.
 * <p>
 * Nodes are numbered from 0. The first watchman node carries the first 8
 * sensors 0 to 7, etc.
 * <p>
 * The array of sensor states is used to update sensor known state only when
 * there's a change on the serial bus. This allows for the sensor state to be
 * updated within the program, keeping this updated state until the next change
 * on the serial bus. E.g. you can manually change a state via an icon, and not
 * have it change back the next time that node is polled.
 * <p>
 * Same applies to the outputs (Dash-8s and Signalmen)
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Bob Jacobsen, Dave Duchamp, multiNode extensions, 2004
 * @author Bob Coleman Copyright (C) 2007, 2008, 2009 Based on CMRI serial
 * example, modified to establish Acela support.
 */
// /*public*/  class AcelaNode extends AbstractNode {

/**
 * Maximum number of sensors/outputs any node of any type can carry.
 */
/*static*/ /*final*/ int AcelaNode::MAXSENSORBITS = 16;  // Used to initialize arrays
/*static*/ /*final*/ int AcelaNode::MAXOUTPUTBITS = 16;  // Used to initialize arrays
/*static*/ /*final*/ int AcelaNode:: MAXNODE = 1024;
/*private*/ /*static*/ int AcelaNode::MAXDELAY = 65535;

// class constants
/*public*/  /*static*/ /*final*/const qint8 AcelaNode::AC = 0x00; // Acela Interface module (no inputs, no outputs)
// Does not really return a code of 0x00
/*public*/ /*static*/ /*final*/const qint8 AcelaNode::TB = 0x01; // TrainBrain (4 output bits and 4 input bits)
/*public*/ /*static*/ /*final*/const qint8 AcelaNode::D8 = 0x02; // Dash-8 (8 output bits)
/*public*/ /*static*/ /*final*/const qint8 AcelaNode::WM = 0x03; // Watchman (8 input bits)
/*public*/ /*static*/ /*final*/const qint8 AcelaNode::SM = 0x04; // SignalMan (16 output bits)
/*public*/ /*static*/ /*final*/const qint8 AcelaNode::SC = 0x05; // SmartCab (1 output bits. no input bits)
/*public*/ /*static*/ /*final*/const qint8 AcelaNode::SW = 0x06; // SwitchMan (16 output bits. no input bits)
/*public*/ /*static*/ /*final*/const qint8 AcelaNode::YM = 0x07; // YardMaster (16 output bits. no input bits)
/*public*/ /*static*/ /*final*/const qint8 AcelaNode::SY = 0x08; // Sentry (no output bits. 16 input bits)
/*public*/ /*static*/ /*final*/const qint8 AcelaNode::UN = 0x09; // Unidentified module -- should be FF
/*public*/  /*static*/ /*final*/ QString AcelaNode::moduleTypes = "ACTBD8WMSMSCSWYMSYUN";

/*static*/ /*final*/ QVector<QString> AcelaNode::nodeNames = QVector<QString>{"0", "1", "2", "3", "4",
    "5", "6", "7", "8", "9",
    "10", "11", "12", "13", "14",
    "15", "16", "17", "18", "19"
};

/*public*/  /*static*/ QVector<QString> AcelaNode::getNodeNames() {
    //return nodeNames.clone();
 return QVector<QString>(nodeNames);
}

/*static*/ /*final*/ QVector<QString> AcelaNode::moduleNames =  QVector<QString>{"Acela",
    "TrainBrain",
    "Dash-8",
    "Watchman",
    "SignalMan",
    "SmartCab",
    "SwitchMan",
    "YardMaster",
    "Sentry"
};

/*public*/  /*static*/ QVector<QString> AcelaNode::getModuleNames() {
    //return moduleNames.clone();
 return QVector<QString>(moduleNames);
}

/*static*/ /*final*/ QVector<QString> AcelaNode::moduleTips = QVector<QString>{"Acela",
    "TrainBrain has 4 output circuits and 4 input circuits",
    "Dash-8 has 8 output circuits and no input circuits",
    "Watchman has no output circuits and 8 input circuits",
    "SignalMan has 16 output circuits and no input circuits",
    "SmartCab has 1 output circuit and no input circuits",
    "SwitchMan has 16 output circuits and no input circuits",
    "YardMaster has 16 output circuits and no input circuits",
    "Sentry has no output circuits and 16 input circuits"
};

/*public*/  /*static*/ /*final*/ QString AcelaNode::sensorTypes = "NFSBCGDT";
/*public*/  /*static*/ /*final*/ QString AcelaNode::sensorPolarities = "ACTINV";
/*public*/  /*static*/ /*final*/ QString AcelaNode::outputWireds = "NONC";
/*public*/  /*static*/ /*final*/ QString AcelaNode::outputInits = "OFFACT";
/*public*/  /*static*/ /*final*/ QString AcelaNode::outputTypes = "ONOFFPULSEBLINK";
/*public*/  /*static*/ /*final*/ int AcelaNode::ONOFF = 0;
/*public*/  /*static*/ /*final*/ int AcelaNode::PULSE = 1;
/*public*/  /*static*/ /*final*/ int AcelaNode::BLINK = 2;
/*public*/  /*static*/ /*final*/ QString AcelaNode::outputSignalHeadTypes = "UKNOWNDOUBLETRIPLEBPOLARWIGWAG";
/*public*/  /*static*/ /*final*/const int AcelaNode::UKNOWN = 0;
/*public*/  /*static*/ /*final*/const int AcelaNode::DOUBLE = 1;
/*public*/  /*static*/ /*final*/const int AcelaNode::TRIPLE = 2;
/*public*/  /*static*/ /*final*/const int AcelaNode::BPOLAR = 3;
/*public*/  /*static*/ /*final*/const int AcelaNode::WIGWAG = 4;
// These can be removed in June 2010:
/*public*/  /*static*/ /*final*/ QString AcelaNode::outputONOFF = "ONOFF";   // used to dump/restore config file.
/*public*/  /*static*/ /*final*/ QString AcelaNode::outputLEN0 = "0";        // used to dump/restore config file.
/*public*/  /*static*/ /*final*/ QString AcelaNode::outputNO = "N0";         // used to dump/restore config file.
/*protected*/ int startingOutputAddress = -1;           // used to aid linear address search
/*protected*/ int endingOutputAddress = -1;             // used to aid linear address search
/*protected*/ int startingSensorAddress = -1;           // used to aid linear address search
/*protected*/ int endingSensorAddress = -1;             // used to aid linear address search

/**
 * Create a new AcelaNode instance on the TrafficController associated
 * with the default AcelaSystemConnectionMemo.
 * <p>
 * Assumes a node address of 0, and a node type of NO_CARD. If this
 * constructor is used, actual node address must be set using
 * {@link jmri.jmrix.AbstractNode#setNodeAddress(int)} and actual
 * node type using {@link #setNodeType(int)}
 */
/*public*/  AcelaNode::AcelaNode(QObject* parent) : AbstractNode(parent)
{
    common(0, UN, ((AcelaSystemConnectionMemo*)InstanceManager::getDefault("AcelaSystemConnectionMemo"))->getTrafficController());
}

/**
 * Create a new AcelaNode instance and initialize default instance variables.
 *
 * @param address the address of first bit on Acela bus (0-1023) type - D8, SM, WM
 * @param type a type constant from the class
 * @param tc the TrafficControllerfor this connection
 */
/*public*/  AcelaNode::AcelaNode(int address, int type, AcelaTrafficController* tc, QObject* parent) : AbstractNode(parent){
    common(address, type, tc);
}

void AcelaNode::common(int address, int type, AcelaTrafficController *tc)
{
 // set address and type and check validity
    setNodeAddress(address);
    setNodeType(type);

    // set default values for other instance variables
    transmissionDelay = 0;

    // clear the Sensor arrays
    for (int i = 0; i < MAXSENSORBITS; i++) {
        sensorArray[i] = nullptr;
        sensorNeedInit[i] = false;
        sensorHasBeenInit[i] = false;
        sensorLastSetting[i] = Sensor::UNKNOWN;
        sensorType[i] = 2; // Car Gap
        sensorPolarity[i] = 1; // Inverse
        sensorThreshold[i] = 4; // Normal -- 0010 0
        sensorConfigArray[i] = 0x00; // Normal
    }

    // clear all output bits
    for (int i = 0; i < MAXOUTPUTBITS; i++) {
        outputArray[i] = 0;
        outputSpecial[i] = 0;
        outputSignalHeadType[i] = 0;
        outputInit[i] = 0;  // Off
        outputWired[i] = 0; // NO (Normally Open)
        outputType[i] = 0; // ONOFF
        outputLength[i] = 10; // 10 tenths of a second
        outputNeedToSend[i] = false;
    }

    // initialize other operational instance variables
    resetMustSend();
    needInit = false;
    hasActiveSensors = false;

    // register this node
    tc->registerAcelaNode(this);
}

/*public*/  void AcelaNode::initNode() {
    if (outputbitsPerCard > 0) {
        // check to see if we can use bulk mode
        bool bulk_message = true;
        int c = 0;
        while (c < outputbitsPerCard) {
            if ((outputType[c] != AcelaNode::ONOFF)
                    || (outputSpecial[c] != 0)) {
                bulk_message = false;
            }
            c++;
        }

        // Initialize all output circuits
        for (int i = 0; i < MAXOUTPUTBITS; i++) {
            outputArray[i] = (qint8) outputInit[i];
            if (!bulk_message) {
                outputNeedToSend[i] = true;
            }
            //  outputWired is applied as the command is being constructed so all GUI views on as on and off as off.
        }
        setMustSend();
    }
    if (sensorbitsPerCard > 0) {
        // Initialize all sensor circuits
        for (int i = 0; i < MAXSENSORBITS; i++) {
            sensorConfigArray[i] = (qint8) ((qint8) (sensorThreshold[i] << 3) + (qint8) (sensorType[i] << 1) + (qint8) (sensorPolarity[i]));
            sensorNeedInit[i] = true;
        }
        hasActiveSensors = true;
    }
}

/**
 * Set starting output address for range.
 * Used to help linear address search.
 * @param startingAddress starting output address for range.
 */
/*public*/  void AcelaNode::setStartingOutputAddress(int startingAddress) {
    startingOutputAddress = startingAddress;
}

/**
 * Get starting output address for range.
 * Used to help linear address search.
 * @return starting output address.
 */
/*public*/  int AcelaNode::getStartingOutputAddress() {
    return startingOutputAddress;
}

/**
 * Set ending output address for range.
 * Used to help linear address search.
 * @param endingAddress end output address for range.
 */
/*public*/  void AcelaNode::setEndingOutputAddress(int endingAddress) {
    endingOutputAddress = endingAddress;
}

/**
 * Get ending output address for range.
 * Used to help linear address search.
 * @return end output address for range.
 */
/*public*/  int AcelaNode::getEndingOutputAddress() {
    return endingOutputAddress;
}

/**
 * Set starting sensor address for range.
 * Used to help linear address search.
 * @param startingAddress start sensor address for range.
 */
/*public*/  void AcelaNode::setStartingSensorAddress(int startingAddress) {
    startingSensorAddress = startingAddress;
}

/**
 * Get starting sensor addresses for range.
 * Used to help linear address search.
 * @return starting sensor address for range.
 */
/*public*/  int AcelaNode::getStartingSensorAddress() {
    return startingSensorAddress;
}

/**
 * Set ending sensor addresses for range.
 * Used to help linear address search.
 * @param endingAddress end sensor address.
 */
/*public*/  void AcelaNode::setEndingSensorAddress(int endingAddress) {
    endingSensorAddress = endingAddress;
}

/**
 * Get ending sensor addresses for range.
 * Used to help linear address search.
 * @return end of range sensor address.
 */
/*public*/  int AcelaNode::getEndingSensorAddress() {
    return endingSensorAddress;
}

/**
 * Set an output bit on this node.
 *
 * @param bitNumber the bit to set
 * @param state bit state to set: 'true' for 0, 'false' for 1
 */
/*public*/  void AcelaNode::setOutputBit(int bitNumber, bool state) {
    // Save old state
    qint8 oldbyte = 0;
    int newbitNumber = 0;
    newbitNumber = bitNumber - startingOutputAddress;
    oldbyte = outputArray[newbitNumber];

    if (state) {
        outputArray[newbitNumber] = 1;
    } else {
        outputArray[newbitNumber] = 0;
    }

    // check for change, necessitating a send
    bool bulk_message = true;
    int c = 0;
    while (c < outputbitsPerCard) {
        if ((outputType[c] != AcelaNode::ONOFF)
                || (outputSpecial[c] != 0)) {
            bulk_message = false;
        }
        c++;
    }
    if (bulk_message) {
        // check for change, necessitating a send
        if (oldbyte != outputArray[newbitNumber]) {
            setMustSend();
        }
    } else {
        outputNeedToSend[newbitNumber] = true;
        setMustSend();
    }
}

/**
 * Get the current state of an output bit.
 *
 * @param bitNumber the bit. Bits are numbered from 0 for Acela
 * @return 'true' for 0, 'false' for 1
 */
/*public*/  bool AcelaNode::getOutputBit(int bitNumber) {
    int newbitNumber = 0;
    newbitNumber = bitNumber - startingOutputAddress;
    qint8 testByte = outputArray[newbitNumber];
    return  (testByte != 0);
}

/**
 * {@inheritDoc}
 */
///*private*/
/*public*/  bool AcelaNode::getSensorsActive() {
    return hasActiveSensors;
}

/**
 * Get Output configuration values.
 * @param circuitnum wired output index number.
 * @return  configuration value.
 */
/*public*/  int AcelaNode::getOutputWired(int circuitnum) {
    return outputWired[circuitnum];
}

/*public*/  QString AcelaNode::getOutputWiredString(int circuitnum) {
    int sensortype = outputWired[circuitnum];
    return outputWireds.mid(sensortype * 2, sensortype * 2 + 2);
}

/**
 * Set Output configuration values.
 * @param circuitnum output index number.
 * @param type output type.
 */
/*public*/  void AcelaNode::setOutputWired(int circuitnum, int type) {
    outputWired[circuitnum] = type;
}

/*public*/  void AcelaNode::setOutputWiredString(int circuitnum, QString stringtype) {
    int type = outputWireds.lastIndexOf(stringtype) / 2;
    outputWired[circuitnum] = type;
}

/*public*/  int AcelaNode::getOutputInit(int circuitnum) {
    return outputInit[circuitnum];
}

/*public*/  QString AcelaNode::getOutputInitString(int circuitnum) {
    int sensortype = outputInit[circuitnum];
    return outputInits.mid(sensortype * 3, sensortype * 3 + 3);
}

/*public*/  void AcelaNode::setOutputInit(int circuitnum, int type) {
    outputInit[circuitnum] = type;
}

/*public*/  void AcelaNode::setOutputInitString(int circuitnum, QString stringtype) {
    int type = outputInits.lastIndexOf(stringtype) / 3;
    outputInit[circuitnum] = type;
}

/*public*/  int AcelaNode::getOutputType(int circuitnum) {
    return outputType[circuitnum];
}

/*public*/  QString AcelaNode::getOutputTypeString(int circuitnum) {
    int outputtype = outputType[circuitnum];
    return outputTypes.mid(outputtype * 5, outputtype * 5 + 5);
}

/*public*/  void AcelaNode::setOutputType(int circuitnum, int type) {
    outputType[circuitnum] = type;
}

/*public*/  void AcelaNode::setOutputTypeString(int circuitnum, QString stringtype) {
    int type = outputTypes.lastIndexOf(stringtype) / 5;
    outputType[circuitnum] = type;
}

/*public*/  int AcelaNode::getOutputLength(int circuitnum) {
    return outputLength[circuitnum];
}

/*public*/  void AcelaNode::setOutputLength(int circuitnum, int newlength) {
    outputLength[circuitnum] = newlength;
}

/*public*/  int AcelaNode::getOutputSpecial(int circuitnum) {
    int newbitNumber = circuitnum - startingOutputAddress;
    return outputSpecial[newbitNumber];
}

/*public*/  void AcelaNode::setOutputSpecial(int circuitnum, int type) {
    int newbitNumber = circuitnum - startingOutputAddress;
    outputSpecial[newbitNumber] = type;
}

/*public*/  int AcelaNode::getOutputSignalHeadType(int circuitnum) {
    int newbitNumber = circuitnum - startingOutputAddress;
    return outputSignalHeadType[newbitNumber];
}

/*public*/  QString AcelaNode::getOutputSignalHeadTypeString(int circuitnum) {
    int newbitNumber = circuitnum - startingOutputAddress;
    int outputsignalheadtype = outputSignalHeadType[newbitNumber];
    return outputSignalHeadTypes.mid(outputsignalheadtype * 6, outputsignalheadtype * 6 + 6);
}

/*public*/  void AcelaNode::setOutputSignalHeadType(int circuitnum, int type) {
    int newbitNumber = circuitnum - startingOutputAddress;
    outputSignalHeadType[newbitNumber] = type;
}

/*public*/  void AcelaNode::setOutputSignalHeadTypeString(int circuitnum, QString stringtype) {
    int newbitNumber = circuitnum - startingOutputAddress;
    int type = outputSignalHeadTypes.lastIndexOf(stringtype) / 6;
    outputSignalHeadType[newbitNumber] = type;
}

/**
 * public  method to set and return Sensor configuration values.
 * @param circuitnum sensor type array index number.
 * @return sensor index value.
 */
/*public*/  int AcelaNode::getSensorType(int circuitnum) {
    return sensorType[circuitnum];
}

/*public*/  QString AcelaNode::getSensorTypeString(int circuitnum) {
    int sensortype = sensorType[circuitnum];
    return sensorTypes.mid(sensortype * 2, sensortype * 2 + 2);
}

/*public*/  void AcelaNode::setSensorType(int circuitnum, int type) {
    sensorType[circuitnum] = type;
}

/*public*/  void AcelaNode::setSensorTypeString(int circuitnum, QString stringtype) {
    int type = sensorTypes.lastIndexOf(stringtype) / 2;
    sensorType[circuitnum] = type;
}

/*public*/  int AcelaNode::getSensorPolarity(int circuitnum) {
    return sensorPolarity[circuitnum];
}

/*public*/  QString AcelaNode::getSensorPolarityString(int circuitnum) {
    int sensorpolarity = sensorPolarity[circuitnum];
    return sensorPolarities.mid(sensorpolarity * 3, sensorpolarity * 3 + 3);
}

/*public*/  void AcelaNode::setSensorPolarity(int circuitnum, int polarity) {
    sensorPolarity[circuitnum] = polarity;
}

/*public*/  void AcelaNode::setSensorPolarityString(int circuitnum, QString stringpolarity) {
    int polarity = sensorPolarities.lastIndexOf(stringpolarity) / 3;
    sensorPolarity[circuitnum] = polarity;
}

/*public*/  int AcelaNode::getSensorThreshold(int circuitnum) {
    return sensorThreshold[circuitnum];
}

/*public*/  void AcelaNode::setSensorThreshold(int circuitnum, int threshold) {
    sensorThreshold[circuitnum] = threshold;
}

/**
 * public  method to return node type.
 * @return node type number.
 */
/*public*/  int AcelaNode::getNodeType() {
    return (nodeType);
}

/*public*/  QString AcelaNode::getNodeTypeString() {
    return moduleTypes.mid(nodeType * 2, nodeType * 2 + 2);
}

/**
 * public  method to set node type.
 * @param stringtype string form of node type.
 */
/*public*/  void AcelaNode::setNodeTypeString(QString stringtype) {
    int type = moduleTypes.lastIndexOf(stringtype) / 2;
    setNodeType(type);
}

/*public*/  void AcelaNode::setNodeType(int type) {
    nodeType = type;
    // set default values for other instance variables
    switch (type) {
        case AC:
        case UN:
            outputbitsPerCard = 0;
            sensorbitsPerCard = 0;
            break;
        case TB:
            outputbitsPerCard = 4;
            sensorbitsPerCard = 4;
            break;
        case D8:
            outputbitsPerCard = 8;
            sensorbitsPerCard = 0;
            break;
        case WM:
            outputbitsPerCard = 0;
            sensorbitsPerCard = 8;
            break;
        case SC:
            outputbitsPerCard = 1;
            sensorbitsPerCard = 0;
            break;
        case SM:
        case SW:
        case YM:
            outputbitsPerCard = 16;
            sensorbitsPerCard = 0;
            break;
        case SY:
            outputbitsPerCard = 0;
            sensorbitsPerCard = 16;
            break;
        default:
            outputbitsPerCard = 0;
            sensorbitsPerCard = 0;
            log->error(tr("Bad node type - %1").arg(type));
    }
}

/**
 * public  method to return number of bits per card.
 * @return number of output bits per card.
 */
/*public*/  int AcelaNode::getNumOutputBitsPerCard() {
    return (outputbitsPerCard);
}

/*public*/  int AcelaNode::getNumSensorBitsPerCard() {
    return (sensorbitsPerCard);
}

/**
 * {@inheritDoc}
 */
///*private*/
/*public*/  bool AcelaNode::checkNodeAddress(int address) {
    return ((address >= 0) && (address < MAXNODE));
}

/**
 * Get the number of sensor bits per node.
 *
 * @return sensorbitsPerCard
 */
/*public*/  int AcelaNode::getSensorBitsPerCard() {
    return (sensorbitsPerCard);
}

/**
 * Get the transmission delay on this node.
 * @return delay in 10s of microseconds.
 */
/*public*/  int AcelaNode::getTransmissionDelay() {
    return (transmissionDelay);
}

/**
 * Set transmission delay.
 * <p>
 * Note: two bytes are used, so range is 0-65,535. If delay is out of
 * range, it is restricted to the allowable range.
 *
 * @param delay a delay between bytes on receive (units of 10 microsec.)
 */
/*public*/  void AcelaNode::setTransmissionDelay(int delay) {
    if ((delay < 0) || (delay > MAXDELAY)) {
        log->warn(tr("transmission delay %1 out of 0-65535 range").arg(delay));
        if (delay < 0) {
            delay = 0;
        }
        if (delay > MAXDELAY) {
            delay = MAXDELAY;
        }
    }
    transmissionDelay = delay;
}

/**
 * {@inheritDoc}
 */
///*private*/
/*public*/  AbstractMRMessage* AcelaNode::createInitPacket() {
    return nullptr;
}

/**
 * Create a Transmit packet (SerialMessage) to send current state.
 */
///*private*/
/*public*/  AbstractMRMessage* AcelaNode::createOutPacket() {
    //  Set up variables that will be used at the end to send the msg.
    int cmdlen = 3;         // Message length == 3, 4, or 5
    qint8 cmdcode = 0x03;    // Message command: default == activate output
    qint8 addrhi = 0x00;     // Used to address more than 255 nodes
    qint8 addrlo = 0x00;     // Address of node
    qint8 settinghi = 0x00;  // Used when setting 16 outputs
    qint8 settinglo = 0x00;  // Used to set output state

    // If we can, we want to send one bulk message for the entire node
    // We can only send a bulk message if all of the output circuits have
    // outputType of ONOFF
    bool bulk_message = true;
    int c = 0;
    while (c < outputbitsPerCard) {
        if ((outputType[c] != AcelaNode::ONOFF) || (outputSpecial[c] != 0)) {
            bulk_message = false;
        }
        c++;
    }

    //  For now, we are not going to support more than 255 nodes
    //  so we leave addrhi at 0x00.
    // We need to see if there is a second output circuit for this
    // node that we need to send.  If there is then we need to set
    // the mustsend flag for the node because the Traffic Controller
    // reset it before calling this routine.
    if (!bulk_message) {
        c = 0;
        bool foundfirst = false;
        bool foundanother = false;
        while (c < outputbitsPerCard) {
            if (outputNeedToSend[c] && foundfirst) {
                foundanother = true;
            }
            if (outputNeedToSend[c] && !foundfirst) {
                foundfirst = true;
            }
            c++;
        }
        if (foundanother) {
            setMustSend();
        }
    }

    //  If we are going to do a bulk command then the address will be
    //  the starting address.  If we are not going to do a bulk command
    //  then the address will start from the starting address.
    int tempint = startingOutputAddress;
    addrlo = tempint/*.byteValue()*/;

    // For each nodetype set up variables that will end up in the msg
    if (bulk_message) {
        if (nodeType == TB) {
            cmdlen = 4;
            cmdcode = 0x07;  // Set 4 outputs: bit on means output on
            int tempsettings = (outputArray[3] ^ outputWired[3]) * 8 + (outputArray[2] ^ outputWired[2]) * 4 + (outputArray[1] ^ outputWired[1]) * 2 + (outputArray[0] ^ outputWired[0]) * 1;
            settinglo = (qint8) (tempsettings);
        }
        if (nodeType == D8) {
            cmdlen = 4;
            cmdcode = 0x08;  // Set 8 outputs: bit on means output on
            int tempsettings = (outputArray[3] ^ outputWired[3]) * 8 + (outputArray[2] ^ outputWired[2]) * 4 + (outputArray[1] ^ outputWired[1]) * 2 + (outputArray[0] ^ outputWired[0]) * 1;
            tempsettings = (outputArray[7] ^ outputWired[7]) * 128 + (outputArray[6] ^ outputWired[6]) * 64 + (outputArray[5] ^ outputWired[5]) * 32 + (outputArray[4] ^ outputWired[4]) * 16 + tempsettings;
            settinglo = (qint8) (tempsettings);
        }
        if ((nodeType == WM) || (nodeType == SY)) {
            //cmdlen = 3;
            cmdcode = 0x01;  //  This really is an error case since these
            //  nodes do not have outputs
        }
        if (nodeType == SC) {
            //cmdlen = 3;
            cmdcode = 0x01;  //  This really is an error case since these
            //  nodes do not have outputs
        }
        if ((nodeType == SM) || (nodeType == SW) || (nodeType == YM)) {
            cmdlen = 5;
            cmdcode = 0x09;  // Set 16 outputs: bit on means output on
            int tempsettings = (outputArray[3] ^ outputWired[3]) * 8 + (outputArray[2] ^ outputWired[2]) * 4 + (outputArray[1] ^ outputWired[1]) * 2 + (outputArray[0] ^ outputWired[0]) * 1;
            tempsettings = (outputArray[7] ^ outputWired[7]) * 128 + (outputArray[6] ^ outputWired[6]) * 64 + (outputArray[5] ^ outputWired[5]) * 32 + (outputArray[4] ^ outputWired[4]) * 16 + tempsettings;
            settinglo = (qint8) (tempsettings);
            int tempsettings2 = (outputArray[11] ^ outputWired[11]) * 8 + (outputArray[10] ^ outputWired[10]) * 4 + (outputArray[9] ^ outputWired[9]) * 2 + (outputArray[8] ^ outputWired[8]) * 1;
            tempsettings2 = (outputArray[15] ^ outputWired[15]) * 128 + (outputArray[14] ^ outputWired[14]) * 64 + (outputArray[13] ^ outputWired[13]) * 32 + (outputArray[12] ^ outputWired[12]) * 16 + tempsettings2;
            settinghi = (qint8) (tempsettings2);
        }
    } else {  // Not bulk message
        // For now, we will simply send the first output circuit that
        // we encounter.  In theory, this could starve a later output
        // circuit on this node.  If someone complains then we should
        // implement a more complicated algorithm.

        c = 0;
        bool foundsomething = false;
        while ((c < outputbitsPerCard) && !foundsomething) {
            if (outputNeedToSend[c]) {
                // Need to adjust addr to address the actual output
                // circuit rather than the starting output address
                // That it currently points to.
                int tempaddr = c + addrlo;
                addrlo = tempaddr/*.byteValue()*/;

                // Reset the needtosend flag for this output circuit
                outputNeedToSend[c] = false;

                // Reset the foundfirst flag
                foundsomething = true;

                // We are here because at least one output circuit on
                // this node is not set to a type of ONOFF
                //  -- but some of the output circuits may still be
                // of type ONOFF.
                if (outputSpecial[c] == 0) {
                    if (outputType[c] == AcelaNode::ONOFF) {
                        // outputArray[c] tells us to to turn the output on
                        // or off.
                        // outputWired[c] tells us whether the relay is
                        // wired backwards.
                        // command 0x01 is activate
                        // command 0x02 is deactivate
                        int tempcommand = (outputArray[c] ^ outputWired[c]);
                        if (tempcommand == 0) {
                            tempcommand = 2;
                        }
                        cmdcode = (qint8) (tempcommand);
                        cmdlen = 3;
                    }

                    if (outputType[c] == AcelaNode::BLINK) {
                        // outputArray[c] tells us to to turn the output on
                        // or off.
                        // outputWired[c] tells us whether the output
                        // should start on or start off.
                        // outputLength[c] tells us how long in tenths of
                        // a second to blink.
                        // output will continue to blink until turned off.
                        // command 0x02 is deactivate
                        // command 0x05 is blink
                        // command 0x06 is reverse blink
                        int tempcommand = outputArray[c];
                        if ((tempcommand == 1) && (outputWired[c] == 1)) {
                            tempcommand = 5;
                        }
                        if ((tempcommand == 1) && (outputWired[c] == 0)) {
                            tempcommand = 6;
                        }
                        if (tempcommand == 0) {
                            tempcommand = 2;
                        }
                        cmdcode = (qint8) (tempcommand);
                        if (cmdcode == 0x02) {
                            cmdlen = 3;
                        } else {
                            cmdlen = 4;
                            settinglo = (qint8) outputLength[c];
                        }
                    }

                    if (outputType[c] == AcelaNode::PULSE) {
                        // outputArray[c] tells us to to turn the output on
                        // or off.
                        // outputWired[c] tells us whether the output
                        // should start on or start off.
                        // outputLength[c] tells us how long in tenths of
                        // a second to pulse the output.
                        // output will actually return to off state after
                        // the pulse duration -- but we will never know.
                        // Program will need to fake this out.
                        // command 0x02 is deactivate
                        // command 0x03 is to pulse on
                        // command 0x04 is to pulse off
                        int tempcommand = outputArray[c];
                        if ((tempcommand == 1) && (outputWired[c] == 1)) {
                            tempcommand = 4;
                        }
                        if ((tempcommand == 1) && (outputWired[c] == 0)) {
                            tempcommand = 3;
                        }
                        if (tempcommand == 0) {
                            tempcommand = 2;
                        }
                        cmdcode = (qint8) (tempcommand);
                        if (cmdcode == 0x02) {
                            cmdlen = 3;
                        } else {
                            cmdlen = 4;
                            settinglo = (qint8) outputLength[c];
                        }
                    }
                } else {
                    switch (outputSignalHeadType[c]) {
                        case DOUBLE: {
                            switch (outputSpecial[c]) {
                                case 1:
                                    cmdcode = 0x0c;
                                    settinglo = 0x01;
                                    break; // Red
                                case 2:
                                    cmdcode = 0x0c;
                                    settinglo = 0x02;
                                    break; // Flashing red
                                case 3: // Yellow
                                case 4: // Flashing Yellow
                                case 6: // Flashing Green
                                    cmdcode = 0x0c;
                                    settinglo = 0x08;
                                    break;
                                case 5:
                                    cmdcode = 0x0c;
                                    settinglo = 0x04;
                                    break; // Green
                                case 7:
                                    cmdcode = 0x0c;
                                    settinglo = 0x00;
                                    break; // Dark
                                default:
                                    cmdcode = 0x0c;
                                    settinglo = 0x03;
                                    break; // Flashing red
                            }
                            break;
                        }
                        case TRIPLE: {
                            switch (outputSpecial[c]) {
                                case 1:
                                    cmdcode = 0x0d;
                                    settinglo = 0x01;
                                    break; // Red
                                case 2:
                                    cmdcode = 0x0d;
                                    settinglo = 0x02;
                                    break; // Flashing red
                                case 3:
                                    cmdcode = 0x0d;
                                    settinglo = 0x04;
                                    break; // Yellow
                                case 4:
                                    cmdcode = 0x0d;
                                    settinglo = 0x08;
                                    break; // Flashing Yellow
                                case 5:
                                    cmdcode = 0x0d;
                                    settinglo = 0x10;
                                    break; // Green
                                case 6:
                                    cmdcode = 0x0d;
                                    settinglo = 0x20;
                                    break; // Flashing Green
                                case 7:
                                    cmdcode = 0x0d;
                                    settinglo = 0x00;
                                    break; // Dark
                                default:
                                    cmdcode = 0x0d;
                                    settinglo = 0x03;
                                    break; // Flashing red
                            }
                            break;
                        }
                        case BPOLAR: {
                            switch (outputSpecial[c]) {
                                case 1:
                                    cmdcode = 0x0c;
                                    settinglo = 0x01;
                                    break; // Red
                                case 2:
                                    cmdcode = 0x0c;
                                    settinglo = 0x02;
                                    break; // Flashing red
                                case 3:
                                    cmdcode = 0x0c;
                                    settinglo = 0x10;
                                    break; // Yellow
                                case 4:
                                    cmdcode = 0x0c;
                                    settinglo = 0x20;
                                    break; // Flashing Yellow
                                case 5:
                                    cmdcode = 0x0c;
                                    settinglo = 0x04;
                                    break; // Green
                                case 6:
                                    cmdcode = 0x0c;
                                    settinglo = 0x08;
                                    break; // Flashing Green
                                case 7:
                                    cmdcode = 0x0c;
                                    settinglo = 0x00;
                                    break; // Dark
                                default:
                                    cmdcode = 0x0c;
                                    settinglo = 0x03;
                                    break; // Flashing red
                            }
                            break;
                        }
                        case WIGWAG: {
                            switch (outputSpecial[c]) {
                                case 1: // Red
                                case 2: // Flashing red
                                case 3:
                                case 4: // Flashing Yellow
                                case 5: // Green
                                case 6: // Flashing Green
                                    cmdcode = 0x0c;
                                    settinglo = 0x0B;
                                    break;
                                case 7: // Dark
                                    cmdcode = 0x0c;
                                    settinglo = 0x00;
                                    break;
                                default: // Flashing red
                                    cmdcode = 0x0c;
                                    settinglo = 0x0F;
                                    break;
                            }
                            break;
                        }
                        default: {
                            switch (outputSpecial[c]) {
                                case 1:
                                    cmdcode = 0x0d;
                                    settinglo = 0x01;
                                    break; // Red
                                case 3:
                                    cmdcode = 0x0d;
                                    settinglo = 0x04;
                                    break; // Yellow
                                case 4:
                                    cmdcode = 0x0d;
                                    settinglo = 0x08;
                                    break; // Flashing Yellow
                                case 5:
                                    cmdcode = 0x0d;
                                    settinglo = 0x10;
                                    break; // Green
                                case 6:
                                    cmdcode = 0x0d;
                                    settinglo = 0x30;
                                    break; // Flashing Green
                                case 7:
                                    cmdcode = 0x0d;
                                    settinglo = 0x00;
                                    break; // Dark
                                case 2: // Flashing red
                                default:
                                    cmdcode = 0x0d;
                                    settinglo = 0x03;
                                    break;
                            }
                        }
                    }
                    cmdlen = 4;
                }
            }
            c++;
        }
    }

    AcelaMessage* m = new AcelaMessage(cmdlen);
    m->setElement(0, cmdcode);
    m->setElement(1, addrhi);
    m->setElement(2, addrlo);
    if (cmdlen > 3) {
        if (cmdlen > 4) {
            m->setElement(3, settinghi);
        } else {
            m->setElement(3, settinglo);
        }
    }
    if (cmdlen > 4) {
        m->setElement(4, settinglo);
    }
    m->setBinary(true);
    return m;
}

/**
 * Use the contents of the poll reply to mark changes.
 *
 * @param l Reply to a poll operation
 */
/*public*/  void AcelaNode::markChanges(AcelaReply* l) {

    // We are going to get back 8 bits per byte from the poll.
    // We have three types of sensor modules:
    // TB with 4 sensor inputs, WM with 8 sensor inputs, SY with 16 sensor inputs
    // The TB causes two cases: either the bits we want start at bit 0 or bit 4.
    // The sensor bits we want for a TB will always be within one byte.
    // The sensor bits we want for a WM could be within one byte if we start at 0,
    //    or spread across two bytes if we start at 4.
    // The sensor bits we want for a SY could be within two byte if we start at 0,
    //    or spread across three bytes if we start at 4.
    int firstByteNum = startingSensorAddress / 8;
    int firstBitAt = startingSensorAddress % 8; // mod operator
    //int numBytes = 1;   // For TB there are only 4 sensors so always 1 byte

    log->debug(tr("Sensor Parsing for module type: %1").arg(moduleNames[nodeType]));
    log->debug(tr("Sensor Parsing has startingSensorAddress: %1").arg(startingSensorAddress));
    log->debug(tr("Sensor Parsing has firstByteNum: %1").arg(firstByteNum));
    log->debug(tr("Sensor Parsing has firstBitAt: %1").arg(firstBitAt));

    //  Using rawvalue may be unnecessary, but trying to minimize reads to getElement
    int rawvalue = l->getElement(firstByteNum);
    log->debug(tr("Sensor Parsing has first rawvalue: %1").arg(rawvalue));

    int usingByteNum = 0;

    try {
        for (int i = 0; i < sensorbitsPerCard; i++) {
            if (sensorArray[i] == nullptr) {
                log->debug(tr("Sensor Parsing for Sensor: %1 + %2 was skipped").arg(startingSensorAddress, i));
                continue;
            } // skip ones that don't exist

            log->debug(tr("Sensor Parsing for Sensor: %1 + %2").arg(startingSensorAddress, i));

            int relvalue = rawvalue;

            //  Need a temporary counter within the byte so we can shift
            int tempi = i;

            //  If necessary, shift by four before we start
            if (usingByteNum == 0) {
                if (firstBitAt == 4) {
                    for (int j = 0; j < firstBitAt; j++) {
                        relvalue = relvalue >> 1;
                    }
                    log->debug(tr("Sensor Parsing for Sensor: %1 + %2 shifted by 4: %3").arg(startingSensorAddress, i, (relvalue)));
                }
            }

            //  If necessary, get next byte
            if (firstBitAt == 4) {
                if (i >= 12) {  // Will only get here if there are 16 sensors
                    usingByteNum = 2;
                    //  Using rawvalue may be unnecessary, but trying to minimize reads to getElement
                    rawvalue = l->getElement(usingByteNum + firstByteNum);
                    log->debug(tr("Sensor Parsing (1stat4) has third rawvalue: %1").arg(rawvalue));
                    relvalue = rawvalue;
                    tempi = i - 12;  // tempi needs to shift down by 12
                } else {
                    if (i >= 4) {
                        usingByteNum = 1;
                        //  Using rawvalue may be unnecessary, but trying to minimize reads to getElement
                        rawvalue = l->getElement(usingByteNum + firstByteNum);
                        log->debug(tr("Sensor Parsing (1stat4) has second rawvalue: %1").arg(rawvalue));
                        relvalue = rawvalue;
                        tempi = i - 4;  // tempi needs to shift down by 4
                    }
                }
            } else {
                if (i >= 8) {  // Will only get here if there are 16 sensors
                    usingByteNum = 1;
                    //  Using rawvalue may be unnecessary, but trying to minimize reads to getElement
                    rawvalue = l->getElement(usingByteNum + firstByteNum);
                    log->debug(tr("Sensor Parsing has second rawvalue: %1").arg(rawvalue));
                    relvalue = rawvalue;
                    tempi = i - 8;  // tempi needs to shift down by 8
                }
            }

            log->debug(tr("Sensor Parsing for Sensor: %1 + %2 has tempi:$3").arg(startingSensorAddress, i, tempi));

            //  Finally we can isolate the bit from the poll result
            for (int j = 0; j < tempi; j++) {
                relvalue = relvalue >> 1;
            }

            log->debug(tr("Sensor Parsing for Sensor: %1 + %2 has relvalue: %3").arg(startingSensorAddress, i, (relvalue)));

            // Now that we have the relvalue need to compare to last time
            bool nooldstate = false;
            qint8 oldstate = 0x00;
            if (sensorLastSetting[i] == Sensor::ACTIVE) {
                oldstate = 0x01;
            } else {
                if (sensorLastSetting[i] == Sensor::INACTIVE) {
                    oldstate = 0x00;
                } else {
                    nooldstate = true;
                }
            }
            int newerstate = relvalue & 0x01;
            qint8 newstate = (qint8) (newerstate);

            if ((nooldstate) || (oldstate != newstate)) {
                if (nooldstate) {
                    log->debug(tr("Sensor Parsing for Sensor: %1 + %2 had no old state.").arg(startingSensorAddress, i));
                }
                if (newstate == 0x00) {
                    sensorLastSetting[i] = Sensor::INACTIVE;
                    sensorArray[i]->setKnownState(sensorLastSetting[i]);
                } else {
                    sensorLastSetting[i] = Sensor::ACTIVE;
                    sensorArray[i]->setKnownState(sensorLastSetting[i]);
                }
//                log->debug(tr("Sensor Parsing for Sensor: %1 + %2 changed state: %3 rawvalue: %4").arg(startingSensorAddress, i, sensorLastSetting[i], (rawvalue)));
            } else {
//                log->debug(tr("Sensor Parsing for Sensor: %1 + %2 did NOT change state: %3 rawvalue: %4").arg(startingSensorAddress, i, sensorLastSetting[i], (rawvalue)));
            }
        }
    } catch (JmriException* e) {
        log->error(tr("exception in markChanges: %1").arg(e->getMessage()));
    }
}

/**
 * Register a sensor on an Acela node.
 * The numbers here are 0 to MAXSENSORBITS, not 1 to MAXSENSORBITS.
 *
 * @param s       Sensor object
 * @param rawaddr index number of sensor's input bit on this
 *                node, valid range from 0 to MAXSENSORBITS
 */
/*public*/  void AcelaNode::registerSensor(Sensor *s, int rawaddr) {
    // validate the sensor ordinal
    if ((rawaddr < 0) || (rawaddr >= MAXNODE)) {
        log->error(tr("Unexpected sensor ordinal in registerSensor: %1").arg(rawaddr));
        return;
    }

    int addr = -1;
    addr = rawaddr - startingSensorAddress;

    hasActiveSensors = true;
    ((AcelaSystemConnectionMemo*)InstanceManager::getDefault("AcelaSystemConnectionMemo"))->getTrafficController()->setAcelaSensorsState(true);
    if (startingSensorAddress < 0) {
        log->info(tr("Trying to register sensor too early: %1S%2").arg(
                ((AcelaSystemConnectionMemo*)InstanceManager::getDefault("AcelaSystemConnectionMemo"))->getSystemPrefix(), // multichar prefix
                rawaddr));
    } else {

        if (sensorArray[addr] == nullptr) {
            sensorArray[addr] = s;
            if (!sensorHasBeenInit[addr]) {
                sensorNeedInit[addr] = true;
            }
        } else {
            // multiple registration of the same sensor
            log->warn(tr("Multiple registration of same sensor: %1S%2").arg(
                    ((AcelaSystemConnectionMemo*)InstanceManager::getDefault("AcelaSystemConnectionMemo"))->getSystemPrefix(), // multichar prefix
                    rawaddr));
        }
    }
}

/**
 * {@inheritDoc}
 */
///*private*/
/*public*/  bool AcelaNode::handleTimeout(AbstractMRMessage* /*m*/, AbstractMRListener* /*l*/) {
    timeout++;
    if (log->isDebugEnabled()) {
        log->warn(tr("Timeout to poll for UA=%1: consecutive timeouts: %2").arg(nodeAddress, timeout));
    }
    return false;   // tells caller to NOT force init
}

/**
 * {@inheritDoc}
 */
///*private*/
/*public*/  void AcelaNode::resetTimeout(AbstractMRMessage* /*m*/) {
    if (timeout > 0) {
        log->debug(tr("Reset %1 timeout count").arg(timeout));
    }
    timeout = 0;
}

/*private*/ /*final*/ /*static*/ Logger* AcelaNode::log = LoggerFactory::getLogger("AcelaNode");
