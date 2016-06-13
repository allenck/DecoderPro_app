#include "indexedcombocheckbox.h"
#include <QCheckBox>

//IndexedComboCheckBox::IndexedComboCheckBox(QWidget *parent) :
//    QCheckBox(parent)
//{
//}
/* Represents a JComboBox as a JCheckBox for indexed CVs
 *
 * @author    Howard G. Penny   Copyright (C) 2005
 * @version   $Revision: 17977 $
 */
// /*public*/ class IndexedComboCheckBox extends JCheckBox {

IndexedComboCheckBox::IndexedComboCheckBox(QComboBox* box, IndexedEnumVariableValue* var, QWidget *parent) : QCheckBox(parent)
{
 //super();
 _var = var;
 _box = box;
 setBackground(getBackground());
 // listen for changes to ourself
 connect(this, SIGNAL(toggled(bool)), this, SLOT(thisActionPerformed()));
//    addActionListener(l1 = new ActionListener());
//    {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            thisActionPerformed(e);
//        }
//    });
 // listen for changes to original
 connect(_box, SIGNAL(currentIndexChanged(int)), this, SLOT(originalActionPerformed()));
//    _box->addActionListener(l2 = new ActionListener());
//    {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            originalActionPerformed(e);
//        }
//    });
    // listen for changes to original state
    //_var->addPropertyChangeListener(p1 = new PropertyChangeListener());
 connect(_var, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(originalActionPerformed()));
//    {
//        /*public*/ void propertyChange(PropertyChangeEvent e) {
//            originalPropertyChanged(e);
//        }
//    });

    // set initial value
    if (_box->currentIndex() == 1) setChecked(true);
}

void IndexedComboCheckBox::thisActionPerformed(ActionEvent* e) {
    // update original state to this state
    if (isChecked())
     _box->setCurrentIndex(1);
    else
     _box->setCurrentIndex(0);
}

void IndexedComboCheckBox::originalActionPerformed(ActionEvent* e) {
    // update this state to original state
    if (_box->currentIndex()==1) setChecked(true);
    else  setChecked(false);
}

void IndexedComboCheckBox::originalPropertyChanged(PropertyChangeEvent* e) {
    // update this color from original state
//    if (e->getPropertyName()==("State")) {
//        if (log.isDebugEnabled()) log.debug("State change seen");
//        setBackground(_var._value.getBackground());
//    }
}


/*public*/ void IndexedComboCheckBox::dispose() {
//    removeActionListener(l1);
//    _box.removeActionListener(l2);
    _var->removePropertyChangeListener(p1);
    l1 = l2 = NULL;
    p1 = NULL;
    _var = NULL;
    _box = NULL;
}
QColor IndexedComboCheckBox::getBackground()
{
 //return getBackground();
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
    return QColor();
}

void IndexedComboCheckBox::setBackground(QColor c)
{
 QColor oldC = getBackground();
 if(oldC != c)
 {
  QString ss = QString("QCheckBox { background-color : rgb(%1,%2,%3);}").arg(c.red()).arg(c.green()).arg(c.blue());
  setStyleSheet(ss);

 }
}
