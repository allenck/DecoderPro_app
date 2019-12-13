#ifndef POSITIONABLEJPANEL_H
#define POSITIONABLEJPANEL_H

#include "positionablelabel.h"
#include "logger.h"
#include "positionable.h"
#include "jpanel.h"

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
class PositionableJPanel : public JPanel, public Positionable
{
 Q_OBJECT
 Q_INTERFACES(Positionable)
public:
    //explicit PositionableJPanel(QObject *parent = 0);
    /*public*/ PositionableJPanel(Editor* editor, QObject *parent = 0);
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(PositionableJPanel* pos);
    /*public*/ void setPositionable(bool enabled);
    /*public*/ bool isPositionable();
    /*public*/ void setEditable(bool enabled);
    /*public*/ bool isEditable() ;
    /*public*/ void setViewCoordinates(bool enabled) ;
    /*public*/ bool getViewCoordinates();
    /*public*/ void setControlling(bool enabled);
    /*public*/ bool isControlling();
    /*public*/ void setHidden(bool hide);
    /*public*/ bool isHidden();
    /*public*/ void showHidden();
    /*public*/ void setLevel(int l);
    /*public*/ void setDisplayLevel(int l);
    /*public*/ int getDisplayLevel();
    /*public*/ void setShowToolTip(bool set) ;
    /*public*/ bool showTooltip();
    /*public*/ void setToolTip(QString tip);
    /*public*/ QString getToolTip();
    /*public*/ void setScale(double s);
    /*public*/ double getScale();
    // no subclasses support rotations (yet)
    /*public*/ void rotate(int deg) ;
    /*public*/ int getDegrees();
    /*public*/ bool getSaveOpaque();
    /*public*/ QWidget *getTextComponent();
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
    virtual /*public*/ void mousePressed(QGraphicsSceneMouseEvent* e);
    virtual /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* e);
    virtual /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* e);
    virtual /*public*/ void mouseExited(QGraphicsSceneMouseEvent* e);
    /*public*/ bool storeItem();
    virtual /*public*/ void mouseEntered(QGraphicsSceneMouseEvent* e);
    virtual /*public*/ void mouseMoved(QGraphicsSceneMouseEvent* e);
    virtual /*public*/ void mouseDragged(QGraphicsSceneMouseEvent* e);
    /*public*/ void setPopupUtility(PositionablePopupUtil* tu);
    /*public*/ PositionablePopupUtil* getPopupUtility();
    /*public*/ void updateSize();
    /*public*/ int maxWidth();
    /*public*/ int maxHeight();
    /*public*/ NamedBean* getNamedBean() { return NULL;}
    void setSize(int w, int h);
    void setName(QString name);
    bool isOpaque();
    QString getName();
    void setLocation(int x, int y);
    int getX();
    int getY();

//    /*public*/ QRect getBounds(QRect rv);
    //QGraphicsProxyWidget* widget;
    QRectF getBounds(QRectF);
    /*public*/ bool updateScene();
    QObject* self() {return (QObject*)this;}
    /*public*/ virtual MyGraphicsProxyWidget* getWidget() {return nullptr;}
signals:

public slots:
private:
    /*private*/ double _scale;// = 1.0;    // scaling factor

    QMenu* lock;// = NULL;
    QAction* showTooltipItem;// = NULL;
    Logger* log;
    void edit();
    bool active;// = true;
    PositionablePopupUtil* _popupUtil = nullptr;
    QString name;
    int _x, _y;
    bool _bOpaque = false;
    MyGraphicsProxyWidget* widget = nullptr;

protected:

    /*protected*/ Editor* _editor;// = NULL;
    /*protected*/ bool debug;// = false;

    /*private*/ QString _tooltip;
    /*protected*/ bool _showTooltip =true;
    /*protected*/ bool _editable = true;
    /*protected*/ bool _positionable = true;
    /*protected*/ bool _viewCoordinates = false;
    /*protected*/ bool _controlling = true;
    /*protected*/ bool _hidden = false;
    /*protected*/ int _displayLevel=0;
    /*protected*/ void makeIconEditorFrame(QObject* pos, QString name, bool table, IconAdder* editor);
    //QGraphicsItemGroup* _itemGroup;
friend class MemoryComboIcon;
friend class MemorySpinnerIcon;
friend class MemoryInputIcon;
};

#endif // POSITIONABLEJPANEL_H
