#ifndef DRAWPOLYGON_H
#define DRAWPOLYGON_H
#include "drawframe.h"

class QGraphicsPathItem;
class GeneralPath;
class QGraphicsScene;
class Editor;
class PositionablePolygon;
class DrawPolygon : public DrawFrame
{
 Q_OBJECT
 public:
  DrawPolygon();
  /*public*/ DrawPolygon(QString which, QString title, ShapeDrawer* parent);
  /*public*/ void paint(QGraphicsScene* g);
  /*public*/ QString getClassName();

 private:
  static Logger* log;
  QList<QPoint>* _vertices;
  QGraphicsPathItem* item;
     int _curX;
     int _curY;
     int _curVertexIdx = -1;
     /*private*/ static /*final*/ int NEAR;// = PositionableShape.SIZE;
     PositionablePolygon* _pShape;
    /*private*/ bool _editing;
     static /*private*/ bool near(QPoint p1, QPoint p2);
     /*private*/ GeneralPath* makePath(QPointF pt);
     /*private*/ QPainterPath* makePath(float x, float y);
     Editor* _editor;
     /*private*/ QPoint getStartPoint();
     /*private*/ bool hitPolygonVertex(QPoint p);
     void setDisplayWidth(int w) ;
     void setDisplayHeight(int h);

 protected:
     /*protected*/ void closingEvent(bool);
     /*protected*/ void moveTo(int x, int y);
     /*protected*/ void anchorPoint(int x, int y);
     /*protected*/ void drawShape(QGraphicsScene* g);
     /*protected*/ bool makeFigure(QGraphicsSceneMouseEvent* event);
     ///*protected*/ void updateFigure(PositionableShape* p);
     /*protected*/ void addVertex(bool up);
     /*protected*/ void deleteVertex();
     /*protected*/ bool doHandleMove(int hitIndex, QPoint pt);
     /*protected*/ QWidget* makeParamsPanel(PositionableShape* ps);
     /*protected*/ void setEditing(bool set);

friend class ShapeDrawer;
friend class PositionablePolygon;
};

#endif // DRAWPOLYGON_H
