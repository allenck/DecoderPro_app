#include "timesincemidnight.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "analogexpressionmanager.h"
#include "timebase.h"
#include "calendar.h"
#include "runtimeexception.h"
#include "timerutil.h"
#include "system.h"
#include "conditionalng.h"
/**
 * This expression returns the number of minutes since midnight for the fast
 * clock or the system clock.
 *
 * @author Daniel Bergqvist Copyright 2020
 * @author Dave Sand Copyright 2021
 */
// /*public*/  class TimeSinceMidnight extends AbstractAnalogExpression implements PropertyChangeListener {

    /*public*/  TimeSinceMidnight::TimeSinceMidnight(QString sys, QString user, QObject *parent) : AbstractAnalogExpression(sys, user, parent) {
        //super(sys, user);
    }

    //@Override
    /*public*/  Base* TimeSinceMidnight::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/ {
        AnalogExpressionManager* manager = (AnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        QString sysName = systemNames.value(AbstractBase::getSystemName());
        QString userName = userNames.value(AbstractBase::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        TimeSinceMidnight* copy = new TimeSinceMidnight(sysName, userName);
        copy->AbstractBase::setComment(AbstractBase::getComment());
        copy->setType(_type);
        return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* TimeSinceMidnight::getCategory() {
        return Category::ITEM;
    }

    /*public*/  void TimeSinceMidnight::setType(Type::TYPE type) {
        assertListenersAreNotRegistered(log, "setType");
        _type = type;

        if (_type == Type::FastClock) {
            _fastClock = (Timebase*)InstanceManager::getDefault("Timebase");
        } else {
            _fastClock = nullptr;
        }
    }

    /*public*/  TimeSinceMidnight::Type::TYPE TimeSinceMidnight::getType() {
        return _type;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  double TimeSinceMidnight::evaluate() {
        Calendar* currentTime = nullptr;

        switch (_type) {
            case Type::TYPE::SystemClock:
                currentTime = Calendar::getInstance();
                break;

            case Type::TYPE::FastClock:
                if (_fastClock == nullptr) return 0;
                currentTime = Calendar::getInstance();
                currentTime->setTime(_fastClock->getTime());
                break;

            default:
                throw new UnsupportedOperationException("_type has unknown value: " + Type::toString(_type));
        }

        return (currentTime->get(Calendar::HOUR_OF_DAY) * 60) + currentTime->get(Calendar::MINUTE);
    }

    //@Override
    /*public*/  FemaleSocket* TimeSinceMidnight::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int TimeSinceMidnight::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString TimeSinceMidnight::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Minutes since midnight");
    }

    //@Override
    /*public*/  QString TimeSinceMidnight::getLongDescription(QLocale locale) {
        switch (_type) {
            case Type::SystemClock:
                return tr(/*locale,*/ "Minutes since midnight system clock");

            case Type::FastClock:
                return tr(/*locale, */"Minutes since midnight by fast clock");

            default:
                throw new RuntimeException(QString("Unknown value of _timerType: "+Type::toString(_type)));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void TimeSinceMidnight::setup() {
        // Do nothing
    }

    /** {@inheritDoc}
     * The SystemClock listener creates a timer on the first call.  Subsequent calls
     * enabled timer processing.
     */
    //@Override
    /*public*/  void TimeSinceMidnight::registerListenersForThisClass() {
        if (!_listenersAreRegistered) {
            switch (_type) {
                case Type::SystemClock:
                    scheduleTimer();
                    break;

                case Type::FastClock:
                    _fastClock->addPropertyChangeListener("time", this);
                    break;

                default:
                    throw new UnsupportedOperationException(QString("_type has unknown value: " + Type::toString(_type)));
            }

            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc}
     * The SystemClock timer flag is set false to suspend processing of timer events.  The
     * timer keeps running for the duration of the JMRI session.
     */
    //@Override
    /*public*/  void TimeSinceMidnight::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            switch (_type) {
                case Type::SystemClock:
                    if (timerTask != nullptr) timerTask->cancel();
                    break;

                case Type::FastClock:
                    if (_fastClock != nullptr) _fastClock->removePropertyChangeListener("time", this);
                    break;

                default:
                    throw new UnsupportedOperationException(QString("_type has unknown value: " +Type::toString(_type)));
            }

            _listenersAreRegistered = false;
        }
    }

    /*private*/ void TimeSinceMidnight::scheduleTimer() {
#if 0

        timerTask = new TimerTask() {
            //@Override

            /*public*/  void run() {
                propertyChange(nullptr);
            }
        };
#endif

        TimerUtil::schedule(timerTask, System::currentTimeMillis() % millisInAMinute, millisInAMinute);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void TimeSinceMidnight::propertyChange(PropertyChangeEvent* evt) {
        getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void TimeSinceMidnight::disposeMe() {
        if (timerTask != nullptr) timerTask->cancel();
    }

//    /*public*/  enum Type {
//        FastClock(Bundle.getMessage("ClockTypeFastClock")),
//        SystemClock(Bundle.getMessage("ClockTypeSystemClock"));

//        /*private*/ /*final*/ String _text;

//        /*private*/ Type(QString text) {
//            this._text = text;
//        }

//        //@Override
//        /*public*/  QString toString() {
//            return _text;
//        }

//    }

    /*private*/ /*final*/ /*static*/ Logger* TimeSinceMidnight::log = LoggerFactory::getLogger("TimeSinceMidnight");
