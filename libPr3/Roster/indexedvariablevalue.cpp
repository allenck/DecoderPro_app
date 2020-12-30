#include "indexedvariablevalue.h"
#include "vartextfield.h"
#include <QIntValidator>

//IndexedVariableValue::IndexedVariableValue(QObject *parent) :
//    VariableValue(parent)
//{
//}
/**
 * Extends VariableValue to represent an indexed variable
 *
 * @author    Howard G. Penny   Copyright (C) 2005
 * @author    Bob Jacobsen   Copyright (C) 2010
 * @version   $Revision: 21023 $
 */
///*public*/ class IndexedVariableValue extends VariableValue
//    implements ActionListener, PropertyChangeListener, FocusListener {

/*public*/ IndexedVariableValue::IndexedVariableValue(int row, QString name, QString comment, QString cvName,
                            bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                            QString cvNum, QString mask, int minVal, int maxVal,
                            QMap<QString,CvValue*>* v, QLabel* status, QString stdname, QObject *parent) :    VariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent)

{
 //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, paarent);
    logit = new Logger("IndexedVariableValue");
    if (logit->isDebugEnabled())
        logit->debug("ctor with cvName "+cvName+", cvNum "+cvNum);
    _row    = row;
    _maxVal = maxVal;
    _minVal = minVal;
    _value = new JTextField(QString("0"), 3);
    _value->setValidator(new QIntValidator(_minVal, _maxVal));
    connect(_value, SIGNAL(editingFinished()), this, SLOT(actionPerformed()));
//    _defaultColor = _value->getBackground();
    CvValue* cv = (_cvMap->value(getCvNum()));
    if (logit->isDebugEnabled())
        logit->debug("cv found as "+cv->toString());
    cv->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(cv, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    if (cv->getInfoOnly()) {
        cv->setState(CvValue::READ);
    } else {
        cv->setState(CvValue::FROMFILE);
    }
    oldContents = "";
    sliders = new QList<IndexedVarSlider*>();
    valuereps = new QList<VarTextField*>();
    _progState = 0;
}

/**
 * Create a null object.  Normally only used for tests and to pre-load classes.
 */
/*protected*/ IndexedVariableValue::IndexedVariableValue(QObject *parent) : VariableValue(parent)
{
    logit = new Logger("IndexedVariableValue");
    QString oldContents;// = "";
    QList<IndexedVarSlider*>* sliders = new QList<IndexedVarSlider*>();
    QList<QLineEdit*>* valuereps = new QList<QLineEdit*>();
}


/*public*/ void IndexedVariableValue::setToolTipText(QString t) {
VariableValue::setToolTipText(t);   // do default stuff
    _value->setToolTip(t);  // set our value
}

/*public*/ QVector<CvValue*>* IndexedVariableValue::usesCVs()
{
 //return new CvValue[]{_cvMap->value(getCvNum())};
 QVector<CvValue*>* list = new QVector<CvValue*>();
 list->append(_cvMap->value(getCvNum()));
 return list;
}

/*public*/ QVariant IndexedVariableValue::rangeVal() {
    return "Decimal: "+QString::number(_minVal)+" - "+QString::number(_maxVal);
}


void IndexedVariableValue::enterField() {
    oldContents = _value->text();
}
void IndexedVariableValue::exitField()
{
 // there may be a lost focus event left in the queue when disposed so protect
 if (_value != NULL && oldContents!=(_value->text()))
 {
  int newVal = _value->text().toInt();
  int oldVal = oldContents.toInt();
  updatedTextField();
  prop->firePropertyChange("Value", (oldVal),
                                (newVal));
  //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", (oldVal), (newVal)));
 }
}

void IndexedVariableValue::updatedTextField() {
    if (logit->isDebugEnabled()) logit->debug("enter updatedTextField");
    // called for new values - set the Indexed CV as needed
    CvValue* cv = _cvMap->value(getCvNum());
    if (logit->isDebugEnabled())
        logit->debug("updatedTextField refs CV "+cv->toString());
    //
    int oldVal = cv->getValue();
    int newVal;  // entered value
//    try {
        newVal = _value->text().toInt();
//    }
//    catch (NumberFormatException ex) { newVal = 0; }
    int newCv = newValue(oldVal, newVal, getMask());
    if (oldVal != newVal)
        cv->setValue(newCv);
}

/** ActionListener implementations */
/*public*/ void IndexedVariableValue::actionPerformed(JActionEvent* /*e*/) {
    if (logit->isDebugEnabled()) logit->debug("actionPerformed");
    int newVal = _value->text().toInt();
    updatedTextField();
    prop->firePropertyChange("Value", QVariant(), (newVal));
    //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", QVariant(), (newVal)));
}

/** FocusListener implementations */
/*public*/ void IndexedVariableValue::focusGained(/*FocusEvent*/QEvent* e) {
    if (logit->isDebugEnabled()) logit->debug("focusGained");
    enterField();
}

/*public*/ void IndexedVariableValue::focusLost(/*FocusEvent*/QEvent* e) {
    if (logit->isDebugEnabled()) logit->debug("focusLost");
    exitField();
}

// to complete this class, fill in the routines to handle "Value" parameter
// and to read/write/hear parameter changes.
/*public*/ QString IndexedVariableValue::getValueString() {
    return _value->text();
}

/*public*/ void IndexedVariableValue::setIntValue(int i) {
    setValue(i);
}

/*public*/ int IndexedVariableValue::getIntValue() {
    return _value->text().toInt();
}

/*public*/ QVariant IndexedVariableValue::getValueObject() {
    return _value->text();
}

/*public*/ QWidget* IndexedVariableValue::getCommonRep()  {
    if (getReadOnly())  {
        QLabel* r = new QLabel(_value->text());
        updateRepresentation(r);
        return r;
    } else
        return _value;
}

/*public*/ QWidget* IndexedVariableValue::getNewRep(QString format)  {
    if (format==("vslider")) {
        IndexedVarSlider* b = new IndexedVarSlider(this, _minVal, _maxVal);
        b->setOrientation(/*JSlider.VERTICAL*/Qt::Vertical);
        sliders->append(b);
        updateRepresentation(b);
        if (!getAvailable()) b->setVisible(false);
        return b;
    }
    else if (format==("hslider")) {
        IndexedVarSlider* b = new IndexedVarSlider(this, _minVal, _maxVal);
        b->setOrientation(/*JSlider.HORIZONTAL*/Qt::Horizontal);
//        if (_maxVal > 20) {
//            b->setMajorTickSpacing(_maxVal/2);
//            b->setMinorTickSpacing((_maxVal+1)/8);
//        } else {
//            b->setMajorTickSpacing(5);
//            b->setMinorTickSpacing(1); // because JSlider does not SnapToValue
//            b->setSnapToTicks(true);   // like it should, we fake it here
//        }
//        b->setSize(b->width(),28);
        QHash<int,QLabel*>* labelTable = new QHash<int,QLabel*>();
        labelTable->insert(  0 , new QLabel("0%")) ;
        if ( _maxVal == 63 ) {   // this if for the QSI mute level, not very universal, needs work
            labelTable->insert(  _maxVal/2 , new QLabel("25%") );
            labelTable->insert( _maxVal , new QLabel("50%") );
        } else {
            labelTable->insert( _maxVal/2 , new QLabel("50%") );
            labelTable->insert( _maxVal , new QLabel("100%") );
        }
//        b->setLabelTable( labelTable );
//        b->setPaintTicks(true);
//        b->setPaintLabels(true);
        sliders->append(b);
        updateRepresentation(b);
        if (!getAvailable()) b->setVisible(false);
        return b;
    }
#if 1 // TODO:
    else
    {
     VarTextField* value = new VarTextField(_value->getDocument(),_value->text(), 3, this);
     if (getReadOnly() || getInfoOnly())
     {
      //value->setEditable(false);
      value->setReadOnly(true);
     }
        valuereps->append(value);
        updateRepresentation(value);
        if (!getAvailable()) value->setVisible(false);
        return value;
    }
#endif
}

/*public*/ void IndexedVariableValue::setAvailable(bool a) {
    for (int i = 0; i<sliders->size(); i++)
        sliders->at(i)->setVisible(a);
    for (int i = 0; i<valuereps->size(); i++)
        valuereps->at(i)->setVisible(a);
    VariableValue::setAvailable(a);
}



/**
 * Set a new value, including notification as needed.  This does the
 * conversion from string to int, so if the place where formatting
 * needs to be applied
 */
/*public*/ void IndexedVariableValue::setValue(int value)
{
 int oldVal;
//    try {
 oldVal = _value->text().toInt();
//    } catch (NumberFormatException ex) { oldVal = -999; }
 if (logit->isDebugEnabled()) logit->debug("setValue with new value "+QString::number(value)+" old value "+QString::number(oldVal));
 if (oldVal != value)
 {
  _value->setText(QString::number(value));
  updatedTextField();
  prop->firePropertyChange("Value", (oldVal), (value));
  //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", (oldVal), (value)));
 }
}


// implement an abstract member to set colors
QColor IndexedVariableValue::getColor() { /*return _value->getBackground();*/ return QColor();}
void IndexedVariableValue::setColor(QColor c) {
    if (c .isValid()) _value->setBackground(c);
    else _value->setBackground(_defaultColor);
//    // prop.firePropertyChange("Value", null, null);
}

/**
 * Notify the connected CVs of a state change from above
 * @param state
 */
/*public*/ void IndexedVariableValue::setCvState(int state) {
    (_cvMap->value(getCvNum()))->setState(state);
}

/*public*/ void IndexedVariableValue::setToRead(bool state) {
    if (getInfoOnly() || getWriteOnly() || !getAvailable()) state = false;
    (_cvMap->value(getCvNum()))->setToRead(state);
}
/*public*/ bool IndexedVariableValue::isToRead() { return getAvailable() && (_cvMap->value(getCvNum()))->isToRead(); }

/*public*/ void IndexedVariableValue::setToWrite(bool state) {
    if (getInfoOnly() || getReadOnly() || !getAvailable()) state = false;
    (_cvMap->value(getCvNum()))->setToWrite(state);
}
/*public*/ bool IndexedVariableValue::isToWrite() { return getAvailable() && (_cvMap->value(getCvNum()))->isToWrite(); }

/*public*/ bool IndexedVariableValue::isChanged() {
    CvValue* cv = (_cvMap->value(getCvNum()));
    return considerChanged(cv);
}

/*public*/ void IndexedVariableValue::readChanges() {
     if (isChanged()) readAll();
}

/*public*/ void IndexedVariableValue::writeChanges() {
     if (isChanged()) writeAll();
}

/*public*/ void IndexedVariableValue::readAll() {
    setBusy(true);  // will be reset when value changes
    setToRead(false);
    if (_progState != IDLE) logit->warn("Programming state "+QString::number(_progState)+", not IDLE, in read()");
    // lets skip the SI step if SI is not used
    if ((_cvMap->value(getCvNum()))->siVal() >= 0) {
        _progState = WRITING_PI4R;
    } else {
        _progState = WRITING_SI4R;
    }
    retries = 0;
    if (logit->isDebugEnabled()) logit->debug("invoke PI write for CV read");
    // to read any indexed CV we must write the PI
    (_cvMap->value(getCvNum()))->writePI(_status);
}

/*public*/ void IndexedVariableValue::writeAll() {
    if (getReadOnly()) {
        logit->error("unexpected write operation when readOnly is set");
    }
    setBusy(true);  // will be reset when value changes
    setToWrite(false);
    if (_progState != IDLE) logit->warn("Programming state "+QString::number(_progState)+", not IDLE, in write()");
    // lets skip the SI step if SI is not used
    if ((_cvMap->value(getCvNum()))->siVal() >= 0) {
        _progState = WRITING_PI4W;
    } else {
        _progState = WRITING_SI4W;
    }
    retries = 0;
    if (logit->isDebugEnabled()) logit->debug("invoke PI write for CV write");
    // to write any indexed CV we must write the PI
    (_cvMap->value(getCvNum()))->writePI(_status);
}

/*public*/ void IndexedVariableValue::confirmAll() {
    setBusy(true);  // will be reset when value changes
    setToRead(false);
    if (_progState != IDLE) logit->warn("Programming state "+QString::number(_progState)+", not IDLE, in read()");
    // lets skip the SI step if SI is not used
    if ((_cvMap->value(getCvNum()))->siVal() >= 0) {
        _progState = WRITING_PI4C;
    } else {
        _progState = WRITING_SI4C;
    }
    retries = 0;
    if (logit->isDebugEnabled()) logit->debug("invoke PI write for CV confirm");
    // to read any indexed CV we must write the PI
    (_cvMap->value(getCvNum()))->writePI(_status);
}

// handle incoming parameter notification
/*public*/ void IndexedVariableValue::propertyChange(PropertyChangeEvent* e) {
    if (logit->isDebugEnabled()) logit->debug("Property changed: "+e->getPropertyName());
    // notification from Indexed CV; check for Value being changed
    if (e->getPropertyName()==("Busy") && (e->getNewValue().toBool())==(false)) {
        // busy transitions drive the state
        switch (_progState) {
        case IDLE:  // no, just an Indexed CV update
            if (logit->isDebugEnabled()) logit->error("Busy goes false with state IDLE");
            return;
        case WRITING_PI4R:   // have written the PI, now write SI if needed
        case WRITING_PI4C:
        case WRITING_PI4W:
            if (logit->isDebugEnabled()) logit->debug("Busy goes false with state WRITING_PI");

            // check for success
            if ((retries < RETRY_MAX)
                && ( (_cvMap->value(getCvNum()))->getState() != CvValue::STORED) ) {
                // need to retry on error; leave progState as it was
                logit->debug("retry");
                retries++;
                (_cvMap->value(getCvNum()))->writePI(_status);
                return;
            }
            // success, move on to next
            retries = 0;

            if (_progState == WRITING_PI4R )
                _progState = WRITING_SI4R;
            else if (_progState == WRITING_PI4C )
                _progState = WRITING_SI4C;
            else
                _progState = WRITING_SI4W;
            (_cvMap->value(getCvNum()))->writeSI(_status);
            return;
        case WRITING_SI4R:  // have written the SI if needed, now read or write CV
        case WRITING_SI4C:
        case WRITING_SI4W:
            if (logit->isDebugEnabled()) logit->debug("Busy goes false with state WRITING_SI");

            // check for success
            if ((retries < RETRY_MAX)
                && ( (_cvMap->value(getCvNum()))->getState() != CvValue::STORED) ) {
                // need to retry on error; leave progState as it was
                logit->debug("retry");
                retries++;
                (_cvMap->value(getCvNum()))->writeSI(_status);
                return;
            }
            // success, move on to next
            retries = 0;
            if (_progState == WRITING_SI4R ) {
                _progState = READING_CV;
                (_cvMap->value(getCvNum()))->readIcV(_status);
            } else if (_progState == WRITING_SI4C ) {
                _progState = COMPARE_CV;
                (_cvMap->value(getCvNum()))->confirmIcV(_status);
             } else {
                _progState = WRITING_CV;
                (_cvMap->value(getCvNum()))->writeIcV(_status);
            }
            return;
        case READING_CV:  // now done with the read request
            if (logit->isDebugEnabled()) logit->debug("Finished reading the Indexed CV");

            // check for success
            if ((retries < RETRY_MAX)
                && ( (_cvMap->value(getCvNum()))->getState() != CvValue::READ) ) {
                // need to retry on error; leave progState as it was
                logit->debug("retry");
                retries++;
                (_cvMap->value(getCvNum()))->readIcV(_status);
                return;
            }
            // success, move on to next
            retries = 0;
            _progState = IDLE;
            setBusy(false);
            return;
        case COMPARE_CV:  // now done with the read request
            if (logit->isDebugEnabled()) logit->debug("Finished reading the Indexed CV for compare");

            // check for success SAME or DIFF?
            if ((retries < RETRY_MAX)
                    && (( _cvMap->value(getCvNum()))
                            ->getState() != CvValue::SAME)
                    && (( _cvMap->value(getCvNum()))
                            ->getState() != CvValue::DIFF)) {
                // need to retry on error; leave progState as it was
                logit->debug("retry");
                retries++;
                (_cvMap->value(getCvNum()))->confirmIcV(_status);
                return;
            }
            // success, move on to next
            retries = 0;

            _progState = IDLE;
            setBusy(false);
            return;
        case WRITING_CV:  // now done with the write request
            if (logit->isDebugEnabled()) logit->debug("Finished writing the Indexed CV");

            // check for success
            if ((retries < RETRY_MAX)
                && ( (_cvMap->value(getCvNum()))->getState() != CvValue::STORED) ) {
                // need to retry on error; leave progState as it was
                logit->debug("retry");
                retries++;
                (_cvMap->value(getCvNum()))->writeIcV(_status);
                return;
            }
            // success, move on to next
            retries = 0;
            _progState = IDLE;
            VariableValue::setState(STORED);
            setBusy(false);
            return;
        default:  // unexpected!
            logit->error("Unexpected state found: "+_progState);
            _progState = IDLE;
            return;
        }
    }
    else if (e->getPropertyName()==("State")) {
        CvValue* cv = _cvMap->value(getCvNum());
        setState(cv->getState());
    }
    else if (e->getPropertyName()==("Value")) {
        // update value of Variable
        CvValue* cv = _cvMap->value(getCvNum());
        int newVal = (cv->getValue() & maskVal(getMask())) >> offsetVal(getMask());
        setValue(newVal);  // check for duplicate done inside setVal
    }
}

// clean up connections when done
/*public*/ void IndexedVariableValue::dispose() {
   if (logit->isDebugEnabled()) logit->debug("dispose");
   if (_value != NULL) {
//       _value->removeActionListener((ActionListener*)this);
//       _value->removeFocusListener(this);
//       _value->removePropertyChangeListener((PropertyChangeListener*)this);
       _value = NULL;
   }
   //(_cvMap->value(getCvNum()))->removePropertyChangeListener(this);
}
