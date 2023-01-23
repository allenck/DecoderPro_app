#include "drawframe.h"
#include <QSlider>
#include "borderlayout.h"
#include <QLabel>
#include <QButtonGroup>
#include "shapedrawer.h"
#include <QRadioButton>
#include "positionableshape.h"
#include "controlpaneleditor.h"
#include <QTimer>
#include "jtextfield.h"
#include <QMessageBox>
#include <QRadioButton>
#include <QComboBox>
#include "box.h"
#include "jcolorchooser.h"
#include "colorselectionmodel.h"
#include "loggerfactory.h"

DrawFrame::DrawFrame(QWidget *parent) :
    JmriJFrame(parent)
{
}
/**
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 *
 */

// /*public*/ abstract class DrawFrame  extends jmri.util.JmriJFrame implements ChangeListener  {

/*static*/ int DrawFrame::STRUT_SIZE = 10;
/*static*/ QPoint DrawFrame::_loc = QPoint(100,100);
/*static*/ QSize DrawFrame::_dim =  QSize(500,700);

//    /*public*/ static final java.util.ResourceBundle rbcp = ControlPanelEditor.rbcp;

/*public*/ DrawFrame::DrawFrame(QString which, QString title, ShapeDrawer* parent) : JmriJFrame(title, false, false, (QWidget*)parent)
{
 setFrameRef(getClassName());
 //super(title, false, false);
 _sensorName = new JTextField(30);
 _shape = NULL;
 _originalShape = NULL;

 resize(400,700);
 _parent = parent;
 //_editing = (_parent == NULL);        // i.e. constructor called from editItem popup
 setTitle(QString("New %1 Shape").arg(title));
 QScrollArea* scrollArea = new QScrollArea;

 _lineWidth = 1;
 _lineColor = QColor(Qt::black);
 _alpha = 127;

 QWidget* panel = new QWidget();
 //panel.setLayout(new BorderLayout(10,10));
 panel->setLayout(panelLayout = new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));

 QWidget* p = new QWidget();
 QLabel* l = new QLabel();
 //p.setLayout(new BoxLayout(p, BoxLayout.Y_AXIS));
 QVBoxLayout* pLayout = new QVBoxLayout(p);
 l->setWordWrap(true);
 pLayout->addWidget(l,0,Qt::AlignLeft);
 if (which==("newShape"))
 {
  //panelLayout->addWidget(Box.createVerticalStrut(STRUT_SIZE));
  //panelLayout->addStrut(STRUT_SIZE);
  l->setText(tr("Set the attributes for the shape.  Then make "));
  //l->setAlignment(Qt::AlignLeft);
  if (title==("Polygon"))
  {
   //l = new QLabel(tr("mouse clicks to create the vertices of the polygon."));
//   l->setAlignment(Qt::AlignLeft);
//   pLayout->addWidget(l);
//   l = new QLabel(tr("Double click on a vertex to complete the polygon."));
   l->setText(l->text() + tr("mouse clicks to create the vertices of the polygon. ") + tr("Double click on a vertex to complete the polygon.\n"));
  }
  else
  {
   //l = new QLabel(tr("a \"selection rectangle\" to hold the shape."));
   l->setText(l->text() + tr("a \"selection rectangle\" to hold the shape.\n"));
  }
//  l->setAlignment(Qt::AlignLeft);
//  pLayout->addWidget(l);
 }
 //panelLayout->addStrut(STRUT_SIZE);
 //QLabel* l = new QLabel(tr("(Optional) To control the visibility of the shape,"));
 //l.setAlignmentX(JComponent.LEFT_ALIGNMENT);
 //pLayout->addWidget(l,0,Qt::AlignLeft);
 l->setText(l->text() + tr("(Optional) To control the visibility of the shape,") + tr("enter the name of a sensor in the [%1] field below.").arg("Visibility or Level Control"));
 //l = new QLabel(tr("enter the name of a sensor in the [%1] field below.").arg(("Visibility or Level Control")));
 //l.setAlignmentX(JComponent.LEFT_ALIGNMENT);

 QWidget* pp = new QWidget();
 QVBoxLayout* ppLayout = new QVBoxLayout(pp);
 ppLayout->addWidget(p);
 panelLayout->addWidget(pp);

 panelLayout->addWidget(makeEditPanel());
 // PositionableShape adds buttons at the bottom
 //panelLayout->addStrut(STRUT_SIZE);
 panelLayout->addWidget(makeSensorPanel());
// panelLayout->addStrut(STRUT_SIZE);

 //setContentPane(panel);
 scrollArea->setWidget(panel);
 setCentralWidget(scrollArea);

// addWindowListener(new java.awt.event.WindowAdapter() {
//     @Override
//     public void windowClosing(java.awt.event.WindowEvent e) {
//         closingEvent(true);
//     }
// });
 addWindowListener(listener = new DFWindowListener(this));
 pack();
 move(_loc.x(), _loc.y());
 setVisible(true);
 setAlwaysOnTop(true);
}

DFWindowListener::DFWindowListener(DrawFrame *frame)
{
 this->frame = frame;
}

void DFWindowListener::windowClosing(QCloseEvent *e)
{
 frame->closingEvent(true);
}

//void DrawFrame::onSelectionRect(QRectF rect, QGraphicsSceneMouseEvent* event)
//{
// makeFigure(event);
// closingEvent(true);
// //editor->resetEditor();
//}

/*protected*/ QWidget* DrawFrame::makeEditPanel()
{
 QWidget* panel = new QWidget();
 QVBoxLayout* panelLayout;
 panel->setLayout(panelLayout = new QVBoxLayout); //(panel/*, BoxLayout.Y_AXIS*/));
 QWidget* p = new QWidget();
 p->setLayout(new QHBoxLayout);//(p/*, BoxLayout.Y_AXIS*/));
 p->layout()->addWidget(new QLabel(tr("Line Width: ")));
 QWidget* pp = new QWidget();
 pp->setLayout(new QHBoxLayout);
 pp->layout()->addWidget(new QLabel(tr("Thin")));
 _lineSlider = new QSlider(/*SwingConstants.HORIZONTAL, 1, 30, _lineWidth*/);
 _lineSlider->setMinimum(1);
 _lineSlider->setMaximum(30);
 _lineSlider->setValue(_lineWidth);
 _lineSlider->setOrientation(Qt::Horizontal);
 connect(_lineSlider, SIGNAL(valueChanged(int)), this, SLOT(widthChange()));
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
 _chooser = new JColorChooser(_parent->getEditor()->getTargetPanel()->backgroundBrush().color());
 _chooser->setColor(QColor(Qt::green));
 _chooser->getSelectionModel()->addChangeListener((ChangeListener*)this);
 _chooser->setPreviewPanel(new QWidget());
 connect(_chooser, SIGNAL(currentColorChanged(QColor)), this, SLOT(stateChanged(QColor)));
 panelLayout->addWidget(_chooser);
 panelLayout->addStrut(STRUT_SIZE);

 p = new QWidget();
 p->setLayout(new QHBoxLayout(p/*, BoxLayout.Y_AXIS*/));
 p->layout()->addWidget(new QLabel(tr("Transparency: ")));
 pp = new QWidget();
 pp->setLayout(new QHBoxLayout);
 pp->layout()->addWidget(new QLabel(tr("Transparent")));
 _alphaSlider = new QSlider(Qt::Horizontal);
 _alphaSlider->setRange(0,255);
 _alphaSlider->setValue(_lineColor.alpha());
 pp->layout()->addWidget(_alphaSlider);
 connect(_alphaSlider, SIGNAL(valueChanged(int)), this, SLOT(On_alphaSlider_valueChanged(int)));
// _fillSlider = new QSlider(/*SwingConstants.HORIZONTAL, 0, 255, _alpha*/);
// _fillSlider->setMinimum(0);
// _fillSlider->setMaximum(255);
// _fillSlider->setOrientation(Qt::Horizontal);
// _fillSlider->setValue(_alpha);
// pp->layout()->addWidget(_fillSlider);
 pp->layout()->addWidget(new QLabel(tr("Opaque")));
 p->layout()->addWidget(pp);
 panelLayout->addWidget(p);
 //panelLayout->addWidget(Box.createVerticalStrut(STRUT_SIZE));
 //panelLayout->addStrut(STRUT_SIZE);

 return panel;
}

void DrawFrame::On_alphaSlider_valueChanged(int)
{
 alphaChange();
}

/*protected*/ QWidget* DrawFrame::makeSensorPanel()
{
 QWidget* panel = new QWidget();
 //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
 QVBoxLayout* panelLayout = new QVBoxLayout(panel);
 QWidget* p = new QWidget();
 QHBoxLayout* pLayout = new QHBoxLayout(p);
 QWidget* p0 = new QWidget();
 QVBoxLayout* p0Layout = new QVBoxLayout(p0);
 p0Layout->addWidget(new QLabel(tr("An Active Sensor can either hide the shape or change its display level")));
 panelLayout->addWidget(p0);
 pLayout->addWidget(new QLabel(tr("Visibility or Level Control") + ":"));
 pLayout->addWidget(_sensorName);
// _sensorName.addActionListener( new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent e) {
//         String msg =_shape.setControlSensor(_sensorName.getText(), _hideShape.isSelected(), _shape.getChangeLevel());
//         if (msg != null) {
//             JOptionPane.showMessageDialog(null, msg, tr("MakeLabel", tr("ErrorSensor")), JOptionPane.INFORMATION_MESSAGE); // NOI18N
//             _sensorName.setText("");
//         }
//     }
// });
 connect(_sensorName, SIGNAL(editingFinished()), this, SLOT(On_sensorName_editingFinished()));
#if 0 // TODO:
 _sensorName.addMouseMotionListener( new MouseMotionListener() {
     @Override
     public void mouseDragged( MouseEvent e) {
         updateShape();
     }
     @Override
     public void mouseMoved(MouseEvent e) {
         QString msg =_shape.setControlSensor(_sensorName.getText(), _hideShape.isSelected(), _shape.getChangeLevel());
         if (msg != null) {
//             JOptionPane.showMessageDialog(null, msg, tr("MakeLabel", tr("ErrorSensor")), JOptionPane.INFORMATION_MESSAGE); // NOI18N
          QMessageBox::information(NULL, tr(""), tr("Error Sensor"));
             _sensorName.setText("");
         }
     }
 });
#endif
 panelLayout->addWidget(p);

 QWidget* p1 = new QWidget();
 //p1.setLayout(new BoxLayout(p1, BoxLayout.Y_AXIS));
 QHBoxLayout* p1Layout = new QHBoxLayout(p1);
 _hideShape = new QRadioButton(tr("Hide Shape"));
 _changeLevel = new QRadioButton(tr("Change Level"));
 QButtonGroup* bg = new QButtonGroup();
 bg->addButton(_hideShape);
 bg->addButton(_changeLevel);
 _levelComboBox = new QComboBox();
 _levelComboBox->addItem(tr("Same Level"));
 for (int i = 1; i < 11; i++)
 {
  _levelComboBox->addItem(tr("Level") + " " + QString::number(i));
 }
// _levelComboBox.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent evt) {
//         int level = _levelComboBox.getSelectedIndex();
//         _shape.setChangeLevel(level);
//     }

// });
 connect(_levelComboBox, SIGNAL(currentIndexChanged(int)), _shape, SLOT(setChangeLevel(int)));
// _hideShape.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent a) {
//         _levelComboBox.setEnabled(false);
//     }
// });
 connect(_hideShape, SIGNAL(toggled(bool)), this, SLOT(On_hideShape()));
// _changeLevel.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent a) {
//         _levelComboBox.setEnabled(true);
//     }
// });
 connect(_changeLevel, SIGNAL(toggled(bool)), this, SLOT(On_changeLevel()));
 p1Layout->addWidget(_hideShape);
 p1Layout->addWidget(_changeLevel);

 QWidget* p2 = new QWidget();
 //p2.setLayout(new BoxLayout(p2, BoxLayout.Y_AXIS));
 QVBoxLayout* p2Layout = new QVBoxLayout(p2);
 QWidget* p3 = new QWidget();
 QVBoxLayout* p3Layout = new QVBoxLayout(p3);
//        p3.add(Box.createRigidArea(_levelComboBox.getPreferredSize()));
 p2Layout->addWidget(p3);
 QWidget* p4 = new QWidget();
 QVBoxLayout* p4Layout = new QVBoxLayout(p4);
 p4Layout->addWidget(_levelComboBox);
 p2Layout->addWidget(p4);

 p0 = new QWidget();
 {
 //p0.setLayout(new BoxLayout(p0, BoxLayout.X_AXIS));
 QHBoxLayout* p0Layout = new QHBoxLayout(p0);
 //p0Layout->addWidget(Box.createHorizontalGlue());
 p0Layout->addWidget(p1);
 p0Layout->addWidget(p2);
 //p0Layout->addWidget(Box.createHorizontalGlue());
 panelLayout->addWidget(p0);
 }
 return panel;
}

void DrawFrame::On_hideShape()
{
  _levelComboBox->setEnabled(false);
}

void DrawFrame::On_changeLevel()
{
  _levelComboBox->setEnabled(true);
}

void DrawFrame::On_sensorName_editingFinished()
{
 QString msg =_shape->setControlSensor(_sensorName->text(), _hideShape->isChecked(), _shape->getChangeLevel());
 if (msg != "") {
//     JOptionPane.showMessageDialog(null, msg, tr("MakeLabel", tr("ErrorSensor")), JOptionPane.INFORMATION_MESSAGE); // NOI18N
  QMessageBox::information(NULL, tr("MakeLabel %1").arg(tr("Error Sensor")), msg);
  _sensorName->setText("");
 }
}

/*protected*/ QWidget* DrawFrame::makeParamsPanel(PositionableShape* ps)
{
 QWidget* panel = new QWidget();
 QVBoxLayout* panelLayout;
 panel->setLayout(panelLayout = new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
 //panelLayout->addWidget(Box.createVerticalStrut(STRUT_SIZE));
 panelLayout->addStrut(STRUT_SIZE);
 return panel;
}

/**
 * Set parameters on the popup that will edit the PositionableShape
 */
/*protected*/ void DrawFrame::setDisplayParams(PositionableShape* ps)
{
 _shape = ps;
 _lineWidth = _shape->getLineWidth();
 _lineSlider->setValue(_lineWidth);
 _lineColor = _shape->getLineColor();
 _fillColor = _shape->getFillColor();
 if (_lineColor.alpha() > _fillColor.alpha()) {
     _alphaSlider->setValue(_lineColor.alpha());
     _lineColorButton->setChecked(true);
 } else {
     _alphaSlider->setValue(_fillColor.alpha());
     _fillColorButton->setChecked(true);
 }
 _sensorName->setText(_shape->getSensorName());
 _levelComboBox->setCurrentIndex(ps->getChangeLevel());
 if (ps->isHideOnSensor()) {
     _hideShape->setChecked(true);
     _levelComboBox->setEnabled(false);
 } else {
     _changeLevel->setChecked(true);
 }

 panelLayout->addWidget(makeParamsPanel(_shape));
 panelLayout->addWidget(makeDoneButtonPanel());
 pack();
}

/**
 * Editing an existing shape (only make copy for cancel of edits)
 * @param ps shape
 */
/*protected*/ void DrawFrame::makeCopy(PositionableShape* ps) {
    // make a copy, but keep it out of editor's content
    _originalShape = (PositionableShape*)ps->deepClone();
    // cloning adds to editor's targetPane - (fix needed in editor)
    _originalShape->remove();
}

void DrawFrame::On_doneButton()
{
 closingEvent(false);
}

void DrawFrame::On_cancelButton()
{
 closingEvent(true);
}

/*private*/ QWidget* DrawFrame::makeDoneButtonPanel()
{
    QWidget* panel0 = new QWidget();
    //panel0.setLayout(new FlowLayout());
    FlowLayout* panel0Layout = new FlowLayout(panel0);
    QPushButton* doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            closingEvent(false);
//        }
//    });
    connect(doneButton, SIGNAL(clicked(bool)), this, SLOT(On_doneButton()));
    panel0Layout->addWidget(doneButton);

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            closingEvent(true);
//        }
//    });
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(On_cancelButton()));
    panel0Layout->addWidget(cancelButton);
    return panel0;
}
/*private*/ void DrawFrame::colorChange() {
        QColor c = _chooser->getColor();
        int alpha =  c.alpha();
        log->debug(tr("colorChange: color= %1, alpha= %2 ").arg(c.name()).arg(alpha));
        _alphaSlider->setValue(c.alpha());
        if (_lineColorButton->isChecked()) {
            _lineColor = QColor(c.red(), c.green(), c.blue(), alpha);
            if (_shape != nullptr) {
                _shape->setLineColor(_lineColor);
            }
        } else {
            _fillColor = QColor(c.red(), c.green(), c.blue(), alpha);
            if (_shape != nullptr) {
                _shape->setFillColor(_fillColor);
            }
        }
        updateShape();
    }

/*private*/ void DrawFrame::alphaChange()
{
    if (_shape==NULL) {
        return;
    }
    int alpha = _alphaSlider->value();
    if (_lineColorButton->isChecked()) {
        _lineColor = QColor(_lineColor.red(), _lineColor.green(), _lineColor.blue(), alpha);
        _shape->setLineColor(_lineColor);
    } else if (_fillColorButton->isChecked() && _fillColor!=QColor()) {
        _fillColor = QColor(_fillColor.red(), _fillColor.green(), _fillColor.blue(), alpha);
        _shape->setFillColor(_fillColor);
    }
    updateShape();
}

/*protected*/ void DrawFrame::closingEvent(bool cancel)
{
 removeWindowListener(listener);
 _loc = getLocation(_loc);
 _dim = getSize(_dim);
 if (_shape!=NULL)
 {
  if (cancel)
  {
   _shape->remove();
   if (_originalShape!=NULL) {
       _originalShape->getEditor()->putItem(_originalShape);
   }
  }
  _shape->closeEditFrame();
 }
 if (_parent != NULL) {
     _parent->closeDrawFrame(this);
 }

 dispose();
}

/*public*/ void DrawFrame::stateChanged(ChangeEvent* e)
{
 colorChange();
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
/*private*/ void DrawFrame::widthChange()
{
    if (_shape==NULL) {
        return;
    }
    _lineWidth = _lineSlider->value();
    _shape->setLineWidth(_lineWidth);
    updateShape();
}

void DrawFrame::onLineColor()
{
 if(_lineColorButton->isChecked())
  _chooser->setColor(_lineColor);
}
void DrawFrame::onFillColor()
{
 if(_fillColorButton->isChecked())
  _chooser->setColor(_fillColor);
}

/*protected*/ void DrawFrame::updateShape() {
    _shape->removeHandles();
    _shape->makeShape();
    _shape->drawHandles();
    _shape->updateSize();
    //_shape->getEditor().getTargetPanel().repaint();
    _shape->_itemGroup->update();
;
}

// these 2 methods update the JTextfields when mouse moves handles
void DrawFrame::setDisplayWidth(int w) {
}

void DrawFrame::setDisplayHeight(int h) {
}

/*private*/ /*static*/ Logger* DrawFrame::log = LoggerFactory::getLogger("DrawFrame");
