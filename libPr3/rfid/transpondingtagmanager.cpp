#include "transpondingtagmanager.h"
#include "loggerfactory.h"
#include "conflictingsystemconnectionmemo.h"
#include "transpondingtag.h"
#include "defaultidtagmanagerxml.h"

/**
 * Concrete implementation for the Internal {@link jmri.IdTagManager}
 * interface that manages TranspondingTags.
 *
 * @author Kevin Dickerson Copyright (C) 2012
 * @since 2.99.4
 */
// /*public*/ class TranspondingTagManager extends jmri.managers.DefaultIdTagManager {

    //@SuppressWarnings("deprecation")
    /*public*/ TranspondingTagManager::TranspondingTagManager(QObject *parent)
     : DefaultIdTagManager(new ConflictingSystemConnectionMemo("L", "LocoNet", parent))
    {
        //super(new jmri.jmrix.ConflictingSystemConnectionMemo("L", "LocoNet")); // NOI18N
        InstanceManager::store(this, "TranspondingTagManager");
    }

    //@Override
    /*protected*/ NamedBean *TranspondingTagManager::createNewIdTag(QString systemName, QString userName) {
        if (!systemName.startsWith(getSystemPrefix() + typeLetter() )) {
            systemName = getSystemPrefix() + typeLetter() + systemName;
        }
        return new TranspondingTag(systemName, userName);
    }

    //@Override
    /*public*/ DefaultIdTag *TranspondingTagManager::newIdTag(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        if (log->isDebugEnabled()) {
            log->debug("new IdTag:"
                    + ((systemName == "") ? "null" : systemName)
                    + ";" + ((userName == "") ? "null" : userName));
        }
        // return existing if there is one
        NamedBean* s;
        if ((userName != "") && ((s = (TranspondingTag*)getByUserName(userName)) != nullptr)) {
            if (getBySystemName(systemName) != s) {
                log->error("inconsistent user (" + userName + ") and system name (" + systemName + ") results; userName related to (" + s->getSystemName() + ")");
            }
            return (DefaultIdTag*)s;
        }
        if ((s = (TranspondingTag*) getBySystemName(systemName)) != nullptr) {
            if ((s->getUserName() == "") && (userName != "")) {
                s->setUserName(userName);
            } else if (userName != "") {
                log->warn("Found IdTag via system name (" + systemName
                        + ") with non-null user name (" + userName + ")");
            }
            return (DefaultIdTag*)s;
        }

        // doesn't exist, make a new one
        s = createNewIdTag(systemName, userName);

        // save in the maps
        Register(s);

        // if that failed, blame it on the input arguments
        if (s == nullptr) {
            throw IllegalArgumentException();
        }

        return (DefaultIdTag*)s;
    }

    //@Override
    /*public*/ void TranspondingTagManager::writeIdTagDetails() throw (IOException) {
        if (this->dirty) {
            (new DefaultIdTagManagerXml(this,"TranspondingIdTags.xml"))->store();  //NOI18N
            this->dirty = false;
            log->debug("...done writing IdTag details");
        }
    }

    //@Override
    /*public*/ void TranspondingTagManager::readIdTagDetails() {
        log->debug("reading idTag Details");
        (new DefaultIdTagManagerXml(this,"TranspondingIdTags.xml"))->load();  //NOI18N
        this->dirty = false;
        log->debug("...done reading IdTag details");
    }

    /*private*/ /*static*/ /*final*/ Logger* TranspondingTagManager::log = LoggerFactory::getLogger("TranspondingTagManager");
