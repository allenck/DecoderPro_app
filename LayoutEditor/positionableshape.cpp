#include "positionableshape.h"
#include <QMenu>
#include <QColor>
#include "editor.h"
#include "drawframe.h"
#include "flowlayout.h"
#include <QPushButton>
#include "coordinateedit.h"
#include "pathiterator.h"
#include "instancemanager.h"
#include "proxysensormanager.h"
#include <QMessageBox>
#include "shape.h"
#include "affinetransform.h"
#include "editor.h"
#include <QGraphicsItemGroup>
#include "generalpath.h"
//#include "optional.h"
#include "sensormanager.h"
#include "instancemanager.h"
#include "positionablepolygon.h"

PositionableShape::PositionableShape(QWidget *parent) :
    PositionableJComponent()
{
}
/**
 * PositionableShape is item drawn by ava.awt.Graphics2D.
 * <P>
 * @author Pete cresman Copyright (c) 2012
 * @version $Revision: 1 $
 */

///*public*/ class PositionableShape extends PositionableJComponent {


//    /*public*/ final static java.util.ResourceBundle rbcp = ControlPanelEditor.rbcp;

/*public*/ PositionableShape::PositionableShape(Editor* editor, QWidget *parent) : PositionableJComponent(editor, parent)
{
 //super(editor);
 init();
 setOpaque(false);
}

/*public*/ PositionableShape::PositionableShape(Editor* editor, JShape* shape, QWidget *parent) : PositionableJComponent(editor, parent)
{
 //this(editor);
 init();
 _shape = shape;
}

void PositionableShape::init()
{
 setObjectName("PositionableShape");
 _lineColor = QColor(Qt::black);
 _alpha = 255;
 _lineWidth = 1;
 _shape = NULL;
 _degrees = 0;
 ((Positionable*)this)->setVisible(true);
 _hitIndex = -1;	// dual use! also is index of polygon's vertices
 _controlSensor = NULL;
 _saveLevel = 5;			// default level set in popup
 _changeLevel = 5;
 _transform = NULL;
 _handles = NULL;
 _editFrame = NULL;
 _lastX = 0;
 _lastY = 0;
 _itemGroup = new MyGraphicsItemGroup();
}

/*public*/ PathIterator* PositionableShape::getPathIterator(AffineTransform* at)
{
 return _shape->getPathIterator(at);
}

/*protected*/ void PositionableShape::setShape(JShape* s) {
    _shape = s;
}

/*protected*/ JShape* PositionableShape::getShape()
{
    return _shape;
}

/*public*/ AffineTransform* PositionableShape::getTransform() {
    return _transform;
}

/*public*/ void PositionableShape::setWidth(int w) {
    if (w > SIZE) {
        _width = w;
    } else {
        _width = SIZE;
    }
    PositionableJComponent::setWidth(_width);
}

/*public*/ void PositionableShape::setHeight(int h) {
    if (h > SIZE) {
        _height = h;
    } else {
        _height = SIZE;
    }
    PositionableJComponent::setHeight(_height);

}

//@Override
/*public*/ int PositionableShape::getHeight() {
    return _height;
}

//@Override
/*public*/ int PositionableShape::getWidth() {
    return _width;
}

//@Override
/*public*/ void PositionableShape::rotate(int deg)
{
    _degrees = deg % 360;
    if (_degrees == 0) {
        _transform = NULL;
    } else {
        double rad = _degrees * 3.14159265359 / 180.0;
        _transform = new AffineTransform();
        // use bit shift to avoid FindBugs paranoia
        _transform->setToRotation(rad, (_width >> 1), (_height >> 1));
    }
    updateSize();
}

/**
 * this class must be overridden by its subclasses and executed
 *  only after its parameters have been set
 */
//@Override
/*public*/ void PositionableShape::makeShape() {}

/*public*/ void PositionableShape::setLineColor(QColor c) {
    if (!c.isValid()) {
        c = QColor(Qt::black);
    }
    _lineColor = c;
}
/*public*/QColor PositionableShape::getLineColor() {
    return _lineColor;
}

/*public*/ void PositionableShape::setFillColor(QColor c) {
    if(c.isValid())
     _fillColor = c;
}
/*public*/ QColor PositionableShape::getFillColor( ) {
    return _fillColor;
}

/*public*/ void PositionableShape::setAlpha(int a) {
    _alpha = a;
}
/*public*/ int PositionableShape::getAlpha() {
    return _alpha;
}

/*public*/ void PositionableShape::setLineWidth(int w) {
    _lineWidth = w;
}
/*public*/ int PositionableShape::getLineWidth() {
    return _lineWidth;
}

//@Override
/*public*/ void PositionableShape::paint(QGraphicsScene* g) {
    /*
    Graphics2D g2d = (Graphics2D)g;
    g2d.setRenderingHint(RenderingHints.KEY_RENDERING,
                         RenderingHints.VALUE_RENDER_QUALITY);
    g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                         RenderingHints.VALUE_ANTIALIAS_ON);
    g2d.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION,
                         RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY);
    g2d.setRenderingHint(RenderingHints.KEY_INTERPOLATION,
                         RenderingHints.VALUE_INTERPOLATION_BICUBIC);
    g2d.setClip(NULL);
    if (_transform!=NULL ) {
        g2d.transform(_transform);
    }
    if (_fillColor!=NULL) {
        g2d.setColor(_fillColor);
        g2d.fill(_shape);
    }
    g2d.setColor(_fillColor);
    BasicStroke stroke = new BasicStroke(_lineWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10f);
    g2d.setColor(_lineColor);
    g2d.setStroke(stroke);
    g2d.draw(_shape);
    */
 if (!getEditor()->isEditable() && !((Positionable*)this)->isVisible())
 {
  return;
 }
 if(_handleGroup != NULL)
 {
  QList<QGraphicsItem*> list = _handleGroup->childItems();
  foreach (QGraphicsItem* it, list)
  {
   _handleGroup->removeFromGroup(it);
   delete it;
  }
 }
 else
 {
  _handleGroup = new MyGraphicsItemGroup;
  _handleGroup->setName("PositionableShape");
  g->addItem(_handleGroup);
 }

// QPointF pt = getLocation();
// QPainterPath* path = makePath(pt.x(), pt.y());
// item = new QGraphicsPathItem(*path);
// item->setBrush(QBrush(/*_fillColor*/QColor(Qt::magenta)));
// item->setPen(QPen(QBrush(_lineColor),_lineWidth, Qt::SolidLine,
//                   Qt::FlatCap, Qt::MiterJoin));
// _itemGroup->addToGroup(item);
// QPointF _pos = getLocation();
// _itemGroup->setPos(_itemGroup->mapToScene(_pos));

 paintHandles(g);
 _handleGroup->update();
}

/*private*/ QPainterPath* PositionableShape::makePath(float x, float y)
{
 QPainterPath* path = new QPainterPath(QPoint(x,y));
 QList<QPoint>* _vertices = new QList<QPoint>();
 PathIterator* iter = getPathIterator(NULL);
 QVector<float>* coord = new QVector<float>(6);
 while (!iter->isDone()) {
     iter->currentSegment(coord);
     _vertices->append(QPoint(x + qRound(coord->at(0)), y + qRound(coord->at(1))));
     iter->next();
 }

 path->moveTo(_vertices->at(0).x() - x, _vertices->at(0).y() - y);
 for (int i = 1; i < _vertices->size(); i++)
 {
  path->lineTo(_vertices->at(i).x() - x, _vertices->at(i).y() - y);
 }
 return path;
}

/*protected*/ void PositionableShape::paintHandles(QGraphicsScene* g2d)
{
 if (_editor->isEditable() && _handles != NULL)
 {
  QList<QGraphicsItem*> list = _handleGroup->childItems();
  foreach(QGraphicsItem* it, list)
  {
   if(qgraphicsitem_cast<QGraphicsRectItem*>(it))
   {
     _handleGroup->removeFromGroup(it);
     delete it;
   }
  }

//            g2d.setColor(Editor.HIGHLIGHT_COLOR);
//            g2d.setStroke(new java.awt.BasicStroke(2.0f));
  QRectF r = _itemGroup->boundingRect();
  r.setX(r.x() -_lineWidth / 2);
  r.setY(r.y()  -_lineWidth / 2);
  r.setWidth(_width + _lineWidth);
  r.setHeight(_height + _lineWidth);
  //g2d.draw(r);
  QGraphicsRectItem* item = new QGraphicsRectItem(r);
  item->setPen(QPen(Editor::HIGHLIGHT_COLOR, 2));
  //item->setPos(getLocation());
  _handleGroup->addToGroup(item);
//       		g2d.fill(r);
  for (int i = 0; i < _handles->length(); i++)
  {
   if (_handles->at(i) != QRect())
   {
//                    g2d.setColor(Color.RED);
//                    g2d.fill(_handles[i]);
//                    g2d.setColor(Editor.HIGHLIGHT_COLOR);
//                    g2d.draw(_handles[i]);
      QGraphicsRectItem* h = new QGraphicsRectItem(_handles->at(i));
      h->setPen(QPen(QColor(Qt::red),2));
      h->setPos(getLocation());
      _handleGroup->addToGroup(h);
   }
  }
  _handleGroup->setZValue(Editor::HANDLES);
  if(_handleGroup->scene() == NULL)
   g2d->addItem(_handleGroup);
 }
}
/*public*/ Positionable* PositionableShape::deepClone() {
    PositionableShape* pos = new PositionableShape(_editor);
    return finishClone(pos);
}

/*public*/ Positionable* PositionableShape::finishClone(Positionable* p) {
    PositionableShape* pos = (PositionableShape*)p;
    pos->_alpha = _alpha;
    pos->_lineWidth = _lineWidth;
    pos->setFillColor(_fillColor);
    pos->_lineColor =  QColor(_lineColor.red(), _lineColor.green(), _lineColor.blue(), _lineColor.alpha());
    pos->_itemGroup = _itemGroup;
    pos->_height = _height;
    pos->_width = _width;


    pos->makeShape();
    pos->updateSize();
    return PositionableJComponent::finishClone(pos);
}

/*public*/ QSize PositionableShape::getSize(QSize /*rv*/) {
    return  QSize(maxWidth(), maxHeight());
}

/*public*/ void PositionableShape::updateSize() {
 QRectF r;
 if (_shape != NULL)
 {
  //if(qobject_cast<PositionablePolygon*>(_shape))
   r = getBounds();
//  else
//   r = _shape->getBounds();
 }
 else
 {
  r = PositionableJComponent:: getBounds();
 }
 setWidth(r.width());
 setHeight(r.height());
 setSize(r.width(), r.height());
}

//@Override
/*public*/ int PositionableShape::maxWidth() {
    return size().width();
}

//@Override
/*public*/ int PositionableShape::maxHeight() {
    return size().height();
}

/*public*/ bool PositionableShape::showPopUp(QMenu* /*popup*/) {
    return false;
}

/**
* Rotate degrees	!!!TODO
* return true if popup is set
*/
/*public*/ bool PositionableShape::setRotateMenu(QMenu* popup)
{
 if (getDisplayLevel() > Editor::BKG)
 {
  //CoordinateEdit* coordinateEdit = new CoordinateEdit();
  popup->addAction(CoordinateEdit::getRotateEditAction(this,this));
  return true;
 }
 return false;
}

/*public*/ bool PositionableShape::setScaleMenu(QMenu* /*popup*/)
{
 return false;
}

/*public*/ int PositionableShape::getDegrees() {
    return _degrees;
}

/*public*/ bool PositionableShape::setEditItemMenu(QMenu* /*popup*/) {
    return false;
}

/*protected*/ void PositionableShape::setEditFrame(DrawFrame* f)
{
    _editFrame = f;
}

/*protected*/ void PositionableShape::setEditParams()
{
 _editFrame->setDisplayParams(this);
 _editFrame->makeCopy(this);
 drawHandles();

}

/*protected*/ QWidget* PositionableShape::makeDoneButtonPanel() {
 QWidget* panel0 = new QWidget();
 panel0->setLayout(new FlowLayout());
 QPushButton* doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                editItem();
//            }
//    });
 connect(doneButton, SIGNAL(clicked()),this, SLOT(editItem()));
 panel0->layout()->addWidget(doneButton);

 QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                _editFrame.dispose();
//            }
//    });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(OnCancel_clicked()));
 panel0->layout()->addWidget(cancelButton);
 return panel0;
}
/*protected*/ void PositionableShape::editItem()
{
 _editFrame->updateFigure(this);
// if(_itemGroup != NULL && _itemGroup->scene() !=NULL)
// {
//  _editor->removeFromTarget(this);
//  //_itemGroup = new QGraphicsItemGroup;
// }
 if(_itemGroup)
 {
  QList<QGraphicsItem*> list = _itemGroup->childItems();
  foreach(QGraphicsItem* it, list)
  {
   _itemGroup->removeFromGroup(it);
   delete it;
  }
 }
 if(_handleGroup)
 {
  QList<QGraphicsItem*> list = _handleGroup->childItems();
  foreach(QGraphicsItem* it, list)
  {
   _handleGroup->removeFromGroup(it);
   delete it;
  }
 }

 makeShape();
 updateSize();
 _editFrame->dispose();
 repaint();
 _editor->addToTarget(this);
}
void PositionableShape::OnCancel_clicked()
{
 _editFrame->dispose();
}

/*public*/ void PositionableShape::propertyChange(PropertyChangeEvent* evt) {
    if (log->isDebugEnabled()) {
        log->debug("property change: " + getNameString() + " property " + evt->getPropertyName() + " is now "
                + evt->getNewValue().toString() + " from " + QString(evt->getSource()->metaObject()->className()));
    }

    if (!_editor->isEditable()) {
        if (evt->getPropertyName()==("KnownState")) {
            if (( evt->getNewValue()).toInt() == Sensor::ACTIVE) {
                if (_doHide) {
                    ((Positionable*)this)->setVisible(true);
                } else {
                    setDisplayLevel(_changeLevel);
                    ((Positionable*)this)->setVisible(true);
                }
            } else if ((evt->getNewValue()).toInt() == Sensor::INACTIVE) {
                if (_doHide) {
                    ((Positionable*)this)->setVisible(false);
                } else {
                    setDisplayLevel(_saveLevel);
                    ((Positionable*)this)->setVisible(true);
                }
            } else {
                setDisplayLevel(_saveLevel);
                ((Positionable*)this)->setVisible(true);
            }
        }
    } else {
        setDisplayLevel(_saveLevel);
        ((Positionable*)this)->setVisible(true);
    }
}

/**
 * Attach a named sensor to shape
 *
 * @param pName Used as a system/user name to lookup the sensor object
 */
/*public*/ QString PositionableShape::setControlSensor(QString pName, bool hide, int level)
{
 NamedBeanHandle<Sensor*>* senHandle = NULL;
 QString msg = "";
 if (pName == "" || pName.trimmed().isEmpty()) {
     setControlSensorHandle(NULL);
     return "";
 }
 _saveLevel = PositionableJComponent::getDisplayLevel();
 //Optional<SensorManager*>* sensorManager = InstanceManager::getOptionalDefault("SensorManager");
 SensorManager* sensorManager = (SensorManager*)InstanceManager::getDefault("SensorManager");
 //if (sensorManager.isPresent()) {
 if(sensorManager != NULL)
 {
     Sensor* sensor = ((ProxySensorManager*)sensorManager)->getSensor(pName);
     //Optional<NamedBeanHandleManager> nbhm = InstanceManager.getOptionalDefault(NamedBeanHandleManager.class);
     NamedBeanHandleManager* nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");
     if (sensor != NULL) {
         if (nbhm != NULL) {
             senHandle = nbhm->getNamedBeanHandle(pName, sensor);
         }
         _doHide = hide;
         _changeLevel = level;
         if (_changeLevel <= 0) {
             _changeLevel = PositionableJComponent::getDisplayLevel();
         }
     } else {
         msg = tr("\"%1\" is not a valid Sensor name.").arg(pName); // NOI18N
     }
 } else {
     msg = tr("No SensorManager for this protocol, shape cannot acquire a sensor."); // NOI18N
 }
 if (msg != "") {
     log->warn(tr("%1 for %2 sensor").arg(msg).arg(tr("VisibleSensor")));
 }
 setControlSensorHandle(senHandle);
 return msg;
}

/*public*/ void PositionableShape::setControlSensorHandle(NamedBeanHandle<Sensor*>* senHandle) {
    if (_controlSensor != NULL) {
     getControlSensor()->removePropertyChangeListener((PropertyChangeListener*)this);
     //disconnect(getControlSensor()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        setDisplayLevel(_saveLevel);
        ((Positionable*)this)->setVisible(true);
    }
    _controlSensor = senHandle;
    if (_controlSensor != NULL) {
     getControlSensor()->addPropertyChangeListener((PropertyChangeListener*)this, _controlSensor->getName(), "PositionalShape");
     //connect(getControlSensor()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
}

/*public*/ Sensor* PositionableShape::getControlSensor() {
    if (_controlSensor == NULL) {
        return NULL;
    }
    return _controlSensor->getBean();
}

/*protected*/ QString PositionableShape::getSensorName() {
        Sensor* s = getControlSensor();
        if (s != NULL) {
            return s->getDisplayName();
        }
        return "";
    }

/*public*/ NamedBeanHandle<Sensor*>* PositionableShape::getControlSensorHandle() {
    return _controlSensor;
}

/*public*/ bool PositionableShape::isHideOnSensor() {
    return _doHide;
}

/*public*/ int PositionableShape::getChangeLevel()
{
    return _changeLevel;
}

/*public*/ void PositionableShape::setChangeLevel(int l) // SLOT
{
 _changeLevel = l;
}

/*public*/ void PositionableShape::dispose()
{
 if (_controlSensor != NULL) {
  getControlSensor()->removePropertyChangeListener((PropertyChangeListener*)this);
  //disconnect(getControlSensor()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 _controlSensor = NULL;
}

/*protected*/ void PositionableShape::closeEditFrame()
{
 _editFrame = NULL;
 removeHandles();
}

/*public*/ void PositionableShape::removeHandles()
{
 _handles = NULL;
 if(_handleGroup != NULL)
 {
  QList<QGraphicsItem*> list = _handleGroup->childItems();
  foreach(QGraphicsItem* it, list)
  {
   _handleGroup->removeFromGroup(it);
   delete it;
  }
 }
//    	invalidate();
 repaint();
}

/*public*/ void PositionableShape::drawHandles()
{
 _handles = new QVector<QRect>(4);
 int rectSize = 2 * SIZE;
 if (_width < rectSize || _height < rectSize)
 {
  rectSize = qMin(_width, _height);
 }
 _handles->replace(RIGHT, QRect(_width - rectSize, _height / 2 - rectSize / 2, rectSize, rectSize));
 _handles->replace(LEFT, QRect(0, _height / 2 - rectSize / 2, rectSize, rectSize));
 _handles->replace(TOP, QRect(_width / 2 - rectSize / 2, 0, rectSize, rectSize));
 _handles->replace(BOTTOM, QRect(_width / 2 - rectSize / 2, _height - rectSize, rectSize, rectSize));
}

/*public*/ QPoint PositionableShape::getInversePoint(int x, int y) //throws java.awt.geom.NoninvertibleTransformException
{
 if (_transform != NULL)
 {
  AffineTransform* t = _transform->createInverse();
  QVector<float>* pt = new QVector<float>(2);
  pt->replace(0, x);
  pt->replace(1, y);
  t->transform(pt, 0, pt, 0, 1);
  return QPoint(qRound(pt->at(0)), qRound(pt->at(1)));
 }
 return QPoint(x, y);
}

/*public*/ float PositionableShape::getFloat(QDomElement element, QString name)
{
 bool bok;
 QString attr = element.attribute(name);
 if (attr != "") {
     float num = attr.toFloat(&bok);
     return num;
 }
 if(!bok)
 {
  log->error("failed to convert integer attribute for " + name + " - " /*+ e*/);
 }
 return 0;
}

/*public*/ void PositionableShape::doMousePressed(QGraphicsSceneMouseEvent* event)
{
 _hitIndex = -1;
 if (!_editor->isEditable())
 {
  return;
 }
 if (_handles != NULL)
 {
  _lastX = event->scenePos().x();
  _lastY = event->scenePos().y();
  int x = _lastX - getX();
  int y = _lastY - getY();
  QPoint pt;
  //try {
      pt = getInversePoint(x, y);
  if(pt == QPoint()) {
      log->error("Can't locate Hit Rectangles " /*+ nte.getMessage()*/);
      return;
  }
  for (int i = 0; i < _handles->length(); i++) {
      if (_handles->at(i) != QRect() && _handles->at(i).contains(pt.x(), pt.y())) {
          _hitIndex = i;
      }
  }
 }
 paint(_editor->editScene);  // Added ACK
}

/*protected*/ bool PositionableShape::doHandleMove(QGraphicsSceneMouseEvent* event)
{
 if (_hitIndex >= 0 && _editor->isEditable())
 {
  int deltaX = event->scenePos().x() - _lastX;
  int deltaY = event->scenePos().y() - _lastY;
  switch (_hitIndex)
  {
   case TOP:
       if (_height - deltaY > SIZE) {
           setHeight(_height - deltaY);
           _editor->moveItem(this, 0, deltaY);
       } else {
           setHeight(SIZE);
           _editor->moveItem(this, 0, _height - SIZE);
       }
       break;
   case RIGHT:
       setWidth(qMax((int)SIZE, _width + deltaX));
       break;
   case BOTTOM:
       setHeight(qMax((int)SIZE, _height + deltaY));
       break;
   case LEFT:
       if (_width - deltaX > SIZE) {
           setWidth(qMax((int)SIZE, _width - deltaX));
           _editor->moveItem(this, deltaX, 0);
       } else {
           setWidth(SIZE);
           _editor->moveItem(this, _width - SIZE, 0);
       }
       break;
  }
  QList<QGraphicsItem*> list = _itemGroup->childItems();
  foreach(QGraphicsItem* it, list)
  {
   _itemGroup->removeFromGroup(it);
   delete it;
  }
  list = _handleGroup->childItems();
  foreach(QGraphicsItem* it, list)
  {
   _handleGroup->removeFromGroup(it);
   delete it;
  }

  makeShape();
  updateSize();
  drawHandles();
  repaint();
  _lastX = event->scenePos().x();
  _lastY = event->scenePos().y();
  return true;
 }
 return false;
}

/*public*/ bool PositionableShape::updateScene() // TODO: this function not in Java
{
 QGraphicsEllipseItem* item = NULL;

 if(_itemGroup != NULL)
 {
  QList<QGraphicsItem*> itemList = _itemGroup->childItems();
  foreach(QGraphicsItem* it, itemList)
  {
   _itemGroup->removeFromGroup(it);
   delete it;
  }
 }
 else
  _itemGroup = new MyGraphicsItemGroup();
 _itemGroup->setName("PositionableShape");

 makeShape();
 //_itemGroup->setPos(getX(), getY());
 if(_handleGroup)
  _handleGroup->setPos(getX(), getY());

 //if(showTooltip()) _itemGroup->setToolTip(getTooltip());
 //int degrees = getDegrees() + getIcon()->getRotation();
 if((getDegrees()) != 0)
 {
  //l->item->rotate(l->getDegrees());
  QRectF bnd = _itemGroup->boundingRect();
  QPointF center = bnd.center();
  _itemGroup->setTransformOriginPoint(center);
  _itemGroup->setRotation(_shape->item->rotation());
 }
 _itemGroup->setZValue(getDisplayLevel());
 _itemGroup->update();
 return true;
}
