#include "positionableshape.h"
#include <QMenu>
#include <QColor>
#include "editor.h"
#include "drawframe.h"
#include "flowlayout.h"
#include <QPushButton>
#include "coordinateedit.h"

//PositionableShape::PositionableShape(QWidget *parent) :
//    PositionableJComponent(parent)
//{
//}
/**
 * PositionableShape is item drawn by ava.awt.Graphics2D.
 * <P>
 * @author Pete cresman Copyright (c) 2012
 * @version $Revision: 1 $
 */

///*public*/ class PositionableShape extends PositionableJComponent {


//    /*public*/ final static java.util.ResourceBundle rbcp = ControlPanelEditor.rbcp;

/*public*/ PositionableShape::PositionableShape(Editor* editor, QWidget *parent) : PositionableJComponent(editor, parent)
{
 //super(editor);
 init();
 setOpaque(false);
}

/*public*/ PositionableShape::PositionableShape(Editor* editor, QGraphicsItem* shape, QWidget *parent = 0) : PositionableJComponent(editor, parent)
{
 //this(editor);
 init();
 _shape = shape;
}
void PositionableShape::init()
{
 setObjectName("PositionableShape");
 _lineColor = QColor(Qt::black);
 _alpha = 255;
 _lineWidth = 1;
 _shape = NULL;
 _degrees = 0;
 setVisible(true);
}
/**
 * this class must be overridden by its subclasses and executed
 *  only after its parameters have been set
 */
/*public*/ void PositionableShape::makeShape() {
}

/*public*/ void PositionableShape::setLineColor(QColor c) {
    if (!c.isValid()) {
        c = QColor(Qt::black);
    }
    _lineColor = c;
}
/*public*/QColor PositionableShape::getLineColor() {
    return _lineColor;
}

/*public*/ void PositionableShape::setFillColor(QColor c) {
    if (c==QColor() || _alpha==0) {
        _fillColor = QColor();
    } else {
        _fillColor =  QColor(c.red(), c.green(), c.blue(), _alpha);
    }
}
/*public*/ QColor PositionableShape::getFillColor( ) {
    return _fillColor;
}

/*public*/ void PositionableShape::setAlpha(int a) {
    _alpha = a;
}
/*public*/ int PositionableShape::getAlpha() {
    return _alpha;
}

/*public*/ void PositionableShape::setLineWidth(int w) {
    _lineWidth = w;
}
/*public*/ int PositionableShape::getLineWidth() {
    return _lineWidth;
}

/*public*/ void PositionableShape::paint(EditScene* /*g*/) {
    /*
    Graphics2D g2d = (Graphics2D)g;
    g2d.setRenderingHint(RenderingHints.KEY_RENDERING,
                         RenderingHints.VALUE_RENDER_QUALITY);
    g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                         RenderingHints.VALUE_ANTIALIAS_ON);
    g2d.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION,
                         RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY);
    g2d.setRenderingHint(RenderingHints.KEY_INTERPOLATION,
                         RenderingHints.VALUE_INTERPOLATION_BICUBIC);
    g2d.setClip(null);
    if (_transform!=null ) {
        g2d.transform(_transform);
    }
    if (_fillColor!=null) {
        g2d.setColor(_fillColor);
        g2d.fill(_shape);
    }
    g2d.setColor(_fillColor);
    BasicStroke stroke = new BasicStroke(_lineWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10f);
    g2d.setColor(_lineColor);
    g2d.setStroke(stroke);
    g2d.draw(_shape);
    */
}

/*public*/ Positionable* PositionableShape::deepClone() {
    PositionableShape* pos = new PositionableShape(_editor);
    return finishClone(pos);
}

/*public*/ Positionable* PositionableShape::finishClone(Positionable* p) {
    PositionableShape* pos = (PositionableShape*)p;
    pos->_alpha = _alpha;
    pos->_lineWidth = _lineWidth;
    pos->setFillColor(_fillColor);
    pos->_lineColor =  QColor(_lineColor.red(), _lineColor.green(), _lineColor.blue());
    pos->makeShape();
    pos->updateSize();
    return PositionableJComponent::finishClone(pos);
}

/*public*/ QSize PositionableShape::getSize(QSize /*rv*/) {
    return  QSize(maxWidth(), maxHeight());
}

/*public*/ void PositionableShape::updateSize() {
    /*
    int w = maxWidth();
    int h = maxHeight();
    if (_transform !=null) {
        Point2D.Double[] pts = new Point2D.Double[4];
        pts[0] = new Point2D.Double(0, 0);
        pts[1] = new Point2D.Double(w, 0);
        pts[2] = new Point2D.Double(w, h);
        pts[3] = new Point2D.Double(0, h);
        _transform.transform(pts, 0, pts, 0, 4);
        Double minX = pts[0].x;
        Double maxX = pts[0].x;
        Double minY = pts[0].y;
        Double maxY = pts[0].y;
        for (int i=1; i<4; i++) {
            minX = Math.min(minX, pts[i].x);
            maxX = Math.max(maxX, pts[i].x);
            minY = Math.min(minY, pts[i].y);
            maxY = Math.max(maxY, pts[i].y);
        }
        w = (int)Math.ceil(maxX-minX);
        h = (int)Math.ceil(maxY-minY);
    }
    setSize(w, h);
    */
    setSize(maxWidth(), maxHeight());
}

/*public*/ int PositionableShape::maxWidth() {
    if (_shape==NULL) {
        return 0;
    }
    return _shape->boundingRect().width();
}

/*public*/ int PositionableShape::maxHeight() {
    if (_shape==NULL) {
        return 0;
    }
    return _shape->boundingRect().height();
}

/*public*/ bool PositionableShape::showPopUp(QMenu* /*popup*/) {
    return false;
}

/**
* Rotate degrees	!!!TODO
* return true if popup is set
*/
/*public*/ bool PositionableShape::setRotateMenu(QMenu* popup)
{
 if (getDisplayLevel() > Editor::BKG)
 {
  CoordinateEdit* coordinateEdit = new CoordinateEdit();
  popup->addAction(CoordinateEdit::getRotateEditAction(this,coordinateEdit));
  return true;
 }
 return false;
}

/*public*/ bool PositionableShape::setScaleMenu(QMenu* /*popup*/)
{
 return false;
}

/*public*/ int PositionableShape::getDegrees() {
    return _degrees;
}

/*public*/ bool PositionableShape::setEditItemMenu(QMenu* /*popup*/) {
    return false;
}

/*protected*/ void PositionableShape::setEditParams()
{
 _editFrame->setDisplayParams(this);

//    QWidget* centralWidget = new QWidget();
//    centralWidget->setLayout(new QVBoxLayout);
//    _editFrame->setCentralWidget(centralWidget);
//    QWidget* contentPane = _editFrame->centralWidget();
 QVBoxLayout* contentPaneLayout = _editFrame->panelLayout;
 contentPaneLayout->addWidget(_editFrame->makeParamsPanel());
 contentPaneLayout->addWidget(makeDoneButtonPanel());
 _editFrame->pack();
}

/*protected*/ QWidget* PositionableShape::makeDoneButtonPanel() {
 QWidget* panel0 = new QWidget();
 panel0->setLayout(new FlowLayout());
 QPushButton* doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                editItem();
//            }
//    });
 connect(doneButton, SIGNAL(clicked()),this, SLOT(editItem()));
 panel0->layout()->addWidget(doneButton);

 QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                _editFrame.dispose();
//            }
//    });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(OnCancel_clicked()));
 panel0->layout()->addWidget(cancelButton);
 return panel0;
}
/*protected*/ void PositionableShape::editItem()
{
 _editFrame->updateFigure(this);
 if(_itemGroup != NULL && _itemGroup->scene() !=NULL)
 {
  _editor->removeFromTarget(this);
  _itemGroup = new QGraphicsItemGroup;
 }
 makeShape();
 updateSize();
 _editFrame->dispose();
 repaint();
 _editor->addToTarget(this);
}
void PositionableShape::OnCancel_clicked()
{
 _editFrame->dispose();
}
