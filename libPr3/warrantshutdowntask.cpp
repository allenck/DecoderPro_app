#include "warrantshutdowntask.h"
#include "loggerfactory.h"
#include "roster.h"
#include "warrantpreferences.h"
#include "warrantmanager.h"
#include "instancemanager.h"
#include "rosterspeedprofile.h"
#include "rosterentry.h"
#include "mergeprompt.h"

/**
 *
 * Allows user to decide if (and which) SpeedProfiles to write to the Roster at
 * the end of a session. Locos running warrants have had their speeds measured
 * and this new data may or may not be merged into any existing SpeedProfiles in
 * the Roster.
 * <p>
 *
 * @author Pete cressman Copyright (C) 2017
 */
///*public*/ class WarrantShutdownTask extends AbstractShutDownTask {


/**
 * Constructor specifies the warning message and action to take
 *
 * @param name the name of the task (used in logs)
 */
/*public*/ WarrantShutdownTask::WarrantShutdownTask(QString name) : AbstractShutDownTask(name)
{
    //super(name);
}

/**
 * Take the necessary action.
 *
 * @return true if the shutdown should continue, false to abort.
 */
//@Override
/*public*/ bool WarrantShutdownTask::execute() {
    WarrantPreferences* preferences = WarrantPreferences::getDefault();
    switch ((int)preferences->getShutdown()) {
        case WarrantPreferences::MERGE_ALL:
            if (makeMergeCandidates()) {
                if ( _anomalies->size() > 0) {
                    makeMergeWindow();
                }
                merge();
            }
            break;
        case WarrantPreferences::PROMPT:
            if (makeMergeCandidates()) {
                makeMergeWindow();
                merge();
            }
            break;
        case WarrantPreferences::NO_MERGE:
            // do nothing
            break;
        default:
            log->warn("No choice made for warrant shutdown");
            break;
    }
    return true;
}

/*private*/ bool WarrantShutdownTask::makeMergeCandidates() {
    WarrantManager* manager = static_cast<WarrantManager*>(InstanceManager::getDefault("WarrantManager"));
    _mergeProfiles = manager->getMergeProfiles();
    if (_mergeProfiles == nullptr || _mergeProfiles->isEmpty()) {
        return false;
    }
    QMap<QString, RosterSpeedProfile*>* sessionProfiles = manager->getSessionProfiles();
    if (sessionProfiles == nullptr || sessionProfiles->isEmpty()) {
        return false;
    }
    bool allEmpty = true;
    QListIterator<RosterSpeedProfile*> it(sessionProfiles->values());
    while(it.hasNext()) {
        RosterSpeedProfile* profile = it.next();
        if (profile->hasForwardSpeeds() || profile->hasReverseSpeeds()) {
            allEmpty = false;
            break;
        }
    }
    if (allEmpty) {
        return false;
    }
    _anomalies = new QMap<QString, QMap<int, bool>*>();
    _mergeCandidates = new QMap<QString, bool>();
    QMapIterator<QString,RosterSpeedProfile*> iter( *_mergeProfiles);
    while (iter.hasNext()) {
        iter.next();
        QMap<int, bool>* anomaly = MergePrompt::validateSpeedProfile(iter.value(), iter.key());
        if (anomaly->size() > 0) {
            _anomalies->insert(iter.key(), anomaly);
        }
        _mergeCandidates->insert(iter.key(), (true));
    }
    return true;
}

/*private*/ void WarrantShutdownTask::makeMergeWindow() {
    new MergePrompt(tr("MergeTitle"), _mergeCandidates, _anomalies);
}

/*private*/ void WarrantShutdownTask::merge() {
    QMapIterator<QString, bool> iter (*_mergeCandidates);
    while (iter.hasNext()) {
        iter.next();
        QString id = iter.key();
        if (iter.value()) {
            RosterEntry* rosterEntry = Roster::getDefault()->entryFromTitle(id);
            if (rosterEntry != nullptr) {
                rosterEntry->setSpeedProfile(_mergeProfiles->value(id));
                if (log->isDebugEnabled()) {
                    log->debug(tr("Write SpeedProfile to Roster. id= %1").arg(id));
                }
            } else {
                if (log->isDebugEnabled()) {
                    log->debug(tr("Unable to Write SpeedProfile to Roster. No RosterEntry for %1").arg(id));
                }
            }
        } else {
            if (log->isDebugEnabled()) {
                log->debug(tr("SpeedProfile not merged to Roster. id= %1").arg(id));
            }
        }
    }
    Roster::getDefault()->writeRoster();
}

/*private*/ /*final*/ /*static*/ Logger* WarrantShutdownTask::log = LoggerFactory::getLogger("WarrantShutdownTask");

