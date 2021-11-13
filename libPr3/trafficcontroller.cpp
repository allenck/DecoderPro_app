#include "trafficcontroller.h"
#include "directsystemconnectionmemo.h"
#include "makepacket.h"
#include "abstractserialportcontroller.h"
#include "loggerfactory.h"

/**
 * Converts Stream-based I/O to/from NMRA packets and controls sending to the
 * direct interface.
 * <p>
 * This is much simpler than many other "TrafficHandler" classes, because
 *   <ul>
 *   <li>It's not handling mode information, or even any information back from the
 *   device; it's just sending.
 *   <li>It can work with the direct packets.
 *   </ul>
 * This actually bears more similarity to a pure implementation of the
 * CommandStation interface, which is where the real guts of it is. In
 * particular, note that transmission is not a threaded operation.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 */
// /*public*/ class TrafficController implements jmri.CommandStation {

    /**
     * Create a new Direct TrafficController instance.
     * @param memo system connection.
     */
    /*public*/ TrafficController::TrafficController(DirectSystemConnectionMemo* memo, QObject* parent) : QObject(parent) {
        //super();
        _memo = memo;
    }

    /**
     * Static function returning the instance to use.
     *
     * @return The registered instance for general use, if need be creating one.
     * @deprecated JMRI Since 4.4 instance() shouldn't be used, convert to JMRI
     * multi-system support structure
     */
    //@Deprecated
    /*static*/ /*public*/ TrafficController* TrafficController::instance() {
        return nullptr;
    }

    /**
     * Send a specific packet to the rails.
     *
     * @param packet  Byte array representing the packet, including the
     *                error-correction byte. Must not be null.
     * @param repeats Number of times to repeat the transmission, but is ignored
     *                in the current implementation
     */
    //@Override
    /*public*/ bool TrafficController::sendPacket(QByteArray packet, int repeats) {

        if (repeats != 1) {
            log->warn("Only single transmissions currently available");
        }

        // convert packet (in byte form) into bits
        QVector<int> msgAsInt = MakePacket::createStream(packet);

        if (msgAsInt[0] == 0) {
            // failed to make packet
//            log->error("Failed to convert packet to transmitable form: {}", java.util.Arrays.toString(packet));
            return false;
        }

        // have to recopy & reformat, as there's only a byte write in Java 1
        // note that msgAsInt has 0th byte containing length still
        QByteArray msg = QByteArray(msgAsInt[0], 0);
        for (int i = 0; i < msg.length(); i++) {
            //msg[i] = (byte) (msgAsInt[i + 1] & 0xFF);
         //msg.replace(i, 1, msgAsInt[i + 1] & 0xFF);
         msg[i]= msgAsInt[i + 1] & 0xFF;
        }

        // and stream the resulting byte array
        try {
            if (ostream != nullptr) {
                if (log->isDebugEnabled()) {
                    QString f = QString("write message: ");
                    for (int i = 0; i < msg.length(); i++) {
                        f+(QString::number(0xFF & msg[i]), 16)+(" ");
                    }
                    log->debug(f/*.toString()*/);
                }
                //ostream->write(msg);
                *ostream << msg;
            } else {
                // no stream connected
                log->warn("sendMessage: no connection established");
            }
        } catch (IOException e) {
            log->warn("sendMessage: Exception: {}", e.getMessage());
        }
        return true;
    }



    /*public*/ bool TrafficController::status() {
        return (ostream != nullptr && istream != nullptr);
    }

    /**
     * Make connection to existing PortController object.
     *
     * @param p the controller to connect to
     */
    /*public*/ void TrafficController::connectPort(AbstractSerialPortController* p) {
        istream = p->getInputStream();
        ostream = p->getOutputStream();
        if (controller != nullptr) {
            log->warn("connectPort: connect called while connected");
        } else {
            log->debug("connectPort invoked");
        }
        controller = p;
    }

    /**
     * Break connection to existing PortController object. Once broken, attempts
     * to send via "message" member will fail.
     *
     * @param p the controller to disconnect from
     */
    /*public*/ void TrafficController::disconnectPort(AbstractSerialPortController* p) {
        istream = nullptr;
        ostream = nullptr;
        if (controller != p) {
            log->warn("disconnectPort: disconnect called from non-connected AbstractPortController");
        }
        controller = nullptr;
    }



    //@Override
    /*public*/ QString TrafficController::getUserName() {
        return _memo->getUserName();
    }

    //@Override
    /*public*/ QString TrafficController::getSystemPrefix() {
        return _memo->getSystemPrefix();
    }

    /*private*/ /*final*/ /*static*/ Logger* TrafficController::log = LoggerFactory::getLogger("TrafficController");
