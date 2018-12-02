#include "dccsignalhead.h"
#include "loggerfactory.h"
#include "commandstation.h"
#include "instancemanager.h"
#include "nmrapacket.h"

/**
 * This class implements a SignalHead the maps the various appearances values to
 * aspect values in the <B>Extended Accessory Decoder Control Packet Format</B>
 * and outputs that packet to the DCC System via the generic CommandStation
 * interface
 * <P>
 * The mapping is as follows:
 * <P>
 * 0 = RED         <BR>
 * 1 = YELLOW      <BR>
 * 2 = GREEN       <BR>
 * 3 = LUNAR       <BR>
 * 4 = FLASHRED    <BR>
 * 5 = FLASHYELLOW <BR>
 * 6 = FLASHGREEN  <BR>
 * 7 = FLASHLUNAR  <BR>
 * 8 = DARK        <BR>
 * <P>
 * The FLASH appearances are expected to be implemented in the decoder.
 *
 * @author Alex Shepherd Copyright (c) 2008
 */
// /*public*/ class DccSignalHead extends AbstractSignalHead {

/*private*/ /*final*/ /*static*/ Logger* DccSignalHead::log = LoggerFactory::getLogger("DccSignalHead");

/*public*/ DccSignalHead::DccSignalHead(QString sys, QString user, QObject* parent)
 : AbstractSignalHead(sys, user, parent)
{
    //super(sys, user);
    configureHead(sys);

}

/*public*/ DccSignalHead::DccSignalHead(QString sys, QObject* parent)
 : AbstractSignalHead(sys, parent)
{
    //super(sys);
    configureHead(sys);
}

void DccSignalHead::configureHead(QString sys) {
  appearanceToOutput =  QMap<int, int>();

    //Set the default appearances
    appearanceToOutput.insert((SignalHead::RED), getDefaultNumberForApperance(SignalHead::RED));
    appearanceToOutput.insert((SignalHead::YELLOW), getDefaultNumberForApperance(SignalHead::YELLOW));
    appearanceToOutput.insert((SignalHead::GREEN), getDefaultNumberForApperance(SignalHead::GREEN));
    appearanceToOutput.insert((SignalHead::LUNAR), getDefaultNumberForApperance(SignalHead::LUNAR));
    appearanceToOutput.insert((SignalHead::FLASHRED), getDefaultNumberForApperance(SignalHead::FLASHRED));
    appearanceToOutput.insert((SignalHead::FLASHYELLOW), getDefaultNumberForApperance(SignalHead::FLASHYELLOW));
    appearanceToOutput.insert((SignalHead::FLASHGREEN), getDefaultNumberForApperance(SignalHead::FLASHGREEN));
    appearanceToOutput.insert((SignalHead::FLASHLUNAR), getDefaultNumberForApperance(SignalHead::FLASHLUNAR));
    appearanceToOutput.insert((SignalHead::DARK), getDefaultNumberForApperance(SignalHead::DARK));
    //New method separates the system name and address using $
    if (sys.contains("$")) {
        dccSignalDecoderAddress = (sys.mid(sys.indexOf("$") + 1, sys.length())).toInt();
        QString commandStationPrefix = sys.mid(0, sys.indexOf("$") - 1);
        QObjectList connList = (InstanceManager::getList("CommandStation"));

        for (int x = 0; x < connList.size(); x++) {
            CommandStation* station = static_cast<CommandStation*>(connList.at(x));
            if (station->getSystemPrefix() == (commandStationPrefix)) {
                c = station;
                break;
            }
        }

        if (c == nullptr) {
            c = static_cast<CommandStation*>(InstanceManager::getNullableDefault("CommandStation"));
            log->error("No match against the command station for " + sys + ", so will use the default");
        }
    } else {
        c = static_cast<CommandStation*>(InstanceManager::getNullableDefault("CommandStation"));
        if ((sys.length() > 2) && ((sys.at(1) == 'H') || (sys.at(1) == 'h'))) {
            dccSignalDecoderAddress = (sys.mid(2, sys.length())).toInt();
        } else {
            dccSignalDecoderAddress = (sys).toInt();
        }
    }
    // validate the decoder address
    // now some systems don't support this whole range
    // also depending on how you view the NRMA spec, 1 - 2044 or 1 - 2048
    if (dccSignalDecoderAddress < NmraPacket::accIdLowLimit || dccSignalDecoderAddress > NmraPacket::accIdAltHighLimit) {
        log->error("SignalHead decoder address out of range: " + QString::number(dccSignalDecoderAddress));
        throw IllegalArgumentException("SignalHead decoder address out of range: " + QString::number(dccSignalDecoderAddress));
    }
}

//@Override
/*public*/ void DccSignalHead::setAppearance(int newAppearance) {
    int oldAppearance = mAppearance;
    mAppearance = newAppearance;

    if (oldAppearance != newAppearance) {
        updateOutput();

        // notify listeners, if any
        firePropertyChange("Appearance", (oldAppearance), (newAppearance));
    }
}

//@Override
/*public*/ void DccSignalHead::setLit(bool newLit) {
    bool oldLit = mLit;
    mLit = newLit;
    if (oldLit != newLit) {
        updateOutput();
        // notify listeners, if any
        firePropertyChange("Lit", (oldLit), (newLit));
    }
}

/**
 * Set the held parameter.
 * <P>
 * Note that this does not directly effect the output on the layout; the
 * held parameter is a local variable which effects the aspect only via
 * higher-level logic
 */
//@Override
/*public*/ void DccSignalHead::setHeld(bool newHeld) {
    bool oldHeld = mHeld;
    mHeld = newHeld;
    if (oldHeld != newHeld) {
        // notify listeners, if any
        firePropertyChange("Held", (oldHeld), (newHeld));
    }
}

/*protected*/ void DccSignalHead::updateOutput() {
    if (c != nullptr) {
        int aspect = getOutputForAppearance(SignalHead::DARK);

        if (getLit()) {
            int app = (mAppearance);
            if (appearanceToOutput.contains(app)) {
                aspect = appearanceToOutput.value(app);
            } else {
                log->error("Unknown appearance " + QString::number(mAppearance) + " displays DARK");
            }
            /*        switch( mAppearance ){
             case SignalHead::DARK:        aspect = 8 ; break;
             case SignalHead::RED:         aspect = 0 ; break;
             case SignalHead::YELLOW:      aspect = 1 ; break;
             case SignalHead::GREEN:       aspect = 2 ; break;
             case SignalHead::LUNAR:       aspect = 3 ; break;
             case SignalHead::FLASHRED:    aspect = 4 ; break;
             case SignalHead::FLASHYELLOW: aspect = 5 ; break;
             case SignalHead::FLASHGREEN:  aspect = 6 ; break;
             case SignalHead::FLASHLUNAR:  aspect = 7 ; break;
             default :                    aspect = 8;
             log.error("Unknown appearance " + mAppearance+" displays DARK");
             break;
             }*/
        }

        QByteArray sigPacket;
        if (_useAddressOffSet) {
            sigPacket = NmraPacket::accSignalDecoderPkt(dccSignalDecoderAddress, aspect);
        } else {
            sigPacket = NmraPacket::altAccSignalDecoderPkt(dccSignalDecoderAddress, aspect);
        }
        if (!sigPacket.isNull()) {
            c->sendPacket(sigPacket, 3);
        }
    }
}


/*public*/ void DccSignalHead::useAddressOffSet(bool boo) {
    _useAddressOffSet = boo;
}

/*public*/ bool DccSignalHead::useAddressOffSet() {
    return _useAddressOffSet;
}


/*public*/ int DccSignalHead::getOutputForAppearance(int appearance) {
    int app = (appearance);
    if (!appearanceToOutput.contains(app)) {
        log->error("Trying to get appearance " + QString::number(appearance) + " but it has not been configured");
        return -1;
    }
    return appearanceToOutput.value(app);
}

/*public*/ void DccSignalHead::setOutputForAppearance(int appearance, int number) {
    int app = (appearance);
    if (appearanceToOutput.contains(app)) {
        log->debug("Appearance " + QString::number(appearance) + " is already defined as " + QString::number(appearanceToOutput.value(app)));
        appearanceToOutput.remove(app);
    }
    appearanceToOutput.insert(app, number);
}

/*public*/ /*static*/ int DccSignalHead::getDefaultNumberForApperance(int i) {
    switch (i) {
        case SignalHead::DARK:
            return 8;
        case SignalHead::RED:
            return 0;
        case SignalHead::YELLOW:
            return 1;
        case SignalHead::GREEN:
            return 2;
        case SignalHead::LUNAR:
            return 3;
        case SignalHead::FLASHRED:
            return 4;
        case SignalHead::FLASHYELLOW:
            return 5;
        case SignalHead::FLASHGREEN:
            return 6;
        case SignalHead::FLASHLUNAR:
            return 7;
        default:
            return 8;
    }
}


//@Override
bool DccSignalHead::isTurnoutUsed(Turnout* /*t*/) {
    return false;
}
