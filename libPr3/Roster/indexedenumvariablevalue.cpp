#include "indexedenumvariablevalue.h"
#include "comboonradiobutton.h"
#include "combooffradiobutton.h"

//IndexedEnumVariableValue::IndexedEnumVariableValue(QObject *parent) :
//    VariableValue(parent)
//{
//}
/**
 * Extends VariableValue to represent a enumerated indexed variable->
 *
 * @author    Howard G. Penny   Copyright (C) 2005
 * @version   $Revision: 17977 $
 *
 */
// /*public*/ class IndexedEnumVariableValue extends VariableValue
//    implements ActionListener, PropertyChangeListener {

/*public*/ IndexedEnumVariableValue::IndexedEnumVariableValue(int row, QString name, QString comment, QString cvName,
                                bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                                QString cvNum, QString mask,
                                QMap<QString, CvValue*>* v, QLabel* status, QString stdname, QObject *parent) : VariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent)
{
 //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname);
 _row    = row;
 _itemArray = NULL;
 _valueArray = NULL;
 _value = NULL;
  comboCBs = new QList<IndexedComboCheckBox*>();
 comboVars = new QList<IVarComboBox*>();
 comboRBs = new QList<ComboRadioButtons*>();
 _progState = 0;
 logit = new Logger("IndexedEnumVariableValue");
 retries = 0;
}

/**
 * Create a NULL object.  Normally only used for tests and to pre-load classes.
 */
/*protected*/ IndexedEnumVariableValue::IndexedEnumVariableValue(QObject *parent) : VariableValue(parent)
{
 _itemArray = NULL;
 _valueArray = NULL;
 _value = NULL;
 _progState = 0;
 logit = new Logger("IndexedEnumVariableValue");
 retries = 0;
}


/*public*/ QVector<CvValue*>* IndexedEnumVariableValue::usesCVs() {
 //return new CvValue[]{_cvMap->value(getCvNum())};
 QVector<CvValue*>* list = new QVector<CvValue*>();
 list->append(_cvMap->value(getCvNum()));
 return list;
}

/*public*/ void IndexedEnumVariableValue::nItems(int n) {
    _itemArray = new QStringList();
    _valueArray = new QVector<int>();
    _nstored = 0;
}

/**
 * Create a new item in the enumeration, with an associated
 * value one more than the last item (or zero if this is the first
 * one added)
 * @param s  Name of the enumeration item
 */
/*public*/ void IndexedEnumVariableValue::addItem(QString s) {
    if (_nstored == 0) {
        addItem(s, 0);
    } else {
        addItem(s, _valueArray->at(_nstored-1)+1);
    }
}

/**
 * Create a new item in the enumeration, with a specified
 * associated value->
 * @param s  Name of the enumeration item
 */
/*public*/ void IndexedEnumVariableValue::addItem(QString s, int value) {
    if (_nstored == 0) {
        _minVal = value;
    }
    _valueArray->replace(_nstored, value);
    _itemArray->replace(_nstored++, s);
}

/*public*/ void IndexedEnumVariableValue::lastItem() {
    // we now know the maxVal, store it for whatever reason
    _maxVal = _valueArray->at(_nstored-1);
    _value = new QComboBox();
    _value ->addItems(*_itemArray);
    // finish initialization
//    _value->setActionCommand("8");
    _defaultColor = getBackground();
    setBackground(COLOR_UNKNOWN);
    // connect to the JComboBox model and the CV so we'll see changes.
//    _value->addActionListener(this);
    connect(_value, SIGNAL(currentIndexChanged(int)), this, SLOT(on_currentIndex_changed(int)));
    CvValue* cv = (_cvMap->value(getCvNum()));
    cv->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(cv, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    if (cv->getInfoOnly()) {
        cv->setState(CvValue::READ);
    } else {
        cv->setState(CvValue::FROMFILE);
    }
}
void IndexedEnumVariableValue::on_currentIndex_changed(int)
{
  actionPerformed(NULL);
}

/*public*/ void IndexedEnumVariableValue::setToolTipText(QString t) {
VariableValue::setToolTipText(t);   // do default stuff
    _value->setToolTip(t);  // set our value
}



/*public*/ QVariant IndexedEnumVariableValue::rangeVal() {
    return "enum: "+QString::number(_minVal)+" - "+QString::number(_maxVal);
}

/*public*/ void IndexedEnumVariableValue::actionPerformed(ActionEvent* e)
{
 if(e != NULL)
 {
    // see if this is from _value itself, or from an alternate rep.
    // if from an alternate rep, it will contain the value to select
    if (!(e->getActionCommand()==("8"))) {
        // is from alternate rep
        //_value->setSelectedItem(e->getActionCommand());
        _value->setItemText(_value->currentIndex(), e->getActionCommand());
    }
    if (logit->isDebugEnabled()) logit->debug("action event: "/*+e*/);
 }
 else
 {
  int i = _value->currentIndex();
 }
 // called for new values - set the CV as neede
 CvValue* cv = _cvMap->value(getCvNum());
 // compute new cv value by combining old and request
 int oldCv = cv->getValue();
 int newVal = getIntValue();
 int newCv = newValue(oldCv, newVal, getMask());
 if (newCv != oldCv)
 {
  cv->setValue(newCv); // to prevent CV going EDITED during loading of decoder file
  // notify
  prop->firePropertyChange("Value", QVariant(), QVariant(getIntValue()));
  //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", QVariant(), QVariant(getIntValue())));
 }
}

// to complete this class, fill in the routines to handle "Value" parameter
// and to read/write/hear parameter changes.
/*public*/ QString IndexedEnumVariableValue::getValueString() {
    return QString::number(_value->currentIndex());
}
/*public*/ void IndexedEnumVariableValue::setIntValue(int i) {
    selectValue(i);
}

/*public*/ QString IndexedEnumVariableValue::getTextValue() {
    return _value->currentText();
}

/**
 * Set to a specific value->
 *
 * This searches for the displayed value, and sets the
 * enum to that particular one->
 *
 * If the value is larger than any defined, a new one is created.
 * @param value
 */
/*protected*/ void IndexedEnumVariableValue::selectValue(int value) {
    if (value>256) logit->error("Saw unreasonable internal value: "+value);
    for (int i = 0; i<_valueArray->count(); i++)
        if (_valueArray->at(i)==value) {
            //found it, select it
            _value->setCurrentIndex(i);
            return;
        }

    // We can be commanded to a number that hasn't been defined.
    // But that's OK for certain applications.  Instead, we add them as needed
    logit->debug("Create new item with value "+QString::number(value)+" count was "+_value->count()
                    +" in "+label());
    _value->addItem("Reserved value "+QString::number(value));
    // and value array is too short
    QVector<int>* oldArray = _valueArray;
    //_valueArray = new int[oldArray.length+1];
    QVector<int>* _valueArray = new QVector<int>(oldArray->count()+1, 0);
    for (int i = 0; i<oldArray->count(); i++)
     _valueArray->replace(i, oldArray->at(i));
    _valueArray->replace(oldArray->count(), value);

    _value->setItemText(_value->currentIndex(),"Reserved value "+QString::number(value));
}

/*public*/ int IndexedEnumVariableValue::getIntValue() {
    if ((_value->currentIndex()>=_valueArray->count()) || _value->count()<0)
        logit->error("trying to get value "+QString::number(_value->count())+" too large"
                   +" for array length "+QString::number(_valueArray->count()));
    return _valueArray->at(_value->currentIndex());
}

/*public*/ QVariant IndexedEnumVariableValue::getValueObject() {
    return (_value->currentIndex());
}

/*public*/ QWidget* IndexedEnumVariableValue::getCommonRep()  { return _value; }

/*public*/ void IndexedEnumVariableValue::setValue(int value)
{
 int oldVal = getIntValue();
 selectValue(value);

 if ((oldVal != value) || (getState() == VariableValue::UNKNOWN))
 {
  prop->firePropertyChange("Value", QVariant(), QVariant(value));
  //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", QVariant(), QVariant(value)));
 }
}

/*public*/ QWidget* IndexedEnumVariableValue::getNewRep(QString format) {
    // sort on format type
    if (format==("checkbox")) {
        // this only makes sense if there are exactly two options
        IndexedComboCheckBox* b = new IndexedComboCheckBox(_value, this);
        comboCBs->append(b);
        updateRepresentation(b);
        if (!getAvailable()) b->setVisible(false);
        return b;
    }
    else if (format==("radiobuttons")) {
        ComboRadioButtons* b = new ComboRadioButtons(_value, this);
        comboRBs->append(b);
        updateRepresentation(b);
        return b;
    }
    else if (format==("onradiobutton")) {
        ComboRadioButtons* b = new ComboOnRadioButton(_value, this);
        comboRBs->append(b);
        updateRepresentation(b);
        return b;
    }
    else if (format==("offradiobutton")) {
        ComboRadioButtons* b = new ComboOffRadioButton(_value, this);
        comboRBs->append(b);
        updateRepresentation(b);
        return b;
    }
 else
 {
  // return a new JComboBox representing the same model
  IVarComboBox* b = new IVarComboBox( this);
  //b.setPreferredSize(new Dimension(284, b.getPreferredSize().height));
  comboVars->append(b);
  updateRepresentation(b);
  return b;
 }
}


// implement an abstract member to set colors
void IndexedEnumVariableValue::setColor(QColor c) {
    if (_value != NULL) {
//        if (c.isValid()) {
//            _value->setBackground(c);
//        }
//        else {
//            _value->setBackground(_defaultColor);
//        }
    }
}

/*public*/ void IndexedEnumVariableValue::setAvailable(bool a) {
    foreach (IndexedComboCheckBox* c, *comboCBs) c->setVisible(a);
    foreach (IVarComboBox* c, *comboVars) c->setVisible(a);
    foreach (ComboRadioButtons* c, *comboRBs) c->setVisible(a);
    VariableValue::setAvailable(a);
}

/**
 * Notify the connected CVs of a state change from above
 * @param state
 */
/*public*/ void IndexedEnumVariableValue::setCvState(int state) {
    (_cvMap->value(getCvNum()))->setState(state);
}

/*public*/ void IndexedEnumVariableValue::setToRead(bool state) {
    if (getInfoOnly() || getWriteOnly()) state = false;
    (_cvMap->value(getCvNum()))->setToRead(state);
}
/*public*/ bool IndexedEnumVariableValue::isToRead() { return getAvailable() && (_cvMap->value(getCvNum()))->isToRead(); }

/*public*/ void IndexedEnumVariableValue::setToWrite(bool state) {
    if (getInfoOnly() || getReadOnly()) state = false;
    (_cvMap->value(getCvNum()))->setToWrite(state);
}
/*public*/ bool IndexedEnumVariableValue::isToWrite() { return getAvailable() && (_cvMap->value(getCvNum()))->isToWrite(); }

/*public*/ bool IndexedEnumVariableValue::isChanged() {
    CvValue* cv = (_cvMap->value(getCvNum()));
    return considerChanged(cv);
}

/*public*/ void IndexedEnumVariableValue::readChanges() {
     if (isChanged()) readAll();
}

/*public*/ void IndexedEnumVariableValue::writeChanges() {
     if (isChanged()) writeAll();
}

/*public*/ void IndexedEnumVariableValue::readAll() {
    setBusy(true);  // will be reset when value changes
    setToRead(false);
    if (_progState != IDLE) logit->warn("Programming state "+QString::number(_progState)+", not IDLE, in read()");
     // lets skip the SI step if SI is not used
    if ((_cvMap->value(getCvNum()))->siVal() >= 0) {
        _progState = WRITING_PI4R;
    } else { // lets skip this step if SI is not used
        _progState = WRITING_SI4R;
    }
    retries = 0;
    if (logit->isDebugEnabled()) logit->debug("invoke PI write for CV read");
    // to read any indexed CV we must write the PI
    (_cvMap->value(getCvNum()))->writePI(_status);
}

/*public*/ void IndexedEnumVariableValue::writeAll() {
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
    // to write any indexed CV we must write the PI first
    (_cvMap->value(getCvNum()))->writePI(_status);
}

/*public*/ void IndexedEnumVariableValue::confirmAll() {
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
/*public*/ void IndexedEnumVariableValue::propertyChange(PropertyChangeEvent* e)
{
    if (logit->isDebugEnabled()) logit->debug("Property changed: "+e->getPropertyName());
    // notification from CV; check for Value being changed
    if (e->getPropertyName()==("Busy") && e->getNewValue().toBool()==(false))
    {
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
    } else if (e->getPropertyName()==("State")) {
        CvValue* cv = _cvMap->value(getCvNum());
        setState(cv->getState());
    } else if (e->getPropertyName()==("Value")) {
        // update value of Variable
        CvValue* cv = _cvMap->value(getCvNum());
        int newVal = (cv->getValue() & maskVal(getMask())) >> offsetVal(getMask());
        setValue(newVal);  // check for duplicate done inside setVal
    }
}



// clean up connections when done
/*public*/ void IndexedEnumVariableValue::dispose() {
    if (logit->isDebugEnabled()) logit->debug("dispose");
//    if (_value != NULL) _value->removeActionListener((ActionListener*)this);
    (_cvMap->value(getCvNum()))->removePropertyChangeListener((PropertyChangeListener*)this);

    for (int i = 0; i<comboCBs->size(); i++) {
        comboCBs->at(i)->dispose();
    }
    for (int i = 0; i<comboVars->size(); i++) {
        comboVars->at(i)->dispose();
    }
    for (int i = 0; i<comboRBs->size(); i++) {
        comboRBs->at(i)->dispose();
    }

    _value = NULL;
}

QColor IndexedEnumVariableValue::getBackground()
{
 //return getBackground();
    QColor c;
    QPalette p = _value->palette();
    QString ss = _value->styleSheet();
    c = p.color(QPalette::Background);
    if(ss == "")
      return c;
    int i = ss.indexOf("background-color");
    int j;
    if(i > 0)
    {
     i= ss.indexOf("rgb(")+4;
     j= ss.indexOf(",",i);
     int red =ss. mid(i,j-i).toInt();
     i=j+1;
     j = ss.indexOf(",",i);
     int green = ss.mid(i,j-i).toInt();
     i=j+1;
     j = ss.indexOf(")");
     int blue =  ss.mid(i,j-i).toInt();
     return QColor(red,green,blue);
    }
    return QColor();
}

void IndexedEnumVariableValue::setBackground(QColor c)
{
 QColor oldC = getBackground();
 if(oldC != c)
 {
  QString ss = QString("QComboBox { background-color : rgb(%1,%2,%3);}").arg(c.red()).arg(c.green()).arg(c.blue());
  _value->setStyleSheet(ss);
 }
}
IVarComboBox::IVarComboBox(/*ComboBoxModel* m,*/ IndexedEnumVariableValue* var)
{
 //super(m);
  log = new Logger("IVarComboBox");
 _var = var;
 _l = new IVCBPropertyChangeListener(this);
//        {
//                /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                    if (log.isDebugEnabled()) log.debug("VarComboBox saw property change: "+e);
//                    originalPropertyChanged(e);
//                }
//            };
    // get the original color right
//        setBackground(_var->_value->getBackground());
 // listen for changes to original state

 _var->addPropertyChangeListener(_l);
 connect(_var->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), _l, SLOT(propertyChange(PropertyChangeEvent*)));
}

void IVarComboBox::originalPropertyChanged(PropertyChangeEvent* e) {
    // update this color from original state
    if (e->getPropertyName()==("State")) {
//            setBackground(_var->_value->getBackground());
    }
}

/*public*/ void IVarComboBox::dispose() {
    if (_var != NULL && _l != NULL ) _var->removePropertyChangeListener(_l);
    _l = NULL;
    _var = NULL;
}

IVCBPropertyChangeListener::IVCBPropertyChangeListener(IVarComboBox* self)
{
 this->self = self;
}

/*public*/ void IVCBPropertyChangeListener::propertyChange(PropertyChangeEvent* e) {
    if (self->log->isDebugEnabled()) self->log->debug("VarComboBox saw property change: "+e->getPropertyName());
    self->originalPropertyChanged(e);
}
