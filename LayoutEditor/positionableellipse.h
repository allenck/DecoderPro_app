#ifndef POSITIONABLEELLIPSE_H
#define POSITIONABLEELLIPSE_H
#include "positionableshape.h"

class QGraphicsItem;
class Editor;
class QMenu;
class PositionableEllipse : public PositionableShape
{
    Q_OBJECT
public:
    //explicit PositionableEllipse(QWidget *parent = 0);
    /*public*/ PositionableEllipse(Editor* editor,QWidget *parent = 0);
    /*public*/ PositionableEllipse(Editor* editor, QGraphicsEllipseItem* shape,QWidget *parent = 0);
//    /*public*/ void setWidth(int w);
//    /*public*/ void setHeight(int h) ;
    /*public*/ void rotate(int deg);
    /*public*/ void makeShape();
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(Positionable* p);
    /*public*/ bool setEditItemMenu(QMenu*  popup);
 ///*public*/ bool updateScene();

signals:

public slots:
    void onEditAct();
private:
//    int _width;
//    int _height;
friend class Editor;
};

#endif // POSITIONABLEELLIPSE_H
