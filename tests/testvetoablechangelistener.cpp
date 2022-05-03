#include "testvetoablechangelistener.h"

TestVetoableChangeListener::TestVetoableChangeListener()
{

}
// /*public*/  class TestVetoableChangeListener implements VetoableChangeListener {


    //@Override
    /*public*/  void TestVetoableChangeListener::vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ {
        events.append(evt);
        if (_throwNext != "") {
            QString mess = _throwNext;
            _throwNext = "";
            throw new PropertyVetoException(mess, evt);
        }
    }

    /*public*/  PropertyChangeEvent* TestVetoableChangeListener::getLastEvent() {
        return events.isEmpty() ? nullptr : events.at(events.size() - 1);
    }

    /*public*/  QList<PropertyChangeEvent*> TestVetoableChangeListener::getEvents() {
        return QList<PropertyChangeEvent*>(events);
    }

    /*public*/  void TestVetoableChangeListener::clear() {
        events.clear();
    }

    /**
     * Throw on the next event.
     *
     * @param mess message to throw; will not throw if null
     */
    /*public*/  void TestVetoableChangeListener::throwNext(QString mess) {
        _throwNext = mess;
    }

    /*public*/  bool TestVetoableChangeListener::willThrowNext() {
        return _throwNext != "";
    }
