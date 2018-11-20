#include "lncpsignalmast.h"
#include "nmrapacket.h"
#include "commandstation.h"
#include "loggerfactory.h"
#include "slotmanager.h"
#include "instancemanager.h"

/**
 * Extend jmri.SignalMast for signals implemented by an LNCP
 * <p>
 * This implementation writes out to the physical signal when it's commanded to
 * change appearance, and updates its internal state when it hears commands from
 * other places.
 * <p>
 * This is a specific implementation for the RR-cirkits LNCP interface board A
 * more general implementation, which can work with any system(s), is available
 * in {@link jmri.implementation.DccSignalMast}.
 *
 * @author Kevin Dickerson Copyright (C) 2002
 */
// /*public*/ class LNCPSignalMast extends DccSignalMast implements LocoNetListener {

    /*public*/ LNCPSignalMast::LNCPSignalMast(QString sys, QString user, QObject* parent) : DccSignalMast(sys, user, "F$lncpsm", parent){
        //super(sys, user, "F$lncpsm"); // NOI18N
        packetRepeatCount = 1;
        configureFromName(sys);
        init();
    }

    /*public*/ LNCPSignalMast::LNCPSignalMast(QString sys, QObject* parent) : DccSignalMast(sys, nullptr, "F$lncpsm", parent){
        //super(sys, nullptr, "F$lncpsm"); // NOI18N
        packetRepeatCount = 1;
        configureFromName(sys);
        init();
    }

    void LNCPSignalMast::init() {

        if ((qobject_cast<SlotManager*>(c)) && (((SlotManager*) c)->getSystemConnectionMemo() != nullptr)) {
            tc = ((SlotManager*) c)->getSystemConnectionMemo()->getLnTrafficController();
        } else {
            tc = static_cast<LnTrafficController*>(InstanceManager::getDefault("LnTrafficController"));
        }

        //We cheat, and store the two bytes that make up an NMRA packet for later use in decoding a message from the LocoNet
        int lowAddr = ((dccSignalDecoderAddress - 1) & 0x03);  // Output Pair Address
        int boardAddr = ((dccSignalDecoderAddress - 1) >> 2); // Board Address
        int midAddr = boardAddr & 0x3F;

        int highAddr = ((~boardAddr) >> 6) & 0x07;

        dccByteAddr1 = ((char) (0x80 | midAddr));
        dccByteAddr2 = ((char) (0x01 | (highAddr << 4) | (lowAddr << 1)));
        tc->addLocoNetListener(~0, (LocoNetListener*)this);
    }

#if 0
    // implementing classes will typically have a function/listener to get
    // updates from the layout, which will then call
    //  /*public*/ void firePropertyChange(String propertyName,
    //      Object oldValue,
    //      Object newValue)
    // _once_ if anything has changed state (or set the commanded state directly)
    @Override
    /*public*/ void message(LocoNetMessage l) {
        if (l.getOpCode() != LnConstants.OPC_IMM_PACKET) {
            return;
        }

        int val7f = l.getElement(2); /* fixed value of 0x7f */

        if (val7f != 0x7f) {
            return;
        }

        int reps = l.getElement(3);
        int len = ((reps & 0x70) >> 4);
        if (len != 3) {
            return;
        }
        int dhi = l.getElement(4);
        int im1 = l.getElement(5);
        int im2 = l.getElement(6);
        int im3 = l.getElement(7);

        byte[] packet = new byte[len];
        packet[0] = (byte) (im1 + ((dhi & 0x01) != 0 ? 0x80 : 0));
        packet[1] = (byte) (im2 + ((dhi & 0x02) != 0 ? 0x80 : 0));

        if (myAddress(packet[0], packet[1])) {
            packet[2] = (byte) (im3 + ((dhi & 0x04) != 0 ? 0x80 : 0));
            int aspect = packet[2];
            for (String appearance : appearanceToOutput.keySet()) {
                if (appearanceToOutput.get(appearance) == aspect) {
                    setKnownState(appearance);
                    return;
                }
            }
            log.error("Aspect for id " + aspect + "on signal mast " + this.getDisplayName() + " not found");
        }

    }
#endif
    //@Override
    /*public*/ void LNCPSignalMast::setAspect(QString aspect) {
        if (appearanceToOutput.contains(aspect) && appearanceToOutput.value(aspect) != -1) {
            c->sendPacket(NmraPacket::altAccSignalDecoderPkt(dccSignalDecoderAddress, appearanceToOutput.value(aspect)), packetRepeatCount);
        } else {
            log->warn("Trying to set aspect (" + aspect + ") that has not been configured on mast " + getDisplayName());
        }
    }

    /*public*/ void LNCPSignalMast::setKnownState(QString aspect) {
        QString oldAspect = this->aspect;
        this->aspect = aspect;
        this->speed = getSignalSystem()->getProperty(aspect, "speed").toString(); // NOI18N
        firePropertyChange("Aspect", oldAspect, aspect); // NOI18N
    }

    //@Override
    /*public*/ void LNCPSignalMast::dispose() {
        //tc.removeLocoNetListener(~0, this);
     disconnect(tc, SIGNAL());
    }


    /*private*/ bool LNCPSignalMast::myAddress(char a1, char a2) {
        if (a1 != dccByteAddr1) {
            return false;
        }
        if (a2 != dccByteAddr2) {
            return false;
        }
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* LNCPSignalMast::log = LoggerFactory::getLogger("LNCPSignalMast");


