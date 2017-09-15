#ifndef POSITIONABLESHAPE_H
#define POSITIONABLESHAPE_H
#include "positionablejcomponent.h"
#include "liblayouteditor_global.h"
#include "namedbeanhandle.h"
#include "shape.h"

class QDomElement;
class PropertyChangeEvent;
class Sensor;
class PathIterator;
class AffineTransform;
class EditScene;
class DrawFrame;
class LIBLAYOUTEDITORSHARED_EXPORT PositionableShape : public PositionableJComponent
{
    Q_OBJECT
 public:
  enum VALUES
  {
   TOP = 0,
   RIGHT = 1,
   BOTTOM = 2,
   LEFT = 3,
   SIZE = 4
  };
  explicit PositionableShape(QWidget *parent = 0);
  /*public*/ PositionableShape(Editor* editor, QWidget *parent = 0);
  /*public*/ PositionableShape(Editor* editor, JShape* shape, QWidget *parent = 0);
  /*public*/ PathIterator* getPathIterator(AffineTransform* at);
  /*public*/ virtual void makeShape();
  /*public*/ void setLineColor(QColor c);
  /*public*/ QColor getLineColor();
  /*public*/ void setFillColor(QColor c);
  /*public*/ QColor getFillColor();
  /*public*/ void setAlpha(int a);
  /*public*/ int getAlpha() ;
  /*public*/ void setLineWidth(int w);
  /*public*/ int getLineWidth();
  /*public*/ void paint(QGraphicsScene* g) ;
  /*public*/ Positionable* deepClone();
  /*public*/ Positionable* finishClone(Positionable* p);
  /*public*/ QSize getSize(QSize rv);
  /*public*/ void updateSize();
  /*public*/ int maxWidth() ;
  /*public*/ int maxHeight();
  /*public*/ bool showPopUp(QMenu* popup);
  /*public*/ bool setRotateMenu(QMenu* popup);
  /*public*/ bool setScaleMenu(QMenu* popup);
  /*public*/ int getDegrees();
  /*public*/ virtual bool setEditItemMenu(QMenu* popup);
  /*public*/ void dispose();
  /*public*/ virtual void removeHandles();
  /*public*/ virtual void drawHandles();
  /*public*/ QString setControlSensor(QString pName, bool hide, int level);
  /*public*/ void setControlSensorHandle(NamedBeanHandle<Sensor*>* senHandle);
  /*public*/ Sensor* getControlSensor();
  /*public*/ NamedBeanHandle<Sensor*>* getControlSensorHandle();
  /*public*/ bool isHideOnSensor();
  /*public*/ int getChangeLevel();
  /*public*/ float getFloat(QDomElement element, QString name);
  /*public*/ QPoint getInversePoint(int x, int y); //throws java.awt.geom.NoninvertibleTransformException
  /*public*/ AffineTransform* getTransform();
  /*public*/ void setWidth(int w);
  /*public*/ virtual void setHeight(int h);
  /*public*/ int getHeight();
  /*public*/ int getWidth();
  /*public*/ void doMousePressed(QGraphicsSceneMouseEvent* event);
  /*public*/ void rotate(int deg);
  /*public*/ bool updateScene();// // TODO: this function not in Java

signals:

public slots:
    void OnCancel_clicked();
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
    /*public*/ void setChangeLevel(int l);

private:
    void init();
    DrawFrame* _editFrame;
    /*private*/ NamedBeanHandle<Sensor*>* _controlSensor;// = null;
    /*private*/ int _saveLevel;// = 5;			// default level set in popup
    /*private*/ int _changeLevel;// = 5;
    /*private*/ bool _doHide;
    /*private*/ QVector<QRect>* _handles;
    /*private*/ QPainterPath* makePath(float x, float y);
    QPointF strt;

protected:
    /*protected*/ JShape*	_shape;
    /*protected*/ QColor	_lineColor;// = Color.black;
    /*protected*/ QColor	_fillColor;
    /*protected*/ int	_alpha;// = 255;
    /*protected*/ int	_lineWidth;// = 1;
    /*protected*/ int		_degrees;
    /*protected*/ AffineTransform* _transform;
    /*protected*/ void setEditParams();
    /*protected*/ QWidget* makeDoneButtonPanel() ;
    /*protected*/ void setShape(JShape* s);
    /*protected*/ JShape* getShape();
    /*protected*/ int _hitIndex;// = -1;	// dual use! also is index of polygon's vertices
    /*protected*/ int _lastX;
    /*protected*/ int _lastY;
    /*protected*/ int _width;
    /*protected*/ int _height;
    /*protected*/ virtual bool doHandleMove(QGraphicsSceneMouseEvent* event);
    /*protected*/ virtual void paintHandles(QGraphicsScene* g2d);
    QGraphicsPathItem* item;
    /*protected*/ QString getSensorName();
    /*protected*/ void closeEditFrame();
    /*protected*/ void setEditFrame(DrawFrame* f);


protected slots:
    /*protected*/ void editItem() ;
friend class PositionableRectangle;
friend class PositionableCircle;
friend class PositionableEllipse;
friend class PositionableRoundRect;
friend class Editor;
friend class PositionablePolygon;
friend class PolygonAction;
friend class ShapeDrawer;
friend class DrawPolygon;
friend class DrawFrame;
};

#endif // POSITIONABLESHAPE_H
