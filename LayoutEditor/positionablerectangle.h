#ifndef POSITIONABLERECTANGLE_H
#define POSITIONABLERECTANGLE_H
#include "positionableshape.h"

//class Shape;
class QGraphicsItem;
class PositionableRectangle : public PositionableShape
{
    Q_OBJECT
public:
    //explicit PositionableRectangle(QWidget *parent = 0);
    /*public*/ PositionableRectangle(Editor* editor, QWidget* parent = 0);
    /*public*/ PositionableRectangle(Editor* editor, QGraphicsRectItem* shape, QWidget* parent = 0);
//    /*public*/ void setWidth(int w);
//    /*public*/ void setHeight(int h);
    /*public*/ void rotate(int deg);
    /*public*/ void makeShape();
// Fix !!!TODO
    /*public*/ Positionable* finishClone(Positionable* p);
    /*public*/ bool setEditItemMenu(QMenu* popup);
    /*public*/ Positionable* deepClone();
    ///*public*/ bool updateScene();
signals:

public slots:
    void editAction();

private:
//    int _width;
//    int _height;
friend class PositionableRoundRect;
friend class Editor;
};

#endif // POSITIONABLERECTANGLE_H
