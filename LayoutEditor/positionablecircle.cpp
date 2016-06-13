#include "positionablecircle.h"
#include "editscene.h"
#include "drawcircle.h"

//PositionableCircle::PositionableCircle(QWidget *parent) :
//    PositionableShape(parent)
//{
//}
/**
 * PositionableCircle  PositionableShapes.
 * <P>
 * @author Pete cresman Copyright (c) 2012
 * @version $Revision: 1 $
 */

// /*public*/ class PositionableCircle extends PositionableShape {


/*public*/ PositionableCircle::PositionableCircle(Editor* editor, QWidget* parent) : PositionableShape(editor, parent) {
 //super(editor);
 _radius = 100;
 _itemGroup = new QGraphicsItemGroup();
}

/*public*/ PositionableCircle::PositionableCircle(Editor* editor, QGraphicsItem* shape, QWidget* parent) : PositionableShape(editor, shape, parent) {
        //super(editor, shape);
     _radius = 100;
    }

/*public*/ void PositionableCircle::setRadius(int r) {
    _radius = r;
}
/*public*/ int PositionableCircle::getRadius() {
    return _radius;
}
/**
 * this class must be overridden by its subclasses and executed
 *  only after its parameters have been set
 */
/*public*/ void PositionableCircle::makeShape() {
   // _shape = new Ellipse2D.Double(0, 0, _radius, _radius);
 _shape = new QGraphicsEllipseItem(0, 0, _radius, _radius);
 ((QGraphicsEllipseItem*)_shape)->setBrush(QBrush(_fillColor));
 ((QGraphicsEllipseItem*)_shape)->setPen(QPen(QBrush(_lineColor),_lineWidth));

 _itemGroup->addToGroup(_shape);
 _itemGroup->setPos(getX(), getY());
}

/*public*/ Positionable* PositionableCircle::deepClone() {
    PositionableCircle* pos = new PositionableCircle(_editor);
    return finishClone(pos);
}

/*public*/ Positionable* PositionableCircle::finishClone(Positionable* p) {
    PositionableCircle* pos = (PositionableCircle*)p;
    pos->_radius = _radius;
    return PositionableShape::finishClone(pos);
}

/*public*/ bool PositionableCircle::setEditItemMenu(QMenu* popup) {
    QString txt = tr("Edit %1 Shape").arg(tr("Circle"));
//    popup.add(new javax.swing.AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                _editFrame = new DrawCircle("editShape", "circle", null);
//                setEditParams();
//            }
//        });
    QAction* act = new QAction(txt, this);
    popup->addAction(act);
    connect(act, SIGNAL(triggered()), this, SLOT(onEditAct()));
    return true;
}
/*
protected void editItem() {
    _editFrame.updateFigure(this);
    updateSize();
    _editFrame.dispose();
    repaint();
}*/
void PositionableCircle::onEditAct()
{
 _editFrame = new DrawCircle("Edit %1 Shape", "circle", NULL);
 setEditParams();

}

/*public*/ bool PositionableCircle::updateScene() // TODO: this function not in Java
{
 QGraphicsEllipseItem* item = NULL;

 if(_itemGroup != NULL)
 {
  QList<QGraphicsItem*> itemList = _itemGroup->childItems();
  foreach(QGraphicsItem* it, itemList)
  {
   if(qgraphicsitem_cast<QGraphicsEllipseItem*>(it) != NULL)
   {
    item = qgraphicsitem_cast<QGraphicsEllipseItem*>(it);
   }
  }
 }
 else
  _itemGroup = new QGraphicsItemGroup();

 if(item != NULL)
 {
  item->setRect(QRectF(0, 0, _radius, _radius));
 }
 else
  item = new QGraphicsEllipseItem(QRectF(0, 0, _radius, _radius),_itemGroup);
 //item->setPos(getX(), getY());
 if(showTooltip()) item->setToolTip(getTooltip());
 //_itemGroup->addToGroup(item);
 item->setPos(getX(), getY());
 item->setBrush(QBrush(_fillColor));
 item->setPen(QPen(QBrush(_lineColor),_lineWidth));

 //if(showTooltip()) _itemGroup->setToolTip(getTooltip());
 //int degrees = getDegrees() + getIcon()->getRotation();
 if((getDegrees()) != 0)
 {
  //l->item->rotate(l->getDegrees());
  QRectF bnd = _itemGroup->boundingRect();
  QPointF center = bnd.center();
  _itemGroup->setTransformOriginPoint(center);
  _itemGroup->setRotation(item->rotation());
 }
 _itemGroup->setZValue(getDisplayLevel());
 _itemGroup->update();
 return true;
}
