#include "speedtablevarvalue.h"
#include"rosterentry.h"
#include "math.h"
#include <QScrollArea>
#include <QGridLayout>
#include "gridbagconstraints.h"
#include "decvariablevalue.h"
#include "jslider.h"
#include <QFontMetrics>
#include "boundedrangemodel.h"

const QString SpeedTableVarValue::VSTART_CV = "2";
const QString SpeedTableVarValue::VHIGH_CV = "5";

//SpeedTableVarValue::SpeedTableVarValue(QObject *parent) :
//    VariableValue(parent)
//{
//}
/**
 * Represent an entire speed table as a single Variable.
 * <P>
 * This presents as a set of vertically oriented sliders, with numeric values above them.
 * That it turn is done using VarSlider and DecVariableValue objects respectively.
 * VarSlider is an interior class to color a JSlider by state. The respective VarSlider
 * and DecVariableValue communicate through their underlying CV objects. Changes to
 * CV Values are listened to by this class, which updates the model objects for the
 * VarSliders; the DecVariableValues listen directly.
 *<P>
 * Color (hence state) of individual sliders (hence CVs) are directly coupled to the
 * state of those CVs.
 *<P> The state of the entire variable has to be a composite of all the sliders, hence CVs.
 * The mapping is (in order):
 *<UL>
 *<LI>If any CVs are UNKNOWN, its UNKNOWN..
 *<LI>If not, and any are EDITED, its EDITED.
 *<LI>If not, and any are FROMFILE, its FROMFILE.
 *<LI>If not, and any are READ, its READ.
 *<LI>If not, and any are STORED, its STORED.
 *<LI>And if we get to here, something awful has happened.
 *</UL><P>
 * A similar pattern is used for a read or write request.  Write writes them all;
 * Read reads any that aren't READ or WRITTEN.
 *<P>
 * Speed tables can have different numbers of entries; 28 is the default, and also the maximum.
 * <P>
 * The NMRA specification says that speed table entries cannot be non-monotonic (e.g. cannot
 * decrease when moving from lower to higher CV numbers). In earlier versions of the code,
 * this was enforced any time a value was changed (for any reason).  This caused a problem
 * when CVs were read that were non-monotonic:  That value was read, causing lower CVs to be made
 * consistent, a change in their value which changed their state, so they were read again.  To
 * avoid this, the class now only enforces non-monotonicity when the slider is adjusted.
 *<P>
 * _value is a holdover from the LongAddrVariableValue, which this was copied from; it should
 * be removed.
 *<P>
 * @author	Bob Jacobsen, Alex Shepherd   Copyright (C) 2001, 2004
 * @author  Dave Heap           Copyright (C) 2012 Added support for Marklin mfx style speed table
 * @author  Dave Heap           Copyright (C) 2013 Changes to fix mfx speed table issue (Vstart & Vhigh not written)
 * @author  Dave Heap                              - generate cvList array to incorporate Vstart & Vhigh
 * @version	$Revision: 22629 $
 *
 */
// /*public*/ class SpeedTableVarValue extends VariableValue implements PropertyChangeListener, ChangeListener {


/**
 * Create the object with a "standard format ctor".
 */
/*public*/ SpeedTableVarValue::SpeedTableVarValue(QString name, QString comment, QString cvName,
                          bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                          QString cvNum, QString mask, int minVal, int maxVal,
                          QMap<QString,CvValue*>* v, JLabel* status, QString stdname, int entries,
                                                  bool mfxFlag, QObject *parent)
 : VariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent)

{
 //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, v, status, stdname, parent);
 logit = new Logger("SpeedTaleVarValue");
 _progState = IDLE;
 retries = 0;
 onlyChanges = false;

 nValues = entries;
 _min = minVal;
 _max = maxVal;
 _range = maxVal-minVal;
 mfx = mfxFlag;

 if (false) //??
 {
  numCvs = nValues + 2;
  cvList = new QVector<QString>(numCvs,0);
  cvList->replace(nValues, VSTART_CV);
  cvList->replace(nValues + 1, VHIGH_CV);
 }
 else
 {
  numCvs = nValues;
  cvList = new QVector<QString>(numCvs,"0");
 }

 models = new QVector<BoundedRangeModel*>(nValues);

 // create the set of models
 for (int i=0; i<nValues; i++)
 {
  // populate cvList
  cvList->replace(i, QString::number(getCvNum().toInt()+i));
  // create each model
  DefaultBoundedRangeModel* j = new DefaultBoundedRangeModel(_range*i/(nValues-1)+_min, 0, _min, _max);
  models->replace(i, j);
  // connect each model to CV for notification
  // the connection is to cvNum through cvNum+nValues (28 values total typically)
  // The invoking code (e.g. VariableTableModel) must ensure the CVs exist
  // Note that the default values in the CVs are zero, but are the ramp
  // values here.  We leave that as work item 177, and move on to set the
  // CV states to "FromFile"
  CvValue* c = _cvMap->value(cvList->at(i));
  c->setValue(_range*i/(nValues-1)+_min);
  c->addPropertyChangeListener((PropertyChangeListener*)this);
  connect(c, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  c->setState(CvValue::FROMFILE);
 }

//    _defaultColor = (new QSlider()).getBackground();
}

/**
 * Create a NULL object.  Normally only used for tests and to pre-load classes.
 */
/*public*/ SpeedTableVarValue::SpeedTableVarValue(QObject *parent) : VariableValue(parent)
{}

/*public*/ QVariant SpeedTableVarValue::rangeVal() {
    logit->warn("rangeVal doesn't make sense for a speed table");
    return "Speed table";
}

/*public*/ QVector<CvValue *> SpeedTableVarValue::usesCVs() {
    QVector<CvValue*> retval = QVector<CvValue*>(numCvs);
    int i;
    for (i=0; i<numCvs; i++)
        retval.replace(i, _cvMap->value(cvList->at(i)));
    return retval;
}

/**
 * Called for new values of a slider.
 * <P>
 * Sets the CV(s) as needed.
 * @param e
 */
/*public*/ void SpeedTableVarValue::stateChanged(/*ChangeEvent* e*/QWidget* s)
{
 // e.getSource() points to the JSlider object - find it in the list
 //JSlider* j = (JSlider*) e->getSource();
 JSlider* j = (JSlider*)s;
 BoundedRangeModel* r = j->getModel();

 for (int i=0; i<nValues; i++)
 {
  if (r == models->at(i))
  {
   // found it, and i is useful!
   setModel(i, ((DefaultBoundedRangeModel*)r)->getValue());
   break; // no need to continue loop
  }
 }
 // notify that Value property changed
 prop->firePropertyChange("Value", QVariant(), VPtr<JSlider>::asQVariant(j));
}

void SpeedTableVarValue::setModel(int i, int value)
{  // value is _min to _max
 if (i < nValues && models->at(i)->getValue() != value)
  models->at(i)->setValue(value);
 // update the CV
 _cvMap->value(cvList->at(i))->setValue(value);
 // if programming, that's it
 if (isReading || isWriting) return;
 else if (i < nValues && !(mfx && (i == 0 || i == (nValues-1))))
 {
  forceMonotonic(i, value);
  matchPoints(i);
 }
}

/**
 * Check entries on either side to see if they are set monotonically.
 * If not, adjust.
 *
 * @param modifiedStepIndex number (index) of the entry
 * @param value  new value
 */
void SpeedTableVarValue::forceMonotonic(int modifiedStepIndex, int value)
{
 // check the neighbors, and force them if needed
 if (modifiedStepIndex > 0)
 {
  // left neighbour
  if (models->at(modifiedStepIndex-1)->getValue() > value)
  {
   setModel(modifiedStepIndex-1, value);
  }
 }
 if (modifiedStepIndex < nValues-1)
 {
  // right neighbour
  if (value > models->at(modifiedStepIndex+1)->getValue())
  {
   setModel(modifiedStepIndex+1, value);
  }
 }
}

/**
 * If there are fixed points specified, set linear
 * step settings to them.
 *
 */
void SpeedTableVarValue::matchPoints(int modifiedStepIndex) {
    if (stepCheckBoxes.isEmpty()) {
        // if no stepCheckBoxes, then GUI not present, and
        // no need to use the matchPoints algorithm
        return;
    }
    if (modifiedStepIndex<0)
        logit->error("matchPoints called with index too small: "+QString::number(modifiedStepIndex));
    if (modifiedStepIndex >= stepCheckBoxes.size())
        logit->error("matchPoints called with index too large: "+QString::number(modifiedStepIndex)
                    +" >= "+QString::number(stepCheckBoxes.size()));
    if (stepCheckBoxes.at(modifiedStepIndex) == NULL)
        logit->error("matchPoints found NULL checkbox "+QString::number(modifiedStepIndex));

    // don't do the match if this step isn't checked,
    // which is necessary to keep from an infinite
    // recursion
    if (!stepCheckBoxes.at(modifiedStepIndex)->isChecked()) return;
    matchPointsLeft(modifiedStepIndex);
    matchPointsRight(modifiedStepIndex);
}

void SpeedTableVarValue::matchPointsLeft(int modifiedStepIndex) {
    // search for checkbox if any
    for (int i = modifiedStepIndex-1; i >= 0 ; i--) {
        if (stepCheckBoxes.at(i)->isChecked()) {
            // now have two ends to adjust
            int leftval = _cvMap->value(cvList->at(i))->getValue();
            int rightval = _cvMap->value(cvList->at(modifiedStepIndex))->getValue();
            int steps = modifiedStepIndex-i;
            logit->debug("left found "+QString::number(leftval)+" "+QString::number(rightval)+" "+(steps));
            // loop to set values
            for (int j = i+1; j < modifiedStepIndex; j++) {
                int newValue = leftval + (rightval-leftval)*(j-i)/steps;
                logit->debug("left set "+QString::number(j)+" to "+QString::number(newValue));
                if (_cvMap->value(cvList->at(j))->getValue() != newValue)
                    _cvMap->value(cvList->at(j))->setValue(newValue);
            }
            return;
        }
    }
    // no match, so don't adjust
    return;
}

void SpeedTableVarValue::matchPointsRight(int modifiedStepIndex) {
    // search for checkbox if any
    for (int i = modifiedStepIndex+1; i < nValues ; i++) { // need at least one intervening point
        if (stepCheckBoxes.at(i)->isChecked()) {
            // now have two ends to adjust
            int rightval = _cvMap->value(cvList->at(i))->getValue();
            int leftval = _cvMap->value(cvList->at(modifiedStepIndex))->getValue();
            int steps = i-modifiedStepIndex;
            logit->debug("right found "+QString::number(leftval)+" "+QString::number(rightval)+" "+QString::number(steps));
            // loop to set values
            for (int j = modifiedStepIndex+1; j < i; j++) {
                int newValue = leftval + (rightval-leftval)*(j-modifiedStepIndex)/steps;
                logit->debug("right set "+QString::number(j)+" to "+QString::number(newValue));
                if (_cvMap->value(cvList->at(j))->getValue() != newValue)
                    _cvMap->value(cvList->at(j))->setValue(newValue);
            }
            return;
        }
    }
    // no match, so don't adjust
    return;
}

/**
 * Enforce mfx bounds conditions.
 *
 */
void SpeedTableVarValue::enforceEndPointsMfx() {
    if (mfx) {
        if (_cvMap->value(cvList->at(0))->getValue() != _min) {
            _cvMap->value(cvList->at(0))->setValue(_min);
        }
        if (_cvMap->value(cvList->at(nValues-1))->getValue() != _max) {
            _cvMap->value(cvList->at(nValues-1))->setValue(_max);
        }
    }
}

/*public*/ int SpeedTableVarValue::getState()  {
    int i;
    for (i=0; i<numCvs; i++)
        if (_cvMap->value(cvList->at(i))->getState() == UNKNOWN ) return UNKNOWN;
    for (i=0; i<numCvs; i++)
        if (_cvMap->value(cvList->at(i))->getState() == EDITED ) return EDITED;
    for (i=0; i<numCvs; i++)
        if (_cvMap->value(cvList->at(i))->getState() == FROMFILE ) return FROMFILE;
    for (i=0; i<numCvs; i++)
        if (_cvMap->value(cvList->at(i))->getState() == READ ) return READ;
    for (i=0; i<numCvs; i++)
        if (_cvMap->value(cvList->at(i))->getState() == STORED ) return STORED;
    logit->error("getState did not decode a possible state");
    return UNKNOWN;
}

// to complete this class, fill in the routines to handle "Value" parameter
// and to read/write/hear parameter changes.
/*public*/ QString SpeedTableVarValue::getValueString()
{
 QString buf;
 for (int i=0; i< models->count(); i++)
 {
  if (i!=0) buf.append(",");
  buf.append(QString::number(models->at(i)->getValue()));
 }
 return buf;
}
/*public*/ void SpeedTableVarValue::setIntValue(int i) {
    logit->warn("setIntValue doesn't make sense for a speed table: "+i);
}

/*public*/ int SpeedTableVarValue::getIntValue() {
    logit->warn("getValue doesn't make sense for a speed table");
    return 0;
}

/*public*/ QVariant SpeedTableVarValue::getValueObject() {
    return QVariant();
}

/*public*/ QWidget* SpeedTableVarValue::getCommonRep()  {
    logit->warn("getValue not implemented yet");
    return new QLabel("speed table");
}

/*public*/ void SpeedTableVarValue::setValue(int value) {
    logit->warn("setValue doesn't make sense for a speed table: "+value);
}

// implement an abstract member to set colors
void SpeedTableVarValue::setColor(QColor c) {
    // prop.firePropertyChange("Value", NULL, NULL);
}

/*public*/ QWidget* SpeedTableVarValue::getNewRep(QString format)
{
 const int GRID_Y_BUTTONS = 3;
 QSignalMapper* mapper = new QSignalMapper;
 //stepSliders = QList<JSlider*>();
 // put together a new panel in scroll pane
 QWidget* j = new QScrollArea();
#if 1
 QGridLayout* g = new QGridLayout();
 GridBagConstraints* cs = new GridBagConstraints();
 j->setLayout(g);

 initStepCheckBoxes();

 for (int i=0; i<nValues; i++)
 {
  cs->gridy = 0;
  cs->gridx = i;

  CvValue* cv = _cvMap->value(cvList->at(i));
  JSlider* s = new VarSlider(models->at(i), cv, i+1);
  //stepSliders.append(s);
  s->setOrientation(/*JSlider.VERTICAL*/Qt::Vertical);
  //s.addChangeListener(this);
  mapper->setMapping(s, s);
  connect(s, SIGNAL(valueChanged(int)), mapper, SLOT(map()));

  int currentState = cv->getState();
  int currentValue = cv->getValue();
  s->setValue(currentValue);
  s->setMinimum(_min);
  s->setMaximum(_max);

  DecVariableValue* decVal = new DecVariableValue("val"+QString::number(i),"","", false, false, false, false, cvList->at(i), "VVVVVVVV", _min, _max, _cvMap, _status, "");
  decVal->setValue(currentValue);
  decVal->setState(currentState);

  QWidget* v = decVal->getCommonRep();
  QFontMetrics fm(j->fontMetrics());
  ((JTextField*)v)->setMinimumWidth(fm.width("99999")*2);
  ((JTextField*)v)->setToolTip(tr("TextStep")
                            +" "+QString::number(i+1)+" CV "+(cvList->at(i)));
//  ((QWidget*)v)->setBorder(NULL);  // pack tighter

  if (mfx && (i == 0 || i == (nValues-1)))
  {
   ((JTextField*)v)->setReadOnly(true); // disable field editing
   s->setEnabled(false);    // disable slider adjustment
  }

  //g.setConstraints(v, cs);

  //if (i==0 && logit->isDebugEnabled()) logit->debug("Font size "+QString::number(v->getFont().getSize()));
  //float newSize = v->getFont().getSize() * 0.8f;
  //v->setFont(jmri.util.FontUtil.deriveFont(v.getFont(),newSize));
  //j.add ( v );
  g->addWidget(v, cs->gridy, cs->gridx, cs->rowSpan(),cs->colSpan());

  cs->gridy++;
  //g.setConstraints(s, cs);

  //j.add(s);
  g->addWidget(s, cs->gridy, cs->gridx, cs->rowSpan(),cs->colSpan());


  cs->gridy++;
  QCheckBox* b = stepCheckBoxes.at(i);

  //g.setConstraints(b, cs);
  //j.add(b, cs);
  g->addWidget(b, cs->gridy, cs->gridx, cs->rowSpan(),cs->colSpan());

  enforceEndPointsMfx();
 }
 connect(mapper, SIGNAL(mapped(QWidget*)), this, SLOT(stateChanged(QWidget*)));
 // add control buttons
 QFrame* k= new QFrame(j);
 QPushButton* b;
 QHBoxLayout* layout = new QHBoxLayout(j);
 k->setLayout(layout);
 layout->addWidget(b = new  QPushButton(tr("Force Straight"),k));
 b->setToolTip(tr("TooltipForceStraight"));
//    b.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent* /*e*/) {
//                doForceStraight(e);
//            }
//        });
 connect(b, SIGNAL(clicked()), this, SLOT(doForceStraight()));
 layout->addWidget(b = new QPushButton(tr("Match Ends"),k));
 b->setToolTip(tr("TooltipMatchEnds"));
//    b.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent* /*e*/) {
//                doMatchEnds(e);
//            }
//        });
 connect(b, SIGNAL(clicked()), this, SLOT(doMatchEnds()));
 layout->addWidget(b = new QPushButton(tr("Constan Ratio"),k));
 b->setToolTip(tr("TooltipConstantRatio"));
//    b.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent* /*e*/) {
//                doRatioCurve(e);
//            }
//        });
 connect(b, SIGNAL(clicked()), this, SLOT(doRatioCurve()));
 layout->addWidget(b = new QPushButton(tr("Log Curve"),k));
 b->setToolTip(tr("TooltipLogCurve"));
//    b.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent* /*e*/) {
//                doLogCurve(e);
//            }
//        });
 connect(b, SIGNAL(clicked()), this, SLOT(doLogCurve()));
 layout->addWidget(b = new QPushButton(tr("Shift Left"),k));
 b->setToolTip(tr("TooltipShiftLeft"));
//    b.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent* /*e*/) {
//                doShiftLeft(e);
//            }
//        });
 connect(b, SIGNAL(clicked()), this, SLOT(doShiftLeft()));
 layout->addWidget(b = new QPushButton(tr("Shift Right"),k));
 b->setToolTip(tr("TooltipShiftRight"));
//    b.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent* /*e*/) {
//                doShiftRight(e);
//            }
//        });
 connect(b, SIGNAL(clicked()), this, SLOT(doShiftRight()));
 cs->gridy = GRID_Y_BUTTONS;
 cs->gridx = 0;
 cs->gridwidth = GridBagConstraints::_RELATIVE;
 //g.setConstraints(k, cs);

 // add Vstart & Vhigh if applicable
 QFrame* l = new QFrame(j);
 QHBoxLayout* layout_l = new QHBoxLayout();
 QString ThisCV;
 CvValue* cv;
 QWidget* v;
 int currentState;
 int currentValue;
 DecVariableValue* decVal;
 QLabel* label;
 QString padding = "                                                    ";

 if (mfx)
 {
  ThisCV = VSTART_CV;
  cv = _cvMap->value(ThisCV);
  currentState = cv->getState();
  currentValue = cv->getValue();
  cv->addPropertyChangeListener((PropertyChangeListener*)this);
  connect(cv, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  decVal = new DecVariableValue("CV"+(ThisCV),"","", false, false, false, false, ThisCV, "VVVVVVVV", _min, _max, _cvMap, _status, "");
  decVal->setValue(currentValue);
  decVal->setState(currentState);
  v = decVal->getCommonRep();
  ((JTextField*)v)->setToolTip(tr("Sets the starting voltage at throttle speed step 1.")+" CV "+(ThisCV));
  //l.add ( v );
  layout_l->addWidget(v);

  label = new QLabel("Vstart", j);
  //l.add ( label );
  layout_l->addWidget(label);

  // because DGH hasn't yet mastered GridBagLayout
  label = new QLabel(padding);
  //l.add ( label );
  layout_l->addWidget(label);
  label = new QLabel(padding);
  //l.add ( label );
  layout_l->addWidget(label);
  label = new QLabel(padding);
  //l.add ( label );
  layout_l->addWidget(label);

  label = new QLabel("Vhigh");
  //l.add ( label );
  layout_l->addWidget(label);

  ThisCV = VHIGH_CV;
  cv = _cvMap->value(ThisCV);
  currentState = cv->getState();
  currentValue = cv->getValue();
  cv->addPropertyChangeListener((PropertyChangeListener*)this);
  decVal = new DecVariableValue("CV"+(ThisCV),"","", false, false, false, false, ThisCV, "VVVVVVVV", _min, _max,_cvMap, _status, "");
  decVal->setValue(currentValue);
  decVal->setState(currentState);
  v = decVal->getCommonRep();
  ((JTextField*)v)->setToolTip(tr("Sets the maximum voltage at full throttle.")+" CV "+(ThisCV));
  //l.add ( v );
  layout_l->addWidget(v);
 }

 QFrame* val = new QFrame();
 QVBoxLayout* vLayout = new QVBoxLayout();
 val->setLayout(vLayout);
 //val.add(j, BorderLayout.NORTH);
 vLayout->addWidget(j);
 //val.add(k, BorderLayout.CENTER);
 vLayout->addWidget(k);
 //if (mfx) {val.add(l, BorderLayout.SOUTH);}
 if(mfx) vLayout->addWidget(l);

 updateRepresentation(val);
 return val;
#endif
}

void SpeedTableVarValue::initStepCheckBoxes() {
    stepCheckBoxes =  QList<QCheckBox*>();
    for (int i=0; i<nValues; i++) {
        QCheckBox* b = new QCheckBox();
        b->setToolTip(tr("TooltipCheckToFix"));
        stepCheckBoxes.append(b);
    }
}

/**
 * Set the values to a straight line from _min to _max
 */
void SpeedTableVarValue::doForceStraight(JActionEvent* e) {
    _cvMap->value(cvList->at(0))->setValue(_min);
    _cvMap->value(cvList->at(nValues-1))->setValue(_max);
    doMatchEnds(e);
}
/**
 * Set the values to a straight line from existing ends
 */
void SpeedTableVarValue::doMatchEnds(JActionEvent* /*e*/) {
    int first = _cvMap->value(cvList->at(0))->getValue();
    int last = _cvMap->value(cvList->at(nValues-1))->getValue();
    logit->debug(" first="+QString::number(first)+" last="+QString::number(last));
    // to avoid repeatedly bumping up later values, push the first one
    // all the way up now
    _cvMap->value(cvList->at(0))->setValue(last);
    // and push each one down
    for (int i = 0; i<nValues; i++) {
        int value = first+i*(last-first)/(nValues-1);
        _cvMap->value(cvList->at(i))->setValue(value);
    }
    enforceEndPointsMfx();
}

/**
 * Set a constant ratio curve
 */
void SpeedTableVarValue::doRatioCurve(JActionEvent* /*e*/) {
    double first = _cvMap->value(cvList->at(0))->getValue();
    if (first<1.) first=1.;
    double last = _cvMap->value(cvList->at(nValues-1))->getValue();
    if (last<first+1) last = first+1.;
    double step = log(last/first)/(nValues-1);
    logit->debug("log ratio step is "+QString::number(step));
    // to avoid repeatedly bumping up later values, push the first one
    // all the way up now
    _cvMap->value(cvList->at(0))->setValue((int)qRound(last));
    // and push each one down
    for (int i = 0; i<nValues; i++) {
        int value = (int)(qFloor(first*qExp(step*i)));
        _cvMap->value(cvList->at(i))->setValue(value);
    }
    enforceEndPointsMfx();
}

/**
 * Set a log curve
 */
void SpeedTableVarValue::doLogCurve(JActionEvent* /*e*/) {
    double first = _cvMap->value(cvList->at(0))->getValue();
    double last = _cvMap->value(cvList->at(nValues-1))->getValue();
    if (last<first+1.) last = first+1.;
    double factor = 1./10.;
    // to avoid repeatedly bumping up later values, push the second one
    // all the way up now
    _cvMap->value(cvList->at(1))->setValue((int)qRound(last));
    // and push each one down (except the first, left as it was)
    double previous = first;
    double ratio = qPow(1.-factor, nValues-1.);
    double limit = last+(last-first)*ratio;
    for (int i = 1; i<nValues; i++) {
        previous = limit-(limit-first)*ratio/qPow(1.-factor, nValues-1.-i);
        int value = (int)(qFloor(previous));
        _cvMap->value(cvList->at(i))->setValue(value);
    }
    enforceEndPointsMfx();
}

/**
 * Shift the curve one CV to left.  The last entry is left unchanged.
 */
void SpeedTableVarValue::doShiftLeft(JActionEvent* /*e*/) {
    for (int i = 0; i<nValues-1; i++) {
        int value = _cvMap->value(cvList->at(i)+1)->getValue();
        _cvMap->value(cvList->at(i))->setValue(value);
    }
    enforceEndPointsMfx();
}

/**
 * Shift the curve one CV to right.  The first entry is left unchanged.
 */
void SpeedTableVarValue::doShiftRight(JActionEvent* /*e*/)
{
 for (int i = nValues-1; i>0; i--)
 {
  int value = _cvMap->value(QString(cvList->at(i).toInt()-1))->getValue();
        _cvMap->value(cvList->at(i))->setValue(value);
    }
    enforceEndPointsMfx();
}



/**
 * Notify the connected CVs of a state change from above
 * @param state
 */
/*public*/ void SpeedTableVarValue::setCvState(int state)
{
 _cvMap->value(cvList->at(0))->setState(state);
}

/*public*/ bool SpeedTableVarValue::isChanged()
{
 for (int i=0; i<numCvs; i++)
 {
  if (considerChanged(_cvMap->value(cvList->at(i))) )
  {
   // this one is changed, return true
   return true;
  }
 }
 return false;
}

/*public*/ void SpeedTableVarValue::readChanges()
{
    if (logit->isDebugEnabled()) logit->debug("readChanges() invoked");
    if (!isChanged()) return;
    onlyChanges = true;
    setBusy(true);  // will be reset when value changes
    if (_progState != IDLE) logit->warn("Programming state "+QString::number(_progState)+", not IDLE, in read()");
    isReading = true;
    isWriting = false;
    _progState = -1;
    retries = 0;
    if (logit->isDebugEnabled()) logit->debug("start series of read operations");
    readNext();
}

/*public*/ void SpeedTableVarValue::writeChanges() {
    if (logit->isDebugEnabled()) logit->debug("writeChanges() invoked");
    if (!isChanged()) return;
    onlyChanges = true;
    if (getReadOnly()) logit->error("unexpected write operation when readOnly is set");
    setBusy(true);  // will be reset when value changes
    VariableValue::setState(STORED);
    if (_progState != IDLE) logit->warn("Programming state "+QString::number(_progState)+", not IDLE, in write()");
    isReading = false;
    isWriting = true;
    _progState = -1;
    retries = 0;
    if (logit->isDebugEnabled()) logit->debug("start series of write operations");
    writeNext();
}


/*public*/ void SpeedTableVarValue::readAll() {
    if (logit->isDebugEnabled()) logit->debug("readAll() invoked");
    onlyChanges = false;
    setToRead(false);
    setBusy(true);  // will be reset when value changes
    if (_progState != IDLE) logit->warn("Programming state "+QString::number(_progState)+", not IDLE, in read()");
    isReading = true;
    isWriting = false;
    _progState = -1;
    retries = 0;
    if (logit->isDebugEnabled()) logit->debug("start series of read operations");
    readNext();
}

/*public*/ void SpeedTableVarValue::writeAll() {
    if (logit->isDebugEnabled()) logit->debug("writeAll() invoked");
    onlyChanges = false;
    if (getReadOnly()) logit->error("unexpected write operation when readOnly is set");
    setToWrite(false);
    setBusy(true);  // will be reset when value changes
    VariableValue::setState(STORED);
    if (_progState != IDLE) logit->warn("Programming state "+QString::number(_progState)+", not IDLE, in write()");
    isReading = false;
    isWriting = true;
    _progState = -1;
    retries = 0;
    if (logit->isDebugEnabled()) logit->debug("start series of write operations");
    writeNext();
}

void SpeedTableVarValue::readNext()
{
 // read operation start/continue
 // check for retry if needed
 if ( (_progState>=0) && (retries < RETRY_MAX)
         && (_cvMap->value(cvList->at(_progState))->getState() != CvValue::READ) )
 {
  // need to retry an error; leave progState (CV number) as it was
  retries++;
 }
 else
 {
  // normal read operation of next CV
  retries = 0;
  _progState++;  // progState is the index of the CV to handle now
 }

 if (_progState >= numCvs)
 {
  // done, clean up and return to invoker
  _progState = IDLE;
  isReading = false;
  isWriting = false;
  setBusy(false);
  return;
 }
 // not done, proceed to do the next
 CvValue* cv = _cvMap->value(cvList->at(_progState));
 int state = cv->getState();
 if (logit->isDebugEnabled()) logit->debug("invoke CV read index "+QString::number(_progState)+" cv state "+QString::number(state));
 if (!onlyChanges || considerChanged(cv) )
  cv->read(_status);
 else readNext(); // repeat until end
}

void SpeedTableVarValue::writeNext() {
    // write operation start/continue
    // check for retry if needed
    if ( (_progState>=0) && (retries < RETRY_MAX)
            && (_cvMap->value(cvList->at(_progState))->getState() != CvValue::STORED) ) {
        // need to retry an error; leave progState (CV number) as it was
        retries++;
    } else {
        // normal read operation of next CV
        retries = 0;
        _progState++;  // progState is the index of the CV to handle now
    }

    if (_progState >= numCvs) {
        _progState = IDLE;
        isReading = false;
        isWriting = false;
        setBusy(false);
        return;
    }
    CvValue* cv = _cvMap->value(cvList->at(_progState));
    int state = cv->getState();
    if (logit->isDebugEnabled()) logit->debug("invoke CV write index "+QString::number(_progState)+" cv state "+QString::number(state));
    if (!onlyChanges || considerChanged(cv) ) cv->write(_status);
    else writeNext();
}

// handle incoming parameter notification
/*public*/ void SpeedTableVarValue::propertyChange(PropertyChangeEvent* e)
{
 if (logit->isDebugEnabled()) logit->debug("property changed event - name: "
                                        +e->getPropertyName());
 // notification from CV; check for Value being changed
 if (e->getPropertyName()==("Busy") && (e->getNewValue())==(false))
 {
  // busy transitions drive an ongoing programming operation
  // see if actually done

  if (isReading) readNext();
  else if (isWriting) writeNext();
  else return;
 }
 else if (e->getPropertyName()==("State"))
 {
  CvValue* cv = _cvMap->value(cvList->at(0));
  if (logit->isDebugEnabled()) logit->debug("CV State changed to "+cv->getState());
  setState(cv->getState());
 }
 else if (e->getPropertyName()==("Value"))
 {
  // find the CV that sent this
  CvValue* cv = (CvValue*) e->getSource();
  int value = cv->getValue();
  // find the index of that CV
  for (int i=0; i<numCvs; i++)
  {
   if (_cvMap->value(cvList->at(i)) == cv)
   {
    // this is the one, so use this i
    setModel(i, value);
//    if(i < stepSliders.count())
//     stepSliders.at(i)->setValue(value);
    break;
   }
  }
  enforceEndPointsMfx();
 }
}
// clean up connections when done
/*public*/ void SpeedTableVarValue::dispose()
{
 if (logit->isDebugEnabled()) logit->debug("dispose");
 // the connection is to cvNum through cvNum+numCvs (28 values typical)
 for (int i=0; i<numCvs; i++)
 {
  _cvMap->value(cvList->at(i))->removePropertyChangeListener((PropertyChangeListener*)this);
 }

 // do something about the VarSlider objects
}
