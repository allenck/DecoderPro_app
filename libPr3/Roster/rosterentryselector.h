#ifndef ROSTERENTRYSELECTOR_H
#define ROSTERENTRYSELECTOR_H
#include "propertychangelistener.h"
#include "rosterentry.h"
#include "rosterentryselector.h"
/**
 * The getter method for a roster entry selection.
 * <p>
 * Classes that implement this interface will be able to provide a source for
 * getting a roster entry or entries to other objects that manipulate roster entries.
 * <p>
 * <b>Note:</b> Classes implementing this interface must fire a propertyChangeEvent
 * for the <i>selectedRosterEntries</i> property whenever the selected roster entries
 * change.
 *
 * @author rhwood
 */

/*public*/ /*interface*/ class LIBPR3SHARED_EXPORT RosterEntrySelector
{
public:
    //static /*final*/ QString SELECTED_ROSTER_ENTRIES;
/**
 * Get the currently selected roster entries. Since the selection could contain
 * multiple roster entries, this returns an array of RosterEntry instead of a
 * single RosterEntry.
 *
 * @return an array of RosterEntries
 */
/*public*/ virtual QList<RosterEntry*>* getSelectedRosterEntries() {return NULL;}

/*public*/ virtual void	addPropertyChangeListener(PropertyChangeListener* /*listener*/) {}

/*public*/ virtual void	addPropertyChangeListener(QString /*propertyName*/, PropertyChangeListener* /*listener*/) {}

/*public*/ virtual void removePropertyChangeListener(PropertyChangeListener* /*listener*/) {}

/*public*/ virtual void removePropertyChangeListener(QString /*propertyName*/, PropertyChangeListener* /*listener*/) {}
private:

};
Q_DECLARE_INTERFACE(RosterEntrySelector, "RosterEntrySelector")
///*final*/ QString RosterEntrySelector::SELECTED_ROSTER_ENTRIES = "selectedRosterEntries";

#endif // ROSTERENTRYSELECTOR_H
