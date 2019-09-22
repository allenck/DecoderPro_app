#include "jmriclientlightmanager.h"
#include "jmriclientsystemconnectionmemo.h"
#include "jmriclientlight.h"

/**
 * Implement light manager for JMRIClient systems
 * <P>
 * System names are "prefixnnn", where prefix is the system prefix and nnn is
 * the light number without padding.
 *
 * @author Paul Bender Copyright (C) 2010
  */
///*public*/ class JMRIClientLightManager extends jmri.managers.AbstractLightManager {


    /*public*/ JMRIClientLightManager::JMRIClientLightManager(JMRIClientSystemConnectionMemo* memo, QObject *parent)
 : AbstractLightManager(memo,parent){
        this->memo = memo;
        this->prefix = memo->getSystemPrefix();
    }

    //@Override
    /*public*/ QString JMRIClientLightManager::getSystemPrefix() {
        return prefix;
    }

    //@Override
    /*public*/ Light* JMRIClientLightManager::createNewLight(QString systemName, QString userName) {
        Light* t;
        int addr = (systemName.mid(prefix.length() + 1).toInt());
        t = new JMRIClientLight(addr, memo);
        t->setUserName(userName);
        return t;
    }

    /**
     * public method to validate system name format returns 'true' if system
     * name has a valid format, else returns 'false'
     */
    //@Override
    /*public*/ Manager::NameValidity JMRIClientLightManager::validSystemNameFormat(QString systemName) {
        return ((systemName.startsWith(prefix + "l")
                || systemName.startsWith(prefix + "L"))
                && (systemName.mid(prefix.length()+ 1).toInt()) > 0) ? NameValidity::VALID : NameValidity::INVALID;
    }

    /**
     * public method to validate system name for configuration returns 'true' if
     * system name has a valid meaning in current configuration, else returns
     * 'false' for now, this method always returns 'true'; it is needed for the
     * Abstract Light class
     */
    //@Override
    /*public*/ bool JMRIClientLightManager::validSystemNameConfig(QString /*systemName*/) {
        return (true);
    }
