#include "cvvalue.h"
#include "programmer.h"
#include "abstractvalue.h"
#include <QTimer>
#include <QPalette>
#include "jtextfield.h"
#include "slotmanager.h"
#include "loggerfactory.h"

/**
 * Encapsulate a single CV value and provide programming access to the decoder.
 *<P>Since this is a single CV in a single decoder, the Programmer used to get
 * access is part of the state.  This allows us to specify a specific ops-mode
 * programmer aimed at a particular decoder.
 *<P>There are three relevant parameters:  Busy, Value, State.  Busy == true means
 * that a read or write operation is going on.  When it transitions to "false", the
 * operation is complete, and the Value and State are stable.  During a read
 * operation, Value changes before State, so you can assume that Value is stable
 * if notified of a State change.
 *
 * @author    Bob Jacobsen   Copyright (C) 2001, 2003, 2004
 * @author    Howard G. Penny   Copyright (C) 2005
 * @version   $Revision: 17977 $
 */
///*public*/ class CvValue extends AbstractValue implements ProgListener {

//    static final java.util.ResourceBundle rbt = jmri.jmrit.symbolicprog.SymbolicProgBundle.bundle();

/*public*/ CvValue::CvValue(QString num, Programmer* pProgrammer, QObject *parent)
 : AbstractValue(parent)
{
    _num = num;
    mProgrammer = pProgrammer;
    _tableEntry = new JTextField("0", 3);
    _defaultColor = _tableEntry->getBackground();
    _tableEntry->setBackground(COLOR_UNKNOWN);

    log->setDebugEnabled(false);
    setObjectName("CvValue");
}

/*public*/ CvValue::CvValue(QString num, QString cvName,  Programmer* pProgrammer, QObject *parent)
 : AbstractValue(parent)
{
    _num   = num;
    _cvName  = cvName;
    if (cvName == "")
     log->error("cvName == NULL in ctor num: "+(num));
    mProgrammer = pProgrammer;
    _tableEntry = new JTextField("0", 3);
    _defaultColor = _tableEntry->getBackground();
    _tableEntry->setBackground(COLOR_UNKNOWN);

     log->setDebugEnabled(true);
    setObjectName("CvValue");
}

/*public*/ QString CvValue::toString()
{
 return "CvValue _num="+(_num)+" _cvName="+_cvName;
}

void CvValue::setProgrammer(Programmer* p) { mProgrammer = p; }
/*public*/ QString CvValue::number() { return _num; }

/*public*/ QString CvValue::cvName() { return _cvName; }

/*public*/ int CvValue::getValue()  { return _value; }

QColor CvValue::getColor()
{
 return _tableEntry->getBackground();
}

/*protected*/ void CvValue::notifyValueChange(int value)
{
 //prop->firePropertyChange("Value", NULL, (value));
 prop->firePropertyChange("Value", QVariant(), QVariant(value));
 emit propertyChange(new PropertyChangeEvent(this, "Value", QVariant(), QVariant(value)));
}

/**
 * Edit a new value into the CV. Only use this for external edits, e.g. set form a GUI,
 * not for internal uses, as it sets the state to EDITED
 */
/*public*/ void CvValue::setValue(int value)
{
 if (log->isDebugEnabled()) log->debug("CV "+(number())+" value changed from "+QString::number(_value)+" to "+QString::number(value));
 setState(EDITED);
 if (_value != value)
 {
  _value = value;
  _tableEntry->setText(QString::number(value));
  notifyValueChange(value);
 }
}

void CvValue::resetStatus(int newState)
{
 if(_state == EDITED)
  setState(newState);
}

/**
 * Get the decoder value read during compare
 * @return _decoderValue
 */
/*public*/ int CvValue::getDecoderValue()  { return _decoderValue; }


/*public*/ int CvValue::getState()  { return _state; }

/**
 * Set state value and send notification.  Also sets GUI color as needed.
 */
/*public*/ void CvValue::setState(int state)
{
 if (log->isDebugEnabled()) log->debug("cv "+(number())+" set state from "+QString::number(_state)+" to "+QString::number(state));
 int oldstate = _state;
 _state = state;
 switch (state)
 {
 case UNKNOWN : setColor(COLOR_UNKNOWN ); break;
 case EDITED  : setColor(COLOR_EDITED ); break;
 case READ    : setColor(COLOR_READ    ); break;
 case STORED  : setColor(COLOR_STORED  ); break;
 case FROMFILE: setColor(COLOR_FROMFILE); break;
 case SAME: setColor(COLOR_SAME); break;
 case DIFF: setColor(COLOR_DIFF); break;
 default:      log->error("Inconsistent state: "+QString::number(_state));
 }
 if (oldstate != state)
 {
  prop->firePropertyChange("State", QVariant(oldstate), QVariant(state));
  emit propertyChange(new PropertyChangeEvent(this, "State", QVariant(oldstate), QVariant(state)));
 }
}
QString CvValue::getStateColor()
{
 QString s="COLOR_UNKNOWN";
 QColor c = COLOR_UNKNOWN;
 switch (_state)
 {
  case UNKNOWN : s="COLOR_UNKNOWN"; break;
  case EDITED  : s="COLOR_EDITED"; c = COLOR_EDITED; break;
  case READ    : s="COLOR_READ"; c = COLOR_READ; break;
  case STORED  : s="COLOR_STORED"; c= COLOR_STORED; break;
  case FROMFILE: s="COLOR_FROMFILE"; c= COLOR_FROMFILE; break;
  case SAME: s="COLOR_SAME"; c = COLOR_SAME; break;
  case DIFF: s="COLOR_DIFF"; c = COLOR_DIFF; break;
  default:      log->error("Inconsistent state: "+QString::number(_state));
 }

 return s+QString(" r(%1), g(%2), b(%3)").arg(c.red()).arg(c.green()).arg(c.blue());
}

// read, write operations
/*public*/ bool CvValue::isBusy() { return _busy; }

/**
 * set the busy state and send notification. Should be used _only_ if
 * this is the only thing changing
 */
/*private*/ void CvValue::setBusy(bool busy)
{
 if (log->isDebugEnabled()) log->debug(QString("setBusy from ")+(_busy?"true":"false")+" to "+(busy?"true":"false")+" state "+QString::number(_state));
 bool oldBusy = _busy;
 _busy = busy;
 notifyBusyChange(oldBusy, busy);
}

/**
 * Notify of changes to the busy state
 */
/*private*/ void CvValue::notifyBusyChange(bool oldBusy, bool newBusy)
{
 if (log->isDebugEnabled()) log->debug(tr("notifyBusy from ")+(oldBusy?"true":"false")+" to "+(newBusy?"true":"false")+" current state "+QString::number(_state));
 if (oldBusy != newBusy)
 {
  prop->firePropertyChange("Busy", QVariant(oldBusy), QVariant(newBusy));
//                                                    oldBusy ? Boolean.TRUE : Boolean.FALSE,
//                                                    newBusy ? Boolean.TRUE : Boolean.FALSE);
  emit propertyChange(new PropertyChangeEvent(this, "Busy", QVariant(oldBusy), QVariant(newBusy)));
 }
}

// color management
void CvValue::setColor(QColor c)
{
 if (c.isValid())
  _tableEntry->setBackground(c);
 else
  _tableEntry->setBackground(_defaultColor);
    //prop.firePropertyChange("Value", NULL, NULL);
}

// object for Table entry
JTextField* CvValue::getTableEntry() {
    return _tableEntry;
}

/**
 * Set bean keeping track of whether this CV is intended to be
 * read-only.  Does not otherwise affect behaviour!
 * Default is "false".
 */
 /*public*/ void CvValue::setReadOnly(bool is) {
    _readOnly = is;
}

/**
 * Retrieve bean keeping track of whether this CV is intended to be
 * read-only.  Does not otherwise affect behaviour!
 * Default is "false".
 */
/*public*/ bool CvValue::getReadOnly() {
    return _readOnly;
}

/**
 * Set bean keeping track of whether this CV is intended to
 * be used as info-only.  Does not otherwise affect behaviour!
 * Default is "false".
 */
/*public*/ void CvValue::setInfoOnly(bool is) {
    _infoOnly = is;
}

/**
 * Retrieve bean keeping track of whether this CV is intended to
 * be used as info-only.  Does not otherwise affect behaviour!
 * Default is "false".
 */
/*public*/ bool CvValue::getInfoOnly() {
    return _infoOnly;
}

/**
 * Set bean keeping track of whether this CV is intended to
 * be used as write-only.  Does not otherwise affect behaviour!
 * Default is "false".
 */
/*public*/ void CvValue::setWriteOnly(bool is) {
    _writeOnly = is;
}

/**
 * Retrieve bean keeping track of whether this CV is intended to
 * be used as write-only.  Does not otherwise affect behaviour!
 * Default is "false".
 */
/*public*/ bool CvValue::getWriteOnly()
{
 return _writeOnly;
}

/*public*/ void CvValue::setToRead(bool state)
{
 if (getInfoOnly() || getWriteOnly())
 {
  state = false;
 }
 _toRead = state;
}
/*public*/ bool CvValue::isToRead() { return _toRead; }

/*public*/ void CvValue::setToWrite(bool state)
{
 if (getInfoOnly() || getReadOnly())
 {
  state = false;
 }
 _toWrite = state;
}

/*public*/ bool CvValue::isToWrite() { return _toWrite; }

// read, write support

/*public*/ void CvValue::read(QLabel* status)
{
 if (log->isDebugEnabled())
  log->debug("read call with Cv number "+(_num));
 setToRead(false);
 // get a programmer reference and write
 _status = status;

 if (status != NULL) status->setText(tr("Reading CV%1...").arg((_num)));

 if (mProgrammer != NULL)
 {
  setBusy(true);
  _reading = true;
  _confirm = false;
  try
  {
   mProgrammer->readCV(_num, (ProgListener*)this);
  }
  catch (Exception e)
  {
   if (status != NULL) status->setText(tr("Exception during CV read: %1").arg(e.getMessage()));

   log->warn("Exception during CV read: "+e.getMessage());
   setBusy(false);
  }
 }
 else
 {
  if (status != NULL) status->setText(tr("No programmer available!"));
  log->error("No programmer available!");
 }
}


/*public*/ void CvValue::confirm(QLabel* status) {
    if (log->isDebugEnabled()) log->debug("confirm call with Cv number "+(_num));
    // get a programmer reference and write
    _status = status;

    if (status != NULL) status->setText(tr("Confirming CV%1...").arg((_num)));

    if (mProgrammer != NULL) {
        setBusy(true);
        _reading = false;
        _confirm = true;
        try {
            ((SlotManager*)mProgrammer)->confirmCV(_num, _value, (ProgListener*)this);
        } catch (Exception e) {
            if (status != NULL) status->setText(tr("Exception during CV confirm: %1").arg(e.getMessage()));
            log->warn("Exception during CV read: "+e.getMessage());
            setBusy(false);
        }
    } else {
        if (status != NULL) status->setText(tr("StateNoProgrammer"));
        log->error("No programmer available!");
    }
}

/*public*/ void CvValue::write(QLabel* status)
{
 if (log->isDebugEnabled()) log->debug("write call with Cv number "+(_num));
 setToWrite(false);
 // get a programmer reference and write
 _status = status;

 if (status != NULL) status->setText(tr("Writing CV%1...").arg(_num));
 if (mProgrammer != NULL)
 {
  setBusy(true);
  _reading = false;
  _confirm = false;
  try {
  setState(UNKNOWN);
  ((SlotManager*)mProgrammer)->writeCV(_num, _value, (ProgListener*)this);
  }
  catch (Exception e)
  {
   setState(UNKNOWN);
   if (status != NULL) status->setText(tr("Exception during CV write: %1").arg(e.getMessage()));
   log->warn("Exception during CV write: "+e.getMessage());
   setBusy(false);
  }
 }
 else
 {
  if (status != NULL) status->setText(tr("StateNoProgrammer"));
  log->error("No programmer available!");
 }
}


/*public*/ void CvValue::programmingOpReply(int value, int retval)
{
 if (log->isDebugEnabled()) log->debug("CV progOpReply for CV "+(_num)+" with retval "+QString::number(retval)
                                        +" during "
                                        +(_reading?"read sequence":
                                          (_confirm?"confirm sequence":"write sequence")));
 if (!_busy) log->error("opReply when not busy!");
 bool oldBusy = _busy;
 if (retval == ProgListener::OK)
 {
  if (_status != NULL) _status->setText(tr("OK"));
  if (_reading)
  {
   // set & notify value directly to avoid state going to EDITED
   _value = value;
   _tableEntry->setText(QString::number(value));
   notifyValueChange(value);
   setState(READ);
   if (log->isDebugEnabled()) log->debug("CV setting not busy on end read");
   _busy = false;
   notifyBusyChange(oldBusy, _busy);
  }
  else if (_confirm)
  {
   // _value doesn't change, just the state, and save the value read
   _decoderValue = value;
   // does the decoder value match the file value
   if (value == _value)
    setState(SAME);
   else
    setState(DIFF);
   _busy = false;
   notifyBusyChange(oldBusy, _busy);
  }
  else
  {  // writing
   setState(STORED);
   _busy = false;
   notifyBusyChange(oldBusy, _busy);
  }
 }
 else
 {
  if (_status != NULL) _status->setText(tr("Programmer error: %1").arg(((SlotManager*)mProgrammer)->decodeErrorCode(retval)));

  // delay to ensure that the message appears!
  QTimer* timer = new QTimer();
//                    1000, new java.awt.event.ActionListener() {
//                /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                    errorTimeout();
//                }
//            });
  connect(timer, SIGNAL(timeout()), this, SLOT(errorTimeout()));
  timer->setInterval(1000);
  timer->setSingleShot(true);
  timer->start();
 }
 if (log->isDebugEnabled()) log->debug("CV progOpReply end of handling CV "+(_num));
}

void CvValue::errorTimeout() {
    setState(UNKNOWN);
    if (log->isDebugEnabled()) log->debug("CV setting not busy on error reply");
    _busy = false;
    notifyBusyChange(true, _busy);
}

// clean up connections when done
/*public*/ void CvValue::dispose() {
    if (log->isDebugEnabled()) log->debug("dispose");
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* CvValue::log = LoggerFactory::getLogger("CvValue");
