#include "defaultdigitalexpressionmanagerxml.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanagerxml.h"
#include "digitalexpressionmanager.h"
#include "runtimeexception.h"
#include "defaultmaledigitalexpressionsocket.h"
/**
 * Provides the functionality for configuring ExpressionManagers
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
///*public*/  class DefaultDigitalExpressionManagerXml extends AbstractManagerXml {


    /*public*/  DefaultDigitalExpressionManagerXml::DefaultDigitalExpressionManagerXml(QObject* parent) : AbstractManagerXml(parent){
    }

    /**
     * Default implementation for storing the contents of a LogixManager
     *
     * @param o Object to store, of type LogixManager
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement DefaultDigitalExpressionManagerXml::store(QObject* o) {
        QDomElement expressions = doc.createElement("LogixNGDigitalExpressions");
        setStoreElementClass(expressions);
        DigitalExpressionManager* tm = (DigitalExpressionManager*) o;
        if (tm != nullptr) {
            if (tm->getNamedBeanSet().isEmpty()) return QDomElement();
            for (NamedBean* nb : tm->getNamedBeanSet()) {
             MaleDigitalExpressionSocket* expression = (MaleDigitalExpressionSocket*)nb;
                log->debug("action system name is " + expression->NamedBean::getSystemName());  // NOI18N
                try {
                    QList<QDomElement> elements = QList<QDomElement>();
                    // The male socket may be embedded in other male sockets
                    MaleDigitalExpressionSocket* a = expression;
                    while (!(static_cast<DefaultMaleDigitalExpressionSocket*>(a))) {
                        elements.append(storeMaleSocket(a));
                        a = (MaleDigitalExpressionSocket*) a->getObject()->bself();
                    }
                    QDomElement e = ConfigXmlManager::elementFromObject(a->getObject()->bself());
                    if (!e.isNull()) {
                        for (QDomElement ee : elements) e.appendChild(ee);
                        expressions.appendChild(e);
                    } else {
                        throw new RuntimeException(QString("Cannot load xml configurator for ") + a->getObject()->bself()->metaObject()->className());
                    }
                } catch (RuntimeException* e) {
                    log->error(tr("Error storing action: %1").arg(e->toString()), e);
                }
            }
        }
        return (expressions);
    }

    /**
     * Subclass provides implementation to create the correct top element,
     * including the type information. Default implementation is to use the
     * local class here.
     *
     * @param expressions The top-level element being created
     */
    /*public*/  void DefaultDigitalExpressionManagerXml::setStoreElementClass(QDomElement expressions) {
        expressions.setAttribute("class", "jmri.jmrit.lohixng.implementation.configurexml.DefaultDigitalExpressionManagerXml");  // NOI18N
    }

    /**
     * Create a DigitalExpressionManager object of the correct class, then
     * register and fill it.
     *
     * @param sharedExpression  Shared top level Element to unpack.
     * @param perNodeExpression Per-node top level Element to unpack.
     * @return true if successful
     */
    //@Override
    /*public*/  bool DefaultDigitalExpressionManagerXml::load(QDomElement sharedExpression, QDomElement perNodeExpression) {
        // create the master object
        replaceExpressionManager();
        // load individual sharedLogix
        loadExpressions(sharedExpression);
        return true;
    }

    /**
     * Utility method to load the individual Logix objects. If there's no
     * additional info needed for a specific logix type, invoke this with the
     * parent of the set of Logix elements.
     *
     * @param expressions Element containing the Logix elements to load.
     */
    /*public*/  void DefaultDigitalExpressionManagerXml::loadExpressions(QDomElement expressions) {

        QDomNodeList expressionList = expressions.childNodes();  // NOI18N
        log->debug("Found " + QString::number(expressionList.size()) + " expressions");  // NOI18N
//        DigitalExpressionManager tm = InstanceManager.getDefault(jmri.jmrit.logixng.DigitalExpressionManager.class);

        for (int i = 0; i < expressionList.size(); i++) {

            QString className = expressionList.at(i).toElement().attribute("class");
//            log.warn("className: " + className);

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

                        MaleSocket* oldLastItem = ((DigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getLastRegisteredMaleSocket();
                        o->load(expressionList.at(i).toElement(), QDomElement());

                        // Load male socket data if a new bean has been registered
                        MaleSocket* newLastItem = ((DigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getLastRegisteredMaleSocket();
                        if (newLastItem != oldLastItem) loadMaleSocket(expressionList.at(i).toElement(), newLastItem);
                        else throw new RuntimeException(QString("No new bean has been added. This class: ")+metaObject()->className()+", new class: "+className);
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
     * Replace the current DigitalExpressionManager, if there is one, with one newly created
     * during a load operation. This is skipped if they are of the same absolute
     * type.
     */
    /*protected*/ void DefaultDigitalExpressionManagerXml::replaceExpressionManager() {
        if (QString(InstanceManager::getDefault("DigitalExpressionManager")->metaObject()->className())
                 == ("DefaultDigitalExpressionManager")) {
            return;
        }
        // if old manager exists, remove it from configuration process
        if (InstanceManager::getNullableDefault("DigitalExpressionManager") != nullptr) {
            ConfigureManager* cmOD = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
            if (cmOD != nullptr) {
                cmOD->deregister(InstanceManager::getDefault("DigitalExpressionManager"));
            }

        }

#if 0 // TODO:
        ThreadingUtil.runOnGUI(() -> {
            // register new one with InstanceManager
            DefaultDigitalExpressionManager pManager = DefaultDigitalExpressionManager.instance();
            InstanceManager.store(pManager, DigitalExpressionManager.class);
            // register new one for configuration
            ConfigureManager cmOD = InstanceManager.getNullableDefault(jmri.ConfigureManager.class);
            if (cmOD != null) {
                cmOD.registerConfig(pManager, jmri.Manager.LOGIXNG_DIGITAL_EXPRESSIONS);
            }
        });
#endif
    }

    //@Override
    /*public*/  int DefaultDigitalExpressionManagerXml::loadOrder() const {
        return ((DigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getXMLOrder();
    }

    /*private*/ /*final*/ /*static*/ Logger* DefaultDigitalExpressionManagerXml::log = LoggerFactory::getLogger("DefaultDigitalExpressionManagerXml");