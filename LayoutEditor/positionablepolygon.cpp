#include "positionablepolygon.h"
#include "pathiterator.h"
#include "drawpolygon.h"
#include "generalpath.h"
#include "editor.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>

PositionablePolygon::PositionablePolygon() : PositionableShape()
{
 setObjectName("PositionablePolygon");
}
/**
 * PositionableRoundRect.
 * <P>
 * @author Pete cresman Copyright (c) 2013
 */
///*public*/ class PositionablePolygon extends PositionableShape {

/**
 *
 */
//private static final long serialVersionUID = 6175122309400060896L;

/*public*/ PositionablePolygon::PositionablePolygon(Editor* editor)
 : PositionableShape(editor)
{
    //super(editor);
 _editing = false;
 setObjectName("PositionablePolygon");
}

/*public*/ PositionablePolygon::PositionablePolygon(Editor* editor, JShape* shape)
 : PositionableShape(editor, shape)
{
    //super(editor, shape);
 _editing = false;
 setObjectName("PositionablePolygon");
}

//@Override
/*public*/ Positionable* PositionablePolygon::deepClone() {
    PositionablePolygon* pos = new PositionablePolygon(_editor);
    return finishClone(pos);
}

/*protected*/ Positionable* PositionablePolygon::finishClone(PositionablePolygon* pos) {

    GeneralPath* path = new GeneralPath(Path2D::WIND_EVEN_ODD);
    path->append(getPathIterator(NULL), false);
    /*
     PathIterator iter = _shape.getPathIterator(NULL);
     float[] coord = new float[6];
     while (!iter.isDone()) {
     int type = iter.currentSegment(coord);
     switch (type) {
     case PathIterator.SEG_MOVETO:
     path.moveTo(coord->at(0), coord->at();
     break;
     case PathIterator.SEG_LINETO:
     path.lineTo(coord->at(0), coord->at();
     break;
     case PathIterator.SEG_QUADTO:
     path.quadTo(coord->at(0), coord->at(, coord->at(2), coord->at(3));
     break;
     case PathIterator.SEG_CUBICTO:
     path.curveTo(coord->at(0), coord->at(, coord->at(2), coord->at(3), coord->at(4), coord[53]);
     break;
     case PathIterator.SEG_CLOSE:
     path.closePath();
     break;
     }
     }
     */
    pos->setShape((JShape*)path);
    pos->_handleGroup = _handleGroup;


    return PositionableShape::finishClone(pos);
}

//@Override
/*public*/ bool PositionablePolygon::setEditItemMenu(QMenu* popup) {
    QString txt = tr("Edit %1 Shape...").arg(tr("Polygon"));
    PolygonAction* act;
    popup->addAction(act = new PolygonAction(txt, this));// {
//        /**
//         *
//         */
//        //private static final long serialVersionUID = 6740597325568794368L;
//        PositionablePolygon* ps;

//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if (_editFrame == NULL) {
//                _editFrame = new DrawPolygon(getEditor(), "polygon", ps);
//                setEditParams();
//            }
//        }

//        javax.swing.AbstractAction init(PositionablePolygon p) {
//            ps = p;
//            return this;
//        }
//    }
 act->init(this);
 connect(act, SIGNAL(triggered(bool)), act, SLOT(actionPerformed()));
    return true;
}

/*public*/ void PolygonAction::actionPerformed(JActionEvent *e)
{
 if (ps->_editFrame == NULL)
 {
  ps->_editFrame = new DrawPolygon("editShape", "Polygon", (ShapeDrawer*)ps);
  ps->setEditParams();
  ps->getEditor()->_highlightcomponent = QRectF();
  ps->updateScene();
 }
}

PolygonAction* PolygonAction::init(PositionablePolygon* p) {
    ps = p;
    return this;
}

/*protected*/ void PositionablePolygon::editing(bool edit) {
    _editing = edit;
}

/*protected*/ int PositionablePolygon::getHitIndex() {
    return _hitIndex;
}

//@Override
/*public*/ void PositionablePolygon::removeHandles() {
    _vertexHandles = NULL;
    PositionableShape::removeHandles();
}

//@Override
/*public*/ void PositionablePolygon::drawHandles()
{
 if (_editing)
 {
  _vertexHandles = new QList<QRect>();
  PathIterator* iter = getPathIterator(NULL);
  QVector<float>* coord = new QVector<float>(6);
  while (!iter->isDone())
  {
   iter->currentSegment(coord);
   int x = qRound(coord->at(0));
   int y = qRound(coord->at(1));
   _vertexHandles->append(QRect(x - SIZE, y - SIZE, 2 * SIZE, 2 * SIZE));
   iter->next();
  }
 }
 else
 {
  PositionableShape::drawHandles();
 }
}

//@Override
/*public*/ void PositionablePolygon::doMousePressed(QGraphicsSceneMouseEvent* event)
{
 _hitIndex = -1;
 if (!_editor->isEditable())
 {
     return;
 }
 if (_editing)
 {
  if (_vertexHandles != NULL)
  {
   _lastX = event->scenePos().x();
   _lastY = event->scenePos().y();
   int x = _lastX - getX();//-SIZE/2;
   int y = _lastY - getY();//-SIZE/2;
   QPoint pt;
   //try {
       pt = getInversePoint(x, y);
   if(pt == QPoint())
   {
       log->error("Can't locate Hit Rectangles "/* + nte.getMessage()*/);
       return;
   }
   for (int i = 0; i < _vertexHandles->size(); i++)
   {
    if (_vertexHandles->at(i).contains(pt.x(), pt.y()))
    {
        _hitIndex = i;
    }
   }
  }
 }
 else
 {
  PositionableShape::doMousePressed(event);
 }
}

//@Override
/*protected*/ bool PositionablePolygon::doHandleMove(QGraphicsSceneMouseEvent* event)
{
 if (_hitIndex >= 0 && _editor->isEditable())
 {
  if (_editing)
  {
   QPoint pt = QPoint(event->scenePos().x() - _lastX, event->scenePos().y() - _lastY);
   /*        		try {
    pt = getInversePoint(event.getX()-_lastX, event.getY()-_lastY);
    } catch (java.awt.geom.NoninvertibleTransformException nte) {
    log.error("Can't locate Hit Rectangles "+nte.getMessage());
    return false;
    }*/
   QRect rect = _vertexHandles->at(_hitIndex);
   rect.setX(rect.x() + pt.x());
   rect.setY(rect.y() + pt.y());
   if (_editFrame != NULL)
   {
    if (event->scenePos().x() - getX() < 0) {
        _editor->moveItem(this, event->scenePos().x() - getX(), 0);
    } else if (isLeftMost(rect.x())) {
        _editor->moveItem(this, event->scenePos().x() - _lastX, 0);
    }
    if (event->scenePos().y() - getY() < 0) {
        _editor->moveItem(this, 0, event->scenePos().y() - getY());
    } else if (isTopMost(rect.y())) {
        _editor->moveItem(this, 0, event->scenePos().y() - _lastY);
    }

    ((DrawPolygon*) _editFrame)->doHandleMove(_hitIndex, pt);
   }
   _lastX = event->scenePos().x();
   _lastY = event->scenePos().y();
  }
  else
  {
   float deltaX = event->scenePos().x() - _lastX;
   float deltaY = event->scenePos().y() - _lastY;
   float width = _width;
   float height = _height;
   if (_height < SIZE || _width < SIZE) {
       log->error("Bad size _width= " + QString::number(_width) + ", _height= " + QString::number(_height));
   }
   GeneralPath* path = NULL;
   switch (_hitIndex)
   {
    case TOP:
        if (height - deltaY > SIZE) {
            path = scale(1, (height - deltaY) / height);
            _editor->moveItem(this, 0, (int) deltaY);
        } else {
            path = scale(1, SIZE / height);
            _editor->moveItem(this, 0, _height - SIZE);
        }
        break;
    case RIGHT:
        path = scale(qMax(SIZE / width, (width + deltaX) / width), 1);
        break;
    case BOTTOM:
        path = scale(1, qMax(SIZE / height, (height + deltaY) / height));
        break;
    case LEFT:
        if (_width - deltaX > SIZE) {
            path = scale((width - deltaX) / width, 1);
            _editor->moveItem(this, (int) deltaX, 0);
        } else {
            path = scale(SIZE / width, 1);
            _editor->moveItem(this, _width - SIZE, 0);
        }
        break;
   }
   if (path != NULL) {
       setShape((JShape*)path);
   }
  }
  drawHandles();
  repaint();
  updateSize();
  _lastX = event->scenePos().x();
  _lastY = event->scenePos().y();
  return true;
 }
 return false;
}

/*private*/ bool PositionablePolygon::isLeftMost(int x)
{
    QListIterator<QRect> it(*_vertexHandles);
    while (it.hasNext()) {
        if (it.next().x() < x) {
            return false;
        }
    }
    return true;
}

/*private*/ bool PositionablePolygon::isTopMost(int y)
{
 QListIterator<QRect> it(*_vertexHandles);
    while (it.hasNext()) {
        if (it.next().y() < y) {
            return false;
        }
    }
    return true;
}

/*private*/ GeneralPath* PositionablePolygon::scale(float ratioX, float ratioY) {
//    	log.info("scale("+ratioX+" , "+ratioY+")");
    GeneralPath* path = new GeneralPath(Path2D::WIND_EVEN_ODD);
    PathIterator* iter = getPathIterator(NULL);
    QVector<float>* coord = new QVector<float>(6);
    while (!iter->isDone()) {
        int type = iter->currentSegment(coord);
        switch (type) {
            case PathIterator::SEG_MOVETO:
                path->moveTo(coord->at(0) * ratioX, coord->at(1) * ratioY);
                break;
            case PathIterator::SEG_LINETO:
                path->lineTo(coord->at(0) * ratioX, coord->at(1) * ratioY);
                break;
            case PathIterator::SEG_QUADTO:
                path->quadTo(coord->at(0), coord->at(1), coord->at(2), coord->at(3));
                break;
            case PathIterator::SEG_CUBICTO:
                path->curveTo(coord->at(0), coord->at(1), coord->at(2), coord->at(3), coord->at(4), coord->at(5));
                break;
            case PathIterator::SEG_CLOSE:
                path->closePath();
                break;
        }
//    		log.debug("type= "+type+"  x= "+coord->at(0)+", y= "+ coord->at();
        iter->next();
    }
    return path;
}

//@Override
/*protected*/ void PositionablePolygon::paintHandles(QGraphicsScene* g2d)
{
 if (_editing)
 {
  if (_vertexHandles != NULL)
  {
   //g2d.setStroke(new java.awt.BasicStroke(2.0f));
   QListIterator<QRect> iter(*_vertexHandles);
//   if(_handleGroup != NULL)
//   {
    QList<QGraphicsItem*> itemList = _handleGroup->childItems();
    foreach(QGraphicsItem* it, itemList)
    {
     if(qgraphicsitem_cast<QGraphicsRectItem*>(it))
     {
      _handleGroup->removeFromGroup(it);
      delete it;
     }
    }
//   }
//   else
//    _handleGroup = new QGraphicsItemGroup();
   if(_handleGroup->scene() == NULL)
    g2d->addItem(_handleGroup);
   while (iter.hasNext())
   {
//                Rectangle rect = iter.next();
//                g2d.setColor(Color.BLUE);
//                g2d.fill(rect);
//                g2d.setColor(Editor::HIGHLIGHT_COLOR);
//                g2d.draw(rect);
    QGraphicsRectItem* item = new QGraphicsRectItem(iter.next());
    item->setPen(QPen(QColor(Qt::blue),2));
    item->setPos(getLocation());
    _handleGroup->addToGroup(item);
   }
   _handleGroup->setZValue(Editor::HANDLES);
   if (_hitIndex >= 0) {
//       Rectangle rect = _vertexHandles.get(_hitIndex);
//       g2d.setColor(Color.RED);
//       g2d.fill(rect);
//       g2d.draw(rect);
    QGraphicsRectItem* item = new QGraphicsRectItem(_vertexHandles->at(_hitIndex));
    item->setPen(QPen(QColor(Qt::red),2));
    item->setPos(getLocation());
    _handleGroup->addToGroup(item);
   }
  }
 }
 else
 {
  PositionableShape::paintHandles(g2d);
 }
}

// this method adds the object to the QGraphicsScene
/*public*/ bool PositionablePolygon::updateScene() // TODO: this function not in Java
{
 //QGraphicsPathItem* item = NULL;
// if(_itemGroup != NULL)
// {
  QList<QGraphicsItem*> itemList = _itemGroup->childItems();
  foreach(QGraphicsItem* it, itemList)
  {
   if(qgraphicsitem_cast<QGraphicsPathItem*>(it) != NULL)
   {
    //item = qgraphicsitem_cast<QGraphicsPathItem*>(it);
    _itemGroup->removeFromGroup(it);
    delete it;
   }
  }
// }
// else
//  _itemGroup = new QGraphicsItemGroup();

 //if(item == NULL)
 {
  QPainterPath* path = makePath(0, 0);
  this->item = new QGraphicsPathItem(*path);
  this->item->setBrush(QBrush(_fillColor));
  this->item->setPen(QPen(QBrush(_lineColor),_lineWidth, Qt::SolidLine,
                    Qt::FlatCap, Qt::MiterJoin));
  this->item->setPos(getX(), getY());
 }
 _itemGroup->addToGroup(item);
 if(_itemGroup->scene() == NULL)  // fix
  _editor->editScene->addItem(_itemGroup);
 QRectF bnd = item->boundingRect();
 _width = bnd.width();
 _height = bnd.height();
 paintHandles(_editor->editScene);

 //if(showTooltip()) _itemGroup->setToolTip(getTooltip());
 //int degrees = getDegrees() + getIcon()->getRotation();
 if((getDegrees()) != 0)
 {
  //l->item->rotate(l->getDegrees());
  QPointF center = bnd.center();
  _itemGroup->setTransformOriginPoint(center);
  //_itemGroup->setRotation(item->rotation());
 }
 bnd = _itemGroup->boundingRect();
 _itemGroup->setZValue(getDisplayLevel());
 _itemGroup->update();
 return true;
}


