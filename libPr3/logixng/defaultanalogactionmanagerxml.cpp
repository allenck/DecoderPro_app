#include "defaultanalogactionmanagerxml.h"
#include "jmriconfigurexmlexception.h"
#include "loggerfactory.h"
#include "defaultmaleanalogactionsocket.h"
#include "abstractanalogaction.h"

/**
 * Provides the functionality for configuring ActionManagers
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
///*public*/  class DefaultAnalogActionManagerXml extends AbstractManagerXml {


    /*public*/  DefaultAnalogActionManagerXml::DefaultAnalogActionManagerXml(QObject*parent) : AbstractManagerXml(parent){
    }

    /**
     * Default implementation for storing the contents of a AnalogActionManager
     *
     * @param o Object to store, of type AnalogActionManager
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement DefaultAnalogActionManagerXml::store(QObject* o) {
        QDomElement actions = doc.createElement("LogixNGAnalogActions");
        setStoreElementClass(actions);
        AnalogActionManager* tm = (DefaultAnalogActionManager*) o;
        if (tm != nullptr) {
            QSet<NamedBean*> set;
            if ((set = tm->getNamedBeanSet()).isEmpty()) return QDomElement();
            for (NamedBean* nb: tm->getNamedBeanSet()) {
              AbstractAnalogAction* action  = (AbstractAnalogAction*)nb->self();
              log->debug("action system name is " + nb->getSystemName());  // NOI18N
              try {
                    QList<QDomElement> elements = QList<QDomElement>();
                    // The male socket may be embedded in other male sockets
                    MaleAnalogActionSocket* a = (DefaultMaleAnalogActionSocket*)action->getParent()->bself();
                              NamedBean* anb = nb;
                    while (!(qobject_cast<DefaultMaleAnalogActionSocket*>(a->self()))) {
                     if(qobject_cast<MaleSocket*>(a->self()))
                        elements.append(storeMaleSocket((MaleSocket*)a->self()));
                         //a = ((DefaultMaleAnalogActionSocket*)((DefaultMaleAnalogActionSocket*) anb->self())->getObject()->bself());
                       a = (MaleAnalogActionSocket*) a->getObject()->bself();
                       anb = (NamedBean*)a->self();
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
    /*public*/  void  DefaultAnalogActionManagerXml::setStoreElementClass(QDomElement actions) {
        actions.setAttribute("class", "jmri.jmrit.logixng.implementation.configut=rexml.DefaultAnalogActionManagerXml");  // NOI18N
    }

    /**
     * Create a AnalogActionManager object of the correct class, then register
     * and fill it.
     *
     * @param sharedAction  Shared top level Element to unpack.
     * @param perNodeAction Per-node top level Element to unpack.
     * @return true if successful
     */
    //@Override
    /*public*/  bool  DefaultAnalogActionManagerXml::load(QDomElement sharedAction, QDomElement perNodeAction) {
        // create the master object
        replaceActionManager();
        // load individual sharedAction
        loadActions(sharedAction);
        return true;
    }

    /**
     * Utility method to load the individual AnalogActionBean objects. If
     * there's no additional info needed for a specific action type, invoke
     * this with the parent of the set of AnalogActionBean elements.
     *
     * @param actions Element containing the AnalogActionBean elements to load.
     */
    /*public*/  void  DefaultAnalogActionManagerXml::loadActions(QDomElement actions) {

        QDomNodeList actionList = actions.childNodes();  // NOI18N
        log->debug(tr("Found %1 actions").arg(actionList.size()));  // NOI18N

        for (int i = 0; i < actionList.size(); i++) {

            QString className = actionList.at(i).toElement().attribute("class");
//            log.error("className: " + className);

            Class/*<?>*/* clazz = xmlClasses.value(className);

            if (clazz == nullptr) {
                try {
                    clazz = Class::forName(className);
                    xmlClasses.insert(className, clazz);
                } catch (ClassNotFoundException* ex) {
                    log->error(tr("cannot load class %1").arg(className), ex);
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

                        MaleSocket* oldLastItem = ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->getLastRegisteredMaleSocket();
                        o->load(actionList.at(i).toElement(), QDomElement());

                        // Load male socket data if a new bean has been registered
                        MaleSocket* newLastItem = ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->getLastRegisteredMaleSocket();
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
     * Replace the current AnalogActionManager, if there is one, with one newly
     * created during a load operation. This is skipped if they are of the same
     * absolute type.
     */
    /*protected*/ void  DefaultAnalogActionManagerXml::replaceActionManager() {
        if (QString(InstanceManager::getDefault("AnalogActionManager")->metaObject()->className())
                 == ("DefaultAnalogActionManager")) {
            return;
        }
        // if old manager exists, remove it from configuration process
        if (InstanceManager::getNullableDefault("AnalogActionManager") != nullptr) {
            ConfigureManager* cmOD = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
            if (cmOD != nullptr) {
                cmOD->deregister(InstanceManager::getDefault("AnalogActionManager"));
            }

        }
#if 0 // TODO:
        ThreadingUtil.runOnGUI(() -> {
            // register new one with InstanceManager
            DefaultAnalogActionManager pManager = DefaultAnalogActionManager.instance();
            InstanceManager.store(pManager, AnalogActionManager.class);
            // register new one for configuration
            ConfigureManager cmOD = InstanceManager.getNullableDefault(jmri.ConfigureManager.class);
            if (cmOD != null) {
                cmOD.registerConfig(pManager, jmri.Manager.LOGIXNG_ANALOG_ACTIONS);
            }
        });
#endif
        ThreadingUtil::runOnGUI(new DAAM_ThreadingUtil(this));

    }

    //@Override
    /*public*/  int  DefaultAnalogActionManagerXml::loadOrder() const {
        return ((AnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->getXMLOrder();
    }

    /*private*/ /*final*/ /*static*/ Logger* DefaultAnalogActionManagerXml::log = LoggerFactory::getLogger("DefaultAnalogActionManagerXml");
