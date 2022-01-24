#include "abstractaudioframe.h"
#include "jtextfield.h"
#include <QLabel>
#include "audio.h"
#include <QSlider>
#include <QBoxLayout>
#include "flowlayout.h"
#include "jtextfield.h"
#include <QDoubleSpinBox>
#include <QVector3D>
#include "abstractaudio.h"
#include <QScrollArea>
#include "jslider.h"
#include "joptionpane.h"


//AbstractAudioFrame::AbstractAudioFrame(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
/**
 * Abstract GUI to edit Audio objects
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Matthew Harris copyright (c) 2009
 * @version $Revision: 28746 $
 */
//abstract /*public*/ class AbstractAudioFrame extends JmriJFrame {

/**
 *
 */
//    private static final long serialVersionUID = 8799988277074614855L;
//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");
//    static final ResourceBundle rba = ResourceBundle.getBundle("jmri.jmrit.audio.swing.AudioTableBundle");


/*static*/ /*final*/ int AbstractAudioFrame::INT_PRECISION = (int) qPow(10, Audio::DECIMAL_PLACES);
/*static*/ /*final*/ float AbstractAudioFrame::FLT_PRECISION = 1 / (float) AbstractAudioFrame::INT_PRECISION;

/**
 * Standard constructor
 *
 * @param title Title of this AudioFrame
 * @param model AudioTableDataModel holding Audio data
 */
/*public*/ AbstractAudioFrame::AbstractAudioFrame(QString title, AudioTableDataModel* model, QWidget *parent) : JmriJFrame(title, parent)
{
 //super(title);
 frame = this;
 // Common UI components for Add/Edit Audio
 sysNameLabel = new QLabel(tr("System Name"));
 sysName = new JTextField(5);
 userNameLabel = new QLabel(tr("User Name"));
 userName = new JTextField(15);
 main = new QWidget();
 scroll = new QScrollArea();

 this->model = model;
}

/**
 * Method to layout the frame.
 * <p>
 * This contains common items.
 * <p>
 * Sub-classes will override this method and provide additional GUI items.
 */
/*public*/ void AbstractAudioFrame::layoutFrame()
{
 frame->addHelpMenu("package.jmri.jmrit.beantable.AudioAddEdit", true);
 QVBoxLayout* frameLayout;
 frame->getContentPane()->setLayout(frameLayout = new QVBoxLayout);// (frame.getContentPane(), BoxLayout.Y_AXIS));
 main->setLayout(mainLayout = new QVBoxLayout);//(main, BoxLayout.Y_AXIS));

 QWidget* p;

 p = new QWidget();
 FlowLayout* pLayout;
 p->setLayout(pLayout = new FlowLayout());
 pLayout->addWidget(sysNameLabel);
 pLayout->addWidget(sysName);
 //frame.getContentPane().add(p);
 QVBoxLayout* centralWidgetLayout;
 if(frame->centralWidget() == NULL)
 {
  QWidget* centralWidget = new QWidget;
  centralWidget->setLayout(centralWidgetLayout = new QVBoxLayout);
 }
 else
  centralWidgetLayout = (QVBoxLayout*)centralWidget()->layout();
 centralWidgetLayout->addWidget(p);
 p = new QWidget();
 p->setLayout(pLayout= new FlowLayout());
 pLayout->addWidget(userNameLabel);
 pLayout->addWidget(userName);
 //frame.getContentPane().add(p);
 centralWidgetLayout->addWidget(p);

 frameLayout->addWidget(scroll);
 QWidget* scrollWidget = new QWidget;
 scrollWidget->setLayout(scrollLayout = new QVBoxLayout);
 scroll->setWidget(scrollWidget);
 scroll->setWidgetResizable(true);
}

/**
 * Method to populate the Audio frame with default values
 */
/*abstract*/ /*public*/ void AbstractAudioFrame::resetFrame() {}

/**
 * Method to populate the Audio frame with current values
 */
/*public*/ void AbstractAudioFrame::populateFrame(Audio* a) {
    sysName->setText(a->getSystemName());
    userName->setText(a->getUserName());
}

/**
 * Check System Name user input.
 *
 * @param entry string retrieved from text field
 * @param counter index of all similar (Source/Buffer) items
 * @param prefix (AudioListener/Source/Buffer) system name prefix string to compare entry against
 * @return true if prefix doesn't match
 */
/*protected*/ bool AbstractAudioFrame::entryError(QString entry, QString prefix, QString counter) {
    if (!entry.startsWith(prefix)) {
        JOptionPane::showMessageDialog(nullptr, tr("System Name entered should start with ''%1''.").arg(prefix),
                tr("Error creating Audio object"), JOptionPane::ERROR_MESSAGE);
        sysName->setText(prefix + counter);
        return true;
    }
    return false;
}

//private static final Logger log = LoggerFactory.getLogger(AbstractAudioFrame.class.getName());
/**
 * A convenience class to create a JPanel to edit a Vector3f object using 3
 * seperate QSpinBox Swing objects
 */
//protected static class JPanelVector3f extends JPanel {

/**
 *
 */
//private static final long serialVersionUID = -2102431744610108951L;

JPanelVector3f::JPanelVector3f(QWidget* parent)
 : QGroupBox(parent)
{
 //super();
 common();
 layoutPanel("", "");
}

JPanelVector3f::JPanelVector3f(QString title,QWidget* parent)
: QGroupBox(title, parent)
{
 //super();
 common();
 layoutPanel(title, "");
}

JPanelVector3f::JPanelVector3f(QString title, QString units, QWidget* parent)
 : QGroupBox(title, parent)
{
 //super();
 common();
 layoutPanel(title, units);
}

void JPanelVector3f::common()
{
 xLabel = new QLabel(tr("X"));
 xValue = new QSpinBox();
 yLabel = new QLabel(tr("Y"));
 yValue = new QSpinBox();
 zLabel = new QLabel(tr("Z"));
 zValue = new QSpinBox();
 unitsLabel = new QLabel();
 QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
 this->setStyleSheet(gbStyleSheet);
}

/*private*/ void JPanelVector3f::layoutPanel(QString title, QString units)
{
 FlowLayout* thisLayout;
 this->setLayout(thisLayout = new FlowLayout());
 if (title.length() != 0)
 {
//        this->setBorder(BorderFactory.createCompoundBorder(
//                BorderFactory.createTitledBorder(title),
//                BorderFactory.createEmptyBorder(5, 5, 5, 5)));
  setTitle(title);
 }
 thisLayout->addWidget(xLabel);
 xValue->setMinimumSize(JTextField(8).getPreferredSize());
// xValue.setModel(
//            new SpinnerNumberModel(0.0, -Audio::MAX_DISTANCE, Audio::MAX_DISTANCE, new FLT_PRECISION));
 xValue->setRange(-Audio::MAX_DISTANCE, Audio::MAX_DISTANCE);
 xValue->setValue(0);
 //xValue.setEditor(new QSpinBox.NumberEditor(xValue, "0.00"));
 thisLayout->addWidget(xValue);

 thisLayout->addWidget(yLabel);
 yValue->setMinimumSize(JTextField(8).getPreferredSize());
// yValue.setModel( new SpinnerNumberModel(new Float(0f), new Float(-Audio::MAX_DISTANCE), new Float(Audio::MAX_DISTANCE), new Float(FLT_PRECISION)));
 //yValue.setEditor(new QSpinBox.NumberEditor(yValue, "0.00"));
 thisLayout->addWidget(yValue);

 thisLayout->addWidget(zLabel);
 zValue->setMinimumSize(JTextField(8).getPreferredSize());
 //zValue.setModel( new SpinnerNumberModel(new Float(0f), new Float(-Audio::MAX_DISTANCE), new Float(Audio::MAX_DISTANCE), new Float(FLT_PRECISION)));
 zValue->setRange(-Audio::MAX_DISTANCE, Audio::MAX_DISTANCE);
 zValue->setValue(0);
 //zValue.setEditor(new QSpinBox.NumberEditor(zValue, "0.00"));
 thisLayout->addWidget(zValue);

 if (units.length() != 0)
 {
  unitsLabel->setText(units);
  thisLayout->addWidget(unitsLabel);
 }
}

/**
 * Set the value of this object
 *
 * @param value value to set
 */
/*public*/ void JPanelVector3f::setValue(QVector3D value) {
 xValue->setValue(value.x());
 yValue->setValue(value.y());
 zValue->setValue(value.z());
}

/**
 * Retrieve the current value of this object
 *
 * @return current value
 */
/*public*/ QVector3D JPanelVector3f::getValue()
{
 return  QVector3D(
         AbstractAudio::roundDecimal( xValue->value()),
         AbstractAudio::roundDecimal( yValue->value()),
         AbstractAudio::roundDecimal( zValue->value()));
}

QDoubleSlider::QDoubleSlider(QWidget *parent)
{
 slider = new JSlider();
 slider->setOrientation(Qt::Horizontal);
 slider->setMinimum(0);
 slider->setMaximum(100);
 connect(slider, SIGNAL(valueChanged(int)), this, SLOT(on_slider_valueChanged(int)));
 slider->setTickInterval(10);
 slider->setTickPosition(QSlider::TicksBelow);
 QVBoxLayout* thisLayout = new QVBoxLayout;
 thisLayout->addWidget(slider);
 setLayout(thisLayout);
}
void QDoubleSlider::setMinimum(double min)
{
 slider->setMinimum((int)(min*100));
}
void QDoubleSlider::setMaximum(double max)
{
 slider->setMaximum((int)max*100);
}
void QDoubleSlider::setValue(double val)
{
 slider->setValue((int)val * 100);
}
void QDoubleSlider::on_slider_valueChanged(int val)
{
 emit valueChanged(val/100.0);
}
double QDoubleSlider::value()
{
 return slider->value()/100.0;
}

/**
* A convenience class to create a JPanel for editing a float value using
* combined JSlider and JSPinner Swing objects
*/
// /*protected*/ /*static*/ class JPanelSliderf extends JPanel {

/**
 *
 */
// private static final long serialVersionUID = -7201712611650896844L;

JPanelSliderf::JPanelSliderf(QString title, float min, float max, int majorTicks, int minorTicks)
{
 //super();
 FlowLayout* thisLayout = NULL;
 if(layout() == NULL)
 {
  thisLayout = new FlowLayout;
  setLayout(thisLayout);
 }
 else
  thisLayout = (FlowLayout*)layout();
 slider = new QDoubleSlider();
 spinner = new QDoubleSpinBox();

 int iMin = qRound(min * AbstractAudioFrame::INT_PRECISION);
 int iMax = qRound(max * AbstractAudioFrame::INT_PRECISION);
 int iInterval = (iMax - iMin) / majorTicks;

 //this->setLayout(new FlowLayout());
// this->setBorder(BorderFactory.createCompoundBorder(
//         BorderFactory.createTitledBorder(title),
//         BorderFactory.createEmptyBorder(5, 5, 5, 5)));
 this->setTitle(title);
 slider->setMinimum(qRound(min * AbstractAudioFrame::INT_PRECISION));
 slider->setMaximum(qRound(max * AbstractAudioFrame::INT_PRECISION));
// slider->setMajorTickSpacing(iInterval);
// slider->setMinorTickSpacing(iInterval / minorTicks);
// @SuppressWarnings("UseOfObsoleteCollectionType")
 // Need to use Hashtable for JSlider labels
 QHash<int, QLabel*> labelTable =  QHash<int, QLabel*>();
 for (int i = iMin; i <= iMax; i += iInterval)
 {
  float f = i;
  f /= AbstractAudioFrame::INT_PRECISION;
  labelTable.insert(i, new QLabel(QString::number(f)));
 }
// slider->setLabelTable(labelTable);
// slider->setPaintTicks(true);
// slider->setPaintLabels(true);
//    slider.addChangeListener(new ChangeListener() {
//        @Override
//        /*public*/ void stateChanged(ChangeEvent e) {
//            float f = slider.getValue();
//            f /= INT_PRECISION;
//            spinner.setValue(f);
//        }
//    });
 connect(slider, SIGNAL(valueChanged(double)), this, SLOT(On_sliderValueChanged()));
 spinner->setMinimumSize(JTextField(5).getPreferredSize());
// spinner.setModel(
//            new SpinnerNumberModel(min, min, max, new Float(FLT_PRECISION)));
 spinner->setMinimum(min);
 spinner->setValue(min);
 spinner->setMaximum(max);
 spinner->setSingleStep((max-min)/100);
// spinner->setEditor(new QSpinBox.NumberEditor(spinner, "0.00"));
//    spinner.addChangeListener(new ChangeListener() {
//        @Override
//        /*public*/ void stateChanged(ChangeEvent e) {
//            slider.setValue(
//                    Math.round((Float) spinner.getValue() * INT_PRECISION));
//        }
//    });
 connect(spinner, SIGNAL(valueChanged(double)), this, SLOT(On_spinner_valueChanged()));
 thisLayout->addWidget(slider);
 thisLayout->addWidget(spinner);
}

void JPanelSliderf::On_spinner_valueChanged()
{
 slider->setValue(qRound( (float)spinner->value() * AbstractAudioFrame::INT_PRECISION));
}
void JPanelSliderf::On_sliderValueChanged()
{
 float f = slider->value();
 f /= AbstractAudioFrame::INT_PRECISION;
 spinner->setValue(f);
}

/**
 * Set the value of this object
 *
 * @param value value to set
 */
/*public*/ void JPanelSliderf::setValue(float value)
{
 spinner->setValue(value);
}

/**
 * Retrieve the current value of this object
 *
 * @return current value
 */
/*public*/ float JPanelSliderf::getValue()
{
 return AbstractAudio::roundDecimal(spinner->value());
}
//};
