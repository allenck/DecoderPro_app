#include "compositevariablevalue.h"
#include "cvvalue.h"

//CompositeVariableValue::CompositeVariableValue(QObject *parent) :
//    EnumVariableValue(parent)
//{
//}
/**
 * Extends EnumVariableValue to represent a composition of variable values.
 * <P>
 * Internally, each "choice" is stored as a list of "setting" items.
 * Numerical values for this type of variable (itself) are strictly sequential,
 * because they are arbitrary.
 * <p>
 * This version of the class has certain limitations:
 *<OL>
 * <LI>Variables referenced in the definition of one of these must have
 * already been declared earlier in the decoder file.  This prevents
 * circular references, and makes it much easier to find the target variables.
 * <LI>
 * This version of the variable never changes "State" (color), though it does
 * track it's value from changes to other variables.
 * <LI>The should be a final choice (entry) that doesn't define any
 * settings.  This will then form the default value when the target variables
 * change.
 * <LI>Programming operations on a variable of this type doesn't do anything, because
 * there doesn't seem to be a consistent model of what "read changes" and "write changes"
 * should do.
 * This has two implications:
 *  <UL>
 *  <LI>Variables referenced as targets must appear on some programming pane,
 *      or they won't be updated by programming operations.
 *  <LI>If this variable references variables that are not on this pane,
 *      the user needs to do a read/write all panes operation to record
 *      the changes made to this variable.
 *  </UL>
 *  It's therefore recommended that a CompositeVariableValue just make changes
 *  to target variables on the same programming page.
 *</ol>
 * <P>
 * @author	Bob Jacobsen   Copyright (C) 2001, 2005
 * @version	$Revision: 17977 $
 *
 */
// /*public*/ class CompositeVariableValue extends EnumVariableValue implements ActionListener, PropertyChangeListener {

/*public*/ CompositeVariableValue::CompositeVariableValue(QString name, QString comment, QString cvName,
                         bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                         QString cvNum, QString mask, int minVal, int maxVal,
                         QMap<QString,CvValue*>* v, JLabel* status, QString stdname, QObject *parent)
    : EnumVariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, minVal, maxVal, v, status, stdname, parent)
{
    //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, minVal, maxVal, v, status, stdname);
    choiceHash = new QHash<QString,SettingList*>();
    variables = new QSet<VariableValue*>();
    amReading = false;
    readingChanges = false;
    amWriting = false;
    writingChanges = false;

    _maxVal = maxVal;
    _minVal = minVal;
    _value = new QComboBox();
    if (logit->isDebugEnabled()) logit->debug("New Composite named "+name);
}

/**
 * Create a NULL object.  Normally only used for tests and to pre-load classes.
 */
/*public*/ CompositeVariableValue::CompositeVariableValue(QObject *parent) : EnumVariableValue(parent)
{
    _value = new QComboBox();
    choiceHash = new QHash<QString,SettingList*>();
    variables = new QSet<VariableValue*>();
    amReading = false;
    readingChanges = false;
    amWriting = false;
    writingChanges = false;
}

/*public*/ QVector<CvValue *> CompositeVariableValue::usesCVs() {
    QSet<CvValue*> cvSet = QSet<CvValue*>();  // 20 is arbitrary
    QSetIterator<VariableValue*> i(*variables);
    while (i.hasNext())
    {
     VariableValue* v = i.next();
        QVector<CvValue*> cvs = v->usesCVs();
        for (int k=0; k<cvs.count(); k++)
            cvSet.insert(cvs.at(k));
    }
    QVector<CvValue*> retval =  /*CvValue[cvSet->size()];*/  QVector<CvValue*>(cvSet.size(), NULL);
    QSetIterator<CvValue*> j (cvSet);
    int index = 0;
    while (j.hasNext()) {
        retval.replace(index++, j.next());
    }
    return retval;
}



/**
 * Create a new possible selection.
 * @param name  Name of the choice being added
 */
/*public*/ void CompositeVariableValue::addChoice(QString name) {
    SettingList* l = new SettingList();
    choiceHash->insert(name, l);
    _value->addItem(name);
}

/**
 * Add a setting to an existing choice.
 */
/*public*/ void CompositeVariableValue::addSetting(QString choice, QString varName, VariableValue* variable, QString value) {
    SettingList* s = choiceHash->value(choice);
    s->addSetting(varName, variable, value);

    if (variable!=NULL) {
        variables->insert(variable);
        if (variable->label()!=(varName))
            logit->warn("Unexpected label /"+variable->label()+"/ for varName /"+varName+"/ during addSetting");
    } else
        logit->error("Variable pointer NULL when varName="+varName+" in choice "+choice+"; ignored");
}

/**
 * Do end of initialization processing.
 */
//@SuppressWarnings("NULL")
/*public*/ void CompositeVariableValue::lastItem()
{
 // configure the representation object
 //    _defaultColor = _value->getBackground();
 EnumVariableValue::setState(READ);

 // note that we don't set this to COLOR_UNKNOWN!  Rather,
 // we check the current value
 findValue();

 // connect to all variables to hear changes
 QSetIterator<VariableValue*> i (*variables);
 while (i.hasNext())
 {
  VariableValue* v = i.next();
  if (v==NULL) logit->error("Variable found as NULL in last item");
  // connect, force an exception if v == NULL
  v->addPropertyChangeListener((PropertyChangeListener*)this);
  connect(v->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 // connect to the JComboBox model so we'll see changes.
//    _value->setActionCommand("");            // so we can tell where change comes from
//    _value->addActionListener(this);
 connect(_value, SIGNAL(currentIndexChanged(int)), this, SLOT(actionPerformed()));
}

/*public*/ void CompositeVariableValue::setToolTipText(QString t) {
    EnumVariableValue::setToolTipText(t);   // do default stuff
    _value->setToolTip(t);  // set our value
}

/*public*/ QVariant CompositeVariableValue::rangeVal() {
    return "composite: "+QString::number(_minVal)+" - "+QString::number(_maxVal);
}

/*public*/ void CompositeVariableValue::actionPerformed(JActionEvent* /*e*/)
{
 // see if this is from _value itself, or from an alternate rep.
 // if from an alternate rep, it will contain the value to select
 //if ((e->getActionCommand()!=("")))
 if(_value->currentText() != "")
 {
  // is from alternate rep
  //_value->setSelectedItem(e->getActionCommand());
  //_value->setItemText(_value->currentIndex(), e->getActionCommand());
  _value->setItemText(_value->currentIndex(),_value->currentText() );
 }
 if (logit->isDebugEnabled()) logit->debug("action event: "/*+e*/);

 // notify
 prop->firePropertyChange("Value", NULL, (getIntValue()));
 // Here for new values; set as needed
 selectValue(getIntValue());
}

/**
 * This variable doesn't change state, hence doesn't change color.
 */
/*public*/ void CompositeVariableValue::setState(int state) {
    if (logit->isDebugEnabled()) logit->debug("Ignore setState("+QString::number(state)+")");
}

/**
 * Set to a specific value.
 *<P>
 * Does this by delegating to the SettingList
 * @param value
 */
/*protected*/ void CompositeVariableValue::selectValue(int value) {
    if (logit->isDebugEnabled()) logit->debug("selectValue("+QString::number(value)+")");
    if (value>_value->count()-1) {
        logit->error("Saw unreasonable internal value: "+QString::number(value));
        return;
    }

    // locate SettingList for that number
    QString choice = (QString)_value->itemText(value);
    SettingList* sl = choiceHash->value(choice);
    sl->setValues();

}

/*public*/ int CompositeVariableValue::getIntValue() {
    return _value->currentIndex();
}

/*public*/ QWidget* CompositeVariableValue::getCommonRep()  { return _value; }

/*public*/ void CompositeVariableValue::setValue(int value) {
    int oldVal = getIntValue();
    selectValue(value);

    if (oldVal != value || getState() == VariableValue::UNKNOWN)
        prop->firePropertyChange("Value", NULL, (value));
}

/**
 * Notify the connected CVs of a state change from above
 * by way of the variables (e.g. not direct to CVs)
 * @param state
 */
/*public*/ void CompositeVariableValue::setCvState(int state) {
    QSetIterator<VariableValue*> i (*variables);
    while (i.hasNext()) {
        VariableValue* v = i.next();
        ((CompositeVariableValue*)v)->setCvState(state);
    }
}

/*public*/ bool CompositeVariableValue::isChanged() {
    QSetIterator<VariableValue*> i(*variables);
    while (i.hasNext()) {
        VariableValue* v = i.next();
        if (v->isChanged()) return true;
    }
    return false;
}

/*public*/ void CompositeVariableValue::setToRead(bool state) {

    QSetIterator<VariableValue*> i(*variables);
    while (i.hasNext()) {
        VariableValue* v = i.next();
        v->setToRead(state);
    }
}

/**
 * This variable needs to be read if any of it's subsidiary
 * variables needs to be read.
 */
/*public*/ bool CompositeVariableValue::isToRead() {
    QSetIterator<VariableValue*> i(*variables);
    while (i.hasNext()) {
        VariableValue* v = i.next();
        if (v->isToRead()) return true;
    }
    return false;
}

/*public*/ void CompositeVariableValue::setToWrite(bool state) {
    if (logit->isDebugEnabled()) logit->debug("Start setToWrite with "+state);

    QSetIterator<VariableValue*> i(*variables);
    while (i.hasNext()) {
        VariableValue* v = i.next();
        v->setToWrite(state);
    }
    logit->debug("End setToWrite");
}

/**
 * This variable needs to be written if any of it's subsidiary
 * variables needs to be written.
 */
/*public*/ bool CompositeVariableValue::isToWrite() {
    QSetIterator<VariableValue*> i(*variables);
    while (i.hasNext()) {
        VariableValue* v = i.next();
        if (v->isToWrite()) return true;
    }
    return false;
}

/*public*/ void CompositeVariableValue::readChanges() {
    if (isChanged()) {
        readingChanges = true;
        amReading = true;
        continueRead();
    }
}

/*public*/ void CompositeVariableValue::writeChanges() {
    if (isChanged()) {
        writingChanges = true;
        amWriting = true;
        continueWrite();
    }
}

/*public*/ void CompositeVariableValue::readAll() {
    readingChanges = false;
    amReading = true;
    continueRead();
}

/**
 * See if there's anything to read, and if so do it.
 */
/*protected*/ void CompositeVariableValue::continueRead()
{
 // search for something to do
 if (logit->isDebugEnabled()) logit->debug("Start continueRead");

 QSetIterator<VariableValue*> i(*variables);
 while (i.hasNext())
 {
  VariableValue* v = i.next();
  if (v->isToRead() && (!readingChanges || v->isChanged()))
  {
   // something to do!
   amReading = true; // should be set already
   setBusy(true);
   if (readingChanges) v->readChanges();
   else v->readAll();
   return;  // wait for busy change event to continue
  }
 }
 // found nothing, ensure cleaned up
 amReading = false;
 EnumVariableValue::setState(READ);
 setBusy(false);
 logit->debug("End continueRead, nothing to do");
}

/*public*/ void CompositeVariableValue::writeAll()
{
 if (getReadOnly()) logit->error("unexpected write operation when readOnly is set");
 writingChanges = false;
 amWriting = true;
 continueWrite();
}

/**
 * See if there's anything to write, and if so do it.
 */
/*protected*/ void CompositeVariableValue::continueWrite()
{
 // search for something to do
 if (logit->isDebugEnabled()) logit->debug("Start continueWrite");

 QSetIterator<VariableValue*> i(*variables);
 while (i.hasNext())
 {
  VariableValue* v = i.next();
  if (v->isToWrite() && (!writingChanges || v->isChanged()))
  {
   // something to do!
   amWriting = true; // should be set already
   setBusy(true);
   logit->debug("request write of "+v->label()+" writing changes "+(writingChanges?"true":"false"));
   if (writingChanges) v->writeChanges();
   else v->writeAll();
   logit->debug("return from starting write request");
   return;  // wait for busy change event to continue
  }
 }
 // found nothing, ensure cleaned up
 amWriting = false;
 EnumVariableValue::setState(STORED);
 setBusy(false);
 logit->debug("End continueWrite, nothing to do");
}

// handle incoming parameter notification
/*public*/ void CompositeVariableValue::propertyChange(PropertyChangeEvent* e)
{
 // notification from CV; check for Value being changed
 if (logit->isDebugEnabled()) logit->debug("propertyChange in "+label()+" type "+e->getPropertyName()+" new value "+e->getNewValue().toString());
 if (e->getPropertyName()==("Busy"))
 {
  if ((e->getNewValue().toBool())==(false))
  {
   logit->debug("busy change continues programming");
   // some programming operation just finished
   if (amReading)
   {
    continueRead();
    return;
   }
   else if (amWriting)
   {
    continueWrite();
    return;
   }
   // if we're not reading or writing, no problem, that's just something else happening
  }
 }
 else if (e->getPropertyName()==("Value"))
 {
  findValue();
 }
}

/**
 * Suspect underlying variables have changed value; check.
 * First match will succeed, so there should not be multiple
 * matches possible. ("First match" is defined in
 * choice-sequence)
 */
void CompositeVariableValue::findValue() {
    if (logit->isDebugEnabled()) logit->debug("findValue invoked on "+label());
    for (int i=0; i<_value->count(); i++) {
        QString choice = (QString)_value->itemText(i);
        SettingList* sl = choiceHash->value(choice);
        if (sl->match()) {
            if (logit->isDebugEnabled()) logit->debug("  match in "+i);
            _value->setItemText(_value->currentIndex(),choice);
            return;
        }
    }
    if (logit->isDebugEnabled()) logit->debug("   no match");
}

// clean up connections when done
/*public*/ void CompositeVariableValue::dispose() {
    if (logit->isDebugEnabled()) logit->debug("dispose");

    QSetIterator<VariableValue*> i(*variables);
    while (i.hasNext()) {
        VariableValue* v = i.next();
        v->removePropertyChangeListener((PropertyChangeListener*)this);
    }

    // remove the graphical representation
    disposeReps();
}
