#include "abstractprogrammer.h"
//#include "bundle.h"
#include "propertychangesupport.h"
#include "defaultprogrammermanager.h"
#include "programmingmode.h"
#include "vptr.h" // for VPtr

/*static*/ int AbstractProgrammer::SHORT_TIMEOUT=2000;
/*static*/ int AbstractProgrammer::LONG_TIMEOUT=60000;

AbstractProgrammer::AbstractProgrammer(QObject *parent) /*:
    Programmer(parent)*/
{
 this->parent = parent;
 timer = NULL;
 log = new Logger();
  propListeners= new QVector<PropertyChangeListener*>();
  propertyChangeSupport = new PropertyChangeSupport(this);
  mode = ProgrammingMode::PAGEMODE;
}
QString AbstractProgrammer::decodeErrorCode(int code)
{
 if (code == ProgListener::OK) return tr("StatusOK");
 QString sbuf ;
 // add each code; terminate each string with ";" please.
  if ((code & ProgListener::NoLocoDetected) != 0)
      sbuf.append(tr("No Loco Detected")+" ");
  if ((code & ProgListener::ProgrammerBusy) != 0)
      sbuf.append(tr("Programmer Busy")+" ");
  if ((code & ProgListener::NotImplemented) != 0)
      sbuf.append(tr("Not Implemented")+" ");
  if ((code & ProgListener::UserAborted) != 0)
      sbuf.append(tr("User Aborted")+" ");
  if ((code & ProgListener::ConfirmFailed) != 0)
      sbuf.append(tr("Confirm Failed")+" ");
  if ((code & ProgListener::FailedTimeout) != 0)
      sbuf.append(tr("Failed Timeout")+" ");
  if ((code & ProgListener::UnknownError) != 0)
      sbuf.append(tr("Unknown Error")+" ");
  if ((code & ProgListener::NoAck) != 0)
      sbuf.append(tr("No Ack")+" ");
  if ((code & ProgListener::ProgrammingShort) != 0)
      sbuf.append(tr("Programming Short")+" ");
  if ((code & ProgListener::SequenceError) != 0)
      sbuf.append(tr("Sequence Error")+" ");
  if ((code & ProgListener::CommError) != 0)
      sbuf.append(tr("Comm Error")+" ");

  // remove trailing separators
  //if (sbuf.length() > 2) sbuf.setsetLength(sbuf.length()-2);
  sbuf = sbuf.trimmed();

  QString retval = sbuf;
  if (retval == "")
   return tr("unknown status code: ")+code;
  else return retval;
 }

/*public synchronized */void AbstractProgrammer::addPropertyChangeListener(PropertyChangeListener* listener) {
//    // add only if not already registered
//    if (!propListeners->contains(l)) {
//        propListeners->append(l);
//    }
 propertyChangeSupport->addPropertyChangeListener(listener);
}

/*public synchronized*/ void AbstractProgrammer::removePropertyChangeListener(PropertyChangeListener* listener) {
//    if (propListeners->contains(l)) {
//        propListeners->remove(propListeners->indexOf(l));
//    }
 propertyChangeSupport->removePropertyChangeListener(listener);
}
/*protected*/ void AbstractProgrammer::notifyPropertyChange(QString key, QVariant oldValue, QVariant value)
{
 propertyChangeSupport->firePropertyChange(key, oldValue, value);
 //emit propertyChange(new PropertyChangeEvent(this, key, oldValue, value));
}

///*public*/ void AbstractProgrammer::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
//{
// Programmer::writeCV(CV.toInt(), val, p);
//}
///*public*/ void AbstractProgrammer::readCV(QString CV, ProgListener* p) throw (ProgrammerException)
//{
// readCV(CV, p);
//}
///*public*/ void AbstractProgrammer::confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
//{
// Programmer::confirmCV(CV.toInt(), val, p);
//}

/**
 * Basic implementation.
 * Override this to turn reading on and off globally.
 */
/*public*/ bool AbstractProgrammer::getCanRead() { return true; }

/**
 * Checks using the current default programming mode
 */
/*public*/ bool AbstractProgrammer::getCanRead(QString addr) {
    if (!getCanRead()) return false; // check basic implementation first
    return addr.toInt()<=1024;
}


//@Override
/*public*/ /*final*/ void AbstractProgrammer::setMode(ProgrammingMode* m) {
 QList<QString> validModes = getSupportedModes();

 if (m == nullptr) {
     if (validModes.size()>0) {
         // null can only be set if there are no valid modes
      log->error("Cannot set null mode when modes are present");
         throw  IllegalArgumentException("Cannot set null mode when modes are present");
     } else {
         mode = nullptr;
     }
 }

 if (validModes.contains(m->getStandardName())) {
     ProgrammingMode* oldMode = mode;
     mode = m;
     notifyPropertyChange("Mode", VPtr<ProgrammingMode>::asQVariant(oldMode), VPtr<ProgrammingMode>::asQVariant(m));
 } else {
  log->error("Invalid requested mode: " + m->getStandardName());
     throw  IllegalArgumentException("Invalid requested mode: " + m->getStandardName());
 }
}

/*public*/ /*final*/ ProgrammingMode* AbstractProgrammer::getMode() { return mode; }

//@Override
/*abstract*/ /*public*/ QList<QString> AbstractProgrammer::getSupportedModes()
{ return QList<QString>();}

/**
 * Basic implementation.
 * Override this to turn writing on and off globally.
 */
/*public*/ bool AbstractProgrammer::getCanWrite()  { return true; }
/**
 * Checks using the current default programming mode.
 */
/*public*/ bool AbstractProgrammer::getCanWrite(QString addr) { return getCanWrite();  }

/**
 * Internal routine to start timer to protect the mode-change.
 */
/*protected*/ void AbstractProgrammer::startShortTimer() {
    restartTimer(SHORT_TIMEOUT);
}

/**
 * Internal routine to restart timer with a long delay
 */
/*protected*/ void AbstractProgrammer::startLongTimer() {
    restartTimer(LONG_TIMEOUT);
}

/**
 * Internal routine to stop timer, as all is well
 */
/*protected*/ /*synchronized*/ void AbstractProgrammer::stopTimer() {
    if (timer!=NULL) timer->stop();
}

/**
 * Internal routine to handle timer starts & restarts
 */
/*protected*/ /*synchronized*/ void AbstractProgrammer::restartTimer(int delay) {
 if (log->isDebugEnabled()) log->debug("restart timer with delay "+QString::number(delay));
 if (timer==NULL)
 {
//  timer = new javax.swing.Timer(delay, new java.awt.event.ActionListener() {
//                public void actionPerformed(java.awt.event.ActionEvent e) {
//                    timeout();
//                }
//            });
//    }
  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
 }
 timer->stop();
 timer->setInterval(delay);
 timer->setSingleShot(true);
 timer->start();
}

/**
 * Find the register number that corresponds to a specific
 * CV number.
 * @throws ProgrammerException if the requested CV does not correspond
 *          to a register
 * @param cv CV number (1 through 512) for which equivalent register is desired
 * @return register number corresponding to cv
 */
 int AbstractProgrammer::registerFromCV(int cv) // throws ProgrammerException
 {
    if (cv<=4) return cv;
    switch (cv) {
    case 29:
        return 5;
    case 7:
        return 7;
    case 8:
        return 8;
    }
    throw new ProgrammerException("error");
 }

 void AbstractProgrammer::timeout()
 {
  // TODO:
  log->warn("timeout not handled");
 }

    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractProgrammer.class.getName());
