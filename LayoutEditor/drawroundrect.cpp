#include "drawroundrect.h"
#include "QVBoxLayout"
#include "jtextfield.h"
#include "controlpaneleditor.h"
#include "editscene.h"
#include "positionableroundrect.h"
#include "shapedrawer.h"

//DrawRoundRect::DrawRoundRect(QWidget *parent) :
//    DrawRectangle(parent)
//{
//}
/**
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 *
 */

// /*public*/ class DrawRoundRect extends DrawRectangle {


/*public*/ DrawRoundRect::DrawRoundRect(QString which, QString title, ShapeDrawer* parent) : DrawRectangle(which, title, parent) {
    //super(which, title, parent);
    _radius = 40;
}

/*protected*/ QWidget* DrawRoundRect::makeParamsPanel() {
   QWidget* panel = DrawRectangle::makeParamsPanel();
   QWidget* p = new QWidget();
   p->setLayout(new QVBoxLayout(p/*, BoxLayout.X_AXIS*/));
   QWidget* pp = new QWidget();
   pp->setLayout(new QHBoxLayout);
   _radiusText = new JTextField(6);
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
   _radiusText->setText(QString::number(_radius));
   _radiusText->setAlignment(Qt::AlignRight);
   pp->layout()->addWidget(_radiusText);
   pp->layout()->addWidget(new JLabel(tr("Corner Radius")));
   p->layout()->addWidget(pp);
   panel->layout()->addWidget(p);
   //panel.add(Box.createVerticalStrut(STRUT_SIZE));
   ((QBoxLayout*)panel->layout())->addStrut(STRUT_SIZE);
   return panel;
}

/**
* Create a new PositionableShape*
*/
/*protected*/ void DrawRoundRect::makeFigure() {
    ControlPanelEditor* ed = _parent->getEditor();
    QRectF r = ed->getSelectRect();
    if (!r.isValid()) {
       return;
    }
    //RoundRectangle2D.Double rr = new RoundRectangle2D.Double(0, 0, r.width, r.height, _radius, _radius);
    QGraphicsRoundRectItem* rr = new QGraphicsRoundRectItem(0, 0, r.width(), r.height(), _radius, _radius);
    rr->setBrush(QBrush(_fillColor));
    rr->setPen(QPen(QBrush(_lineColor),_lineWidth));
    PositionableRoundRect* ps = new PositionableRoundRect(ed, rr);
    ps->_itemGroup = new QGraphicsItemGroup();
    ps->_itemGroup->addToGroup(rr);
    ps->setLocation(r.x(), r.y());
    ps->setHeight(_height);
    ps->setWidth(_width);
    ps->setDisplayLevel(ControlPanelEditor::MARKERS);
    setPositionableParams(ps);
    ps->updateSize();
    ed->putItem(ps);
}


/*protected*/ void DrawRoundRect::setPositionableParams(PositionableShape* p) {
    DrawRectangle::setPositionableParams(p);
       ((PositionableRoundRect*) p)->setCornerRadius(_radius);
}

/**
 * Set parameters on the popup that will edit the PositionableShape
 */
/*protected*/ void DrawRoundRect::setDisplayParams(PositionableShape* p) {
    DrawRectangle::setDisplayParams(p);
    PositionableRoundRect* pos = (PositionableRoundRect*)p;
    _radius = pos->getCornerRadius();
}

/**
 * Editing is done.  Update the existing PositionableShape
 */
/*protected*/ void DrawRoundRect::updateFigure(PositionableShape* p) {
   PositionableRoundRect* pos = (PositionableRoundRect*)p;
   setPositionableParams(pos);
//	   pos.makeShape();
}
