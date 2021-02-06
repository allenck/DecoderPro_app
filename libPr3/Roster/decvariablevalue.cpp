#include "decvariablevalue.h"
#include "decvarslider.h"
#include "actionlistener.h"
#include <QIntValidator>
#include "jslider.h"
#include "jlabel.h"
#include "math.h"

//DecVariableValue::DecVariableValue(QObject *parent) :
//    VariableValue(parent)
//{
//}
/**
 * Decimal representation of a value.
 *
 * @author		Bob Jacobsen   Copyright (C) 2001
 * @version             $Revision: 18544 $
 *
 */
///*public*/ class DecVariableValue extends VariableValue
//    implements ActionListener, PropertyChangeListener, FocusListener {

/*public*/ DecVariableValue::DecVariableValue(QString name, QString comment, QString cvName, bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly, QString cvNum, QString mask, int minVal, int maxVal, QMap<QString,CvValue*>* v, JLabel* status, QString stdname, QObject *parent)
    : VariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname)
{
 //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname);
 _maxVal = maxVal;
 _minVal = minVal;
 _value = new JTextField("0",3);
 //_value->setValidator(new QIntValidator(_minVal, _maxVal));
 setObjectName("CV"+getCvNum());

 _value->setObjectName("DecVar"+cvNum);
 log = new Logger("DecVariableValue");
 log->setDebugEnabled(false);
 oldContents = "";
 reps = new QList<QWidget*>();
 sliders = new QList<DecVarSlider*>();
 _defaultColor = _value->getBackground();
 _value->setBackground(COLOR_UNKNOWN);
 // connect to the JTextField value, cv
 //    _value.addActionListener(this);
 connect(_value, SIGNAL(textEdited(QString)), this, SLOT(actionPerformed()));
 connect(_value, SIGNAL(editingFinished()), this, SLOT(actionPerformed()));
//    _value.addFocusListener(this);
 connect(_value, SIGNAL(enterField()), this, SLOT(focusGained()));
 connect(_value, SIGNAL(leaveField()), this, SLOT(focusLost()));
 CvValue* cv = _cvMap->value(getCvNum());
 cv->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(cv, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 cv->setState(CvValue::FROMFILE);
}

/*public*/ void DecVariableValue::setToolTipText(QString t)
{
  VariableValue::setToolTipText(t);   // do default stuff
  _value->setToolTip(t);  // set our value
}


int DecVariableValue::fieldLength()
{
 if (_maxVal <= 255)
  return 3;
  return (int) qCeil(log10(_maxVal))+1;
}

/*public*/ QVector<CvValue *> DecVariableValue::usesCVs()
{
 //return new CvValue[]{_cvVector.elementAt(getCvNum())};
 QVector<CvValue*> list = QVector<CvValue*>();
 list.append(_cvMap->value(getCvNum()));
 return list;
}

/*public*/ QVariant DecVariableValue::rangeVal()
{
 return "Decimal: "+QString::number(_minVal)+" - "+QString::number(_maxVal);
}


void DecVariableValue::enterField()
{
 oldContents = _value->text();
}
void DecVariableValue::exitField()
{
 // what to do for the case where _value == null?
 if(_value->text()!=(""))
 {
  // there may be a lost focus event left in the queue when disposed so protect
  if (oldContents!=(_value->text()))
  {
   int newVal = (_value->text()).toInt();
   int oldVal = (oldContents).toInt();
   updatedTextField();
   prop->firePropertyChange("Value", QVariant(oldVal), QVariant(newVal));
   //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", QVariant(oldVal), QVariant(newVal)));
  }
 }
 else
 {
  //As the user has left the contents blank, we shall re-instate the old
  // value as, when a write to decoder is performed, the cv remains the same value.
  _value->setText(oldContents);
 }
}

/**
 * Invoked when a permanent change to the JTextField has been
 * made.  Note that this does _not_ notify property listeners;
 * that should be done by the invoker, who may or may not
 * know what the old value was. Can be overwritten in subclasses
 * that want to display the value differently.
 */
void DecVariableValue::updatedTextField()
{
 if (log->isDebugEnabled()) log->debug("updatedTextField");
 // called for new values - set the CV as needed
 CvValue* cv = _cvMap->value(getCvNum());
 // compute new cv value by combining old and request
 int oldCv = cv->getValue();
 int newVal = 0;
 bool bOk;
 newVal = (_value->text()).toInt(&bOk);
if(!bOk) { newVal = 0; }
int newCv = setValueInCV(oldCv, newVal, getMask(), _maxVal);
 if (oldCv != newCv)
   cv->setValue(newCv);
}

/** ActionListener implementations */
/*public*/ void DecVariableValue::actionPerformed(/*JActionEvent* e*/)
{
 if (log->isDebugEnabled()) log->debug("actionPerformed");

 int newVal = (_value->text()).toInt();
 updatedTextField();
 prop->firePropertyChange("Value", QVariant(), QVariant(newVal));
 //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", QVariant(), QVariant(newVal)));
}

/** FocusListener implementations */
/*public*/ void DecVariableValue::focusGained(/*FocusEvent*/QEvent* e) {
    if (log->isDebugEnabled()) log->debug("focusGained");
    enterField();
}

/*public*/ void DecVariableValue::focusLost(/*FocusEvent*/QEvent* e) {
    if (log->isDebugEnabled()) log->debug("focusLost");
    exitField();
}

// to complete this class, fill in the routines to handle "Value" parameter
// and to read/write/hear parameter changes.
/*public*/ QString DecVariableValue::getValueString() {
    return _value->text();
}

/*public*/ void DecVariableValue::setIntValue(int i) {
    setValue(i);
}

/*public*/ int DecVariableValue::getIntValue() {
    return (_value->text()).toInt();
}

/*public*/ QVariant DecVariableValue::getValueObject() {
    return (_value->text());
}

/*public*/ QWidget* DecVariableValue::getCommonRep()
{
 if (getReadOnly())
 {
  QLabel* r = new QLabel(_value->text());
  reps->append(r);
  updateRepresentation(r);
  return r;
 }
 else
  return _value;
}

/*public*/ void DecVariableValue::setAvailable(bool a) {
    _value->setVisible(a);
    foreach (QWidget* c, *reps) c->setVisible(a);
    VariableValue::setAvailable(a);
}


/*public*/ QWidget* DecVariableValue::getNewRep(QString format)
{
 QString f = format;
 if (format==("vslider"))
 {
  DecVarSlider* b = new DecVarSlider(this, _minVal, _maxVal);
  b->setOrientation(/*JSlider.VERTICAL*/Qt::Vertical);
  sliders->append(b);
  reps->append(b);
  updateRepresentation(b);
  return b;
}
else if (format==("hslider"))
 {
  DecVarSlider* b = new DecVarSlider(this, _minVal, _maxVal);
  b->setOrientation(/*JSlider.HORIZONTAL*/Qt::Horizontal);
  sliders->append(b);
  reps->append(b);
  updateRepresentation(b);
  return b;
 }
 else if (format == ("hslider-percent")) {
     DecVarSlider* b = new DecVarSlider(this, _minVal, _maxVal);
     b->setOrientation(/*JSlider::HORIZONTAL*/Qt::Horizontal);
     if (_maxVal > 20) {
         b->setMajorTickSpacing(_maxVal / 2);
//         b->setMinorTickSpacing((_maxVal + 1) / 8);
     } else {
         b->setMajorTickSpacing(5);
//         b->setMinorTickSpacing(1); // because JSlider does not SnapToValue
//         b->setSnapToTicks(true);   // like it should, we fake it here
     }
     b->resize(b->width(), 28);
     QHash<int, JLabel*> labelTable = QHash<int, JLabel*>();
     labelTable.insert((0), new JLabel("0%"));
     if (_maxVal == 63) {   // this if for the QSI mute level, not very universal, needs work
         labelTable.insert((_maxVal / 2), new JLabel("25%"));
         labelTable.insert((_maxVal), new JLabel("50%"));
     } else {
         labelTable.insert((_maxVal / 2), new JLabel("50%"));
         labelTable.insert((_maxVal), new JLabel("100%"));
     }
     b->setLabelTable(labelTable);
     b->setPaintTicks(true);
     b->setPaintLabels(true);
     sliders->append(b);
     updateRepresentation(b);
     if (!getAvailable()) {
         b->setVisible(false);
     }
     return b;
 }
 else
 {
  JTextField* value = new DecVarTextField(_value->getDocument(), _value->text(), fieldLength(), this);
   if (getReadOnly() || getInfoOnly()) {
       value->setEditable(false);
   }
   reps->append(value);
   updateRepresentation(value);
   return value;
}
}


/**
 * Set a new value, including notification as needed.  This does the
 * conversion from string to int, so if the place where formatting
 * needs to be applied
 */
/*public*/ void DecVariableValue::setValue(int value)
{
 int oldVal;
 bool bOk;
 oldVal = (_value->text()).toInt(&bOk);
 if(!bOk)
 {
  oldVal = -999;
 }
 if (value < _minVal) value = _minVal;
 if (value > _maxVal) value = _maxVal;
 if (log->isDebugEnabled()) log->debug("setValue with new value "+QString::number(value)+" old value "+QString::number(oldVal));
 if (oldVal != value)
 {
  _value->setText(QString::number(value));
  updatedTextField();
  prop->firePropertyChange("Value", QVariant(oldVal), QVariant(value));
  //emit notifyPropertyChange(new PropertyChangeEvent(this, "Value", QVariant(oldVal), QVariant(value)));
 }
}

// implement an abstract member to set colors
QColor DecVariableValue::getDefaultColor() {
    return _defaultColor;
}

// implement an abstract member to set colors
QColor DecVariableValue::getColor()
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

void DecVariableValue::setColor(QColor c)
{
 if(log->isDebugEnabled()) log->debug(QString("set color: r(%1), g(%2), b(%3) CV=%4, state=%6, value= %5").arg(c.red()).arg(c.green()).arg(c.blue()).arg(getCvNum()).arg(getIntValue()).arg(_cvMap->value(getCvNum())->getState()));
 if (c.isValid())
 {
  _value->setBackground(c);
  currColor = c;
 }
 else _value->setBackground(_defaultColor);
    // prop.firePropertyChange("Value", null, null);
}

/**
 * Notify the connected CVs of a state change from above
 * @param state
 */
/*public*/ void DecVariableValue::setCvState(int state) {
    _cvMap->value(getCvNum())->setState(state);
}

/*public*/ bool DecVariableValue::isChanged() {
    CvValue* cv = _cvMap->value(getCvNum());
    if (log->isDebugEnabled()) log->debug("isChanged for "+(getCvNum())+" state "+QString::number(cv->getState()));
    return considerChanged(cv);
}

/*public*/ void DecVariableValue::readChanges() {
     if (isChanged()) readAll();
}

/*public*/ void DecVariableValue::writeChanges() {
     if (isChanged()) writeAll();
}

/*public*/ void DecVariableValue::readAll() {
    setToRead(false);
    setBusy(true);  // will be reset when value changes
    //super.setState(READ);
    _cvMap->value(getCvNum())->read(_status);
}

/*public*/ void DecVariableValue::writeAll() {
    setToWrite(false);
    if (getReadOnly()) {
        log->error("unexpected write operation when readOnly is set");
    }
    setBusy(true);  // will be reset when value changes
    _cvMap->value(getCvNum())->write(_status);
}

// handle incoming parameter notification
/*public*/ void DecVariableValue::propertyChange(PropertyChangeEvent* e)
{
 // notification from CV; check for Value being changed
 if (log->isDebugEnabled()) log->debug("Property changed: "+e->getPropertyName()+ " oldVal= "+ e->getOldValue().toString()+" newVal= "+ e->getNewValue().toString());
 if (e->getPropertyName()==("Busy"))
 {
  if ((e->getNewValue().toBool())==false)
  {
   setToRead(false);
   setToWrite(false);  // some programming operation just finished
   setBusy(false);
  }
 }
 else if (e->getPropertyName()==("State"))
 {
  CvValue* cv = _cvMap->value(getCvNum());
  if (cv->getState() == STORED)
   setToWrite(false);
  if (cv->getState() == READ)
   setToRead(false);
  setState(cv->getState());
  if (log->isDebugEnabled()) log->debug(cv->getStateColor());
  //_value->setBackground(cv->getStateColor());
 }
 else if (e->getPropertyName()==("Value"))
 {
  // update value of Variable
  CvValue* cv = _cvMap->value(getCvNum());
  //int newVal = (cv->getValue() & maskVal(getMask())) >> offsetVal(getMask());
  int newVal = getValueInCV(cv->getValue(), getMask(), _maxVal);
  setValue(newVal);  // check for duplicate done inside setVal
 }
}

// clean up connections when done
/*public*/ void DecVariableValue::dispose() {
    if (log->isDebugEnabled()) log->debug("dispose");
//    if (_value != NULL) _value->removeActionListener(this);
    _cvMap->value(getCvNum())->removePropertyChangeListener((PropertyChangeListener*)this);

    _value = NULL;
    // do something about the VarTextField
}

void DecVariableValue::value_changed()
{
  //updatedTextField();
 actionPerformed(/*NULL*/);
}

/* Internal class extends a JTextField so that its color is consistent with
 * an underlying variable
 *
 * @author   Bob Jacobsen   Copyright (C) 2001
 */
// /*public*/ class VarTextField extends JTextField {

    DecVarTextField::DecVarTextField(Document* doc, QString text, int col, DecVariableValue* var)
     : JTextField(doc, text, col)
    {
        //super(doc, text, col);
        _var = var;
        _var->log->setDebugEnabled(true);
        // get the original color right
        setBackground(_var->_value->getBackground());
        // listen for changes to ourself
//        addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            public void actionPerformed(java.awt.event.ActionEvent e) {
//                thisActionPerformed(e);
//            }
//        });
        connect(this, &DecVarTextField::textEdited, [=]{
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
         connect(this, &DecVarTextField::focusGained, [=]{
           if (_var->log->isDebugEnabled()) {
               _var->log->debug("focusGained");
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
         connect(this, &DecVarTextField::focusLost, [=]{
           if (_var->log->isDebugEnabled()) {
               _var->log->debug("focusLost");
           }
           leaveField();
         });
        // listen for changes to original state
//        _var.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
//            @Override
//            public void propertyChange(java.beans.PropertyChangeEvent e) {
         connect(this->_var->prop, &PropertyChangeSupport::propertyChange, [=](PropertyChangeEvent* e) {
                originalPropertyChanged(e);
//            }
        });
    }

    void DecVarTextField::thisActionPerformed(/*java.awt.event.ActionEvent e*/) {
        // tell original
        _var->actionPerformed(/*e*/);
    }

    void DecVarTextField::originalPropertyChanged(PropertyChangeEvent* e) {
        // update this color from original state
        if (e->getPropertyName() == ("State")) {
            setBackground(_var->_value->getBackground());
        }
        if(e->getPropertyName() == "Value")
         setText(e->getNewValue().toString());
    }

//}
