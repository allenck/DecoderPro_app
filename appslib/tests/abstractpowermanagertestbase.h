#ifndef virtualPOWERMANAGERTESTBASE_H
#define virtualPOWERMANAGERTESTBASE_H

#include <QObject>
#include "exceptions.h"
#include "propertychangelistener.h"

class PowerManager;
class AbstractPowerManagerTestBase : public QObject
{
    Q_OBJECT
public:
    explicit AbstractPowerManagerTestBase(QObject *parent = nullptr);
    virtual /*public*/ void setUp() =0;
    /*public*/ void testCreate();
    /*public*/ void testSetPowerOn() throw (JmriException);
    /*public*/ void testSetPowerOff() throw (JmriException);
    /*public*/ void testSetPowerIdle() throw (JmriException);
    /*public*/ void testStateOn() throw (JmriException);
    /*public*/ void testStateOff() throw (JmriException);
    /*public*/ void testStateIdle() throw (JmriException);
    /*public*/ void testAddListener() throw (JmriException);
    /*public*/ void testRemoveListener();
    /*public*/ void testDispose1() throw (JmriException);
    /*public*/ void testDispose2() throw (JmriException);
    /*public*/ void testImplementsIdle();

signals:

public slots:
protected:
    // service routines to simulate receiving on, off from interface
    /*protected*/ virtual void hearOn() = 0;

    /*protected*/ virtual void hearOff() = 0;

    /*protected*/ virtual void hearIdle() = 0;

    /*protected*/ virtual void sendOnReply() = 0;	  // get a reply to On command from layout

    /*protected*/ virtual void sendOffReply() = 0;   // get a reply to Off command from layout

    /*protected*/ virtual void sendIdleReply() = 0;

    /*protected*/ virtual int numListeners() = 0;

    /*protected*/ virtual int outboundSize() = 0;

    /*protected*/ virtual bool outboundOnOK(int /*index*/) = 0;

    /*protected*/ virtual bool outboundOffOK(int /*index*/) = 0;

    /*protected*/ virtual bool outboundIdleOK(int /*index*/) = 0;

    /*protected*/ PowerManager* p = nullptr;	// holds objects under test

    static /*protected*/ bool listenerResult;// = false;
    friend class Listen;
};
/*protected*/ class Listen : public PropertyChangeListener {
Q_OBJECT
    AbstractPowerManagerTestBase* tb;
public:
    Listen(AbstractPowerManagerTestBase* tb) {this->tb = tb;}
public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e) {
        tb->listenerResult = true;
    }
};

#endif // virtualPOWERMANAGERTESTBASE_H
