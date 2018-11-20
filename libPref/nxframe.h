#ifndef NXFRAME_H
#define NXFRAME_H
#include "warrantroute.h"
#include "windowlistener.h"
#include "warrant.h"
#include "sleeperthread.h"
#include "libpref_global.h"

class WarrantPreferences;
class QVBoxLayout;
class QRadioButton;
class QCheckBox;
class LIBPREFSHARED_EXPORT NXFrame : public WarrantRoute
{
 Q_OBJECT
public:
 explicit NXFrame(QWidget *parent = 0);
 static /*public*/ NXFrame* getInstance();
 /*public*/ void setMaxSpeed(float s);
 /*public*/ float getMaxSpeed() ;
 /*public*/ void setTimeInterval(float s);
 /*public*/ void setRampIncrement(float throttleIncr);
 /*public*/ void setStartHalt(bool s);
 /*public*/ bool getStartHalt();
 /*public*/ void setScale(float s);
 /*public*/ float getScale();
 /*public*/ void init();
 /*public*/ void updatePanel(int interp);
 /*public*/ void selectedRoute(QList<BlockOrder*> orders);
 /*public*/ static float INCRE_RATE;// = 1.08f;  // multiplier to increase throttle increments

signals:

public slots:
 void on_runAuto();
 void on_runManual();
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 void onMaxSpeed();
 void onSpeedUnits();
 void onOriginUnits();
 void onDestUnits();

private:
 /*private*/ float _scale;// = 87.1f;

 JTextField* _trainName;// = new JTextField(6);
 JTextField* _maxSpeedBox;// = new JTextField(6);
 /*private*/ QPushButton* _speedUnits;
 JTextField* _minSpeedBox;// = new JTextField(6);
 /*private*/ /*final*/ JTextField* _originDist;// = new JTextField(6);
 /*private*/ QPushButton* _originUnits;
 /*private*/ /*final*/ JTextField* _destDist;// = new JTextField(6);
 /*private*/ QPushButton* _destUnits;
 QRadioButton* _forward;// = new JRadioButton();
 QRadioButton* _reverse;// = new JRadioButton();
 QCheckBox*  _stageEStop;// = new JCheckBox();
 QCheckBox*  _haltStartBox;// = new JCheckBox();
 QCheckBox*  _calibrateBox;// = new JCheckBox();
//    QCheckBox*  _addTracker = new JCheckBox();
 JTextField *_rampInterval;// = new JTextField(6);
 QRadioButton* _runAuto;// = new JRadioButton(Bundle.getMessage("RunAuto"));
 QRadioButton* _runManual;// = new JRadioButton(Bundle.getMessage("RunManual"));
 /*private*/ QWidget* _routePanel;// = new JPanel();
 /*private*/ QWidget* _autoRunPanel;
 /*private*/ /*final*/ QWidget*  __trainHolder;// = new JPanel();
 /*private*/ QWidget*  _switchPanel;
 /*private*/ QWidget*  _trainPanel;
 QWidget*      _manualPanel;
//  static boolean _addTracker = false;
 /*private*/ bool _haltStart;// = false;
 /*private*/ float _maxSpeed;// = 0.5f;
 /*private*/ float _minSpeed;// = 0.05f;
 /*private*/ float _intervalTime;// = 0.0f;     // milliseconds
 /*private*/ float _throttleIncr;// = 0.0f;
 /*private*/ float _maxThrottle;// = 0.75f;
 /*private*/ float _startDist;   // mm start distance to portal
 /*private*/ float _stopDist;    // mm stop distance from portal
 /*private*/ float _totalLen;    // route length of warrant

 /*private*/ /*final*/ JTextField* _maxThrottleBox;// = new JTextField(6);
 /*private*/ /*final*/ QCheckBox* _noRamp;// = new JCheckBox();
 /*private*/ /*final*/ QCheckBox* _shareRouteBox;// = new JCheckBox();

 /*private*/ static NXFrame* _instance;
 QVBoxLayout* controlPanelLayout;
 /*private*/ void makeMenus();
 /*private*/ QWidget* makeAutoRunPanel();
 /*private*/ QWidget* makeSwitchPanel();
 /*private*/ void enableAuto(bool enable);
 /*private*/ bool makeAndRunWarrant();
 /*private*/ void runManual();
 /*private*/ QString getBoxData();
 /*private*/ float getPathLength(BlockOrder* bo);
 /*private*/ float getTotalLength(float defaultBlockLen);
 /*private*/ QString getTotalLength();
 /*private*/ float getUpRampLength();
 /*private*/ float getDownRampLength();
 /*private*/ float getRampLength(float totalLen, RosterSpeedProfile* speedProfile);
 /*private*/ QString makeCommands(Warrant* w);
 /*private*/ QPushButton* getButton(QString text);
 /*private*/ WarrantPreferences* updatePreferences();

protected:
 /*protected*/ QWidget* _controlPanel;
 /*protected*/ void closeFrame();
 /*protected*/ void setThrottleIncrement(float increment);

 friend class NXWindowListener;
 friend class WarrantPreferences;
 friend class WarrantTableFrame;
};
class NXWindowListener : public WindowListener
{
 Q_OBJECT
 NXFrame* frame;
public:
 NXWindowListener(NXFrame* frame) {this->frame = frame;}
 void windowClosing(QCloseEvent */*e*/)
 {
  frame->closeFrame();
 }
};
class Halter : public  /*Runnable*/ QObject
{
 Q_OBJECT

    Warrant* war;
    NXFrame* frame;
public:
    Halter (Warrant* w, NXFrame* frame)
    {
     war = w;
     this->frame = frame;
    }
public slots:

    /*public*/ void process()
    {
     int limit = 0;
     try
     {
      // wait until _engineer is assigned so HALT can take effect
      while (!war->controlRunTrain(Warrant::HALT) && limit<3000)
      {
          //Thread.sleep(200);
       SleeperThread::msleep(200);
          limit += 200;
      }
     }
     catch (InterruptedException e)
     {
      war->controlRunTrain(Warrant::HALT);
     }
    }
signals:
    void finished();
};
#endif // NXFRAME_H
