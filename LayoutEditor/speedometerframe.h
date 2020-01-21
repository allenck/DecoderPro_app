#ifndef SPEEDOMETERFRAME_H
#define SPEEDOMETERFRAME_H
#include "jmrijframe.h"
#include "xmlfile.h"

class SensorIcon;
class QLabel;
class QPushButton;
class QRadioButton;
class QButtonGroup;
class JTextField;
class SpeedometerFrame : public JmriJFrame
{
 Q_OBJECT
public:
 explicit SpeedometerFrame(QWidget *parent = 0);
 /*public*/ void setInputs(QString start, QString stop1, QString stop2, QString d1, QString d2);
 /*public*/ /*final*/ void setInputBehavior(bool startOnEntry, bool stopOnEntry1, bool stopOnEntry2) ;
 /*public*/ /*final*/ void setUnitsMetric(bool metric);
 /*public*/ void doLoad();
 /*public*/ void setupIconMap(SensorIcon* sensor);
 /*public*/ JTextField* stopSensor2; // newJTextField(5);
 /*public*/ void enableConfiguration(bool enable);
 /*public*/ int verifyInputs(bool warn);
 /*public*/ QString getClassName();

public slots:
 void on_clearButton_clicked();
 /*public*/ void setup();
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 /*public*/ void propertyChange1(PropertyChangeEvent* e);
 /*public*/ void propertyChange2(PropertyChangeEvent* e);
 /*public*/ void doStore();

signals:

private:
 /*final*/ QString blank;// = "       ";
 JTextField* startSensor; // newJTextField(5);
 QButtonGroup* startGroup; // newQButtonGroup();
 QRadioButton* startOnEntry; // newQRadioButton(Bundle.getMessage("RadioButtonEntry"));
 QRadioButton* startOnExit; // newQRadioButton(Bundle.getMessage("RadioButtonExit"));
 
 JTextField* stopSensor1; // newJTextField(5);
 QButtonGroup* stopGroup1; // newQButtonGroup();
 QRadioButton* stopOnEntry1; // newQRadioButton(Bundle.getMessage("RadioButtonEntry"));
 QRadioButton* stopOnExit1; // newQRadioButton(Bundle.getMessage("RadioButtonExit"));
 
 QButtonGroup* stopGroup2; // newQButtonGroup();
 QRadioButton* stopOnEntry2; // newQRadioButton(Bundle.getMessage("RadioButtonEntry"));
 QRadioButton* stopOnExit2; // newQRadioButton(Bundle.getMessage("RadioButtonExit"));
 
 JTextField* distance1; // newJTextField(5);
 JTextField* distance2; // newJTextField(5);
 
 QPushButton* dimButton; // newQPushButton("");   // content will be set to English during startup
 QPushButton* startButton; // newQPushButton(Bundle.getMessage("ButtonStart"));
 
 QLabel* text1; // newQLabel(Bundle.getMessage("Distance1English"));
 QLabel* text2; // newQLabel(Bundle.getMessage("Distance2English"));
 QLabel* text3; // newQLabel(Bundle.getMessage("Speed1English"));
 QLabel* text4; // newQLabel(Bundle.getMessage("Speed2English"));
 
 QPushButton* clearButton; // newQPushButton(Bundle.getMessage("ButtonClear"));
 
 QLabel* result1; // newQLabel(blank);
 QLabel* time1; // newQLabel(blank);
 QLabel* result2; // newQLabel(blank);
 QLabel* time2; // newQLabel(blank);
 
 QPushButton* saveButton; // newQPushButton(Bundle.getMessage("ButtonSave"));
 
 SensorIcon* startSensorIcon;
 SensorIcon* stopSensorIcon1;
 SensorIcon* stopSensorIcon2;
 qint64 startTime;// = 0;
 qint64 stopTime1;// = 0;
 qint64 stopTime2;// = 0;
 Logger* log;

 /**
  * "Distance Is Metric": If true, metric distances are being used.
  */
 bool _dim;
private slots:
 /*final*/ void dim();
 void on_startSensor();
 void on_stopSensor1();
 void on_stopSensor2();
 void startSensor_propertyChange(PropertyChangeEvent*);
 void stopSensor1_propertyChange(PropertyChangeEvent*);
 void stopSensor2_propertyChange(PropertyChangeEvent*);
};
/*public*/ /*static*/ class SpeedometerXml : public XmlFile
{
 Q_OBJECT
public:
    /*public*/ static QString getDefaultFileName();
    /*public*/ File* getFile(bool store);
    /*public*/ static QString baseFileName;// = "Speedometer.xml";
    /*public*/ static QString getFileName();
    /*public*/ static QString getFileLocation() ;
    /*public*/ static QString fileLocation;// = FileUtil::getUserFilesPath();

};
#endif // SPEEDOMETERFRAME_H
