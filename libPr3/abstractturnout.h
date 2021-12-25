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
#include "localdatetime.h"
#include "sleeperthread.h"

class IntervalCheck;
class TurnoutOperation;
class TurnoutOperator;
class LIBPR3SHARED_EXPORT AbstractTurnout : public Turnout, public PropertyChangeListener
{
 friend class InternalTurnoutManager;
 Q_OBJECT
 Q_INTERFACES(PropertyChangeListener)
public:
 explicit AbstractTurnout(QObject *parent = 0);
 /*public*/ int getKnownState() override;
 /*public*/ QString describeState(int state) override;

     //@Override
     /*public*/ QString getBeanType() override{
         return tr("Turnout");
     }
    /**
     * Public access to changing turnout state. Sets the commanded state and,
     * if appropriate starts a TurnoutOperator to do its thing. If there is no
     * TurnoutOperator (not required or nothing suitable) then just tell the layout
     * and hope for the best.
     */
    /*public*/ void setCommandedState(int s) override;
    /*public*/ int getCommandedState() override;
    /*public*/ void setCommandedStateAtInterval(int s) override;
    /**
     * Show whether state is one you can safely run trains over
     * @return	true iff state is a valid one and the known state is the same as commanded
     */
    /*public*/ bool isConsistentState() override;
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
    /*public*/ virtual void setState(int s) override;
    /**
     * Implement a shorter name for getKnownState.
     * <P>
     * This generally shouldn't be used by Java code; use getKnownState instead.
     * The is provided to make Jython script access easier to read.
     * <P>
     * Note that getState() and setState(int) are not symmetric: getState is the
     * known state, and set state modifies the commanded state.
     */
    /*public*/ int getState() override;
    /* Type of turnout control - defaults to 0 for 'steady state' */

    /*public*/ int getNumberOutputBits() override;
    /*public*/ void setNumberOutputBits(int num) override;
    /*public*/ int getControlType() override;
    /*public*/ void setControlType(int num) override;
    /*public*/ int getValidFeedbackTypes() override;
    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of //cheap array copy
    /*public*/ QVector<QString> getValidFeedbackNames() override;
    /*public*/ void setFeedbackMode(QString mode) /*throw(IllegalArgumentException)*/ override;
    /*public*/ void setFeedbackMode(int mode) /*throw(IllegalArgumentException)*/ override;
    /*public*/ int getFeedbackMode() override;
    /*public*/ QString getFeedbackModeName() override;
    /*public*/ void requestUpdateFromLayout() override;

    /*public*/ void setInverted(bool inverted) override;
    /**
     * Get the turnout inverted state. If true, commands sent to the layout are
     * reversed. Thrown becomes Closed, and Closed becomes Thrown.
     * <P>
     * Used in polling loops in system-specific code, so made final to allow
     * optimization.
     */
    /*final public*/ bool getInverted() override;
    /**
     * Determine if the turnouts can be inverted. If true inverted turnouts
     * supported.
     */
    /*public*/ bool canInvert()const override;
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
    /*public*/ void setLocked(int turnoutLockout, bool locked) override;
    /**
     * Determine if turnout is locked. Returns true if turnout is locked.
     * There are two types of locks, cab lockout, and pushbutton lockout.
     */
    /*public*/ bool getLocked(int turnoutLockout) override;
    /*public*/ bool canLock(int turnoutLockout) override;
    /*public*/ void enableLockOperation(int turnoutLockout, bool enabled) override;
    /**
     *  When true, report to console anytime a cab attempts to change the
     *  state of a turnout on the layout.  When a turnout is cab locked, only
     *  JMRI is allowed to change the state of a turnout.
     */
    /*public*/ void setReportLocked(bool reportLocked) override;
    /**
     *  When true, report to console anytime a cab attempts to change the
     *  state of a turnout on the layout.  When a turnout is cab locked, only
     *  JMRI is allowed to change the state of a turnout.
     */
/*public*/ bool getReportLocked() override;

    /*public*/ QStringList getValidDecoderNames() override;
    /*public*/ QString getDecoderName() override;
    /*public*/ void setDecoderName(QString decoderName) override;
    /*public*/ TurnoutOperator* getCurrentOperator();
    /*public*/ TurnoutOperation* getTurnoutOperation() override;
    /*public*/ void setTurnoutOperation(TurnoutOperation* toper) override;
    /*public*/ bool getInhibitOperation() override;
    /*public*/ void setInhibitOperation(bool io) override;
    /*public*/ void provideFirstFeedbackSensor(QString pName) /*throw(JmriException)*/ override;
    /*public*/ void provideFirstFeedbackNamedSensor(NamedBeanHandle<Sensor*>* s);
    /*public*/ Sensor* getFirstSensor() override;
    /*public*/ NamedBeanHandle <Sensor*>* getFirstNamedSensor() override;
    /*public*/ void provideSecondFeedbackSensor(QString pName) /*throw(JmriException)*/ override;
    /*public*/ void provideSecondFeedbackNamedSensor(NamedBeanHandle<Sensor*>* s);
    /*public*/ Sensor* getSecondSensor() override;
    /*public*/ NamedBeanHandle <Sensor*>* getSecondNamedSensor() override;
    /*public*/ void setInitialKnownStateFromFeedback() override;
    /**
     * React to sensor changes by changing the KnownState
     * if using an appropriate sensor mode
     */
    ///*public*/ void propertyChange(PropertyChangeEvent* evt);
    /*public*/ void setBinaryOutput(bool state) override;
    /*public*/ void dispose() override;
    /*public*/ float getDivergingLimit() override;
    /*public*/ QString getDivergingSpeed() override;
    /*public*/ void setDivergingSpeed(QString s) const /*throw(JmriException) */override;
    /*public*/ float getStraightLimit() override;
    /*public*/ QString getStraightSpeed() override;
    /*public*/ void setStraightSpeed(QString s)const  /*throw(JmriException)*/ override;
    QObject* self() override{return (QObject*)this;}
    /*public*/ QList<NamedBeanUsageReport*> getUsageReport(NamedBean* bean)override;
    /*public*/ bool isCanFollow()override;
    /*public*/ Turnout* getLeadingTurnout()override;
    /*public*/ void setLeadingTurnout(/*@CheckForNull*/ Turnout* turnout)override;
    /*public*/ void setLeadingTurnout(/*@CheckForNull*/ Turnout* turnout, bool followingCommandedState)override;
    /*public*/ bool isFollowingCommandedState()override;
    /*public*/ void setFollowingCommandedState(bool following)override;
    //void propertyChange(PropertyChangeEvent *);
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/override;

public slots:
    void propertyChange(PropertyChangeEvent *evt) override;

private:
    mutable QString _divergeSpeed;
    mutable QString _straightSpeed;
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
    /*private*/ Turnout* leadingTurnout = nullptr;
    /*private*/ bool followingCommandedState = true;
    LocalDateTime* nextWait;
    IntervalCheck* thr = nullptr;

protected:
    AbstractTurnout(QString systemName, QObject *parent=0);
    AbstractTurnout(QString systemName, QString userName, QObject *parent=0);
    QVector<QString> _validFeedbackNames;

    QVector<int> _validFeedbackModes;

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

    bool inhibitOperation = true; // do not automate this turnout, even if globally operations are on
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
    friend class IntervalCheck;

};

class IntervalCheck : public QObject
{
  Q_OBJECT
  AbstractTurnout* at;
  int s;
 public:
  IntervalCheck(int s, AbstractTurnout* at) {this->s = s; this->at = at;}
 signals:
  void finished();
 public slots:
  void process()
  {
   at->log->debug(tr("go to sleep for %1 ms...").arg(qMax(0ULL, LocalDateTime::now()->until(at->nextWait, LocalDateTime::ChronoUnit::MILLIS))));
   try {
       SleeperThread::msleep(qMax(0ULL, LocalDateTime::now()->until(at->nextWait, LocalDateTime::ChronoUnit::MILLIS))); // nextWait might have passed in the meantime
       at->log->debug(tr("back from sleep, forward on %1").arg(LocalDateTime::now()->toString()));
       at->setCommandedState(s);
   } catch (InterruptedException* ex) {
       at->log->debug(tr("setCommandedStateAtInterval(s) interrupted at %1").arg(LocalDateTime::now()->toString()));
//       Thread.currentThread().interrupt(); // retain if needed later
       emit finished();
   }

  }
};

#endif // ABSTRACTTURNOUT_H
