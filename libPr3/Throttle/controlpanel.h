#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QDockWidget>
#include "logger.h"
#include <QTime>
#include <QtXml>

class QButtonGroup;
class ButtonFrame;
class NamedIcon;
class QPushButton;
class JLabel;
class PropertyChangeEvent;
class LearnThrottleFrame;
class QSlider;
class QSpinBox;
class QRadioButton;
class DccThrottle;
class ControlPanel : public QDockWidget
{
    Q_OBJECT
public:
    //explicit ControlPanel(QWidget *parent = 0);
    /*public*/ ControlPanel(LearnThrottleFrame* ltf, QWidget *parent);
    /*public*/ void dispose();
    /*public*/ void setEnabled(bool isEnabled);
    /*public*/ void setSpeedSteps(int steps);
    /*public*/ void setSpeedController(bool displaySlider);
    /*public*/ void setSpeedValues(int speedIncrement, int speed);
    /*public*/ void accelerate1();
    /*public*/ void accelerate10();
    /*public*/ void decelerate1();
    /*public*/ void decelerate10();
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement e);
 enum SPEEDS
 {
  /* Constants for speed selection method */
   SLIDERDISPLAY = 0,
   STEPDISPLAY = 1,
   SLIDERDISPLAYCONTINUOUS = 2
 };
 /*public*/ QString getSwitchSliderFunction();
 /*public*/ void setSwitchSliderFunction(QString fn);

signals:

public slots:
    /*public*/ void notifyThrottleFound(DccThrottle* t);
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
    /*private*/ LearnThrottleFrame* _throttleFrame;

    /*private*/ QSlider* speedSlider;
    /*private*/ QSpinBox* speedSpinner;
//    /*private*/ SpinnerNumberModel speedSpinnerModel;
    /*private*/ QRadioButton* SpeedStep128Button;
    /*private*/ QRadioButton* SpeedStep28Button;
    /*private*/ QRadioButton* SpeedStep27Button;
    /*private*/ QRadioButton* SpeedStep14Button;

    /*private*/ QWidget* speedControlPanel;
    /*private*/	QWidget* spinnerPanel;
    /*private*/	QWidget* sliderPanel;
    ButtonFrame* buttonFrame;

    /*private*/ bool _displaySlider;// = true;
    /*private*/ bool _emergencyStop;// = false;

    /*private*/ DccThrottle* _throttle;
    /*private*/ bool internalAdjust;// = false;

    // LocoNet really only has 126 speed steps i.e. 0..127 - 1 for em stop
    /*private*/ int MAX_SPEED;// = 126;
    Logger* log;
    /*private*/ void initGUI();
    /*private*/ void speedSetting(float speed);
    /*private*/ void configureAvailableSpeedStepModes();

    /*private*/ bool trackSlider;// = false;
    /*private*/ bool trackSliderDefault;// = false;
    /*private*/ long trackSliderMinInterval;// = 200;         // milliseconds
    /*private*/ long trackSliderMinIntervalDefault;// = 200;  // milliseconds
    /*private*/ long trackSliderMinIntervalMin;// = 50;       // milliseconds
    /*private*/ long trackSliderMinIntervalMax;// = 1000;     // milliseconds
    /*private*/ long lastTrackedSliderMovementTime;// = 0;
    // LocoNet really only has 126 speed steps i.e. 0..127 - 1 for em stop
    /*private*/ int intSpeedSteps;// = 126;

    /*private*/ int maxSpeed;// = 126; //The maximum permissible speed

    /*private*/ bool speedControllerEnable;// = false;

    // Switch to continuous slider on function...
    /*private*/ QString switchSliderFunction = "Fxx";
    /*private*/ QString prevShuntingFn = "";

private slots:
    void OnSliderChanged(int);
    void OnSpinnerChanged(int);
    void OnSpeedStep14();
    void OnSpeedStep28();
    void OnSpeedStep27();
    void OnSpeedStep128();
};
class ButtonFrame : public QWidget
{
 Q_OBJECT
    /*private*/ QRadioButton *forwardButton, *reverseButton;
    /*private*/ JLabel *forwardLight, *reverseLight, *stopLabel;
    /*private*/ QRadioButton *stopButton;
    /*private*/ int _gap;
    QButtonGroup* group;// = new QButtonGroup();

    /*private*/ void initGUI();
    DccThrottle* _throttle;
    NamedIcon* directionOffIcon;// = new NamedIcon("program:resources/icons/USS/sensor/amber-off.gif", "amber-off");
    NamedIcon* directionOnIcon;// = new NamedIcon("program:resources/icons/USS/sensor/amber-on.gif", "amber-on");
    NamedIcon* stopIcon;// = new NamedIcon("program:resources/icons/USS/sensor/red-on.gif", "red-on");
     static int STRUT_SIZE;// = 10;
public:
    ButtonFrame( QWidget* parent = 0);
    /*public*/ void setForwardDirection(bool isForward);
public slots:
    void OnForwardButton();
    void OnReverseButton();
    void stop();
    /*public*/ void notifyThrottleFound(DccThrottle* t);

};

#endif // CONTROLPANEL_H
