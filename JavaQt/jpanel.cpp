#include "jpanel.h"
#include "lineborder.h"
#include <QPaintEvent>
#include <QPainter>

JPanel::JPanel(QWidget* parent) :  QFrame(parent)
{

}

/*public*/ void JPanel::setBorder(Border* border)
{
  setFrameStyle(QFrame::Plain);
  setFrameShape(QFrame::Panel);
  setLineWidth(((LineBorder*)border)->lineWidth());
  if(((LineBorder*)border)->roundedCorners())
   setStyleSheet(tr("QFrame{background-color: red; border: %1px solid %2; border-radius: 10px;}").arg(((LineBorder*)border)->lineWidth()).arg(((LineBorder*)border)->color().name()));
  else
   setStyleSheet(tr("QFrame { border: %1px solid %2; }").arg(((LineBorder*)border)->lineWidth()).arg(((LineBorder*)border)->color().name()));
}

/*public*/ void JPanel::setBackground(QColor color)
{
 setStyleSheet(tr("QFrame {background-color: rgb(%1, %2, %3)}").arg(color.red()).arg(color.green()).arg(color.blue()));
}

//void JPanel::paintEvent(QPaintEvent *e)
//{
// QPainter* painter = new QPainter(this);
// paintComponent(painter);
// painter->end();
//}
///*public*/ void JPanel::paintComponent(QPainter *)
//{

//}
