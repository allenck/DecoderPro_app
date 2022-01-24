#ifndef VERSION_H
#define VERSION_H
#include <QString>
#include "exceptions.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT Version
{
public:
    Version();
    /**
     * Major number changes with large incompatible
     * changes in requirements or API.
     */
    static /*final*/ const /*public*/ int major = 4;

    /**
     * Minor number changes with each production release.
     * Odd is development, even is production.
     */
    static /*final*/ const /*public*/ int minor = 20;

    /* Test number changes with individual releases,
     * generally fastest for test releases. Set 0 for production
     */
    static /*final*/ const /*public*/ int test = 0;
    /* The user who built this release */
    static /*final*/ const /*public*/ QString buildUser;// = "allen";

    /* The SVN revision ID for this release (if known) */
    static /*final*/ const /*public*/ QString revisionId;// = "unknown";

    /* The date/time of this build */
    static /*final*/ const /*public*/ QString buildDate;// = "20131110-1418";

    /* Has this build been created as a possible "official" release? */
    static /*final*/ const /*public*/ bool official;// = false;

    /* Has this build been created from a branch in Subversion? */
    static /*final*/ const /*public*/ bool branched;// = false;
    /*public*/ static QString getModifier() ;
    static /*public*/ QString name();
    static /*public*/ bool isCanonicalVersion(QString version);
    static /*public*/ int compareCanonicalVersions(QString version) throw (IllegalArgumentException) ;
    static /*public*/ int compareCanonicalVersions(QString version1, QString version2) throw (IllegalArgumentException);
    static /*public*/ QString getCanonicalVersion();
    static /*public*/ QString getCopyright();

};

#endif // VERSION_H
