#ifndef ABSTRACTAUTOMATON_H
#define ABSTRACTAUTOMATON_H
#include <QThread>
#include "runnable.h"
#include "logger.h"
#include <QFrame>
#include <QPushButton>
#include <QTextEdit>
#include "propertychangelistener.h"
#include "propertychangeevent.h"
#include <QWaitCondition>
#include "jframe.h"
#include "proglistener.h"
#include <QVBoxLayout>
#include "dcclocoaddress.h"
#include "rosterentry.h"
#include <QEventLoop>
#include "liblayouteditor_global.h"

//class Runnable;
class AutomatSummary;
class Sensor;
class Turnout;
class NamedBean;
class DccThrottle;
class BasicRosterEntry;
class PropertyChangeListener;
class LIBLAYOUTEDITORSHARED_EXPORT AbstractAutomaton : public QObject
{
    Q_OBJECT
public:
    //explicit AbstractAutomaton(QObject *parent = 0);
    /*public*/ AbstractAutomaton(QObject *parent = 0);
    /*public*/ AbstractAutomaton(QString name, QObject *parent= 0);
    ~AbstractAutomaton();
    /*public*/ void start(bool bRunInThread = true);
//    /*public*/ void run();
    /*public*/ void stop();
    void done();
    /*public*/ int getCount();
    /*public*/ QString getName() ;
    /*public*/ void setName(QString name);
    void defaultName();
    /*public*/ void waitMsec( int milliseconds );
    /*public*/ int waitSensorChange(int mState, Sensor* mSensor);
    /*public*/ void waitSensorActive(QList<Sensor*> mSensors);
    /*public*/ void waitSensorActive(Sensor* mSensor);
    /*public*/ void waitSensorInactive(Sensor* mSensor);
    /*public*/ /*synchronized*/ void waitSensorState(Sensor* mSensor, int state);
    /*public*/ void waitSensorInactive(QList<Sensor*> mSensors);
    /*public*/ /*synchronized*/ void waitSensorState(QList<Sensor*> mSensors, int state);
    /*public*/ /*synchronized*/ void waitTurnoutConsistent(QList<Turnout*> mTurnouts);
    /*public*/ void setTurnouts(QList<Turnout*> closed, QList<Turnout*> thrown);
    /*public*/ void waitChange(QVector<NamedBean*> mInputs);
    /*public*/ /*synchronized*/ void waitSensorChange(QList<Sensor*> mSensors);
    /*public*/ DccThrottle* getThrottle(int address, bool longAddress);
    /*public*/ DccThrottle* getThrottle(BasicRosterEntry* re);
    /*public*/ bool writeServiceModeCV(QString CV, int value);
    /*public*/ int readServiceModeCV(QString CV);
    /*public*/ bool writeOpsModeCV(QString CV, int value, bool longAddress, int loco);
    void notifyAll();
    /*public*/ void notifyThrottleFound(DccThrottle* t);
    /*public*/ void notifyFailedThrottleRequest(DccLocoAddress* address, QString reason);
    /*public*/ void setTerminateSensor(Sensor* ts);

signals:
 void finished();
 void terminate();

public slots:
    virtual void init();
    void sensorChange(PropertyChangeEvent*);
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    void threadTerminated();
    /*public*/ void process();

private:
 AutomatSummary* summary;// = AutomatSummary.instance();
 QThread* currentThread;// = NULL;
 Logger* log;
 QMainWindow* debugWaitFrame;// = NULL;
 /*private*/ QString name;// = NULL;
 /*private*/ int count;
 QMutex mutex;
 QMutex throttleMutex;
 QWaitCondition condition;
 QEventLoop loop;
 /**
  * Flag used to ensure that service routines
  * are only invoked in the automaton thread.
  */
 /*private*/ bool inThread;// = false;

 /*private*/ AbstractAutomaton* self;// = this;
 /*private*/ bool checkForState(QList<Sensor*> mSensors, int state) ;
 /*private*/ bool checkForConsistent(QList<Turnout*> mTurnouts);
 /*private*/ DccThrottle* throttle;
 /*private*/ void debuggingWait();
 /*private*/ /*volatile*/ int cvReturnValue;
 QFrame* messageFrame;// = NULL;
 QString message;// = NULL;
 Sensor* terminateSensor;
 bool bRun;
 bool bRunInThread;


 friend class Runnable1;
#if 0
 class SensorListener : PropertyChangeListener
 {
     AbstractAutomaton* me;
  public:
     SensorListener(AbstractAutomaton* me)
     {
      this-> me = me;
     }
     void propertyChange(PropertyChangeEvent* e)
     {
      /*synchronized (self) */
      {
       QMutexLocker locker(&me->self->mutex);
       me->self->notifyAll(); // should be only one thread waiting, but just in case
      }
     }
 };
#endif
 class ProgListener1 : public ProgListener
 {
 public:
     ProgListener1(AbstractAutomaton* self)
     {
      this->_self = self;
     }

     /*public*/ void programmingOpReply(int /*value*/, int /*status*/)
     {
      /*synchronized (self)*/
      {
       QMutexLocker locker(&mutex2);
       _self->notifyAll(); // should be only one thread waiting, but just in case
      }
     }
     QObject* self() {return (QObject*)this;}
 private:
     QMutex mutex2;
     AbstractAutomaton* _self;
 };
 class ProgListener2 : public ProgListener
 {
   public:
     ProgListener2(AbstractAutomaton* self)
     {
      this->_self = self;
     }
     QObject* self() {return (QObject*)this;}

     /*public*/ void programmingOpReply(int value, int /*status*/) {
         _self->cvReturnValue = value;
         /*synchronized (self) */{
             QMutexLocker locker(&mutex);
             _self->notifyAll(); // should be only one thread waiting, but just in case
         }
     }
 private:
     QMutex mutex;
     AbstractAutomaton* _self;
 };
 class ProgListener3 : public ProgListener
 {
   public:
     ProgListener3(AbstractAutomaton* self)
     {
      this->_self = self;
     }
     QObject* self() {return (QObject*)this;}

     /*public*/ void programmingOpReply(int /*value*/, int /*status*/)
     {
         /*synchronized (self)*/ {
             QMutexLocker locker(&mutex);
             _self->notifyAll(); // should be only one thread waiting, but just in case
         }
     }
 private:
     AbstractAutomaton* _self;
     QMutex mutex;
 };
private slots:
 void terminateSensor_changed(PropertyChangeEvent*);

protected:
 ///*protected*/ virtual void init();
 /*protected*/ virtual bool handle();
 /**
  * Control optional debugging prompt.
  * If this is set true,
  * each call to wait() will prompt the user whether to continue.
  */
 /*protected*/ bool promptOnWait;// = false;
 /*protected*/ void wait(int milliseconds);
 friend class AbstractAutomaton_Wrapper;
};
/**
 * Internal class to show a Frame
 */
/*public*/ class MsgFrame : Runnable
{
    QString mMessage;
    bool mPause;
    bool mShow;
    JFrame* mFrame;// = NULL;
    QPushButton* mButton;
    QTextEdit* mArea;
 public:
    MsgFrame();
    /*public*/ void hide();
    /*public*/ void show(QString pMessage, bool pPause) ;
    /*public*/ void run();
protected:
 /*protected*/ virtual void format();
};

class Runnable1 : public Runnable
{
    Q_OBJECT
public:
    Runnable1(AbstractAutomaton* self)
    {
     this->self = self;
    }

 /*public*/ void run()
 {
  // create a prompting frame
  if (self->debugWaitFrame==NULL)
  {
    debugWaitFrame = new QMainWindow();
    debugWaitFrame->setWindowTitle(tr("Automaton paused"));
    QPushButton* b = new QPushButton("Continue");
    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(new QVBoxLayout());
    debugWaitFrame->setCentralWidget(centralWidget);
    //debugWaitFrame.getContentPane().add(b);
    centralWidget->layout()->addWidget(b);
//             b.addActionListener(new java.awt.event.ActionListener() {
//                 /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                     synchronized (self) {
//                         self->notifyAll(); // should be only one thread waiting, but just in case
//                     }
//                     debugWaitFrame.setVisible(false);
//                 }
//             });
//            debugWaitFrame->pack();
    connect(b, SIGNAL(clicked()), this, SLOT(on_buttonClicked()));
        }

        debugWaitFrame->setVisible(true);
    }
public slots:
    void on_buttonClicked()
    {
     /*synchronized (self)*/
     {
     //QMutexLocker locker(&mutex);
     self->notifyAll(); // should be only one thread waiting, but just in case
     }
    }
private:
    AbstractAutomaton* self;
    QMainWindow* debugWaitFrame;
};
#endif // ABSTRACTAUTOMATON_H
