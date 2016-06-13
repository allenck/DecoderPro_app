#include "positionablerectangle.h"
#include <QGraphicsItem>
#include "drawrectangle.h"
#include <QPen>

//PositionableRectangle::PositionableRectangle(QObject *parent) :
//    PositionableShape(parent)
//{
//}
/**
 * PositionableRoundRect.
 * <P>
 * @author Pete cresman Copyright (c) 2012
 * @version $Revision: 1 $
 */

// /*public*/ class PositionableRectangle extends PositionableShape {


/*public*/ PositionableRectangle::PositionableRectangle(Editor* editor, QWidget* parent) : PositionableShape(editor, parent){
    //super(editor);
    _itemGroup = new QGraphicsItemGroup();
}

/*public*/ PositionableRectangle::PositionableRectangle(Editor* editor, QGraphicsItem* shape, QWidget* parent) : PositionableShape(editor, shape, parent)
{
    //super(editor, shape);
    _itemGroup = new QGraphicsItemGroup();
    _itemGroup->addToGroup(shape);
}

/*public*/ void PositionableRectangle::setWidth(int w) {
    _width = w;
}
/*public*/ void PositionableRectangle::setHeight(int h) {
    _height = h;
}
/**
 * Rotate shape
 */
/*public*/ void PositionableRectangle::rotate(int deg) {
    _degrees = deg;
#if 0
    if (_degrees==0) {
        _transform = null;
        makeShape();
    } else {
        _transform = AffineTransform.getTranslateInstance(_width/2, _height/2);
        _transform.rotate(deg*Math.PI/180);
        _transform.translate(-_width/2, -_height/2);
    }
#endif
    _itemGroup->setRotation(deg);
    updateSize();
}
/**
 * this class must be overridden by its subclasses and executed
 *  only after its parameters have been set
 */
/*public*/ void PositionableRectangle::makeShape() {
   // _shape = new Rectangle2D.Double(0, 0, _width, _height);

   _shape  = new QGraphicsRectItem( QRectF(0, 0, _width, _height));
   ((QGraphicsRectItem*)_shape)->setBrush(QBrush(_fillColor));
   ((QGraphicsRectItem*)_shape)->setPen(QPen(QBrush(_lineColor),_lineWidth));

   _itemGroup->addToGroup(_shape);
   _itemGroup->setPos(getX(), getY());
}

/*public*/ Positionable* PositionableRectangle::deepClone() {
    PositionableRectangle* pos = new PositionableRectangle(_editor);
    return finishClone(pos);
}
// Fix !!!TODO
/*public*/ Positionable* PositionableRectangle::finishClone(Positionable* p) {
    PositionableRectangle* pos = (PositionableRectangle*)p;
    pos->_width = _width;
    pos->_height = _height;
    return PositionableShape::finishClone(pos);
}

/*public*/ bool PositionableRectangle::setEditItemMenu(QMenu* popup) {
    QString txt = tr("Edit %1 Shape").arg(tr("Rectangle"));
//        popup.add(new javax.swing.AbstractAction(txt) {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                	_editFrame = new DrawRectangle("editShape", "rectangle", null);
//                	setEditParams();
//                }
//            });
  QAction* act = new QAction(txt,this);
  popup->addAction(act);
    connect(act,SIGNAL(triggered()), this, SLOT(editAction()));
    return true;
}
void PositionableRectangle::editAction()
{
 _editFrame = new DrawRectangle("Edit %1 Shape", "Rectangle", NULL);
  setEditParams();

}

/*public*/ bool PositionableRectangle::updateScene() // TODO: this function not in Java
{
 QGraphicsRectItem* item = NULL;

 if(_itemGroup != NULL)
 {
  QList<QGraphicsItem*> itemList = _itemGroup->childItems();
  foreach(QGraphicsItem* it, itemList)
  {
   if(qgraphicsitem_cast<QGraphicsRectItem*>(it) != NULL)
   {
    item = qgraphicsitem_cast<QGraphicsRectItem*>(it);
   }
  }
 }
 else
  _itemGroup = new QGraphicsItemGroup();

 if(item != NULL)
 {
  item->setRect(QRectF(0, 0, _width, _height));
 }
 else
  item = new QGraphicsRectItem(0, 0, _width, _height, _itemGroup);
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
