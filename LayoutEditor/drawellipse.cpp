#include "drawellipse.h"
#include "controlpaneleditor.h"
#include "jtextfield.h"
#include <QBoxLayout>
#include "positionableellipse.h"
#include "shapedrawer.h"

//DrawEllipse::DrawEllipse(QWidget *parent) :
//    DrawFrame(parent)
//{
//}
/**
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 *
 */

// /*public*/ class DrawEllipse extends DrawFrame{


/*public*/ DrawEllipse::DrawEllipse(QString which, QString title, ShapeDrawer* parent) : DrawFrame(which, title, parent)
{
    //super(which, title, parent);
}

/*protected*/ QWidget* DrawEllipse::makeParamsPanel(PositionableShape* ps) {
    QWidget* panel = DrawFrame::makeParamsPanel(ps);
    //panel->setLayout(new QVBoxLayout);
    QWidget* p = new QWidget();
    p->setLayout(new QVBoxLayout(p/*, BoxLayout.X_AXIS*/));
    QWidget* pp = new QWidget();
    pp->setLayout(new QVBoxLayout);
    _widthText = new JTextField(6);
//    _widthText.addKeyListener(new KeyListener() {
//        public void keyTyped(KeyEvent E) { }
//        public void keyPressed(KeyEvent E){ }
//        public void keyReleased(KeyEvent E) {
//          JTextField tmp = (JTextField) E.getSource();
//          String t = tmp.getText();
//          if (t!=null && t.length()>0) {
//              _width = Integer.parseInt(t);
//          }
//        }
//        });
    _widthText->setText(QString::number(_width));
    _widthText->setAlignment(Qt::AlignRight);
    pp->layout()->addWidget(_widthText);
    pp->layout()->addWidget(new QLabel(tr("Width")));
    p->layout()->addWidget(pp);
    //p.add(Box.createHorizontalStrut(STRUT_SIZE));
    ((QBoxLayout*)p->layout())->addStrut(STRUT_SIZE);

    pp = new QWidget();
    pp->setLayout(new QVBoxLayout);
    _heightText = new JTextField(6);
//    _heightText.addKeyListener(new KeyListener() {
//        public void keyTyped(KeyEvent E) { }
//        public void keyPressed(KeyEvent E){ }
//        public void keyReleased(KeyEvent E) {
//          JTextField tmp = (JTextField) E.getSource();
//          String t = tmp.getText();
//          if (t!=null && t.length()>0) {
//              _height = Integer.parseInt(t);
//          }
//        }
//        });
    _heightText->setText(QString::number(_height));
    _heightText->setAlignment(Qt::AlignRight);
    pp->layout()->addWidget(_heightText);
    pp->layout()->addWidget(new QLabel(tr("Height")));
    p->layout()->addWidget(pp);

    panel->layout()->addWidget(p);
    //panel.add(Box.createVerticalStrut(STRUT_SIZE));
    ((QBoxLayout*)p->layout())->addStrut(STRUT_SIZE);
    return panel;
}
/**
 * Create a new PositionableShape
 */
/*protected*/ void DrawEllipse::makeFigure() {
    ControlPanelEditor* ed = _parent->getEditor();
    QRectF r = ed->getSelectRect();
    if (!r.isValid()) {
        return;
    }
    _width = r.width();
    _height = r.height();
    QGraphicsEllipseItem* rr = new QGraphicsEllipseItem(0, 0, _width, _height);
    rr->setBrush(QBrush(_fillColor));
    rr->setPen(QPen(QBrush(_lineColor),_lineWidth));
    PositionableEllipse* ps = new PositionableEllipse(ed, rr);
    ps->_itemGroup = new MyGraphicsItemGroup();
    ps->_itemGroup->setName("PositionableElipse");
    ps->_itemGroup->addToGroup(rr);
    ps->setLocation(r.x(), r.y());
    ps->setHeight(_height);
    ps->setWidth(_width);
    ps->setDisplayLevel(ControlPanelEditor::MARKERS);
    setPositionableParams(ps);
    ps->updateSize();
    ed->putItem(ps);
}

/**
 * Set parameters on a new or updated PositionableShape
 */
/*protected*/ void DrawEllipse::setPositionableParams(PositionableShape* p) {
    DrawFrame::setDisplayParams(p);
    PositionableEllipse* pos = (PositionableEllipse*)p;
    pos->setWidth(_width);
    pos->setHeight(_height);
}

/**
 * Set parameters on the popup that will edit the PositionableShape
 */
/*protected*/ void DrawEllipse::setDisplayParams(PositionableShape* p) {
    DrawFrame::setDisplayParams(p);
    PositionableEllipse* pos = (PositionableEllipse*)p;
    _width = pos->getWidth();
    _height = pos->getHeight();
}

/**
 * Editing is done.  Update the existing PositionableShape
 */
/*protected*/ void DrawEllipse::updateFigure(PositionableShape* p) {
    PositionableEllipse* pos = (PositionableEllipse*)p;
    setPositionableParams(pos);
//		pos.makeShape();
}
