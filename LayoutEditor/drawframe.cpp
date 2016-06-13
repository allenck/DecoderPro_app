#include "drawframe.h"
#include <QColorDialog>
#include <QSlider>
#include "borderlayout.h"
#include <QLabel>
#include <QButtonGroup>
#include "shapedrawer.h"
#include <QRadioButton>
#include "positionableshape.h"
#include "controlpaneleditor.h"
#include <QTimer>

//DrawFrame::DrawFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 *
 */

// /*public*/ abstract class DrawFrame  extends jmri.util.JmriJFrame implements ChangeListener  {

/*static*/ int DrawFrame::STRUT_SIZE = 10;
/*static*/ QPoint DrawFrame::_loc = QPoint(100,100);
/*static*/ QSize DrawFrame::_dim =  QSize(500,500);

//    /*public*/ static final java.util.ResourceBundle rbcp = ControlPanelEditor.rbcp;

/*public*/ DrawFrame::DrawFrame(QString which, QString title, ShapeDrawer* parent) : JmriJFrame(title, false, false, (QWidget*)parent)
{
 //super(title, false, false);
 resize(400,500);
 _parent = parent;
 setTitle(QString(which).arg(title));
 QScrollArea* scrollArea = new QScrollArea;

 _lineWidth = 1;
 _lineColor = QColor(Qt::black);
 _alpha = 127;

 QWidget* panel = new QWidget();
 //panel.setLayout(new BorderLayout(10,10));
 panel->setLayout(panelLayout = new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));

 if (which==("New %1 Shape"))
 {
  //panel.add(Box.createVerticalStrut(STRUT_SIZE));
  panelLayout->addStrut(STRUT_SIZE);
//  QWidget* p = new QWidget();
//  p->setLayout(new QVBoxLayout); //(p/*, BoxLayout.Y_AXIS*/));
  QVBoxLayout* pLayout = new QVBoxLayout;
  QLabel* l = new QLabel(tr("Set the attributes for the shape.  Then make a "));
  l->setAlignment(Qt::AlignLeft);
  pLayout->addWidget(l);
  l = new QLabel(tr("\"selection rectangle\" in the panel to hold the shape."));
  l->setAlignment(Qt::AlignLeft);
  pLayout->addWidget(l);
//  QWidget* pp = new QWidget();
//  pp->setLayout(new QVBoxLayout);
  QVBoxLayout* ppLayout = new QVBoxLayout;
  ppLayout->addLayout(pLayout);
  QWidget* params = makeParamsPanel();
  ppLayout->addWidget(params);
  panelLayout->addLayout(ppLayout);
  editor = parent->getEditor();
  connect(editor, SIGNAL(selectionRect(QRectF)), this, SLOT(onSelectionRect(QRectF)));
 }
 //panel.add(Box.createVerticalStrut(STRUT_SIZE));
 panelLayout->addStrut(STRUT_SIZE);
 panelLayout->addWidget(makePanel());
 //panel.add(Box.createVerticalStrut(STRUT_SIZE));
 panelLayout->addStrut(STRUT_SIZE);

 //setContentPane(panel);
 setCentralWidget(scrollArea);
 scrollArea->setWidget(panel);
 scrollArea->setWidgetResizable(true);

//    addWindowListener(new java.awt.event.WindowAdapter() {
//          /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//              closingEvent();
//          }
//    });
 DFWindowListener* listener = new DFWindowListener(this);
 addWindowListener(listener);
 pack();
 setLocation(_loc.x(), _loc.y());
 setVisible(true);
 QTimer::singleShot(50, this, SLOT(pack()));
}
DFWindowListener::DFWindowListener(DrawFrame *frame)
{
 this->frame = frame;
}
void DFWindowListener::windowClosing(QCloseEvent *e)
{
 frame->closingEvent();
}

void DrawFrame::onSelectionRect(QRectF)
{
 makeFigure();
 closingEvent();
 editor->resetEditor();
}

/*protected*/ QWidget* DrawFrame::makePanel()
{
 QWidget* panel = new QWidget();
 QVBoxLayout* panelLayout;
 panel->setLayout(panelLayout = new QVBoxLayout); //(panel/*, BoxLayout.Y_AXIS*/));
 QWidget* p = new QWidget();
 p->setLayout(new QVBoxLayout);//(p/*, BoxLayout.Y_AXIS*/));
 p->layout()->addWidget(new QLabel(tr("Line Width")));
 QWidget* pp = new QWidget();
 pp->setLayout(new QHBoxLayout);
 pp->layout()->addWidget(new QLabel(tr("Thin")));
 _lineSlider = new QSlider(/*SwingConstants.HORIZONTAL, 1, 30, _lineWidth*/);
 _lineSlider->setMinimum(1);
 _lineSlider->setMaximum(30);
 _lineSlider->setValue(_lineWidth);
 _lineSlider->setOrientation(Qt::Horizontal);
 pp->layout()->addWidget(_lineSlider);
 pp->layout()->addWidget(new QLabel(tr("Thick")));
 p->layout()->addWidget(pp);
 panel->layout()->addWidget(p);
 p = new QWidget();
 p->setLayout(new QHBoxLayout);
 QButtonGroup* bg = new QButtonGroup();
 _lineColorButton = new QRadioButton(tr("Line Color"));
 p->layout()->addWidget(_lineColorButton);
 bg->addButton(_lineColorButton);
 _fillColorButton = new QRadioButton(tr("Fill Color"));
 p->layout()->addWidget(_fillColorButton);
 bg->addButton(_fillColorButton);
 _lineColorButton->setChecked(true);
 connect(_lineColorButton, SIGNAL(clicked()), this, SLOT(onLineColor()));
 connect(_fillColorButton, SIGNAL(clicked()), this, SLOT(onFillColor()));
 panelLayout->addWidget(p);
//	       _chooser = new JColorChooser(_parent.getEditor().getTargetPanel().getBackground());
 _chooser = new QColorDialog(QColor(Qt::lightGray));
//    _chooser->setColor(QColor(Qt::green));
//    _chooser.getSelectionModel().addChangeListener(this);
//    _chooser->setPreviewPanel(new QWidget());
 _chooser->setOption(QColorDialog::NoButtons, true);
 _chooser->setOption(QColorDialog::ShowAlphaChannel,true);
 connect(_chooser, SIGNAL(currentColorChanged(QColor)), this, SLOT(stateChanged(QColor)));
 panelLayout->addWidget(_chooser);
 p = new QWidget();
 p->setLayout(new QVBoxLayout(p/*, BoxLayout.Y_AXIS*/));
 p->layout()->addWidget(new QLabel(tr("Transparency")));
 pp = new QWidget();
 pp->setLayout(new QHBoxLayout);
 pp->layout()->addWidget(new QLabel(tr("Transparent")));
 _fillSlider = new QSlider(/*SwingConstants.HORIZONTAL, 0, 255, _alpha*/);
 _fillSlider->setMinimum(0);
 _fillSlider->setMaximum(255);
 _fillSlider->setOrientation(Qt::Horizontal);
 _fillSlider->setValue(_alpha);
 pp->layout()->addWidget(_fillSlider);
 pp->layout()->addWidget(new QLabel(tr("Opaque")));
 p->layout()->addWidget(pp);
 panelLayout->addWidget(p);
 //panel.add(Box.createVerticalStrut(STRUT_SIZE));
 panelLayout->addStrut(STRUT_SIZE);
 return panel;
}

/*protected*/ QWidget* DrawFrame::makeParamsPanel()
{
 QWidget* panel = new QWidget();
 QVBoxLayout* panelLayout;
 panel->setLayout(panelLayout = new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
 //panel.add(Box.createVerticalStrut(STRUT_SIZE));
 panelLayout->addStrut(STRUT_SIZE);
 return panel;
}

/**
 * Set parameters on the popup that will edit the PositionableShape
 */
/*protected*/ void DrawFrame::setDisplayParams(PositionableShape* ps) {
    _alpha = ps->getAlpha();
    _fillSlider->setValue(_alpha);
    _lineWidth = ps->getLineWidth();
    _lineSlider->setValue(_lineWidth);
    _lineColor = ps->getLineColor();
    _fillColor = ps->getFillColor();
}

/*protected*/ void DrawFrame::setPositionableParams(PositionableShape* ps) {
    ps->setAlpha(_fillSlider->value());		//set before setting colors
    ps->setLineColor(_lineColor);
    ps->setFillColor(_fillColor);
    ps->setLineWidth(_lineSlider->value());
}

/*protected*/ void DrawFrame::setDrawParams() {
#if 0
    TargetPane targetPane = (TargetPane)_parent.getEditor().getTargetPanel();
    Stroke stroke = new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 10f);
    targetPane.setSelectRectStroke(stroke);
    targetPane.setSelectRectColor(Color.green);
#endif
}

/*protected*/ void DrawFrame::closingEvent()
{
 if (_parent!=NULL)
 {
  _parent->closeDrawFrame(this);
  _parent->getEditor()->resetEditor();
 }
 _loc = getLocation(_loc);
 _dim = getSize(_dim);
 //disconnect(editor, SIGNAL(selectionRect(QRectF)), this, SLOT(onSelectionRect(QRectF)));

 close();
 dispose();
}

/*public*/ void DrawFrame::stateChanged(/*ChangeEvent* e*/QColor color)
{
 if (_lineColorButton->isChecked())
 {
  _lineColor = color;
 }
 else if (_fillColorButton->isChecked())
 {
  _fillColor = color;
 }
}

// /*abstract*/ /*protected*/ void DrawFrame::makeFigure(){}
// /*abstract*/ /*protected*/ void DrawFrame::updateFigure(PositionableShape* /*pos*/){}

/**
 * Stores the width/height of this component into "return value" <b>rv</b>
 * and return <b>rv</b>.   If rv is <code>null</code> a new
 * <code>Dimension</code> object is allocated.  This version of
 * <code>getSize</code> is useful if the caller wants to avoid
 * allocating a new <code>Dimension</code> object on the heap.
 *
 * @param rv the return value, modified to the components size
 * @return rv
 */
/*public*/ QSize DrawFrame::getSize(QSize rv)
{
 if (rv.isNull())
 {
  return size();
 }
 else
 {
  rv= size();
  return rv;
 }
}

/**
 * Stores the x,y origin of this component into "return value" <b>rv</b>
 * and return <b>rv</b>.   If rv is <code>null</code> a new
 * <code>Point</code> is allocated.
 * This version of <code>getLocation</code> is useful if the
 * caller wants to avoid allocating a new <code>Point</code>
 * object on the heap.
 *
 * @param rv the return value, modified to the components location
 * @return rv
 */
/*public*/ QPoint DrawFrame::getLocation(QPoint rv)
{
 if (rv.isNull())
 {
  return  mapToGlobal(QPoint(0,0));
 }
 else
 {
  rv = mapToGlobal(QPoint(0,0));
  return rv;
 }
}
void DrawFrame::onLineColor()
{
 if(_lineColorButton->isChecked())
  _chooser->setCurrentColor(_lineColor);
}
void DrawFrame::onFillColor()
{
 if(_fillColorButton->isChecked())
  _chooser->setCurrentColor(_fillColor);
}
