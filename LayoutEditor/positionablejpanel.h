#ifndef POSITIONABLEJPANEL_H
#define POSITIONABLEJPANEL_H

#include "positionablelabel.h"
#include "logger.h"

class QGraphicsItemGroup;
class JFrameItem;
class NamedBean;
class PositionablePopupUtil;
class IconAdder;
class QFrame;
class QGraphicsSceneMouseEvent;
class Positionable;
class Editor;
class QMenu;
class PositionableJPanel : public PositionableLabel
{
    Q_OBJECT
public:
    //explicit PositionableJPanel(QObject *parent = 0);
    /*public*/ PositionableJPanel(Editor* editor, QObject *parent = 0);
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(Positionable* p);
//    /*public*/ void setPositionable(bool enabled);
//    /*public*/ bool isPositionable();
//    /*public*/ void setEditable(bool enabled);
//    /*public*/ bool isEditable() ;
//    /*public*/ void setViewCoordinates(bool enabled) ;
//    /*public*/ bool getViewCoordinates();
//    /*public*/ void setControlling(bool enabled);
//    /*public*/ bool isControlling();
//    /*public*/ void setHidden(bool hide);
//    /*public*/ bool isHidden();
//    /*public*/ void showHidden();
//    /*public*/ void setLevel(int l);
//    /*public*/ void setDisplayLevel(int l);
//    /*public*/ int getDisplayLevel();
//    /*public*/ void setShowTooltip(bool set) ;
//    /*public*/ bool showTooltip();
//    /*public*/ void setTooltip(QString tip);
//    /*public*/ QString getTooltip();
    /*public*/ void setScale(double s);
    /*public*/ double getScale();
    // no subclasses support rotations (yet)
    /*public*/ void rotate(int deg) ;
    /*public*/ int getDegrees();
    /*public*/ bool getSaveOpaque();
    /*public*/ QObject* getTextComponent();
    /*public*/ QString getNameString();
    /*public*/ Editor* getEditor();
    /*public*/ void setEditor(Editor* ed);
    // overide where used - e.g. momentary
    /*public*/ void doMousePressed(QGraphicsSceneMouseEvent* event);
    /*public*/ void doMouseReleased(QGraphicsSceneMouseEvent* event);
    /*public*/ void doMouseClicked(QGraphicsSceneMouseEvent* event);
    /*public*/ void doMouseDragged(QGraphicsSceneMouseEvent* event);
    /*public*/ void doMouseMoved(QGraphicsSceneMouseEvent* event);
    /*public*/ void doMouseEntered(QGraphicsSceneMouseEvent* event);
    /*public*/ void doMouseExited(QGraphicsSceneMouseEvent* event);
    /*public*/ bool doViemMenu();
    /*public*/ bool setRotateOrthogonalMenu(QMenu* popup);
    /*public*/ bool setRotateMenu(QMenu* popup);
    /*public*/ bool setScaleMenu(QMenu* popup);
    /*public*/ bool setDisableControlMenu(QMenu* popup);
    /*public*/ bool setTextEditMenu(QMenu* popup);
    /*public*/ bool showPopUp(QMenu* popup);
    JFrameItem* _iconEditorFrame;
    IconAdder* _iconEditor;
    /*public*/ bool setEditIconMenu(QMenu* popup);
    /*public*/ bool setEditItemMenu(QMenu* popup) ;
    /*public*/ void remove();
    void cleanup();
    /*public*/ bool isActive();
    /*public*/ void mousePressed(QGraphicsSceneMouseEvent* e);
    /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* e);
    /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* e);
    /*public*/ void mouseExited(QGraphicsSceneMouseEvent* e);
    /*public*/ bool storeItem();
    /*public*/ void mouseEntered(QGraphicsSceneMouseEvent* e);
    /*public*/ void mouseMoved(QGraphicsSceneMouseEvent* e);
    /*public*/ void mouseDragged(QGraphicsSceneMouseEvent* e);
//    /*public*/ void setPopupUtility(PositionablePopupUtil* tu);
//    /*public*/ PositionablePopupUtil* getPopupUtility();
    /*public*/ void updateSize();
    /*public*/ int maxWidth();
    /*public*/ int maxHeight();
    /*public*/ NamedBean* getNamedBean() { return NULL;}
    void setSize(int w, int h);
    void setName(QString name);
    bool isOpaque();
    QString getName();
//    void setLocation(int x, int y);
//    /*public*/ QRect getBounds(QRect rv);
    //QGraphicsProxyWidget* widget;
    QRectF getBounds(QRectF);
    /*public*/ bool updateScene();
signals:

public slots:
private:
    /*private*/ double _scale;// = 1.0;    // scaling factor

    QMenu* lock;// = NULL;
    QAction* showTooltipItem;// = NULL;
    Logger* log;
    void edit();
    bool active;// = true;
   // PositionablePopupUtil* _popupUtil;
    QString name;
//    int _x, _y;
    bool _bOpaque;
protected:

    /*protected*/ Editor* _editor;// = NULL;
    /*protected*/ bool debug;// = false;

    /*private*/ QString _tooltip;
    /*protected*/ bool _showTooltip;// =true;
    /*protected*/ bool _editable;// = true;
//    /*protected*/ bool _positionable;// = true;
//    /*protected*/ bool _viewCoordinates;// = false;
//    /*protected*/ bool _controlling;// = true;
//    /*protected*/ bool _hidden;// = false;
//    /*protected*/ int _displayLevel;
    /*protected*/ void makeIconEditorFrame(QObject* pos, QString name, bool table, IconAdder* editor);
    //QGraphicsItemGroup* _itemGroup;

};

#endif // POSITIONABLEJPANEL_H
