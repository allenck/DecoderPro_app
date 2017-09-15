#ifndef POSITIONABLECIRCLE_H
#define POSITIONABLECIRCLE_H
#include "positionableshape.h"

class PositionableCircle : public PositionableShape
{
    Q_OBJECT
public:
    //explicit PositionableCircle(QWidget *parent = 0);
    /*public*/ PositionableCircle(Editor* editor, QWidget* parent = 0);
    /*public*/ PositionableCircle(Editor* editor, QGraphicsEllipseItem* shape, QWidget* parent = 0);
    ///*public*/ void setRadius(int r);
    /*public*/ void setHeight(int r);
    ///*public*/ int getRadius();
    /*public*/ void makeShape();
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(Positionable* p);
    /*public*/ bool setEditItemMenu(QMenu* popup);
    ///*public*/ bool updateScene();

signals:

public slots:
    void onEditAct();
protected:
///*protected*/ int	_radius;// = 100;
friend class Editor;
};

#endif // POSITIONABLECIRCLE_H
