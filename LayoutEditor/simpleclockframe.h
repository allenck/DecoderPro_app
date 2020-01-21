#ifndef SIMPLECLOCKFRAME_H
#define SIMPLECLOCKFRAME_H
#include "jmrijframe.h"
#include "exceptions.h"
#include "liblayouteditor_global.h"

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
    /*private*/ Timebase* clock;
    /*private*/ QString hardwareName;// = null;
    //private boolean synchronize = true;
    //private boolean correct = true;
    /*private*/ bool changed;// = false;
    DecimalFormat* threeDigits;// = new DecimalFormat("0.000");	// 3 digit precision for speedup factor
    /*private*/ int internalSourceIndex;// = 0;
    /*private*/ int hardwareSourceIndex;// = 1;

    /*private*/ int startNone;// = 0;
    /*private*/ int startNixieClock;// = 1;
    /*private*/ int startAnalogClock;// = 2;
    /*private*/ int startLcdClock;// = 3;
    Logger* log;
    void setTimeLabel();
    void closeEvent(QCloseEvent *);
    void updateRate();
    void updateRunningButton();

private slots:
    /*private*/ void setTimeSourceChanged();
    /*private*/ void synchronizeChanged();
    /*private*/ void correctChanged();
    /*private*/ void displayChanged();
    /*private*/ void startStoppedChanged();
    /*private*/ void startSetTimeChanged();
    void updateTime();
    /*private*/ void setClockStartChanged();

protected:
    /*protected*/ bool showTime;// = false;
    /*protected*/ QComboBox* timeSourceBox;// = NULL;
    /*protected*/ QComboBox* clockStartBox;// = NULL;

    /*protected*/ QCheckBox* synchronizeCheckBox;// = NULL;
    /*protected*/ QCheckBox* correctCheckBox;// = NULL;
    /*protected*/ QCheckBox* displayCheckBox;// = NULL;
    /*protected*/ QCheckBox* showStartupCheckBox;// = NULL;
    /*protected*/ QCheckBox* startStoppedCheckBox;// = NULL;
    /*protected*/ QCheckBox* startSetTimeCheckBox;// = NULL;

    /*protected*/ JTextField* factorField;// = new JTextField(5);
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

};

#endif // SIMPLECLOCKFRAME_H
