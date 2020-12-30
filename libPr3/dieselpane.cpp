#include "dieselpane.h"
#include "eventlistenerlist.h"
#include <QSlider>
#include "jtogglebutton.h"
#include <QVariant>
#include <QGridLayout>
#include "propertychangeevent.h"

//DieselPane::DieselPane(QWidget *parent) :
//  EnginePane(parent)
//{
//}
//@SuppressWarnings("serial")
//class DieselPane extends EnginePane {


/*public*/ DieselPane::DieselPane(QString n,QWidget *parent) :
EnginePane(n, parent) {
    //super(n);
    initComponents();
    throttle_setting = throttle_slider->value();
    engine_started = start_button->isSelected();
}

/*public*/ DieselPane::DieselPane(QWidget *parent) :
EnginePane(parent) {
    //this(null);
}

/*public*/ void DieselPane::initContext(QVariant context) {
    initComponents();
}

/*public*/ void DieselPane::initComponents() {
    //listenerList = new EventListenerList();

    //this->setLayout(new GridLayout(2, 0));
QGridLayout* g = new QGridLayout(this);

    //Setup the throttle slider.
    throttle_slider = new QSlider(Qt::Horizontal); //(JSlider.HORIZONTAL, THROTTLE_MIN,
    throttle_slider->setMaximum(THROTTLE_MAX);
    throttle_slider->setMinimum(THROTTLE_MIN);
    throttle_slider->setValue(THROTTLE_INIT);
    //throttle_slider.setMajorTickSpacing(1);
    //throttle_slider.setPaintTicks(true);
    throttle_slider->setMinimumSize(QSize(400, 0));
    //throttle_slider.setSnapToTicks(true);
//        throttle_slider.addChangeListener(new ChangeListener() {
//            /*public*/ void stateChanged(ChangeEvent e) {
//                throttleChange(e);
//            }
//        });
    connect(throttle_slider, SIGNAL(valueChanged(int)), this, SLOT(throttleChange()));
    g->addWidget(throttle_slider, 0,0/*,0,0*/);

    // Setup the start button
    start_button = new JToggleButton();
    start_button->setText("Engine Start");
//        start_button.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                startButtonChange(e);
//            }
//        });
    connect(start_button, SIGNAL(clicked()), this, SLOT(startButtonChange()));
    g->addWidget(start_button, 0, 1/*, 0, 0*/);
    throttle_slider->setVisible(true);
    start_button->setVisible(true);
    this->setVisible(true);
    //this.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));
}

/*public*/ void DieselPane::throttleChange(ChangeEvent* e)
{
    firePropertyChangeEvent(new PropertyChangeEvent(this, "throttle",
            throttle_setting,
            throttle_slider->value()));
    throttle_setting = throttle_slider->value();
}

/*public*/ void DieselPane::startButtonChange(JActionEvent* /*e*/) {
    firePropertyChangeEvent(new PropertyChangeEvent(this, "start",
            engine_started,
            start_button->isSelected()));
    engine_started = start_button->isSelected();
}

/*public*/ bool DieselPane::engineIsOn() {
    return (start_button->isSelected());
}

/*public*/ int DieselPane::throttleNotch() {
    return (throttle_slider->value());
}

/*public*/ void DieselPane::setThrottle(int t) {
    throttle_slider->setValue(t);
}
