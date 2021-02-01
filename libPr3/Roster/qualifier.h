#ifndef QUALIFIER_H
#define QUALIFIER_H
#include <QObject>
#include "propertychangeevent.h"

class Qualifier : public QObject
{
 Q_OBJECT
public:
 Qualifier() : QObject() {}
    /**
     * Process the current value & do whatever is needed.
     */
    /*public*/ virtual void update() {}

    /**
     * Check whether this Qualifier is currently in the OK,
     * qualified-to-act state.
     *
     * @return true if this Qualifier is currently saying OK
     */
    /*public*/ virtual bool currentDesiredState() {return false;}

    /**
     * Drive the available or not state of the qualified object.
     *<p>Subclasses implement this to control a specific type
     * of qualified object, like a Variable or Pane.
     */
    /*public*/ virtual void setWatchedAvailable(bool /*enable*/) {}

 public slots:
     virtual /*public*/ void propertyChange(PropertyChangeEvent* e) = 0;

};

#endif // QUALIFIER_H
