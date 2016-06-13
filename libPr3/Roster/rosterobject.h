#ifndef ROSTEROBJECT_H
#define ROSTEROBJECT_H
#include "beaninterface.h"

/**
 * Provide a common class for Roster entries and groups to inherit from. This
 * supports building tree-like user interfaces for Roster entries and groups.
 *
 * @author Randall Wood <randall.h.wood@alexandriasoftware.com>
 */
/*public*/ /*interface*/class RosterObject : public BeanInterface
{
public:
 RosterObject(QObject* parent) : BeanInterface(parent) {}
    /**
     * Get the formatted single-line String for displaying the object.
     *
     * @return a formatted name
     */
 /*abstract*/ /*public*/ virtual QString getDisplayName() { return "";}
};

#endif // ROSTEROBJECT_H
