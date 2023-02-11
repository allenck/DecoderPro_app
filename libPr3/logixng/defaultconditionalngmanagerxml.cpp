#include "defaultconditionalngmanagerxml.h"
#include "defaultconditionalngmanager.h"
#include "instancemanager.h"
#include "defaultlogixngmanager.h"
#include "defaultlogixng.h"
#include "defaultconditionalng.h"
#include "loggerfactory.h"
#include "logixng_thread.h"
#include "defaultfemaledigitalactionsocket.h"
#include "defaultconditionalngmanager.h"

/**
 * Provides the functionality for configuring ConditionalNGManagers
 * <P>
 *
 * @author Dave Duchamp     Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 * @author Dave Sand        Copyright (c) 2021
 */
// /*public*/  class DefaultConditionalNGManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

DefaultConditionalNGManagerXml::DefaultConditionalNGManagerXml(QObject *parent)
 : AbstractNamedBeanManagerConfigXML(parent){
 setObjectName("DefaultConditionalNGManagerXml");
}

/**
 * Default implementation for storing the contents of a ConditionalNG_Manager
 *
 * @param o Object to store, of type ConditionalNG_Manager
 * @return Element containing the complete info
 */
//@Override
/*public*/  QDomElement DefaultConditionalNGManagerXml::store(QObject* o) {
    QDomElement conditionalNGs = doc.createElement("LogixNGConditionalNGs");
    setStoreElementClass(conditionalNGs);
    ConditionalNG_Manager* tm = (DefaultConditionalNGManager*) o;
    LogixNG_Manager* lm = (DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");
    if (tm != nullptr) {
        if (lm->getNamedBeanSet().isEmpty()) return QDomElement();
        for (NamedBean* nb : lm->getNamedBeanSet()) {
         DefaultLogixNG* logixNG = (DefaultLogixNG*)nb->self();
            for (int i=0; i < logixNG->getNumConditionalNGs(); i++) {
                DefaultConditionalNG* conditionalNG = logixNG->getConditionalNG(i);

                log->debug("ConditionalNG system name is " + nb->getSystemName());//((DefaultConditionalNG*)conditionalNG->bself())->AbstractNamedBean::getSystemName());  // NOI18N
                bool enabled = conditionalNG->isEnabled();
                QDomElement elem = doc.createElement("ConditionalNG");  // NOI18N
                QDomElement esn;
                elem.appendChild(esn=doc.createElement("systemName"));
                  esn.appendChild(doc.createTextNode(nb->getSystemName()));//(((DefaultConditionalNG*)conditionalNG->bself())->AbstractNamedBean::getSystemName()))));  // NOI18N

                // store common part
                storeCommon(nb, elem);

                QDomElement ethr;
                elem.appendChild(ethr=doc.createElement("thread"));
                ethr.appendChild(doc.createTextNode(
                        QString::number(conditionalNG->getStartupThreadId())));  // NOI18N

                QDomElement e2 = doc.createElement("Socket");
                QDomElement e2sn;
                e2.appendChild(e2sn=doc.createElement("socketName"));
                e2sn.appendChild(doc.createTextNode(conditionalNG->getChild(0)->getName()));
                MaleSocket* socket = conditionalNG->getChild(0)->getConnectedSocket();
                QString socketSystemName;
                if (socket != nullptr) {
                    socketSystemName = socket->getSystemName();
                } else {
                    socketSystemName = ((DefaultConditionalNG*)conditionalNG->bself())->getSocketSystemName();
                }
                if (socketSystemName != "") {
                 QDomElement esn2;
                    e2.appendChild(esn2 =doc.createElement("systemName"));
                      esn2.appendChild(doc.createTextNode(socketSystemName));
                }
                elem.appendChild(e2);

                elem.setAttribute("enabled", enabled ? "yes" : "no");  // NOI18N

                conditionalNGs.appendChild(elem);
            }
        }
    }
    return (conditionalNGs);
}

/**
 * Subclass provides implementation to create the correct top element,
 * including the type information. Default implementation is to use the
 * local class here.
 *
 * @param logixngs The top-level element being created
 */
/*public*/  void DefaultConditionalNGManagerXml::setStoreElementClass(QDomElement logixngs) {
    logixngs.setAttribute("class", "jmri.jmrit.logicng.implementation.configurexml.DefaultConditionalNGManagerXml");  // NOI18N
}

/**
 * Create a ConditionalNG_Manager object of the correct class, then register and
 * fill it.
 *
 * @param sharedConditionalNG  Shared top level Element to unpack.
 * @param perNodeConditionalNG Per-node top level Element to unpack.
 * @return true if successful
 */
//@Override
/*public*/  bool DefaultConditionalNGManagerXml::load(QDomElement sharedConditionalNG, QDomElement perNodeConditionalNG) {
    // create the master object
    replaceConditionalNGManager();
    // load individual sharedLogix
    loadConditionalNGs(sharedConditionalNG);
    return true;
}

/**
 * Utility method to load the individual ConditionalNG objects. If there's no
 * additional info needed for a specific logixng type, invoke this with the
 * parent of the set of ConditionalNG elements.
 *
 * @param conditionalNGs Element containing the ConditionalNG elements to load.
 */
/*public*/  void DefaultConditionalNGManagerXml::loadConditionalNGs(QDomElement conditionalNGs) {
    QDomNodeList conditionalNGList = conditionalNGs.elementsByTagName("ConditionalNG");  // NOI18N
    log->debug("Found " + QString::number(conditionalNGList.size()) + " ConditionalNGs");  // NOI18N
    ConditionalNG_Manager* tm = (DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager");

    for (int i = 0; i < conditionalNGList.size(); i++) {

        QDomElement conditionalNG_Element = conditionalNGList.at(i).toElement();

        QString sysName = getSystemName(conditionalNG_Element);
        if (sysName == "") {
            log->warn("unexpected null in systemName " + conditionalNG_Element.tagName());  // NOI18N
            break;
        }

        QString userName = getUserName(conditionalNG_Element);

        int threadId = LogixNG_Thread::DEFAULT_LOGIXNG_THREAD;
        QDomElement threadElem = conditionalNG_Element.firstChildElement("thread");
        if (!threadElem.isNull()) threadId = (threadElem.text().trimmed().toInt());

        QString enabled = "";
        if (conditionalNG_Element.attribute("enabled") != "") {  // NOI18N
            enabled = conditionalNG_Element.attribute("enabled");  // NOI18N
        }
        log->debug("create ConditionalNG: (" + sysName + ")("  // NOI18N
                + (userName == "" ? "<null>" : userName) + ")");  // NOI18N

        // Create a new ConditionalNG but don't setup the initial tree.
        LogixNG* logixNG = tm->getParentLogixNG(sysName);
        if (logixNG == nullptr) {
            log->warn(tr("unexpected null while finding parent logixNG for '%1'").arg(conditionalNG_Element.tagName()));  // NOI18N
            break;
        }

        DefaultConditionalNG* conditionalNG =
                (DefaultConditionalNG*)tm->createConditionalNG(logixNG, sysName, userName, threadId);

        if (conditionalNG != nullptr) {
            // load common part
            loadCommon((AbstractNamedBean*)conditionalNG, conditionalNG_Element);

            QDomElement socketName = conditionalNG_Element.firstChildElement("Socket").firstChildElement("socketName");
            if (!socketName.isNull()) {
                conditionalNG->getFemaleSocket()->setName(socketName.text().trimmed());
            }
            QDomElement socketSystemName = conditionalNG_Element.firstChildElement("Socket").firstChildElement("systemName");
            if (!socketSystemName.isNull()) {
//                    log.warn("Socket system name: {}", socketSystemName.getTextTrim());
                conditionalNG->setSocketSystemName(socketSystemName.text().trimmed());
            }

            // set enabled/disabled if attribute was present
            if ((enabled != "") && (enabled != (""))) {
                if (enabled == ("yes")) {  // NOI18N
                    conditionalNG->setEnabled(true);
                } else if (enabled == ("no")) {  // NOI18N
                    conditionalNG->setEnabled(false);
                }
            }
        }
    }
}

/**
 * Replace the current LogixManager, if there is one, with one newly created
 * during a load operation. This is skipped if they are of the same absolute
 * type.
 */
/*protected*/ void DefaultConditionalNGManagerXml::replaceConditionalNGManager() {
    if (((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->getClassName()
             == ("jmri.jmrit.logixng.implementation.DefaultConditionalNGManager")) {
        return;
    }
    // if old manager exists, remove it from configuration process
    if (InstanceManager::getNullableDefault("ConditionalNG_Manager") != nullptr) {
        ConfigureManager* cmOD = (AppsConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
        if (cmOD != nullptr) {
            cmOD->deregister(InstanceManager::getDefault("ConditionalNG_Manager"));
        }

    }

//    ThreadingUtil.runOnGUI(() -> {
//        // register new one with InstanceManager
//        DefaultConditionalNGManager pManager = DefaultConditionalNGManager.instance();
//        InstanceManager.store(pManager, ConditionalNG_Manager.class);
//        // register new one for configuration
//        ConfigureManager cmOD = InstanceManager.getNullableDefault(jmri.ConfigureManager.class);
//        if (cmOD != null) {
//            cmOD.registerConfig(pManager, jmri.Manager.LOGIXNGS);
//        }
//    });
    ThreadingUtil::runOnGUI(new DefaultConditionalNGManagerXml_run1(this));
}

//@Override
/*public*/  int DefaultConditionalNGManagerXml::loadOrder() const {
    return ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->getXMLOrder();
}

/*private*/ /*final*/ /*static*/ Logger* DefaultConditionalNGManagerXml::log = LoggerFactory::getLogger("DefaultConditionalNGManagerXml");
