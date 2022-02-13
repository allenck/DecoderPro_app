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
        setObjectName("TranspondingTagManager");
        storeInstance();
    }

    /*final*/ void TranspondingTagManager::storeInstance(){
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
        TranspondingTag* s;
        if (userName != "") {
            s = (TranspondingTag*)getByUserName(userName);
            if (s != nullptr) {
                if (getBySystemName(systemName) != s) {
                    log->error(tr("inconsistent user (%1) and system name (%2) results; userName related to (%3)").arg(userName, systemName, s->getSystemName()));
                }
                return s;
            }
        }
        s = (TranspondingTag*) getBySystemName(systemName);
        if (s != nullptr) {
            if ((s->getUserName() == "") && (userName != "")) {
                s->setUserName(userName);
            } else if (userName != "") {
                log->warn(tr("Found IdTag via system name (%1) with non-null user name (%2)").arg(systemName, userName));
            }
            return s;
        }
        // doesn't exist, make a new one
        s =(TranspondingTag*) createNewIdTag(systemName, userName);

        // save in the maps
        Register(s);

        // if that failed, blame it on the input arguments
        if (s == nullptr) {
            throw new IllegalArgumentException();
        }

        return (DefaultIdTag*)s;
    }

    //@Override
    /*public*/ void TranspondingTagManager::writeIdTagDetails() /*throw (IOException)*/ {
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
