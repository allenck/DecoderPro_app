#include "defaultanalogexpressionmanagerxml.h"
#include "jmriconfigurexmlexception.h"
#include "loggerfactory.h"
#include "analogexpressionmanager.h"
#include "instancemanager.h"
#include "threadingutil.h"
#include "loggingutil.h"
#include "class.h"
#include "defaultmaleanalogexpressionsocket.h"
#include "defaultanalogexpressionmanager.h"
#include "appsconfigurationmanager.h"

/**
 * Provides the functionality for configuring ExpressionManagers
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
///*public*/  class DefaultAnalogExpressionManagerXml extends AbstractManagerXml {

    /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

    /*public*/  DefaultAnalogExpressionManagerXml::DefaultAnalogExpressionManagerXml(QObject* parent) : AbstractManagerXml(parent) {
    }

    /**
     * Default implementation for storing the contents of a LogixManager
     *
     * @param o Object to store, of type LogixManager
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement DefaultAnalogExpressionManagerXml::store(QObject* o) {
        QDomElement expressions = doc.createElement("LogixNGAnalogExpressions");
        setStoreElementClass(expressions);
        DefaultAnalogExpressionManager* tm = (DefaultAnalogExpressionManager*) o;
        if (tm != nullptr) {
            if (tm->getNamedBeanSet().isEmpty()) return QDomElement();
            for (NamedBean* nb : tm->getNamedBeanSet()) {
             //DefaultMaleAnalogExpressionSocket* expression = (DefaultMaleAnalogExpressionSocket*)nb->self();
             AbstractMaleSocket* expression = (AbstractMaleSocket*)nb->self();
                log->debug("expression system name is " + expression->AbstractNamedBean::getSystemName());  // NOI18N
                try {
                    QList<QDomElement> elements = QList<QDomElement>();
                    // The male socket may be embedded in other male sockets
                    AbstractMaleSocket* a = expression;
                    while (!(static_cast<DefaultMaleAnalogExpressionSocket*>(a))) {
                        elements.append(storeMaleSocket(a));
                        a = (DefaultMaleAnalogExpressionSocket*) a->getObject()->bself();
                    }
                    QDomElement e = ConfigXmlManager::elementFromObject(a->getObject()->bself());
                    if (e != QDomElement()) {
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
    /*public*/  void DefaultAnalogExpressionManagerXml::setStoreElementClass(QDomElement expressions) {
        expressions.setAttribute("class", "jmri.jmrit.logixng.implementation.configurexml.DefaultAnalogExpressionManagerXml");  // NOI18N
    }

    /**
     * Create a AnalogExpressionManager object of the correct class, then
     * register and fill it.
     *
     * @param sharedExpression  Shared top level Element to unpack.
     * @param perNodeExpression Per-node top level Element to unpack.
     * @return true if successful
     */
    //@Override
    /*public*/  bool DefaultAnalogExpressionManagerXml::load(QDomElement sharedExpression, QDomElement perNodeExpression) {
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
    /*public*/  void DefaultAnalogExpressionManagerXml::loadExpressions(QDomElement expressions) {

        QDomNodeList expressionList = expressions.childNodes();  // NOI18N
        log->debug("Found " + QString::number(expressionList.size()) + " actions");  // NOI18N

        for (int i = 0; i < expressionList.size(); i++) {

            QString className = expressionList.at(i).toElement().attribute("class");
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

                        MaleSocket* oldLastItem = ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->getLastRegisteredMaleSocket();
                        o->load(expressionList.at(i).toElement(), QDomElement());

                        // Load male socket data if a new bean has been registered
                        MaleSocket* newLastItem = ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->getLastRegisteredMaleSocket();
                        if (newLastItem != oldLastItem) loadMaleSocket(expressionList.at(i).toElement(), newLastItem);
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
     * Replace the current LogixManager, if there is one, with one newly created
     * during a load operation. This is skipped if they are of the same absolute
     * type.
     */
    /*protected*/ void DefaultAnalogExpressionManagerXml::replaceExpressionManager() {
        if (QString(InstanceManager::getDefault("AnalogExpressionManager")->metaObject()->className())
                 == ("DefaultAnalogExpressionManager")) {
            return;
        }
        // if old manager exists, remove it from configuration process
        if (InstanceManager::getNullableDefault("AnalogExpressionManager") != nullptr) {
            ConfigureManager* cmOD = ((ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager"));
            if (cmOD != nullptr) {
                cmOD->deregister(InstanceManager::getDefault("AnalogExpressionManager"));
            }

        }
#if 0 //TODO:
        ThreadingUtil::runOnGUI(() -> {
            // register new one with InstanceManager
            DefaultAnalogExpressionManager pManager = DefaultAnalogExpressionManager.instance();
            InstanceManager.store(pManager, AnalogExpressionManager.class);
            // register new one for configuration
            ConfigureManager cmOD = InstanceManager.getNullableDefault(jmri.ConfigureManager.class);
            if (cmOD != null) {
                cmOD.registerConfig(pManager, jmri.Manager.LOGIXNG_ANALOG_EXPRESSIONS);
            }
        });
#else
       ThreadingUtil::runOnGUI(new DAEMRun());
#endif
    }

 void DAEMRun::run()
 {
  // register new one with InstanceManager
  DefaultAnalogExpressionManager* pManager = DefaultAnalogExpressionManager::instance();
  InstanceManager::store(pManager, "AnalogExpressionManager");
  // register new one for configuration
  ConfigureManager* cmOD = (AppsConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
  if (cmOD != nullptr) {
      cmOD->registerConfig(pManager, Manager::LOGIXNG_ANALOG_EXPRESSIONS);
  }
 }

    //@Override
    /*public*/  int DefaultAnalogExpressionManagerXml::loadOrder() const {
        return ((AnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->getXMLOrder();
    }

    /*private*/ /*final*/ /*static*/ Logger* DefaultAnalogExpressionManagerXml::log = LoggerFactory::getLogger("DefaultAnalogExpressionManagerXml");
