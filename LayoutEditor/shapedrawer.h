#ifndef SHAPEDRAWER_H
#define SHAPEDRAWER_H

#include <QWidget>

class PositionableShape;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class Positionable;
class QMenu;
class DrawFrame;
class ControlPanelEditor;
class ShapeDrawer : public QWidget
{
    Q_OBJECT
public:
    //explicit ShapeDrawer(QObject *parent = 0);
    /*public*/ ShapeDrawer(ControlPanelEditor* ed, QWidget *parent = 0);
    /*public*/ virtual QMenu* makeMenu();
    ///*public*/ void saveSelectionGroup(QList<Positionable*>* selectionGroup);
    /*public*/ bool doMousePressed(QGraphicsSceneMouseEvent* event, Positionable* pos);
    /*public*/ bool doMouseReleased(Positionable* selection, QGraphicsSceneMouseEvent* event);
    /*public*/ bool doMouseClicked(QGraphicsSceneMouseEvent* event);
    /*public*/ bool doMouseDragged(QGraphicsSceneMouseEvent* event);
    /*public*/ bool doMouseMoved(QGraphicsSceneMouseEvent* event);

    virtual /*public*/ void paint(QGraphicsScene* g);
    /*public*/ void add(bool up);
    /*public*/ void _delete();

signals:

public slots:
    /*private*/ void newRectangle();
    /*private*/ void newCircle();
    /*private*/ void newEllipse();
    /*private*/ void newRoundRectangle();
    /*private*/ void newPolygon();

private:
    /*private*/ bool 	_creatingNewShape;// = false;
    /*private*/ DrawFrame* 	_drawFrame;
    /*private*/ PositionableShape* _currentSelection;
    //QList<Positionable*>* _saveSelectionGroup;
    void closeEvent(QCloseEvent *);
protected:
    /*protected*/ ControlPanelEditor* _editor;
    /*protected*/ void setDrawFrame(DrawFrame* f);
    /*protected*/ void closeDrawFrame(DrawFrame* f);
    /*protected*/ ControlPanelEditor* getEditor();
friend class DrawFrame;
friend class DrawRectangle;
friend class DrawCircle;
friend class DrawEllipse;
friend class DrawRoundRect;
friend class DrawPolygon;
};

#endif // SHAPEDRAWER_H
