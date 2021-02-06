#include "longaddrvariablevalue.h"
#include "actionlistener.h"
#include <QIntValidator>
#include "loggerfactory.h"

//LongAddrVariableValue::LongAddrVariableValue(QObject *parent) :
//    VariableValue(parent)
//{
//}
/**
 * Extends VariableValue to represent a NMRA long address
 * @author			Bob Jacobsen   Copyright (C) 2001, 2002
 * @version			$Revision: 17977 $
 *
 */
// /*public*/ class LongAddrVariableValue extends VariableValue
//    implements ActionListener, PropertyChangeListener, FocusListener {

/*public*/ LongAddrVariableValue::LongAddrVariableValue(QString name, QString comment, QString cvName,
                             bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                             QString cvNum, QString mask, int minVal, int maxVal,
                             QMap<QString, CvValue*>* v, JLabel* status, QString stdname, QObject *parent)
    : VariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent)


{
 //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent);
    logit = new Logger("LongAddrVariableValue");
    _maxVal = maxVal;
    _minVal = minVal;
    _value = new JTextField("0", 5);
    _defaultColor = _value->getBackground();
    _value->setBackground(COLOR_UNKNOWN);
    _value->setValidator(new QIntValidator(_minVal, _maxVal));
    // connect to the JTextField value, cv
//    _value->addActionListener(this);
    connect(_value, SIGNAL(editingFinished()), this, SLOT(actionPerformed()));
//    _value->addFocusListener(this);
    // connect for notification
    CvValue* cv = (_cvMap->value(getCvNum()));
    cv->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(cv, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    cv->setState(CvValue::FROMFILE);
    CvValue* cv1 = (_cvMap->value(QString::number(getCvNum().toInt()+1)));
    cv1->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(cv1, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    cv1->setState(CvValue::FROMFILE);
    oldContents = "";
    _progState = 0;
    connect(_value, SIGNAL(editingFinished()), this, SLOT(textChanged()));
}

/*public*/ QVector<CvValue *> LongAddrVariableValue::usesCVs()
{
 //return new CvValue[]{
 QVector<CvValue*> list = QVector<CvValue*>(2, NULL);
 list.replace(0, _cvMap->value(getCvNum()));
 list.replace(1, _cvMap->value(QString::number(getCvNum().toInt()+1)));
 return list;
}

/*public*/ void LongAddrVariableValue::setToolTipText(QString t)
{
 VariableValue::setToolTipText(t);   // do default stuff
 _value->setToolTip(t);  // set our value
}

// the connection is to cvNum and cvNum+1

/*public*/ QVariant LongAddrVariableValue::rangeVal()
{
 return "Long address";
}


void LongAddrVariableValue::enterField()
{
 oldContents = _value->text();
}
void LongAddrVariableValue::exitField()
{
 // this _can_ be invoked after dispose, so protect
 if (_value != NULL && oldContents!=(_value->text()))
 {
  int newVal = (_value->text()).toInt();
  int oldVal = (oldContents).toInt();
  updatedTextField();
  prop->firePropertyChange("Value", QVariant(oldVal), QVariant(newVal));
  //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", QVariant(oldVal), QVariant(newVal)));
 }
}

void LongAddrVariableValue::updatedTextField() {
    if (logit->isDebugEnabled()) logit->debug("actionPerformed");
    // called for new values - set the CV as needed
    CvValue* cv17 = _cvMap->value(getCvNum());
    CvValue* cv18 = _cvMap->value(QString::number(getCvNum().toInt()+1));
    // no masking involved for long address
    int newVal;
//    try {
        newVal = (_value->text()).toInt();
//    }
//    catch (java.lang.NumberFormatException ex) { newVal = 0; }

    // no masked combining of old value required, as this fills the two CVs
    int newCv17 = ((newVal/256)&0x3F) | 0xc0;
    int newCv18 = newVal & 0xFF;
    cv17->setValue(newCv17);
    cv18->setValue(newCv18);
    if (logit->isDebugEnabled()) logit->debug("new value "+QString::number(newVal)+" gives CV17="+QString::number(newCv17)+" CV18="+QString::number(newCv18));
}

/** ActionListener implementations */
/*public*/ void LongAddrVariableValue::actionPerformed(/*JActionEvent* e*/)
{
 if (logit->isDebugEnabled()) logit->debug("actionPerformed");
 int newVal = (_value->text()).toInt();
 updatedTextField();
 prop->firePropertyChange("Value", QVariant(), QVariant(newVal));
 //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", QVariant(), QVariant(newVal)));
}

/** FocusListener implementations */
/*public*/ void LongAddrVariableValue::focusGained(/*FocusEvent*/ QEvent* e) {
    if (logit->isDebugEnabled()) logit->debug("focusGained");
    enterField();
}

/*public*/ void LongAddrVariableValue::focusLost(/*FocusEvent*/QEvent* e) {
    if (logit->isDebugEnabled()) logit->debug("focusLost");
    exitField();
}

// to complete this class, fill in the routines to handle "Value" parameter
// and to read/write/hear parameter changes.
/*public*/ QString LongAddrVariableValue::getValueString() {
    return _value->text();
}
/*public*/ void LongAddrVariableValue::setIntValue(int i) {
    setValue(i);
}

/*public*/ int LongAddrVariableValue::getIntValue() {
    return (_value->text()).toInt();
}

/*public*/ QVariant LongAddrVariableValue::getValueObject() {
    return (_value->text());
}

/*public*/ QWidget* LongAddrVariableValue::getCommonRep()  {
    if (getReadOnly())  {
        QLabel* r = new QLabel(_value->text());
        updateRepresentation(r);
        return r;
    } else
        return _value;
}
/*public*/ void LongAddrVariableValue::setValue(int value)
{
 int oldVal;
//    try {
 oldVal = (_value->text()).toInt();
//    }
//    catch (java.lang.NumberFormatException ex) { oldVal = -999; }
 if (logit->isDebugEnabled()) logit->debug("setValue with new value "+QString::number(value)+" old value "+QString::number(oldVal));
 _value->setText(QString::number(value));
 if (oldVal != value || getState() == VariableValue::UNKNOWN)
  actionPerformed(/*NULL*/);
 prop->firePropertyChange("Value", QVariant(oldVal), QVariant(value));
 //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", QVariant(oldVal), QVariant(value)));
}

// implement an abstract member to set colors
void LongAddrVariableValue::setColor(QColor c)
{
 if (c .isValid()) _value->setBackground(c);
 else _value->setBackground(_defaultColor);
    // prop.firePropertyChange("Value", NULL, NULL);
}

/*public*/ QWidget* LongAddrVariableValue::getNewRep(QString format)
{
 return updateRepresentation(new LAVarTextField(_value->getDocument(), _value->text(), 5, this));
}

/**
 * Notify the connected CVs of a state change from above
 * @param state
 */
/*public*/ void LongAddrVariableValue::setCvState(int state)
{
 (_cvMap->value(getCvNum()))->setState(state);
}

/*public*/ bool LongAddrVariableValue::isChanged()
{
 CvValue* cv1 = (_cvMap->value(getCvNum()));
 CvValue* cv2 = (_cvMap->value(QString::number(getCvNum().toInt()+1)));
 return (considerChanged(cv1)||considerChanged(cv2));
}

/*public*/ void LongAddrVariableValue::setToRead(bool state) {
    (_cvMap->value(getCvNum()))->setToRead(state);
    (_cvMap->value(QString::number(getCvNum().toInt()+1)))->setToRead(state);
}

/*public*/ bool LongAddrVariableValue::isToRead() {
    return (_cvMap->value(getCvNum()))->isToRead() || (_cvMap->value(QString::number(getCvNum().toInt()+1)))->isToRead();
}

/*public*/ void LongAddrVariableValue::setToWrite(bool state) {
    (_cvMap->value(getCvNum()))->setToWrite(state);
    (_cvMap->value(QString::number(getCvNum().toInt()+1)))->setToWrite(state);
}

/*public*/ bool LongAddrVariableValue::isToWrite() {
    return (_cvMap->value(getCvNum()))->isToWrite() || (_cvMap->value(QString::number(getCvNum().toInt()+1)))->isToWrite();
}

/*public*/ void LongAddrVariableValue::readChanges() {
     if (isChanged()) readAll();
}

/*public*/ void LongAddrVariableValue::writeChanges() {
     if (isChanged()) writeAll();
}

/*public*/ void LongAddrVariableValue::readAll() {
    if (logit->isDebugEnabled()) logit->debug("longAddr read() invoked");
    setToRead(false);
    setBusy(true);  // will be reset when value changes
    if (_progState != IDLE) logit->warn("Programming state "+QString::number(_progState)+", not IDLE, in read()");
    _progState = READING_FIRST;
    if (logit->isDebugEnabled()) logit->debug("invoke CV read");
    (_cvMap->value(getCvNum()))->read(_status);
}

/*public*/ void LongAddrVariableValue::writeAll() {
    if (logit->isDebugEnabled()) logit->debug("write() invoked");
    if (getReadOnly()) logit->error("unexpected write operation when readOnly is set");
    setToWrite(false);
    setBusy(true);  // will be reset when value changes
    if (_progState != IDLE) logit->warn("Programming state "+QString::number(_progState)+", not IDLE, in write()");
    _progState = WRITING_FIRST;
    if (logit->isDebugEnabled()) logit->debug("invoke CV write");
    (_cvMap->value(getCvNum()))->write(_status);
}

// handle incoming parameter notification
/*public*/ void LongAddrVariableValue::propertyChange(PropertyChangeEvent* e)
{
 if (logit->isDebugEnabled()) logit->debug("property changed event - name: "
                                        +e->getPropertyName());
 // notification from CV; check for Value being changed
 if (e->getPropertyName()==("Busy") && (e->getNewValue().toBool())==(false))
 {
  // busy transitions drive the state
  switch (_progState)
  {
  case IDLE:  // no, just a CV update
   if (logit->isDebugEnabled()) logit->error("Busy goes false with state IDLE");
   return;
  case READING_FIRST:   // read first CV, now read second
   if (logit->isDebugEnabled()) logit->debug("Busy goes false with state READING_FIRST");
   _progState = READING_SECOND;
   (_cvMap->value(QString::number(getCvNum().toInt()+1)))->read(_status);
   return;
  case READING_SECOND:  // finally done, set not busy
   if (logit->isDebugEnabled()) logit->debug("Busy goes false with state READING_SECOND");
   _progState = IDLE;
   (_cvMap->value(getCvNum()))->setState(READ);
   (_cvMap->value(QString::number(getCvNum().toInt()+1)))->setState(READ);
   VariableValue::setState(READ);
   setBusy(false);
   return;
  case WRITING_FIRST:  // no, just a CV update
   if (logit->isDebugEnabled()) logit->debug("Busy goes false with state WRITING_FIRST");
   _progState = WRITING_SECOND;
   (_cvMap->value(QString::number(getCvNum().toInt()+1)))->write(_status);
   return;
  case WRITING_SECOND:  // now done with complete request
   if (logit->isDebugEnabled()) logit->debug("Busy goes false with state WRITING_SECOND");
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
 else if (e->getPropertyName()==("State"))
 {
  CvValue* cv = _cvMap->value(getCvNum());
  if (logit->isDebugEnabled()) logit->debug("CV State changed to "+QString::number(cv->getState()));
  setState(cv->getState());
 }
 else if (e->getPropertyName()==("Value"))
 {
  // update value of Variable
  CvValue* cv0 = _cvMap->value(getCvNum());
  CvValue* cv1 = _cvMap->value(QString::number(getCvNum().toInt()+1));
  int newVal = (cv0->getValue()&0x3f)*256 + cv1->getValue();
  setValue(newVal);  // check for duplicate done inside setVal
  // state change due to CV state change, so propagate that
  setState(cv0->getState());
  // see if this was a read or write operation
  switch (_progState)
  {
  case IDLE:  // no, just a CV update
            if (logit->isDebugEnabled()) logit->debug("Value changed with state IDLE");
            return;
  case READING_FIRST:  // yes, now read second
            if (logit->isDebugEnabled()) logit->debug("Value changed with state READING_FIRST");
            return;
  case READING_SECOND:  // now done with complete request
            if (logit->isDebugEnabled()) logit->debug("Value changed with state READING_SECOND");
            return;
  default:  // unexpected!
    logit->error("Unexpected state found: "+_progState);
   _progState = IDLE;
   return;
  }
 }
}


    /* Internal class extends a JTextField so that its color is consistent with
     * an underlying variable
     *
     * @author   Bob Jacobsen   Copyright (C) 2001
     */
    //public class VarTextField extends JTextField {

        LAVarTextField::LAVarTextField(Document* doc, QString text, int col, LongAddrVariableValue* var)
         : JTextField(doc, text, col)
        {
            //super(doc, text, col);
            _var = var;
            // get the original color right
            setBackground(_var->_value->getBackground());
            // listen for changes to ourself
//            addActionListener(new java.awt.event.ActionListener() {
//                @Override
//                public void actionPerformed(java.awt.event.ActionEvent e) {
//                    thisActionPerformed(e);
//                }
//            });
            connect(this, &LAVarTextField::textEdited, [=]{
             thisActionPerformed();
            });
//            addFocusListener(new java.awt.event.FocusListener() {
//                @Override
//                public void focusGained(FocusEvent e) {
//                    log.debug("focusGained");
//                    enterField();
//                }
            connect(this, &LAVarTextField::focusGained, [=]{
              if (_var->logit->isDebugEnabled()) {
                  _var->logit->debug("focusGained");
              }
              enterField();
            });

//                @Override
//                public void focusLost(FocusEvent e) {
//                    log.debug("focusLost");
//                    exitField();
//                }
//            });
            connect(this, &LAVarTextField::focusLost, [=]{
              if (_var->logit->isDebugEnabled()) {
                  _var->logit->debug("focusLost");
              }
              leaveField();
            });
            // listen for changes to original state
//            _var.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
//                @Override
//                public void propertyChange(java.beans.PropertyChangeEvent e) {
            connect(this->_var->prop, &PropertyChangeSupport::propertyChange, [=](PropertyChangeEvent* e) {
                    originalPropertyChanged(e);
//                }
            });
        }

//    LongAddrVariableValue* _var;

    void LAVarTextField::thisActionPerformed(/*ActionEvent* e*/) {
        // tell original
        _var->actionPerformed(/*e*/);
    }

    void LAVarTextField::originalPropertyChanged(PropertyChangeEvent* e) {
        // update this color from original state
        if (e->getPropertyName()==("State")) {
//            setBackground(_var->_value->getBackground());
        }
    }

//};

// clean up connections when done
/*public*/ void LongAddrVariableValue::dispose() {
    if (logit->isDebugEnabled()) logit->debug("dispose");
//    if (_value != NULL) _value->removeActionListener((ActionListener*)this);
    (_cvMap->value(getCvNum()))->removePropertyChangeListener((PropertyChangeListener*)this);
    (_cvMap->value(QString::number(getCvNum().toInt()+1)))->removePropertyChangeListener((PropertyChangeListener*)this);

    _value = NULL;
    // do something about the VarTextField
}
void LongAddrVariableValue::textChanged()
{
 actionPerformed(/*NULL*/);
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* LongAddrVariableValue::logit = LoggerFactory::getLogger("LongAddrVariableValue");
