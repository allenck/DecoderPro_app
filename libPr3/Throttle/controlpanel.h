#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QDockWidget>
#include "logger.h"
#include <QTime>
#include <QtXml>
#include <QMenu>
#include <QFrame>
#include "addresslistener.h"
#include "jcombobox.h"
#include "spinnernumbermodel.h"
#include "gridbagconstraints.h"
#include "jpanel.h"
#include "gridbaglayout.h"
#include "jspinner.h"
#include "speedstepmode.h"
#include <QAbstractButton>

class RosterEntry;
class ThrottlesPreferences;
class MySlider;
class JSlider;
class AddressPanel;
class LocoAddress;
class QButtonGroup;
class ButtonFrame;
class NamedIcon;
class QPushButton;
class JLabel;
class PropertyChangeEvent;
class QSlider;
class QSpinBox;
class QRadioButton;
class DccThrottle;
class ControlPanel : public QDockWidget, public AddressListener
{
    Q_OBJECT
 Q_INTERFACES(AddressListener)
public:
    //explicit ControlPanel(QWidget *parent = 0);
    /*public*/ ControlPanel(QWidget *parent = 0);
    /*public*/ void setAddressPanel(AddressPanel* addressPanel);
    /*public*/  ~ControlPanel();
    /*public*/ void destroy();
    /*public*/ void dispose();
    /*public*/ void setEnabled(bool isEnabled);
    /*public*/ void setSpeedController(int displaySlider);
    /*public*/ void setSpeedValues(float speedIncrement, float speed);
    /*public*/ void accelerate1();
    /*public*/ void accelerate10();
    /*public*/ void decelerate1();
    /*public*/ void decelerate10();
    /*public*/ QDomElement getXml();
    /*public*/ void setXml(QDomElement e);
    /*public*/ QWidget* getContentPane() {return widget();}
    /*public*/ void setForwardDirection(bool fwd);
    /*public*/ JSlider* getSpeedSlider();
    /*public*/ JSlider* getSpeedSliderContinuous();
    /*public*/ void toFront() { raise();}

 enum SPEEDS
 {
  /* Constants for speed selection method */
   SLIDERDISPLAY = 0,
   STEPDISPLAY = 1,
   SLIDERDISPLAYCONTINUOUS = 2
 };
 /*public*/ QString getSwitchSliderFunction();
 /*public*/ void setSwitchSliderFunction(QString fn);
 /*public*/ bool isSpeedControllerAvailable(int displaySlider);
 /*final*/ /*public*/ static int BUTTON_SIZE;// = 40;
 /*public*/ bool isEnabled();
 /*public*/ int getDisplaySlider();
 /*public*/ void setTrackSlider(bool track);
 /*public*/ bool getTrackSlider();
 QObject* self() {return (QObject*)this;}
 /*public*/ void saveToRoster(RosterEntry* re);

signals:

public slots:
 /*public*/ void notifyAddressChosen(LocoAddress* l);
 /*public*/ void notifyAddressReleased(LocoAddress* la);
 /*public*/ void notifyAddressThrottleFound(DccThrottle* t);
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 /*public*/ void notifyConsistAddressChosen(int newAddress, bool isLong);
 /*public*/ void notifyConsistAddressReleased(int address, bool isLong);
 /*public*/ void notifyConsistAddressThrottleFound(DccThrottle* throttle);
 /*public*/ void actionPerformed(/*ActionEvent e*/);

private:
    /*private*/ QWidget* mainPanel;
    /*private*/ JSlider* speedSlider;
    /*private*/ JSlider* speedSliderContinuous;
    /*private*/ JSpinner* speedSpinner;
    /*private*/ SpinnerNumberModel* speedSpinnerModel;
    /*private*/ JComboBox/*<SpeedStepMode>*/* speedStepBox;
//    /*private*/ QRadioButton* speedStep128Button;
//    /*private*/ QRadioButton* speedStep28Button;
//    /*private*/ QRadioButton* speedStep27Button;
//    /*private*/ QRadioButton* speedStep14Button;
    /*private*/ QRadioButton *forwardButton, *reverseButton;
    /*private*/ QPushButton* stopButton;
    /*private*/ QPushButton* idleButton;
    SpeedStepMode* speedStepMode;
    /*private*/ QFrame* speedControlPanel;
    /*private*/	QWidget* spinnerPanel;
    GridBagLayout* spinnerPanelLayout;
    /*private*/	QFrame* sliderPanel;
    GridBagLayout* sliderPanelLayout;
    /*private*/ QWidget* speedSliderContinuousPanel;
    GridBagLayout* speedSliderContinuousPanelLayout;
    ButtonFrame* buttonFrame;
    /*private*/ AddressPanel* addressPanel; //for access to roster entry

    /*private*/ int _displaySlider;// = SLIDERDISPLAY;
    /*private*/ bool _emergencyStop;// = false;

    /*private*/ DccThrottle* _throttle = nullptr;
    /*private*/ JPanel* buttonPanel = nullptr;
    /*private*/ JPanel* topButtonPanel = nullptr;
    /*private*/ bool internalAdjust;// = false;

    // LocoNet really only has 126 speed steps i.e. 0..127 - 1 for em stop
    /*private*/ int MAX_SPEED;// = 126;
    static Logger* log;
    /*private*/ void initGUI();
    /*private*/ void speedSetting(float speed);
//    /*private*/ void configureAvailableSpeedStepModes();
    /*private*/ GridBagConstraints makeDefaultGridBagConstraints();
    /*private*/ void layoutTopButtonPanel();
    GridBagLayout* topButtonPanelLayout;
    /*private*/ void layoutButtonPanel();
    /*private*/ void layoutSliderPanel();
    /*private*/ void layoutSpeedSliderContinuous();
    /*private*/ void layoutSpinnerPanel();
    /*private*/ void setupButton(QAbstractButton *button, /*final*/ ThrottlesPreferences* preferences, /*final*/ QString iconPath,
            /*final*/ QString selectedIconPath, /*final*/ QString message);
    /*private*/ void changeOrientation();

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
    /*private*/ void setSpeedStepsMode(SpeedStepMode::SSMODES speedStepMode);
    QMenu* propertiesPopup;
    /*private*/ void setIsForward(bool isForward);
    GridBagLayout* buttonPanelLayout = nullptr;
    void resizeEvent(QResizeEvent*);

private slots:
    void OnSpeedSliderChanged(int);
    void speedSliderContinuousChanged(int);
    void OnSpinnerChanged(int);
    void OnSpeedStep14();
    void OnSpeedStep28();
    void OnSpeedStep27();
    void OnSpeedStep128();
    void forwardButtonClicked();
    void reverseButtonClicked();
    void stop();
    void idleButtonClicked();
    void on_editProperties();
    void on_menu_requested();

    friend class ControlPanelTest;
};
#if 0
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
#endif

#endif // CONTROLPANEL_H
