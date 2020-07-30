#include "editscene.h"
#include <QGraphicsView>

#include <QMainWindow>

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

void EditScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
 emit sceneWheelMoveEvent(event);
 QGraphicsScene::wheelEvent(event);
}

void EditScene::repaint()
{
 update();
}

QColor EditScene::getBackground()
{
 QBrush b = views().at(0)->backgroundBrush();
 if(b == Qt::NoBrush)
  return QColor(Qt::white);
 return b.color();
}

/**
 * Returns the top-level ancestor of this component (either the
 * containing <code>Window</code> or <code>Applet</code>),
 * or <code>null</code> if this component has not
 * been added to any container.
 *
 * @return the top-level <code>Container</code> that this component is in,
 *          or <code>null</code> if not in any container
 */
/*public*/ QWidget* EditScene::getTopLevelAncestor()
{

 for(QObject* p = this; p != nullptr; p = p->parent())
 {
  //if(p instanceof Window || p instanceof Applet)
     if(qobject_cast<QMainWindow*>(p)!=nullptr)
  {
   return (QWidget*)p;
  }
 }
 return nullptr;
}
