#include "drawrectangle.h"
#include "controlpaneleditor.h"
#include "jtextfield.h"
#include "shapedrawer.h"
#include "positionablerectangle.h"

//DrawRectangle::DrawRectangle(QWidget *parent) :
//    DrawFrame(parent)
//{
//}
/**
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 *
 */

///*public*/ class DrawRectangle extends DrawFrame{


/*public*/ DrawRectangle::DrawRectangle(QString which, QString title, ShapeDrawer* parent) : DrawFrame(which, title, parent)
{
 //super(which, title, parent);
 _lineWidth = 3;
 if(parent != NULL)
 ControlPanelEditor* editor = parent->getEditor();
}

/*protected*/ QWidget* DrawRectangle::makeParamsPanel(PositionableShape* ps)
{
 QWidget* panel = DrawFrame::makeParamsPanel(ps);
 QWidget* p = new QWidget();
 p->setLayout(new QVBoxLayout(p/*, BoxLayout.X_AXIS*/));
 QWidget* pp = new QWidget();
 pp->setLayout(new QHBoxLayout);
 _widthText = new JTextField(6);
 _widthText->setValidator(new QIntValidator());
//    _widthText.addKeyListener(new KeyListener() {
//        /*public*/ void keyTyped(KeyEvent E) { }
//        /*public*/ void keyPressed(KeyEvent E){ }
//        /*public*/ void keyReleased(KeyEvent E) {
//          JTextField tmp = (JTextField) E.getSource();
//          String t = tmp.getText();
//          if (t!=null && t.length()>0) {
//              _width = Integer.parseInt(t);
//          }
//        }
//        });
    connect(_widthText, SIGNAL(textEdited(QString)), this, SLOT(widthEdited(QString)));
    _widthText->setText(QString::number(_width));
    _widthText->setAlignment(Qt::AlignRight);
    pp->layout()->addWidget(_widthText);
    pp->layout()->addWidget(new QLabel(tr("width")));
    p->layout()->addWidget(pp);
    //p.add(Box.createHorizontalStrut(STRUT_SIZE));
    ((QBoxLayout*)p->layout())->addStrut(STRUT_SIZE);
    pp = new QWidget();
    pp->setLayout(new QHBoxLayout);
    _heightText = new JTextField(6);
    _heightText->setValidator(new QIntValidator());
//    _heightText.addKeyListener(new KeyListener() {
//        /*public*/ void keyTyped(KeyEvent E) { }
//        /*public*/ void keyPressed(KeyEvent E){ }
//        /*public*/ void keyReleased(KeyEvent E) {
//          JTextField tmp = (JTextField) E.getSource();
//          String t = tmp.getText();
//          if (t!=null && t.length()>0) {
//              _height = Integer.parseInt(t);
//          }
//        }
//        });
    connect(_heightText, SIGNAL(textEdited(QString)), this, SLOT(heightEdited(QString)));
    _heightText->setText(QString::number(_height));
    _heightText->setAlignment(Qt::AlignRight);
    pp->layout()->addWidget(_heightText);
    pp->layout()->addWidget(new QLabel(tr("height")));
    p->layout()->addWidget(pp);

    panel->layout()->addWidget(p);
    //panel.add(Box.createVerticalStrut(STRUT_SIZE));
    ((QBoxLayout*)p->layout())->addStrut(STRUT_SIZE);
    return panel;
}
void DrawRectangle::widthEdited(QString t)
{
    if(t != "" && t.length() > 0)
        _width = t.toInt();
}
void DrawRectangle::heightEdited(QString t)
{
    if(t != "" && t.length() > 0)
        _height = t.toInt();
}

/**
 * Create a new PositionableShape
 */
/*protected*/ void DrawRectangle::makeFigure()
{
 ControlPanelEditor* ed = _parent->getEditor();
 QRectF r = ed->getSelectRect();
 if (!r.isValid())
 {
  return;
 }
 _width = r.width();
 _height = r.height();
 QGraphicsRectItem* rr = new QGraphicsRectItem(QRectF(0, 0, _width, _height));
 rr->setBrush(QBrush(_fillColor));
 rr->setPen(QPen(QBrush(_lineColor),_lineWidth));
 PositionableRectangle* ps = new PositionableRectangle(ed, rr);
 ps->_itemGroup = new MyGraphicsItemGroup();
 ps->_itemGroup->setName("drawRectangle");
 ps->_itemGroup->addToGroup(rr);
 ps->setLocation(r.x(), r.y());
 ps->setHeight(_height);
 ps->setWidth(_width);
 ps->setDisplayLevel(ControlPanelEditor::MARKERS);
 setDisplayParams(ps);
 ps->updateSize();
 ed->putItem(ps);
}

/**
 * Set parameters on a new or updated PositionableShape
 */
///*protected*/ void DrawRectangle::setPositionableParams(PositionableShape* p) {
//    DrawFrame::setPositionableParams(p);
//    PositionableRectangle* pos = (PositionableRectangle*)p;
//    pos->setWidth(_width);
//    pos->setHeight(_height);
//}

/**
 * Set parameters on the popup that will edit the PositionableShape
 */
/*protected*/ void DrawRectangle::setDisplayParams(PositionableShape* p) {
    DrawFrame::setDisplayParams(p);
    PositionableRectangle* pos = (PositionableRectangle*)p;
    _width = pos->getWidth();
    _height = pos->getHeight();
}

/**
 * Editing is done.  Update the existing PositionableShape
 */
///*protected*/ void DrawRectangle::updateFigure(PositionableShape* p) {
//    PositionableRectangle* pos = (PositionableRectangle*)p;
//    setPositionableParams(pos);
////		pos.makeShape();
//}
/*public*/ QString DrawRectangle::getClassName()
{
 return "jmri.jmrit.display.controlPanelEditor.shape.DrawRectangle";
}

