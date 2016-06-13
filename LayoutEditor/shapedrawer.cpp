#include "shapedrawer.h"
#include <QMenu>
#include "drawrectangle.h"
#include "controlpaneleditor.h"
#include <QGraphicsSceneMouseEvent>
#include "drawframe.h"
#include "drawcircle.h"
#include "drawellipse.h"
#include "drawroundrect.h"

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

/*public*/ ShapeDrawer::ShapeDrawer(ControlPanelEditor* ed, QWidget *parent) :
QWidget(parent)
{
    _editor = ed;
    _creatingNewShape = false;
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

    /*

    shapeItem = new JMenuItem(tr("Draw Polygon"));
    drawMenu.add(shapeItem);
    shapeItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent event) {
                newPolygon();
            }
        });
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
  QWidget* params = _drawFrame->makeParamsPanel();
        //((QVBoxLayout*)_drawFrame->centralWidget()->layout())->insertWidget(0, params, 0, Qt::AlignTop);
  _drawFrame->panelLayout->insertWidget(0, params, 0, Qt::AlignTop);
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
  QWidget* params = _drawFrame->makeParamsPanel();
        //((QVBoxLayout*)_drawFrame->centralWidget()->layout())->insertWidget(0,params, 0, Qt::AlignTop);
  _drawFrame->panelLayout->insertWidget(0,params, 0, Qt::AlignTop);

 }
 else
 {
  _drawFrame->toFront();
 }
}
#if 0
private void newPolygon() {
}
private void newLine() {
}
#endif
/*private*/ void ShapeDrawer::newCircle()
{
 if (_drawFrame==NULL)
 {
  _drawFrame = new DrawCircle(tr("New %1 Shape"), "Circle", this);
  QWidget* params = _drawFrame->makeParamsPanel();
  //((QVBoxLayout*)_drawFrame->centralWidget()->layout())->insertWidget(0,params, 0, Qt::AlignTop);
  _drawFrame->panelLayout->insertWidget(0,params, 0, Qt::AlignTop);
 }
 else
 {
  _drawFrame->toFront();
 }
}
/*private*/ void ShapeDrawer::newEllipse() {
    if (_drawFrame==NULL) {
        _drawFrame = new DrawEllipse(tr("New %1 Shape"), "Ellipse", this);
        QWidget* params = _drawFrame->makeParamsPanel();
        //((QVBoxLayout*)_drawFrame->centralWidget()->layout())->insertWidget(0,params, 0, Qt::AlignTop);
        _drawFrame->panelLayout->insertWidget(0,params, 0, Qt::AlignTop);
    } else {
        _drawFrame->toFront();
    }
}

/*protected*/ void ShapeDrawer::closeDrawFrame(DrawFrame* /*f*/) {
    _drawFrame = NULL;
}

/*protected*/ ControlPanelEditor* ShapeDrawer::getEditor() {
 return _editor;
}

/**************************** Mouse *************************/

/**
* Keep selections when editing.  Restore what super NULLs
*/
/*public*/ void ShapeDrawer::saveSelectionGroup(QList<Positionable*>* selectionGroup) {
 _saveSelectionGroup = selectionGroup;
}

/*public*/ bool ShapeDrawer::doMousePressed(QGraphicsSceneMouseEvent* /*event*/)
{
 if (_drawFrame!=NULL)
 {
  _editor->setSelectionGroup(QList<Positionable*>());
  _drawFrame->setDrawParams();
  return true;
 }
 return false;
}

/*public*/ bool ShapeDrawer::doMouseReleased(Positionable* /*selection*/, QGraphicsSceneMouseEvent* /*event*/)
{
 if (_drawFrame!=NULL)
 {
  _drawFrame->makeFigure();
  _drawFrame->closingEvent();
  _editor->resetEditor();
  return true;
 }
 return false;
}

/*public*/ bool ShapeDrawer::doMouseClicked(Positionable* /*selection*/, QGraphicsSceneMouseEvent* /*event*/) {
    if (_drawFrame!=NULL) {
        return true;
    }
    return false;
}

/**
* No dragging when editing
*/
/*public*/ bool ShapeDrawer::doMouseDragged(Positionable* /*selection*/, QGraphicsSceneMouseEvent* event)
{
 if (_drawFrame!=NULL)
 {
  _editor->drawSelectRect(event->scenePos().x(), event->scenePos().y());
  return true;     // no dragging when editing
 }
 return false;
}
void ShapeDrawer::closeEvent(QCloseEvent *)
{
 closeDrawFrame(_drawFrame);
}
