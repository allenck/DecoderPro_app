#include "variablevalue.h"
#include "loggerfactory.h"
#include "exceptions.h"

//VariableValue::VariableValue(QObject *parent) :
//    AbstractValue(parent)
//{
//}
/**
 * Represents a single Variable value; abstract base class.
 *
 * <p>The "changed" parameter (non-bound, accessed via isChanged)
 * indicates whether a "write changes" or "read changes" operation
 * should handle this object.
 *
 * @author   Bob Jacobsen   Copyright (C) 2001, 2002, 2003, 2004, 2005
 * @author   Howard G. Penny Copyright (C) 2005
 * @version  $Revision: 17977 $
 */
// public abstract class VariableValue extends AbstractValue implements java.beans.PropertyChangeListener {
// and thus can be called without limit
// and thus should be called a limited number of times

// The actual stored value is not the most interesting thing
// Instead, you usually get a (Object) representation for display in
// a table, etc. Modification of the state of that object then
// gets reflected back, causing the underlying CV objects to change.
//    abstract /*public*/ Component getCommonRep();	// and thus should be called a limited number of times
//    abstract /*public*/ Component getNewRep(String format); // this one is returning a new object

/**
 * @return String that can (usually) be interpreted as an integer
 */
//    abstract /*public*/ String getValueString();
/**
 * @return Value as a native-form Object
 */
//    abstract /*public*/ Object getValueObject();
/**
 * @return User-desired value, which may or may not be an integer
 */
/*public*/ QString VariableValue::getTextValue() { return getValueString(); }

/**
 * Set the value from a single number.
 *
 * In some cases, e.g. speed tables, this will result in
 * complex behavior, where setIntValue(getIntValue()) results
 * in something unexpected.
 */
//    abstract /*public*/ void setIntValue(int i);

/**
 * Get the value as a single number.
 *
 * In some cases, e.g. speed tables, this will result in
 * complex behavior, where setIntValue(getIntValue()) results
 * in something unexpected.
 */
//    abstract /*public*/ int getIntValue();

void VariableValue::updatedTextField() {
    logit->error("unexpected use of updatedTextField()"/*, new Exception("traceback")*/);
}

/**
 * Provide a user-readable description of the CVs accessed by this variable.
 * <p>
 * Default is a single CV number
 */
/*public*/ QString VariableValue::getCvDescription() {
    return "CV" + _cvNum;
}

/**
 * Set the value from a single number.
 *
 * In some cases, e.g. speed tables, this will result in complex behavior,
 * where setIntValue(getIntValue()) results in something unexpected.
 */
//abstract public void setIntValue(int i);

/**
 * Set value from a String value.
 * <p>
 * The current implementation is a stand-in.  Note that
 * e.g. Speed Tables don't use a single Int, so will
 * just be skipped. The solution to that is to overload this in
 * complicated variable types.
 */
/*public*/ void VariableValue::setValue(QString value) {
    bool bok;
        int val = value.toInt(&bok);
        if(bok)
         setIntValue(val);
    else
        logit->debug(tr("skipping set of non-integer value \"%1\"").arg(value));
}

/**
 * Get the value as a single number.
 *
 * In some cases, e.g. speed tables, this will result in complex behavior,
 * where setIntValue(getIntValue()) results in something unexpected.
 */
// /*abstract*/ /*public*/ int getIntValue() {return 0;}

/**
 * Always read the contents of this Variable
 */
//    abstract /*public*/ void readAll();
/**
 * Always write the contents of this Variable
 */
//    abstract /*public*/ void writeAll();
/**
 * Confirm the contents of this Variable
 */
/*public*/ void VariableValue::confirmAll(){
    logit->error("should never execute this");
}


/**
 * Read the contents of this Variable if it's in a state
 * that indicates it was "changed"
 * @see #isChanged
 */
//    abstract /*public*/ void readChanges();

/**
 * Write the contents of this Variable if it's in a state
 * that indicates it was "changed"
 * @see #isChanged
 */
//    abstract /*public*/ void writeChanges();

/**
 * Determine whether this Variable is "changed", so that
 * "read changes" and "write changes" will act on it.
 * @see #considerChanged
 */
//    abstract /*public*/ bool isChanged();

/**
 * Default implementation for subclasses to tell if a CV meets a common definition
 * of "changed".  This implementation will only
 * consider a variable to be changed if the underlying CV(s) state is
 * EDITTED, e.g. if the CV(s) has been manually editted.
 * @param c CV to be examined
 * @return true if to be considered changed
 */
/*static*/ /*public*/ bool VariableValue::considerChanged(CvValue* c)
{
 int state = c->getState();
 if (state == CvValue::EDITED || state == CvValue::UNKNOWN)
 {
  return true;
 }
 else
 {
  return false;
 }
}

// handle incoming parameter notification
//    abstract /*public*/ void propertyChange(java.beans.PropertyChangeEvent e);
//    abstract /*public*/ void dispose();

//    abstract /*public*/ Object rangeVal();

// methods implemented here:
/*public*/ VariableValue::VariableValue(QString label, QString comment, QString cvName, bool readOnly,
                                        bool infoOnly, bool writeOnly, bool opsOnly, QString cvNum,
                                        QString mask, QMap<QString, CvValue*>* v, JLabel* status, QString item, QObject *parent)
 : AbstractValue(parent)
{
 logit->setDebugEnabled(true);
    _label = label;
    _comment = comment;
    _cvName = cvName;
    _readOnly = readOnly;
    _infoOnly = infoOnly;
    _writeOnly = writeOnly;
    _opsOnly = opsOnly;
    _cvNum = cvNum;
    _mask = mask;
    _cvMap = v;
    _status = status;
    _item = item;
    _state = UNKNOWN;
    _busy = false;
    this->parent = parent;
    setObjectName("VariableValue");
}

/**
 * Create a null object.  Normally only used for tests and to pre-load classes.
 */
/*protected*/ VariableValue::VariableValue(QObject *parent): AbstractValue(parent)
{
 this->parent = parent;
}

// common information - none of these are bound
/*public*/ QString VariableValue::label() { return _label; }
/*public*/ QString VariableValue::item() { return _item; }
/*public*/ QString VariableValue::cvName() { return _cvName; }

/**
 * Set tooltip text to be used by both the "value" and
 * representations of this Variable.
 * <P>This is expected to be overridden in subclasses to
 * change their internal info.
 * @see #updateRepresentation
 * @param t
 */
/*public*/ void VariableValue::setToolTipText(QString t) {
    _tooltipText = t;
}
/**
 * Add the proper tooltip text to a graphical rep
 * before returning it, sets the visibility
 * @param c
 */
/*protected*/ QWidget* VariableValue::updateRepresentation(QWidget* c) {
    c->setToolTip(_tooltipText);
    c->setVisible(getAvailable());
    return c;
}

/*public*/ QString VariableValue::getComment() { return _comment; }

/*public*/ bool VariableValue::getReadOnly() { return _readOnly; }

/*public*/ bool VariableValue::getInfoOnly() { return _infoOnly; }

/*public*/ bool VariableValue::getWriteOnly() { return _writeOnly; }

/*public*/ bool VariableValue::getOpsOnly() { return _opsOnly; }

/*public*/ QString VariableValue::getCvNum() { return _cvNum; }
/*public*/ QString VariableValue::getCvName() { return _cvName; }
/*public*/ QString VariableValue::getMask() { return _mask; }

/*public*/ int VariableValue::getState()  { return _state; }
/*public*/ void VariableValue::setState(int state)
{
 int oldstate = _state;
 _state = state;
 switch (state)
 {
 case UNKNOWN : setColor(COLOR_UNKNOWN ); break;
 case EDITED  : setColor(COLOR_EDITED  ); break;
 case READ    : setColor(COLOR_READ    ); break;
 case STORED  : setColor(COLOR_STORED  ); break;
 case FROMFILE: setColor(COLOR_FROMFILE); break;
 case SAME: 		setColor(COLOR_SAME); break;
 case DIFF: 		setColor(COLOR_DIFF); break;
  default: logit->error("Inconsistent state: "+QString::number(_state));
 }
 if (_state != state /*|| _state == UNKNOWN*/)
 {
  prop->firePropertyChange("State", QVariant(_state), QVariant(state));
  //emit propertyChange(new PropertyChangeEvent(this, "State", QVariant(_state), QVariant(state)));
 emit propertyChange(new PropertyChangeEvent(this, "State", QVariant(oldstate), QVariant(state)));}
}

/**
 * Simple implementation for the case of a single CV. Intended
 * to be sufficient for many subclasses.
 */
/*public*/ void VariableValue::setToRead(bool state) {
    if (getInfoOnly() || getWriteOnly() || !getAvailable()) state = false;
    _cvMap->value(getCvNum())->setToRead(state);
}
/**
 * Simple implementation for the case of a single CV. Intended
 * to be sufficient for many subclasses.
 */
/*public*/ bool VariableValue::isToRead() { return _cvMap->value(getCvNum())->isToRead(); }

/**
 * Simple implementation for the case of a single CV. Intended
 * to be sufficient for many subclasses.
 */
/*public*/ void VariableValue::setToWrite(bool state) {
    if (getInfoOnly() || getReadOnly() || !getAvailable()) {
        state = false;
    }
    if (logit->isDebugEnabled()) logit->debug(tr("setToWrite(")+(state?"true":"false")+") for "+label()+" via CvNum "+(getCvNum()));
    _cvMap->value(getCvNum())->setToWrite(state);
}
/**
 * Simple implementation for the case of a single CV. Intended
 * to be sufficient for many subclasses.
 */
/*public*/ bool VariableValue::isToWrite() { return _cvMap->value(getCvNum())->isToWrite(); }

/**
 * Propogate a state change here to the CVs that are related, which will
 * in turn propagate back to here
 */
//    abstract /*public*/ void setCvState(int state);

/**
 *  A variable is busy during read, write operations
 */
/*public*/ bool VariableValue::isBusy() { return _busy; }
/*protected*/ void VariableValue::setBusy(bool newBusy)
{
 bool oldBusy = _busy;
 _busy = newBusy;
 if (newBusy != oldBusy)
 {
  prop->firePropertyChange("Busy", QVariant(oldBusy), QVariant(newBusy));
  //emit notifyPropertyChange(new PropertyChangeEvent(this, "Busy", QVariant(oldBusy), QVariant(newBusy)));
 }
}

// tool to handle masking, updating

/**
 * In case a set of masks was provided, at end of Ctor pick the first mask
 * for implementing classes that use just one. Call not required if mask is
 * ignored.
 */
/*protected*/ void VariableValue::simplifyMask() {
    if (_mask != "" && _mask.contains(" ")) {
        logit->debug(tr("Mask for var %1 was:%2").arg(getCvName()).arg(_mask));
        _mask = _mask.split(" ")[0];
        logit->debug(tr("Mask1 for var %1 is:%2").arg(getCvName()).arg(_mask));
    }
}

/**
 * Convert a String bit mask like XXXVVVXX to an int like 0b00011100.
 *
 * @param maskString the textual (XXXVVVXX style) mask
 * @return the binary integer (0b00011100 style) mask
 */
/*protected*/ int VariableValue::maskValAsInt(QString maskString) {
    // convert String mask to int
    int mask = 0;
    for (int i = 0; i < maskString.length(); i++) {
        mask = mask << 1;
        if(i < maskString.length())
        {
            if (maskString.at(i) == 'V') {
                mask = mask | 1;
            }
        } else{
            logit->error(tr("mask \"%1\" could not be handled for variable %2").arg(maskString).arg(label()));
        }
    }
    return mask;
}

/**
 * Is this a bit mask (such as XVVVXXXX form) vice radix mask (small
 * integer)?
 *
 * @param mask the bit mask to check
 * @return {@code true} if XVVVXXXX form
 */
/*protected*/ bool VariableValue::isBitMask(QString mask) {
    return mask.isEmpty() || mask.startsWith("X") || mask.startsWith("V");
}

/**
 * Find number of places to shift a value left to align
 * if with a mask.  For example, as mask of "XXVVVXXX"
 * means that the value 5 needs to be shifted left 3 places
 * before being masked and stored as XX101XXX
 */
/*protected*/ int VariableValue::offsetVal(QString maskString) {
    // convert String mask to int
    int offset = 0;
    for (int i=0; i<8; i++) {
        if (maskString.at(i) == 'V') {
            offset = 7-i;  // number of places to shift left
        }
    }
    return offset;
}

/**
 * Get the current value from the CV, using the mask as needed.
 *
 * @param Cv         the CV of interest
 * @param maskString the (XXXVVVXX style) mask for extracting the Variable
 *                   value from this CV
 * @param maxVal     the maximum possible value for this Variable
 * @return the current value of the Variable
 */
/*protected*/ int VariableValue::getValueInCV(int Cv, QString maskString, int maxVal) {
    if (isBitMask(maskString)) {
        return (Cv & maskValAsInt(maskString)) >> offsetVal(maskString);
    } else {
        int radix = (maskString).toInt();
        logit->trace(tr("get value %1 radix %2 returns %3").arg(Cv).arg(radix).arg(Cv / radix));
        return (Cv / radix) % (maxVal + 1);
    }
}


/**
 * Set a value into a CV, using the mask as needed.
 *
 * @param oldCv      Value of the CV before this update is applied
 * @param newVal     Value for this variable (e.g. not the CV value)
 * @param maskString The bit mask for this variable in character form
 * @param maxVal     the maximum possible value for this Variable
 * @return int new value for the CV
 */
/*protected*/ int VariableValue::setValueInCV(int oldCv, int newVal, QString maskString, int maxVal) {
    if (isBitMask(maskString)) {
        int mask = maskValAsInt(maskString);
        int offset = offsetVal(maskString);
        return (oldCv & ~mask) + ((newVal << offset) & mask);
    } else {
        int radix = maskString.toInt();
        int lowPart = oldCv % radix;
        int newPart = newVal % (maxVal + 1) * radix;
        int highPart = (oldCv / (radix * (maxVal + 1))) * (radix * (maxVal + 1));
        int retval = highPart + newPart + lowPart;
        logit->trace(tr("Set sees oldCv %1 radix %2, lowPart %3, newVal %4, highPart %5, does %6").arg(oldCv).arg(radix).arg(lowPart).arg(newVal).arg(highPart).arg(retval));
        return retval;
    }
}

/**
 * Provide access to CVs referenced by this operation
 */
//    abstract /*public*/ CvValue[] usesCVs();
/**
 * Add so that DecVariableValue can be used for different CV's dynamically.
 */
void VariableValue::setSV(int cv)
{
 _cvNum = cv;
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* VariableValue::logit = LoggerFactory::getLogger("VariableValue");

