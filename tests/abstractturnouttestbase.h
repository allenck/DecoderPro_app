#ifndef ABSTRACTTURNOUTTESTBASE_H
#define ABSTRACTTURNOUTTESTBASE_H

#include <QObject>
#include "turnout.h"
#include "abstractsensor.h"

class AbstractTurnoutTestBase : public QObject
{
    Q_OBJECT
public:
    explicit AbstractTurnoutTestBase(QObject *parent = nullptr);
    virtual /*public*/ void setUp()=0;    	// load t with actual object; create scaffolds as needed

    /**
     * @return number of listeners registered with the TrafficController by the object under test
     */
    virtual /*public*/ int numListeners()=0;
    virtual /*public*/ void checkThrownMsgSent() throw (InterruptedException) =0;
    virtual /*public*/ void checkClosedMsgSent() throw (InterruptedException) =0;
    /*public*/ void testCreate();
    /*public*/ void testAddListener();
    /*public*/ void testRemoveListener();
    /*public*/ void testDispose();
    /*public*/ void testCommandClosed() throw (InterruptedException) ;
    /*public*/ void testCommandThrown() throw (InterruptedException);
    /*public*/ void testRequestUpdate() throw (JmriException);
    /*public*/ void testGetAndSetInverted();
    /*public*/ void testInvertedCommandClosed() throw (InterruptedException);
    /*public*/ void testInvertedCommandThrown() throw (InterruptedException) ;
    /*public*/ void testProvideFirstFeedbackSensor() throw (JmriException);
    /*public*/ void testProvideSecondFeedbackSensor() throw (JmriException);
    /*public*/ void testOneSensorFeedback() throw (JmriException);
    /*public*/ void testTwoSensorFeedback() throw (JmriException);
    /*public*/ void testDirectFeedback() throw (Exception);
    /*public*/ void testGetBeanType();

signals:

public slots:

protected:
    /*protected*/ Turnout* t = nullptr;	// holds object under test; set by setUp()
    static /*protected*/ bool listenerResult;// = false;
    static /*protected*/ int listenStatus;// = Turnout::UNKNOWN;
 friend class ListenO1;
};

/*public*/ class ListenO1 : public QObject, public PropertyChangeListener {
Q_OBJECT
   Q_INTERFACES(PropertyChangeListener) AbstractTurnoutTestBase* base;
public:
    ListenO1(AbstractTurnoutTestBase* base) {this->base = base;}
QObject* self() {return (QObject*)this;}public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e) {
        base->listenerResult = true;
        if (e->getPropertyName() == ("KnownState")) {
            base->listenStatus =  e->getNewValue().toInt();
        }
    }
};
class TestSensor :  public AbstractSensor {
    Q_OBJECT
        AbstractTurnoutTestBase* base;
    public:
        /*public*/ mutable bool request = false;

        /*public*/ TestSensor(QString sysName, QString userName, AbstractTurnoutTestBase* base) :AbstractSensor(sysName, userName)
        {
            //super(sysName, userName);
            this->base = base;
        }

        //@Override
        /*public*/ void requestUpdateFromLayout()const override{
            request = true;
        }

        bool getRequest(){
          return request;
        }

        void resetRequest(){
          request=false;
        }
};
#endif // ABSTRACTTURNOUTTESTBASE_H
