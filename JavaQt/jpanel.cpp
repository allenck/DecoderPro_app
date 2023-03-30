#include "jpanel.h"
#include "lineborder.h"
#include <QPaintEvent>
#include <QPainter>
#include <QLayout>
#include "titledborder.h"

JPanel::JPanel(QWidget* parent) :  QFrame(parent)
{

}
JPanel::JPanel(QLayout* layout, QWidget* parent) :  QFrame(parent)
{
 setLayout(layout);
}

JPanel::JPanel(FlowLayout* layout, QWidget* parent) :  QFrame(parent)
{
 setLayout(layout);
}

/**
 * Set the value of the {@link #border} property.
 *
 * @param newBorder The new value of the property
 *
 * @see #getBorder
 */
/*public*/ void JPanel::setBorder(Border* newBorder)
{
#if 0
 border = newBorder;
  setFrameStyle(QFrame::Plain);
  setFrameShape(QFrame::Panel);
  setLineWidth(((LineBorder*)border)->lineWidth());
  if(((LineBorder*)border)->roundedCorners())
   setStyleSheet(tr("QFrame{background-color: red; border: %1px solid %2; border-radius: 10px;}").arg(((LineBorder*)border)->lineWidth()).arg(((LineBorder*)border)->color().name()));
  else
   setStyleSheet(tr("QFrame { border: %1px solid %2; }").arg(((LineBorder*)border)->lineWidth()).arg(((LineBorder*)border)->color().name()));

#else
 Border* oldBorder = getBorder();
  if (oldBorder == newBorder)
    return;

  if(layout()==nullptr)
   return;
  border = newBorder;
//  if(qobject_cast<TitledBorder*>(border->self()))
//  {
//   int left,top, right, bottom;
//   this->layout()->getContentsMargins(&left,&top, &right, &bottom);
//   QFont f =font();
//   QFontMetrics fm(f);
//   top +=fm.height();
//    this->layout()->setContentsMargins(left,top, right, bottom);
//  }
  if(qobject_cast<AbstractBorder*>(border->self()))
  {
   // make any ajustment to the layout such as for adding space for a titled border title.
   ((AbstractBorder*)border)->adjustLayout(this->layout());
  }
  //  {
//  QLayout* layout = this->layout();
//  if(layout == nullptr)
//  {
//   layout = new QVBoxLayout();
//   setLayout(layout);
//  }
//  layout->addWidget(border->self());

//  border->self()->setVisible(true);
//  //firePropertyChange("border", oldBorder, newBorder);
//  repaint();
#endif
}

/**
 * Get the value of the {@link #border} property.
 *
 * @return The property's current value
 *
 * @see #setBorder
 */
/*public*/ Border* JPanel::getBorder()
{
   return border;
}
#if 1
void JPanel::paintEvent(QPaintEvent * evt)
{
 QFrame::paintEvent(evt);
 QFrame::update();
 if(border)
 {
  QRect r = this->rect();
  border->paintBorder(this, r.x(), r.y(), r.width(), r.height());
 }
}
#endif
/*public*/ void JPanel::setBackground(QColor color)
{
 setStyleSheet(tr("QFrame {background-color: rgb(%1, %2, %3)}").arg(color.red()).arg(color.green()).arg(color.blue()));
}

// remove and hide all child widgets and delete layout.
/*public*/ void JPanel::removeAll()
{
 QList<QWidget*> children = findChildren<QWidget*>();
 QLayout* _layout = layout();
 if(_layout)
 {
  foreach(QWidget* w, children)
  {
   _layout->removeWidget(w);
   w->hide();
  }
  delete _layout;
  _layout = nullptr;
 }
}

/*public*/ QWidget* JPanel::getComponent(int index)
{
 QList<QWidget*> children = findChildren<QWidget*>();
 return children.at(index);
}

/*public*/ QColor JPanel::getForeground()
{
 return palette().color(QWidget::foregroundRole());
}

/*public*/ QColor JPanel::getBackground()
{
 return palette().color(QWidget::backgroundRole());
}

QLayout* JPanel::findParentLayout(QWidget* w)
{
   QLayout* layout;
   if (w->parentWidget() != nullptr)
      if (w->parentWidget()->layout() != nullptr)
          return layout = findParentLayout(w, w->parentWidget()->layout());
    return nullptr;
}

QLayout* JPanel::findParentLayout(QWidget* w, QLayout* topLevelLayout)
{
  for (QObject* qo: topLevelLayout->children())
  {
     QLayout* layout = qobject_cast<QLayout*>(qo);
     if (layout != nullptr)
     {
        if (layout->indexOf(w) > -1)
          return layout;
        else if (!layout->children().isEmpty())
        {
          layout = findParentLayout(w, layout);
          if (layout != nullptr)
            return layout;
        }
     }
  }
  return nullptr;
}

void JPanel::setLayout(QLayout *layout)
{
 if(this->layout())
  throw new IllegalArgumentException("panel already has a layout");
 QWidget::setLayout(layout);
}

/*public*/ void JPanel::addPropertyChangeListener(PropertyChangeListener* pl)
{
 pcs->addPropertyChangeListener(pl);
}
