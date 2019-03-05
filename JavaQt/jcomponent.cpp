#include "jcomponent.h"
#include <QFont>

JComponent::JComponent(QWidget *parent) : QWidget(parent)
{

}

bool JComponent::isOpaque() {return _opaque;}
QColor JComponent::getBackground()
{
 return palette().color(QWidget::backgroundRole());
}

void JComponent::setBackground(QColor c)
{
 setStyleSheet(tr("QWidget{background-color: rgb(%1,%2,%3)").arg(c.red()).arg(c.green()).arg(c.blue()));
}

void JComponent::setOpaque(bool)
{
 setStyleSheet("background-color: rgba(0,0,0,0)");
}

QFont JComponent::getFont()
{
 return font();
}
