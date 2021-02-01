#include "progdebugger.h"
#include "defaultprogrammermanager.h"
#include "propertychangesupport.h"
#include <QTimer>
#include "programmingmode.h"
#include "rosterentry.h"
#include "abstractprogrammerfacade.h"

//ProgDebugger::ProgDebugger(QObject *parent) :
//    AddressedProgrammer(parent)
//{
//}
/**
 * Debugging implementation of Programmer interface.
 *<P>
 * Remembers writes, and returns the last written value
 * when a read to the same CV is made.
 *<p>
 * Only supports the DCC single-number address space.
 *
 * @author			Bob Jacobsen Copyright (C) 2001, 2007, 2013
 * @version         $Revision: 28274 $
 */
//*public*/ class ProgDebugger implements AddressedProgrammer  {

/*public*/ ProgDebugger::ProgDebugger(QObject *parent) :
    QObject(parent) {
    common();
    mode = ProgrammingMode::PAGEMODE;
}

/*public*/ ProgDebugger::ProgDebugger(bool pLongAddress, int pAddress, QObject *parent) :
    QObject(parent)
{
    common();
    longAddr = pLongAddress;
    address = pAddress;
    mode = ProgrammingMode::OPSBITMODE;
}
void ProgDebugger::common()
{
 // write CV is recorded for later use
 _lastWriteVal = -1;
 _lastWriteCv = -1;
  nOperations = 0;
  _nextRead = 123;
  longAddr = true;
  address = -1;
  mValues = QHash<int,int>();
  log = new Logger("ProgDebugger");
  _lastReadCv = -1;
  /**
   * By default, the highest test CV is 256 so that
   * we can test composite operations
   */
  writeLimit = 256;
  readLimit = 256;
  propertyChangeSupport = new PropertyChangeSupport(this);
}

/*public*/ int ProgDebugger::lastWrite() { return _lastWriteVal; }
/*public*/ int ProgDebugger::lastWriteCv() { return _lastWriteCv; }

/**
 * Reset the CV to a value so one
 * can detect if it's been written.
 * <p>
 * Does not change the "lastWrite" and "lastWriteCv" results.
 */
/*public*/ void ProgDebugger::resetCv(int cv, int val) {
    mValues.insert(cv, (val));
}

/**
 * Get the CV value directly, without going through
 * the usual indirect protocol. Used for e.g. testing.
 * <p>
 * Does not change the "lastRead" and "lastReadCv" results.
 */
/*public*/ int ProgDebugger::getCvVal(int cv) {
    // try to get something from hash table
    int saw = (mValues.value((cv)));
    if (saw!=0) return saw;
    log->warn("CV "+QString::number(cv)+" has no defined value");
    return -1;
}

/**
 * See if a CV has been written
 */
 /*public*/ bool ProgDebugger::hasBeenWritten(int cv) {
    int saw = (mValues.value((cv)));
    return (saw!=NULL);
 }

/**
 * Clear written status
 */
 /*public*/ void ProgDebugger::clearHasBeenWritten(int cv) {
    mValues.remove((cv));
 }

/*public*/ QString ProgDebugger::decodeErrorCode(int i) {
    log->debug("decoderErrorCode "+i);
    return "error "+i;
}

/*public*/ void ProgDebugger::writeCV(QString CVName, int val, ProgListener* p) throw (ProgrammerException) {
    int CV = CVName.toInt();
    nOperations++;
    /*final*/ ProgListener* m = p;
    // log out the request
    log->info("write CV: "+QString::number(CV)+" to: "+QString::number(val)+" mode: "+getMode()->getStandardName());
    _lastWriteVal = val;
    _lastWriteCv = CV;
    // save for later retrieval
    mValues.insert((CV), (val));

    // return a notification via the queue to ensure end
//    Runnable r = new Runnable() {
//            ProgListener* l = m;
//            /*public*/ void run() {
//                log->debug("write CV reply");
//                if (l!=NULL) l.programmingOpReply(-1, 0); }  // 0 is OK status
//        };
    PDRunnable1* r = new PDRunnable1(m);
    sendReturn(r);
}
ProgDebugger::PDRunnable1::PDRunnable1(ProgListener *l)
{
 this->l = l;
}

void ProgDebugger::PDRunnable1::run()
{
 Logger* log = new Logger("PDRunnable1");
 log->debug("write CV reply");
 if(l != nullptr)
 {
   if(qobject_cast<AbstractProgrammerFacade*>(l->self()))
    ((AbstractProgrammerFacade*)l)->programmingOpReply(-1, 0);
   else    if(qobject_cast<CvValue*>(l->self()))
    ((CvValue*)l)->programmingOpReply(-1, 0);
   else
     l->programmingOpReply(-1, 0);   // 0 is OK status
 }
}

// read CV values
// note that the hashTable will be used if the CV has been written
/*public*/ void ProgDebugger::nextRead(int r) { _nextRead = r; }

/*public*/ int ProgDebugger::lastReadCv() { return _lastReadCv; }

/*public*/ void ProgDebugger::confirmCV(QString CVName, int val, ProgListener* p) throw (ProgrammerException)
{
 int  CV = CVName.toInt();
 /*final*/ ProgListener* m = p;

    nOperations++;
    // guess by comparing current value in val to has table
    int saw = mValues.value((CV));
    int result = -1; // what was read
    if (saw!=NULL) {
        result = saw;
        confirmOK = (result==val);
        log->info("confirm CV: "+QString::number(CV)+" mode: "+getMode()->getStandardName()+" will return "+QString::number(result)+" pass: "+confirmOK);
    } else {
        result = -1;
        confirmOK = false;
        log->info("confirm CV: "+QString::number(CV)+" mode: "+getMode()->getStandardName()+" will return -1 pass: false due to no previous value");
    }
    _lastReadCv = CV;
    // return a notification via the queue to ensure end
    /*final*/ int returnResult = result;  // /*final*/ to allow passing to inner class
//    Runnable r = new Runnable() {
//            ProgListener* l = m;
//            int result = returnResult;
//            /*public*/ void run() {
//                log->debug("read CV reply");
//                if (confirmOK) l.programmingOpReply(result, ProgListener.OK);
//                else l.programmingOpReply(result, ProgListener.ConfirmFailed);
//            }
//        };
    PDRunnable2* r = new PDRunnable2(returnResult, m, this);
    sendReturn(r);
}
ProgDebugger::PDRunnable2::PDRunnable2(int returnResult, ProgListener *l, ProgDebugger* parent)
{
 this->result = returnResult;
 this->l = l;
 this->parent = parent;
}
void ProgDebugger::PDRunnable2::run()
{
Logger* log = new Logger("PDRunnable2");

 log->debug("read CV reply");
 if(l != nullptr)
 {
  if(qobject_cast<AbstractProgrammerFacade*>(l->self()))
  {
   if (parent->confirmOK)
    ((AbstractProgrammerFacade*)l)->programmingOpReply(result, ProgListener::OK);
   else ((AbstractProgrammerFacade*)l)->programmingOpReply(result, ProgListener::ConfirmFailed);

  }
  else
  {
   if (parent->confirmOK)
    l->programmingOpReply(result, ProgListener::OK);
   else l->programmingOpReply(result, ProgListener::ConfirmFailed);
  }
 }
}

/*public*/ void ProgDebugger::readCV(QString CVName, ProgListener* p) throw (ProgrammerException) {
    int CV = CVName.toInt();
    /*final*/ ProgListener* m = p;
    _lastReadCv = CV;
    nOperations++;

    int readValue = _nextRead;
    // try to get something from hash table
    int saw = mValues.value((CV));
    if (saw!=NULL) readValue = saw;

    log->info("read CV: "+QString::number(CV)+" mode: "+getMode()->getStandardName()+" will read "+QString::number(readValue));

    /*final*/ int returnValue = readValue;
    // return a notification via the queue to ensure end
//    Runnable r = new Runnable() {
//            int retval = returnValue;
//            ProgListener* l = m;
//            /*public*/ void run() {
//                // log->debug("read CV reply - start sleep");
//                // try { Thread.sleep(100); } catch (Exception e) {}
//                log->debug("read CV reply");
//                l.programmingOpReply(retval, 0); }  // 0 is OK status
//        };
    PDRunnable3* r = new PDRunnable3(returnValue, m);
    sendReturn(r);

}
ProgDebugger::PDRunnable3::PDRunnable3(int returnResult, ProgListener *l)
{
 this->retval = returnResult;
 this->l = l;
}
void ProgDebugger::PDRunnable3::run()
{
    Logger* log = new Logger("PDRunnable3");

    // log->debug("read CV reply - start sleep");
    // try { Thread.sleep(100); } catch (Exception e) {}
    log->debug("read CV reply");
    if(qobject_cast<AbstractProgrammerFacade*>(l->self()))
    {
     ((AbstractProgrammerFacade*)l)->programmingOpReply(retval, 0);
    }
    else
     if(qobject_cast<CvValue*>(l->self()))
     {
      ((CvValue*)l)->programmingOpReply(retval, 0);
     }
    else
     l->programmingOpReply(retval, 0);   // 0 is OK status
}

//@Override
/*public*/ /*final*/ void ProgDebugger::setMode(ProgrammingMode* m) {
    log->debug(QString("Setting mode from %1 to %2").arg(mode->getStandardName()).arg( m->getStandardName()));
    if (getSupportedModes().contains(m->getStandardName())) {
        ProgrammingMode* oldMode = mode;
        mode = m;
        notifyPropertyChange("Mode", VPtr<ProgrammingMode>::asQVariant(oldMode), VPtr<ProgrammingMode>::asQVariant(m));
    } else {
        throw IllegalArgumentException("Invalid requested mode: "+m->getStandardName());
    }
}
/*public*/ /*final*/ ProgrammingMode* ProgDebugger::getMode() { return mode; }
/*public*/ QList<QString> ProgDebugger::getSupportedModes() {
    if (address >= 0 ) {
//        // addressed programmer
//        return Arrays.asList(
//            new ProgrammingMode[]
//            {
//                DefaultProgrammerManager::OPSBITMODE,
//                DefaultProgrammerManager::OPSBYTEMODE
//            }
//        );
        QList<QString> l = QList<QString>() <<"OPSBITMODE" <<
                "OPSBYTEMODE";
        return l;
    } else {
        // global programmer
//        return Arrays.asList(
//            new ProgrammingMode[]
//            {
//                DefaultProgrammerManager::PAGEMODE,
//                DefaultProgrammerManager::DIRECTBITMODE,
//                DefaultProgrammerManager::DIRECTBYTEMODE
//            }
//        );
        QList<QString> l = QList<QString>() <<"PAGEMODE" <<
                "DIRECTBITMODE" << "DIRECTBYTEMODE" << "DIRECTMODE";
        return l;
    }
}

/*public*/ void ProgDebugger::setTestReadLimit(int lim) { readLimit = lim; }
/*public*/ void ProgDebugger::setTestWriteLimit(int lim) { writeLimit = lim; }

/*public*/ bool ProgDebugger::getCanRead() {
    log->debug("getCanRead() returns true");
    return true;
}
/*public*/ bool ProgDebugger::getCanRead(QString addr) {
    log->debug("getCanRead("+addr+") returns "+((addr.toInt()<=readLimit)));
    return (addr.toInt()<=readLimit);
}

/*public*/ bool ProgDebugger::getCanWrite()  {
    log->debug("getCanWrite() returns true");
    return true;
}
/*public*/ bool ProgDebugger::getCanWrite(QString addr) {
    log->debug("getCanWrite("+addr+") returns "+((addr.toInt()<=writeLimit)));
    return (addr.toInt()<=writeLimit);
}


/**
 * Add a PropertyChangeListener to the listener list.
 *
 * @param listener The PropertyChangeListener to be added
 */
/*public*/ void ProgDebugger::addPropertyChangeListener(PropertyChangeListener* listener) {
    propertyChangeSupport->addPropertyChangeListener(listener);
}

/*public*/ void ProgDebugger::removePropertyChangeListener(PropertyChangeListener* listener) {
    propertyChangeSupport->removePropertyChangeListener(listener);
}

/*protected*/ void ProgDebugger::notifyPropertyChange(QString key, QVariant oldValue, QVariant value) {
    propertyChangeSupport->firePropertyChange(key, oldValue, value);
}


/*public*/ bool ProgDebugger::getLongAddress() {return true;}

/*public*/ int ProgDebugger::getAddressNumber() { return address; }

/*public*/ QString ProgDebugger::getAddress() { return QString::number(getAddressNumber())+" "+QString::number(getLongAddress()); }

/*static*/ const bool ProgDebugger::IMMEDIATERETURN = false;
/*static*/ const int ProgDebugger::DELAY = 10;
/**
 * Arrange for the return to be invoked on the Swing thread.
 */
void ProgDebugger::sendReturn(Runnable* run) {
 this->run = run;
    if (IMMEDIATERETURN) {
//        javax.swing.SwingUtilities.invokeLater(run);
     run->run();
    }
    else
    {
     //javax.swing.Timer timer = new javax.swing.Timer(DELAY, NULL);
//        java.awt.event.ActionListener l = new java.awt.event.ActionListener(){
//            javax.swing.Timer timer;
//            Runnable run;
//            java.awt.event.ActionListener init(javax.swing.Timer t, Runnable r) {
//                this.timer = t;
//                this.run = r;
//                return this;
//            }
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                this.timer.stop();
//                javax.swing.SwingUtilities.invokeLater(run);
//            }
//        }.init(timer, run);
//        timer.addActionListener(l);
//        timer.start();
        QTimer::singleShot(DELAY, this, SLOT(On_timer()));
    }
}
void ProgDebugger::On_timer()
{
//TODO:
 run->run();

}
////    static Logger log = LoggerFactory.getLogger(ProgDebugger.class.getName());
//}
