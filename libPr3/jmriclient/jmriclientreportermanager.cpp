#include "jmriclientreportermanager.h"
#include "jmriclientsystemconnectionmemo.h"
#include "reporter.h"
#include "jmriclientreporter.h"

/**
 * Implement reporter manager for JMRIClient systems
 * <P>
 * System names are "prefixnnn", where prefix is the system prefix and nnn is
 * the reporter number without padding.
 *
 * @author Paul Bender Copyright (C) 2011
  */
// /*public*/ class JMRIClientReporterManager extends jmri.managers.AbstractReporterManager {


    /*public*/ JMRIClientReporterManager::JMRIClientReporterManager(JMRIClientSystemConnectionMemo* memo, QObject *parent)
    : AbstractReporterManager(memo, parent)
    {
        this->memo = memo;
        this->prefix = memo->getSystemPrefix();
    }

    //@Override
    /*public*/ QString JMRIClientReporterManager::getSystemPrefix() {
        return prefix;
    }

    //@Override
    /*public*/ Reporter* JMRIClientReporterManager::createNewReporter(QString systemName, QString userName) {
        Reporter* t;
        int addr = (systemName.mid(prefix.length() + 1).toInt());
        t = new JMRIClientReporter(addr, memo);
        t->setUserName(userName);
        return t;
    }
