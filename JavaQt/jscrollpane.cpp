#include "jscrollpane.h"
#include "lineborder.h"
#include "titledborder.h"
#include <QVBoxLayout>

/* QScrollArea that can have a border*/

JScrollPane::JScrollPane(QWidget* parent) : JPanel(parent)
{
 QVBoxLayout* l;
 setLayout(l = new QVBoxLayout());
 sa = new QScrollArea();
 //l->setContentsMargins(0,0,0,0);
 l->addWidget(sa);
}
/**
 * Set the value of the {@link #border} property.
 *
 * @param newBorder The new value of the property
 *
 * @see #getBorder
 */
/*public*/ void JScrollPane::setBorder(Border* newBorder)
{
 Border* oldBorder = getBorder();
  if (oldBorder == newBorder)
    return;
  if(this->layout() == nullptr)
   setLayout(new QVBoxLayout());

  border = newBorder;
  if(qobject_cast<AbstractBorder*>(border->self()))
  {
   // make any ajustment to the layout such as for adding space for a titled border title.
   ((AbstractBorder*)border)->adjustLayout(this->layout());
  }
}

/**
 * Get the value of the {@link #border} property.
 *
 * @return The property's current value
 *
 * @see #setBorder
 */
/*public*/ Border* JScrollPane::getBorder()
{
   return border;
}

void JScrollPane::paintEvent(QPaintEvent * evt)
{
 QWidget::paintEvent(evt);
 QWidget::update();
 if(border)
 {
  QRect r = this->rect();
  border->paintBorder(this, r.x(), r.y(), r.width(), r.height());
 }
}

/*public*/ void JScrollPane::setWidget(QWidget* w)
{
 sa->setWidget(w);
}

/*public*/ void JScrollPane::setWidgetResizable(bool b)
{
 sa->setWidgetResizable(b);
}
