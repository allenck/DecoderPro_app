#include "expressionclock.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "calendar.h"
#include "logixng/conditionalng.h"
#include "timertask.h"
#include "timerutil.h"
#include "system.h"

/**
 * This expression is a clock.
 *
 * @author Daniel Bergqvist Copyright 2020
 * @author Dave Sand Copyright 2021
 */
// /*public*/ class ExpressionClock extends AbstractDigitalExpression implements PropertyChangeListener {



    /*public*/ ExpressionClock::ExpressionClock(QString sys, QString user, QObject* parent)
     : AbstractDigitalExpression(sys, user, parent){
        //super(sys, user);
      setObjectName("ExpressionClock");
    }

    //@Override
    /*public*/ Base* ExpressionClock::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/ {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ExpressionClock* copy = new ExpressionClock(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->set_Is_IsNot(_is_IsNot);
        copy->setType(_type);
        copy->setRange(_beginTime, _endTime);
        return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ExpressionClock::getCategory() {
        return Category::ITEM;
    }

    /*public*/ void ExpressionClock::set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) {
        _is_IsNot = is_IsNot;
    }

    /*public*/ Is_IsNot_Enum::VAL ExpressionClock::get_Is_IsNot() {
        return _is_IsNot;
    }

    /*public*/ void ExpressionClock::setType(Type::VAL type) {
        assertListenersAreNotRegistered(log, "setType");
        _type = type;

        if (_type == Type::FastClock) {
            _fastClock =( Timebase*)InstanceManager::getDefault("Timebase");
        } else {
            _fastClock = nullptr;
        }
    }

    /*public*/ ExpressionClock::Type::VAL ExpressionClock::getType() {
        return _type;
    }

    /*public*/ void ExpressionClock::setRange(int beginTime, int endTime) {
        assertListenersAreNotRegistered(log, "setRange");
        _beginTime = beginTime;
        _endTime = endTime;
    }

    /*public*/ int ExpressionClock::getBeginTime() {
        return _beginTime;
    }

    /*public*/ int ExpressionClock::getEndTime() {
        return _endTime;
    }

    /**
     * Convert minutes since midnight to hh:mm.
     * @param minutes The number of minutes from 0 to 1439.
     * @return time formatted as hh:mm.
     */
    /*public*/ /*static*/ QString ExpressionClock::formatTime(int minutes) {
        QString hhmm = "00:00";
        if (minutes >= 0 && minutes < 1440) {
            hhmm = QString::asprintf("%02d:%02d",
                    minutes / 60,
                    minutes % 60);
        }
        return hhmm;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ExpressionClock::evaluate() {
        bool result;

        Calendar* currentTime = nullptr;

        switch (_type) {
            case Type::SystemClock:
                currentTime = Calendar::getInstance();
                break;

            case Type::FastClock:
                if (_fastClock == nullptr) return false;
                currentTime = Calendar::getInstance();
                currentTime->setTime(_fastClock->getTime());
                break;

            default:
                throw new UnsupportedOperationException("_type has unknown value: " + Type::toString(_type));
        }

        int currentMinutes = (currentTime->get(Calendar::HOUR_OF_DAY) * 60) + currentTime->get(Calendar::MINUTE);
        // check if current time is within range specified
        if (_beginTime <= _endTime) {
            // range is entirely within one day
            result = (_beginTime <= currentMinutes) && (currentMinutes <= _endTime);
        } else {
            // range includes midnight
            result = _beginTime <= currentMinutes || currentMinutes <= _endTime;
        }

        if (_is_IsNot == Is_IsNot_Enum::Is) {
            return result;
        } else {
            return !result;
        }
    }

    //@Override
    /*public*/ FemaleSocket* ExpressionClock::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ExpressionClock::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ExpressionClock::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Clock");
    }

    //@Override
    /*public*/ QString ExpressionClock::getLongDescription(QLocale locale) {
        switch (_type) {
            case Type::SystemClock:
                return tr(/*locale,*/ "Clock_Long_SystemClock").arg(Is_IsNot_Enum::toString(_is_IsNot),
                        ExpressionClock::formatTime(_beginTime),
                        ExpressionClock::formatTime(_endTime));

            case Type::FastClock:
                return tr(/*locale,*/ "Fast clock %1 between %2 and %3").arg(Is_IsNot_Enum::toString(_is_IsNot),
                        ExpressionClock::formatTime(_beginTime),
                        ExpressionClock::formatTime(_endTime));

            default:
                throw new RuntimeException("Unknown value of _timerType: "+Type::toString(_type));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionClock::setup() {
        // Do nothing
    }

    /** {@inheritDoc}
     * The SystemClock listener creates a timer on the first call.  Subsequent calls
     * enabled timer processing.
     */
    //@Override
    /*public*/ void ExpressionClock::registerListenersForThisClass() {
        if (!_listenersAreRegistered) {
            switch (_type) {
                case Type::SystemClock:
                    scheduleTimer();
                    break;

                case Type::FastClock:
                _fastClock->addPropertyChangeListener("time", this);
                    break;

                default:
                    throw new UnsupportedOperationException("_type has unknown value: " + Type::toString(_type));
            }

            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc}
     * The SystemClock timer flag is set false to suspend processing of timer events.  The
     * timer keeps running for the duration of the JMRI session.
     */
    //@Override
    /*public*/ void ExpressionClock::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            switch (_type) {
                case Type::SystemClock:
                    if (timerTask != nullptr) timerTask->cancel();
                    break;

                case Type::FastClock:
                if (_fastClock != nullptr) _fastClock->removePropertyChangeListener("time", this);
                    break;

                default:
                    throw new UnsupportedOperationException("_type has unknown value: " + Type::toString(_type));
            }

            _listenersAreRegistered = false;
        }
    }

    /*private*/ void ExpressionClock::scheduleTimer() {
        timerTask = new EC_TimerTask(this);
//        {
//            //@Override
//            /*public*/ void run() {
//                propertyChange(null);
//            }
//        };
        TimerUtil::schedule(timerTask, System::currentTimeMillis() % milisInAMinute, milisInAMinute);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionClock::propertyChange(PropertyChangeEvent* evt) {
    getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionClock::disposeMe() {
        if (timerTask != nullptr) timerTask->cancel();
    }

//    /*public*/ enum Type::VAL {
//        FastClock(Bundle.getMessage("ClockTypeFastClock")),
//        SystemClock(Bundle.getMessage("ClockTypeSystemClock"));

//        /*private*/ final QString _text;

//        /*private*/ Type(QString text) {
//            this._text = text;
//        }

//        //@Override
//        /*public*/ QString ExpressionClock::toString() {
//            return _text;
//        }


    /*private*/ /*final*/ /*static*/ Logger* ExpressionClock::log = LoggerFactory::getLogger("ExpressionClock");
