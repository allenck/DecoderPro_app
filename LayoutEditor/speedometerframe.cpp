#include "speedometerframe.h"
#include "fileutil.h"
#include "sensoricon.h"
#include "jtextfield.h"
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include "instancemanager.h"
#include "namedbeanhandlemanager.h"
#include <QButtonGroup>
#include <QBoxLayout>
#include "paneleditor.h"
#include "file.h"
#include "sensoricon.h"
#include "QApplication"
#include "abstractsensor.h"
#include <QDateTime>
#include <QMessageBox>

//SpeedometerFrame::SpeedometerFrame(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
/**
 * Frame providing access to a speedometer.
 * <P>
 * This contains very simple debouncing logic:
 * <UL>
 * <LI>The clock starts when the "start" sensor makes the correct transition.
 * <LI>When a "stop" sensor makes the correct transition, the speed is computed
 * and displayed.
 * </UL>
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2004, 2007
 * @author Adapted for metric system - S.K. Bosch
 * @author Matthew Harris Copyright (c) 2011
 * @version	$Revision: 28771 $
 */
///*public*/ class SpeedometerFrame extends jmri.util.JmriJFrame {

/**
 *
 */
///*public*/ static final long serialVersionUID = -8321031366797967218L;

/**
 *
 * @param d1 First timer distance in current units. Express with the decimal
 *           marker in the current Locale.
 * @param d2 Second timer distance in current units. Express with the
 *           decimal marker in the current Locale.
 */
/*public*/ void SpeedometerFrame::setInputs(QString start, QString stop1, QString stop2, QString d1, QString d2)
{
 startSensor->setText(start);
 stopSensor1->setText(stop1);
 stopSensor2->setText(stop2);
 distance1->setText(d1);
 distance2->setText(d2);
}

/*public*/ /*final*/ void SpeedometerFrame::setInputBehavior(bool startOnEntry, bool stopOnEntry1, bool stopOnEntry2)
{
 this->startOnEntry->setChecked(startOnEntry);
 this->startOnExit->setChecked(!startOnEntry);
 this->stopOnEntry1->setChecked(stopOnEntry1);
 this->stopOnExit1->setChecked(!stopOnEntry1);
 this->stopOnEntry2->setChecked(stopOnEntry2);
 this->stopOnExit2->setChecked(!stopOnEntry2);
}

/*public*/ /*final*/ void SpeedometerFrame::setUnitsMetric(bool metric)
{
 if (_dim != metric)
 {
  dim();
 }
}

/*public*/ SpeedometerFrame::SpeedometerFrame(QWidget *parent) :
  JmriJFrame(parent)
{
 //super(false, false);
 /*final*/ QString blank = "       ";
 startSensor = new JTextField(5);
 startGroup = new QButtonGroup();
 startOnEntry = new QRadioButton(tr("entry"));
 startOnExit = new QRadioButton(tr("exit"));

 stopSensor1 = new JTextField(5);
 stopGroup1 = new QButtonGroup();
 stopOnEntry1 = new QRadioButton(tr("entry"));
 stopOnExit1 = new QRadioButton(tr("exit"));

 stopSensor2 = new JTextField(5);
 stopGroup2 = new QButtonGroup();
 stopOnEntry2 = new QRadioButton(tr("entry"));
 stopOnExit2 = new QRadioButton(tr("exit"));

 distance1 = new JTextField(5);
 distance2 = new JTextField(5);

 dimButton = new QPushButton("");   // content will be set to English during startup
 startButton = new QPushButton(tr("Start"));

 text1 = new QLabel(tr("Distance 1 (scale feet):"));
 text2 = new QLabel(tr("Distance 2 (scale feet):"));
 text3 = new QLabel(tr("Timer 1 Speed (scale MPH):"));
 text4 = new QLabel(tr("Timer 2 Speed (scale MPH):"));

 clearButton = new QPushButton(tr("Clear"));

 result1 = new QLabel(blank);
 time1 = new QLabel(blank);
 result2 = new QLabel(blank);
 time2 = new QLabel(blank);

 saveButton = new QPushButton(tr("Save"));
 //Install the named bean handle if not installed, which can happen if opened from DP3
 if (InstanceManager::getDefault("NamedBeanHandleManager") == NULL)
 {
  InstanceManager::store(new NamedBeanHandleManager(), "NamedBeanHandleManager");
 }
 startTime = 0;
 stopTime1 = 0;
 stopTime2 = 0;
 log = new Logger("SpeedometerFrame");

 setInputBehavior(true, true, true);

 startGroup->addButton(startOnEntry);
 startGroup->addButton(startOnExit);
 stopGroup1->addButton(stopOnEntry1);
 stopGroup1->addButton(stopOnExit1);
 stopGroup2->addButton(stopOnEntry2);
 stopGroup2->addButton(stopOnExit2);

 // general GUI config
 setTitle(tr("Speedometer"));
 //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget();
 QVBoxLayout* thisLayout = new QVBoxLayout(centralWidget);
 setCentralWidget(centralWidget);

 // need a captive panel editor for
 // the sensor icons to work
 PanelEditor* editor = new PanelEditor();
//    editor->makePrivateWindow();
 editor->setVisible(false);

 // add items to GUI
 //JPanel pane1 = new JPanel();
 FlowLayout* pane1Layout = new FlowLayout();
 //pane1.setLayout(new FlowLayout());
 pane1Layout->addWidget(new QLabel(tr("Sensor")));
 startSensor->setToolTip(tr("Number of sensor starting the timer"));
 pane1Layout->addWidget(startSensor);
 pane1Layout->addWidget(new QLabel(tr("starts timers on")));
 pane1Layout->addWidget(startOnEntry);
 pane1Layout->addWidget(startOnExit);
 startSensorIcon = new SensorIcon(editor);
 setupIconMap(startSensorIcon);
 startSensorIcon->setToolTip(tr("Shows sensor state; click to change"));
 pane1Layout->addWidget(startSensorIcon);
 thisLayout->addLayout(pane1Layout);

 //JPanel pane2 = new JPanel();
 //pane2.setLayout(new FlowLayout());
 FlowLayout* pane2Layout = new FlowLayout();
 pane2Layout->addWidget(new QLabel(tr("Sensor")));
 stopSensor1->setToolTip(tr("Number of sensor ending the 1st timer"));
 pane2Layout->addWidget(stopSensor1);
 pane2Layout->addWidget(new QLabel(tr("stops timer 1 on")));
 pane2Layout->addWidget(stopOnEntry1);
 pane2Layout->addWidget(stopOnExit1);
 stopSensorIcon1 = new SensorIcon(editor);
 setupIconMap(stopSensorIcon1);
 stopSensorIcon1->setToolTip(tr("Shows sensor state; click to change"));
 pane2Layout->addWidget(stopSensorIcon1);
 thisLayout->addLayout(pane2Layout);

//    JPanel pane3 = new JPanel();
//    pane3.setLayout(new FlowLayout());
 FlowLayout* pane3Layout = new FlowLayout();
 pane3Layout->addWidget(new QLabel(tr("Sensor")));
 stopSensor2->setToolTip(tr("Number of sensor ending the 2nd timer"));
 pane3Layout->addWidget(stopSensor2);
 pane3Layout->addWidget(new QLabel(tr("stops timer 2 on")));
 pane3Layout->addWidget(stopOnEntry2);
 pane3Layout->addWidget(stopOnExit2);
 stopSensorIcon2 = new SensorIcon(editor);
 setupIconMap(stopSensorIcon2);
 stopSensorIcon2->setToolTip(tr("Shows sensor state; click to change"));
 pane3Layout->addWidget(stopSensorIcon2);
 thisLayout->addLayout(pane3Layout);

//    JPanel pane4 = new JPanel();
//    pane4.setLayout(new FlowLayout());
 FlowLayout* pane4Layout = new FlowLayout();
 pane4Layout->addWidget(text1);
 pane4Layout->addWidget(distance1);
 thisLayout->addLayout(pane4Layout);

//    JPanel pane5 = new JPanel();
//    pane5.setLayout(new FlowLayout());
 FlowLayout* pane5Layout = new FlowLayout();
 pane5Layout->addWidget(text2);
 pane5Layout->addWidget(distance2);
 thisLayout->addLayout(pane5Layout);

//    JPanel buttons = new JPanel();
 FlowLayout* buttonsLayout = new FlowLayout();
 buttonsLayout->addWidget(dimButton);
 dimButton->setToolTip(tr("Use this to choose between English and Metric"));
 buttonsLayout->addWidget(startButton);
 buttonsLayout->addWidget(clearButton);
 buttonsLayout->addWidget(saveButton);
 thisLayout->addLayout(buttonsLayout);

 clearButton->setVisible(false);

 // see if there's a sensor manager, if not disable
 if (NULL == InstanceManager::sensorManagerInstance())
 {
  startButton->setEnabled(false);
  startButton->setToolTip(tr("Sensors are not supported with this DCC connection"));
 }

//    JPanel pane6 = new JPanel();
//    pane6.setLayout(new FlowLayout());
 FlowLayout* pane6Layout = new FlowLayout();
 pane6Layout->addWidget(text3);
 pane6Layout->addWidget(result1);
 pane6Layout->addWidget(new QLabel(tr(" Time (seconds):")));
 pane6Layout->addWidget(time1);
 thisLayout->addLayout(pane6Layout);

//    JPanel pane7 = new JPanel();
//    pane7.setLayout(new FlowLayout());
 FlowLayout* pane7Layout = new FlowLayout();
 pane7Layout->addWidget(text4);
 pane7Layout->addWidget(result2);
 pane7Layout->addWidget(new QLabel(tr(" Time (seconds):")));
 pane7Layout->addWidget(time2);
 thisLayout->addLayout(pane7Layout);

 // set the units consistently
 dim();

 // add the actions to the config button
//    dimButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            dim();
//        }
//    });
 connect(dimButton, SIGNAL(clicked()), this, SLOT(dim()));
//    startButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            setup();
//        }
//    });
 connect(startButton, SIGNAL(clicked()), this, SLOT(setup()));

//    clearButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            time1->setText(blank);
//            time2->setText(blank);
//            result1->setText(blank);
//            result2->setText(blank);
//        }
//    });
 connect(clearButton, SIGNAL(clicked()), this, SLOT(on_clearButton_clicked()));

//    saveButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            doStore();
//        }
//    });
 connect(saveButton, SIGNAL(clicked()), this, SLOT(doStore()));

 // start displaying the sensor status when the number is entered
//    startSensor.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            startSensorIcon.setSensor(startSensor.getText());
//        }
//    });
 connect(startSensor, SIGNAL(editingFinished()), this, SLOT(on_startSensor()));

//    stopSensor1.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            stopSensorIcon1.setSensor(stopSensor1.getText());
//        }
//    });
 connect(stopSensor1, SIGNAL(editingFinished()), this, SLOT(on_stopSensor1()));


//    stopSensor2.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            stopSensorIcon2.setSensor(stopSensor2.getText());
//        }
//    });
 connect(stopSensor2, SIGNAL(editingFinished()), this, SLOT(on_stopSensor2()));

 // add help menu to window
 addHelpMenu("package.jmri.jmrit.speedometer.SpeedometerFrame", true);

 // and get ready to display
 adjustSize();

 // finally, load any previously saved defaults
 doLoad();
}

void SpeedometerFrame::on_clearButton_clicked()
{
 time1->setText(blank);
 time2->setText(blank);
 result1->setText(blank);
 result2->setText(blank);

 enableConfiguration(true);
}

void SpeedometerFrame::on_startSensor()
{
 startSensorIcon->setSensor(startSensor->text());
 Sensor* s = startSensorIcon->getSensor();
 if(s != NULL)
 {
  log->debug(tr("start sensor set to %1").arg(s->getDisplayName()));
  connect(((AbstractSensor*)s)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(startSensor_propertyChange(PropertyChangeEvent*)));
 }
}

void SpeedometerFrame::startSensor_propertyChange(PropertyChangeEvent *)
{
 Sensor* s = startSensorIcon->getSensor();
 int iState = s->getState();
 NamedIcon* icon = startSensorIcon->getIcon(iState);
 startSensorIcon->displayState(iState);
 ((JLabel*)startSensorIcon)->setIcon(icon);
 update();
}

void SpeedometerFrame::on_stopSensor1()
{
 stopSensorIcon1->setSensor(stopSensor1->text());
 Sensor* s = stopSensorIcon1->getSensor();
 if(s != NULL)
 {
  log->debug(tr("stop sensor 1 set to %1").arg(s->getDisplayName()));
  connect(((AbstractSensor*)s)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(stopSensor1_propertyChange(PropertyChangeEvent*)));
 }
}

void SpeedometerFrame::stopSensor1_propertyChange(PropertyChangeEvent *)
{
 Sensor* s = stopSensorIcon1->getSensor();
 int iState = s->getState();
 NamedIcon* icon = stopSensorIcon1->getIcon(iState);
 stopSensorIcon1->displayState(iState);
 ((JLabel*)stopSensorIcon1)->setIcon(icon);
 update();
}

void SpeedometerFrame::on_stopSensor2()
{
 stopSensorIcon2->setSensor(stopSensor2->text());
 Sensor* s = stopSensorIcon2->getSensor();
 if(s != NULL)
 {
  log->debug(tr("stop sensor 2 set to %1").arg(s->getDisplayName()));
  connect(((AbstractSensor*)s)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(stopSensor2_propertyChange(PropertyChangeEvent*)));
 }
}

void SpeedometerFrame::stopSensor2_propertyChange(PropertyChangeEvent *)
{
 Sensor* s = stopSensorIcon2->getSensor();
 int iState = s->getState();
 NamedIcon* icon = stopSensorIcon2->getIcon(iState);
 stopSensorIcon2->displayState(iState);
 ((JLabel*)stopSensorIcon2)->setIcon(icon);
 update();
}

// establish whether English or Metric representation is wanted
/*final*/ void SpeedometerFrame::dim()
{
 dimButton->setEnabled(true);
 if (dimButton->text()==(tr("To Metric units")))
 {
  dimButton->setText(tr("To English units"));
  _dim = true;
  text1->setText(tr("Distance 1 (scale cm):"));
  text2->setText(tr("Distance 2 (scale cm):"));
  text3->setText(tr("Timer 1 Speed (scale KMH):"));
  text4->setText(tr("Timer 2 Speed (scale KMH):"));
 }
 else
 {
  dimButton->setText(tr("To Metric units"));
  _dim = false;
  text1->setText(tr("Distance 1 (scale feet):"));
  text2->setText(tr("Distance 2 (scale feet):"));
  text3->setText(tr("Timer 1 Speed (scale MPH):"));
  text4->setText(tr("Timer 2 Speed (scale MPH):"));
 }
}

/*public*/ void SpeedometerFrame::setup()
{
    //startButton.setToolTipText("You can only configure this once");

 // Check inputs are valid and get the number of valid stop sensors
 int valid = verifyInputs(true);
 if (log->isDebugEnabled()) {
     log->debug("Number of valid stop sensors: " + valid);
 }
 enableConfiguration(valid == 0);
 if (valid == 0) {
     return;
 }

 // set start sensor
 Sensor* s;
 s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
         provideSensor(startSensor->text());
//    s->addPropertyChangeListener(new PropertyChangeListener() {
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//            SpeedometerFrame.log->debug("start sensor fired");
//            if (e.getPropertyName()==("KnownState")) {
//                int now = ((Integer) e.getNewValue()).intValue();
//                if ((now == Sensor.ACTIVE && startOnEntry->isChecked())
//                        || (now == Sensor.INACTIVE && startOnExit->isChecked())) {
//                    startTime = System.currentTimeMillis();  // milliseconds
//                    if (log->isDebugEnabled()) {
//                        log->debug("set start " + startTime);
//                    }
//                }
//            }
//        }
//    });
 AbstractSensor* as = (AbstractSensor*)s;
 connect(as->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 startSensorIcon->setSensor(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(startSensor->text(), s));

 // set stop sensor1
 s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
         provideSensor(stopSensor1->text());
//    s->addPropertyChangeListener(new PropertyChangeListener()
//    {
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//            SpeedometerFrame.log->debug("stop sensor fired");
//            if (e.getPropertyName()==("KnownState")) {
//                int now = ((Integer) e.getNewValue()).intValue();
//                if ((now == Sensor.ACTIVE && stopOnEntry1->isChecked())
//                        || (now == Sensor.INACTIVE && stopOnExit1->isChecked())) {
//                    stopTime1 = System.currentTimeMillis();  // milliseconds
//                    if (log->isDebugEnabled()) {
//                        log->debug("set stop " + stopTime1);
//                    }
//                    // calculate and show speed
//                    float secs = (stopTime1 - startTime) / 1000.f;
//                    float feet = 0.0f;
//                    try {
//                        feet = IntlUtilities.floatValue(distance1.getText());
//                    } catch (java.text.ParseException ex) {
//                        log->error("invalid floating point number as input: " + distance1.getText());
//                    }
//                    float speed;
//                    if (dim == false) {
//                        speed = (feet / 5280.f) * (3600.f / secs);
//                    } else {
//                        speed = (feet / 100000.f) * (3600.f / secs);
//                    }
//                    if (log->isDebugEnabled()) {
//                        log->debug("calc from " + secs + "," + feet + ":" + speed);
//                    }
//                    result1->setText(String.valueOf(speed).substring(0, 4));
//                    String time = String.valueOf(secs);
//                    int offset = time.indexOf(".");
//                    if (offset == -1) {
//                        offset = time.length();
//                    }
//                    offset = offset + 2;  // the decimal point, plus tenths digit
//                    if (offset > time.length()) {
//                        offset = time.length();
//                    }
//                    time1->setText(time.substring(0, offset));
//                }
//            }
//        }
//    });
 as = (AbstractSensor*)s;
 connect(as->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange1(PropertyChangeEvent*)));
 stopSensorIcon1->setSensor(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(stopSensor1->text(), s));

 if (valid == 1) {
     return;
 }

 // set stop sensor2
 s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
         provideSensor(stopSensor2->text());
//    s.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
//        // handle change in stop sensor
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//            SpeedometerFrame.log->debug("stop sensor fired");
//            if (e.getPropertyName()==("KnownState")) {
//                int now = ((Integer) e.getNewValue()).intValue();
//                if ((now == Sensor.ACTIVE && stopOnEntry2->isChecked())
//                        || (now == Sensor.INACTIVE && stopOnExit2->isChecked())) {
//                    stopTime2 = System.currentTimeMillis();  // milliseconds
//                    if (log->isDebugEnabled()) {
//                        log->debug("set stop " + stopTime2);
//                    }
//                    // calculate and show speed
//                    float secs = (stopTime2 - startTime) / 1000.f;
//                    float feet = 0.0f;
//                    try {
//                        feet = IntlUtilities.floatValue(distance2.getText());
//                    } catch (java.text.ParseException ex) {
//                        log->error("invalid floating point number as input: " + distance2.getText());
//                    }
//                    float speed;
//                    if (dim == false) {
//                        speed = (feet / 5280.f) * (3600.f / secs);
//                    } else {
//                        speed = (feet / 100000.f) * (3600.f / secs);
//                    }
//                    if (log->isDebugEnabled()) {
//                        log->debug("calc from " + secs + "," + feet + ":" + speed);
//                    }
//                    result2->setText(String.valueOf(speed).substring(0, 4));
//                    String time = String.valueOf(secs);
//                    int offset = time.indexOf(".");
//                    if (offset == -1) {
//                        offset = time.length();
//                    }
//                    offset = offset + 2;  // the decimal point, plus tenths digit
//                    if (offset > time.length()) {
//                        offset = time.length();
//                    }
//                    time2->setText(time.substring(0, offset));
//                }
//            }
//        }
//    });
 as = (AbstractSensor*)s;
 connect(as->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange2(PropertyChangeEvent*)));

 NamedBeanHandle<Sensor*>* namedSensor2 = ((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(stopSensor2->text(), s);
 stopSensorIcon2->setSensor(namedSensor2);
}

/*public*/ void SpeedometerFrame::propertyChange(PropertyChangeEvent* e)
{
    log->debug("start sensor fired");
    if (e->getPropertyName()==("KnownState")) {
        int now =  e->getNewValue().toInt();
        if ((now == Sensor::ACTIVE && startOnEntry->isChecked())
                || (now == Sensor::INACTIVE && startOnExit->isChecked())) {
            startTime = /*System.currentTimeMillis()*/QDateTime::currentMSecsSinceEpoch();  // milliseconds
            if (log->isDebugEnabled()) {
                log->debug("set start " + QString::number(startTime));
            }
        }
    }
}

/*public*/ void SpeedometerFrame::propertyChange1(PropertyChangeEvent* e) {
    log->debug("stop sensor fired");
    if (e->getPropertyName()==("KnownState")) {
        int now =  e->getNewValue().toInt();
        if ((now == Sensor::ACTIVE && stopOnEntry1->isChecked())
                || (now == Sensor::INACTIVE && stopOnExit1->isChecked())) {
            stopTime1 = /*System.currentTimeMillis()*/QDateTime::currentMSecsSinceEpoch();  // milliseconds
            if (log->isDebugEnabled()) {
                log->debug("set stop " + stopTime1);
            }
            // calculate and show speed
            float secs = (stopTime1 - startTime) / 1000.f;
            float feet = 0.0f;
//            try {
            bool bOk;
                feet = distance1->text().toFloat(&bOk);
                if(!bOk){
                log->error("invalid floating point number as input: " + distance1->text());
            }
            float speed;
            if (_dim == false) {
                speed = (feet / 5280.f) * (3600.f / secs);
            } else {
                speed = (feet / 100000.f) * (3600.f / secs);
            }
            if (log->isDebugEnabled()) {
                log->debug("calc from " + QString::number(secs) + "," + QString::number(feet) + ":" + QString::number(speed));
            }
            result1->setText(QString::number(speed).mid(0, 4));
            QString time = QString::number(secs);
            int offset = time.indexOf(".");
            if (offset == -1) {
                offset = time.length();
            }
            offset = offset + 2;  // the decimal point, plus tenths digit
            if (offset > time.length()) {
                offset = time.length();
            }
            time1->setText(time.mid(0, offset));
        }
    }
}

/*public*/ void SpeedometerFrame::propertyChange2(PropertyChangeEvent* e) {
    log->debug("stop sensor fired");
    if (e->getPropertyName()==("KnownState")) {
        int now = e->getNewValue().toInt();
        if ((now == Sensor::ACTIVE && stopOnEntry2->isChecked())
                || (now == Sensor::INACTIVE && stopOnExit2->isChecked())) {
            stopTime2 = QDateTime::currentMSecsSinceEpoch();  // milliseconds
            if (log->isDebugEnabled()) {
                log->debug("set stop " + stopTime2);
            }
            // calculate and show speed
            float secs = (stopTime2 - startTime) / 1000.f;
            float feet = 0.0f;
            bool bOk;
                feet = distance2->text().toFloat(&bOk);
                if(!bOk) {
                log->error("invalid floating point number as input: " + distance2->text());
            }
            float speed;
            if (_dim == false) {
                speed = (feet / 5280.f) * (3600.f / secs);
            } else {
                speed = (feet / 100000.f) * (3600.f / secs);
            }
            if (log->isDebugEnabled()) {
                log->debug("calc from " + QString::number(secs) + "," + QString::number(feet) + ":" + QString::number(speed));
            }
            result2->setText(QString::number(speed).mid(0, 4));
            QString time = QString::number(secs);
            int offset = time.indexOf(".");
            if (offset == -1) {
                offset = time.length();
            }
            offset = offset + 2;  // the decimal point, plus tenths digit
            if (offset > time.length()) {
                offset = time.length();
            }
            time2->setText(time.mid(0, offset));
        }
    }
}


/*public*/ void SpeedometerFrame::enableConfiguration(bool enable) {
    // Buttons first
    startButton->setEnabled(enable);
    startButton->setVisible(enable);
    clearButton->setEnabled(!enable);
    clearButton->setVisible(!enable);
    saveButton->setEnabled(enable);

    // Now Start sensor
    startSensor->setEnabled(enable);
    startOnEntry->setEnabled(enable);
    startOnExit->setEnabled(enable);

    // Now Stop sensor 1
    stopSensor1->setEnabled(enable);
    stopOnEntry1->setEnabled(enable);
    stopOnExit1->setEnabled(enable);

    // Now Stop sensor 2
    stopSensor2->setEnabled(enable);
    stopOnEntry2->setEnabled(enable);
    stopOnExit2->setEnabled(enable);

    // Finally, distances
    distance1->setEnabled(enable);
    distance2->setEnabled(enable);
    dimButton->setEnabled(enable);
}

/**
 * Verifies if correct inputs have been made and returns the number of valid
 * stop sensors.
 *
 * @param warn true if warning messages to be displayed
 * @return 0 if not verified; otherwise the number of valid stop sensors
 *         defined
 */
/*public*/ int SpeedometerFrame::verifyInputs(bool warn)
{

    // Initially, no stop sensors are valid
    int verify = 0;

    Sensor* s;

    // Check the start sensor
    try {
        s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                provideSensor(startSensor->text());
        if (s == NULL) {
            throw new Exception();
        }
    } catch (Exception e) {
        // couldn't locate the sensor, that's an error
        log->error("Start sensor invalid: " + startSensor->text());
        if (warn) {
//            JOptionPane.showMessageDialog(
//                    this,
//                    tr("ErrorStartSensor"),
//                    tr("TitleError"),
//                    JOptionPane.WARNING_MESSAGE);
         QMessageBox::critical(this, tr("Error"), tr("Start Sensor not valid - please re-enter"));
        }
        return verify;
    }

    // Check stop sensor 1
    try {
        s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                provideSensor(stopSensor1->text());
        if (s == NULL) {
            throw new Exception();
        }
    } catch (Exception e) {
        // couldn't locate the sensor, that's an error
        log->error("Stop 1 sensor invalid : " + stopSensor1->text());
        if (warn) {
//            JOptionPane.showMessageDialog(
//                    this,
//                    tr("ErrorStopSensor1"),
//                    tr("TitleError"),
//                    JOptionPane.WARNING_MESSAGE);
         QMessageBox::critical(this, tr("Error"), tr("Stop Sensor 1 not valid - please re-enter"));
        }
        return verify;
    }

    // Check distance1 has been defined
    if (distance1->text()==("")) {
        log->error("Distance 1 has not been defined");
        if (warn) {
//            JOptionPane.showMessageDialog(
//                    this,
//                    tr("ErrorDistance1"),
//                    tr("TitleError"),
//                    JOptionPane.WARNING_MESSAGE);
         QMessageBox::critical(this, tr("Error"), tr("Distance 1 has not been defined - please re-enter"));
        }
        return verify;
    }

    // We've got this far, so at least start and one stop sensor is valid
    verify = 1;

    // Check stop sensor2 if either sensor 2 and/or distance 2 defined
    if (stopSensor2->text()!=("") || distance2->text()!=("")) {
        try {
            s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                    provideSensor(stopSensor2->text());
            if (s == NULL) {
                throw new Exception();
            }
        } catch (Exception e) {
            // couldn't locate the sensor, that's an error
            log->error("Stop 2 sensor invalid: " + stopSensor2->text());
            if (warn) {
//                JOptionPane.showMessageDialog(
//                        this,
//                        tr("ErrorStopSensor2"),
//                        tr("TitleError"),
//                        JOptionPane.WARNING_MESSAGE);
             QMessageBox::warning(this, tr("Error"), tr("Stop Sensor 2 not valid - please re-enter"));
            }
            return 0;
        }

        // Check distance2 has been defined
        if (distance2->text()==("")) {
            log->error("Distance 2 has not been defined");
            enableConfiguration(true);
            if (warn) {
//                JOptionPane.showMessageDialog(
//                        this,
//                        tr("ErrorDistance2"),
//                        tr("TitleError"),
//                        JOptionPane.WARNING_MESSAGE);
             QMessageBox::critical(this, tr("Error"), tr("Distance 2 has not been defined - please re-enter"));
            }
            return 0;
        }

        // We've got this far, so stop sensor 2 is valid
        verify = 2;
    }
    return verify;
}
#if 1
/*public*/ void SpeedometerFrame::doStore()
{
 log->debug("Check if there's anything to store");
 int verify = verifyInputs(false);
 if (verify == 0) {
//        if (JOptionPane.showConfirmDialog(
//                this,
//                tr("QuestionNothingToStore"),
//                tr("TitleStoreQuestion"),
//                JOptionPane.YES_NO_OPTION,
//                JOptionPane.QUESTION_MESSAGE) == JOptionPane.NO_OPTION) {
  if(QMessageBox::question(this, tr("Store these settings?"), tr("The current settings are either blank or invalid.\n Do you wish to store them anyway?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
  {
   return;
  }
 }
 log->debug("Start storing speedometer settings...");

 SpeedometerXml* x = new SpeedometerXml();

 x->makeBackupFile(SpeedometerXml::getDefaultFileName());

 File* file = x->getFile(true);

 // Create root element
 QDomDocument doc = QDomDocument();
 QDomElement root = doc.createElement("speedometer-config");
//    root.setAttribute("noNamespaceSchemaLocation",
//            "http://jmri.org/xml/schema/speedometer-3-9-3.xsd",
//            org.jdom2.Namespace.getNamespace("xsi",
//                    "http://www.w3.org/2001/XMLSchema-instance"));
 root.setAttribute("xsi:noNamespaceSchemaLocation",
         "http://jmri.org/xml/schema/speedometer-3-9-3.xsd");
 root.setAttribute("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");

 //Document doc = new Document(root);

 // add XSLT processing instruction
//    QMap<QString, QString> m = QMap<QString, QString>();
//    m.insert("type", "text/xsl");
//    m.insert("href", SpeedometerXml::xsltLocation + "speedometer.xsl");
 QDomProcessingInstruction p =  doc.createProcessingInstruction("xml-stylesheet", QString("type=\"text/xsl\" href=\"%1").arg(SpeedometerXml::xsltLocation + "speedometer.xsl\""));
 doc.appendChild( p);
 doc.appendChild(root);

 QDomElement values;

 // Store configuration
 root.appendChild(values = doc.createElement("configuration"));
 QDomElement e = doc.createElement("useMetric");
 e.appendChild( doc.createTextNode(_dim ? "yes" : "no"));
 values.appendChild(e);

 // Store values
 if (verify > 0 || startSensor->text().length() > 0)
 {
  // Create sensors element
  root.appendChild(values = doc.createElement("sensors"));

  // Store start sensor
  QDomElement e = doc.createElement("sensor");
  QDomElement e1 =  doc.createElement("sensorName");
  e1.appendChild(doc.createTextNode(startSensor->text()));
  e.appendChild(e1);
  QDomElement e2 = doc.createElement("type");
  e2.appendChild(doc.createTextNode("StartSensor"));
  e.appendChild(e2);
  QDomElement e3 = doc.createElement("trigger");
  e3.appendChild(doc.createElement(startOnEntry->isChecked() ? "entry" : "exit"));
  e.appendChild(e3);
  values.appendChild(e);

  // If valid, store stop sensor 1
  if (verify > 0)
  {
   e = doc.createElement("sensor");
   QDomElement e1 = doc.createElement("sensorName");
   e1.appendChild(doc.createTextNode(stopSensor1->text()));
   e.appendChild(e1);
   QDomElement e2 = doc.createElement("type");
   e2.appendChild(doc.createTextNode("StopSensor1"));
   e.appendChild(e2);
   QDomElement e3 = doc.createElement("trigger");
     e3.appendChild(doc.createTextNode(stopOnEntry1->isChecked() ? "entry" : "exit"));
   e.appendChild(e3);
   // try {
   QDomElement e4 = doc.createElement("distance");
   e4.appendChild(doc.createTextNode(distance1->text()));
       e.appendChild(e4);
//            } catch (ParseException ex) {
//                log->error("Distance isn't a valid floating number: " + distance1.getText());
//            }
   values.appendChild(e);
  }

  // If valid, store stop sensor 2
  if (verify > 1)
  {
   e = doc.createElement("sensor");
   QDomElement e1 = doc.createElement("sensorName");
   e1.appendChild(doc.createTextNode(stopSensor2->text()));
   e.appendChild(e1);
   QDomElement e2 = doc.createElement("type");
   e2.appendChild(doc.createTextNode("StopSensor2"));
   e.appendChild(e2);
   QDomElement e3 = doc.createElement("trigger");
   e3.appendChild(doc.createTextNode(stopOnEntry2->isChecked() ? "entry" : "exit"));
   e.appendChild(e3);
   //try {
   QDomElement e4 = doc.createElement("distance");
   e4.appendChild(doc.createTextNode(distance2->text()));
       e.appendChild(e4);
//            } catch (java.text.ParseException ex) {
//                log->error("Distance isn't a valid floating number: " + distance2.getText());
//            }
   values.appendChild(e);
  }
 }
 try
 {
  x->writeXML(file, doc);
 }
 catch (FileNotFoundException ex)
 {
  log->error("File not found when writing: " + ex.getMessage());
 } catch (IOException ex)
 {
  log->error("IO Exception when writing: " + ex.getMessage());
 }

 log->debug("...done");
}
#endif

/*public*/ void SpeedometerFrame::doLoad()
{
 log->debug("Check if there's anything to load");
 SpeedometerXml* x = new SpeedometerXml();
 File* file = x->getFile(false);

 if (file == NULL) {
     log->debug("Nothing to load");
     return;
 }

 log->debug("Start loading speedometer settings...");

 // Find root
 QDomElement root;
 if(!file->exists()) return;
 try
 {
  root = x->rootFromFile(file);
  if ( root == QDomElement())
  {
   log->debug("File could not be read");
   return;
  }

  // First read configuration
  if (root.firstChildElement("configuration") != QDomElement())
  {
   //@SuppressWarnings("unchecked")
   QDomNodeList l = root.firstChildElement("configuration").childNodes();
   if (log->isDebugEnabled()) {
       log->debug("readFile sees " + QString::number(l.size()) + " configurations");
   }
   for (int i = 0; i < l.size(); i++)
   {
    QDomElement e = l.at(i).toElement();
    if (log->isDebugEnabled())
    {
     log->debug("Configuration " + e.tagName() + " value " + e.text());
    }
    if (e.tagName()==("useMetric"))
    {
     setUnitsMetric(e.text()==("yes") ? true : false);
    }
   }
  }
  // Now read sensor information
  if (root.firstChildElement("sensors") != QDomElement())
  {
   // @SuppressWarnings("unchecked")
   QDomNodeList l = root.firstChildElement("sensors").elementsByTagName("sensor");
   if (log->isDebugEnabled())
   {
    log->debug("readFile sees " + QString::number(l.size()) + " sensors");
   }
   for (int i = 0; i < l.size(); i++)
   {
    QDomElement e = l.at(i).toElement();
    QString sensorType = e.firstChildElement("type").text();
    if (sensorType==("StartSensor"))
    {
     startSensor->setText(e.firstChildElement("sensorName").text());
     bool trigger = e.firstChildElement("trigger").text()==("entry");
     startOnEntry->setChecked(trigger);
     startOnExit->setChecked(!trigger);
     on_startSensor();
    }
    else if (sensorType==("StopSensor1"))
    {
     stopSensor1->setText(e.firstChildElement("sensorName").text());
     bool trigger = e.firstChildElement("trigger").text()==("entry");
     stopOnEntry1->setChecked(trigger);
     stopOnExit1->setChecked(!trigger);
     distance1->setText(e.firstChildElement("distance").text());
     on_stopSensor1();
    }
    else if (sensorType==("StopSensor2"))
    {
     stopSensor2->setText(e.firstChildElement("sensorName").text());
     bool trigger = e.firstChildElement("trigger").text()==("entry");
     stopOnEntry2->setChecked(trigger);
     stopOnExit2->setChecked(!trigger);
     distance2->setText(e.firstChildElement("distance").text());
     on_stopSensor2();
    }
    else
    {
     log->warn("Unknown sensor type: " + sensorType);
    }
   }
  }
 } catch (JDOMException ex) {
     log->error("File invalid: " + ex.getMessage());
 } catch (IOException ex) {
     log->error("Error reading file: " + ex.getMessage());
 }

 log->debug("...done");
}

/*public*/ void SpeedometerFrame::setupIconMap(SensorIcon* sensor)
{
 sensor->setIcon("SensorStateActive",
         new NamedIcon(":/resources/icons/smallschematics/tracksegments/circuit-occupied.gif",
                 "resources/icons/smallschematics/tracksegments/circuit-occupied.gif"));
 sensor->setIcon("SensorStateInactive",
         new NamedIcon(":/resources/icons/smallschematics/tracksegments/circuit-empty.gif",
                 "resources/icons/smallschematics/tracksegments/circuit-empty.gif"));
 sensor->setIcon("BeanStateInconsistent",
         new NamedIcon(":/resources/icons/smallschematics/tracksegments/circuit-error.gif",
                 "resources/icons/smallschematics/tracksegments/circuit-error.gif"));
 sensor->setIcon("BeanStateUnknown",
         new NamedIcon(":/resources/icons/smallschematics/tracksegments/circuit-error.gif",
                 "resources/icons/smallschematics/tracksegments/circuit-error.gif"));
}

///*public*/ static class SpeedometerXml extends XmlFile {

    /*public*/ /*static*/ QString SpeedometerXml::getDefaultFileName() {
        return getFileLocation() + getFileName();
    }

    /*public*/ File* SpeedometerXml::getFile(bool store) {
        QFile* file = findFile(getDefaultFileName());
        if (file == NULL && store) {
            file = new QFile(getDefaultFileName());
        }
        QString path = getDefaultFileName();
        return new File(path);
    }

    /*public*/ /*static*/ QString SpeedometerXml::baseFileName = "Speedometer.xml";

    /*public*/ /*static*/ QString SpeedometerXml::getFileName() {
        return /*Application.getApplicationName()*/QApplication::applicationName() + baseFileName;
    }

    /**
     * Absolute path to location of Speedometer files.
     *
     * @return path to location
     */
    /*public*/ /*static*/ QString SpeedometerXml::getFileLocation() {
        return fileLocation;
    }

    /*public*/ /*static*/ QString SpeedometerXml::fileLocation = FileUtil::getUserFilesPath();

//};
/*public*/ QString SpeedometerFrame::getClassName()
{
 return "jmri.jmrit.speedometer.SpeedometerFrame";
}
