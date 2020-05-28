#ifndef SIMPLECLOCKFRAME_H
#define SIMPLECLOCKFRAME_H
#include "jmrijframe.h"
#include "exceptions.h"
#include "liblayouteditor_global.h"
#include "focuslistener.h"
#include "jtextfield.h"

class PropertyChangeEvent;
class JLabel;
class QPushButton;
class JTextField;
class QCheckBox;
class QComboBox;
class DecimalFormat;
class Timebase;
class LIBLAYOUTEDITORSHARED_EXPORT SimpleClockFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit SimpleClockFrame(QWidget *parent = 0);
    ~SimpleClockFrame();
    /*public*/ void initComponents() throw (Exception);
    /*public*/ QString getClassName();

signals:

public slots:
    /*public*/ void setRateButtonActionPerformed();
    /*public*/ void setTimeButtonActionPerformed();
    /*public*/ void startButtonActionPerformed();
    /*public*/ void stopButtonActionPerformed();
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
 enum START
 {
  START_RUNNING = 0,
  START_STOPPED = 1,
  START_NORUNCHANGE = 2
};

    /*private*/ Timebase* clock;
    /*private*/ QString hardwareName = nullptr;
    //private boolean synchronize = true;
    //private boolean correct = true;
    /*private*/ bool changed;// = false;
    DecimalFormat* threeDigits;// = new DecimalFormat("0.000");	// 3 digit precision for speedup factor
    /*private*/ int internalSourceIndex;// = 0;
    /*private*/ int hardwareSourceIndex;// = 1;

    /*private*/ int startNone = 0;
    /*private*/ int startNixieClock = 1;
    /*private*/ int startAnalogClock = 2;
    /*private*/ int startLcdClock = 3;
    /*private*/ int startPragotronClock = 4 ;

    Logger* log;
    void setTimeLabel();
    void closeEvent(QCloseEvent *);
    void updateRate();
    /*private*/ void startSetRateChanged();
    void updateRunningButton();
    /*private*/ void startFactorFieldChanged();

private slots:
    /*private*/ void setTimeSourceChanged();
    /*private*/ void synchronizeChanged();
    /*private*/ void correctChanged();
    /*private*/ void displayChanged();
    /*private*/ void startStoppedChanged();
    /*private*/ void startSetTimeChanged();
    void updateTime();
    /*private*/ void setClockStartChanged();
    /*private*/ void startRunBoxChanged();
    /*private*/ void showStopButtonChanged();

protected:
    /*protected*/ bool showTime;// = false;
    /*protected*/ QComboBox* timeSourceBox = nullptr;
    /*protected*/ QComboBox* clockStartBox = nullptr;
    /*protected*/ QComboBox* startRunBox = nullptr;

    /*protected*/ QCheckBox* synchronizeCheckBox = nullptr;
    /*protected*/ QCheckBox* correctCheckBox = nullptr;
    /*protected*/ QCheckBox* displayCheckBox = nullptr;
    /*protected*/ QCheckBox* showStartupCheckBox = nullptr;
    /*protected*/ QCheckBox* startStoppedCheckBox = nullptr;
    /*protected*/ QCheckBox* startSetTimeCheckBox = nullptr;
    /*protected*/ QCheckBox* startSetRateCheckBox = nullptr;
    /*protected*/ QCheckBox* displayStartStopButton = nullptr;

    /*protected*/ JTextField* factorField;// = new JTextField(5);
    /*protected*/ JTextField* startFactorField = new JTextField(5);
    /*protected*/ JTextField* hoursField;// = new JTextField(2);
    /*protected*/ JTextField* minutesField;// = new JTextField(2);
    /*protected*/ JTextField* startHoursField;// = new JTextField(2);
    /*protected*/ JTextField* startMinutesField;// = new JTextField(2);

    /*protected*/ QPushButton* setRateButton;// = new QPushButton(tr("ButtonSet"));
    /*protected*/ QPushButton* setTimeButton;// = new QPushButtonn(tr("ButtonSet"));
    /*protected*/ QPushButton* startButton;// = new QPushButton(tr("ButtonStart"));
    /*protected*/ QPushButton* stopButton;// = new QPushButton(tr("ButtonStop"));
    /*protected*/ QPushButton* setStartTimeButton;// = new QPushButton(tr("ButtonSet"));

    /*protected*/ JLabel* clockStatus;// = new JLabel();
    /*protected*/ JLabel* timeLabel;// = new JLabel();

    friend class SCFFocusListener;
};

class SCFFocusListener : public FocusListener
{
  Q_OBJECT
  SimpleClockFrame* frame;
 public:
  SCFFocusListener(SimpleClockFrame* frame) {this->frame = frame;}
     /*public*/ void focusLost(FocusEvent* focusEvent) {
//         if (!focusEvent->isTemporary())
         {
             frame->startFactorFieldChanged();
         }
         //super.focusLost(focusEvent);
     }

 };
#endif // SIMPLECLOCKFRAME_H
