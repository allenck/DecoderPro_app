#include "timer.h"
#include "exceptions.h"

Timer::Timer(QObject *parent) : QTimer(parent)
{

}
/*public*/ Timer::Timer(int delay, ActionListener* listener, QObject *parent) : QTimer(parent) {
    // compiled code
 setInterval(delay);
 initialDelay = delay;
 connect(this, SIGNAL(timeout()), listener, SLOT(actionPerformed()));
}
/*public*/ void Timer::setDelay(int delay) {
    // compiled code
 setInterval(delay);
}

/*public*/ int Timer::getDelay() {
    // compiled code
 return QTimer::interval();
}

/*public*/ void Timer::setInitialDelay(int initialDelay) {
 this->initialDelay = initialDelay;
}

/*public*/ int Timer::getInitialDelay() {
  return initialDelay;
}

/*public*/ void Timer::setRepeats(bool flag) {
  setSingleShot(!flag);
}

/*public*/ bool Timer::isRepeats() {
 return !isSingleShot();
}

/*public*/ bool Timer::start() {
 QTimer::start(initialDelay);
 return true;
}

/*public*/ bool Timer::reStart() {
 QTimer::start(interval());
 return true;
}

/*public*/ bool Timer::stop() {
 QTimer::stop();
 throw InterruptedException();
}

/*public*/ bool Timer::isRunning()
{
 return QTimer::isActive();
}
