#include "mygraphicsproxywidget.h"

MyGraphicsProxyWidget::MyGraphicsProxyWidget(QGraphicsItem *parent) :
    QGraphicsProxyWidget(parent){}
void MyGraphicsProxyWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
 QGraphicsProxyWidget::mouseMoveEvent(event);
}
void MyGraphicsProxyWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
 QGraphicsProxyWidget::mousePressEvent(event);
}
void MyGraphicsProxyWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
 QGraphicsProxyWidget::mouseReleaseEvent(event);
}
void MyGraphicsProxyWidget::keyPressEvent(QKeyEvent *event)
{
QGraphicsProxyWidget::keyPressEvent(event);
}
void MyGraphicsProxyWidget::keyReleaseEvent(QKeyEvent *event)
{
 QGraphicsProxyWidget::keyReleaseEvent(event);
}
