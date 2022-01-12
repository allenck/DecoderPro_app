#include "standalonereportermanager.h"
#include "rfidtrafficcontroller.h"
#include "rfidmessage.h"
#include "standalonemessage.h"
#include "standalonereply.h"
#include "rfidsystemconnectionmemo.h"
#include "idtag.h"
#include "idtagmanager.h"
#include "instancemanager.h"
#include "rfidprotocol.h"
#include "loggerfactory.h"
#include "timeoutrfidreporter.h"
#include "rfidsystemconnectionmemo.h"

/**
 * Rfid implementation of a ReporterManager.
 * <P>
 * System names are "FRpppp", where ppp is a representation of the RFID reader.
 * <P>
 * @author Bob Jacobsen Copyright (C) 2008
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
///*public*/ class StandaloneReporterManager extends RfidReporterManager {


    /*public*/ StandaloneReporterManager::StandaloneReporterManager(RfidSystemConnectionMemo* memo, QObject *parent) : RfidReporterManager(memo, parent){
        //super(prefix);
//        this->tc = tc;
//        this->prefix = prefix;
        attach();
    }

    /*private*/ void StandaloneReporterManager::attach() {
        tc->addRfidListener((RfidListener*)this);
    }

    //@Override
    /*protected*/ Reporter* StandaloneReporterManager::createNewReporter(QString systemName, QString userName) {
        log->debug("Create new Reporter: " + systemName);
        if (!(systemName == (prefix + typeLetter() + "[" + tc->getRange() + "]"))) {
            log->warn("Invalid Reporter name: " + systemName + " - out of supported range " + tc->getRange());
            throw  IllegalArgumentException("Invalid Reporter name: " + systemName + " - out of supported range " + tc->getRange());
        }
        TimeoutRfidReporter* r;
        r = new TimeoutRfidReporter(systemName, userName);
        r->addPropertyChangeListener(this);
        return r;
    }

    //@Override
    /*public*/ void StandaloneReporterManager::message(RfidMessage* m) {
        if (m->toString() == ( StandaloneMessage(tc->getAdapterMemo()->getProtocol()->initString(), 0).toString())) {
            log->info("Sent init string: " + m->toString());
        } else {
            RfidReporterManager::message(m);
        }
    }

    //@Override
    /*public*/ /*synchronized*/ void StandaloneReporterManager::reply(RfidReply* r) {
        if (qobject_cast<StandaloneReply*>(r)) {
            processReply((StandaloneReply*) r);
        }
    }

    /*private*/ void StandaloneReporterManager::processReply(StandaloneReply* r) {
        if (!tc->getAdapterMemo()->getProtocol()->isValid(r)) {
            log->warn("Invalid message - skipping " + r->toString());
            return;
        }
        DefaultIdTag* idTag = qobject_cast<IdTagManager*>(InstanceManager::getDefault("IdTagManager"))->provideIdTag(tc->getAdapterMemo()->getProtocol()->getTag(r));
        TimeoutRfidReporter* report = (TimeoutRfidReporter*) provideReporter(prefix + typeLetter() + "1");
        report->notify(idTag);
    }

    /*private*/ /*static*/ /*final*/ Logger* StandaloneReporterManager::log = LoggerFactory::getLogger("StandaloneReporterManager");

