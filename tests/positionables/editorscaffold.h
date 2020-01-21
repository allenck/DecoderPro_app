#ifndef EDITORSCAFFOLD_H
#define EDITORSCAFFOLD_H
#include "editor.h"

class EditorScaffold : public Editor
{
 Q_OBJECT
public:
 EditorScaffold(QWidget* parent = nullptr);
 /*public*/ EditorScaffold(QString name, bool saveSize, bool savePosition, QWidget *parent= nullptr);
 /*public*/ EditorScaffold(QString name, QWidget *parent= nullptr);
 /*public*/ void mousePressed(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseDragged(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseMoved(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseEntered(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseExited(QGraphicsSceneMouseEvent* event);
 /*public*/ void initView();
 /*public*/ QString getClassName() {}

protected:
 /*protected*/ void init(QString name);
 /*protected*/ void targetWindowClosingEvent(QCloseEvent* e);
 /*protected*/ void paintTargetPanel(QGraphicsScene* g);
 /*protected*/ void setNextLocation(Positionable* obj);
 /*protected*/ void showPopUp(Positionable* p, QGraphicsSceneMouseEvent* event);
 /*protected*/ void copyItem(Positionable* p);

};

#endif // EDITORSCAFFOLD_H
