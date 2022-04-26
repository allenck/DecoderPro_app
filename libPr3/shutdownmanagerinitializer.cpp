#include "shutdownmanagerinitializer.h"
#include "loggerfactory.h"
#include "system.h"
#include "class.h"
#include "defaultshutdownmanager.h"

ShutDownManagerInitializer::ShutDownManagerInitializer(QObject *parent) : AbstractInstanceInitializer(parent)
{

}
/**
 * An initializer for the {@link jmri.ShutDownManager} that allows the
 * ShutDownManager to be used to be specified as a Java property.
 * <p>
 * This InstanceInitializer provides a
 * {@link jmri.managers.DefaultShutDownManager} unless the name of the class to
 * use as the ShutDownManager is specified in the {@code jmri.shutdownmanager}
 * Java System Property. If the property is specified, it must be a complete
 * name of a class that implements jmri.ShutDownManager and has a public default
 * constructor.
 */
//@ServiceProvider(service = InstanceInitializer.class)
//public class ShutDownManagerInitializer extends AbstractInstanceInitializer {

    /*private*/ /*static*/ /*final*/ Logger* ShutDownManagerInitializer::log = LoggerFactory::getLogger("ShutDownManagerInitializer");

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ /*<T>*/ QObject* ShutDownManagerInitializer::getDefault(/*Class<T>*/QString type) const {
        if (type == "ShutDownManager") {
            QString property = System::getProperty("jmri.shutdownmanager");
            if (property != nullptr) {
                try {
                    Class* c = Class::forName(property);
                    if (c->isAssignableFrom("ShutDownManager")) {
                        return (QObject*)c/*.getConstructor()*/->newInstance();
                    }
                    log->error(tr("Specified jmri.shutdownmanager value %1 is not a jmri.ShutDownManager subclass").arg(property));
                } catch ( ClassNotFoundException* e)
//                        InstantiationException |
//                        IllegalAccessException |
//                        InvocationTargetException |
//                        NoSuchMethodException |
//                        SecurityException e)
                        {
                    log->error(tr("Unable to instanciate ShutDownManager class %1 with default constructor").arg(property));
                }
            }
            return new DefaultShutDownManager();
        }
        return AbstractInstanceInitializer::getDefault(type);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QSet</*Class<?>*/QString>* ShutDownManagerInitializer::getInitalizes() {
        QSet</*Class<?>*/QString>* set = AbstractInstanceInitializer::getInitalizes();
        set->insert("ShutDownManager");
        return set;
    }
