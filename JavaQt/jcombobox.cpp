#include "jcombobox.h"
#include "eventobject.h"


JComboBox::JComboBox(QWidget* parent) : QComboBox(parent)
{
 connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
}

JComboBox::JComboBox(QStringList list, QWidget* parent) : QComboBox(parent)
{
 addItems(list);
 connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
}

/*public*/ bool JComboBox::isOpaque()
{
 return _opaque;
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
 emit itemStateChanged(new EventObject(this));
}
