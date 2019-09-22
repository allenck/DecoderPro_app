#include "distributor.h"
#include "loggerfactory.h"

Distributor::Distributor(QObject *parent) : QObject(parent)
{

}
/**
 * Distributes Readings and the Measurements calculated from them.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2006, 2008
 *
  */
// /*public*/ class Distributor {
#if 0
/**
 * Request being informed when a new Reading is available.
 */
/*public*/ void addReadingListener(ReadingListener l) {
    // add only if not already registered
    if (!readingListeners.contains(l)) {
        readingListeners.addElement(l);
    }
}

/**
 * Request to no longer be informed when new Readings arrive.
 */
/*public*/ void removeReadingListener(ReadingListener l) {
    if (readingListeners.contains(l)) {
        readingListeners.removeElement(l);
    }
}
#endif
/**
 * Invoked when a new Reading is created
 */
//@SuppressWarnings("unchecked")
/*public*/ void Distributor::submitReading(Reading* s) {
    // make a copy of the listener vector to synchronized not needed for transmit
//    Vector<ReadingListener> v;
//    synchronized (this) {
//        v = (Vector<ReadingListener>) readingListeners.clone();
//    }
//    if (log->isDebugEnabled()) {
//        log->debug("notify " + QString::number(v.size())
//                + " ReadingListeners about item ");
//    }
    // forward to all listeners
//    int cnt = v.size();
//    for (int i = 0; i < cnt; i++) {
//        ReadingListener client = v.elementAt(i);
//        javax.swing.SwingUtilities.invokeLater(new ForwardReading(s, client));
//    }
    emit newReading(s);
}

/**
 * Request being informed when a new Measurement is available.
 */
/*public*/ void Distributor::addMeasurementListener(MeasurementListener* l) {
    // add only if not already registered
//    if (!measurementListeners.contains(l)) {
//        measurementListeners.addElement(l);
//    }
 // TODO:
}

/**
 * Request to no longer be informed when new Measurements arrive.
 */
/*public*/ void Distributor::removeMeasurementListener(MeasurementListener* l) {
//    if (measurementListeners.contains(l)) {
//        measurementListeners.removeElement(l);
//    }
}

/**
 * Invoked when a new Measurement is created
 */
//@SuppressWarnings("unchecked")
/*public*/ void Distributor::submitMeasurement(Measurement* s) {
    // make a copy of the listener vector to synchronized not needed for transmit
//    Vector<MeasurementListener> v;
//    synchronized (this) {
//        v = (Vector<MeasurementListener>) measurementListeners.clone();
//    }
//    if (log->isDebugEnabled()) {
//        log->debug("notify " + QString::number(v.size())
//                + " MeasurementListeners about item ");
//    }
    // forward to all listeners
//    int cnt = v.size();
//    for (int i = 0; i < cnt; i++) {
//        MeasurementListener client = v.elementAt(i);
//        javax.swing.SwingUtilities.invokeLater(new ForwardMeasurement(s, client));
//    }
    emit newMeasurement(s);
}

/*static*/ /*volatile*/ /*private*/ Distributor* Distributor::_instance = NULL;

/*public*/ /*static*/ Distributor* Distributor::instance() {
    if (_instance == NULL) {
        _instance = new Distributor();
    }
    return _instance;
}
#if 0
////////////////////////////
// Implementation details //
////////////////////////////
final private Vector<ReadingListener> readingListeners = new Vector<ReadingListener>();
final private Vector<MeasurementListener> measurementListeners = new Vector<MeasurementListener>();
#endif
/*private*/ /*final*/ /*static*/ Logger* Distributor::log = LoggerFactory::getLogger("Distributor");

#if 0
/**
 * Forward the Reading from the Swing thread
 */
static class ForwardReading implements Runnable {

    Reading s;
    ReadingListener client;

    ForwardReading(Reading s, ReadingListener client) {
        this.s = s;
        this.client = client;
    }

    @Override
    /*public*/ void run() {
        client.notify(s);
    }
}

/**
 * Forward the Measurement from the Swing thread
 */
static class ForwardMeasurement implements Runnable {

    Measurement s;
    MeasurementListener client;

    ForwardMeasurement(Measurement s, MeasurementListener client) {
        this.s = s;
        this.client = client;
    }

    @Override
    /*public*/ void run() {
        client.notify(s);
    }
}
#endif
