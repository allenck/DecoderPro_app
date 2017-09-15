#ifndef POSITIONABLEJCOMPONENT_H
#define POSITIONABLEJCOMPONENT_H

//#include <QObject>
#include "logger.h"
#include "positionable.h"
#include <QFont>

class MyGraphicsProxyWidget;
class Editor;
class Positionable;
class PositionableJComponent : public Positionable
{
    Q_OBJECT
public:
    explicit PositionableJComponent(QWidget *parent = 0);
    /*public*/ PositionableJComponent(Editor* editor,QObject *parent = 0);
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(Positionable* pos);
    /*public*/ QObject* getTextComponent();
    /*public*/ void setPositionable(bool enabled);
    /*public*/ bool isPositionable();
    /*public*/ void setEditable(bool enabled);
    /*public*/ bool isEditable();
    /*public*/ void setViewCoordinates(bool enabled);
    /*public*/ bool getViewCoordinates();
    /*public*/ void setControlling(bool enabled);
    /*public*/ bool isControlling() ;
    /*public*/ void setHidden(bool hide);
    /*public*/ bool isHidden();
    /*public*/ void showHidden();
    /*public*/ void setLevel(int l);
    /*public*/ void setDisplayLevel(int l);
    /*public*/ int getDisplayLevel() ;
    /*public*/ void setShowTooltip(bool set);
    /*public*/ bool showTooltip() ;
    /*public*/ void setTooltip(QString tip) ;
    /*public*/ QString getTooltip();
    /*public*/ void setScale(double s);
    /*public*/ double getScale();
    // no subclasses support rotations (yet)
    /*public*/ void rotate(int deg) ;
    /*public*/ int getDegrees();
    /*public*/ bool getSaveOpaque() ;
    /*public*/ QString getNameString();
    /*public*/ Editor* getEditor();
    /*public*/ void setEditor(Editor* ed);
    // overide where used - e.g. momentary
    /*public*/ void doMousePressed(QGraphicsSceneMouseEvent* event);
    /*public*/ void doMouseReleased(QGraphicsSceneMouseEvent*  event);
    /*public*/ void doMouseClicked(QGraphicsSceneMouseEvent*  event);
    /*public*/ void doMouseDragged(QGraphicsSceneMouseEvent*  event);
    /*public*/ void doMouseMoved(QGraphicsSceneMouseEvent*  event);
    /*public*/ void doMouseEntered(QGraphicsSceneMouseEvent*  event);
    /*public*/ void doMouseExited(QGraphicsSceneMouseEvent*  event);
    /*public*/ bool storeItem();
    /*public*/ bool doViemMenu();
    /*public*/ bool setRotateOrthogonalMenu(QMenu* popup);
    /*public*/ virtual bool setRotateMenu(QMenu* popup);
    /*public*/ virtual bool setScaleMenu(QMenu* popup);
    /*public*/ bool setDisableControlMenu(QMenu* popup);
    /*public*/ bool setTextEditMenu(QMenu* popup) ;
    /*public*/ virtual bool setEditItemMenu(QMenu* popup);
    /*public*/ bool showPopUp(QMenu* popup) ;
    /*public*/ bool setEditIconMenu(QMenu* popup) ;
    /*public*/ PositionablePopupUtil* getPopupUtility() ;
    /*public*/ void setPopupUtility(PositionablePopupUtil* tu);
    /*public*/ void updateSize();
    /*public*/ int maxWidth();
    /*public*/ int maxHeight();
    /*public*/ void remove();
    void cleanup();
    /*public*/ bool isActive();
    /*public*/ NamedBean* getNamedBean();

    // JComponent stuff
    ///*public*/ QRect getBounds();
    QRectF getBounds(QRectF r = QRectF());
    bool contains(int x, int y);
    int getX();
    int getY();
    void setLocation(int x, int y);
    void setLocation(QPointF p);
    QPointF getLocation();
    void setSize(int width, int height);
    QSize getSize();
//    void setVisible(bool b);
//    bool isVisible();
    void setWidth(int width);
    void setHeight(int height);
    int getWidth();
    int getHeight();
    void setOpaque(bool isOpaque);
    bool isOpaque() ;
    void setBackground(QColor bg);
    QColor getBackground();
    void setForeground(QColor bg);
    QColor getForeground();
    QFont getFont();
    void invalidate();
    void repaint();
    bool requestFocusInWindow();

signals:

public slots:
private:
  Logger* log;
  /*protected*/ Editor* _editor;// = null;
  /*protected*/ bool debug;// = false;

  /*private*/ QString _tooltip;
  /*private*/ bool _showTooltip;// =true;
  /*private*/ bool _editable;// = true;
  /*private*/ bool _positionable;// = true;
  /*private*/ bool _viewCoordinates;// = false;
  /*private*/ bool _controlling;// = true;
  /*private*/ bool _hidden;// = false;
  /*private*/ int _displayLevel;
  /*private*/ double _scale;         // user's scaling factor

//  JMenuItem lock = null;
//  JCheckBoxMenuItem showTooltipItem = null;
  bool active;// = true;

  double _x, _y;
  QPointF _loc;
  QSize _size;
  int _width, _height;
//  bool _bVisible;
  bool _bOpaque;
  QColor _background, _foreground;
  QFont _font;
  friend class AnalogClock2Display;
  friend class PositionableShape;
  friend class PositionableRectangle;
  friend class PositionableCircle;
  friend class PositionableEllipse;
  friend class PositionableRoundRect;
  friend class Editor;
  friend class PositionablePolygon;
  friend class DrawPolygon;
};
#endif // POSITIONABLEJCOMPONENT_H
