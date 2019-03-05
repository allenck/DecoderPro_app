#include "shapedrawer.h"
#include <QMenu>
#include "drawrectangle.h"
#include "controlpaneleditor.h"
#include <QGraphicsSceneMouseEvent>
#include "drawframe.h"
#include "drawcircle.h"
#include "drawellipse.h"
#include "drawroundrect.h"
#include "drawpolygon.h"
#include "positionableshape.h"

//ShapeDrawer::ShapeDrawer(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 *
 */

// /*public*/ class ShapeDrawer  {


//    /*public*/ final static ResourceBundle rbcp = ControlPanelEditor.rbcp;

/*public*/ ShapeDrawer::ShapeDrawer(ControlPanelEditor* ed, QObject *parent) :
QObject(parent)
{
    _editor = ed;
    _creatingNewShape = false;
    _drawFrame = NULL;
    _currentSelection = NULL;
}

/*public*/ QMenu* ShapeDrawer::makeMenu() {
    QMenu* drawMenu = new QMenu(tr("Draw Shapes"));

    QAction* shapeItem = new QAction(tr("Draw Rectangle"),this);
    drawMenu->addAction(shapeItem);
//    shapeItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                newRectangle();
//            }
//        });
    connect(shapeItem,SIGNAL(triggered()), this, SLOT(newRectangle()));

    shapeItem = new QAction(tr("Draw Round Rectangle"),this);
    drawMenu->addAction(shapeItem);
//    shapeItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                newRoundRectangle();
//            }
//        });
    connect(shapeItem, SIGNAL(triggered()), this, SLOT(newRoundRectangle()));

    shapeItem = new QAction(tr("Draw Polygon"), this);
    drawMenu->addAction(shapeItem);
//    shapeItem.addActionListener(new ActionListener() {
//            public void actionPerformed(ActionEvent event) {
//                newPolygon();
//            }
//        });
    connect(shapeItem, SIGNAL(triggered()), this, SLOT(newPolygon()));

    /*
    shapeItem = new JMenuItem(tr("Draw Line"));
    drawMenu.add(shapeItem);
    shapeItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent event) {
                newLine();
            }
        });
        */
    shapeItem = new QAction(tr("Draw Circle"),this);
    drawMenu->addAction(shapeItem);
//    shapeItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                newCircle();
//            }
//        });
    connect(shapeItem, SIGNAL(triggered()), this, SLOT(newCircle()));

    shapeItem = new QAction(tr("Draw Ellipse"),this);
    drawMenu->addAction(shapeItem);
//    shapeItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                newEllipse();
//            }
//        });
    connect(shapeItem, SIGNAL(triggered()), this, SLOT(newEllipse()));
    return drawMenu;
}

/*private*/ void ShapeDrawer::newRectangle()
{
 if (_drawFrame==NULL)
 {
  _drawFrame = new DrawRectangle(tr("New %1 Shape"), "Rectangle", this);
 }
 else
 {
  _drawFrame->toFront();
 }
}

/*private*/ void ShapeDrawer::newRoundRectangle()
{
 if (_drawFrame==NULL)
 {
  _drawFrame = new DrawRoundRect(tr("New %1 Shape"), "Round Rect", this);
 }
 else
 {
  _drawFrame->toFront();
 }
}
/*private*/ void ShapeDrawer::newPolygon()
{
 if (_drawFrame == NULL)
 {
  _drawFrame = new DrawPolygon("newShape", "Polygon", this);
 }
 else
 {
  _drawFrame->toFront();
 }
}
#if 0
private void newLine() {
}
#endif
/*private*/ void ShapeDrawer::newCircle()
{
 if (_drawFrame==NULL)
 {
  _drawFrame = new DrawCircle(tr("New %1 Shape"), "Circle", this);
 }
 else
 {
  _drawFrame->toFront();
 }
}
/*private*/ void ShapeDrawer::newEllipse() {
    if (_drawFrame==NULL) {
        _drawFrame = new DrawEllipse(tr("New %1 Shape"), "Ellipse", this);
    } else {
        _drawFrame->toFront();
    }
}

/*protected*/ void ShapeDrawer::setDrawFrame(DrawFrame* f) {
        _drawFrame = f;
    }

/*protected*/ void ShapeDrawer::closeDrawFrame(DrawFrame* /*f*/)
{
    _drawFrame = NULL;
}

/*protected*/ ControlPanelEditor* ShapeDrawer::getEditor() {
 return _editor;
}

/*public*/ void ShapeDrawer::paint(QGraphicsScene* g)
{
   //if (_drawFrame instanceof DrawPolygon) {
 if(qobject_cast<DrawPolygon*>(_drawFrame) != NULL)
 {
  ((DrawPolygon*) _drawFrame)->drawShape(g);
 }
}
/**************************** Mouse *************************/

/**
* Keep selections when editing.  Restore what super NULLs
*/
///*public*/ void ShapeDrawer::saveSelectionGroup(QList<Positionable*>* selectionGroup) {
// _saveSelectionGroup = selectionGroup;
//}

/*public*/ bool ShapeDrawer::doMousePressed(QGraphicsSceneMouseEvent* event, Positionable* pos)
{
 //if (_drawFrame instanceof DrawPolygon) {
 if(qobject_cast<DrawPolygon*>(_drawFrame))
 {
  DrawPolygon* f = (DrawPolygon*) _drawFrame;
  f->anchorPoint(event->screenPos().x(), event->screenPos().y());
 }
 //if (pos instanceof PositionableShape && _editor.isEditable()) {
 if(qobject_cast<PositionableShape*>((QObject*)pos) != NULL && _editor->isEditable())
 {
  if (pos != _currentSelection)
  {
   if (_currentSelection != NULL)
   {
    _currentSelection->removeHandles();
   }
   _currentSelection = (PositionableShape*) pos;
   _currentSelection->drawHandles();
  }
  return true;
 }
 if (_currentSelection != NULL) {
     _currentSelection->removeHandles();
     _currentSelection = NULL;
 }
 return false;
}

/*public*/ bool ShapeDrawer::doMouseReleased(Positionable* /*selection*/, QGraphicsSceneMouseEvent* event)
{
 if (_drawFrame != NULL && _drawFrame->_shape == NULL)
 {
  if (_drawFrame->makeFigure(event))
   _editor->resetEditor();
  return true;
 }
 return false;
}

/*public*/ bool ShapeDrawer::doMouseClicked(QGraphicsSceneMouseEvent* event) // double click event
{
 if (_drawFrame != NULL)
 {
//  if(qobject_cast<DrawPolygon*>(_drawFrame)/* && event->getClickCount()>1) */)
//  {
//   ((DrawPolygon*)_drawFrame)->setEditing(true);
//  }
//  return true;
}
return false;}

/**
* No dragging when editing
*/
/*public*/ bool ShapeDrawer::doMouseDragged(QGraphicsSceneMouseEvent* event)
{
// if (_drawFrame instanceof DrawPolygon && _currentSelection == null) {
 if(qobject_cast<DrawPolygon*>(_drawFrame) && _currentSelection == NULL)
 {
  ((DrawPolygon*) _drawFrame)->moveTo(event->screenPos().x(), event->screenPos().y());
  return true;		// no select rect
 }
 else if (_currentSelection != NULL)
 {

  return _currentSelection->doHandleMove(event);
 }
 return false;
}

/*
 * Make rubber band line
 */
/*public*/ bool ShapeDrawer::doMouseMoved(QGraphicsSceneMouseEvent* event) {
 if(qobject_cast<DrawPolygon*>(_drawFrame))
 {
  ((DrawPolygon*) _drawFrame)->moveTo(event->screenPos().x(), event->screenPos().y());
  return true;     // no dragging when editing
 }
 return false;
}

/*public*/ void ShapeDrawer::add(bool up)
{
 if(qobject_cast<DrawPolygon*>(_drawFrame)) {
     ((DrawPolygon*) _drawFrame)->addVertex(up);
 }
}

/*public*/ void ShapeDrawer::_delete() {
    if(qobject_cast<DrawPolygon*>(_drawFrame)) {
        ((DrawPolygon*) _drawFrame)->deleteVertex();
    }
}

void ShapeDrawer::closeEvent(QCloseEvent *)
{
 closeDrawFrame(_drawFrame);
}
