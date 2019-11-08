#include "trackreporter.h"
#include "collection.h"

/**
 * Extension of the AbstractReporter class that implements CollectingReporter
 * and represents the contents of a track.  This is an internal construct that
 * does not correspond to a physical reporter.
 *
 * @author Paul Bender Copyright (C) 2019
 */
// /*public*/ class TrackReporter extends AbstractReporter implements CollectingReporter {


/*public*/ TrackReporter::TrackReporter(QString systemName, QObject* parent) : AbstractReporter(systemName, parent){
//        super(systemName);
//        collection = new ArrayDeque<Object>();
 collection = new Collection();
}

/*public*/ TrackReporter::TrackReporter(QString systemName, QString userName, QObject* parent) : AbstractReporter(systemName, userName, parent) {
//    super(systemName, userName);
//    collection = new ArrayDeque<Object>();
 collection = new Collection();
}

/**
 * Provide a general method for updating the report.
 */
//@Override
/*public*/ void TrackReporter::setReport(QVariant r) {
    if (r == _currentReport) {
        return;
    }
    QVariant old = _currentReport;
    QVariant oldLast = _lastReport;
    _currentReport = r;
    if (!r.isNull()) {
        _lastReport = r;
        // notify
        firePropertyChange("lastReport", oldLast, _lastReport);
    }
    // notify
    firePropertyChange("currentReport", old, _currentReport);
}

//@Override
/*public*/ int TrackReporter::getState() {
   return state;
}

//@Override
/*public*/ void TrackReporter::setState(int s) {
   state = s;
}

//CollectingReporter Interface Method(s)
/**
 * @return the collection of elements associated with this reporter.
 */
//@Override
/*public*/ Collection* TrackReporter::getCollection(){
   return(collection);
}

// Special methods to set the report from the ends of the track
// these methods record the order of reports seen.

//@SuppressWarnings("unchecked")
/*public*/ void TrackReporter::pushEast(QVariant o){
     if(!o.isNull()) {
        collection->addFirst(o);
        setReport(o);
     }
}

//@SuppressWarnings("unchecked")
/*public*/ void TrackReporter::pushWest(QVariant o){
     if(!o.isNull()) {
        collection->addLast(o);
        setReport(o);
     }
}

/*public*/ QVariant TrackReporter::pullEast(){
   QVariant retval = collection->removeFirst();
   setReport(collection->peekFirst());
   return retval;
}

/*public*/ QVariant TrackReporter::pullWest(){
   QVariant retval = collection->removeLast();
   setReport(collection->peekLast());
   return retval;
}
