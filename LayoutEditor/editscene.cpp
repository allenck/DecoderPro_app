#include "editscene.h"

EditScene::EditScene(QObject *parent) :
    QGraphicsScene(parent)
{
}
EditScene::EditScene(QRectF rect, QObject *parent) : QGraphicsScene(rect, parent)
{

}

void EditScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    emit sceneMouseMove(e);
 QGraphicsScene::mouseMoveEvent(e);
 QPointF pos = e->scenePos();
}
void EditScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    emit sceneMouseRelease(e);
 QGraphicsScene::mouseReleaseEvent(e);
}
void EditScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
 emit sceneMousePress(event);
 QGraphicsScene::mousePressEvent(event);
}
void EditScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
 emit sceneMouseDoubleClick(event);
 QGraphicsScene::mouseDoubleClickEvent(event);
}
void EditScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
 emit sceneDragEnter(event);
}
void EditScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
 emit sceneDragLeave(event);
}
void EditScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
 emit sceneDragMove(event);
}
void EditScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
 emit sceneDropEvent(event);
}
void EditScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
 emit sceneContextMenu(event);
    QGraphicsScene::contextMenuEvent(event);
}
void EditScene::keyPressEvent(QKeyEvent *event)
{
 emit sceneKeyPress(event);
 QGraphicsScene::keyPressEvent(event);
}
void EditScene::keyReleaseEvent(QKeyEvent *event)
{
 emit sceneKeyRelease(event);
 QGraphicsScene::keyReleaseEvent(event);
}

void EditScene::repaint()
{
 update();
}
