#include "indexedvarslider.h"
#include "defaultboundedrangemodel.h"

//IndexedVarSlider::IndexedVarSlider(QWidget *parent) :
//    QSlider(parent)
//{
//}
/* Extends a JSlider so that its color & value are consistent with
 * an underlying variable; we return one of these in IndexedVariableValue.getNewRep.
 *
 * @author    Howard G. Penny   Copyright (C) 2005
 * @version   $Revision: 17977 $
 */
// /*public*/ class IndexedVarSlider extends JSlider implements ChangeListener {


IndexedVarSlider::IndexedVarSlider(IndexedVariableValue* iVar, int min, int max, QWidget *parent) : JSlider(new DefaultBoundedRangeModel(min, 0, min, max),parent)
{
    //super(new DefaultBoundedRangeModel(min, 0, min, max));
    log = new Logger("IndexedVarSlider");
    setMinimum(min);
    setMaximum(max);
    _iVar = iVar;
    // get the original color right
    //setBackground(_iVar->getColor());
    // set the original value
    setValue((_iVar->getValueString()).toInt());
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(on_value_Changed(int)));
    // listen for changes here
//    addChangeListener(this);
    // listen for changes to associated variable
    _iVar->addPropertyChangeListener(/*new PropertyChangeListener()*/(PropertyChangeListener*)this);
    connect(_iVar->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//    {
//        /*public*/ void propertyChange(PropertyChangeEvent* e) {
//            originalPropertyChanged(e);
//        }
//    });
}

/*public*/ void IndexedVarSlider::stateChanged(ChangeEvent* e) {
    // called for new values of a slider - set the variable value as needed
    // e.getSource() points to the JSlider object - find it in the list
    JSlider* j = (JSlider*) e->getSource();
    BoundedRangeModel* r = j->getModel();

    _iVar->setIntValue(((DefaultBoundedRangeModel*)r)->getValue());
    _iVar->setState(AbstractValue::EDITED);
}

void IndexedVarSlider::originalPropertyChanged(PropertyChangeEvent* e) {
    if (log->isDebugEnabled()) log->debug("IndexedVarSlider saw property change: "+e->getPropertyName());
    // update this color from original state
    if (e->getPropertyName()==("State")) {
        //setBackground(_iVar->getColor());
    }
    if (e->getPropertyName()==("Value")) {
        int newValue = (((QLineEdit*)_iVar->getCommonRep())->text()).toInt();
        setValue(newValue);
    }
}

void IndexedVarSlider::on_value_Changed(int v)
{
    ChangeEvent* event = new ChangeEvent(this);
    stateChanged(event);
}
/*public*/ void IndexedVarSlider::propertyChange(PropertyChangeEvent* e) {
            originalPropertyChanged(e);
        }
