#ifndef EDITPANEL_H
#define EDITPANEL_H

#include <QGraphicsScene>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QPainter>

class EditScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit EditScene(QObject *parent = 0);
    EditScene(QRectF, QObject* parent = 0);
    void repaint();

signals:
 void sceneMouseMove(QGraphicsSceneMouseEvent* e);
 void sceneMouseRelease(QGraphicsSceneMouseEvent* e);
 void sceneMousePress(QGraphicsSceneMouseEvent* e);
 void sceneMouseDoubleClick(QGraphicsSceneMouseEvent* e);
 void sceneDragEnter(QGraphicsSceneDragDropEvent* event);
 void sceneDragLeave(QGraphicsSceneDragDropEvent* event);
 void sceneDragMove(QGraphicsSceneDragDropEvent* event);
 void sceneDropEvent(QGraphicsSceneDragDropEvent*);
 void sceneContextMenu(QGraphicsSceneContextMenuEvent *event);
 void sceneKeyPress(QKeyEvent*);
 void sceneKeyRelease(QKeyEvent*);

public slots:
private:
 void mouseMoveEvent(QGraphicsSceneMouseEvent* e);
 void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
 void mousePressEvent(QGraphicsSceneMouseEvent* event);
 void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
 void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
 void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
 void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
 void dropEvent(QGraphicsSceneDragDropEvent *event);
 void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
 void keyPressEvent(QKeyEvent *event);
 void keyReleaseEvent(QKeyEvent *event);
};

class QGraphicsEllipseItem;
class QGraphicsArcItem : public QGraphicsEllipseItem {
public:
    QGraphicsArcItem ( qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0 ) :
        QGraphicsEllipseItem(x, y, width, height, parent) {
    }

protected:
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
    {
        painter->setPen(pen());
        painter->setBrush(brush());
        painter->drawArc(rect(), startAngle(), spanAngle());

//        if (option->state & QStyle::State_Selected)
//            qt_graphicsItem_highlightSelected(this, painter, option);
    }
};

class QGraphicsRoundRectItem : public QGraphicsRectItem {
public:
    QGraphicsRoundRectItem ( qreal x, qreal y, qreal width, qreal height, qreal xRaduis, qreal yRadius, QGraphicsItem * parent = 0 ) :
        QGraphicsRectItem(x, y, width, height, parent)
    {
     this->x = x;
     this->y = y;
     this->width = width;
     this->height = height;
     this->xRadius = xRaduis;
     this->yRadius = yRadius;
    }
    void setRect( qreal x, qreal y, qreal width, qreal height, qreal xRaduis, qreal yRadius)
    {
     this->x = x;
     this->y = y;
     this->width = width;
     this->height = height;
     this->xRadius = xRaduis;
     this->yRadius = yRadius;
    }

private:
    qreal x, y, width, height, xRadius, yRadius;
protected:
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
    {
        painter->setPen(pen());
        painter->setBrush(brush());
        painter->drawRoundedRect(x, y, width, height, xRadius, yRadius);

//        if (option->state & QStyle::State_Selected)
//            qt_graphicsItem_highlightSelected(this, painter, option);
    }
};

#endif // EDITPANEL_H
