#include "defaultstringexpressionmanagerxml.h"
#include "stringexpressionmanager.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultmalestringexpressionsocket.h"
#include "runtimeexception.h"
#include "class.h"
#include "defaultstringexpressionmanager.h"
#include "appsconfigurationmanager.h"
#include "abstractstringexpression.h"
/**
 * Provides the functionality for configuring ExpressionManagers
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
// /*public*/  class DefaultStringExpressionManagerXml extends AbstractManagerXml {


/*public*/  DefaultStringExpressionManagerXml::DefaultStringExpressionManagerXml(QObject *parent) : AbstractManagerXml(parent){
}

/**
 * Default implementation for storing the contents of a LogixManager
 *
 * @param o Object to store, of type LogixManager
 * @return Element containing the complete info
 */
//@Override
/*public*/  QDomElement DefaultStringExpressionManagerXml::store(QObject* o) {
    QDomElement expressions = doc.createElement("LogixNGStringExpressions");
    setStoreElementClass(expressions);
    StringExpressionManager* tm = (DefaultStringExpressionManager*) o;
    if (tm != nullptr) {
     QSet<NamedBean*> set;
        if ((set=tm->getNamedBeanSet()).isEmpty()) return QDomElement();
        for (NamedBean* nb : tm->getNamedBeanSet()) {
            AbstractStringExpression* expression = (AbstractStringExpression*)nb->self();
            log->debug("expression system name is " + expression->AbstractNamedBean::getSystemName());  // NOI18N
//               log.error("expression system name is " + expression.getSystemName() + ", " + expression.getLongDescription());  // NOI18N
            try {
                QList<QDomElement> elements = QList<QDomElement>();
                // The male socket may be embedded in other male socketsb
                Base* base = expression->getParent();
                QObject* o = (QObject*)base;
                MaleStringExpressionSocket* a = (DefaultMaleStringExpressionSocket*)o;
                while (!(static_cast<DefaultMaleStringExpressionSocket*>(a->bself()))) {
                    elements.append(storeMaleSocket(a));
                    a = (DefaultMaleStringExpressionSocket*) a->getObject()->bself();
                }
                QDomElement e = ConfigXmlManager::elementFromObject(((AbstractMaleSocket*)a->bself())->getObject()->bself());
                if (e != QDomElement()) {
                    for (int i=0; i <  elements.size(); i++)
                    {
                     QDomElement ee = elements.at(i).toElement();
                     e.appendChild(ee);
                    }
//                        e.addContent(storeMaleSocket(expression));
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
/*public*/  void DefaultStringExpressionManagerXml::setStoreElementClass(QDomElement expressions) {
    expressions.setAttribute("class", "jmri.jmrit.logixng,implementation.configurexml.DefaultStringExpressionManagerXml");  // NOI18N
}

/**
 * Create a StringExpressionManager object of the correct class, then
 * register and fill it.
 *
 * @param sharedExpression  Shared top level Element to unpack.
 * @param perNodeExpression Per-node top level Element to unpack.
 * @return true if successful
 */
//@Override
/*public*/  bool DefaultStringExpressionManagerXml::load(QDomElement sharedExpression, QDomElement perNodeExpression) {
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
/*public*/  void DefaultStringExpressionManagerXml::loadExpressions(QDomElement expressions) {

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

                    MaleSocket* oldLastItem = ((StringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->getLastRegisteredMaleSocket();
                    o->load(expressionList.at(i).toElement(), QDomElement());

                    // Load male socket data if a new bean has been registered
                    MaleSocket* newLastItem = ((StringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->getLastRegisteredMaleSocket();
                    if (newLastItem != oldLastItem) loadMaleSocket(expressionList.at(i).toElement(), newLastItem);
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
 * Replace the current LogixManager, if there is one, with one newly created
 * during a load operation. This is skipped if they are of the same absolute
 * type.
 */
/*protected*/ void DefaultStringExpressionManagerXml::replaceExpressionManager() {
    if (QString(InstanceManager::getDefault("StringExpressionManager")->metaObject()->className())
             == ("DefaultStringExpressionManager")) {
        return;
    }
    // if old manager exists, remove it from configuration process
    if (InstanceManager::getNullableDefault("StringExpressionManager") != nullptr) {
        ConfigureManager* cmOD = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
        if (cmOD != nullptr) {
            cmOD->deregister(InstanceManager::getDefault("StringExpressionManager"));
        }

    }

#if 0// TODO:
    ThreadingUtil::runOnGUI(() -> {
        // register new one with InstanceManager
        DefaultStringExpressionManager pManager = DefaultStringExpressionManager.instance();
        InstanceManager.store(pManager, StringExpressionManager.class);
        // register new one for configuration
        ConfigureManager cmOD = InstanceManager.getNullableDefault(jmri.ConfigureManager.class);
        if (cmOD != null) {
            cmOD.registerConfig(pManager, jmri.Manager.LOGIXNG_STRING_EXPRESSIONS);
        }
    });
#else
    ThreadingUtil::runOnGUI(new DSEMRun());
#endif
}

void DSEMRun::run()
{
 // register new one with InstanceManager
 DefaultStringExpressionManager* pManager = DefaultStringExpressionManager::instance();
 InstanceManager::store(pManager, "StringExpressionManager");
 // register new one for configuration
 ConfigureManager* cmOD = (AppsConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
 if (cmOD != nullptr) {
     cmOD->registerConfig(pManager, Manager::LOGIXNG_STRING_EXPRESSIONS);
 }

}
//@Override
/*public*/  int DefaultStringExpressionManagerXml::loadOrder() const {
    return ((StringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->getXMLOrder();
}

/*private*/ /*final*/ /*static*/ Logger* DefaultStringExpressionManagerXml::log = LoggerFactory::getLogger("DefaultStringExpressionManagerXml");

