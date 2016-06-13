#include "positionableroundrect.h"
#include "drawroundrect.h"
#include "editscene.h"

//PositionableRoundRect::PositionableRoundRect(QWidget *parent) :
//    PositionableRectangle(parent)
//{
//}
/**
 * PositionableRoundRect adds corner radii to PositionableShapes.
 * <P>
 * @author Pete cresman Copyright (c) 2012
 * @version $Revision: 1 $
 */

// /*public*/ class PositionableRoundRect extends PositionableRectangle {


/*public*/ PositionableRoundRect::PositionableRoundRect(Editor* editor, QWidget *parent) : PositionableRectangle(editor, parent)
{
    //super(editor);
    _radius = 10;
}

/*public*/ PositionableRoundRect::PositionableRoundRect(Editor* editor, QGraphicsItem* shape, QWidget *parent) : PositionableRectangle(editor, shape, parent)
{
 //super(editor, shape);
 _radius = 10;
 _itemGroup = new QGraphicsItemGroup();
}

/*public*/ void PositionableRoundRect::setCornerRadius(int r) {
    _radius = r;
}
/*public*/ int PositionableRoundRect::getCornerRadius() {
    return _radius;
}
/**
 * this class must be overridden by its subclasses and executed
 *  only after its parameters have been set
 */
/*public*/ void PositionableRoundRect::makeShape() {
   //_shape = new RoundRectangle2D.Double(0, 0, _width, _height, _radius, _radius);
 _shape = new QGraphicsRoundRectItem(0, 0, _width, _height, _radius, _radius);
 ((QGraphicsRoundRectItem*)_shape)->setBrush(QBrush(_fillColor));
 ((QGraphicsRoundRectItem*)_shape)->setPen(QPen(QBrush(_lineColor),_lineWidth));

 _itemGroup->addToGroup(_shape);
 _itemGroup->setPos(getX(), getY());
}

/*public*/ Positionable* PositionableRoundRect::deepClone()
{
    PositionableRoundRect* pos = new PositionableRoundRect(_editor);
    return finishClone(pos);
}

/*public*/ Positionable* PositionableRoundRect::finishClone(Positionable* p) {
    PositionableRoundRect* pos = (PositionableRoundRect*)p;
    pos->_radius = _radius;
    return PositionableRectangle::finishClone(pos);
}

/*public*/ bool PositionableRoundRect::setEditItemMenu(QMenu* popup) {
    QString txt = tr("Edit %1 Shape").arg(tr("Round Rectangle"));
//        popup.add(new javax.swing.AbstractAction(txt) {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                	_editFrame = new DrawRoundRect("editShape", "rectangle", null);
//                	setEditParams();
//                }
//            });
 QAction* editAct = new QAction(txt, this);
 popup->addAction(editAct);
 connect(editAct, SIGNAL(triggered()),this, SLOT(onEditAct()));
 return true;
}
void PositionableRoundRect::onEditAct()
{
 _editFrame = new DrawRoundRect(tr("Edit %1 Shape"), tr("Round Rectangle"), NULL);
 setEditParams();
}

/*public*/ bool PositionableRoundRect::updateScene() // TODO: this function not in Java
{
 QGraphicsRoundRectItem* item = NULL;

 if(_itemGroup != NULL)
 {
  QList<QGraphicsItem*> itemList = _itemGroup->childItems();
  foreach(QGraphicsItem* it, itemList)
  {
   if(qgraphicsitem_cast<QGraphicsRoundRectItem*>(it) != NULL)
   {
    item = qgraphicsitem_cast<QGraphicsRoundRectItem*>(it);
   }
  }
 }
 else
  _itemGroup = new QGraphicsItemGroup();

 if(item != NULL)
 {
  item->setRect(0, 0, _width, _height,_radius, _radius);
 }
 else
  item = new QGraphicsRoundRectItem(0, 0, _width, _height, _radius, _radius,_itemGroup);
 if(showTooltip()) item->setToolTip(getTooltip());
 item->setPos(getX(), getY());
 item->setBrush(QBrush(_fillColor));
 item->setPen(QPen(QBrush(_lineColor),_lineWidth));

 if((getDegrees()) != 0)
 {
  QRectF bnd = item->boundingRect();
  QPointF center = bnd.center();
  item->setTransformOriginPoint(center);
  item->setRotation(item->rotation()+ (qreal) getDegrees());
 }
 _itemGroup->setZValue(getDisplayLevel());
 _itemGroup->update();
 return true;
}
