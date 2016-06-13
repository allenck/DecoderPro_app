#ifndef SHAPEDRAWER_H
#define SHAPEDRAWER_H

#include <QWidget>

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
    /*public*/ void saveSelectionGroup(QList<Positionable*>* selectionGroup);
    /*public*/ bool doMousePressed(QGraphicsSceneMouseEvent* event);
    /*public*/ bool doMouseReleased(Positionable* selection, QGraphicsSceneMouseEvent* event);
    /*public*/ bool doMouseClicked(Positionable* selection, QGraphicsSceneMouseEvent* event);
    /*public*/ bool doMouseDragged(Positionable* selection, QGraphicsSceneMouseEvent* event);

signals:

public slots:
    /*private*/ void newRectangle();
    /*private*/ void newCircle();
    /*private*/ void newEllipse();
    /*private*/ void newRoundRectangle();

private:
    /*private*/ bool 	_creatingNewShape;// = false;
    /*private*/ DrawFrame* 	_drawFrame;
    QList<Positionable*>* _saveSelectionGroup;
    void closeEvent(QCloseEvent *);
protected:
    /*protected*/ ControlPanelEditor* _editor;
    /*protected*/ void closeDrawFrame(DrawFrame* f);
    /*protected*/ ControlPanelEditor* getEditor();
friend class DrawFrame;
friend class DrawRectangle;
friend class DrawCircle;
friend class DrawEllipse;
friend class DrawRoundRect;
};

#endif // SHAPEDRAWER_H
