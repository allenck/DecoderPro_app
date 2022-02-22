#ifndef DOUBLETURNOUTSIGNALHEAD_H
#define DOUBLETURNOUTSIGNALHEAD_H
#include "defaultsignalhead.h"
#include "namedbeanhandle.h"
#include "actionlistener.h"
#include "propertychangelistener.h"

class Turnout;
class Timer;
class LIBPR3SHARED_EXPORT DoubleTurnoutSignalHead : public DefaultSignalHead
{
    Q_OBJECT
public:
    //explicit DoubleTurnoutSignalHead(QObject *parent = 0);
    /*public*/ DoubleTurnoutSignalHead(QString sys, QString user, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* red, QObject *parent = 0);
    /*public*/ DoubleTurnoutSignalHead(QString sys, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* red, QObject *parent = 0);
    ~DoubleTurnoutSignalHead() {dispose();}
    /*public*/ void dispose() ;
    /*public*/ NamedBeanHandle<Turnout*>* getRed();
    /*public*/ NamedBeanHandle<Turnout*>* getGreen();
    /*public*/ void setRed(NamedBeanHandle<Turnout*>* t);
    /*public*/ void setGreen(NamedBeanHandle<Turnout*>* t);
    /*protected*/ void updateOutput(); // needs to be public for flash to work

signals:

public slots:
// /*public*/ void propertyChange(PropertyChangeEvent* propertyChangeEvent);
 virtual void readOutput();

private:

    NamedBeanHandle<Turnout*>* mRed = nullptr;
    NamedBeanHandle<Turnout*>* mGreen = nullptr;
    static Logger* log;
    Timer* readUpdateTimer = nullptr;
    bool isTurnoutUsed(Turnout* t);
    int mRedCommanded;
    int mGreenCommanded;
    /*private*/ PropertyChangeListener* turnoutChangeListener = nullptr;
    void commandState(int red, int green);

protected:
    //friend class DefaultSignalHead;
 friend class TripleTurnoutSignalHead;
 friend class QuadOutputSignalHead;
 friend class TripleOutputSignalHead;
 friend class DoubleTurnoutSignalHeadTest;
 friend class TurnoutPropertyChangeListener;
};

class TimerActionListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 DoubleTurnoutSignalHead* dtsh;
public:
 TimerActionListener( DoubleTurnoutSignalHead* dtsh) {this->dtsh = dtsh;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)override;
};

class TurnoutPropertyChangeListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 DoubleTurnoutSignalHead* dtsh;
public:
 TurnoutPropertyChangeListener(DoubleTurnoutSignalHead* dtsh) {this->dtsh = dtsh;}
 QObject* pself() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent*)override;
};
#endif // DOUBLETURNOUTSIGNALHEAD_H
