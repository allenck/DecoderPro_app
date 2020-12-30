#include "splitvariablevalue.h"
#include "vartextfield.h"

//SplitVariableValue::SplitVariableValue(QObject *parent) :
//    VariableValue(parent)
//{
//}
/**
 * Extends VariableValue to represent a variable
 * split across two CVs.
 * <P>The mask represents the part of the value that's
 * present in the first CV; higher-order bits are loaded to the
 * second CV.
 * <P>The original use is for addresses of stationary (accessory)
 * <P>Factor and Offset are applied when going <i>to</i> value
 * of the variable <i>to</> the CV values:
 *<PRE>
 Value to put in CVs = ((value in text field) - Offset)/Factor
 Value to put in text field = ((value in CVs) * Factor) + Offset
 *</PRE>
 * decoders.
 * @author			Bob Jacobsen   Copyright (C) 2002, 2003, 2004
 * @version			$Revision: 21268 $
 *
 */
///*public*/ class SplitVariableValue extends VariableValue
//    implements ActionListener, PropertyChangeListener, FocusListener {

/*public*/ SplitVariableValue::SplitVariableValue(QString name, QString comment, QString cvName,
                          bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                          QString cvNum, QString mask, int minVal, int maxVal,
                          QMap<QString,CvValue*>* v, QLabel* status, QString stdname,
                          int pSecondCV, int pFactor, int pOffset, QString uppermask, QObject *parent) :
    VariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent)

{
    //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent);
    logit = new Logger("SplitVariableValue");
    _maxVal = maxVal;
    _minVal = minVal;
    _value = new JTextField("0",5);
    _defaultColor = _value->getBackground();
    _value->setBackground(COLOR_UNKNOWN);
    mFactor = pFactor;
    mOffset = pOffset;
    // connect to the JTextField value, cv
//    _value.addActionListener(this);
    connect(_value, SIGNAL(editingFinished()), this, SLOT(actionPerformed()));
//    _value.addFocusListener(this);
    mSecondCV = pSecondCV;

    lowerbitmask = maskVal(mask);
    lowerbitoffset = offsetVal(mask);
    upperbitmask = maskVal(uppermask);

    // upper bit offset includes lower bit offset, and MSB bits missing from upper part
    upperbitoffset = offsetVal(uppermask);
    QString t = mask;
    while (t.length()>0) {
        if (!t.startsWith("V"))
            upperbitoffset++;
        t = t.mid(1);
    }
    if (logit->isDebugEnabled()) logit->debug("CV "+(getCvNum())+","+QString::number(getSecondCvNum())+" upper mask "+uppermask+" had offsetVal="+QString::number(offsetVal(uppermask))
        +" so upperbitoffset="+QString::number(upperbitoffset));

    // connect for notification
    CvValue* cv = (_cvMap->value(getCvNum()));
    cv->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(cv, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    cv->setState(CvValue::FROMFILE);
    CvValue* cv1 = (_cvMap->value(QString::number(getSecondCvNum())));
    if(cv1 != NULL)
    {
    cv1->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(cv1, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    cv1->setState(CvValue::FROMFILE);
    }
    oldContents = "";
    reps = new QList<QWidget*>();
    _progState = 0;
}

/*public*/ QVector<CvValue*>* SplitVariableValue::usesCVs() {
    QVector<CvValue*>* list = new QVector<CvValue*>;
    list->append(_cvMap->value(getCvNum()));
    list->append(_cvMap->value(QString::number(getSecondCvNum())));
  return list;
}


/*public*/ void SplitVariableValue::setToolTipText(QString t) {
VariableValue::setToolTipText(t);   // do default stuff
    _value->setToolTip(t);  // set our value
}
/*public*/ int SplitVariableValue::getSecondCvNum() { return mSecondCV;}

// the connection is to cvNum and cvNum+1


/*public*/ QVariant SplitVariableValue::rangeVal() {
    return "Split value";
}

void SplitVariableValue::enterField() {
    oldContents = _value->text();
}

void SplitVariableValue::exitField() {
    // there may be a lost focus event left in the queue when disposed so protect
    if (_value != NULL && oldContents!=(_value->text())) {
        int newVal = (((_value->text()).toInt())-mOffset)/mFactor;
        int oldVal = (((oldContents).toInt())-mOffset)/mFactor;
        updatedTextField();
        prop->firePropertyChange("Value", (oldVal), (newVal));
        //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", (oldVal), (newVal)));
    }
}

void SplitVariableValue::updatedTextField()
{
    if (logit->isDebugEnabled()) logit->debug("CV "+(getCvNum())+","+QString::number(getSecondCvNum())+" enter updatedTextField in SplitVal");
    // called for new values - set the CV as needed
    CvValue* cv1 = _cvMap->value(getCvNum());
    CvValue* cv2 = _cvMap->value(QString::number(getSecondCvNum()));

    int newEntry;  // entered value
//    try {
        newEntry = (_value->text()).toInt();
//    }
//    catch (java.lang.NumberFormatException ex) { newEntry = 0; }

    // calculate resulting number
    int newVal = (newEntry-mOffset)/mFactor;

    // combine with existing values via mask
    if (logit->isDebugEnabled())
        logit->debug("CV "+(getCvNum())+","+QString::number(getSecondCvNum())+" lo cv was "+QString::number(cv1->getValue())+" mask="+QString::number(lowerbitmask)+" offset="+QString::number(lowerbitoffset));
    int newCv1 = ( (newVal << lowerbitoffset) & lowerbitmask )
                | (~lowerbitmask & cv1->getValue());

    if (logit->isDebugEnabled())
        logit->debug("CV "+(getCvNum())+","+QString::number(getSecondCvNum())+" hi cv was "+QString::number(cv2->getValue())+" mask="+QString::number(upperbitmask)+" offset="+QString::number(upperbitoffset));
    int newCv2 = (((newVal << upperbitoffset)>>8)&upperbitmask)
                | (~upperbitmask & cv2->getValue());
    if (logit->isDebugEnabled()) logit->debug("CV "+(getCvNum())+","+QString::number(getSecondCvNum())+" new value "+QString::number(newVal)+" gives first="+QString::number(newCv1)+" second="+QString::number(newCv2));

    // cv updates here trigger updated property changes, which means
    // we're going to get notified sooner or later.
    cv1->setValue(newCv1);
    cv2->setValue(newCv2);
    if (logit->isDebugEnabled()) logit->debug("CV "+(getCvNum())+","+QString::number(getSecondCvNum())+" exit updatedTextField");

}

/** ActionListener implementations */
/*public*/ void SplitVariableValue::actionPerformed(JActionEvent* /*e*/) {
    if (logit->isDebugEnabled()) logit->debug("CV "+(getCvNum())+","+QString::number(getSecondCvNum())+" actionPerformed");
    int newVal = (((_value->text()).toInt())-mOffset)/mFactor;
    updatedTextField();
    prop->firePropertyChange("Value", NULL, (newVal));
    //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", QVariant(), (newVal)));
}

/** FocusListener implementations */
/*public*/ void SplitVariableValue::focusGained(/*FocusEvent*/QEvent* e) {
    if (logit->isDebugEnabled()) logit->debug("CV "+(getCvNum())+","+QString::number(getSecondCvNum())+" focusGained");
    enterField();
}

/*public*/ void SplitVariableValue::focusLost(/*FocusEvent*/QEvent* e) {
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" focusLost");
    exitField();
}

// to complete this class, fill in the routines to handle "Value" parameter
// and to read/write/hear parameter changes.
/*public*/ QString SplitVariableValue::getValueString() {
    // until 2.9.5, this was just the 1st CV value
    //int newVal = (((_value.text()).toInt())-mOffset)/mFactor;
    return _value->text();
}
/*public*/ void SplitVariableValue::setIntValue(int i) {
    // until 2.9.5, this was just the 1st CV value
    //setValue((i-mOffset)/mFactor);
    setValue(i);
}

/*public*/ int SplitVariableValue::getIntValue() {
    return (((_value->text()).toInt())-mOffset)/mFactor;
}

/*public*/ QVariant SplitVariableValue::getValueObject() {
    return (_value->text());
}

/*public*/ QWidget* SplitVariableValue::getCommonRep()  {
    if (getReadOnly())  {
        QLabel* r = new QLabel(_value->text());
        updateRepresentation(r);
        return r;
    } else
        return _value;
}

/*public*/ void SplitVariableValue::setValue(int value) {
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" enter setValue "+QString::number(value));
    int oldVal;
//    try {
        oldVal = ((_value->text()).toInt()-mOffset)/mFactor;
//    } catch (java.lang.NumberFormatException ex) { oldVal = -999; }
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" setValue with new value "+QString::number(value)+" old value "+QString::number(oldVal));
    _value->setText(QString::number( value*mFactor + mOffset));
    if (oldVal != value || getState() == VariableValue::UNKNOWN)
        actionPerformed(NULL);
    prop->firePropertyChange("Value", (oldVal), (value*mFactor + mOffset));
    //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", (oldVal), (value*mFactor + mOffset)));
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" exit setValue "+value);
}


// implement an abstract member to set colors
void SplitVariableValue::setColor(QColor c) {
    if (c.isValid()) _value->setBackground(c);
    else _value->setBackground(_defaultColor);
//    // prop.firePropertyChange("Value", NULL, NULL);
}

/*public*/ QWidget* SplitVariableValue::getNewRep(QString format)  {
    JTextField* value = new VarTextField(_value->getDocument(),_value->text(), 5, this);
    //value->setMaxLength(5);
    if (getReadOnly() || getInfoOnly()) {
        value->setReadOnly(false);
    }
    reps->append(value);
    return updateRepresentation(value);
}

/*public*/ void SplitVariableValue::setAvailable(bool a) {
    _value->setVisible(a);
    foreach (QWidget* c, *reps) c->setVisible(a);
    VariableValue::setAvailable(a);
}


/**
 * Notify the connected CVs of a state change from above
 * @param state
 */
/*public*/ void SplitVariableValue::setCvState(int state) {
    (_cvMap->value(getCvNum()))->setState(state);
}

/*public*/ bool SplitVariableValue::isChanged() {
    CvValue* cv1 = (_cvMap->value(getCvNum()));
    CvValue* cv2 = (_cvMap->value(QString::number(getSecondCvNum())));
    return (considerChanged(cv1)||considerChanged(cv2));
}

/*public*/ void SplitVariableValue::readChanges() {
     if (isToRead() && !isChanged())
        logit->debug("!!!!!!! unacceptable combination in readChanges: "+label());
     if (isChanged() || isToRead()) readAll();
}

/*public*/ void SplitVariableValue::writeChanges() {
     if (isToWrite() && !isChanged())
        logit->debug("!!!!!! unacceptable combination in writeChanges: "+label());
     if (isChanged() || isToWrite()) writeAll();
}

/*public*/ void SplitVariableValue::readAll() {
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" splitval read() invoked");
    setToRead(false);
    setBusy(true);  // will be reset when value changes
    //super.setState(READ);
    if (_progState != IDLE) logit->warn("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" programming state "+_progState+", not IDLE, in read()");
    _progState = READING_FIRST;
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" invoke CV read");
    (_cvMap->value(getCvNum()))->read(_status);
}

/*public*/ void SplitVariableValue::writeAll() {
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" write() invoked");
    if (getReadOnly()) logit->error("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" unexpected write operation when readOnly is set");
    setToWrite(false);
    setBusy(true);  // will be reset when value changes
    if (_progState != IDLE) logit->warn("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" Programming state "+_progState+", not IDLE, in write()");
    _progState = WRITING_FIRST;
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" invoke CV write");
    (_cvMap->value(getCvNum()))->write(_status);
}

// handle incoming parameter notification
/*public*/ void SplitVariableValue::propertyChange(PropertyChangeEvent* e) {
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" property changed event - name: "
                                        +e->getPropertyName());
    // notification from CV; check for Value being changed
    if (e->getPropertyName()==("Busy") && (e->getNewValue().toBool())==(false)) {
        // busy transitions drive the state
        switch (_progState) {
        case IDLE:  // no, just a CV update
            if (logit->isDebugEnabled()) logit->error("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" Busy goes false with state IDLE");
            return;
        case READING_FIRST:   // read first CV, now read second
            if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" Busy goes false with state READING_FIRST");
            // was the first read successful?
            if (getState() != UNKNOWN){
                _progState = READING_SECOND;
                (_cvMap->value(QString::number(getSecondCvNum())))->read(_status);
            // first read failed we're done!
            } else {
                if (logit->isDebugEnabled()) logit->debug("First read failed, abort second read");
                _progState = IDLE;
                setBusy(false);
            }
            return;
        case READING_SECOND:  // finally done, set not busy
            if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" Busy goes false with state READING_SECOND");
            _progState = IDLE;
            (_cvMap->value(getCvNum()))->setState(READ);
            (_cvMap->value(QString::number(getSecondCvNum())))->setState(READ);
            //super.setState(READ);
            setBusy(false);
            return;
        case WRITING_FIRST:  // no, just a CV update
            if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" Busy goes false with state WRITING_FIRST");
            _progState = WRITING_SECOND;
            (_cvMap->value(QString::number(getSecondCvNum())))->write(_status);
            return;
        case WRITING_SECOND:  // now done with complete request
            if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" Busy goes false with state WRITING_SECOND");
            _progState = IDLE;
            VariableValue::setState(STORED);
            setBusy(false);
            return;
        default:  // unexpected!
            logit->error("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" Unexpected state found: "+_progState);
            _progState = IDLE;
            return;
        }
    }
    else if (e->getPropertyName()==("State")) {
        CvValue* cv = _cvMap->value(getCvNum());
        if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" State changed to "+QString::number(cv->getState()));
        setState(cv->getState());
    }
    else if (e->getPropertyName()==("Value")) {
        // update value of Variable
        CvValue* cv0 = _cvMap->value(getCvNum());
        CvValue* cv1 = _cvMap->value(QString::number(getSecondCvNum()));
        int newVal = ((cv0->getValue()&lowerbitmask) >> lowerbitoffset)
            + (((cv1->getValue()&upperbitmask)*256)>>upperbitoffset);
        if (logit->isDebugEnabled())
            logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" set value to "+newVal+" based on cv0="+cv0->getValue()+" cv1="+cv1->getValue());
        setValue(newVal);  // check for duplicate done inside setVal
        if (logit->isDebugEnabled())
            logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" in property change after setValue call, cv0="+cv0->getValue()+" cv1="+cv1->getValue());
        // state change due to CV state change, so propagate that
        setState(cv0->getState());
        // see if this was a read or write operation
        switch (_progState) {
        case IDLE:  // no, just a CV update
            if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" Value changed with state IDLE");
            return;
        case READING_FIRST:  // yes, now read second
            if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" Value changed with state READING_FIRST");
            return;
        case READING_SECOND:  // now done with complete request
            if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" Value changed with state READING_SECOND");
            return;
        default:  // unexpected!
            logit->error("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" Unexpected state found: "+_progState);
            _progState = IDLE;
            return;
        }
    }
}

#if 0
/* Internal class extends a JTextField so that its color is consistent with
 * an underlying variable
 *
 * @author	Bob Jacobsen   Copyright (C) 2001
 * @version     $Revision: 21268 $
 */
/*public*/ class VarTextField extends JTextField {

    VarTextField(Document doc, QString text, int col, SplitVariableValue var) {
        super(doc, text, col);
        _var = var;
        // get the original color right
        setBackground(_var._value.getBackground());
        // listen for changes to ourself
        addActionListener(new java.awt.event.ActionListener() {
                /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
                    thisActionPerformed(e);
                }
            });
        addFocusListener(new java.awt.event.FocusListener() {
                /*public*/ void focusGained(FocusEvent e) {
                    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" focusGained");
                    enterField();
                }

                /*public*/ void focusLost(FocusEvent e) {
                    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+QString::number(getSecondCvNum())+" focusLost");
                    exitField();
                }
            });
        // listen for changes to original state
        _var.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
                /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
                    originalPropertyChanged(e);
                }
            });
    }

    SplitVariableValue _var;

    void thisActionPerformed(java.awt.event.ActionEvent e) {
        // tell original
        _var.actionPerformed(e);
    }

    void originalPropertyChanged(java.beans.PropertyChangeEvent e) {
        // update this color from original state
        if (e.getPropertyName()==("State")) {
            setBackground(_var._value.getBackground());
        }
    }

}
#endif
// clean up connections when done
/*public*/ void SplitVariableValue::dispose() {
    if (logit->isDebugEnabled()) logit->debug("dispose");
//    if (_value != NULL) _value->removeActionListener(this);
    (_cvMap->value(getCvNum()))->removePropertyChangeListener((PropertyChangeListener*)this);
    (_cvMap->value(QString::number(getSecondCvNum())))->removePropertyChangeListener((PropertyChangeListener*)this);

    _value = NULL;
    // do something about the VarTextField
}
