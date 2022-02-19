#include "defaultdigitalbooleanactionmanagerxml.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "digitalbooleanactionmanager.h"
#include "runtimeexception.h"
#include "defaultmaledigitalbooleanactionsocket.h"
/**
 * Provides the functionality for configuring ActionManagers
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
///*public*/  class DefaultDigitalBooleanActionManagerXml extends AbstractManagerXml {


    /*public*/  DefaultDigitalBooleanActionManagerXml::DefaultDigitalBooleanActionManagerXml(QObject* parent) :AbstractManagerXml(parent){
    }

    /**
     * Default implementation for storing the contents of a DigitalBooleanActionManager
     *
     * @param o Object to store, of type DigitalBooleanActionManager
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement DefaultDigitalBooleanActionManagerXml::store(QObject* o) {
        QDomElement actions = doc.createElement("LogixNGDigitalBooleanActions");
        setStoreElementClass(actions);
        DigitalBooleanActionManager* tm = (DigitalBooleanActionManager*) o;
        if (tm != nullptr) {
            if (tm->getNamedBeanSet().isEmpty()) return QDomElement();
            for (NamedBean* nb : tm->getNamedBeanSet()) {
             MaleDigitalBooleanActionSocket* action = (MaleDigitalBooleanActionSocket*)nb;
                log->debug("action system name is " + action->NamedBean::getSystemName());  // NOI18N
                try {
                    QList<QDomElement> elements = QList<QDomElement>();
                    // The male socket may be embedded in other male sockets
                    MaleDigitalBooleanActionSocket* a = action;
                    while (!(static_cast<DefaultMaleDigitalBooleanActionSocket*>(a))) {
                        elements.append(storeMaleSocket(a));
                        a = (MaleDigitalBooleanActionSocket*) a->getObject()->bself();
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
    /*public*/  void DefaultDigitalBooleanActionManagerXml::setStoreElementClass(QDomElement actions) {
        actions.setAttribute("class", "jmri.jmrit.logixng,implementation.configurexml.DefaultMaleDigitalBooleanActionSocket");  // NOI18N
    }

    /**
     * Create a DigitalBooleanActionManager object of the correct class, then register
     * and fill it.
     *
     * @param sharedAction  Shared top level Element to unpack.
     * @param perNodeAction Per-node top level Element to unpack.
     * @return true if successful
     */
    //@Override
    /*public*/  bool DefaultDigitalBooleanActionManagerXml::load(QDomElement sharedAction, QDomElement perNodeAction) {
        // create the master object
        replaceActionManager();
        // load individual sharedAction
        loadActions(sharedAction);
        return true;
    }

    /**
     * Utility method to load the individual DigitalBooleanActionBean objects. If
     * there's no additional info needed for a specific action type, invoke
     * this with the parent of the set of DigitalBooleanActionBean elements.
     *
     * @param actions Element containing the DigitalBooleanActionBean elements to load.
     */
    /*public*/  void DefaultDigitalBooleanActionManagerXml::loadActions(QDomElement actions) {

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
                } catch (NoSuchMethodException* /*| SecurityException */ex) {
                    log->error("cannot create constructor", ex);
                }

                if (c != nullptr) {
                    try {
                        AbstractNamedBeanManagerConfigXML* o = (AbstractNamedBeanManagerConfigXML*)c->newInstance();

                        MaleSocket* oldLastItem = ((DigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->getLastRegisteredMaleSocket();
                        o->load(actionList.at(i).toElement(), QDomElement());

                        // Load male socket data if a new bean has been registered
                        MaleSocket* newLastItem = ((DigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->getLastRegisteredMaleSocket();
                        if (newLastItem != oldLastItem) loadMaleSocket(actionList.at(i).toElement(), newLastItem);
                        else throw new RuntimeException(QString("No new bean has been added. This class: ")+metaObject()->className());
                    } catch (InstantiationException* /*| IllegalAccessException | IllegalArgumentException | InvocationTargetException*/ ex) {
                        log->error("cannot create object", ex);
                    } catch (JmriConfigureXmlException* ex) {
                        log->error("cannot load action", ex);
                    }
                }
            }
        }
    }

    /**
     * Replace the current DigitalBooleanActionManager, if there is one, with one newly
     * created during a load operation. This is skipped if they are of the same
     * absolute type.
     */
    /*protected*/ void DefaultDigitalBooleanActionManagerXml::replaceActionManager() {
        if (QString(InstanceManager::getDefault("DigitalBooleanActionManager")->metaObject()->className()
)                 == ("DefaultDigitalBooleanActionManager")) {
            return;
        }
        // if old manager exists, remove it from configuration process
        if (InstanceManager::getNullableDefault("DigitalBooleanActionManager") != nullptr) {
            ConfigureManager* cmOD = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
            if (cmOD != nullptr) {
                cmOD->deregister(InstanceManager::getDefault("DigitalBooleanActionManager"));
            }

        }
#if 0 // TODO:
        ThreadingUtil.runOnGUI(() -> {
            // register new one with InstanceManager
            DefaultDigitalBooleanActionManager pManager = DefaultDigitalBooleanActionManager.instance();
            InstanceManager.store(pManager, DigitalBooleanActionManager.class);
            // register new one for configuration
            ConfigureManager cmOD = InstanceManager.getNullableDefault(jmri.ConfigureManager.class);
            if (cmOD != null) {
                cmOD.registerConfig(pManager, jmri.Manager.LOGIXNG_DIGITAL_BOOLEAN_ACTIONS);
            }
        });
#endif
    }

    //@Override
    /*public*/  int DefaultDigitalBooleanActionManagerXml::loadOrder()const {
        return ((DigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->getXMLOrder();
    }

    /*private*/ /*final*/ /*static*/ Logger* DefaultDigitalBooleanActionManagerXml::log = LoggerFactory::getLogger("DefaultDigitalBooleanActionManagerXml");
