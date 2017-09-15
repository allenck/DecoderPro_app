#ifndef PYTHONWRAPPERS_H
#define PYTHONWRAPPERS_H

#include <QObject>
#if 0
#include "jframe.h"
#include <QBoxLayout>
#include "loconetmessage.h"
#include "lntrafficcontroller.h"
#include "instancemanager.h"
#include "loconetsystemconnectionmemo.h"
#include "warrantmanager.h"
#include "lnturnout.h"
#include "lnsensor.h"
#include "abstractautomaton.h"
#include "flowlayout.h"
#include "panelmenu.h"
#include "editor.h"
#include "jbutton.h"
#include "audiosource.h"
#include "audiobuffer.h"
#include "audiolistener.h"
#include "abstractaudiomanager.h"
#include "qtsoundaudiobuffer.h"
#include "dccthrottle.h"
#include "siglet.h"
#include "abstractshutdowntask.h"

// add a wrapper that allows to access the CustomObject from PythonQt
class JFrame_Wrapper : public QObject
{

  Q_OBJECT

public Q_SLOTS:
  // add a constructor
  JFrame* new_JFrame(const QString& title)
  {
   return new JFrame(title);
  }
  // add a destructor
  void delete_JFrame(JFrame* o) { delete o; }

  // add access methods
  QWidget* getContentPane(JFrame* o)
  {
   if(o->centralWidget() == NULL)
   {
    QWidget* centralWidget = new QWidget;
//    QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
//    centralWidget->setLayout(centralWidgetLayout);
    o->setCentralWidget(centralWidget);
   }
   return o->centralWidget();
  }

  QString title(JFrame* o) { return o->title();}
  QVBoxLayout* centralWidgetLayout(JFrame* o)
  {
   if(o->centralWidget() == NULL)
   {
    QWidget* centralWidget = new QWidget;
    QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
    centralWidget->setLayout(centralWidgetLayout);
    o->setCentralWidget(centralWidget);
   }
   return (QVBoxLayout*)o->centralWidget()->layout();
  }

  void pack(JFrame* o) { o->pack();}
  void show(JFrame* o) { o->show();}
  void setVisible(JFrame* o, bool b) {o->setVisible(b);}
};

class LocoNetMessage_Wrapper : public QObject
{

  Q_OBJECT

public Q_SLOTS:
  // add a constructor
  LocoNetMessage* new_LocoNetMessage(const int msgSize)
  {
   return new LocoNetMessage(msgSize);
  }
  // add a destructor
  void delete_LocoNetMessage(LocoNetMessage* o) { delete o; }

  // add access methods
  void setElement(LocoNetMessage* o, int n, int v) { o->setElement(n,v);}
};

class LnTrafficController_Wrapper : public QObject
{

  Q_OBJECT

public Q_SLOTS:
  // add a constructor
  LnTrafficController* new_LnTrafficController()
  {
   return new LnTrafficController();
  }
  LnTrafficController* instance()
  {
   QObjectList* list = InstanceManager::getList("SystemConnectionMemo");
   int i = 0;
   foreach (QObject* memo, *list)
   {
    if(qobject_cast<LocoNetSystemConnectionMemo*>(memo) != NULL)
    {
     LocoNetSystemConnectionMemo*  connectionMemo = (LocoNetSystemConnectionMemo*)memo;
     LnTrafficController* trafficController = (LnTrafficController*)connectionMemo->getLnTrafficController();
     return trafficController;
    }
   }
   return NULL;
  }
  void sendLocoNetMessage(LnTrafficController* o, LocoNetMessage* m)
  {
   o->sendLocoNetMessage(m);
  }
};
class Turnout_Wrapper : public QObject
{

  Q_OBJECT

public Q_SLOTS:
  // add a constructor
  Turnout* new_Turnout(QObject* parent)
  {
   return new Turnout(parent);
  }
  Turnout* newTurnout(QString sysName, QObject* parent) { return new Turnout(sysName, parent);}
  Turnout* newTurnout(QString sysName, QString userName, QObject* parent) { return new Turnout(sysName, userName, parent);}
  QString getFeedbackModeName(Turnout*t){ return t->getFeedbackModeName();}
  /*public*/ void setCommandedState(AbstractTurnout* t, int s) { t->setCommandedState(s);}
  /*public*/ int getCommandedState(AbstractTurnout* t) {return t->getCommandedState();}

};
class LnTurnout_Wrapper : public QObject
{

  Q_OBJECT

public Q_SLOTS:
  // add a constructor
  LnTurnout* new_Turnout(QString prefix, int number, LnTrafficController* controller)
  {
   return new LnTurnout(prefix, number, controller);
  }
  QString feedbackModeName(LnTurnout* t)
  {
   return t->getFeedbackModeName();
  }
};
class LnPacketizer_Decorators : public QObject
{
 Q_OBJECT
public slots:
 void sendLocoNetMessage(LnPacketizer* p, LocoNetMessage* m)
 {
  p->sendLocoNetMessage(m);
 }
};
class InstanceManager_Decorators : public QObject
{
 Q_OBJECT
public slots:
 ProxyTurnoutManager* turnoutManagerInstance(InstanceManager* m)
 { return (ProxyTurnoutManager*)m->turnoutManagerInstance(); }
 ProxySensorManager* sensorManagerInstance(InstanceManager* m)
 { return (ProxySensorManager*)m->sensorManagerInstance(); }
 SignalHeadManager* signalHeadManagerInstance(InstanceManager *m) {return m->signalHeadManagerInstance();}
 SignalMastManager* signalMastManagerInstance(InstanceManager *m) {return m->signalMastManagerInstance();}
 ProxyLightManager* lightManagerInstance(InstanceManager* m)
 { return (ProxyLightManager*)m->lightManagerInstance(); }
 CommandStation* commandStationInstance(InstanceManager *m) {return m->commandStationInstance();}
 ReporterManager* reporterManagerInstance(InstanceManager *m) {return m->reporterManagerInstance();}
 MemoryManager* memoryManagerInstance(InstanceManager *m) {return m->memoryManagerInstance();}
 RouteManager* routeManagerInstance(InstanceManager *m) {return m->routeManagerInstance();}
 BlockManager* blockManagerInstance(InstanceManager *m) {return m->blockManagerInstance();}
 PowerManager* powerManagerInstance(InstanceManager *m) {return m->powerManagerInstance();}
 ProgrammerManager* programmerManagerInstance(InstanceManager *m) {return m->programmerManagerInstance();}
 ShutDownManager* shutDownManagerInstance(InstanceManager *m) {return m->shutDownManagerInstance();}
 AudioManager* audioManagerInstance(InstanceManager *m) {return m->audioManagerInstance();}
 LayoutBlockManager* layoutBlockManagerInstance(InstanceManager* m)
 { return (LayoutBlockManager*)m->getDefault("LayoutBlockManager");}
 WarrantManager* warrantManagerInstance(InstanceManager* m)
 { return (WarrantManager*)m->getDefault("WarrantManager");}
};
class Turnout_Decorators : public QObject
{
 Q_OBJECT
public slots:
 int static_Turnout_CLOSED() {return Turnout::CLOSED;}
 int static_Turnout_THROWN(Turnout* t) {return Turnout::THROWN;}
 void setCommandedState(Turnout* t, int state) {return t->setCommandedState(state);}
 int commandedState(Turnout* t) { return t->getCommandedState();}
 QString systemName(Turnout* t) { return t->getSystemName();}
 QString userName(Turnout* t) { return t->getUserName();}
 QString displayName(Turnout* t) { return t->getDisplayName(); }
};
#endif
class PythonWrappers : public QObject
{
 Q_OBJECT
public:
 explicit PythonWrappers(QObject *parent = 0);
 static void defineClasses();
signals:

public slots:
};
#if 0
class ProxyTurnoutManager_Decorators : public QObject
{
 Q_OBJECT
public slots:
 Turnout* provideTurnout(ProxyTurnoutManager* t, QString s)
 {
  Turnout* to = t->provideTurnout(s);
  return to;
 }
};
class AbstractTurnout_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
 AbstractTurnout* new_AbstractTurnout(QObject* parent)
 {
  return new AbstractTurnout(parent);
 }
 QString feedbackModeName(AbstractTurnout* t) {  return t->getFeedbackModeName(); }
};
class AbstractNamedBean_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
 AbstractNamedBean* new_AbstractNamedBean(QObject* parent)
 {
  return new AbstractNamedBean(parent);
 }
// AbstractNamedBean* new_AbstractNamedBean(QString sysName, QObject* parent)
// {
//  return new AbstractNamedBean(sysName, parent);
// }
// AbstractNamedBean* new_AbstractNamedBean(QString sysName, QString userName, QObject* parent)
// {
//  return new AbstractNamedBean(sysName, userName, parent);
// }
 QString getSystemName(AbstractNamedBean* b) { return b->getSystemName();}
 QString getUserName(AbstractNamedBean* b) { return b->getUserName();}
 QString getDisplayName(AbstractNamedBean* b) { return b->getDisplayName();}
 QString getComment(AbstractNamedBean* b) { return b->getComment();}

};
class NamedBean_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
 NamedBean* new_NamedBean(QObject* parent)
 {
  return new NamedBean(parent);
 }
 NamedBean* new_AbstractNamedBean(QString sysName, QObject* parent)
 {
  return new NamedBean(sysName, parent);
 }
 void setState(NamedBean* b, int s) { b->setState(s);}
 int getState(NamedBean* b) {return b->getState();}

};
class ProxySensorManager_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
 ProxySensorManager* new_ProxySensorManager() { return new ProxySensorManager();}
 Sensor* getSensor(ProxySensorManager* m, QString name) {return m->getSensor(name);}
 Sensor* provideSensor(ProxySensorManager* m, QString name) {return m->provideSensor(name);}
 Sensor* getBySystemName(ProxySensorManager* m, QString name) {return m->getBySystemName(name);}
 Sensor* getByUserName(ProxySensorManager* m, QString name) {return m->getByUserName(name);}
 Sensor* newSensor(ProxySensorManager* m, QString systemName, QString userName) {return m->newSensor(systemName, userName);}
 QString createSystemName(ProxySensorManager* m,QString curAddress, QString prefix) { return m->createSystemName(curAddress, prefix);}
 QString getNextValidAddress(ProxySensorManager* m,QString curAddress, QString prefix) { return m->getNextValidAddress(curAddress, prefix);}
 long getDefaultSensorDebounceGoingActive(ProxySensorManager* m) {return m->getDefaultSensorDebounceGoingActive();}
 long getDefaultSensorDebounceGoingInActive(ProxySensorManager* m) {return m->getDefaultSensorDebounceGoingInActive();}
 void setDefaultSensorDebounceGoingActive(ProxySensorManager* m, long timer) {return m->setDefaultSensorDebounceGoingActive(timer);}
 void setDefaultSensorDebounceGoingInActive(ProxySensorManager* m, long timer) {return m->setDefaultSensorDebounceGoingInActive(timer);}
};
class LnSensor_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
 LnSensor* newLnSensor(QString systemName, QString userName, LnTrafficController* tc, QString prefix,QObject *parent) {return new LnSensor(systemName, userName, tc, prefix, parent);}
 LnSensor* newLnSensor(QString systemName,  LnTrafficController* tc, QString prefix,QObject *parent) {return new LnSensor(systemName, tc, prefix, parent);}
 void setKnownState(LnSensor* s, int st) { s->setKnownState(st);}
 void message(LnSensor* s, LocoNetMessage* l) {s->message(l);}
 void dispose(LnSensor* s) {s->dispose();}
};

class AbstractSensor_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
 void setInverted(AbstractSensor* s, bool b) { s->setInverted(b);}
 bool getInverted(AbstractSensor* s) {return s->getInverted();}
 QString getStateName(AbstractSensor* s, int i) {return s->getStateName(i);}
};
class Sensor_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
};
class AbstractAutomaton_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
 AbstractAutomaton* new_AbstractAutomaton() {return new AbstractAutomaton();}
 AbstractAutomaton* new_AbstractAutomaton(QString name) {return new AbstractAutomaton(name);}
 void init(AbstractAutomaton* a) { a->init(); }
 void handle(AbstractAutomaton* a) {a->handle();}
 void waitMsec(AbstractAutomaton* a, int milliseconds) { a->waitMsec(milliseconds);}
 DccThrottle* getThrottle(AbstractAutomaton* a, int address, bool longAddress) { return a->getThrottle(address, longAddress); }
 void waitSensorActive(AbstractAutomaton* a, Sensor* s) { a->waitSensorActive(s);}
};
class AbstractAutomaton_Decorators : public QObject
{
 Q_OBJECT
public slots:
 //void init(AbstractAutomaton* a) { a->init(); }
};
class Runnable_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
 Runnable* new_Runnable() { return new Runnable();}
 void start(Runnable* r) { r->start();}
};

class FlowLayout_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
 FlowLayout* new_FlowLayout() { return new FlowLayout();}
 FlowLayout* new_FlowLayout(QWidget *parent, int margin, int hSpacing, int vSpacing) { return new FlowLayout(parent, margin, hSpacing, vSpacing);}
 FlowLayout* new_FlowLayout(int margin, int hSpacing, int vSpacing) {return new FlowLayout(margin, hSpacing, vSpacing);}
};

class PanelMenu_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
 PanelMenu* static_PanelMenu_instance() { return PanelMenu::instance();}
 QList<Editor*>* getEditorPanelList(PanelMenu* m) {return m->getEditorPanelList();}
 QString getTitle(PanelMenu* m) { return m->title();}
};

class Editor_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
  // add a constructor
 QString getTitle(Editor* e) { return e->getTitle(); }
};

class JButton_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
 JButton* new_JButton(QString text) { return new JButton(text);}
 bool emitActionPerformed(ActionEvent* /*e*/) { emit actionPerformed(e); return true; }
//signals:
 Q_SIGNALS:
 void actionPerformed(ActionEvent* /*e*/);
};

class ActionEvent_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
 QString getActionCommand(ActionEvent* /*e*/) { return e->getActionCommand();}
};

class AudioManager_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
 Audio* provideAudio(AbstractAudioManager* m, QString fn)
 {

  Audio* a =  m->provideAudio(fn);
  QString n = a->getSystemName();
  switch (n.at(2).toLatin1())
  {
  case 'B':
   return (AudioBuffer*)a;
  case 'L':
   return (AudioListener*)a;
  case 'S':
   return (AudioSource*)a;
  }
  return a;
 }
 AudioBuffer* provideAudioBuffer(AbstractAudioManager* m, QString fn) { return (AudioBuffer*)m->provideAudio(fn); }
 AudioSource* provideAudioSource(AbstractAudioManager* m, QString fn) { return (AudioSource*)m->provideAudio(fn); }

};

class AbstractAudioManager_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
 Audio* provideAudio(AbstractAudioManager* m, QString fn) { return m->provideAudio(fn); }

};
class DefaultAudioManager_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
};

class Audio_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:

};

class AudioBuffer_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
 void setURL(AudioBuffer* b, QString s) { b->setURL(s);}
};

class AudioSource_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
 void setAssignedBuffer(AudioSource* s, QString name) { s->setAssignedBuffer(name);}
 void setPitch(AudioSource* s, float p) { s->setPitch(p); }
 void setLooped(AudioSource* s, bool b) { s->setLooped(b);}
 void setPosition(AudioSource* s, float x, float y, float z) { s->setPosition(x, y, z);}
 void setMinLoops(AudioSource* s, int l) { s->setMinLoops(l); }
 void setMaxLoops(AudioSource* s, int l) { s->setMaxLoops(l); }
 void setVelocity(AudioSource* s, QVector3D v) { s->setVelocity(v);}
 void play(AudioSource* s) { s->play();}
 void pause(AudioSource* s) { s->pause();}
 void resume(AudioSource* s) { s->resume();}
 void rewind(AudioSource* s) { s->rewind();}
 void stop(AudioSource* s) { s->stop();}
 void fadeIn(AudioSource* s) { s->fadeIn();}
 void fadeOut(AudioSource* s) { s->fadeOut();}
};

class AudioListener_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:

};
class QtSoundAudioBuffer_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
 void setURL(AudioBuffer* b, QString s) { b->setURL(s);}
};

class AbstractAudioBuffer_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:

};
class AbstractAudio_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:

};
class DccThrottle_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:

};
class Throttle_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
 void setF0(Throttle* t, bool b) { t->setF0(b);}
 void setF1(Throttle* t, bool b) { t->setF1(b);}
 void setF2(Throttle* t, bool b) { t->setF2(b);}
 void setF3(Throttle* t, bool b) { t->setF3(b);}
 void setF4(Throttle* t, bool b) { t->setF4(b);}
 void setF5(Throttle* t, bool b) { t->setF5(b);}
 void setF6(Throttle* t, bool b) { t->setF6(b);}
 void setIsForward(Throttle* t, bool b) { t->setIsForward(b);}
 void setSpeedSetting(Throttle* t, float spd) { t->setSpeedSetting(spd);}

};

class Siglet_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
 Siglet* new_Siglet() { return new Siglet();}
 Siglet* new_Siglet(QString name) { return new Siglet(name); }
 void defineIO(Siglet* s) { s->defineIO();}
 void setOutput(Siglet*s) { s->setOutput();}
};

class AbstractShutDownTask_Wrapper : public QObject
{
 Q_OBJECT
public Q_SLOTS:
 AbstractShutDownTask* new_AbstractShutDownTask(QString name) {return new AbstractShutDownTask(name);}
 bool execute(AbstractShutDownTask* t) { return t->execute(); }
};
#endif // end if 0
#endif // PYTHONWRAPPERS_H
