#ifndef POSITIONABLEROUNDRECT_H
#define POSITIONABLEROUNDRECT_H
#include "positionablerectangle.h"

class QGraphicsRoundRectItem;
class PositionableRoundRect : public PositionableRectangle
{
    Q_OBJECT
public:
    //explicit PositionableRoundRect(QWidget *parent = 0);
    /*public*/ PositionableRoundRect(Editor* editor, QWidget *parent = 0);
    /*public*/ PositionableRoundRect(Editor* editor, QGraphicsRoundRectItem* shape, QWidget *parent = 0);
    /*public*/ void setCornerRadius(int r) ;
    /*public*/ int getCornerRadius();
    /*public*/ void makeShape();
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(Positionable* p);
    /*public*/ bool setEditItemMenu(QMenu* popup);
    ///*public*/ bool updateScene();

signals:

public slots:
    void onEditAct();
private:

protected:
    /*protected*/ int	_radius;// = 10;
friend class Editor;
};

#endif // POSITIONABLEROUNDRECT_H
