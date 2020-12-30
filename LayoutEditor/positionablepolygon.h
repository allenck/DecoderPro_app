#ifndef POSITIONABLEPOLYGON_H
#define POSITIONABLEPOLYGON_H
#include "positionableshape.h"
#include <QRect>
#include "abstractaction.h"

class GeneralPath;
class PositionablePolygon : public PositionableShape
{
 Q_OBJECT
public:
 PositionablePolygon();
 /*public*/ PositionablePolygon(Editor* editor);
 /*public*/ PositionablePolygon(Editor* editor, JShape* shape);
 /*public*/ Positionable* deepClone();
 /*public*/ void removeHandles();
 /*public*/ void drawHandles();
 /*public*/ bool setEditItemMenu(QMenu* popup);
 /*public*/ void doMousePressed(QGraphicsSceneMouseEvent* event);
 /*public*/ bool updateScene(); // TODO: this function not in Java


private:
 /*private*/ QList<QRect>* _vertexHandles;
 /*private*/ bool _editing;// = false;
 /*private*/ bool isLeftMost(int x);
 /*private*/ bool isTopMost(int y);
 /*private*/ GeneralPath* scale(float ratioX, float ratioY);

protected:
 /*protected*/ Positionable* finishClone(PositionablePolygon* pos);
 /*protected*/ void editing(bool edit);
 /*protected*/ int getHitIndex();
 /*protected*/ bool doHandleMove(QGraphicsSceneMouseEvent* event);
 /*protected*/ void paintHandles(QGraphicsScene* g2d);

friend class DrawPolygon;
};

class PolygonAction :  public AbstractAction
{
 Q_OBJECT
 PositionablePolygon* ps;
public:
 PolygonAction(QString txt, QObject* parent) : AbstractAction(txt, parent) {}
 PolygonAction* init(PositionablePolygon* p);

public slots:
/*public*/ void actionPerformed(JActionEvent* e = 0)override;
};

#endif // POSITIONABLEPOLYGON_H
