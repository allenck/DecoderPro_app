#include "abstractmetermanagerxml.h"
#include "loggerfactory.h"
#include "metermanager.h"
#include "defaultmeter.h"
#include "instancemanager.h"

/**
 * Provides the basic load and store functionality for configuring
 * MeterManagers, working with AbstractMeterManagers.
 * <p>
 * This class cannot create Meters, so the meters must either be already
 * created, for example by the connections, in which case this class only
 * updates the data of the meter, for example its user name.
 * Or this class is overridden by a class that knows how to create the meters.
 *
 * @author Bob Jacobsen      Copyright (C) 2002, 2008
 * @author Daniel Bergqvist  Copyright (C) 2020
 */
///*public*/ class AbstractMeterManagerXml extends AbstractNamedBeanManagerConfigXML {

    /*public*/ AbstractMeterManagerXml::AbstractMeterManagerXml(QObject *parent)
     : AbstractNamedBeanManagerConfigXML(parent)
    {
    }

    /**
     * Default implementation for storing the contents of a MeterManager.
     *
     * @param o Object to store, of type MeterManager
     * @return Element containing the complete info
     */
    //@Override
    /*public*/ QDomElement AbstractMeterManagerXml::store(QObject* o) {
        QDomElement meters = doc.createElement("meters");
        setStoreElementClass(meters);
        MeterManager* mm = (MeterManager*) o;
        if (mm != nullptr) {
            QSet<NamedBean*> memList = mm->getNamedBeanSet();
            // don't return an element if there are no meters to include
            if (memList.isEmpty()) {
                return QDomElement();
            }
            // store the meters
            for (NamedBean* nb : memList) {
             DefaultMeter* m = (DefaultMeter*)nb;
                QString mName = m->getSystemName();
                log->debug(tr("system name is %1").arg(mName));

                QDomElement elem = doc.createElement("meter");
                elem.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(mName)));

                // store common part
                storeCommon(m, elem);

                log->debug(tr("store Meter %1").arg(mName));
                meters.appendChild(elem);
            }
        }
        return meters;
    }

    /**
     * Subclass provides implementation to create the correct top element,
     * including the type information. Default implementation is to use the
     * local class here.
     *
     * @param meters The top-level element being created
     */
    /*public*/ void AbstractMeterManagerXml::setStoreElementClass(QDomElement meters) {
        meters.setAttribute("class", /*this.getClass().getName()*/"jmri.managers.configurexml.AbstractMeterManagerXml");  // NOI18N
    }

    /**
     * Create a MeterManager object of the correct class, then register and
     * fill it.
     *
     * @param sharedMeters  Shared top level Element to unpack.
     * @param perNodeMemories Per-node top level Element to unpack.
     * @return true if successful
     * @throws jmri.configurexml.JmriConfigureXmlException if error during load.
     */
    //@Override
    /*public*/ bool AbstractMeterManagerXml::load(QDomElement sharedMeters, QDomElement perNodeMemories) throw (JmriConfigureXmlException) {
        loadMeters(sharedMeters);
        return true;
    }

    /**
     * Utility method to load the individual Meter objects. If there's no
     * additional info needed for a specific Meter type, invoke this with the
     * parent of the set of Meter elements.
     *
     * @param meters Element containing the Meter elements to load.
     */
    /*public*/ void AbstractMeterManagerXml::loadMeters(QDomElement meters) {
        QDomNodeList meterList = meters.elementsByTagName("meter");
        log->debug(tr("Found %1 Meter objects").arg(meterList.size()));
        MeterManager* mm = (MeterManager*)InstanceManager::getDefault("MeterManager");

        //for (Element el : meterList)
        for(int i=0; i < meterList.count(); i++)
        {
         QDomElement el = meterList.at(i).toElement();
            QString sysName = getSystemName(el);
            if (sysName.isNull()) {
                log->warn(tr("unexpected null in systemName %1").arg(el.tagName()));
                break;
            }

            QString userName = getUserName(el);

            checkNameNormalization(sysName, userName, mm);

            log->debug(tr("get Meter: (%1)($2)").arg(sysName).arg((userName.isNull() ? "<null>" : userName)));
            Meter* m = (Meter*)mm->getBySystemName(sysName);
            if (m != nullptr) {
                ((DefaultMeter*)m)->setUserName(userName);
                // load common parts
                loadCommon((NamedBean*)m, el);
            } else {
                log->debug(tr("Meter (%1) does not exists and cannot be created").arg(sysName));
            }
        }
    }

    //@Override
    /*public*/ int AbstractMeterManagerXml::loadOrder() const
    {
        return ((MeterManager*)InstanceManager::getDefault("MeterManager"))->getXMLOrder();
    }

    /*private*/ /*final*/ /*static*/ Logger* AbstractMeterManagerXml::log = LoggerFactory::getLogger("AbstractMeterManagerXml");
