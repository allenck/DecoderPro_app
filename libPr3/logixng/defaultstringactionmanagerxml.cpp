#include "defaultstringactionmanagerxml.h"
#include "loggerfactory.h"
#include "runtimeexception.h"
#include "malestringactionsocket.h"
#include "defaultmalestringactionsocket.h"
#include "abstractstringaction.h"

/**
 * Provides the functionality for configuring ActionManagers
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
///*public*/  class DefaultStringActionManagerXml extends AbstractManagerXml {


    /*public*/  DefaultStringActionManagerXml::DefaultStringActionManagerXml(QObject *parent)
     : AbstractManagerXml(parent) {
     setObjectName("DefaultStringActionManagerXml");
    }

    /**
     * Default implementation for storing the contents of a StringActionManager
     *
     * @param o Object to store, of type StringActionManager
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement DefaultStringActionManagerXml::store(QObject* o) {
        QDomElement actions = doc.createElement("LogixNGStringActions");
        setStoreElementClass(actions);
        StringActionManager* tm = (StringActionManager*) o;
        if (tm != nullptr) {
            if (tm->getNamedBeanSet().isEmpty()) return QDomElement();
            for (NamedBean* nb : tm->getNamedBeanSet()) {
             //MaleStringActionSocket* action = (DefaultMaleStringActionSocket*)nb->self();
             AbstractStringAction* action = (AbstractStringAction*)nb->self();
                log->debug("action system name is " + action->NamedBean::getSystemName());  // NOI18N
//                log.error("action system name is " + action.getSystemName() + ", " + action.getLongDescription());  // NOI18N
                try {
                    QList<QDomElement> elements = QList<QDomElement>();
                    // The male socket may be embedded in other male sockets
                    Base* p = action->getParent();
                    //MaleStringActionSocket* a = (DefaultMaleStringActionSocket*)((AbstractStringAction*)action)->getParent()->bself();
                   MaleStringActionSocket* a = (DefaultMaleStringActionSocket*)p->bself();
                    while (!(static_cast<DefaultMaleStringActionSocket*>(a))) {
                        elements.append(storeMaleSocket(a));
                        a = (MaleStringActionSocket*) ((AbstractMaleSocket*)a->bself())->getObject()->bself();
                    }
                    QDomElement e = ConfigXmlManager::elementFromObject(((AbstractMaleSocket*)a->bself())->getObject()->bself());
                    if (!e.isNull()) {
                        for (QDomElement ee : elements) e.appendChild(ee);
//                        e.addContent(storeMaleSocket(a));
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
    /*public*/  void DefaultStringActionManagerXml::setStoreElementClass(QDomElement actions) {
        actions.setAttribute("class", "jmri.jmrit.logixng.implementation.configurexml.DefaultStringActionManagerXml");  // NOI18N
    }

    /**
     * Create a StringActionManager object of the correct class, then register
     * and fill it.
     *
     * @param sharedAction  Shared top level Element to unpack.
     * @param perNodeAction Per-node top level Element to unpack.
     * @return true if successful
     */
    //@Override
    /*public*/  bool DefaultStringActionManagerXml::load(QDomElement sharedAction, QDomElement perNodeAction) {
        // create the master object
        replaceActionManager();
        // load individual sharedAction
        loadActions(sharedAction);
        return true;
    }

    /**
     * Utility method to load the individual StringActionBean objects. If
     * there's no additional info needed for a specific action type, invoke
     * this with the parent of the set of StringActionBean elements.
     *
     * @param actions Element containing the StringActionBean elements to load.
     */
    /*public*/  void DefaultStringActionManagerXml::loadActions(QDomElement actions) {

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

                        MaleSocket* oldLastItem = ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))->getLastRegisteredMaleSocket();
                        o->load(actionList.at(i).toElement(), QDomElement());

                        // Load male socket data if a new bean has been registered
                        MaleSocket* newLastItem = ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))->getLastRegisteredMaleSocket();
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
     * Replace the current StringActionManager, if there is one, with one newly
     * created during a load operation. This is skipped if they are of the same absolute
     * type.
     */
    /*protected*/ void DefaultStringActionManagerXml::replaceActionManager() {
        if (QString(InstanceManager::getDefault("StringActionManager")->metaObject()->className())
                 == ("DefaultStringActionManager")) {
            return;
        }
        // if old manager exists, remove it from configuration process
        if (InstanceManager::getNullableDefault("StringActionManager") != nullptr) {
            ConfigureManager* cmOD = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
            if (cmOD != nullptr) {
                cmOD->deregister(InstanceManager::getDefault("StringActionManager"));
            }

        }
#if 0 // TODO:
        ThreadingUtil.runOnGUI(() -> {
            // register new one with InstanceManager
            DefaultStringActionManager pManager = DefaultStringActionManager.instance();
            InstanceManager.store(pManager, StringActionManager.class);
            // register new one for configuration
            ConfigureManager cmOD = InstanceManager.getNullableDefault(jmri.ConfigureManager.class);
            if (cmOD != null) {
                cmOD.registerConfig(pManager, jmri.Manager.LOGIXNG_STRING_ACTIONS);
            }
        });
#endif
       ThreadingUtil::runOnGUI(new DSA_ThreadingUtil()) ;
    }

    //@Override
    /*public*/  int DefaultStringActionManagerXml::loadOrder() const {
        return ((StringActionManager*)InstanceManager::getDefault("StringActionManager"))->getXMLOrder();
    }

    /*private*/ /*final*/ /*static*/ Logger* DefaultStringActionManagerXml::log = LoggerFactory::getLogger("DefaultStringActionManagerXml");
