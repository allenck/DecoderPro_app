#include "positionableellipse.h"
#include "QGraphicsEllipseItem"
#include "drawellipse.h"
#include <QPen>

//PositionableEllipse::PositionableEllipse(QWidget *parent) :
//    PositionableShape(parent)
//{
//}
/**
 * PositionableRoundRect.
 * <P>
 * @author Pete cresman Copyright (c) 2012
 * @version $Revision: 1 $
 */

///*public*/ class PositionableEllipse extends PositionableShape {


/*public*/ PositionableEllipse::PositionableEllipse(Editor* editor,QWidget *parent) : PositionableShape(editor, parent) {
 //super(editor);
 _itemGroup = new QGraphicsItemGroup();
}

/*public*/ PositionableEllipse::PositionableEllipse(Editor* editor, QGraphicsItem* shape,QWidget *parent) : PositionableShape(editor, shape,parent)
{
        //super(editor, shape);
    }

    /*public*/ void PositionableEllipse::setWidth(int w) {
        _width = w;
    }
    /*public*/ void PositionableEllipse::setHeight(int h) {
        _height = h;
    }
    /**
     * Rotate shape
     */
    /*public*/ void PositionableEllipse::rotate(int deg) {
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
        _shape->setRotation(deg);
        updateSize();
    }

/**
 * this class must be overridden by its subclasses and executed
 *  only after its parameters have been set
 */
/*public*/ void PositionableEllipse::makeShape()
{
 //_shape = new Ellipse2D.Double(0, 0, _width, _height);
 _shape = new QGraphicsEllipseItem(0, 0, _width, _height);
 ((QGraphicsEllipseItem*)_shape)->setBrush(QBrush(_fillColor));
 ((QGraphicsEllipseItem*)_shape)->setPen(QPen(QBrush(_lineColor),_lineWidth));

 _itemGroup->addToGroup(_shape);
 _itemGroup->setPos(getX(), getY());
}

    /*public*/ Positionable* PositionableEllipse::deepClone() {
        PositionableEllipse* pos = new PositionableEllipse(_editor);
        return finishClone(pos);
    }

    /*public*/ Positionable* PositionableEllipse::finishClone(Positionable* p) {
        PositionableEllipse* pos = (PositionableEllipse*)p;
        pos->_width = _width;
        pos->_height = _height;
        return PositionableShape::finishClone(pos);
    }

    /*public*/ bool PositionableEllipse::setEditItemMenu(QMenu*  popup)
{
 QString txt = tr("Edit %1 Shape").arg(tr("Ellipse"));
//        popup.add(new javax.swing.AbstractAction(txt) {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                	_editFrame = new DrawEllipse("editShape", "ellipse", null);
//                	setEditParams();
//                }
//            });
 QAction* act = new QAction(txt, this);
 popup->addAction(act);
 connect(act, SIGNAL(triggered()), this, SLOT(onEditAct()));
 return true;
}

void PositionableEllipse::onEditAct()
{
 _editFrame = new DrawEllipse("Edit %1 Shape", "Ellipse", NULL);
 setEditParams();
}

/*public*/ bool PositionableEllipse::updateScene() // TODO: this function not in Java
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
  item->setRect(QRectF(0, 0, _width, _height));
 }
 else
  item = new QGraphicsEllipseItem(QRectF(0, 0, _width, _height),_itemGroup);
 if(showTooltip()) item->setToolTip(getTooltip());
 item->setPos(getX(), getY());
 item->setBrush(QBrush(_fillColor));
 item->setPen(QPen(QBrush(_lineColor),_lineWidth));

 //if((getDegrees()) != 0)
 {
  QRectF bnd = item->boundingRect();
  QPointF center = bnd.center();
  item->setTransformOriginPoint(center);
  item->setRotation(/*item->rotation() + */(qreal) getDegrees());
 }
 _itemGroup->setZValue(getDisplayLevel());
 _itemGroup->update();
 return true;
}
