#include "abstractvalue.h"

QColor AbstractValue::COLOR_UNKNOWN = QColor(Qt::red);
QColor AbstractValue::COLOR_EDITED  = QColor(255,170,0);
QColor AbstractValue::COLOR_READ     = QColor(Qt::darkYellow);
QColor AbstractValue::COLOR_STORED   = QColor(Qt::green);
QColor AbstractValue::COLOR_FROMFILE = QColor(Qt::yellow);
QColor AbstractValue::COLOR_SAME     = QColor(Qt::darkGreen);
QColor AbstractValue::COLOR_DIFF = QColor(Qt::red);

AbstractValue::AbstractValue(QObject *parent) :
    QObject(parent)
{
 prop = new PropertyChangeSupport(this);
// COLOR_UNKNOWN = QColor(Qt::red);
// COLOR_EDITED  = QColor(255,170,0);
// COLOR_READ     = QColor();
// COLOR_STORED   = QColor();
// COLOR_FROMFILE = QColor(Qt::yellow);
// COLOR_SAME     = QColor();
// COLOR_DIFF = QColor(Qt::magenta);

}
/**
 * Define common base class methods for CvValue and VariableValue classes
 * <P>
 * The ToRead parameter (bool, unbound) is used to remember whether
 * this object has been read during a "read all" operation.  This allows
 * removal of duplicate operations.
 * <P>
 * The ToWrite parameter (bool, unbound) is used to remember whether
 * this object has been read during a "write all" operation.  This allows
 * removal of duplicate operations.
 * <P>
 * The Available parameter (bool, unbound) remembers whether the variable
 * should be displayed, programmed, etc.
 *
 * Description:		Represents a single CV value
 * @author			Bob Jacobsen   Copyright (C) 2001, 2005
 * @version			$Revision: 17977 $
 */
///*public*/ abstract class AbstractValue {

    // method to handle color changes for states
//    /*abstract*/ virtual void setColor(QColor c);


/*public*/ void AbstractValue::setToRead(bool state) {
    _toRead = state;
}
/*public*/ bool AbstractValue::isToRead() { return _toRead; }

/*public*/ void AbstractValue::setToWrite(bool state) {
    _toWrite = state;
}
/*public*/ bool AbstractValue::isToWrite() { return _toWrite; }

/*public*/ /*static*/ QString AbstractValue::stateNameFromValue(int val) {
    switch (val) {
        case UNKNOWN:
            return "Unknown";
        case EDITED:
            return "Edited";
        case READ:
            return "Read";
        case STORED:
            return "Stored";
        case FROMFILE:
            return "FromFile";
        case SAME:
            return "Same";
        case DIFF:
            return "Different";
        default:
            return "<unexpected value: "+QString::number(val)+">";
    }
}

/*public*/ void AbstractValue::setAvailable(bool available)
{
 bool oldval = this->available;
 this->available = available;
 if (oldval != this->available)
 {
  prop->firePropertyChange("Available",oldval, available);
 }
}
/*public*/ bool AbstractValue::getAvailable() { return available; }

/*public*/ void AbstractValue::addPropertyChangeListener(PropertyChangeListener* p)
{
 prop->addPropertyChangeListener(p);
}

/*public*/ void AbstractValue::removePropertyChangeListener(PropertyChangeListener* p)
{
 prop->removePropertyChangeListener(p);
}
