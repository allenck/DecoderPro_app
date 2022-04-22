#include "defaultnamedtablemanagerxml.h"
#include "loggerfactory.h"
#include "defaultnamedtablemanager.h"
#include "runtimeexception.h"
#include "class.h"
#include "defaultnamedtablemanager.h"
#include "instancemanager.h"
#include "appsconfigurationmanager.h"
#include "abstractnamedtable.h"


/**
 * Provides the functionality for configuring DefaultNamedTableManager
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
// /*public*/  class DefaultNamedTableManagerXml extends AbstractManagerXml {


/*public*/  DefaultNamedTableManagerXml::DefaultNamedTableManagerXml(QObject* parent) : AbstractManagerXml(parent){
}

/**
 * Default implementation for storing the contents of a NamedTableManager
 *
 * @param o Object to store, of type LogixManager
 * @return Element containing the complete info
 */
//@Override
/*public*/  QDomElement DefaultNamedTableManagerXml::store(QObject* o) {
    QDomElement tables = doc.createElement("LogixNGTables");
    setStoreElementClass(tables);
    DefaultNamedTableManager* tm = (DefaultNamedTableManager*) o;
    if (tm != nullptr) {
        if (tm->AbstractManager::getNamedBeanSet().isEmpty()) return QDomElement();
        for (NamedBean* nb: tm->AbstractManager::getNamedBeanSet()) {
         NamedTable* table = (AbstractNamedTable*)nb->self();
            log->debug("table system name is " + table->getSystemName());  // NOI18N
            try {
                QDomElement e = ConfigXmlManager::elementFromObject(table);
                if (!e.isNull()) {
                    tables.appendChild(e);
                }
            } catch (RuntimeException* e) {
                log->error(tr("Error storing table: %1").arg(e->toString()), e);
            }
        }
    }
    return (tables);
}

/**
 * Subclass provides implementation to create the correct top element,
 * including the type information. Default implementation is to use the
 * local class here.
 *
 * @param expressions The top-level element being created
 */
/*public*/  void DefaultNamedTableManagerXml::setStoreElementClass(QDomElement expressions) {
    expressions.setAttribute("class", "jmri.jmrit.logixng.implementation.configurexml.DefaultNamedTableManagerXml");  // NOI18N
}

/**
 * Create a NamedTableManager object of the correct class, then
 * register and fill it.
 *
 * @param sharedExpression  Shared top level Element to unpack.
 * @param perNodeExpression Per-node top level Element to unpack.
 * @return true if successful
 */
//@Override
/*public*/  bool DefaultNamedTableManagerXml::load(QDomElement sharedExpression, QDomElement perNodeExpression) {
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
/*public*/  void DefaultNamedTableManagerXml::loadTables(QDomElement expressions) {

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
            /*Constructor<?>*/Class* c = nullptr;
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
 * Replace the current NamedTableManager, if there is one, with one newly created
 * during a load operation. This is skipped if they are of the same absolute
 * type.
 */
/*protected*/ void DefaultNamedTableManagerXml::replaceExpressionManager() {
    if (QString(InstanceManager::getDefault("NamedTableManager")->metaObject()->className())
             ==("DefaultNamedTableManager")) {
        return;
    }
    // if old manager exists, remove it from configuration process
    if (InstanceManager::getNullableDefault("NamedTableManager") != nullptr) {
        ConfigureManager* cmOD = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
        if (cmOD != nullptr) {
            cmOD->deregister(InstanceManager::getDefault("NamedTableManager"));
        }

    }
#if 0 // TODO::
    ThreadingUtil::runOnGUI(() -> {
        // register new one with InstanceManager
        DefaultNamedTableManager pManager = DefaultNamedTableManager.instance();
        InstanceManager.store(pManager, NamedTableManager.class);
        // register new one for configuration
        ConfigureManager cmOD = InstanceManager.getNullableDefault(jmri.ConfigureManager.class);
        if (cmOD != null) {
            cmOD.registerConfig(pManager, jmri.Manager.LOGIXNG_TABLES);
        }
    });
#else
 ThreadingUtil::runOnGUI(new DNTMRun());
#endif
}

void DNTMRun::run()
{
 // register new one with InstanceManager
 DefaultNamedTableManager* pManager = DefaultNamedTableManager::instance();
 InstanceManager::store(pManager, "NamedTableManager");
 // register new one for configuration
 ConfigureManager* cmOD = (AppsConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
 if (cmOD != nullptr) {
     cmOD->registerConfig(pManager, Manager::LOGIXNG_TABLES);
 }
}

//@Override
/*public*/  int DefaultNamedTableManagerXml::loadOrder() const {
    return ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->getXMLOrder();
}

/*private*/ /*final*/ /*static*/ Logger* DefaultNamedTableManagerXml::log = LoggerFactory::getLogger("DefaultNamedTableManagerXml");
