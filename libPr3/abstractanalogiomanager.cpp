#include "abstractanalogiomanager.h"
#include "systemconnectionmemo.h"
/**
 * Abstract partial implementation of a AnalogIOManager.
 * <p>
 * Based on AbstractSignalHeadManager.java and AbstractSensorManager.java
 *
 * @author Dave Duchamp      Copyright (C) 2004
 * @author Daniel Bergqvist  Copyright (C) 2020
 */
///*public*/  abstract class AbstractAnalogIOManager extends AbstractManager<AnalogIO>
//        implements AnalogIOManager {

    /**
     * Create a new AnalogIOManager instance.
     *
     * @param memo the system connection
     */
    /*public*/  AbstractAnalogIOManager::AbstractAnalogIOManager(SystemConnectionMemo* memo, QObject *parent) : AbstractManager(memo, parent) {
        //super(memo);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int AbstractAnalogIOManager::getXMLOrder() const {
        return Manager::ANALOGIOS;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  QChar AbstractAnalogIOManager::typeLetter() const {
        return 'V';
    }

    /**
     * Get bean type handled.
     *
     * @return a string for the type of object handled by this manager
     */
    //@Override
    //@Nonnull
    /*public*/  QString AbstractAnalogIOManager::getBeanTypeHandled(bool plural) const{
        return plural ? tr("AnalogIOs") : tr("AnalogIO");
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  /*Class<AnalogIO>*/QString AbstractAnalogIOManager::getNamedBeanClass() const{
        return "AnalogIO";
    }

//    /*private*/ final static Logger log = LoggerFactory.getLogger(AbstractAnalogIOManager.class);
