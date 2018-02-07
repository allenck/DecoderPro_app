#include "engine.h"
#include "distributor.h"
#include "transmitter.h"
#include "receiver.h"
#include "calculator.h"

namespace RPS
{
/**
 * Engine does basic computations of RPS system.
 * <p>
 * Holds all the alignment info. Receivers are indexed by their RPS receiver
 * number in all cases.
 * <p>
 * Gets a reading from the Distributor and passes back a Measurement
 * <p>
 * Bound properties:
 * <ul>
 * <li>vSound - velocity of sound, in whatever units are in use
 * </ul>
 * <p>
 * This class maintains a collection of "Transmitter" objects representing the
 * RPS-equipped rolling stock (usually engines) on the layout. This is an
 * extension to the common Roster, and every entry in this class's collection
 * must be present in the Roster.
 *
 * @author	Bob Jacobsen Copyright (C) 2006, 2008
 */
// /*public*/ class Engine implements ReadingListener {

/*public*/ Engine::Engine(QObject *parent) {
 algorithm = "Ash 2.1";  // default value, configured separately
 vsound = 0.013544;  // 0.013544 inches/usec, .000345 m/usec,
 offset = 0;
}

void Engine::loadValues() {
    // load dummy contents
#if 0
    setInitialAlignment();
    loadInitialTransmitters();
#endif
}

/*public*/ void Engine::dispose() {
}

/*public*/ void Engine::setVSound(double v) {
    double oldVal = vsound;
    vsound = v;
    log->info("change vsound from " + QString::number(oldVal) + " to " + QString::number(v));
    //prop.firePropertyChange("vSound", double(oldVal), double(v));
    emit propertyChange(new PropertyChangeEvent(this, "vSound", double(oldVal), double(v)));
}

/*public*/ double Engine::getVSound() {
    return vsound;
}

/*public*/ void Engine::setOffset(int offset) {
    this->offset = offset;
}

/*public*/ int Engine::getOffset() {
    return offset;
}

/**
 * Set the maximum receiver number expected. If the highest value in the
 * hardware is 5, that's what's needed here.
 *
 */
/*public*/ void Engine::setMaxReceiverNumber(int n) {
    log->debug("setReceiverCount to " + QString::number(n));
    if ((receivers != NULL) && (n == receivers->length() + 1)) {
        return;
    }
    QVector<Receiver*>* oldReceivers = receivers;
    receivers = new QVector<Receiver*>(n + 1);  // n is highest address, so need n+1
    if (oldReceivers == NULL) {
        return;
    }
    // clear new array
    for (int i = 0; i < receivers->length(); i++) {
        receivers->replace(i,  NULL);
    }
    // copy the existing receivers
    for (int i = 0; i < qMin(n + 1, oldReceivers->length()); i++) {
        receivers->replace(i, oldReceivers->at(i));
    }
}

/*public*/ int Engine::getMaxReceiverNumber() {
    if (receivers == NULL) {
        return 0;
    }
    return receivers->length() - 1;
}
#if 0
/**
 * Get a particular reciever by address (starting at 1)
 */
/*public*/ void setReceiver(int address, Receiver receiver) {
    if (receivers == NULL) {
        throw new IllegalArgumentException("Must initialize first");
    }
    if (address >= receivers.length) {
        throw new IllegalArgumentException("Index " + address + " is larger than expected " + receivers.length);
    }
    log->debug("store receiver " + address + " in " + this);
    receivers[address] = receiver;
}

/*public*/ Receiver getReceiver(int i) {
    return receivers->at(i);
}

/*public*/ void setReceiverPosition(int i, Point3d p) {
    receivers->at(i).setPosition(p);
}
#endif
/*public*/ QVector3D Engine::getReceiverPosition(int i) {
    if (receivers->at(i) == NULL) {
        log->debug("getReceiverPosition of NULL receiver index i=" + QString::number(i));
        return QVector3D();
    }
    return receivers->at(i)->getPosition();
}
#if 0
/*public*/ void setAlgorithm(String algorithm) {
    this->algorithm = algorithm;
}

/*public*/ String getAlgorithm() {
    return algorithm;
}
#endif
//@Override
/*public*/ void Engine::notify(Reading* r) {
    // This implementation creates a new Calculator
    // each time to ensure that the most recent
    // receiver positions are used; this should be
    // replaced with some notification system
    // to reduce the work done.

    // ok to send next poll
    log->debug("po false " + r->getID());
    pollOutstanding = false;

    // make a list of receiver positions to provide
    // to the new Calculator.  Missing/unconfigured receivers
    // are NULL.

    QVector<QVector3D>* list = new QVector<QVector3D>(receivers->length());
    for (int i = 0; i < receivers->length(); i++) {

        if (receivers->at(i) == NULL) {
            list->replace(i, QVector3D());
            continue;  // skip receivers not present
        }

        QVector3D p = getReceiverPosition(i);
        if (p != QVector3D()) {
            receivers->at(i)->setLastTime((int) r->getValue(i));  // recievers numbered from 1
            log->debug("    " + QString::number(i) + "th value min " + receivers->at(i)->getMinTime() + " < time "
                    + r->getValue(i) + " < max "
                    + receivers->at(i)->getMaxTime() + " at " + QString::number(p.x())+ "," + QString::number(p.y())+","+QString::number(p.z() ));
            if (receivers->at(i)->isActive() && (receivers->at(i)->getMinTime() <= r->getValue(i))
                    && (r->getValue(i) <= receivers->at(i)->getMaxTime())) {
                list->replace(i, p);
            } else {
                list->replace(i, QVector3D());
            }
        } else {
            list->replace(i, QVector3D());
            log->error("Unexpected NULL position from receiver " + QString::number(i));
        }
    }
#if 0
    Calculator* c = Algorithms.newCalculator(list, getVSound(),
            getOffset(), getAlgorithm());

    Measurement* m = c->convert(r, lastPoint);

    saveLastMeasurement(r->getID(), m);

    lastPoint = m;
    Distributor::instance()->submitMeasurement(m);
#endif
}

// Store the lastMeasurement
void Engine::saveLastMeasurement(QString id, Measurement* m) {
    for (int i = 0; i < getNumTransmitters(); i++) {
        if (getTransmitter(i)->getID() == (id) && getTransmitter(i)->isPolled())
        {
            getTransmitter(i)->setLastMeasurement(m);
            // might be more than one, so don't end here
        }
    }
}
#if 0
// Store alignment info
/*public*/ void storeAlignment(File file) throws IOException {
    PositionFile pf = new PositionFile();
    pf.prepare();
    pf.setConstants(getVSound(), getOffset(), getAlgorithm());

    for (int i = 1; i <= getMaxReceiverNumber(); i++) {
        if (getReceiver(i) == NULL) {
            continue;
        }
        pf.setReceiver(i, getReceiver(i));
    }
    pf.store(file);
}

/*public*/ void loadAlignment(File file) throws org.jdom2.JDOMException, IOException {
    // start by getting the file
    PositionFile pf = new PositionFile();
    pf.loadFile(file);

    // get VSound
    setVSound(pf.getVSound());

    // get offset
    setOffset(pf.getOffset());

    // get algorithm
    setAlgorithm(pf.getAlgorithm());

    // get receivers
    setMaxReceiverNumber(pf.maxReceiver());  // count from 1
    Point3d p;
    bool a;
    int min;
    int max;
    for (int i = 1; i <= getMaxReceiverNumber(); i++) {
        p = pf.getReceiverPosition(i);
        if (p == NULL) {
            continue;
        }

        a = pf.getReceiverActive(i);
        min = pf.getReceiverMin(i);
        max = pf.getReceiverMax(i);

        log->debug("load " + i + " with " + p);
        Receiver r = new Receiver(p);
        r.setActive(a);
        r.setMinTime(min);
        r.setMaxTime(max);
        setReceiver(i, r);
    }

}

protected void setInitialAlignment() {
    File defaultFile = new File(PositionFile.defaultFilename());
    try {
        loadAlignment(defaultFile);
    } catch (Exception e) {
        log->debug("load exception" + e);
        // load dummy values
        setDefaultAlignment();
    }
}

protected void setDefaultAlignment() {
    setMaxReceiverNumber(2);
    setReceiver(1, new Receiver(new Point3d(0.0, 0.0, 72.0)));
    setReceiver(2, new Receiver(new Point3d(72.0, 0.0, 72.0)));
}

//**************************************
// Methods to handle polling
//**************************************
/*public*/ void setPollingInterval(int pollingInterval) {
    this->pollingInterval = pollingInterval;
}
int pollingInterval = 500;

/*public*/ int getPollingInterval() {
    return pollingInterval;
}

bool polling = false;

/*public*/ void setPolling(bool polling) {
    this->polling = polling;
    if (polling) {
        startpoll();
    } else {
        stoppoll();
    }
}

/*public*/ bool getPolling() {
    return polling;
}


void loadInitialTransmitters() {
    transmitters = new java.util.ArrayList<Transmitter>();
    // load transmitters from the JMRI roster
    java.util.List<RosterEntry> l = Roster.getDefault().matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    log->debug("Got " + l.size() + " roster entries");
    for (int i = 0; i < l.size(); i++) {
        RosterEntry r = NULL;
        try {
            r = l.get(i);
            int address = Integer.parseInt(r.getDccAddress());
            Transmitter t = new Transmitter(r.getId(), false, address, r.isLongAddress());
            t.setRosterName(r.getId());
            transmitters.add(t);
        } catch (Exception e) {
            // just skip this entry
            if (r != NULL) {
                log->warn("Skip roster entry: " + r.getId());
            } else {
                log->warn("Failed roster entry skipped");
            }
        }
    }

    // load the polling status, custom IDs, etc, from file if possible
    try {
        loadPollConfig(new File(PollingFile.defaultFilename()));
    } catch (Exception e) {
        e.printStackTrace();
    }
}

// Store polling info
/*public*/ void storePollConfig(File file) throws IOException {
    PollingFile pf = new PollingFile();
    pf.prepare();
    pf.setPoll();

    for (int i = 0; i < getNumTransmitters(); i++) {
        pf.setTransmitter(i);
    }
    pf.store(file);
}

/*public*/ void loadPollConfig(File file) throws org.jdom2.JDOMException, IOException {
    if (file.exists()) {
        PollingFile pf = new PollingFile();
        pf.loadFile(file);
        // first make sure transmitters defined
        pf.getTransmitters(this);
        // and possibly start polling
        pf.getPollValues();
    }
}

/*public*/ Transmitter getTransmitterByAddress(int addr) {
    if (addr < 0) {
        return NULL;
    }
    if (transmitters == NULL) {
        return NULL;
    }
    for (int i = 0; i < getNumTransmitters(); i++) {
        if (getTransmitter(i).getAddress() == addr) {
            return getTransmitter(i);
        }
    }
    return NULL;
}
#endif
/*public*/ Transmitter* Engine::getTransmitter(int i) {
    if (i < 0) {
        return NULL;
    }
    if (transmitters == NULL) {
        return NULL;
    }
    return transmitters->value(i);
}

/*public*/ int Engine::getNumTransmitters() {
    if (transmitters == NULL) {
        return 0;
    }
    return transmitters->size();
}
#if 0
/*public*/ String getPolledID() {
    Transmitter t = getTransmitter(pollIndex);
    if (t == NULL) {
        return "";
    }
    return t.getID();
}

/*public*/ int getPolledAddress() {
    Transmitter t = getTransmitter(pollIndex);
    if (t == NULL) {
        return -1;
    }
    return t.getAddress();
}

/**
 * The real core of the polling, this selects the next one to poll. -1 means
 * none selected, try again later.
 */
int selectNextPoll() {
    int startindex = pollIndex;
    while (++pollIndex < getNumTransmitters()) {
        if (getTransmitter(pollIndex).isPolled()) {
            return pollIndex;
        }
    }
    // here, we got to the end without finding somebody to poll
    // try the start
    pollIndex = -1; // will autoincrement to 0
    while (++pollIndex <= startindex) {
        if (getTransmitter(pollIndex).isPolled()) {
            return pollIndex;
        }
    }
    // no luck, say so
    return -1;
}

int pollIndex = -1; // left at last one done
bool bscPoll = false;
bool throttlePoll = false;

/*public*/ void setBscPollMode() {
    bscPoll = true;
    throttlePoll = false;
}

/*public*/ void setDirectPollMode() {
    bscPoll = false;
    throttlePoll = false;
}

/*public*/ void setThrottlePollMode() {
    bscPoll = false;
    throttlePoll = true;
}

/*public*/ bool getBscPollMode() {
    return bscPoll;
}

/*public*/ bool getThrottlePollMode() {
    return throttlePoll;
}

/*public*/ bool getDirectPollMode() {
    return !(bscPoll || throttlePoll);
}

void startpoll() {
    // time to start operation
    pollThread = new Thread() {
        @Override
        /*public*/ void run() {
            log->debug("Polling starts");
            while (true) {
                try {
                    int i = selectNextPoll();
                    log->debug("Poll " + i);
                    setOn(i);
                    log->debug("po true " + i);
                    pollOutstanding = true;
                    synchronized (this) {
                        wait(20);
                    }
                    setOff(i);
                    log->debug("start wait");
                    waitBeforeNextPoll(pollingInterval);
                    log->debug("end wait");
                } catch (InterruptedException e) {
                    // cancel whatever is happening
                    log->debug("Polling stops");
                    Thread.currentThread().interrupt(); // retain if needed later
                    return; // end operation
                }
            }
        }
    };
    pollThread.start();
}


/**
 * Wait before sending next poll.
 * <P>
 * Waits specified time, and then checks to see if response has been
 * returned. If not, it waits again (twice) by 1/2 the interval, then
 * finally polls anyway.
 */
void waitBeforeNextPoll(int pollingInterval) throws InterruptedException {
    synchronized (this) {
        wait(pollingInterval);
    }
    if (!pollOutstanding) {
        return;
    }
    log->debug("--- extra wait");
    for (int i = 0; i < 20; i++) {
        synchronized (this) {
            wait(pollingInterval / 4);
        }
        log->debug("-------------extra wait");
        if (!pollOutstanding) {
            return;
        }
    }
}

void stoppoll() {
    if (pollThread != NULL) {
        pollThread.interrupt();
    }
}

void setOn(int i) {
    Transmitter t = getTransmitter(i);
    byte[] packet;
    if (bscPoll) {
        // poll using BSC instruction
        packet = jmri.NmraPacket.threeBytePacket(
                t.getAddress(), t.isLongAddress(),
                (byte) 0xC0, (byte) 0xA5, (byte) 0xFE);
        if (jmri.InstanceManager.getNullableDefault(CommandStation.class) != NULL) {
            jmri.InstanceManager.getDefault(CommandStation.class).sendPacket(packet, 1);
        }
    } else {
        // poll using F2
        if (throttlePoll) {
            // use throttle; first, get throttle
            if (t.checkInit()) {
                // now send F2
                t.getThrottle().setF2(true);
            } else {
                return;  // bail if not ready
            }
        } else {
            // send packet direct
            packet = jmri.NmraPacket.function0Through4Packet(
                    t.getAddress(), t.isLongAddress(),
                    false, false, true, false, false);
            if (jmri.InstanceManager.getNullableDefault(CommandStation.class) != NULL) {
                jmri.InstanceManager.getDefault(CommandStation.class).sendPacket(packet, 1);
            }
        }
    }
}

void setOff(int i) {
    if (!bscPoll) {
        // have to turn off F2 since not using BSC
        Transmitter t = get/*public*/(i);
        if (throttlePoll) {
            // use throttle; first, get throttle
            if (t.checkInit()) {
                // now send F2
                t.getThrottle().setF2(false);
            } else {
                return;  // bail if not ready
            }
        } else {
            // send direct
            byte[] packet = jmri.NmraPacket.function0Through4Packet(
                    t.getAddress(), t.isLongAddress(),
                    false, false, false, false, false);
            if (jmri.InstanceManager.getNullableDefault(CommandStation.class) != NULL) {
                jmri.InstanceManager.getDefault(CommandStation.class).sendPacket(packet, 1);
            }
        }
    }
}
#endif
// for now, we only allow one Engine
//@SuppressFBWarnings(value = "MS_PKGPROTECT") // for tests
/*static*/ /*volatile*/ /*protected*/ Engine* Engine::_instance = NULL;

//@SuppressFBWarnings(value = "LI_LAZY_INIT_UPDATE_STATIC") // see comment in method
/*static*/ /*public*/ Engine* Engine::instance() {
    if (_instance == NULL) {
        // NOTE: _instance has to be initialized before loadValues()
        // is called, because it invokes instance() indirectly.
        _instance = new Engine();
        _instance->loadValues();
    }
    return _instance;
}
#if 0
// handle outgoing parameter notification
java.beans.PropertyChangeSupport prop = new java.beans.PropertyChangeSupport(this);

/*public*/ void removePropertyChangeListener(java.beans.PropertyChangeListener p) {
    prop.removePropertyChangeListener(p);
}

/*public*/ void addPropertyChangeListener(java.beans.PropertyChangeListener p) {
    prop.addPropertyChangeListener(p);
}
#endif
/*private*/ /*final*/ /*static*/ Logger* Engine::log = LoggerFactory::getLogger("Engine");
//}

} //end namespace RPS
