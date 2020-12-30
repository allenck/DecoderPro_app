#include "combocheckbox.h"

//ComboCheckBox::ComboCheckBox(QObject *parent) :
//    QCheckBox(parent)
//{
//}
/* Represents a JComboBox as a JCheckBox
 *
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version
 */
// /*public*/ class ComboCheckBox extends JCheckBox {
class P1 : public PropertyChangeListener
{
public:
    P1(ComboCheckBox* comboCheckBox)
    {
     this->comboCheckBox = comboCheckBox;
    }
    ComboCheckBox* comboCheckBox;
    void propertyChange(PropertyChangeEvent *e)
    {
     comboCheckBox->originalPropertyChanged(e);
    }
};

ComboCheckBox::ComboCheckBox(QComboBox* box, EnumVariableValue* var) {
    //super();
    _var = var;
    _box = box;
    log = new Logger("ComboCheckBox");
    setBackground(getBackground());
    // listen for changes to ourself
    connect(this, SIGNAL(clicked()), this, SLOT(thisActionPerformed()));
//    addActionListener(l1 = new ActionListener());
//    {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            thisActionPerformed(e);
//        }
//    });
    // listen for changes to original
//    _box->addActionListener(l2 = new ActionListener());
    connect(_box, SIGNAL(currentIndexChanged(int)), this, SLOT(originalActionPerformed()));
//    {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            originalActionPerformed(e);
//        }
//    });
    // listen for changes to original state
    //_var->addPropertyChangeListener(p1 = new PropertyChangeListener());
    connect(_var, SIGNAL(valueChanged(int)), this, SLOT(originalActionPerformed()));
//    {
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//            originalPropertyChanged(e);
//        }
//    });

    // set initial value
    if (_box->currentIndex() == 1) setChecked(true);
}

void ComboCheckBox::thisActionPerformed(JActionEvent* /*e*/) {
    // update original state to this state
    if (isChecked()) _box->setCurrentIndex(1);
    else  _box->setCurrentIndex(0);
}

void ComboCheckBox::originalActionPerformed(JActionEvent* /*e*/) {
    // update this state to original state
    if (_box->currentIndex()==1) setChecked(true);
    else  setChecked(false);
}

void ComboCheckBox::originalPropertyChanged(PropertyChangeEvent* e) {
    // update this color from original state
    if (e->getPropertyName()=="State")
    {
        if (log->isDebugEnabled()) log->debug("State change seen");
        setBackground(_var->getBackground());
    }
    if(e->getPropertyName() == "Value")
    {

    }
}


/*public*/ void ComboCheckBox::dispose() {
//    removeActionListener(l1);
//    _box->removeActionListener(l2);
    _var->removePropertyChangeListener(p1);
    _var = NULL;
    _box = NULL;
}
QColor ComboCheckBox::getBackground()
{
 QColor c;
 QPalette p = _box->palette();
 QString ss = _box->styleSheet();
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
void ComboCheckBox::setBackground( QColor c )
{
// QPalette p = palette();
// p.setColor(QPalette::Inactive, QPalette::Background, c);
// setPalette(p);
 QColor oldC = getBackground();
 if(oldC != c)
 {
  QString ss = QString("QComboBox { background-color : rgb(%1,%2,%3);}").arg(c.red()).arg(c.green()).arg(c.blue());
  _box->setStyleSheet(ss);
 }
}
//void ComboCheckBox::boxToggled()
//{
// //_var->_value
// thisActionPerformed(NULL);
//}
