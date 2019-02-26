#ifndef ABSTRACTTURNOUT_H
#define ABSTRACTTURNOUT_H
//#include "abstractnamedbean.h"
#include "turnout.h"
#include "exceptions.h"
#include "namedbeanhandle.h"
#include "turnoutoperation.h"
//#include "instancemanager.h"
#include "namedbeanhandlemanager.h"
#include "libPr3_global.h"

class TurnoutOperation;
class TurnoutOperator;
class LIBPR3SHARED_EXPORT AbstractTurnout : public Turnout
{
 friend class InternalTurnoutManager;
 Q_OBJECT
public:
 explicit AbstractTurnout(QObject *parent = 0);
 /*public*/ int getKnownState();
 /*public*/ QString describeState(int state);

     //@Override
     /*public*/ QString getBeanType() {
         return tr("Turnout");
     }
    /**
     * Public access to changing turnout state. Sets the commanded state and,
     * if appropriate starts a TurnoutOperator to do its thing. If there is no
     * TurnoutOperator (not required or nothing suitable) then just tell the layout
     * and hope for the best.
     */
    /*public*/ void setCommandedState(int s);
    /*public*/ int getCommandedState();
    /**
     * Show whether state is one you can safely run trains over
     * @return	true iff state is a valid one and the known state is the same as commanded
     */
    /*public*/ bool isConsistentState();
    /**
     * The name pretty much says it.
     *<P>
     * Triggers all listeners, etc. For use by the TurnoutOperator classes.
     */
    void setKnownStateToCommanded() ;
    /**
     * Implement a shorter name for setCommandedState.
     * <P>
     * This generally shouldn't be used by Java code; use setCommandedState
     * instead. The is provided to make Jython script access easier to read.
     * <P>
     * Note that getState() and setState(int) are not symmetric: getState is the
     * known state, and set state modifies the commanded state.
     */
    /*public*/ virtual void setState(int s);
    /**
     * Implement a shorter name for getKnownState.
     * <P>
     * This generally shouldn't be used by Java code; use getKnownState instead.
     * The is provided to make Jython script access easier to read.
     * <P>
     * Note that getState() and setState(int) are not symmetric: getState is the
     * known state, and set state modifies the commanded state.
     */
    /*public*/ virtual int getState();
    /* Type of turnout control - defaults to 0 for 'steady state' */

    /*public*/ int getNumberOutputBits();
    /*public*/ void setNumberOutputBits(int num);
    /*public*/ int getControlType();
    /*public*/ void setControlType(int num);
    /*public*/ int getValidFeedbackTypes();
    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of //cheap array copy
    /*public*/ QStringList getValidFeedbackNames();
    /*public*/ void setFeedbackMode(QString mode) throw(IllegalArgumentException);
    /*public*/ void setFeedbackMode(int mode) throw(IllegalArgumentException);
    /*public*/ int getFeedbackMode();
    /*public*/ QString getFeedbackModeName();
    /*public*/ void requestUpdateFromLayout();

    /*public*/ void setInverted(bool inverted);
    /**
     * Get the turnout inverted state. If true, commands sent to the layout are
     * reversed. Thrown becomes Closed, and Closed becomes Thrown.
     * <P>
     * Used in polling loops in system-specific code, so made final to allow
     * optimization.
     */
    /*final public*/ bool getInverted();
    /**
     * Determine if the turnouts can be inverted. If true inverted turnouts
     * supported.
     */
    /*public*/ virtual bool canInvert();
    /**
     * Turnouts that are locked should only respond to JMRI commands to change
     * state. We simulate a locked turnout by monitoring the known state
     * (turnout feedback is required) and if we detect that the known state has
     * changed, negate it by forcing the turnout to return to the commanded
     * state. Turnout that have local buttons can also be locked if their
     * decoder supports it.
     *
     * @param locked
     */
    /*public*/ void setLocked(int turnoutLockout, bool locked);
    /**
     * Determine if turnout is locked. Returns true if turnout is locked.
     * There are two types of locks, cab lockout, and pushbutton lockout.
     */
    /*public*/ bool getLocked(int turnoutLockout);
    /*public*/ bool canLock(int turnoutLockout);
    /*public*/ void enableLockOperation(int turnoutLockout, bool enabled);
    /**
     *  When true, report to console anytime a cab attempts to change the
     *  state of a turnout on the layout.  When a turnout is cab locked, only
     *  JMRI is allowed to change the state of a turnout.
     */
    /*public*/ void setReportLocked(bool reportLocked);
    /**
     *  When true, report to console anytime a cab attempts to change the
     *  state of a turnout on the layout.  When a turnout is cab locked, only
     *  JMRI is allowed to change the state of a turnout.
     */
/*public*/ bool getReportLocked();

    /*public*/ QStringList getValidDecoderNames();
    /*public*/ QString getDecoderName();
    /*public*/ void setDecoderName(QString decoderName);
    /*public*/ TurnoutOperator* getCurrentOperator();
    /*public*/ TurnoutOperation* getTurnoutOperation();
    /*public*/ void setTurnoutOperation(TurnoutOperation* toper);
    /*public*/ bool getInhibitOperation();
    /*public*/ void setInhibitOperation(bool io);
    /*public*/ void provideFirstFeedbackSensor(QString pName) throw(JmriException);
    /*public*/ void provideFirstFeedbackNamedSensor(NamedBeanHandle<Sensor*>* s);
    /*public*/ Sensor* getFirstSensor();
    /*public*/ NamedBeanHandle <Sensor*>* getFirstNamedSensor();
    /*public*/ void provideSecondFeedbackSensor(QString pName) throw(JmriException);
    /*public*/ void provideSecondFeedbackNamedSensor(NamedBeanHandle<Sensor*>* s);
    /*public*/ Sensor* getSecondSensor();
    /*public*/ NamedBeanHandle <Sensor*>* getSecondNamedSensor();
    /*public*/ void setInitialKnownStateFromFeedback();
    /**
     * React to sensor changes by changing the KnownState
     * if using an appropriate sensor mode
     */
    ///*public*/ void propertyChange(PropertyChangeEvent* evt);
    /*public*/ void setBinaryOutput(bool state);
    /*public*/ virtual void dispose();
    /*public*/ float getDivergingLimit();
    /*public*/ QString getDivergingSpeed();
    /*public*/ void setDivergingSpeed(QString s) throw(JmriException);
    /*public*/ float getStraightLimit();
    /*public*/ QString getStraightSpeed();
    /*public*/ void setStraightSpeed(QString s) throw(JmriException);

signals:
    //void propertyChange(PropertyChangeEvent *);

public slots:
    void on_propertyChange(PropertyChangeEvent *evt);

private:
    QString _divergeSpeed;
    QString _straightSpeed;
    //bool useBlockSpeed = true;

    //float speedThroughTurnout = 0;
    /*
     * support for associated sensor or sensors
     */
    //Sensor getFirstSensor() = null;
    /*private*/ NamedBeanHandle<Sensor*>*_firstNamedSensor;

    //Sensor getSecondSensor() = null;
    /*private*/ NamedBeanHandle<Sensor*>* _secondNamedSensor;
    static Logger* log;

protected:
    AbstractTurnout(QString systemName, QObject *parent=0);
    AbstractTurnout(QString systemName, QString userName, QObject *parent=0);
    QStringList _validFeedbackNames;

    QList<int> _validFeedbackModes;

    int _validFeedbackTypes; //= DIRECT | ONESENSOR | TWOSENSOR;

    int _activeFeedbackType;
    int _knownState;

    int _commandedState;

    int _numberOutputBits;

    /* Number of bits to control a turnout - defaults to one */
    int _controlType;
    bool _inverted;
    bool _cabLockout; // = false;

    bool _pushButtonLockout; // = false;

    bool _enableCabLockout;// = false;

    bool _enablePushButtonLockout;// = false;
    bool _reportLocked;// = true;

#if 1 // TODO: define TurnoutOperator
    TurnoutOperator* myOperator;
#endif
    TurnoutOperation* myTurnoutOperation;

    bool inhibitOperation;// = false; // do not automate this turnout, even if globally operations are on
    bool binaryOutput;// = false;
    /**
     * Handle a request to change state, typically by sending a message to the
     * layout in some child class. Public version (used by TurnoutOperator)
     * sends the current commanded state without changing it.
     *
     * @param s new state value
     */
    /*abstract protected*/ virtual void forwardCommandChangeToLayout(int s) /*=0*/;
    /*protected*/ virtual void forwardCommandChangeToLayout() /*=0*/;
    /**
     * Sets a new Commanded state, if need be notifying the listeners, but does
     * NOT send the command downstream. This is used when a new commanded state
     * is noticed from another command.
     */
    /*protected*/ void newCommandedState(int s);
    /**
     * Add a protected newKnownState() for use by implementations.
     * <P>
     * Use this to update internal information when a state change is detected
     * <em>outside</em> the Turnout object, e.g. via feedback from sensors on
     * the layout.
     * <P>
     * If the layout status of the Turnout is observed to change to THROWN or
     * CLOSED, this also sets the commanded state, because it's assumed that
     * somebody somewhere commanded that move. If it's observed to change to
     * UNKNOWN or INCONSISTENT, that's perhaps either an error or a move in
     * progress, and no change is made to the commanded state.
     * <P>
     * This implementation sends a command to the layout for the new state if
     * going to THROWN or CLOSED, because there may be others listening to
     * network state.
     * <P>
     * Not intended for general use, e.g. for users to set the KnownState.
     *
     * @param s
     *            New state value
     */
    /*protected*/ void newKnownState(int s);
    /**
     * Valid stationary decoder names
     */
    /*protected*/ QStringList _validDecoderNames;// = PushbuttonPacket
    // set the turnout decoder default to unknown
    /*protected*/ QString _decoderName;// = PushbuttonPacket.unknown;
    /*abstract protected*/ virtual void turnoutPushbuttonLockout(bool locked) /*=0*/;
    /*protected*/ void turnoutPushbuttonLockout();
    /*protected*/ void operationPropertyChange(PropertyChangeEvent* evt);
    /**
     * Allow an actual turnout class to transform private
     * feedback types into ones that the generic turnout operations know about
     * @return	apparent feedback mode for operation lookup
     */
    /*protected*/ int getFeedbackModeForOperation();
    /*protected*/ void sensorPropertyChange(PropertyChangeEvent* evt);
    /*protected*/ TurnoutOperator*  getTurnoutOperator();
    friend class NoFeedbackTurnoutOperator;
    friend class SensorTurnoutOperator;
};

#endif // ABSTRACTTURNOUT_H
