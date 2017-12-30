#ifndef JSONROSTER_H
#define JSONROSTER_H

class QString;
/**
 * Constants for JSON handling of the JMRI Roster.
 *
 * @author Randall Wood
 */
/*public*/ class JsonRoster {
public:
    /**
     * {@value #ROSTER}
     */
    /*public*/ static  QString ROSTER;// = "roster"; // NOI18N
    /**
     * {@value #ROSTER_ENTRY}
     */
    /*public*/ static /*final*/ QString ROSTER_ENTRY;// = "rosterEntry"; // NOI18N
    /**
     * {@value #ROSTER_GROUP}
     */
    /*public*/ static /*final*/ QString ROSTER_GROUP;// = "rosterGroup"; // NOI18N
    /**
     * {@value #ROSTER_GROUPS}
     */
    /*public*/ static /*final*/ QString ROSTER_GROUPS;// = "rosterGroups"; // NOI18N
    /**
     * {@value #ATTRIBUTES}
     */
    /*public*/ static /*final*/ QString ATTRIBUTES;// = "attributes"; // NOI18N
    /**
     * {@value #DATE_MODIFIED}
     */
    /*public*/ static /*final*/ QString DATE_MODIFIED;// = "dateModified"; // NOI18N
private:
    /**
     * Unusable constructor, made private to avoid public documentation.
     */
    /*private*/ JsonRoster() {
    }
};
#endif // JSONROSTER_H
