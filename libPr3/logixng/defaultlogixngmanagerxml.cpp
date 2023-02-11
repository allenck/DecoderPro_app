#include "defaultlogixngmanagerxml.h"
#include "logixng_manager.h"
#include "logixng_thread.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "conditionalng.h"
#include "defaultlogixngmanager.h"
#include "defaultlogixnginitializationmanager.h"
#include "configxmlmanager.h"
#include "defaultlogixng.h"
#include "class.h"
#include "threadingutil.h"
#include "appsconfigurationmanager.h"

/**
 * Provides the functionality for configuring LogixNGManagers
 * <P>
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
///*public*/ class DefaultLogixNGManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/ DefaultLogixNGManagerXml::DefaultLogixNGManagerXml(QObject* parent) : AbstractNamedBeanManagerConfigXML(parent){
    }

    /**
     * Default implementation for storing the contents of a LogixNG_Manager
     *
     * @param o Object to store, of type LogixNG_Manager
     * @return Element containing the complete info
     */
    //@Override
    /*public*/ QDomElement DefaultLogixNGManagerXml::store(QObject* o) {
        bool hasData = false;

        QDomElement logixNGs = doc.createElement("LogixNGs");
        setStoreElementClass(logixNGs);
        LogixNG_Manager* tm = (DefaultLogixNGManager*) o;
        if (tm != nullptr) {
            for (LogixNG_Thread* thread : LogixNG_Thread::getThreads()) {
                QDomElement e = doc.createElement("Thread");  // NOI18N
                QDomElement e1;
                e.appendChild(e1=doc.createElement("id")); e1.appendChild(doc.createTextNode(QString::number(thread->getThreadId())));
                e.appendChild(e1=doc.createElement("name")); e1.appendChild(doc.createTextNode(thread->getThreadName()));
                logixNGs.appendChild(e);
            }

            for (NamedBean* nb : tm->getNamedBeanSet()) {
             DefaultLogixNG* logixNG = (DefaultLogixNG*)nb->self();
                log->debug("logixng system name is " + logixNG->getSystemName());  // NOI18N
                bool enabled = logixNG->isEnabled();
                QDomElement elem = doc.createElement("LogixNG");
                QDomElement esn;// NOI18N
                elem.appendChild(esn=doc.createElement("systemName")); esn.appendChild(doc.createTextNode(nb->getSystemName()));  // NOI18N

                // store common part
                storeCommon((NamedBean*)nb, elem);

                QDomElement e = doc.createElement("ConditionalNGs");
                QDomElement e1;
                for (int i=0; i < logixNG->getNumConditionalNGs(); i++) {
                    e.appendChild(e1=doc.createElement("systemName"));  e1.appendChild(doc.createTextNode(logixNG->getConditionalNG(i)->AbstractNamedBean::getSystemName()));
                }
                elem.appendChild(e);

                elem.setAttribute("enabled", enabled ? "yes" : "no");  // NOI18N

                logixNGs.appendChild(elem);
                hasData = true;
            }

            QDomElement elemInitializationTable = doc.createElement("InitializationTable");  // NOI18N
            for (LogixNG* logixNG : ((DefaultLogixNGInitializationManager*)InstanceManager::getDefault("LogixNG_InitializationManager"))->getList()) {
                QDomElement e = doc.createElement("LogixNG");
                e.appendChild(doc.createTextNode(logixNG->Base::getSystemName()));   // NOI18N
                elemInitializationTable.appendChild(e);
            }
            logixNGs.appendChild(elemInitializationTable);

            // Store items on the clipboard
            QDomElement elemClipboard = doc.createElement("Clipboard");  // NOI18N
            Clipboard* clipboard = tm->getClipboard();
            if (clipboard->getFemaleSocket()->isConnected()) {
                Base* rootObject = clipboard->getFemaleSocket()->getConnectedSocket()->getObject();
                try {
                    QDomElement e = ConfigXmlManager::elementFromObject(rootObject->bself());
                    if (e != QDomElement()) {
                        elemClipboard.appendChild(e);
                    }
                } catch (Exception* e) {
                    log->error(tr("Error storing action: %1").arg(e->getMessage()), e);
                }
            }
            logixNGs.appendChild(elemClipboard);
        }
        return hasData ? logixNGs : QDomElement();
    }

    /**
     * Subclass provides implementation to create the correct top element,
     * including the type information. Default implementation is to use the
     * local class here.
     *
     * @param logixngs The top-level element being created
     */
    /*public*/ void DefaultLogixNGManagerXml::setStoreElementClass(QDomElement logixngs) {
        logixngs.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixNG->implementation.configurexml.DefaultLogixNGManagerXml");  // NOI18N
    }

    /**
     * Create a LogixNG_Manager object of the correct class, then register and
     * fill it.
     *
     * @param sharedLogixNG  Shared top level Element to unpack.
     * @param perNodeLogixNG Per-node top level Element to unpack.
     * @return true if successful
     */
    //@Override
    /*public*/ bool DefaultLogixNGManagerXml::load(QDomElement sharedLogixNG, QDomElement perNodeLogixNG) {
        // create the master object
        replaceLogixNGManager();
        // load individual sharedLogix
        loadThreads(sharedLogixNG);
        loadLogixNGs(sharedLogixNG);
        loadInitializationTable(sharedLogixNG);
        loadClipboard(sharedLogixNG);
        return true;
    }

    /**
     * Utility method to load the individual LogixNG objects. If there's no
     * additional info needed for a specific logixng type, invoke this with the
     * parent of the set of LogixNG elements.
     *
     * @param sharedLogixNG Element containing the LogixNG elements to load.
     */
    /*public*/ void DefaultLogixNGManagerXml::loadThreads(QDomElement sharedLogixNG) {
        QDomNodeList threads = sharedLogixNG.elementsByTagName("Thread");  // NOI18N
        log->debug("Found " + QString::number(threads.size()) + " threads");  // NOI18N

        for (int i = 0; i < threads.size(); i++) {

            QDomElement threadElement = threads.at(i).toElement();

            int threadId = threadElement.firstChildElement("id").text().trimmed().toInt();
            QString threadName = threadElement.firstChildElement("name").text().trimmed();

            log->debug("create thread: " + QString::number(threadId) + ", " + threadName);  // NOI18N
            LogixNG_Thread::createNewThread(threadId, threadName);
        }
    }

    /**
     * Utility method to load the individual LogixNG objects. If there's no
     * additional info needed for a specific logixng type, invoke this with the
     * parent of the set of LogixNG elements.
     *
     * @param sharedLogixNG Element containing the LogixNG elements to load.
     */
    /*public*/ void DefaultLogixNGManagerXml::loadLogixNGs(QDomElement sharedLogixNG) {
        QDomNodeList logixNGList = sharedLogixNG.elementsByTagName("LogixNG");  // NOI18N
        log->debug("Found " + QString::number(logixNGList.size()) + " logixngs");  // NOI18N
        LogixNG_Manager* tm = (DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");

        for (int i = 0; i < logixNGList.size(); i++) {

            QDomElement logixNG_Element = logixNGList.at(i).toElement();

            QString sysName = getSystemName(logixNG_Element);
            if (sysName == "") {
                log->warn("unexpected null in systemName " + logixNG_Element.tagName());  // NOI18N
                break;
            }

            QString userName = getUserName(logixNG_Element);

            QString yesno = "";
            if (logixNGList.at(i).toElement().attribute("enabled") != "") {  // NOI18N
                yesno = logixNG_Element.attribute("enabled");  // NOI18N
            }
            log->debug("create logixng: (" + sysName + ")("  // NOI18N
                    + (userName == "null" ? "<null>" : userName) + ")");  // NOI18N

            // Create a new LogixNG but don't setup the initial tree.
            DefaultLogixNG* logixNG = (DefaultLogixNG*)tm->createLogixNG(sysName, userName);
            if (logixNG != nullptr) {
                // load common part
                loadCommon((AbstractNamedBean*)logixNG->self(), logixNGList.at(i).toElement());

                // set enabled/disabled if attribute was present
                if ((yesno != "") && (yesno != (""))) {
                    if (yesno == ("yes")) {  // NOI18N
                        logixNG->setEnabled(true);
                    } else if (yesno == ("no")) {  // NOI18N
                        logixNG->setEnabled(false);
                    }
                }

                QDomNodeList conditionalNGList =
                        logixNG_Element.firstChildElement("ConditionalNGs").childNodes();  // NOI18N

                for (int j = 0; j < conditionalNGList.size(); j++) {

                    QDomElement systemNameElement = conditionalNGList.at(j).toElement();
                    QString systemName = "";
                    if (systemNameElement != QDomElement()) {
                        systemName = systemNameElement.text().trimmed();
                    }
                    logixNG->setConditionalNG_SystemName(j, systemName);
                }
            }
        }
    }

    /*public*/ void DefaultLogixNGManagerXml::loadInitializationTable(QDomElement sharedLogixNG) {
        LogixNG_Manager* tm = (LogixNG_Manager*)
                InstanceManager::getDefault("LogixNG_Manager");

        LogixNG_InitializationManager* initializationManager =(LogixNG_InitializationManager*)
                InstanceManager::getDefault("LogixNG_InitializationManager");

        QDomNodeList initTableList = sharedLogixNG.elementsByTagName("InitializationTable");  // NOI18N
        if (initTableList.isEmpty()) return;
        QDomNodeList logixNGList = initTableList.at(0).childNodes();
        if (logixNGList.isEmpty()) return;
        //foreach (QDomNode n , logixNGList) {
        for(int i=0; i < logixNGList.size(); i++)
        {
         QDomElement e = logixNGList.at(i).toElement();
            LogixNG* logixNG = (DefaultLogixNG*)tm->getBySystemName(e.text().trimmed())->self();
            if (logixNG != nullptr) {
                initializationManager->add(logixNG);
            } else {
                log->warn(tr("LogixNG '%1' cannot be found").arg(e.text().trimmed()));
            }
        }
    }

    /*public*/ void DefaultLogixNGManagerXml::loadClipboard(QDomElement sharedLogixNG) {
        QDomNodeList clipboardList = sharedLogixNG.elementsByTagName("Clipboard");  // NOI18N
        if (clipboardList.isEmpty()) return;
        QDomNodeList clipboardSubList = clipboardList.at(0).childNodes();
        if (clipboardSubList.isEmpty()) return;

        QString className = clipboardSubList.at(0).toElement().attribute("class");
//        log.error("className: " + className);

        Class/*<?>*/* clazz;
        try {
            clazz = Class::forName(className);
        } catch (ClassNotFoundException* ex) {
            log->error("cannot load class " + className, ex);
            return;
        }
#if 0
        Constructor<?> c;
        try {
            c = clazz->getConstructor();
        } catch (NoSuchMethodException* | SecurityException ex) {
            log->error("cannot create constructor", ex);
            return;
        }

        try {
            Object o = c.newInstance();

            if (o == null) {
                log.error("class is null");
                return;
            }
            if (! (o instanceof ClipboardManyXml)) {
                log.error("class has wrong type: " + o.getClass().getName());
                return;
            }

            LogixNG_Manager tm = InstanceManager.getDefault(jmri.jmrit.logixNG->LogixNG_Manager.class);
            ClipboardMany anyMany = ((ClipboardManyXml)o).loadItem(clipboardList.get(0));
            List<String> errors = new ArrayList<>();
            if (! ((DefaultClipboard)tm.getClipboard()).replaceClipboardItems(anyMany, errors)) {
                for (String s : errors) log.error(s);
            }
        } catch (InstantiationException* | IllegalAccessException | IllegalArgumentException | InvocationTargetException ex) {
            log.error("cannot create object", ex);
        }
#endif
    }

    /**
     * Replace the current LogixManager, if there is one, with one newly created
     * during a load operation. This is skipped if they are of the same absolute
     * type.
     */
    /*protected*/ void DefaultLogixNGManagerXml::replaceLogixNGManager() {
        if (InstanceManager::getDefault("LogixNG_Manager")->metaObject()->className()
                == QString("DefaultLogixNGManager")) {
            return;
        }
        // if old manager exists, remove it from configuration process
        if (InstanceManager::getNullableDefault("LogixNG_Manager") != nullptr) {
            ConfigureManager* cmOD = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
            if (cmOD != nullptr) {
                cmOD->deregister(InstanceManager::getDefault("LogixNG_Manager"));
            }

        }
#if 0
        ThreadingUtil::runOnGUI(() -> {
            // register new one with InstanceManager
            DefaultLogixNGManager pManager = DefaultLogixNGManager.instance();
            InstanceManager.store(pManager, LogixNG_Manager.class);
            // register new one for configuration
            ConfigureManager cmOD = InstanceManager.getNullableDefault(jmri.ConfigureManager.class);
            if (cmOD != null) {
                cmOD.registerConfig(pManager, jmri.Manager.LOGIXNGS);
            }
        });

#else
        ThreadingUtil::runOnGUI(new DLMRun());
#endif
    }

void DLMRun::run()
{
 // register new one with InstanceManager
 DefaultLogixNGManager* pManager = DefaultLogixNGManager::instance();
 InstanceManager::store(pManager, "LogixNG_Manager");
 // register new one for configuration
 ConfigureManager* cmOD = (AppsConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
 if (cmOD != nullptr) {
     cmOD->registerConfig(pManager, Manager::LOGIXNGS);
 }
}
    //@Override
    /*public*/ int DefaultLogixNGManagerXml::loadOrder() const{
        return ((LogixNG_Manager*)InstanceManager::getDefault("LogixNG_Manager"))->getXMLOrder();
    }

    /*private*/ /*final*/ /*static*/ Logger* DefaultLogixNGManagerXml::log = LoggerFactory::getLogger("DefaultLogixNGManagerXml");
