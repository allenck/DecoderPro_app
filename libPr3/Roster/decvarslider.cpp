#include "decvarslider.h"
#include "defaultboundedrangemodel.h"
#include "shortaddrvariablevalue.h"

//DecVarSlider::DecVarSlider(QWidget *parent) :
//    QSlider(parent)
//{
//}
/* Extends a JSlider so that its color & value are consistent with
 * an underlying variable; we return one of these in DecValVariable.getNewRep.
 *
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version			$Revision: 17977 $
 */
// /*public*/ class DecVarSlider extends JSlider implements ChangeListener {

DecVarSlider::DecVarSlider(DecVariableValue* var, int min, int max, QWidget *parent) : JSlider(new DefaultBoundedRangeModel(min, 0, min, max),parent)
{
 //super(new DefaultBoundedRangeModel(min, 0, min, max, parent));
 logit = new Logger("DecVarSlider");
 setMinimum(min);
 setMaximum(max);
 _var = var;
 // get the original color right
 setBackground(_var->getColor());
 // set the original value
 QString val = _var->getValueString();
 setValue(val.toInt());
 // listen for changes here
 connect(this, SIGNAL(valueChanged(int)), this, SLOT(on_value_Changed(int)));
 addChangeListener((ChangeListener*)this);
 // listen for changes to associated variable
 // _var->addPropertyChangeListener(new PropertyChangeListener();
 DVSPropertyChangeListener* l = new DVSPropertyChangeListener(this);
//    {
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//            originalPropertyChanged(e);
//        }
//    });
 connect(_var->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
}

DVSPropertyChangeListener::DVSPropertyChangeListener(DecVarSlider *self) { this->self = self;}
void DVSPropertyChangeListener::propertyChange(PropertyChangeEvent* e) {self->originalPropertyChanged(e);}

void DecVarSlider::propertyChange(PropertyChangeEvent* e)
{
// if(qobject_cast<ShortAddrVariableValue*>(_var)!= NULL)
//  ((ShortAddrVariableValue*)_var)->setValue(/*value()*/e->getNewValue().toInt());
// else
// if(qobject_cast<DecVariableValue*>(_var)!= NULL)
//  ((DecVariableValue*)_var)->setValue(/*value()*/e->getNewValue().toInt());
//     else
// {
//  logit->debug(tr("missing cast ")+ _var->metaObject()->className());
//  Q_ASSERT(false);
// }
 originalPropertyChanged(e);
}

/*public*/ void DecVarSlider::stateChanged(ChangeEvent* e)
{
 // called for new values of a slider - set the variable value as needed
 // e.getSource() points to the JSlider object - find it in the list
 JSlider* j = (JSlider*) e->getSource();
 BoundedRangeModel* r = j->getModel();

 //_var->setIntValue(((DefaultBoundedRangeModel*)r)->getValue());
 ((DefaultBoundedRangeModel*)r)->setValue(value());
 _var->setValue(value());
 _var->setState(AbstractValue::EDITED);
}


void DecVarSlider::originalPropertyChanged(PropertyChangeEvent* e)
{
 if (logit->isDebugEnabled()) logit->debug("VarSlider saw property change: "+e->getPropertyName());
 // update this color from original state
 if (e->getPropertyName()==("State"))
 {
  setBackground(_var->getColor());
 }
 if (e->getPropertyName()==("Value"))
 {
  int newValue = (((QLineEdit*)_var->getCommonRep())->text()).toInt();
  //int newValue = e->getNewValue().toInt();
  setValue(newValue);
 }
}
void DecVarSlider::on_value_Changed(int v)
{
 ChangeEvent* event = new ChangeEvent(this);
 stateChanged(event);
}

QColor DecVarSlider::getBackground()
{
 QColor c;
 QPalette p = palette();
 QString ss = styleSheet();
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
}
void DecVarSlider::setBackground(QColor c)
{
 QString ss = QString("QSlider { background-color : rgb(%1,%2,%3);}").arg(c.red()).arg(c.green()).arg(c.blue());
 setStyleSheet(ss);
}
