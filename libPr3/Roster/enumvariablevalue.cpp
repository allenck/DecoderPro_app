#include "enumvariablevalue.h"
#include "actionevent.h"
#include "comboonradiobutton.h"
#include "combooffradiobutton.h"
#include "treepath.h"
#include <QApplication>

//EnumVariableValue::EnumVariableValue(QObject *parent) :
//    VariableValue(parent)
//{
//}
/**
 * Extends VariableValue to represent a enumerated variable.
 *
 * @author	Bob Jacobsen   Copyright (C) 2001, 2002, 2003
 * @version	$Revision: 17977 $
 *
 */
// /*public*/ class EnumVariableValue extends VariableValue implements ActionListener, PropertyChangeListener {

/*public*/ EnumVariableValue::EnumVariableValue(QString name, QString comment, QString cvName,
                         bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                         QString cvNum, QString mask, int minVal, int maxVal,
                         QMap<QString,CvValue*>* v, JLabel* status, QString stdname, QObject *parent) : VariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent)
{
    //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname);
    _maxVal = maxVal;
    _minVal = minVal;
    _value = NULL;
    _itemArray = NULL;
    _valueArray = NULL;
    _nstored = 0;
    logit = new Logger("EnumVariableValue");
    comboCBs = new QList<ComboCheckBox*>();
    comboVars = new QList<VarComboBox*>();
    comboRBs = new QList<ComboRadioButtons*>();

    treeNodes = QVector<DefaultMutableTreeNode*>();
    treeNodes.append(new DefaultMutableTreeNode(""));
}

/**
 * Create a NULL object.  Normally only used for tests and to pre-load classes.
 */
/*public*/ EnumVariableValue::EnumVariableValue(QObject *parent) : VariableValue(parent)
{
    _value = new QComboBox();
    _itemArray = NULL;
    _valueArray = NULL;
    _pathArray = NULL;
    logit = new Logger("EnumVariableValue");
    comboCBs = new QList<ComboCheckBox*>();
    comboVars = new QList<VarComboBox*>();
    comboRBs = new QList<ComboRadioButtons*>();
}

/*public*/ QVector<CvValue *> EnumVariableValue::usesCVs()
{
    QVector<CvValue*> list = QVector<CvValue*>();
    list.append(_cvMap->value(getCvNum()));
    return list;
}

/*public*/ void EnumVariableValue::nItems(int n) {
    _itemArray = new QVector<QString>(n);
    _pathArray = new QVector<TreePath*>(n);
    _valueArray = new QVector<int>(n,0);
    _nstored = 0;
}

/**
 * Create a new item in the enumeration, with an associated
 * value one more than the last item (or zero if this is the first
 * one added)
 * @param s  Name of the enumeration item
 */
/*public*/ void EnumVariableValue::addItem(QString s)
{
 if (_nstored == 0)
 {
  addItem(s, 0);
 }
 else
 {
  addItem(s, _valueArray->at(_nstored-1)+1);
 }
}

/**
 * Create a new item in the enumeration, with a specified
 * associated value.
 * @param s  Name of the enumeration item
 */
/*public*/ void EnumVariableValue::addItem(QString s, int value)
{
 if(_nstored == _valueArray->length())
  _valueArray->append(value); // add ACK
 else
  _valueArray->replace(_nstored, value);
 TreeLeafNode* node = new TreeLeafNode(s, _nstored);
 if(!treeNodes.isEmpty())
 {
  DefaultMutableTreeNode* lst = treeNodes.last();
  treeNodes.last()->add(node);
 }
 QVector<TreeNode*>* path = node->getPath();
 QVector<QObject*>* ol = new QVector<QObject*>();
 foreach(TreeNode* n, *path) ol->append((QObject*)n);
 if(_nstored == _pathArray->length())
  _pathArray->append(new TreePath( /*path*/ ol)); // add ACK
 else
  _pathArray->replace(_nstored, new TreePath( /*path*/ ol));
 if(_nstored == _itemArray->length())
 {
  _itemArray->append(s); // add ACK
  _nstored++;
 }
 else
  _itemArray->replace(_nstored++, s);
}

/*public*/ void EnumVariableValue::startGroup(QString name)
{
 DefaultMutableTreeNode* next = new DefaultMutableTreeNode(name);
 treeNodes.last()->add(next);
 treeNodes.append(next);
}


/*public*/ void EnumVariableValue::endGroup()
{
 treeNodes.remove(treeNodes.count()-1);
}

/*public*/ void EnumVariableValue::lastItem()
{
// Q_ASSERT(_value == NULL);
 _value = new QComboBox();
 _value->addItems(_itemArray->toList());
 // finish initialization
//    _value->setActionCommand("");
 _defaultColor = getBackground();
 setBackground(COLOR_UNKNOWN);
 // connect to the JComboBox model and the CV so we'll see changes.
//    _value->addActionListener(this);
 connect(_value, SIGNAL(currentIndexChanged(int)), this, SLOT(on_currentIndex_changed(int)));
 qApp->processEvents(); // process any item selection signals.
 CvValue* cv = _cvMap->value(getCvNum());
 cv->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(cv, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 cv->setState(CvValue::FROMFILE);
}

/*public*/ void EnumVariableValue::setToolTipText(QString t)
{
 VariableValue::setToolTipText(t);   // do default stuff
 _value->setToolTip(t);  // set our value
}


/*public*/ void EnumVariableValue::setAvailable(bool a) {
    _value->setVisible(a);
    foreach (ComboCheckBox* c, *comboCBs) c->setVisible(a);
    foreach (VarComboBox* c, *comboVars) c->setVisible(a);
    foreach (ComboRadioButtons* c, *comboRBs) c->setVisible(a);
    VariableValue::setAvailable(a);
}

/*public*/ QVariant EnumVariableValue::rangeVal() {
    return QVariant(tr("enum: ")+_minVal+" - "+_maxVal);
}

void EnumVariableValue::on_currentIndex_changed(int i)
{
 if(_value->count() < 1) return;
    //ActionEvent* actionEvent = new ActionEvent(this, i, "xxx", i);
    if(_value != NULL &&_value->currentIndex() != i)
     _value->setCurrentIndex(i);

    actionPerformed();
}

/*public*/ void EnumVariableValue::actionPerformed(JActionEvent* e)
{
 if(e != NULL)
 {
  // see if this is from _value itself, or from an alternate rep.
  // if from an alternate rep, it will contain the value to select
  if (logit->isDebugEnabled()) logit->debug(label()+" start action event: "/*+e*/);
  if (!(e->getActionCommand()==("")))
  {
   // is from alternate rep
  //_value->setSelectedItem(e->getActionCommand());
   _value->setItemData(_value->currentIndex(),e->getActionCommand());

   if (logit->isDebugEnabled()) logit->debug(label()+" action event was from alternate rep");
  }
 }
 int _currentIndex = _value->currentIndex();

 if(_value->currentIndex() < 0) return;

 int oldVal = getIntValue();

 // called for new values - set the CV as needed
 CvValue* cv = _cvMap->value(getCvNum());
 // compute new cv value by combining old and request
 int oldCv = cv->getValue();
 int newVal = getIntValue();
 int newCv = setValueInCV(oldCv, newVal, getMask(), _maxVal-1);
 if (newCv != oldCv)
 {
  cv->setValue(newCv);  // to prevent CV going EDITED during loading of decoder file

  // notify  (this used to be before setting the values)
  if (logit->isDebugEnabled()) logit->debug(label()+" about to firePropertyChange");
   prop->firePropertyChange("Value", QVariant(), QVariant(oldVal));
  if (logit->isDebugEnabled()) logit->debug(label()+" returned to from firePropertyChange");
 }
 if (logit->isDebugEnabled()) logit->debug(label()+" end action event saw oldCv="+oldCv+" newVal="+newVal+" newCv="+newCv);
}

// to complete this class, fill in the routines to handle "Value" parameter
// and to read/write/hear parameter changes.
/*public*/ QString EnumVariableValue::getValueString() {
    return _value->currentText();
}
/*public*/ void EnumVariableValue::setIntValue(int i) {
    selectValue(i);
}

/*public*/ QString EnumVariableValue::getTextValue() {
    //return _value->getSelectedItem().toString();
 return _value->currentText();
}

/*public*/ QVariant EnumVariableValue::getValueObject() {
    return (_value->currentIndex());
}

/**
 * Set to a specific value.
 * <P>
 * This searches for the displayed value, and sets the
 * enum to that particular one.  It used to work off an index,
 * but now it looks for the value.
 * <P>
 * If the value is larger than any defined, a new one is created.
 * @param value
 */
/*protected*/ void EnumVariableValue::selectValue(int value)
{
 if (value>256) logit->error("Saw unreasonable internal value: "+value);
 for (int i = 0; i<_valueArray->count(); i++)
  if (_valueArray->at(i)==value)
  {
   //found it, select it
   int oldIndex = _value->currentIndex();
   _value->setCurrentIndex(i);
   emit valueChanged(i);
   return;
  }

 // We can be commanded to a number that hasn't been defined.
 // But that's OK for certain applications.  Instead, we add them as needed
 logit->debug("Create new item with value "+QString::number(value)+" count was "+QString::number(_value->count()) +" in "+label());
 _value->addItem("Reserved value "+value);
 // and value array is too short
 QVector<int>* oldArray = _valueArray;
 _valueArray = new QVector<int>(oldArray->count()+1);
 for (int i = 0; i<oldArray->count(); i++) _valueArray->replace(i,oldArray->at(i));
 _valueArray->replace(oldArray->count(), value);

 //_value->setSelectedItem("Reserved value "+value);
 _value->setItemText(_value->currentIndex(),"Reserved value "+QString::number(value));
}

/*public*/ int EnumVariableValue::getIntValue()
{
 if (_value->currentIndex()>=_valueArray->count() || _value->currentIndex()<0)
  logit->error("trying to get value "+QString::number(_value->currentIndex())+" too large"
                +" for array length "+QString::number(_valueArray->count())+" in var "+label());
 if(_value->currentIndex() < 0)
     return 0;
 if(_valueArray->count() == 0) return 0;
 return _valueArray->at(_value->currentIndex());
}

/*public*/ QWidget* EnumVariableValue::getCommonRep()  { return _value; }

/*public*/ void EnumVariableValue::setValue(int value)
{
 int oldVal = getIntValue();
 selectValue(value);

 if (oldVal != value || getState() == VariableValue::UNKNOWN)
  prop->firePropertyChange("Value", QVariant(), QVariant(value));
}

/*public*/ QWidget* EnumVariableValue::getNewRep(QString format)
{
 // sort on format type
 if (format==("checkbox"))
 {
  // this only makes sense if there are exactly two options
  ComboCheckBox* b = new ComboCheckBox(_value, this);
  comboCBs->append(b);
  updateRepresentation(b);
  return b;
 }
 else if (format==("radiobuttons"))
 {
  ComboRadioButtons* b = new ComboRadioButtons(_value, this);
  comboRBs->append(b);
  updateRepresentation(b);
  return b;
 }
 else if (format==("onradiobutton"))
 {
  ComboRadioButtons* b = new ComboOnRadioButton(_value, this);
  comboRBs->append(b);
  updateRepresentation(b);
  return b;
 }
 else if (format==("offradiobutton"))
 {
  ComboRadioButtons* b = new ComboOffRadioButton(_value, this);
  comboRBs->append(b);
  updateRepresentation(b);
  return b;
 }
 else
 {
  // return a new JComboBox representing the same model
  //VarComboBox* b = new VarComboBox(_value->getModel(), this);
  VarComboBox* b = new VarComboBox(/*new ComboBoxModel(),*/this);
  for(int i=0; i< _value->count(); i++)
   b->addItem(_value->itemText(i));
  comboVars->append(b);
  updateRepresentation(b);
  return b;
 }
}


// implement an abstract member to set colors
void EnumVariableValue::setColor(QColor c)
{
    if (c .isValid()) setBackground(c);
    else setBackground(_defaultColor);
    // prop.firePropertyChange("Value", NULL, NULL);
}

QColor EnumVariableValue::getBackground()
{
 //return getBackground();
    QColor c;
    if(_value == NULL) return c;
    QPalette p = _value->palette();
    QString ss = _value->styleSheet();
    c = p.color(QPalette::Background);
    if(ss == "")
      return c;
    int i = ss.indexOf("background");
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

void EnumVariableValue::setBackground(QColor c)
{
 if(_value == NULL) return;
 QColor oldC = getBackground();
 if(oldC != c)
 {
  QString ss = QString("QComboBox { background : rgb(%1,%2,%3);}").arg(c.red()).arg(c.green()).arg(c.blue());
  _value->setStyleSheet(ss);
 }
}

/**
 * Notify the connected CVs of a state change from above
 * @param state
 */
/*public*/ void EnumVariableValue::setCvState(int state) {
    _cvMap->value(getCvNum())->setState(state);
}

/*public*/ bool EnumVariableValue::isChanged() {
    CvValue* cv = _cvMap->value(getCvNum());
    return considerChanged(cv);
}

/*public*/ void EnumVariableValue::readChanges() {
     if (isToRead() && !isChanged())
        logit->debug("!!!!!!! unacceptable combination in readChanges: "+label());
     if (isChanged() || isToRead()) readAll();
}

/*public*/ void EnumVariableValue::writeChanges() {
     if (isToWrite() && !isChanged())
        logit->debug("!!!!!! unacceptable combination in writeChanges: "+label());
     if (isChanged() || isToWrite()) writeAll();
}

/*public*/ void EnumVariableValue::readAll() {
    setToRead(false);
    setBusy(true);  // will be reset when value changes
    _cvMap->value(getCvNum())->read(_status);
}

/*public*/ void EnumVariableValue::writeAll() {
    setToWrite(false);
    if (getReadOnly()) logit->error("unexpected write operation when readOnly is set");
    setBusy(true);  // will be reset when value changes
    _cvMap->value(getCvNum())->write(_status);
}

// handle incoming parameter notification
/*public*/ void EnumVariableValue::propertyChange(PropertyChangeEvent* e) {
    // notification from CV; check for Value being changed
    if (e->getPropertyName()==("Busy")) {
        if (e->getNewValue().toBool()==(false)) {
            setToRead(false);
            setToWrite(false);  // some programming operation just finished
            setBusy(false);
        }
    } else if (e->getPropertyName()==("State")) {
        CvValue* cv = _cvMap->value(getCvNum());
        if (cv->getState() == STORED) setToWrite(false);
        if (cv->getState() == READ) setToRead(false);
        setState(cv->getState());
    } else if (e->getPropertyName()==("Value")) {
        // update value of Variable
        CvValue* cv = _cvMap->value(getCvNum());
        int newVal = getValueInCV(cv->getValue(), getMask(), _maxVal-1); // _maxVal value is count of possibles, i.e. radix
        setValue(newVal);  // check for duplicate done inside setVal
    }
}

// clean up connections when done
/*public*/ void EnumVariableValue::dispose() {
    if (logit->isDebugEnabled()) logit->debug("dispose");

    // remove connection to CV
    _cvMap->value(getCvNum())->removePropertyChangeListener((PropertyChangeListener*)this);

    // remove connection to graphical representation
    disposeReps();

}

void EnumVariableValue::disposeReps()
{
    //if (_value != NULL) _value->removeActionListener(this);
    disconnect(_value, SIGNAL(currentIndexChanged(int)), this, SLOT(on_currentIndex_changed(int)));

    for (int i = 0; i<comboCBs->size(); i++) {
        comboCBs->at(i)->dispose();
    }
    for (int i = 0; i<comboVars->size(); i++) {
        comboVars->at(i)->dispose();
    }
    for (int i = 0; i<comboRBs->size(); i++) {
        comboRBs->at(i)->dispose();
    }
}

TreeLeafNode::TreeLeafNode(QString name, int index)
    : DefaultMutableTreeNode(name)
{
    //super(name);
    this->index = index;
}
