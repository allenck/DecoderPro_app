#include "splitvariablevalue.h"
#include "loggerfactory.h"
#include "cvutil.h"
#include "system.h"

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
        QMap<QString, CvValue *> *v, JLabel* status, QString stdname,
        QString pSecondCV, int pFactor, int pOffset, QString uppermask, QString extra1, QString extra2, QString extra3, QString extra4, QObject* parent)
  :  VariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent)
{
 //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname);
    logit = new Logger("SplitVariableValue");
    _minVal = 0;
 _maxVal = ~0;
 stepOneActions(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, minVal, maxVal, v, status, stdname, pSecondCV, pFactor, pOffset, uppermask, extra1, extra2, extra3, extra4);
 _name = name;
 _mask = mask; // will be converted to MaskArray to apply separate mask for each CV
 if (mask != "" && mask.contains(" ")) {
     _maskArray = mask.split(" "); // type accepts multiple masks for SplitVariableValue
 } else {
     _maskArray = QStringList();
     _maskArray.append(mask);
 }
 _cvNum = cvNum;
 _textField = new JTextField("0");
 _defaultColor = _textField->getBackground();
 _textField->setBackground(COLOR_UNKNOWN);
 mFactor = pFactor;
 mOffset = pOffset;
 // legacy format variables
 mSecondCV = pSecondCV;
 _uppermask = uppermask;

 // connect to the JTextField value
 //_textField.addActionListener(this);
 connect(_textField, &JTextField::editingFinished, [=]{actionPerformed();});
 //_textField.addFocusListener(this);
 connect(_textField, &JTextField::focusGained, [=]{
    logit->debug(tr("Variable=%1; focusGained").arg(_name));
            enterField();
 });
 connect(_textField, &JTextField::focusLost, [=]{
    logit->debug(tr("Variable=%1; focusLost").arg(_name));
            exitField();
 });

 logit->debug(tr("Variable=%1;comment=%2;cvName=%3;cvNum=%4;stdname=%5").arg(_name).arg(comment).arg(cvName).arg(_cvNum).arg(stdname));

 // upper bit offset includes lower bit offset, and MSB bits missing from upper part
 logit->debug(tr("Variable=%1; upper mask %2 had offsetVal=%3 so upperbitoffset=%4").arg(_name).arg(_uppermask).arg(offsetVal(_uppermask)).arg(offsetVal(_uppermask)));

 // set up array of used CVs
 cvList = QList<CvItem*>();

 QList<QString> nameList = CvUtil::expandCvList(_cvNum); // see if cvName needs expanding
 if (nameList.isEmpty()) {
     // primary CV
     QString tMask;
     if (!_maskArray.empty() && _maskArray.length() == 1) {
         logit->debug(tr("PrimaryCV mask=%1").arg(_maskArray[0]));
         tMask = _maskArray[0];
     } else {
         tMask = _mask; // mask supplied could be an empty string
     }
     cvList.append(new CvItem(_cvNum, tMask));

     if (pSecondCV != "" && pSecondCV != ("")) {
         cvList.append(new CvItem(pSecondCV, _uppermask));
     }
 } else {
     for (int i = 0; i < nameList.size(); i++) {
         cvList.append(new CvItem(nameList.at(i), _maskArray[qMin(i, _maskArray.length() - 1)]));
         // use last mask for all following CVs if fewer masks than the number of CVs listed were provided
         logit->debug(tr("Added mask #%1: %2").arg(i).arg(_maskArray[qMin(i, _maskArray.length() - 1)]));
     }
 }

 cvCount = cvList.size();

 for (int i = 0; i < cvCount; i++) {
     cvList.at(i)->startOffset = currentOffset;
     QString t = cvList.at(i)->cvMask;
     if (t.contains("V")) {
         currentOffset = currentOffset + t.lastIndexOf("V") - t.indexOf("V") + 1;
     } else {
         logit->error(tr("Variable=%1;cvName=%2;cvMask=%3 is an invalid bitmask").arg(_name).arg(cvList.at(i)->cvName).arg(cvList.at(i)->cvMask));
     }
     logit->debug(tr("Variable=%1;cvName=%2;cvMask=%3;startOffset=%4;currentOffset=%5").arg(_name).arg(cvList.at(i)->cvName).arg(cvList.at(i)->cvMask).arg(cvList.at(i)->startOffset).arg(currentOffset));

     // connect CV for notification
     CvValue* cv = _cvMap->value(cvList.at(i)->cvName);
     cvList.at(i)->thisCV = cv;
 }

 stepTwoActions();

 _textField->setColumns(_columns);

 // have to do when list is complete
 for (int i = 0; i < cvCount; i++) {
     cvList.at(i)->thisCV->addPropertyChangeListener((PropertyChangeListener*)this);
     cvList.at(i)->thisCV->setState(CvValue::FROMFILE);
 }
}

/**
 * Subclasses can override this to pick up constructor-specific attributes
 * and perform other actions before cvList has been built.
 *
 * @param name      name.
 * @param comment   comment.
 * @param cvName    cv name.
 * @param readOnly  true for read only, else false.
 * @param infoOnly  true for info only, else false.
 * @param writeOnly true for write only, else false.
 * @param opsOnly   true for ops only, else false.
 * @param cvNum     cv number.
 * @param mask      cv mask.
 * @param minVal    minimum value.
 * @param maxVal    maximum value.
 * @param v         hashmap of string and cv value.
 * @param status    status.
 * @param stdname   std name.
 * @param pSecondCV second cv (no longer preferred, specify in cv)
 * @param pFactor   factor.
 * @param pOffset   offset.
 * @param uppermask upper mask (no longer preferred, specify in mask)
 * @param extra1    extra 1.
 * @param extra2    extra 2.
 * @param extra3    extra 3.
 * @param extra4    extra 4.
 */
/*public*/ void SplitVariableValue::stepOneActions(QString name, QString comment, QString cvName,
        bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
        QString cvNum, QString mask, int minVal, int maxVal,
        QMap<QString, CvValue*>* v, JLabel* status, QString stdname,
        QString pSecondCV, int pFactor, int pOffset, QString uppermask, QString extra1, QString extra2, QString extra3, QString extra4) {
    if (extra3 != "") {
        _minVal = getValueFromText(extra3);
    }
    if (extra4 != "") {
        _maxVal = getValueFromText(extra4);
    }
}

/**
 * Subclasses can override this to invoke further actions after cvList has
 * been built.
 */
/*public*/ void SplitVariableValue::stepTwoActions() {
    if (currentOffset > bitCount) {
        QString eol = System::getProperty("line.separator");
        throw Error(
                "Decoder File parsing error:"
                + eol + "The Decoder Definition File specified \"" + _cvNum
                + "\" for variable \"" + _name + "\". This expands to:"
                + eol + "\"" + getCvDescription() + "\""
                + eol + "This requires " + currentOffset + " bits, which exceeds the " + bitCount
                + " bit capacity of the long integer used to store the variable."
                + eol + "The Decoder Definition File needs correction.");
    }
    _columns = cvCount * 2; //update column width now we have a better idea
}

/*public*/ QVector<CvValue*> SplitVariableValue::usesCVs() {
 QVector<CvValue*> theseCvs = QVector<CvValue*>(cvCount);
 for (int i = 0; i < cvCount; i++) {
     theseCvs[i] = cvList.at(i)->thisCV;
 }
 return theseCvs;
}

//@Override
/*public*/ QString SplitVariableValue::getCvNum() {
    QString retString = "";
    if (cvCount > 0) {
        retString = cvList.at(0)->cvName;
    }
    return retString;
}

//@Deprecated
/*public*/ QString SplitVariableValue::getSecondCvNum() {
    QString retString = "";
    if (cvCount > 1) {
        retString = cvList.at(1)->cvName;
    }
    return retString;
}

/*public*/ void SplitVariableValue::setToolTipText(QString t) {
VariableValue::setToolTipText(t);   // do default stuff
    _textField->setToolTip(t);  // set our value
}
///*public*/ int SplitVariableValue::getSecondCvNum() { return mSecondCV;}

// the connection is to cvNum and cvNum+1


/*public*/ QVariant SplitVariableValue::rangeVal() {
    return "Split value";
}

QString SplitVariableValue::getTextFromValue(long v) {
    return (QString::number(v));
}

QVector<int> SplitVariableValue::getCvValsFromTextField() {
    long newEntry;  // entered value
    try{
        newEntry = getValueFromText(_textField->text());
    } catch (NumberFormatException ex) {
        newEntry = 0;
    }

    // calculate resulting number
    long newVal = (newEntry - mOffset) / mFactor;
    logit->debug(tr("Variable=%1;newEntry=%2;newVal=%3 with Offset=%4 + Factor=%5 applied").arg(_name).arg(newEntry).arg(newVal).arg(mOffset).arg(mFactor));

    QVector<int> retVals = QVector<int>(cvCount);

    // extract individual values via masks
    for (int i = 0; i < cvCount; i++) {
        retVals[i] = (((int) (newVal >> cvList.at(i)->startOffset))
                & (maskValAsInt(cvList.at(i)->cvMask) >> offsetVal(cvList.at(i)->cvMask)));
    }
    return retVals;
}
/**
 * Contains numeric-value specific code.
 * <br><br>
 * Calculates new value for _textField and invokes
 * {@link #setLongValue(long) setLongValue(newVal)} to make and notify the
 * change
 *
 * @param intVals array of new CV values
 */
void SplitVariableValue::updateVariableValue(QVector<int> intVals) {

    long newVal = 0;
    for (int i = 0; i < intVals.length(); i++) {
        newVal = newVal | (((long) intVals[i]) << cvList.at(i)->startOffset);
        logit->debug(tr("Variable=%1; i=%2; newVal=%3").arg(_name).arg(i).arg(getTextFromValue(newVal)));
    }
    logit->debug(tr("Variable=%1; set value to %2").arg(_name).arg(newVal));
    setLongValue(newVal);  // check for duplicate is done inside setLongValue
    logit->debug(tr("Variable=%1; in property change after setValue call").arg(_name));
}

long SplitVariableValue::getValueFromText(QString s) {
    return (s.toLong());
}

void SplitVariableValue::enterField() {
    oldContents = _textField->text();
}

void SplitVariableValue::exitField() {
    // there may be a lost focus event left in the queue when disposed so protect
    if (_textField != NULL && oldContents!=(_textField->text())) {
        int newVal = (((_textField->text()).toInt())-mOffset)/mFactor;
        int oldVal = (((oldContents).toInt())-mOffset)/mFactor;
        updatedTextField();
        prop->firePropertyChange("Value", (oldVal), (newVal));
        //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", (oldVal), (newVal)));
    }
}

void SplitVariableValue::updatedTextField()
{
 QVector<int> retVals = getCvValsFromTextField();

 // combine with existing values via mask
 for (int j = 0; j < cvCount; j++) {
     int i = j;
     // special care needed if _textField is shrinking
     if (_fieldShrink) {
         i = (cvCount - 1) - j; // reverse CV updating order
     }
     logit->debug(tr("retVals[%1]=%2;cvList.get(%3).cvMask%4;offsetVal=%5").arg(i).arg(retVals[i]).arg(i).arg(cvList.at(i)->cvMask).arg(offsetVal(cvList.at(i)->cvMask)));
     int cvMask = maskValAsInt(cvList.at(i)->cvMask);
     CvValue* thisCV = cvList.at(i)->thisCV;
     int oldCvVal = thisCV->getValue();
     int newCvVal = (oldCvVal & ~cvMask)
             | ((retVals[i] << offsetVal(cvList.at(i)->cvMask)) & cvMask);
     logit->debug(tr("%1;cvMask=%2;oldCvVal=%3;retVals[%4]=%5;newCvVal=%6").arg(cvList.at(i)->cvName).arg(cvMask).arg(oldCvVal).arg(i).arg(retVals[i]).arg(newCvVal));

     // cv updates here trigger updated property changes, which means
     // we're going to get notified sooner or later.
     if (newCvVal != oldCvVal) {
         thisCV->setValue(newCvVal);
     }
 }
 logit->debug(tr("Variable=%1; exit updatedTextField").arg(_name));
}

/** ActionListener implementations */
/*public*/ void SplitVariableValue::actionPerformed(/*JActionEvent* e*/) {
    if (logit->isDebugEnabled()) logit->debug("CV "+(getCvNum())+","+getSecondCvNum()+" actionPerformed");
    int newVal = (((_textField->text()).toInt())-mOffset)/mFactor;
    updatedTextField();
    prop->firePropertyChange("Value", NULL, (newVal));
    //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", QVariant(), (newVal)));
}

/** FocusListener implementations */
/*public*/ void SplitVariableValue::focusGained(/*FocusEvent*/QEvent* e) {
    if (logit->isDebugEnabled()) logit->debug("CV "+(getCvNum())+","+getSecondCvNum()+" focusGained");
    enterField();
}

/*public*/ void SplitVariableValue::focusLost(/*FocusEvent*/QEvent* e) {
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+getSecondCvNum()+" focusLost");
    exitField();
}

// to complete this class, fill in the routines to handle "Value" parameter
// and to read/write/hear parameter changes.
/*public*/ QString SplitVariableValue::getValueString() {
    // until 2.9.5, this was just the 1st CV value
    //int newVal = (((_value.text()).toInt())-mOffset)/mFactor;
    return _textField->text();
}
/*public*/ void SplitVariableValue::setIntValue(int i) {
    // until 2.9.5, this was just the 1st CV value
    //setValue((i-mOffset)/mFactor);
    setValue(i);
}

/*public*/ int SplitVariableValue::getIntValue() {
    return (((_textField->text()).toInt())-mOffset)/mFactor;
}

/*public*/ QVariant SplitVariableValue::getValueObject() {
    return (_textField->text());
}

/*public*/ QWidget* SplitVariableValue::getCommonRep()  {
    if (getReadOnly())  {
        JLabel* r = new JLabel(_textField->text());
        updateRepresentation(r);
        return r;
    } else
        return _textField;
}

/*public*/ void SplitVariableValue::setLongValue(long value) {
    logit->debug(tr("Variable=%1; enter setValue %2").arg(_name).arg(value));
    long oldVal;
    try {
        oldVal = (getValueFromText(_textField->text()) - mOffset) / mFactor;
    } catch (NumberFormatException ex) {
        oldVal = -999;
    }
    logit->debug(tr("Variable=%1; setValue with new value %2 old value %3").arg(_name).arg(value).arg(oldVal));
    _textField->setText(getTextFromValue(value * mFactor + mOffset));
    if (oldVal != value || getState() == VariableValue::UNKNOWN) {
        actionPerformed(/*nullptr*/);
    }
    // TODO PENDING: the code used to fire value * mFactor + mOffset, which is a text representation;
    // but 'oldValue' was converted back using mOffset / mFactor making those two (new / old)
    // using different scales. Probably a bug, but it has been there from well before
    // the extended splitVal. Because of the risk of breaking existing
    // behaviour somewhere, deferring correction until at least the next test release.
    prop->firePropertyChange("Value", oldVal, value * mFactor + mOffset);
    logit->debug(tr("Variable=%1; exit setLongValue old=%2 new=%3").arg(_name).arg(oldVal).arg(value));
}

/*public*/ void SplitVariableValue::setValue(int value) {
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+getSecondCvNum()+" enter setValue "+QString::number(value));
    int oldVal;
//    try {
        oldVal = ((_textField->text()).toInt()-mOffset)/mFactor;
//    } catch (java.lang.NumberFormatException ex) { oldVal = -999; }
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+getSecondCvNum()+" setValue with new value "+QString::number(value)+" old value "+QString::number(oldVal));
    _textField->setText(QString::number( value*mFactor + mOffset));
    if (oldVal != value || getState() == VariableValue::UNKNOWN)
        actionPerformed(/*NULL*/);
    prop->firePropertyChange("Value", (oldVal), (value*mFactor + mOffset));
    //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", (oldVal), (value*mFactor + mOffset)));
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+getSecondCvNum()+" exit setValue "+value);
}


// implement an abstract member to set colors
void SplitVariableValue::setColor(QColor c) {
    if (c.isValid()) _textField->setBackground(c);
    else _textField->setBackground(_defaultColor);
//    // prop.firePropertyChange("Value", NULL, NULL);
}

/*public*/ QWidget* SplitVariableValue::getNewRep(QString format)  {
 JTextField* value = new SPVarTextField(_textField->getDocument(), _textField->text(), _columns, this);
 if (getReadOnly() || getInfoOnly()) {
     value->setEditable(false);
 }
 reps.append(value);
 return updateRepresentation(value);
}

/*public*/ void SplitVariableValue::setAvailable(bool a) {
    _textField->setVisible(a);
    foreach (QWidget* c, reps) c->setVisible(a);
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
    CvValue* cv2 = (_cvMap->value(getSecondCvNum()));
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
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+getSecondCvNum()+" splitval read() invoked");
    setToRead(false);
    setBusy(true);  // will be reset when value changes
    //super.setState(READ);
    if (_progState != IDLE) logit->warn("CV "+getCvNum()+","+getSecondCvNum()+" programming state "+_progState+", not IDLE, in read()");
    _progState = READING_FIRST;
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+getSecondCvNum()+" invoke CV read");
    (_cvMap->value(getCvNum()))->read(_status);
}

/*public*/ void SplitVariableValue::writeAll() {
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+getSecondCvNum()+" write() invoked");
    if (getReadOnly()) logit->error("CV "+getCvNum()+","+getSecondCvNum()+" unexpected write operation when readOnly is set");
    setToWrite(false);
    setBusy(true);  // will be reset when value changes
    if (_progState != IDLE) logit->warn("CV "+getCvNum()+","+getSecondCvNum()+" Programming state "+_progState+", not IDLE, in write()");
    _progState = WRITING_FIRST;
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+getSecondCvNum()+" invoke CV write");
    (_cvMap->value(getCvNum()))->write(_status);
}

/**
 * Assigns a priority value to a given state.
 *
 * @param state State to be converted to a priority value
 * @return Priority value from state, with UNKNOWN numerically highest
 */
//@SuppressFBWarnings(value = {"SF_SWITCH_NO_DEFAULT", "SF_SWITCH_FALLTHROUGH"}, justification = "Intentional fallthrough to produce correct value")
int SplitVariableValue::priorityValue(int state) {
    int value = 0;
    switch (state) {
        case AbstractValue::UNKNOWN:
            value++;
        //$FALL-THROUGH$
        case AbstractValue::DIFF:
            value++;
        //$FALL-THROUGH$
        case AbstractValue::EDITED:
            value++;
        //$FALL-THROUGH$
        case AbstractValue::FROMFILE:
            value++;
        //$FALL-THROUGH$
        default:
            //$FALL-THROUGH$
            return value;
    }
}

// handle incoming parameter notification
/*public*/ void SplitVariableValue::propertyChange(PropertyChangeEvent* e) {
    if (logit->isDebugEnabled()) logit->debug("CV "+getCvNum()+","+getSecondCvNum()+" property changed event - name: "
                                        +e->getPropertyName());
    // notification from CV; check for Value being changed
    if (e->getPropertyName() == ("Busy") && ( e->getNewValue().toBool())== (false)) {
     // busy transitions drive the state
     if (logit->isDebugEnabled() && _progState != IDLE) {
         logit->debug(tr("getState() = %1").arg((cvList.at(qAbs(_progState) - 1)->thisCV)->getState()));
     }

     if (_progState == IDLE) { // State machine is idle, so "Busy" transition is the result of a CV update by another source.
         // The source would be a Read/Write from either the CVs pane or another Variable with one or more overlapping CV(s).
         // It is definitely not an error condition, but needs to be ignored by this variable's state machine.
         logit->debug("Variable={}; Busy goes false with state IDLE", _name);
     } else if (_progState >= READING_FIRST) {   // reading CVs
         if ((cvList.at(qAbs(_progState) - 1)->thisCV)->getState() == READ) {   // was the last read successful?
             retry = 0;
             if (qAbs(_progState) < cvCount) {   // read next CV
                 _progState++;
                 if (logit->isDebugEnabled()) {
                     logit->debug(tr("Reading CV=%1").arg(cvList.at(qAbs(_progState) - 1)->cvName));
                 }
                 (cvList.at(qAbs(_progState) - 1)->thisCV)->read(_status);
             } else {  // finally done, set not busy
                 logit->debug(tr("Variable=%1; Busy goes false with success READING state %2").arg(_name).arg(_progState));
                 _progState = IDLE;
                 setBusy(false);
             }
         } else {   // read failed
             logit->debug(tr("Variable=%1; Busy goes false with failure READING state %1").arg(_name).arg(_progState));
             if (retry < RETRY_COUNT) { //have we exhausted retry count?
                 retry++;
                 (cvList.at(qAbs(_progState) - 1)->thisCV)->read(_status);
             } else {
                 _progState = IDLE;
                 setBusy(false);
                 if (RETRY_COUNT > 0) {
                     for (int i = 0; i < cvCount; i++) { // mark all CVs as unknown otherwise problems may occur
                         cvList.at(i)->thisCV->setState(AbstractValue::UNKNOWN);
                     }
                 }
             }
         }
     } else {  // writing CVs
         if ((cvList.at(qAbs(_progState) - 1)->thisCV)->getState() == STORED) {   // was the last read successful?
             if (qAbs(_progState) < cvCount) {   // write next CV
                 _progState--;
                 if (logit->isDebugEnabled()) {
                     logit->debug(tr("Writing CV=%1").arg(cvList.at(qAbs(_progState) - 1)->cvName));
                 }
                 (cvList.at(qAbs(_progState) - 1)->thisCV)->write(_status);
             } else {  // finally done, set not busy
                 logit->debug(tr("Variable=%1; Busy goes false with success WRITING state %2").arg(_name).arg(_progState));
                 _progState = IDLE;
                 setBusy(false);
             }
         } else {   // read failed we're done!
             logit->debug(tr("Variable=%1; Busy goes false with failure WRITING state %2").arg(_name).arg(_progState));
             _progState = IDLE;
             setBusy(false);
         }
     }
 } else if (e->getPropertyName() == ("State")) {
     logit->debug(tr("state change due to CV state change, so propagate that"));
     int varState = getState(); // AbstractValue.SAME;
     logit->debug(tr("%1 state was %2").arg(_name).arg(varState));
     for (int i = 0; i < cvCount; i++) {
         int state = cvList.at(i)->thisCV->getState();
         if (i == 0) {
             varState = state;
         } else if (priorityValue(state) > priorityValue(varState)) {
             varState = AbstractValue::UNKNOWN; // or should it be = state ?
         }
     }
     setState(varState);
     logit->debug(tr("%1 state set to %2").arg(_name).arg(varState));
 } else if (e->getPropertyName() == ("Value")) {
     // update value of Variable
     logit->debug("update value of Variable");

     QVector<int> intVals = QVector<int>(cvCount);

     for (int i = 0; i < cvCount; i++) {
         intVals[i] = (cvList.at(i)->thisCV->getValue() & maskValAsInt(cvList.at(i)->cvMask)) >> offsetVal(cvList.at(i)->cvMask);
     }

     updateVariableValue(intVals);

     logit->debug("state change due to CV value change, so propagate that");
     int varState = AbstractValue::SAME;
     for (int i = 0; i < cvCount; i++) {
         int state = cvList.at(i)->thisCV->getState();
         if (priorityValue(state) > priorityValue(varState)) {
             varState = state;
         }
     }
     setState(varState);
 }
}


/* Internal class extends a JTextField so that its color is consistent with
 * an underlying variable
 *
 * @author	Bob Jacobsen   Copyright (C) 2001
 * @version     $Revision: 21268 $
 */
///*public*/ class VarTextField extends JTextField {

    SPVarTextField::SPVarTextField(Document* doc, QString text, int col, SplitVariableValue* var)
     : JTextField(doc, text, col)
    {
        //super(doc, text, col);
        _var = var;
        // get the original color right
        setBackground(_var->_textField->getBackground());
        // listen for changes to ourself
        //        addActionListener(new java.awt.event.ActionListener() {
        //            @Override
        //            public void actionPerformed(java.awt.event.ActionEvent e) {
        //                thisActionPerformed(e);
        //            }
        //        });
                connect(this, &SPVarTextField::textEdited, [=]{
                 thisActionPerformed();
                });
        //        addFocusListener(new java.awt.event.FocusListener() {
        //            @Override
        //            public void focusGained(FocusEvent e) {
        //                if (log.isDebugEnabled()) {
        //                    log.debug("focusGained");
        //                }
        //                enterField();
        //            }
                 connect(this, &SPVarTextField::focusGained, [=]{
                   if (_var->logit->isDebugEnabled()) {
                       _var->logit->debug("focusGained");
                   }
                   enterField();
                 });

        //            @Override
        //            public void focusLost(FocusEvent e) {
        //                if (log.isDebugEnabled()) {
        //                    log.debug("focusLost");
        //                }
        //                exitField();
        //            }
        //        });
                 connect(this, &SPVarTextField::focusLost, [=]{
                   if (_var->logit->isDebugEnabled()) {
                       _var->logit->debug("focusLost");
                   }
                   leaveField();
                 });

        // listen for changes to original state
//        _var->addPropertyChangeListener(new java.beans.PropertyChangeListener() {
//                /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
          connect(this->_var->prop, &PropertyChangeSupport::propertyChange, [=](PropertyChangeEvent* e) {
                    originalPropertyChanged(e);
//                }
            });
    }

    //SplitVariableValue _var;

    void SPVarTextField::thisActionPerformed(/*java.awt.event.ActionEvent e*/) {
        // tell original
        _var->actionPerformed(/*e*/);
    }

    void SPVarTextField::originalPropertyChanged(PropertyChangeEvent* e) {
        // update this color from original state
        if (e->getPropertyName()==("State")) {
            setBackground(_var->_textField->getBackground());
        }
    }

//}

// clean up connections when done
/*public*/ void SplitVariableValue::dispose() {
    if (logit->isDebugEnabled()) logit->debug("dispose");
//    if (_textField != NULL) _textField->removeActionListener(this);
    (_cvMap->value(getCvNum()))->removePropertyChangeListener((PropertyChangeListener*)this);
    (_cvMap->value(getSecondCvNum()))->removePropertyChangeListener((PropertyChangeListener*)this);

    _textField = nullptr;
    _maskArray = QStringList();
    // do something about the VarTextField
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* SplitVariableValue::logit = LoggerFactory::getLogger("SplitVariableValue");
