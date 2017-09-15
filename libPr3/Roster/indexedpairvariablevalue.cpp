#include "indexedpairvariablevalue.h"
#include "vartextfield.h"
#include <QIntValidator>

//IndexedPairVariableValue::IndexedPairVariableValue(QObject *parent) :
//    VariableValue(parent)
//{
//}
/**
 * Extends VariableValue to represent a indexed variable
 * split across two indexed CVs.
 *
 * Factor is the multiplier of the value in the high order CV
 *
 * Value to put in High CV = (value in text field)/Factor
 * Value to put in Low CV = (value in text field) - High CV value
 *
 * Value to put in text field = ((value in High CV) * Factor) + Low CV
 *
 * @author   Howard G. Penny  Copyright (C) 2005
 * @version  $Revision: 18651 $
 *
 */
///*public*/ class IndexedPairVariableValue extends VariableValue
//    implements ActionListener, PropertyChangeListener, FocusListener {

/*public*/ IndexedPairVariableValue::IndexedPairVariableValue(QString name, QString comment, QString cvName,
                                     bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                                     QString cvNum, QString mask, int minVal, int maxVal,
                                     QMap<QString, CvValue*>* v, QLabel* status, QString stdname,
                                     QString pSecondCV, int pFactor, int pOffset, QString uppermask,
                                     bool upperFirst, QObject *parent)
    : VariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent)
{
    //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent);
    log = new Logger("IndexedPairVariableValue");
    _mask = mask;
    _uppermask = uppermask;
    _maxVal = maxVal;
    _minVal = minVal;
    mSecondCVname = pSecondCV;
    int len = 4;
    if (maxVal>999) len = 5;
    if (maxVal>9999) len = 6;
    _value = new JTextField("0",len);
    _value->setValidator(new QIntValidator(_minVal, _maxVal));
    _defaultColor = _value->getBackground();
    _value->setBackground(COLOR_UNKNOWN);
     _upperFirst = upperFirst;
     mFactor = pFactor;
     mOffset = pOffset;
     if (log->isDebugEnabled()) log->debug("CV "+getCvName()+","+(getSecondCvNum())+" mfactor "+QString::number(mFactor)+" and mOffset="+QString::number(mOffset));
     doLow = false;
     doHigh = false;


    // connect to the JTextField value, cv
//    _value->addActionListener(this);
    connect(_value, SIGNAL(editingFinished()), this, SLOT(actionPerformed()));
//    _value->addFocusListener(this);
    mSecondCVname = pSecondCV;
    //mSecondCVrow = secondCVrow;

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
    if (log->isDebugEnabled()) log->debug("CV "+(getCvNum())+","+(getSecondCvNum())+" upper mask "+uppermask+" had offsetVal="+uppermask+
        +" so upperbitoffset="+QString::number(upperbitoffset));

    // connect for notification
    CvValue* cv = (_cvMap->value(getCvName()));
    cv->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(cv, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    cv->setState(CvValue::FROMFILE);
    CvValue* cv1 = (_cvMap->value(mSecondCVname));
    cv1->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(cv1, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    cv1->setState(CvValue::FROMFILE);
}

/*public*/ QVector<CvValue*>* IndexedPairVariableValue::usesCVs() {
//    return new CvValue[]{
//         _cvMap->value(getCvNum()),
//         _cvMap->value(mSecondCVname)};
    QVector<CvValue*>* list = new QVector<CvValue*>();
    list->append(_cvMap->value(getCvName()));
    list->append(_cvMap->value(mSecondCVname));
    return list;
}


/*public*/ QString IndexedPairVariableValue::getSecondCvNum() { return mSecondCVname;}


/*public*/ void IndexedPairVariableValue::setToolTipText(QString t) {
VariableValue::setToolTipText(t);   // do default stuff
    _value->setToolTip(t);  // set our value
}

// the connection is to cvNum and cvNum+1


/*public*/ QVariant IndexedPairVariableValue::rangeVal() {
    return "Split value";
}

void IndexedPairVariableValue::enterField() {
    oldContents = _value->text();
}

void IndexedPairVariableValue::exitField() {
    // there may be a lost focus event left in the queue when disposed so protect
    if (_value != NULL && oldContents!=(_value->text())) {
        int newVal = (_value->text()).toInt();
        int oldVal = (oldContents).toInt();
        updatedTextField();
        prop->firePropertyChange("Value", (oldVal),
                                (newVal));
        //emit notifyPropertyChange(new PropertyChangeEvent(this,"Value", (oldVal),
//                                                          (newVal)));
    }
}

void IndexedPairVariableValue::updatedTextField() {
    if (log->isDebugEnabled()) log->debug("CV "+(getCvNum())+","+(getSecondCvNum())+" enter updatedTextField in SplitVal");
    // called for new values - set the CV as needed
    CvValue* cv1 = _cvMap->value(getCvNum());
    CvValue* cv2 = _cvMap->value(getSecondCvNum());

    int newEntry;  // entered value
//    try {
        newEntry = (_value->text()).toInt();
//    }
//    catch (java.lang.NumberFormatException ex) { newEntry = 0; }

    // calculate resulting number
    int newVal = (newEntry-mOffset)/mFactor;

    // combine with existing values via mask
    if (log->isDebugEnabled())
        log->debug("CV "+(getCvNum())+","+(getSecondCvNum())+" lo cv was "+QString::number(cv1->getValue())+" mask="+lowerbitmask+" offset="+lowerbitoffset);
    int newCv1 = ( (newVal << lowerbitoffset) & lowerbitmask )
                | (~lowerbitmask & cv1->getValue());

    if (log->isDebugEnabled())
        log->debug("CV "+(getCvNum())+","+(getSecondCvNum())+" hi cv was "+QString::number(cv2->getValue())+" mask="+QString::number(upperbitmask)+" offset="+QString::number(upperbitoffset));
    int newCv2 = (((newVal << upperbitoffset)>>8)&upperbitmask)
                | (~upperbitmask & cv2->getValue());
    if (log->isDebugEnabled()) log->debug("CV "+(getCvNum())+","+(getSecondCvNum())+" new value "+newVal+" gives first="+newCv1+" second="+newCv2);

    // cv updates here trigger updated property changes, which means
    // we're going to get notified sooner or later.
    cv1->setValue(newCv1);
    cv2->setValue(newCv2);
    if (log->isDebugEnabled()) log->debug("CV "+getCvNum()+","+(getSecondCvNum())+" exit updatedTextField");

}

/** ActionListener implementations */
/*public*/ void IndexedPairVariableValue::actionPerformed(ActionEvent* /*e*/) {
    if (log->isDebugEnabled()) log->debug("CV "+getCvNum()+","+(getSecondCvNum())+" actionPerformed");
    int newVal = ((_value->text().toInt())-mOffset)/mFactor;
    updatedTextField();
    prop->firePropertyChange("Value", NULL, (newVal));
    //emit notifyPropertyChange(new PropertyChangeEvent(this,"Value", QVariant(), (newVal)));
}

/** FocusListener implementations */
/*public*/ void IndexedPairVariableValue::focusGained(/*FocusEvent*/QEvent* e) {
    if (log->isDebugEnabled()) log->debug("CV "+getCvNum()+","+(getSecondCvNum())+" focusGained");
    enterField();
}

/*public*/ void IndexedPairVariableValue::focusLost(/*FocusEvent*/QEvent* e) {
    if (log->isDebugEnabled()) log->debug("CV "+getCvNum()+","+(getSecondCvNum())+" focusLost");
    exitField();
}

// to complete this class, fill in the routines to handle "Value" parameter
// and to read/write/hear parameter changes.
/*public*/ QString IndexedPairVariableValue::getValueQString() {
    // until 2.13.1-dev, this was just the 1st CV value
    //int newVal = (_value->text()).toInt())-mOffset)/mFactor;
    return _value->text();
}
/*public*/ void IndexedPairVariableValue::setIntValue(int i) {
    // until 2.13.1-dev, this was just the 1st CV value
    //setValue((i-mOffset)/mFactor);
    setValue(i);
}

/*public*/ int IndexedPairVariableValue::getIntValue() {
    return (_value->text().toInt()-mOffset)/mFactor;
}

/*public*/ QVariant IndexedPairVariableValue::getValueObject() {
    return (_value->text());
}

/*public*/ QWidget* IndexedPairVariableValue::getCommonRep()  {
    if (getReadOnly())  {
        QLabel* r = new QLabel(_value->text());
        updateRepresentation(r);
        return r;
    } else
        return _value;
}

/*public*/ void IndexedPairVariableValue::setValue(int value) {
    if (log->isDebugEnabled()) log->debug("CV "+getCvNum()+","+(getSecondCvNum())+" enter setValue "+value);
    int oldVal;
//    try {
        oldVal = (_value->text().toInt()-mOffset)/mFactor;
//    } catch (java.lang.NumberFormatException ex) { oldVal = -999; }
    if (log->isDebugEnabled()) log->debug("CV "+getCvNum()+","+(getSecondCvNum())+" setValue with new value "+value+" old value "+oldVal);
    _value->setText(QString::number( value*mFactor + mOffset));
 if (oldVal != value || getState() == VariableValue::UNKNOWN)
  actionPerformed(NULL);
 prop->firePropertyChange("Value", (oldVal), (value*mFactor + mOffset));
 //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", (oldVal), (value*mFactor + mOffset)));
 if (log->isDebugEnabled()) log->debug("CV "+getCvNum()+","+(getSecondCvNum())+" exit setValue "+value);
}

// implement an abstract member to set colors
void IndexedPairVariableValue::setColor(QColor c) {
//    if (c.isValid()) _value.setBackground(c);
//    else _value.setBackground(_defaultColor);
}

/*public*/ QWidget* IndexedPairVariableValue::getNewRep(QString format)  {
    JTextField* value = new VarTextField(_value->getDocument(),_value->text(), 3, this);
    value->setValidator(new QIntValidator(0,255));
    value->setMaxLength(3);
    if (getReadOnly() || getInfoOnly()) {
        value->setReadOnly(true);
    }
    reps->append(value);
    updateRepresentation(value);
    return value;
}

/*public*/ void IndexedPairVariableValue::setAvailable(bool a) {
    _value->setVisible(a);
    foreach (QWidget* c, *reps) c->setVisible(a);
    VariableValue::setAvailable(a);
}




/**
 * Notify the connected CVs of a state change from above
 * @param state
 */
/*public*/ void IndexedPairVariableValue::setCvState(int state) {
    (_cvMap->value(getCvNum()))->setState(state);
}

/*public*/ void IndexedPairVariableValue::setToRead(bool state) {
    if (getInfoOnly() || getWriteOnly() || !getAvailable()) state = false;
    (_cvMap->value(getCvNum()))->setToRead(state);
    (_cvMap->value(mSecondCVname))->setToRead(state);
}
/*public*/ bool IndexedPairVariableValue::isToRead() {
     return getAvailable() &&
             ( (_cvMap->value(getCvNum()))->isToRead() || (_cvMap->value(mSecondCVname))->isToRead() );
}

/*public*/ void IndexedPairVariableValue::setToWrite(bool state) {
    if (getInfoOnly() || getReadOnly() || !getAvailable()) state = false;
    (_cvMap->value(getCvNum()))->setToWrite(state);
    (_cvMap->value(mSecondCVname))->setToWrite(state);
}
/*public*/ bool IndexedPairVariableValue::isToWrite() {
    return getAvailable() &&
            ( (_cvMap->value(getCvNum()))->isToWrite() || (_cvMap->value(mSecondCVname))->isToWrite() );
}

/*public*/ bool IndexedPairVariableValue::isChanged() {
    CvValue* cv1 = (_cvMap->value(getCvNum()));
    CvValue* cv2 = (_cvMap->value(mSecondCVname));
    return (considerChanged(cv1)||considerChanged(cv2));
}

/*public*/ void IndexedPairVariableValue::readChanges() {
    if (isChanged()) readAll();
}

/*public*/ void IndexedPairVariableValue::writeChanges() {
    if (isChanged()) writeAll();
}

/*public*/ void IndexedPairVariableValue::readAll()
{
 if (_upperFirst)
 {
  programmingLow = false;
  doLow = true;
  doHigh = false;
 }
 else
 {
  programmingLow = true;
  doLow = false;
  doHigh = true;
 }
 doRead();
}
/*public*/ void IndexedPairVariableValue::doRead() {
        setBusy(true);  // will be reset when value changes
        setToRead(false);
        if (_progState != IDLE) log->warn("Programming state "+QString::number(_progState)+", not IDLE, in read()");
        // lets skip the SI step if SI is not used
        if (log->isDebugEnabled()) log->debug(tr("doRead with programmingLow ")+(programmingLow?"true":"false")+" "+getCvName()+" "+mSecondCVname);
        if ((_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->siVal() >= 0) {
            _progState = WRITING_PI4R;
        }
        else {
            _progState = WRITING_SI4R;
        }
        retries = 0;
        if (log->isDebugEnabled()) log->debug("invoke PI write for CV read");
        // to read any indexed CV we must write the PI
        (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->writePI(_status);
    }
/*public*/ void IndexedPairVariableValue::writeAll() {
    if (getReadOnly()) {
        log->error("unexpected write operation when readOnly is set");
    }

    if (_upperFirst) {
        programmingLow = false;
        doLow = true;
        doHigh = false;
    } else {
        programmingLow = true;
        doLow = false;
        doHigh = true;
    }
    doWrite();

}
/*public*/ void IndexedPairVariableValue::doWrite() {
       setBusy(true);  // will be reset when value changes
       setToWrite(false);
       if (_progState != IDLE) log->warn("Programming state "+QString::number(_progState)+", not IDLE, in write()");
       // lets skip the SI step if SI is not used
       if ((_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->siVal() >= 0) {
           _progState = WRITING_PI4W;
       } else {
           _progState = WRITING_SI4W;
       }
       retries = 0;
       if (log->isDebugEnabled()) log->debug(tr("invoke PI write for CV write ")+(programmingLow?"true":"false")+" "+QString::number(_progState));
       // to write any indexed CV we must write the PI
       (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->writePI(_status);
   }
/*public*/ void IndexedPairVariableValue::confirmAll()
{
 if (_upperFirst)
 {
  programmingLow = false;
  doLow = true;
  doHigh = false;
 }
 else
 {
  programmingLow = true;
  doLow = false;
  doHigh = true;
 }

 setBusy(true);  // will be reset when value changes
 setToRead(false);
 if (_progState != IDLE) log->warn("Programming state "+QString::number(_progState)+", not IDLE, in confirm()");
            // lets skip the SI step if SI is not used
            if ((_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->siVal() >= 0) {
                _progState = WRITING_PI4C;
            }
            else {
                _progState = WRITING_SI4C;
            }
            retries = 0;
            if (log->isDebugEnabled()) log->debug("invoke PI write for CV confirm");
            // to read any indexed CV we must write the PI
            (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->writePI(_status);
        }

// handle incoming parameter notification
/*public*/ void IndexedPairVariableValue::propertyChange(PropertyChangeEvent* e) {
    if (log->isDebugEnabled()) log->debug("property changed event - name: "
                                        +e->getPropertyName());
    // notification from CV; check for Value being changed
    if (e->getPropertyName()==("Busy") && (e->getNewValue())==(false)) {
        // busy transitions drive the state
        switch (_progState) {
            case IDLE:  // no, just a CV update
                if (log->isDebugEnabled()) log->error("Busy goes false with state IDLE");
                return;
            case WRITING_PI4R:   // have written the PI, now write SI if needed
            case WRITING_PI4C:
            case WRITING_PI4W:
                if (log->isDebugEnabled()) log->debug("Busy goes false with state WRITING_PI");

                // check for success
                if ((retries < RETRY_MAX)
                    && ( (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->getState() != CvValue::STORED) ) {
                    // need to retry on error; leave progState as it was
                    log->debug("retry");
                    retries++;
                    (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->writePI(_status);
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
                (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->writeSI(_status);
                return;
            case WRITING_SI4R:
            case WRITING_SI4C:
            case WRITING_SI4W:  // have written SI if needed, now read or write CV
                if (log->isDebugEnabled()) log->debug("Busy goes false with state WRITING_SI");

                // check for success
                if ((retries < RETRY_MAX)
                    && ( (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->getState() != CvValue::STORED) ) {
                    // need to retry on error; leave progState as it was
                    log->debug("retry");
                    retries++;
                    (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->writeSI(_status);
                    return;
                }
                // success, move on to next
                retries = 0;

                if (_progState == WRITING_SI4R ) {
                    _progState = READING_CV;
                    (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->readIcV(_status);
                } else if (_progState == WRITING_SI4C ) {
                    _progState = COMPARE_CV;
                    (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->confirmIcV(_status);
                } else {
                    _progState = WRITING_CV;
                    (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->writeIcV(_status);
                }
                return;
            case READING_CV:  // now done with the read request
                if (log->isDebugEnabled()) log->debug("Finished reading the Indexed CV");

                // check for success
                if ((retries < RETRY_MAX)
                    && ( (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->getState() != CvValue::READ) ) {
                    // need to retry on error; leave progState as it was
                    log->debug("retry");
                    retries++;
                    (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->readIcV(_status);
                    return;
                }
                // success, move on to next
                retries = 0;

                _progState = IDLE;
                if (programmingLow) {
                    programmingLow = false;
                    readAll();
                } else {
                    programmingLow = true;
                    setBusy(false);
                }
                return;
            case COMPARE_CV:  // now done with the read request
                if (log->isDebugEnabled()) log->debug("Finished reading the Indexed CV for compare");

                // check for success SAME or DIFF?
                if ((retries < RETRY_MAX)
                        && (( _cvMap->value(programmingLow ? getCvName() : mSecondCVname))
                                ->getState() != CvValue::SAME)
                                && (( _cvMap->value(programmingLow ? getCvName() : mSecondCVname))
                                        ->getState() != CvValue::DIFF)) {
                    // need to retry on error; leave progState as it was
                    log->debug("retry");
                    retries++;
                    (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->confirmIcV(_status);
                }
                return;
            case WRITING_CV:  // now done with the write request
                if (log->isDebugEnabled()) log->debug("Finished writing the Indexed CV");

                // check for success
                if ((retries < RETRY_MAX)
                    && ( (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->getState() != CvValue::STORED) ) {
                    // need to retry on error; leave progState as it was
                    log->debug("retry");
                    retries++;
                    (_cvMap->value(programmingLow ? getCvName() : mSecondCVname))->writeIcV(_status);
                    return;
                }
                // success, move on to next
                retries = 0;

                _progState = IDLE;
                if (programmingLow) {
                    programmingLow = false;
                    writeAll();
                } else {
                    programmingLow = true;
                    VariableValue::setState(STORED);
                    setBusy(false);
                }
                return;
            default:  // unexpected!
                log->error("Unexpected state found: "+_progState);
                _progState = IDLE;
                return;
        }
    }

    else if (e->getPropertyName()==("State")) {
        CvValue* cvLow = _cvMap->value(getCvNum());
        CvValue* cvHigh = _cvMap->value(mSecondCVname);
        if (log->isDebugEnabled()) log->debug("CV State changed to "+QString::number(cvLow->getState()));
        if (cvHigh->getState() == VariableValue::UNKNOWN) {
            if (cvLow->getState() == VariableValue::EDITED) {
                setState(VariableValue::EDITED);
            } else {
                setState(VariableValue::UNKNOWN);
            }
        } else {
            setState(cvLow->getState());
        }
    }
    else if (e->getPropertyName()==("Value")) {
        // update value of Variable
        CvValue* cv0 = _cvMap->value(getCvNum());
        CvValue* cv1 = _cvMap->value(mSecondCVname);
        int newVal = ((cv0->getValue()&lowerbitmask) >> lowerbitoffset)
            + (((cv1->getValue()&upperbitmask)*256)>>upperbitoffset);
        if (log->isDebugEnabled())
            log->debug("CV "+getCvNum()+","+(getSecondCvNum())+" set value to "+newVal+" based on cv0="+cv0->getValue()+" cv1="+cv1->getValue());
        setValue(newVal);  // check for duplicate done inside setVal
        if (log->isDebugEnabled())
            log->debug("CV "+getCvNum()+","+(getSecondCvNum())+" in property change after setValue call, cv0="+cv0->getValue()+" cv1="+cv1->getValue());
        // state change due to CV state change, so propagate that
        if (cv1->getState() == VariableValue::UNKNOWN) {
            if (cv0->getState() == VariableValue::EDITED) {
                setState(VariableValue::EDITED);
            } else {
                setState(VariableValue::UNKNOWN);
            }
        } else {
            setState(cv0->getState());
        }
    }
}

#if 0
/* Internal class extends a JTextField so that its color is consistent with
 * an underlying variable
 *
 * @author	Bob Jacobsen   Copyright (C) 2001
 * @version     $Revision: 18651 $
 */
/*public*/ class VarTextField : QLineEdit {

    VarTextField(Document doc, QString text, int col, IndexedPairVariableValue var) {
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
                if (log->isDebugEnabled()) log->debug("focusGained");
                enterField();
            }

            /*public*/ void focusLost(FocusEvent e) {
                if (log->isDebugEnabled()) log->debug("focusLost");
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

    IndexedPairVariableValue _var;

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

};
#endif
// clean up connections when done
/*public*/ void IndexedPairVariableValue::dispose() {
    if (log->isDebugEnabled()) log->debug("dispose");
    if (_value != NULL) {
//        _value->removeActionListener(this);
//        _value->removeFocusListener(this);
//        _value->removePropertyChangeListener((PropertyChangeListener*)this);
        _value = NULL;
    }
    (_cvMap->value(getCvNum()))->removePropertyChangeListener((PropertyChangeListener*)this);
    (_cvMap->value(mSecondCVname))->removePropertyChangeListener((PropertyChangeListener*)this);
}
