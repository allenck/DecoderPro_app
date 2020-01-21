#include "drawcircle.h"
#include "jtextfield.h"
#include <QLabel>
#include <QBoxLayout>
#include "controlpaneleditor.h"
#include "shapedrawer.h"
#include "positionablecircle.h"

//DrawCircle::DrawCircle(QWidget *parent) :
//    DrawFrame(parent)
//{
//}
/**
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 *
 */

// /*public*/ class DrawCircle extends DrawFrame {


/*public*/ DrawCircle::DrawCircle(QString which, QString title, ShapeDrawer* parent) : DrawFrame(which, title, parent) {
    //super(which, title, parent);
    _radius = 100;
}

/**
 * Create a new PositionableShape
 */
/*protected*/ QWidget* DrawCircle::makeParamsPanel(PositionableShape* ps)
{
   QWidget* panel = DrawFrame::makeParamsPanel(ps);

   QWidget* p = new QWidget();
   p->setLayout(new QVBoxLayout(p/*, BoxLayout.Y_AXIS*/));
   p->layout()->addWidget(new QLabel(tr("Circle")));
   QWidget* pp = new QWidget();
   pp->setLayout(new QVBoxLayout);
   _diameterText = new JTextField(6);
//   _radiusText.addKeyListener(new KeyListener() {
//       public void keyTyped(KeyEvent E) { }
//       public void keyPressed(KeyEvent E){ }
//       public void keyReleased(KeyEvent E) {
//         JTextField tmp = (JTextField) E.getSource();
//         String t = tmp.getText();
//         if (t!=null && t.length()>0) {
//             _radius = Integer.parseInt(t);
//         }
//       }
//    });
   _diameterText->setText(QString::number(_radius));
   _diameterText->setAlignment(Qt::AlignRight);
   pp->layout()->addWidget(_diameterText);
   pp->layout()->addWidget(new QLabel(tr("Circle Radius")));
   p->layout()->addWidget(pp);
   panel->layout()->addWidget(p);
   //panel->layout()->addWidget(Box.createVerticalStrut(STRUT_SIZE));
   ((QBoxLayout*)panel->layout())->addStrut(STRUT_SIZE);
   return panel;
}

/*protected*/ void DrawCircle::makeFigure() {
    ControlPanelEditor* ed = _parent->getEditor();
    QRectF r = ed->getSelectRect();
    if (!r.isValid()) {
        return;
    }
    _radius = qMax(r.width(), r.height());
    QGraphicsEllipseItem* rr = new QGraphicsEllipseItem(0, 0, _radius, _radius);
    rr->setBrush(QBrush(_fillColor));
    rr->setPen(QPen(QBrush(_lineColor),_lineWidth));
    PositionableCircle* ps = new PositionableCircle(ed, rr);
    ps->_itemGroup = new MyGraphicsItemGroup();
    ps->_itemGroup->setName("PositionableCircle");

    ps->_itemGroup->addToGroup(rr);
    ps->setLocation(r.x(), r.y());
//    ps->setHeight(_height);
//    ps->setWidth(_width);
    ps->setDisplayLevel(ControlPanelEditor::MARKERS);
    setDisplayParams(ps);
    ps->updateSize();
    ed->putItem(ps);
    DrawFrame::closingEvent(true);
}

/**
 * Set parameters on a new or updated PositionableShape
 */
///*protected*/ void DrawCircle::setPositionableParams(PositionableShape* p) {
//    DrawFrame::setDisplayParams(p);
//   ((PositionableCircle*) p)->setRadius(_radius);
//}

/**
 * Set parameters on the popup that will edit the PositionableShape
 */
///*protected*/ void DrawCircle::setDisplayParams(PositionableShape* p) {
//    DrawFrame::setDisplayParams(p);
//    PositionableCircle* pos = (PositionableCircle*)p;
//    _radius = pos->getRadius();
//}

/**
 * Editing is done.  Update the existing PositionableShape
 */
///*protected*/ void DrawCircle::updateFigure(PositionableShape* p) {
//    PositionableCircle* pos = (PositionableCircle*)p;
//    setPositionableParams(pos);
////		pos.makeShape();
//}

//@Override
void DrawCircle::setDisplayWidth(int w) {
    _diameterText->setText(QString::number(w));
}

//@Override
void DrawCircle::setDisplayHeight(int h) {
    _diameterText->setText(QString::number(h));
}
/*public*/ QString DrawCircle::getClassName()
{
 return "jmri.jmrit.display.controlPanelEditor.shape.DrawCircle";
}
