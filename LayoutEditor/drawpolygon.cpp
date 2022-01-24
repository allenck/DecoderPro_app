#include "drawpolygon.h"
#include "editor.h"
#include "controlpaneleditor.h"
#include "shapedrawer.h"
#include "positionableshape.h"
#include "positionablepolygon.h"
#include "pathiterator.h"
#include "generalpath.h"
#include "box.h"
#include <QVBoxLayout>
#include "loggerfactory.h"

DrawPolygon::DrawPolygon(): DrawFrame(NULL)
{

}

/**
 * <P>
 * @author Pete Cressman Copyright: Copyright (c) 2013
 * @version $Revision: 1 $
 *
 */
///*public*/ class DrawPolygon extends DrawFrame {

/**
 *
 */
//private static final long serialVersionUID = -8879310189293502065L;

/*public*/ DrawPolygon::DrawPolygon(QString which, QString title, ShapeDrawer* parent)
 : DrawFrame(which, title, parent)
{
 //super(which, title, parent);
 _curVertexIdx = -1;
 _vertices = new QList<QPoint>();
 _pShape = NULL;
 _editor = NULL;
 _editing = false;
 item = NULL;
}
/*private*/ /*static*/ /*final*/ int DrawPolygon::NEAR = PositionableShape::SIZE;

//@Override
/*protected*/ QWidget* DrawPolygon::makeParamsPanel(PositionableShape* ps)
{
 QWidget* panel = DrawFrame::makeParamsPanel(ps);
 _pShape = (PositionablePolygon*)ps;
 _editing = true;
 _pShape->editing(true);
  int x = ps->getX();
  int y = ps->getY();
  PathIterator* iter = ps->getPathIterator(NULL);
  QVector<float>* coord = new QVector<float>(6);
  _vertices = new QList<QPoint>(); // Added ACK
  while (!iter->isDone()) {
      iter->currentSegment(coord);
      _vertices->append(QPoint(x + qRound(coord->at(0)), y + qRound(coord->at(1))));
      iter->next();
  }
  _pShape->drawHandles();
  return panel;
}

/*protected*/ void DrawPolygon::setEditing(bool /*set*/)
{
 _editing = true;
}

//@Override
/*protected*/ void DrawPolygon::closingEvent(bool cancel)
{
 if (_pShape != NULL)
 {
  _pShape->editing(false);
  if(!near(_vertices->at(_vertices->count()-1), _vertices->at(0)))
  {
   _vertices->append(_vertices->at(0));
   QPoint spt = getStartPoint();
   _shape->setShape(makePath(spt));
  }
 }
 DrawFrame::closingEvent(cancel);
}

/*
 * Rubber Band line
 * @see jmri.jmrit.display.controlPanelEditor.shape.DrawFrame#drawLine(int, int)
 */
/*protected*/ void DrawPolygon::moveTo(int x, int y)
{
 if (!_editing)
 {
  _curX = x;
  _curY = y;
 }
}

/*protected*/ void DrawPolygon::anchorPoint(int x, int y)
{
 _curVertexIdx = -1;
 QPoint anchorPt =  QPoint(x, y);
 for (int i = 0; i < _vertices->size(); i++)
 {
  if (near(_vertices->at(i), anchorPt))
  {
   _curVertexIdx = i;
   _curX = x;
   _curY = y;
   return;
  }
 }
}

/*protected*/ void DrawPolygon::drawShape(QGraphicsScene* g)
{
 if (!_editing)
 {
  if (_vertices->size() == 0)
  {
   return;
  }

  if(_pShape != NULL && _pShape->_itemGroup != NULL)
  {
   QList<QGraphicsItem*> list = _pShape->_itemGroup->childItems();
   foreach (QGraphicsItem* i, list)
   {
    _pShape->_itemGroup->removeFromGroup(i);
    delete i;
   }
  }
  //else
  if(item  != NULL)
  {
   g->removeItem(item);
   delete item;
   item = NULL;
  }

//        Graphics2D g2d = (Graphics2D) g;
        //if(_pShape->_itemGroup)
   _lineWidth = _lineSlider->value();
//        BasicStroke stroke = new BasicStroke(_lineWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10f);

//        g2d.setColor(_lineColor);
//        g2d.setStroke(stroke);
   QPainterPath* path;
//   if(_pShape)
//   {
//    path = (QPainterPath*)_pShape->getShape();
//   }
//   else
    path = makePath(_curX, _curY);
//        path.lineTo(_curX, _curY);
//        g2d.draw(path);
   //QPainterPath* path = new QPainterPath(QPoint(0,0));
   //path->lineTo(_curX, _curY);
   item = new QGraphicsPathItem(*path);
   item->setBrush(QBrush(_fillColor));
   item->setPen(QPen(QBrush(_lineColor),_lineWidth, Qt::SolidLine,
                     Qt::FlatCap, Qt::MiterJoin));
   item->setPos(_curX, _curY);
//   _pShape->_itemGroup = new QGraphicsItemGroup();
//   _pShape->_itemGroup->addToGroup(item);
//   _pShape->setLocation(_curX, _curY);
//   _pShape->setDisplayLevel(ControlPanelEditor::MARKERS);
//   setPositionableParams(_pShape);
//   _pShape->updateSize();
//   _editor->putItem(_pShape);
   if(_pShape)
   {
    _pShape->item = item;
    _pShape->_itemGroup->addToGroup(item);
//    QPointF pt = _pShape->getLocation();
//    _pShape->_itemGroup->setPos(pt);
    _pShape->paint(g);
   }
   else
   {
    if(item && item->scene())
     log->warn(tr("item already has been added %1 %2").arg(__FILE__).arg(__LINE__));
    g->addItem(item);
   }
 }
}

//	@Override
// /*public*/ void DrawPolygon::paint(QGraphicsScene* g) {
// super.paint(g);

// if (_editing) {
// int hitIndex = _pShape.getHitIndex();
// if (hitIndex>=0) {
// super.paint(g);
// Graphics2D g2d = (Graphics2D)g;
// _lineWidth = _lineSlider.getValue();
// BasicStroke stroke = new BasicStroke(_lineWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10f);
// g2d.setColor(_lineColor);
// g2d.setStroke(stroke);
// GeneralPath path = new GeneralPath();
// if (hitIndex==0) {
// Point p0 = _vertices->get(1);
// path.moveTo(p0.x, p0.y);
// path.lineTo(_curX, _curY);
// } else if (hitIndex==_vertices->size()-1) {
// Point p0 = _vertices->get(hitIndex-1);
// path.moveTo(p0.x, p0.y);
// path.lineTo(_curX, _curY);
// } else {
// Point p0 = _vertices->get(hitIndex-1);
// Point p1 = _vertices->get(hitIndex+1);
// path.moveTo(p0.x, p0.y);
// path.lineTo(_curX, _curY);
// path.lineTo(p1.x, p1.y);
// }
// g2d.draw(path);
// }
// }
// }

 /**
 * Create a new PositionableShape
 */
//@Override
/*protected*/ bool DrawPolygon::makeFigure(QGraphicsSceneMouseEvent* event)
{
 if (_editing)
 {
   int hitIndex = _pShape->getHitIndex();
   if (hitIndex >= 0)
   {
    QPoint pt;
    //try {
    pt = _pShape->getInversePoint(event->scenePos().x(), event->scenePos().y());
    if(pt == QPoint())
    {
     Logger::error("Can't locate Hit Rectangles " /*+ nte->getMessage()*/);
     return false;
    }
    _vertices->removeAt(hitIndex);
    _vertices->insert(hitIndex, pt);
    _pShape->setShape((JShape*)makePath(getStartPoint()));

   }
   return false;
  }
  else
  {
   QPoint p = QPoint(event->scenePos().x(), event->scenePos().y());
   if (hitPolygonVertex(p))
   {
    if (near(_vertices->at(0), p))
    {
     _vertices->append(p);	// close polygon
    }
    Editor* ed = _parent->getEditor();
    QPoint spt = getStartPoint();
    PositionablePolygon* ps = new PositionablePolygon(ed, makePath(spt));
//    //ps->item = this->item;
//    if(ps->_itemGroup == NULL)
//    {
//     item->scene()->removeItem(item);
//     ps->_itemGroup = new QGraphicsItemGroup();
//    }
    if(item && item->scene())
    {
     item->scene()->removeItem(item);
     delete item;
     item = NULL;
    }
    QPainterPath* path = makePath(spt.x(), spt.y());
    ps->item = new QGraphicsPathItem(*path);
    ps->item->setBrush(QBrush(_fillColor));
    ps->item->setPen(QPen(QBrush(_lineColor),_lineWidth, Qt::SolidLine,
                      Qt::FlatCap, Qt::MiterJoin));
    ps->item->setPos(spt);

    ps->setLineWidth(_lineWidth);
    ps->setLineColor(_lineColor);
    ps->setFillColor(_fillColor);
    ps->_itemGroup->addToGroup(ps->item);
    ps->setHeight(ps->_itemGroup->boundingRect().height());
    ps->setWidth(ps->_itemGroup->boundingRect().width());
    ps->setLocation(spt);
    ps->setDisplayLevel(Editor::MARKERS);
    ps->updateSize();
    ps->setEditFrame(this);
    setDisplayParams(ps);
    ed->putItem(ps);
    return true;
   }
   _vertices->append(p);
   return false;
 }
}

/*protected*/ bool DrawPolygon::doHandleMove(int hitIndex, QPoint pt) {
    QPoint p = _vertices->at(hitIndex);
    p.setX(p.x() + pt.x());
    p.setY(p.y() + pt.y());
    _vertices->replace(hitIndex, p); // added ACK
    _pShape->setShape((JShape*)makePath(getStartPoint()));
    return false;
}

/**
 * @param pt is "startPoint" the upper left corner of the figure
 */
/*private*/ GeneralPath* DrawPolygon::makePath(QPointF pt) {
    GeneralPath* path = new GeneralPath(Path2D::WIND_EVEN_ODD, _vertices->size() + 1);
    path->moveTo(_vertices->at(0).x() - pt.x(), _vertices->at(0).y() - pt.y());
    for (int i = 1; i < _vertices->size(); i++) {
        path->lineTo(_vertices->at(i).x() - pt.x(), _vertices->at(i).y() - pt.y());
    }
    return path;
}

/*private*/ QPainterPath* DrawPolygon::makePath(float x, float y)
{
 QPainterPath* path = new QPainterPath(QPoint(x,y));
 path->moveTo(_vertices->at(0).x() - x, _vertices->at(0).y() - y);
 for (int i = 1; i < _vertices->size(); i++)
 {
  path->lineTo(_vertices->at(i).x() - x, _vertices->at(i).y() - y);
 }
 return path;
}


/**
 * "startPoint" will be the upper left corner of the figure
 *
 */
/*private*/ QPoint DrawPolygon::getStartPoint() {
    int x = _vertices->at(0).x();
    int y = _vertices->at(0).y();
    for (int i = 1; i < _vertices->size(); i++) {
        x = qMin(x, _vertices->at(i).x());
        y = qMin(y, _vertices->at(i).y());
    }
    QPoint p = QPoint(x, y);
    return p;
}

/*private*/ bool DrawPolygon::hitPolygonVertex(QPoint p)
{
 for (int i = 0; i < _vertices->size(); i++)
 {
  if (near(_vertices->at(i), p))
  {
   return true;
  }
 }
 return false;
}

/*static*/ /*private*/ bool DrawPolygon::near(QPoint p1, QPoint p2) {
    if (qAbs(p1.x() - p2.x()) < NEAR && qAbs(p1.y() - p2.y()) < NEAR) {
        return true;
    }
    return false;
}

/**
 * Editing is done. Update the existing PositionableShape
 */
//@Override
///*protected*/ void DrawPolygon::updateFigure(PositionableShape* p) {
//    PositionablePolygon* pos = (PositionablePolygon*) p;
//    _editing = false;
//    _pShape->editing(false);
//    setPositionableParams(pos);
//}
//@Override
void DrawPolygon::setDisplayWidth(int w) {
}

//@Override
void DrawPolygon::setDisplayHeight(int h) {
}

/*protected*/ void DrawPolygon::addVertex(bool up)
{
 if (_editing)
 {
  int hitIndex = _pShape->getHitIndex();
  QPoint r1 = _vertices->at(hitIndex);
  QPoint newVertex;
  if (up) {
      if (hitIndex == _vertices->size() - 1) {
          newVertex = QPoint(r1.x() + 20, r1.y() + 20);
      } else if (hitIndex >= 0) {
          QPoint r2 = _vertices->at(hitIndex + 1);
          newVertex = QPoint((r1.x() + r2.x()) / 2, (r1.y() + r2.y()) / 2);
      } else {
          return;
      }
      _pShape->_hitIndex++;
  } else {
      if (hitIndex > 0) {
          QPoint r2 = _vertices->at(hitIndex - 1);
          newVertex = QPoint((r1.x() + r2.x()) / 2, (r1.y() + r2.y()) / 2);
      } else if (hitIndex == 0) {
          newVertex = QPoint(r1.x() + 20, r1.y() + 20);
      } else {
          return;
      }
  }
  _vertices->insert(_pShape->getHitIndex(), newVertex);
  _pShape->setShape((JShape*)makePath(getStartPoint()));
  _pShape->drawHandles();
 }
}

/*protected*/ void DrawPolygon::deleteVertex()
{
 if (_editing)
 {
        int hitIndex = _pShape->getHitIndex();
        if (hitIndex < 0) {
            return;
        }
        _vertices->removeAt(hitIndex);
        _pShape->_hitIndex--;
        _pShape->setShape((JShape*)makePath(getStartPoint()));
        _pShape->drawHandles();
    }
}

/*public*/ QString DrawPolygon::getClassName()
{
 return "jmri.jmrit.display.controlPanelEditor.shape.DrawPolygon";
}


 /*private*/ /*final*/ /*static*/ Logger* DrawPolygon::log = LoggerFactory::getLogger("DrawPolygon");
