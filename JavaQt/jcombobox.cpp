#include "jcombobox.h"
#include "eventobject.h"
#include "itemlistener.h"
#include "itemevent.h"
#include "exceptions.h"

JComboBox::JComboBox(QWidget* parent) : QComboBox(parent)
{
 connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
 cbModel = new QStringListModel();
 setModel(cbModel);
}

JComboBox::JComboBox(QStringList list, QWidget* parent) : QComboBox(parent)
{
 connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
 cbModel = new QStringListModel();
 setModel(cbModel);
 addItems(list);
}

JComboBox::JComboBox(ComboBoxModel* model, QWidget* parent)
{

}

/*public*/ bool JComboBox::isOpaque()
{
 return _opaque;
}
/*public*/ QColor JComboBox::getForeground()
{
 return palette().color(QWidget::foregroundRole());
}
/*public*/ QColor JComboBox::getBackground()
{
 return palette().color(QWidget::backgroundRole());
}
/*public*/ void JComboBox::setBackground(QColor c)
{
 setStyleSheet(tr("QWidget{background-color: rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue()));
}
/*public*/ void JComboBox::setOpaque(bool b)
{
 _opaque = b;
}
/*public*/ QFont JComboBox::getFont()
{
 return font();
}

/*public*/ void JComboBox::setFont(QFont)
{

}

void JComboBox::currentIndexChanged(int)
{
 ItemEvent* itemEvent = new ItemEvent(this);
// if(currentData().isValid())
//  itemEvent->setItem(currentData());
 emit itemStateChanged(itemEvent);
}


/*public*/ void JComboBox::addChangeListener(ChangeListener* l)
{
 //listeners.append(l);
 connect(this, SIGNAL(stateChanged(ChangeEvent*)), l, SLOT(stateChanged(ChangeEvent*)));

}

/*public*/ void JComboBox::removeChangeListener(ChangeListener* l)
{
 //listeners.removeOne(l);
 disconnect(this, SIGNAL(stateChanged(ChangeEvent*)), l, SLOT(stateChanged(ChangeEvent*)));
}
/*public*/ void JComboBox::addFocusListener(FocusListener* l)
{
 //listeners.append(l);
 connect(this, SIGNAL(stateChanged(ChangeEvent*)), l, SLOT(stateChanged(ChangeEvent*)));

}
/*public*/ void JComboBox::removeFocusListener(FocusListener *l)
{
 //listeners.removeOne(l);
 disconnect(this, SIGNAL(stateChanged(ChangeEvent*)), l, SLOT(stateChanged(ChangeEvent*)));
}

/*private*/ void JComboBox::focusInEvent(QFocusEvent* e)
{
 emit focusGained(new FocusEvent());
}

/*private*/ void JComboBox::focusOutEvent(QFocusEvent* e)
{
 emit focusLost(new FocusEvent());
}

/*public*/ void JComboBox::addItemListener(ItemListener* listener)
{
 connect(this, SIGNAL(itemStateChanged(ItemEvent*)), listener, SLOT(itemStateChanged(ItemEvent*)));
}

/*public*/ QStringList JComboBox::itemList(){
 return cbModel->stringList();
}

/*public*/ QVariant JComboBox::getItemAt(int i)
{
 //return itemData(i);
 return map.value(itemText(i));
}

/*public*/ void JComboBox::clear()
{
 map.clear();
 QComboBox::clear();
}

/*public*/ QVariant JComboBox::currentData() {
 return map.value(QComboBox::currentText());
}

/*public*/ QVariant JComboBox::itemData(int index)
{
 if(index >= QComboBox::count())
  throw new IndexOutOfBoundsException();
 QVariant v = QComboBox::itemData(index);
 if(v.isValid())
  return v;
 return map.value(itemText(index));
}


/*public*/ void JComboBox::addItem(QString text,  QVariant data)
{
 if(data.isValid())
 {
  map.insert(text, data);
 }
 QComboBox::addItem(text, data);
}

/*public*/ bool JComboBox::isSelected()
{
 return  (currentIndex() >= -1);
}
