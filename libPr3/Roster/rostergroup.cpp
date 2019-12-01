#include "rostergroup.h"
#include "roster.h"
#include "rosterentry.h"

//RosterGroup::RosterGroup(QObject *parent) :
//  RosterObject(parent)
//{
//}
/**
 * A RosterGroup object contains information about groupings of entries within
 * the {@link jmri.jmrit.roster.Roster}.
 *
 * This object allows groups to be manipulated as Java beans.
 *
 * @author Randall Wood <randall.h.wood@alexandriasoftware.com>
 */
///*public*/ class RosterGroup extends Bean implements RosterObject {


/**
 * Create a roster group.
 *
 * This sets the name without calling {@link #setName(java.lang.String) }.
 *
 * @param name
 */
/*public*/ RosterGroup::RosterGroup(QString name, QObject *parent) :
    Bean(parent) {
    this->name = name;
}

/**
 * Get the list of entries associated with this group.
 *
 * @return the list of entries or an empty list.
 */
/*public*/ QList<RosterEntry*> RosterGroup::getEntries() {
    return Roster::getDefault()->getEntriesInGroup(this->getName());
}

/**
 * Get the RosterGroup's name.
 *
 * Use {@link #getDisplayName() } to get the name to be displayed to a user.
 *
 * @return the name
 * @see #getDisplayName()
 */
/*public*/ QString RosterGroup::getName() {
    return this->name;
}

/**
 * Set the RosterGroup's name, changing it in every entry associated with
 * the roster.
 *
 * @param newName the new name
 */
/*public*/ void RosterGroup::setName(QString newName)
{
 if (Roster::getDefault()->getRosterGroups().contains(newName))
 {
  return;
 }
 QString oldName = this->name;
 QString oldGroup = Roster::getRosterGroupProperty(oldName);
 QString newGroup = Roster::getRosterGroupProperty(newName);
 //Roster::getDefault()->getRosterGroups().insert(newName, Roster::getDefault()->getRosterGroups().remove(oldName));
 Roster::getDefault()->getRosterGroups().insert(newName, new RosterGroup(newName)); // not sure about this ACK
 Roster::getDefault()->getRosterGroups().remove(oldName);
 foreach (RosterEntry* re, this->getEntries())
 {
  re->putAttribute(newGroup, "yes"); // NOI18N
  re->deleteAttribute(oldGroup);
 }
 this->name = newName;
 Roster::getDefault()->rosterGroupRenamed(oldName, newName);
}

//@Override
/*public*/ QString RosterGroup::getDisplayName() {
    return this->getName();
}

/**
 * Flag indicating that this RosterGroup can be edited by the user.
 *
 * The default implementation always returns true.
 *
 * @return true if the group can be edited.
 */
/*public*/ bool RosterGroup::canEdit() {
    return true;
}

/**
 * Flag indicating that this RosterGroup can be deleted by the user.
 *
 * The default implementation always returns true.
 *
 * @return true if the group can be deleted.
 */
/*public*/ bool RosterGroup::canDelete() {
    return true;
}

/**
 * Flag indicating that this RosterGroup can be duplicated by the user.
 *
 * The default implementation always returns true.
 *
 * @return true if the group can be copied.
 */
/*public*/ bool RosterGroup::canCopy() {
    return true;
}

/**
 * Flag indicating that the contents of this RosterGroup can be changed by
 * the user.
 *
 * The default implementation always returns true.
 *
 * @return true if entries in this group can be changed.
 */
/*public*/ bool RosterGroup::canChangeContents() {
    return true;
}
