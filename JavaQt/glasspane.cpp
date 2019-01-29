#include "glasspane.h"
#include <QBoxLayout>
#include <QPainter>

GlassPane::GlassPane(QWidget* contentPane, QWidget *parent) : QWidget(parent)
{
 this->contentPane = contentPane;
 QVBoxLayout* layout;
 setLayout(layout = new QVBoxLayout);
 //layout->addWidget(new QLabel("Processing..."), 0, Qt::AlignCenter);
 resize(contentPane->rect().width(), contentPane->height());
 QPoint p = contentPane->pos();
 move(p.x(), p.y());
 setMouseTracking(true);

 setCursor(Qt::WaitCursor);
}
/*public*/ void GlassPane::dispose() {
//        this.removeMouseListener(listener);
//        this.removeMouseMotionListener(listener);
 setMouseTracking(false);
 close();
}
void GlassPane::paintEvent(QPaintEvent* /*event*/)
{
  QColor backgroundColor = palette().light().color();
  backgroundColor.setAlpha(100);
  QPainter customPainter(this);
  customPainter.fillRect(rect(),backgroundColor);
}

void GlassPane::mouseMoveEvent(QMouseEvent *event)
{
 //redispatchMouseEvent(event);
}
void GlassPane::mousePressEvent(QMouseEvent * event)
{
 //redispatchMouseEvent(event);
}
void GlassPane::mouseReleaseEvent(QMouseEvent * event)
{
// redispatchMouseEvent(event);
// if(inButton)   ((JToggleButton*)component)->animateClick();
}
