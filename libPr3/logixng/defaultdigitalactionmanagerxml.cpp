#include "defaultdigitalactionmanagerxml.h"
#include "loggerfactory.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "runtimeexception.h"
#include "defaultmaledigitalactionsocket.h"

/**
 * Provides the functionality for configuring ActionManagers
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
///*public*/  class DefaultDigitalActionManagerXml extends AbstractManagerXml {


    /*public*/  DefaultDigitalActionManagerXml::DefaultDigitalActionManagerXml(QObject* parent) : AbstractManagerXml(parent){
    }

    /**
     * Default implementation for storing the contents of a DigitalActionManager
     *
     * @param o Object to store, of type DigitalActionManager
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement DefaultDigitalActionManagerXml::store(QObject* o) {
        QDomElement actions = doc.createElement("LogixNGDigitalActions");
        setStoreElementClass(actions);
        DigitalActionManager* tm = (DigitalActionManager*) o;
        if (tm != nullptr) {
            if (tm->getNamedBeanSet().isEmpty()) return QDomElement();
            for (NamedBean* nb : tm->getNamedBeanSet()) {
             DefaultMaleDigitalActionSocket* action = (DefaultMaleDigitalActionSocket*)nb->self();
                log->debug("action system name is " + action->AbstractNamedBean::getSystemName());  // NOI18N
                try {
                    QList<QDomElement> elements = QList<QDomElement>();
                    // The male socket may be embedded in other male sockets
                    DefaultMaleDigitalActionSocket* a = action;
                    while (!(static_cast<DefaultMaleDigitalActionSocket*>(a))) {
                        elements.append(storeMaleSocket(a));
                        a = (DefaultMaleDigitalActionSocket*) a->getObject()->bself();
                    }
                    QDomElement e = ConfigXmlManager::elementFromObject(a->getObject()->bself());
                    if (!e.isNull()) {
                        for (QDomElement ee : elements) e.appendChild(ee);
                        actions.appendChild(e);
                    } else {
                        throw new RuntimeException(QString("Cannot load xml configurator for ") + a->getObject()->bself()->metaObject()->className());
                    }
                } catch (RuntimeException* e) {
                    log->error(tr("Error storing action: %1").arg(e->toString()), e);
                }
            }
        }
        return (actions);
    }

    /**
     * Subclass provides implementation to create the correct top element,
     * including the type information. Default implementation is to use the
     * local class here.
     *
     * @param actions The top-level element being created
     */
    /*public*/  void DefaultDigitalActionManagerXml::setStoreElementClass(QDomElement actions) {
        actions.setAttribute("class", "jmri.jmrit.logixng.implementation.configurexml.DefaultDigitalActionManagerXml");  // NOI18N
    }

    /**
     * Create a DigitalActionManager object of the correct class, then register
     * and fill it.
     *
     * @param sharedAction  Shared top level Element to unpack.
     * @param perNodeAction Per-node top level Element to unpack.
     * @return true if successful
     */
    //@Override
    /*public*/  bool DefaultDigitalActionManagerXml::load(QDomElement sharedAction, QDomElement perNodeAction) {
        // create the master object
        replaceActionManager();
        // load individual sharedAction
        loadActions(sharedAction);
        return true;
    }

    /**
     * Utility method to load the individual DigitalActionBean objects. If
     * there's no additional info needed for a specific action type, invoke
     * this with the parent of the set of DigitalActionBean elements.
     *
     * @param actions Element containing the DigitalActionBean elements to load.
     */
    /*public*/  void DefaultDigitalActionManagerXml::loadActions(QDomElement actions) {

        QDomNodeList actionList = actions.childNodes();  // NOI18N
        log->debug("Found " + QString::number(actionList.size()) + " actions");  // NOI18N

        for (int i = 0; i < actionList.size(); i++) {

            QString className = actionList.at(i).toElement().attribute("class");
//            log.error("className: " + className);

            Class/*<?>*/* clazz = xmlClasses.value(className);

            if (clazz == nullptr) {
                try {
                    clazz = Class::forName(className);
                    xmlClasses.insert(className, clazz);
                } catch (ClassNotFoundException* ex) {
                    log->error("cannot load class " + className, ex);
                }
            }

            if (clazz != nullptr) {
                /*Constructor<?>*/Class* c = nullptr;
                try {
                    c = clazz->getConstructor();
                } catch (NoSuchMethodException* /*| SecurityException*/ ex) {
                    log->error("cannot create constructor", ex);
                }

                if (c != nullptr) {
                    try {
                        AbstractNamedBeanManagerConfigXML* o = (AbstractNamedBeanManagerConfigXML*)c->newInstance();

                        MaleSocket* oldLastItem = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getLastRegisteredMaleSocket();
                        o->load(actionList.at(i).toElement(), QDomElement());

                        // Load male socket data if a new bean has been registered
                        MaleSocket* newLastItem = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getLastRegisteredMaleSocket();
                        if (newLastItem != oldLastItem) loadMaleSocket(actionList.at(i).toElement(), newLastItem);
                        else throw new RuntimeException(QString("No new bean has been added. This class: ")+metaObject()->className());
                    } catch (InstantiationException* /*| IllegalAccessException | IllegalArgumentException | InvocationTargetException */ex) {
                        log->error("cannot create object", ex);
                    } catch (JmriConfigureXmlException* ex) {
                        log->error("cannot load action", ex);
                    }
                }
            }
        }
    }

    /**
     * Replace the current DigitalActionManager, if there is one, with one newly
     * created during a load operation. This is skipped if they are of the same
     * absolute type.
     */
    /*protected*/ void DefaultDigitalActionManagerXml::replaceActionManager() {
        if (QString(InstanceManager::getDefault("DigitalActionManager")->metaObject()->className())
                 == ("DefaultDigitalActionManager")) {
            return;
        }
        // if old manager exists, remove it from configuration process)
        if (InstanceManager::getNullableDefault("DigitalActionManager") != nullptr) {
            ConfigureManager* cmOD = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
            if (cmOD != nullptr) {
                cmOD->deregister(InstanceManager::getDefault("DigitalActionManager"));
            }

        }
#if 0 // TODO:
        ThreadingUtil.runOnGUI(() -> {
            // register new one with InstanceManager
            DefaultDigitalActionManager pManager = DefaultDigitalActionManager.instance();
            InstanceManager.store(pManager, DigitalActionManager.class);
            // register new one for configuration
            ConfigureManager cmOD = InstanceManager.getNullableDefault(jmri.ConfigureManager.class);
            if (cmOD != null) {
                cmOD.registerConfig(pManager, jmri.Manager.LOGIXNG_DIGITAL_ACTIONS);
            }
        });
#endif
    }

    //@Override
    /*public*/  int DefaultDigitalActionManagerXml::loadOrder() const {
        return ((DigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getXMLOrder();
    }

    /*private*/ /*final*//*static*/Logger* DefaultDigitalActionManagerXml::log = LoggerFactory::getLogger("DefaultDigitalActionManagerXml");
