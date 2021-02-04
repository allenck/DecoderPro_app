#include "comboradiobuttons.h"
#include "variablevalue.h"
#include "actionevent.h"
#include <QDebug>

//ComboRadioButtons::ComboRadioButtons(QWidget *parent) :
//    QWidget(parent)
//{
//}
/* Represents a JComboBox as a JPanel of radio buttons.
 *
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version			$Revision: 17977 $
 */
// /*public*/ class ComboRadioButtons extends JPanel {


class NewListener : public PropertyChangeListener
{
public:
    NewListener(ComboRadioButtons* parent)
    {
     this->parent = parent;
    }
    ComboRadioButtons* parent;
public slots:
    void propertyChange(PropertyChangeEvent *e)
    {
     parent->originalPropertyChanged(e);
    }
};

ComboRadioButtons::ComboRadioButtons(QComboBox* box, EnumVariableValue* var, QWidget *parent) : QWidget(parent)
{
 //super();
 _var = var;
 _value = var->_value;
 _box = box;
 init();
}


void ComboRadioButtons::init()
{
 log = new Logger("ComboRadioButtons");
 g = new QButtonGroup();
 v = new QVector<QRadioButton*>();
 l1 = new QVector<ActionListener*>(_box->count());
 b1 = new QVector<QRadioButton*>(_box->count());
 vLayout = new QVBoxLayout();
 setLayout(vLayout);

 mapper = new QSignalMapper();
 // create the buttons, include in group, listen for changes by name
 for (int i=0; i<_box->count(); i++)
 {
  QString name = ((QString)(_box->itemText(i)));
  QRadioButton* b = new QRadioButton( name );
  b1->replace(i, b);
  connect(b, SIGNAL(toggled(bool)), mapper, SLOT(map()));
  //ActionEvent* actionEvent = new ActionEvent(b,i,name, i);
  mapper->setMapping(b, i);
//        b->setActionCommand(name);
//        b->addActionListener(l1[i] = new ActionListener());
//        {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                thisActionPerformed(e);
//            }
//        });
  v->append(b);
  addToPanel(b, i);
  g->addButton(b);
 }
 setColor();
 connect(mapper, SIGNAL(mapped(int)), SLOT(actionPerformed(int)));

//    setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
    // listen for changes to original
//    _box->addActionListener(l2 = new ActionListener());
//    {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            originalActionPerformed(e);
//        }
//    });
 connect(_box, SIGNAL(currentIndexChanged(int)), this, SLOT(originalActionPerformed()));
    // listen for changes to original state
    //_var->addPropertyChangeListener(p1 = new PropertyChangeListener());
 NewListener* listener;
  _var->addPropertyChangeListener(listener = new NewListener(this));
  connect(_var->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
//    {
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//            originalPropertyChanged(e);
//        }
//    });


 // set initial value
 v->at(_box->currentIndex())->setChecked(true);
}

/**
 * Add a button to the panel if desired.  In this class,
 * its always added, but in the On and Off subclasses, its only
 * added for certain ones
 */
void ComboRadioButtons::addToPanel(QRadioButton* b, int i) {
//    add(b);
 vLayout->addWidget(b);
}

void ComboRadioButtons::thisActionPerformed(JActionEvent* e)
{
    // update original state to selected button
//    _box->setSelectedItem(e.getActionCommand());
 if(e != NULL)
 {
  qDebug() << e->getActionCommand();
  if(qobject_cast<EnumVariableValue*>(_var) != NULL)
   ((EnumVariableValue*)_var)->setIntValue(e->getModifiers());
 }
}

void ComboRadioButtons::originalActionPerformed(JActionEvent* /*e*/) {
    // update this state to original state if there's a button
    // that corresponds
    while (_box->currentIndex()+1>=v->size()) {
        // oops - box has grown; add buttons!
        QRadioButton* b;
        v->append(b = new QRadioButton("Reserved value "+QString::number(v->size())));
        g->addButton(b);
    }
    v->at(_box->currentIndex())->setChecked(true);
}

void ComboRadioButtons::originalPropertyChanged(PropertyChangeEvent* e)
{
 // update this color from original state
 if (e->getPropertyName()==("State"))
 {
  if (log->isDebugEnabled()) log->debug("State change seen");
    setColor();
 }
 else if(e->getPropertyName() == "Value")
 {
     //setText(e->getNewValue().toString());
  if(qobject_cast<EnumVariableValue*>(_var)!= NULL)
  {
   EnumVariableValue* thisVar = (EnumVariableValue*)_var;
//   ((EnumVariableValue*)_var)->setValue(e->getNewValue().toInt());
   b1->at(e->getNewValue().toInt())->setChecked(true);
  }
  else
  {
   log->debug(tr("Missing cast for ")+_var->metaObject()->className());
   Q_ASSERT(false);
  }
 }
}
void ComboRadioButtons::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("Value"))
 {
  b1->at(1)->setChecked(e->getNewValue().toBool());
 }
}

/*protected*/ void ComboRadioButtons::setColor()
{
 for (int i = 0; i<v->size(); i++)
 {
  setBackground(v->at(i), getBackground(v->at(i)));
 }
}

/**
 * Setting tooltip both on this panel, and all
 * buttons inside
 */
/*public*/ void ComboRadioButtons::setToolTipText(QString t) {
    //super.setToolTipText(t);   // do default stuff
    setToolTip(t);
    // include all buttons
    foreach (QRadioButton* b, *b1) {
        b->setToolTip(t);
    }
}

/*public*/ void ComboRadioButtons::dispose() {
    for (int i = 0; i<l1->count(); i++) {
//            b1->at(i)->removeActionListener(l1->at(i));
        }
//    _box->removeActionListener(l2);
    _var->removePropertyChangeListener(p1);
    _var = NULL;
    _box = NULL;
}
/*public*/ void ComboRadioButtons::actionPerformed(int i)
{
 if(!b1->at(i)->isChecked()) return;
 if(qobject_cast<EnumVariableValue*>(_var)!=NULL)
  ((EnumVariableValue*)_var)->_value->setCurrentIndex(i);
 else
 {
  log->debug(tr("missing cast")+ _var->metaObject()->className());
  Q_ASSERT(false);
 }
 thisActionPerformed(NULL);
}
void ComboRadioButtons::on_valueChanged(EnumVariableValue * v)
{
 emit valueChanged(v);
 b1->at(v->_value->currentIndex())->setChecked(true);
}

QColor ComboRadioButtons::getBackground(QRadioButton* b)
{
    QColor c;
    QPalette p = b->palette();
    QString ss = b->styleSheet();
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
void ComboRadioButtons::setBackground(QRadioButton* b, QColor c)
{
    QColor oldC = getBackground(b);
    if(oldC != c)
    {
     QString ss = QString("QRadioButton { background-color : rgb(%1,%2,%3);}").arg(c.red()).arg(c.green()).arg(c.blue());
     b->setStyleSheet(ss);
    }
}

