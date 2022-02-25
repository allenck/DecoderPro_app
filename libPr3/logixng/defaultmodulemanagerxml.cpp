#include "defaultmodulemanagerxml.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "modulemanager.h"
#include "defaultmodulemanager.h"
#include "runtimeexception.h"
#include "class.h"

/**
 * Provides the functionality for configuring DefaultModuleManager
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
// /*public*/  class DefaultModuleManagerXml extends AbstractManagerXml {


/*public*/  DefaultModuleManagerXml::DefaultModuleManagerXml(QObject *parent) : AbstractManagerXml(parent) {
}

/**
 * Default implementation for storing the contents of a ModuleManager
 *
 * @param o Object to store, of type LogixManager
 * @return Element containing the complete info
 */
//@Override
/*public*/  QDomElement DefaultModuleManagerXml::store(QObject* o) {
    QDomElement expressions = doc.createElement("LogixNGModules");
    setStoreElementClass(expressions);
    DefaultModuleManager* tm = (DefaultModuleManager*) o;
    if (tm != nullptr) {
        if (tm->AbstractManager::getNamedBeanSet().isEmpty()) return QDomElement();
        for (NamedBean* nb : tm->AbstractManager::getNamedBeanSet()) {
         Module* module = (Module*)nb->self();
            try {
                QDomElement e = ConfigXmlManager::elementFromObject(module->self());
                if (!e.isNull()) {
                    expressions.appendChild(e);
                }
            } catch (RuntimeException* e) {
                log->error(tr("Error storing action: %1").arg(e->toString()), e);
            }
        }
    }
    return expressions;
}

/**
 * Subclass provides implementation to create the correct top element,
 * including the type information. Default implementation is to use the
 * local class here.
 *
 * @param expressions The top-level element being created
 */
/*public*/  void DefaultModuleManagerXml::setStoreElementClass(QDomElement expressions) {
    expressions.setAttribute("class", "jmri.jmrit.logixng.implementation.configurexml.DefaultModuleManagerXml");  // NOI18N
}

/**
 * Create a ModuleManager object of the correct class, then
 * register and fill it.
 *
 * @param sharedExpression  Shared top level Element to unpack.
 * @param perNodeExpression Per-node top level Element to unpack.
 * @return true if successful
 */
//@Override
/*public*/  bool DefaultModuleManagerXml::load(QDomElement sharedExpression, QDomElement perNodeExpression) {
    // create the master object
    replaceExpressionManager();
    // load individual sharedLogix
    loadTables(sharedExpression);
    return true;
}

/**
 * Utility method to load the individual Logix objects. If there's no
 * additional info needed for a specific logix type, invoke this with the
 * parent of the set of Logix elements.
 *
 * @param expressions Element containing the Logix elements to load.
 */
/*public*/  void DefaultModuleManagerXml::loadTables(QDomElement expressions) {

    QDomNodeList expressionList = expressions.childNodes();  // NOI18N
    log->debug("Found " + QString::number(expressionList.size()) + " tables");  // NOI18N

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
           /* Constructor<?> */Class* c = nullptr;
            try {
                c = clazz->getConstructor();
            } catch (NoSuchMethodException* /*| SecurityException*/ ex) {
                log->error("cannot create constructor", ex);
            }

            if (c != nullptr) {
                try {
                    AbstractNamedBeanManagerConfigXML* o = (AbstractNamedBeanManagerConfigXML*)c->newInstance();
                    o->load(expressionList.at(i).toElement(), QDomElement());
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
 * Replace the current ModuleManager, if there is one, with one newly created
 * during a load operation. This is skipped if they are of the same absolute
 * type.
 */
/*protected*/ void DefaultModuleManagerXml::replaceExpressionManager() {
    if (QString(InstanceManager::getDefault("ModuleManager")->metaObject()->className())
             == ("DefaultModuleManager")) {
        return;
    }
    // if old manager exists, remove it from configuration process
    if (InstanceManager::getNullableDefault("ModuleManager") != nullptr) {
        ConfigureManager* cmOD = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
        if (cmOD != nullptr) {
            cmOD->deregister(InstanceManager::getDefault("ModuleManager"));
        }

    }
#if 0
    ThreadingUtil.runOnGUI(() -> {
        // register new one with InstanceManager
        DefaultModuleManager pManager = DefaultModuleManager.instance();
        InstanceManager.store(pManager, ModuleManager.class);
        // register new one for configuration
        ConfigureManager cmOD = InstanceManager.getNullableDefault(jmri.ConfigureManager.class);
        if (cmOD != null) {
            cmOD.registerConfig(pManager, jmri.Manager.LOGIXNG_TABLES);
        }
    });
#endif
}

////@Override
/*public*/  int DefaultModuleManagerXml::loadOrder() const {
    return ((ModuleManager*)InstanceManager::getDefault("ModuleManager"))->getXMLOrder();
}

/*private*/ /*final*/ /*static*/ Logger* DefaultModuleManagerXml::log = LoggerFactory::getLogger("DefaultModuleManagerXml");
