#ifndef LAYOUTSHAPE_H
#define LAYOUTSHAPE_H

#include <QObject>
#include <QColor>
#include <QPointF>
#include "hitpointtype.h"

class QGraphicsItemGroup;
class LayoutShapePointType;
class QGraphicsEllipseItem;
class EditScene;
class QGraphicsSceneMouseEvent;
class QMenu;
class LayoutShapePoint;
class LayoutShapeType;
class LayoutEditor;
class Logger;
/**
 * enum LayoutShapeType eOpen, eClosed, eFilled
 */
/*public*/ /*enum*/class LayoutShapeType
{


    /*private*/ /*final*/ /*transient*/ QString name;
public:
 enum TYPES
 {
  eOpen, //("Open"),
  eClosed, //("Closed"),
  eFilled, //("Filled");
 };
    LayoutShapeType(QString name);
    LayoutShapeType() {
     type = eOpen;
     this->name = "Open";
    }
    LayoutShapeType(TYPES t) {
     switch (t) {
     case eOpen:
     this->name = "Open";
      break;
     case eClosed:
     this->name = "Closed";
      break;
     case eFilled:
     this->name = "Filled";
      break;
     default:
      break;
     }
     type = t;
    }

    //Build an immutable map of String name to enum pairs.
//    static {
//        Map<String, LayoutShapeType> map = new ConcurrentHashMap<>();

//        for (LayoutShapeType instance : LayoutShapeType.values()) {
//            map.put(instance.getName(), instance);
//        }
//        ENUM_MAP = Collections.unmodifiableMap(map);
//    }

    /*public*/ static LayoutShapeType::TYPES getName(/*@CheckForNull*/ QString name);
    /*public*/ QString getName();
    /*public*/ LayoutShapeType::TYPES getType() {return type;}
    static QString getName(LayoutShapeType::TYPES t)
    {
     switch(t)
     {
     case eOpen:
      return "Open";
     case eClosed:
      return "Closed";
     case eFilled:
      return "Filled";
     default:
      return "?";
     }
    }

private:
    LayoutShapeType::TYPES type;
    /*private*/ /*transient*/ static /*final*/ QMap<QString, LayoutShapeType::TYPES> ENUM_MAP;

};

/**
 * enum LayoutShapePointType eStraight, eCurve
 */
/*public*/ /*enum*/ class LayoutShapePointType
{
 public:
 enum TYPES
 {
  eStraight, //("Straight"),
  eCurve     //("Curve");
 };
private:
    /*private*/ /*final*/ /*transient*/ QString name;
 LayoutShapePointType::TYPES type;
public:
    LayoutShapePointType(QString name);

    //Build an immutable map of String name to enum pairs.
//    static {
//        Map<String, LayoutShapePointType> map = new ConcurrentHashMap<>();
//        for (LayoutShapePointType instance : LayoutShapePointType.values()) {
//            map.put(instance.getName(), instance);
//        }
//        ENUM_MAP = Collections.unmodifiableMap(map);
//    }

    /*public*/ static TYPES getName(/*@CheckForNull*/ QString name);

    /*public*/ QString getName();

    /*public*/ LayoutShapePointType::TYPES getType() {return type;}
    /*public*/ LayoutShapePointType(LayoutShapePointType::TYPES t)
    {
     switch(t)
     {
      case eStraight:
      type = t;
      name = "Straight";
      break;
     case eCurve:
      type = t;
      name = "Curve";
      break;
     default:
      break;
     }
    }
    static QString typeName(LayoutShapePointType::TYPES t)
    {
     switch(t)
     {
     case eStraight:
      return "Straight";
     case eCurve:
      return "Curve";
     default:
      return "?";
     }
    }
private:
    /*private*/ static /*final*/ /*transient*/ QMap<QString, TYPES> ENUM_MAP;

}; // enum LayoutShapePointType

class LayoutShape : public QObject
{
 Q_OBJECT
public:
 /*public*/ LayoutShape(QString name, LayoutShapeType::TYPES t, LayoutEditor* layoutEditor, QObject *parent = nullptr);
 /*public*/ LayoutShape(QString name, LayoutEditor* layoutEditor, QObject* parent=nullptr);

 /*public*/ static /*final*/ int MAX_LINEWIDTH;// = 200;
 /*public*/ LayoutShape(QString name, QPointF c, LayoutEditor* layoutEditor, QObject *parent = nullptr);
 /*public*/ LayoutShape(LayoutShape* layoutShape, QObject *parent = nullptr);
 /*public*/ QString toString();
 /*public*/ QString getDisplayName();
 /*public*/ QString getName();
 /*public*/ void setName(QString n);
 /*public*/ LayoutShapeType::TYPES getType();
 /*public*/ void setType(LayoutShapeType::TYPES t);
 /*public*/ int getLineWidth();
 /*public*/ void setLineWidth(int w) ;
 /*public*/ QColor getLineColor();
 /*public*/ void setLineColor(QColor color);
 /*public*/ QColor getFillColor();
 /*public*/ void setFillColor(QColor color);
 /*public*/ int getLevel();
 /*public*/ void setLevel(int l);
 /*public*/ LayoutEditor* getLayoutEditor();
 /*public*/ void addPoint(QPointF p);
 /*public*/ void addPoint(QPointF p, int nearIndex);
 /*public*/ void addPoint(LayoutShapePointType::TYPES t, QPointF p);
 /*public*/ void setPoint(int idx, QPointF p);
 /*public*/ QPointF getPoint(int idx);
 /*public*/ QList<LayoutShapePoint *> getPoints();
 /*public*/ int getNumberPoints();
 /*public*/ int getMaxNumberPoints();
 /*public*/ QRectF getBounds();
 /*public*/ static bool isShapeHitPointType(HitPointType::TYPES t);
 ///*public*/ static bool isShapePointOffsetHitPointType(int t);
 /*public*/ QPointF getCoordsCenter();
 /*public*/ void setCoordsCenter(/*@Nonnull*/ QPointF p);
 /*public*/ void scaleCoords(double xFactor, double yFactor);
 /*public*/ void translateCoords(double xFactor, double yFactor);
 /*public*/ void rotateCoords(double angleDEG);
 void dispose();
 void remove();
 /*public*/ QGraphicsEllipseItem* trackEditControlCircleAt(/*@Nonnull*/ QPointF inPoint);
 /*public*/ QGraphicsEllipseItem* trackControlCircleAt(/*@Nonnull*/ QPointF inPoint);
 /*public*/ QGraphicsItemGroup* invalidateItem(EditScene* g2, QGraphicsItemGroup* item);

signals:

public slots:
 void on_changeName();
 void on_setOpen();
 void on_setClosed();
 void on_setFilled();
 void on_setStraight();
 void on_setCurve();
 void on_lineColor();
 void on_setFillColor();
 void on_lineWidth();
 void on_setLevel();
 void on_duplicateShape();
 void on_deleteShape();
 void on_deletePoint();
 void on_changeShapePointType();

private:
 static Logger* log;
 // operational instance variables (not saved between sessions)
 /*private*/ LayoutEditor* layoutEditor = nullptr;
 /*private*/ QString name;
 /*private*/ LayoutShapeType::TYPES layoutShapeType;
 /*private*/ int level = 3;
 /*private*/ int lineWidth = 3;
 /*private*/ QColor lineColor;// = Color.BLACK;
 /*private*/ QColor fillColor;// = Color.DARK_GRAY;

 // these are saved
 // list of LayoutShapePoints
 /*private*/ /*final*/ QList<LayoutShapePoint*> shapePoints;
 /*private*/ QMenu* popup = nullptr;
 QGraphicsItemGroup* rects= nullptr;
 QGraphicsItemGroup* paths = nullptr;
 int pointIndex;
 QString otherPointTypeName;

protected:
 /*protected*/ HitPointType::TYPES findHitPointType(/*@Nonnull*/ QPointF hitPoint, bool useRectangles);
 /*protected*/ QMenu* showShapePopUp(/*@CheckForNull*/ QGraphicsSceneMouseEvent* mouseEvent, HitPointType::TYPES hitPointType);
 /*protected*/ void draw(EditScene* g2);
 /*protected*/ void drawEditControls(EditScene* g2);

 friend class LayoutEditor;
 friend class LayoutShapeTest;
 friend class LayoutEditorComponent;
};

/**
 * These are the points that make up the outline of the shape. Each point
 * can be ether a straight or a control point for a curve
 */
/*public*/ /*static*/ class LayoutShapePoint //: public QObject
{
 //Q_OBJECT
    /*private*/ /*transient*/ LayoutShapePointType::TYPES type;
    /*private*/ /*transient*/ QPointF point;
 QString name;
public:
    /**
     * constructor method
     *
     * @param c QPointF for initial point
     */
    /*public*/ LayoutShapePoint(QPointF c);
    /*public*/ LayoutShapePoint(LayoutShapePointType::TYPES t, QPointF c);
 enum PTYPES
 {
  eStright, //("Straight"),
  eCurved, //("Curved"),
 };

 /*public*/ LayoutShapePoint(QString name)
{
 if(name == "Straight")
 {
  this->name = name;
  t = eStright;
 }
 if(name == "Curved")
 {
  this->name = name;
  t = eCurved;
 }
}

 LayoutShapePoint(PTYPES t) {
  switch (t) {
  case eStright:
  this->name = "Straight";
   break;
  case eCurved:
  this->name = "Curved";
   break;
  default:
   break;
  }
 }
    /*public*/ LayoutShapePointType::TYPES getType();
    /*public*/ void setType(LayoutShapePointType::TYPES type);
    /*public*/ QPointF getPoint();
    /*public*/ void setPoint(QPointF point);
private:
 PTYPES t;
};   // class LayoutShapePoint




#endif // LAYOUTSHAPE_H
