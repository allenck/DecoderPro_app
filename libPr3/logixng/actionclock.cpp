#include "actionclock.h"
#include "defaultdigitalactionmanager.h"

/**
 * This action provides the ability to set the fast clock time and start and stop the fast clock.
 *
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright 2021
 */
///*public*/  class ActionClock extends AbstractDigitalAction {


    /*public*/  ActionClock::ActionClock(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     setObjectName("ActionClock");
    }

    //@Override
    /*public*/  Base* ActionClock::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionClock* copy = new ActionClock(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setBeanState(_clockState);
        copy->setClockTime(_clockTime);
        return manager->registerAction(copy);
    }

    /*public*/  void ActionClock::setBeanState(ClockState::STATE state) {
        _clockState = state;
    }

    /*public*/  ActionClock::ClockState::STATE ActionClock::getBeanState() {
        return _clockState;
    }

    /*public*/  void ActionClock::setClockTime(int minutes) {
        _clockTime = minutes;
    }

    /*public*/  int ActionClock::getClockTime() {
        return _clockTime;
    }

    /**
     * Convert minutes since midnight to hh:mm.
     * @param minutes The number of minutes from 0 to 1439.
     * @return time formatted as hh:mm.
     */
    /*public*/  /*static*/ QString ActionClock::formatTime(int minutes) {
        QString hhmm = "00:00";
        if (minutes >= 0 && minutes < 1440) {
            hhmm = QString("%1:%2").arg(
                    minutes / 60,
                    minutes % 60);
        }
        return hhmm;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category ActionClock::getCategory() {
        return Category::ITEM;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionClock::execute() /*throws JmriException*/ {
        ClockState::STATE theState = _clockState;
//        ThreadingUtil::runOnLayoutWithJmriException(() -> {
//            switch(theState) {
//                case SetClock:
//                    Calendar cal = Calendar.getInstance();
//                    cal.setTime(InstanceManager.getDefault(jmri.Timebase.class).getTime());
//                    cal.set(Calendar.HOUR_OF_DAY, _clockTime / 60);
//                    cal.set(Calendar.MINUTE, _clockTime % 60);
//                    cal.set(Calendar.SECOND, 0);
//                    InstanceManager.getDefault(jmri.Timebase.class).userSetTime(cal.getTime());
//                    break;
//                case StartClock:
//                    InstanceManager.getDefault(jmri.Timebase.class).setRun(true);
//                    break;
//                case StopClock:
//                    InstanceManager.getDefault(jmri.Timebase.class).setRun(false);
//                    break;
//                default:
//                    throw new IllegalArgumentException("Invalid clock state: " + theState.name());
//            }
//        });
        ThreadingUtil::runOnLayoutWithJmriException(new ActionClock_run(_clockTime, theState));
    }

    //@Override
    /*public*/  FemaleSocket* ActionClock::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ActionClock::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ActionClock::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "ActionClock");
    }

    //@Override
    /*public*/  QString ActionClock::getLongDescription(QLocale locale) {
        if (getBeanState() == ClockState::SetClock) {
            return tr(/*locale,*/ "%1 to %2").arg(ClockState::toString(_clockState), ActionClock::formatTime(getClockTime()));
        }
        return tr(/*locale,*/ "%1").arg(ClockState::toString( _clockState));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionClock::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionClock::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionClock::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionClock::disposeMe() {
    }


