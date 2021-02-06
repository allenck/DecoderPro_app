#include "constantvalue.h"

//ConstantValue::ConstantValue(QObject *parent) :
//    VariableValue(parent)
//{
//}
/**
 * Extends VariableValue to represent a constant enum-like-thing
 * Note that there's no CV associated with this.
 *
 * @author    Bob Jacobsen   Copyright (C) 2001
 * @version   $Revision: 17977 $
 *
 */
// /*public*/ class ConstantValue extends VariableValue {

/*public*/ ConstantValue::ConstantValue(QString name, QString comment, QString cvName,
                     bool readOnly, bool infoOnly, bool writeOnly,  bool opsOnly,
                     QString cvNum, QString mask, int minVal, int maxVal,
                     QMap<QString,CvValue*>* v, JLabel* status, QString stdname, QObject *parent) :
    VariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent)

{
 //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent);
    logit = new Logger("ConstantValue");
    _itemArray = NULL;
    _maxVal = maxVal;
    _minVal = minVal;
    _value = new QComboBox();
    for (int i=0; i<=maxVal; i++) {
        _value->addItem("0");
    }
    comboCBs = new QList<QCheckBox*>();
    comboRBs = new QList<QRadioButton*>();
}

/**
 * Create a NULL object.  Normally only used for tests and to pre-load classes.
 */
/*public*/ ConstantValue::ConstantValue(QObject *parent) : VariableValue(parent)
{
 _value = NULL;
 comboCBs = new QList<QCheckBox*>();
 comboRBs = new QList<QRadioButton*>();

}

/*public*/ QVector<CvValue *> ConstantValue::usesCVs() {
    return  QVector<CvValue*>();
}


/*public*/ void ConstantValue::setToolTipText(QString t) {
VariableValue::setToolTipText(t);   // do default stuff
    _value->setToolTip(t);  // set our value
}


/*public*/ QVariant ConstantValue::rangeVal() {
    return "constant: "+QString::number(_minVal)+" - "+QString::number(_maxVal);
}

// to complete this class, fill in the routines to handle "Value" parameter
// and to read/write/hear parameter changes.
/*public*/ QString ConstantValue::getValueString() {
    return QString::number(_value->currentIndex());
}
/*public*/ void ConstantValue::setIntValue(int i) {
    _value->setCurrentIndex(i);  // automatically fires a change event
}
/*public*/ int ConstantValue::getIntValue() {
    return _value->currentIndex();
}

/*public*/ QVariant ConstantValue::getValueObject() {
    return (_value->currentIndex());
}

/*public*/ QWidget* ConstantValue::getCommonRep()  { return _value; }
/*public*/ void ConstantValue::setValue(int value) {
    int oldVal = _value->currentIndex();
    _value->setCurrentIndex(value);
    if (oldVal != value || getState() == VariableValue::UNKNOWN)
        prop->firePropertyChange("Value", QVariant(), (value));
}

/*public*/ QWidget* ConstantValue::getNewRep(QString format) {
    // sort on format type
    if (format==("checkbox")) {
        // this only makes sense if there are exactly two options
        QCheckBox* b = new QCheckBox();
        b->setEnabled(false);
        b->setChecked(true);
        comboCBs->append(b);
        updateRepresentation(b);
        return b;
    }
    else if (format==("radiobuttons")) {
        QRadioButton* b = new QRadioButton();
        comboRBs->append(b);
        updateRepresentation(b);
        return b;
    }
    else if (format==("onradiobutton")) {
        QRadioButton* b = new QRadioButton();
        comboRBs->append(b);
        updateRepresentation(b);
        return b;
    }
    else if (format==("offradiobutton")) {
        QRadioButton* b = new QRadioButton();
        comboRBs->append(b);
        updateRepresentation(b);
        return b;
    }
    else {
        logit->error("Did not recognize a value format: "+format);
        return NULL;
    }
}


// implement an abstract member to set colors
void ConstantValue::setColor(QColor c) {
}

/**
 * No connected CV, so this notify does nothing
 * @param state
 */
/*public*/ void ConstantValue::setCvState(int state) {
}

/*public*/ bool ConstantValue::isChanged() {
    return false;
}

/*public*/ void ConstantValue::setToRead(bool state) {}

/*public*/ bool ConstantValue::isToRead() {
    return false;
}

/*public*/ void ConstantValue::setToWrite(bool state) {}

/*public*/ bool ConstantValue::isToWrite() {
    return false;
}

/*public*/ void ConstantValue::readChanges() {
     if (isChanged()) readAll();
}

/*public*/ void ConstantValue::writeChanges() {
     if (isChanged()) writeAll();
}

/**
 * Skip actually reading, but set states and notifications anyway.
 * <P>
 * This sets the state to READ so that you can
 * have algorithms like "write all variables that aren't in READ state"
 * This is different from the 'normal' VariableValue objects, which
 * rely on the associated CV objects to drive state changes at the
 * end of the write.
 */
/*public*/ void ConstantValue::readAll() {
    if (logit->isDebugEnabled()) logit->debug("read invoked");
    setToRead(false);
    setState(READ);
    setBusy(true);
    setBusy(false);
}
/**
 * Skip actually writing, but set states and notifications anyway.
 * <P>
 * This sets the state to STORED so that you can
 * have algorithms like "write all variables that aren't in STORED state"
 * This is different from the 'normal' VariableValue objects, which
 * rely on the associated CV objects to drive state changes at the
 * end of the write.
 */
/*public*/ void ConstantValue::writeAll() {
    if (logit->isDebugEnabled()) logit->debug("write invoked");
    setToWrite(false);
    setState(STORED);
    setBusy(true);
    setBusy(false);
}

/*public*/ void ConstantValue::propertyChange(PropertyChangeEvent* e) {
    logit->warn("Unexpected propertyChange: "/*+e*/);
}

// clean up connections when done
/*public*/ void ConstantValue::dispose() {
    if (logit->isDebugEnabled()) logit->debug("dispose");

    _value = NULL;
    // do something about the VarComboBox
}
