#include "swingtools.h"
#include "loggerfactory.h"
#include "runtimeexception.h"
#include "class.h"
#include "logixng/logixng_metatypes.h"
#include "abstractswingconfigurator.h"
#include "javatoqt.h"

/**
 * LogixNG Swing tools.
 *
 * @author Daniel Bergqvist 2019
 */
// /*public*/  /*final*/ class SwingTools {

    // Private constructor to ensure this class never get instanciated.
    /*private*/ SwingTools::SwingTools(QObject* parent): QObject(parent){
    }

    /**
     * Find the name of the adapter class for an object.
     *
     * @param o object of a configurable type
     * @return class name of adapter
     */
    /*public*/  /*static*/ QString SwingTools::adapterNameForObject(QObject* o) {
        return adapterNameForClass(o->metaObject()->className());
    }

    /**
     * Find the name of the adapter class for an object.
     *
     * @param c class of a configurable type
     * @return class name of adapter
     */
    /*public*/  /*static*/ QString SwingTools::adapterNameForClass(QString c) {
        QString className = c/*.getName()*/;
        log->trace(tr("handle object of class %1").arg(className));
        QString qClass = JavaToQt::getQtName(c);
        if(qClass.contains("::"))
        {
         return qClass+"Swing";
        }
        int lastDot = className.lastIndexOf(".");
        if (lastDot > 0) {
            // found package-class boundary OK
            QString result = className.mid(0, lastDot)
                    + ".swing."
                    + className.mid(lastDot + 1, className.length())
                    + "Swing";
            log->trace(tr("adapter class name is %1").arg(result));
            return result;
        } else {
            // No last dot found! This should not be possible in Java.
            log->error("No package name found, which is not yet handled!");
            throw new RuntimeException("No package name found, which is not yet handled!");
        }
    }

    /**
     * Get a SwingConfiguratorInterface for an object
     * @param object The object to get a SwingConfiguratorInterface of
     * @return a SwingConfiguratorInterface object
     */
    /*static*/ /*public*/  SwingConfiguratorInterface* SwingTools::getSwingConfiguratorForObject(QObject* object) {
        SwingConfiguratorInterface* adapter = nullptr;
        try {
#if 1
            adapter = (SwingConfiguratorInterface*) Class::forName(adapterNameForObject(object))/*->getDeclaredConstructor()*/->newInstance();
#endif
        }
        catch (ClassNotFoundException*  ex) {
        }
        catch ( IllegalAccessException* ex) {
         log->error(tr("Cannot load SwingConfiguratorInterface adapter for %1", object->metaObject()->className()), ex);
        }
        catch ( InstantiationException* ex) {
         log->error(tr("Cannot load SwingConfiguratorInterface adapter for %1", object->metaObject()->className()), ex);
        }
        catch (NoSuchMethodException* ex) {
            log->error(tr("Cannot load SwingConfiguratorInterface adapter for %1", object->metaObject()->className()), ex);
        }
        catch (InvocationTargetException* ex) {
            log->error(tr("Cannot load SwingConfiguratorInterface adapter for %1", object->metaObject()->className()), ex);
        }
        if (adapter != nullptr) {
            return adapter;
        } else {
            log->error(tr("Cannot load SwingConfiguratorInterface for %1").arg(object->metaObject()->className()));
            return nullptr;
        }
    }

    /**
     * Get a SwingConfiguratorInterface for a class
     * @param clazz The class to get a SwingConfiguratorInterface of
     * @return a SwingConfiguratorInterface object
     */
    /*static*/ /*public*/  SwingConfiguratorInterface* SwingTools::getSwingConfiguratorForClass(QString clazz) {
        SwingConfiguratorInterface* adapter = nullptr;
        if(!LogixNG_Metatypes::ng_done)
         new LogixNG_Metatypes();
        try {
            adapter = (AbstractSwingConfigurator*) Class::forName(adapterNameForClass(clazz))/*->getDeclaredConstructor()*/->newInstance();
        }
//        catch (ClassNotFoundException* ex) { // temp
//            log->error(tr("Cannot load SwingConfiguratorInterface adapter for %1").arg(clazz), ex);
//        }
        catch (IllegalAccessException* ex) {
            log->error(tr("Cannot load SwingConfiguratorInterface adapter for %1").arg(clazz), ex);
        }
        catch ( InstantiationException* ex) {
            log->error(tr("Cannot load SwingConfiguratorInterface adapter for %1").arg(clazz), ex);
        }
        catch (NoSuchMethodException* ex) {
            log->error(tr("Cannot load SwingConfiguratorInterface adapter for %1").arg(clazz), ex);
        }
        catch (InvocationTargetException* ex) {
            log->error(tr("Cannot load SwingConfiguratorInterface adapter for %1").arg(clazz), ex);
        }
        if (adapter != nullptr) {
            return adapter;
        } else {
            log->error(tr("Cannot load SwingConfiguratorInterface for %1").arg(clazz));
            return nullptr;
        }
    }


    /*private*/ /*final*/ /*static*/ Logger* SwingTools::log = LoggerFactory::getLogger("SwingTools");

