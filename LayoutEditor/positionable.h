#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include <QObject>
//#include "mylayouteditor.h"
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QFont>
#include <QMenu>
//#include "editor.h"
#include <QLabel>
#include <QGraphicsItemGroup>
#include "exceptions.h"
#include "jcomponent.h"
#include "editscene.h"

class Border;
class MyGraphicsItemGroup : public QGraphicsItemGroup
{
 QString _name;
public:
 enum { Type = 65536 + 1 };
 int type() const
 {
  // Enable the use of qgraphicsitem_cast with this item.
  return Type;
 }
 void setName(QString name) { this->_name = name;}
 QString name() { return _name;}
};

class QGraphicsScene;
class QGraphicsTextItem;
class QGraphicsItem;
class QGraphicsItemGroup;
class Editor;
class PositionablePopupUtil;
class NamedBean;
class Positionable //: public QLabel
{
 public:
    /**
     * Defines display objects.
     * <P>
     * These are capable of:
     * <UL>
     * <LI>Being positioned by being dragged around on the screen.
     * (See {@link #setPositionable})
     * <LI>Being hidden. (See {@link #setHidden})
     * <LI>Controlling the layout. (See {@link #setControlling})
     * </OL>
     * These are manipulated externally, for example by a
     * subclass of {@link Editor}.
     * They are generally not stored
     * directly as part of the state of the object, though they
     * could be, but as part of the state of the external control.
     *<p>
     * Instead of the usual MouseEvent handling methods, e.g mouseClicked(...),
     * Positionables have similar methods called doMouseClicked
     * invoked by the {@link Editor} subclass that contains
     * them, so the Editor can handle e.g. box selection, etc.
     *
     * @see PositionableJComponent
     * @see PositionableLabel
     * @author Bob Jacobsen Copyright (c) 2002
     * @author Pete Cressman Copyright (c) 2010
     * @version $Revision: 21256 $
     */
//    /*public*/ interface Positionable extends Cloneable  {
     /*public*/ virtual void setPositionable(bool /*enabled*/) =0;
     /*public*/ virtual bool isPositionable() =0;

     /*public*/ virtual void setEditable(bool /*enabled*/) =0;
     /*public*/ virtual bool isEditable()  =0;

     /*public*/ virtual void setShowToolTip(bool /*set*/) =0;
     /*public*/ virtual bool showToolTip() =0;
//        /*public*/ virtual void setTooltip(ToolTip tip);
     /*public*/ virtual void setToolTip(QString tip);

     /*public*/ virtual QString getToolTip();

     /*public*/ virtual void setViewCoordinates(bool /*enabled*/) {}
     /*public*/ virtual bool getViewCoordinates() {return false;}
     /*public*/ virtual void setControlling(bool /*enabled*/) =0;
     /*public*/virtual  bool isControlling() =0;

     /*public*/ virtual void setHidden(bool /*enabled*/)=0;
     /*public*/ virtual bool isHidden() =0;
     /*public*/ virtual void showHidden() =0;

     /*public*/ virtual int getDisplayLevel()=0;
     /*public*/ void virtual setDisplayLevel(int /*l*/) =0;

     /*public*/ virtual Editor* getEditor() =0;
     /*public*/ virtual void setEditor(Editor* /*ed*/) =0;
     /*public*/ virtual void updateSize() {}
     /*public*/ virtual int maxWidth()=0;
     /*public*/ virtual int maxHeight() =0;

     /**
     * Make a deep copy of Positional object. Implementation should
     * create a new object and immediately pass the object to
     * finishClone() returning the result of finishClone().
     * i.e. implementation must be:
     * public Positionable deepClone() {
     *    Subtype t = new Subtype();
     *    return finishClone(t);
     * }
     */
     /*public*/ virtual Positionable* deepClone() =0;
     /**
     * Finsh the deep Copy of a Positional object. Implementation should
     * make deep copies of the additional members of this sub class and
     * then pass Positionable p to super.finishClone().
     * i.e. implementation must terminate with statement
     * return super.finishClone(p);
     * See IndicatorTurnoutIcon extends TurnoutIcon extends PositionableLabel
     * for an example of how to continue deep cloning a chain of subclasses.
     */
     /*public*/virtual  Positionable* finishClone(Positionable* /*p*/) =0;

     /** Methods to add popup menu items
     * return true if a popup item is set
     */
     /*public*/ virtual QString getNameString() {return "";}
     /*public*/ virtual bool setRotateOrthogonalMenu(QMenu* /*popup*/){return false;}
     /*public*/ virtual bool setRotateMenu(QMenu* /*popup*/) {return false;}
     /*public*/ virtual bool setScaleMenu(QMenu* /*popup*/){return false;}
     /*public*/ virtual bool setEditIconMenu(QMenu* /*popup*/){return false;}
     /*public*/ virtual bool setEditItemMenu(QMenu* /*popup*/){return false;}
     /*public*/ virtual bool setDisableControlMenu(QMenu* /*popup*/){return false;}
     /*public*/ virtual bool setTextEditMenu(QMenu* /*popup*/){return false;}

     /*public*/ virtual bool showPopUp(QMenu* /*popup*/) {return false;}

     /*public*/ virtual void setScale(double /*s*/) {}
     /*public*/ virtual double getScale() {return 0;}
     /*public*/ virtual void rotate(int /*deg*/) {}
     /*public*/ virtual int getDegrees() {return 0;}
     /*public*/ virtual bool getSaveOpaque() {return 0;}		// for rotated text
     /*public*/ virtual JComponent* getTextComponent() {return nullptr;}

     /*public*/ virtual void remove() {}

     /**
      * Store a permanent copy of this Positionable
      * The editorXml will call this method to find out whether it
      * should store this Positionable item.
      * @return true if the Editor should store this in the configuration file
      * @return false if if the Editor should not store this object
      */
     /*public*/ virtual bool storeItem() {return false;}
     /**
      * Use the 'Standard' presentation of the popup menu items.
      * The editor will call this method to find out whether it
      * should creates any popup viewing menu items.
      * @return true if Editor may add the standardpopup menu items
     */
     /*public*/ virtual bool doViemMenu(){return false;}
     /*
     * Utility to handle Margins, Borders and other common popup items
     * @return null if these item do not apply
     */
     /*public*/ virtual PositionablePopupUtil* getPopupUtility() {return NULL;}
     /*public*/ virtual void setPopupUtility(PositionablePopupUtil* /*tu*/) {}
     /*public*/ virtual NamedBean* getNamedBean() {throw NullPointerException();}
     // Mouse-handling events.  See
     // Editor class for more information on how these are used.
     /*public*/ virtual void doMousePressed(QGraphicsSceneMouseEvent* /*event*/) {}
     /*public*/ virtual void doMouseReleased(QGraphicsSceneMouseEvent* /*event*/) {}
     /*public*/ virtual void doMouseClicked(QGraphicsSceneMouseEvent* /*event*/) {}
     /*public*/ virtual void doMouseDragged(QGraphicsSceneMouseEvent* /*event*/) {}
     /*public*/ virtual void doMouseMoved(QGraphicsSceneMouseEvent* /*event*/) {}
     /*public*/ virtual void doMouseEntered(QGraphicsSceneMouseEvent* /*event*/) {}
     /*public*/ virtual void doMouseExited(QGraphicsSceneMouseEvent* /*event*/) {}

     // The following are common for all JComponents
     /*public*/ virtual QRectF getBounds(QRectF /*r*/ = QRectF()) {return QRectF();}
     /*public*/ virtual bool contains(int /*x*/, int /*y*/) {return false;}
     /*public*/ virtual int getX() = 0;
     /*public*/ virtual int getY() = 0;
     /*public*/ virtual QPointF getLocation() {return QPointF();}
     /*public*/ virtual void setLocation(int /*x*/, int /*y*/){}
     /*public*/ virtual void setLocation(QPointF /*p*/) {}
     /*public*/ virtual void setSize(int /*width*/, int /*height*/) {}
     /*public*/ virtual void setVisible(bool b) {_bVisible = b;}
     /*public*/ virtual bool isVisible() {return _bVisible;}
     /*public*/ virtual int getWidth() {return 0;}
     /*public*/ virtual int getHeight() {return 0;}
//        /*public*/ virtual Container getParent();
     /*public*/ virtual void setOpaque(bool /*isOpaque*/) {}
     /*public*/ virtual bool isOpaque()  {return false;}
     /*public*/ virtual void setBackground(QColor ){}
     /*public*/ virtual QColor getBackground() {return QColor();}
     /*public*/ virtual void setForeground(QColor /*bg*/) {}
     /*public*/ virtual QColor getForeground() {return QColor();}
     /*public*/ virtual QFont getFont() {return QFont();}
     /*public*/ virtual void setBorder(Border* /*border*/) {}
//        /*public*/ virtual Dimension getPreferredSize();
//    /*public*/ virtual void invalidate() {repaint();}
//        /*public*/ virtual void repaint() {}
     /*public*/ virtual bool requestFocusInWindow() {return false;}
     QGraphicsItem* getItem();
     void setItem(QGraphicsTextItem* item);
     MyGraphicsItemGroup* _itemGroup = nullptr;
     MyGraphicsItemGroup* _handleGroup = nullptr;
     virtual QString getGroupName() { return "Positionable";}
     virtual QObject* self() = 0;
     virtual QString getClass() {return "";}
 #if QT_VERSION >= 0x050000
     virtual void languageChange() {}
 #endif
     virtual bool updateScene() { return false;}
     virtual void setLevel(int /*level*/) {}
     virtual void paint(EditScene*) {}

 private:
     bool _bVisible = true;
};
Q_DECLARE_INTERFACE(Positionable, "Positionable")
#endif // POSITIONABLE_H
