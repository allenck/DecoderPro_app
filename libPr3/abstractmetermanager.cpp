#include "abstractmetermanager.h"

/**
 * Default implementation of a MeterManager.
 *
 * @author Dave Duchamp      Copyright (C) 2004
 * @author Daniel Bergqvist  Copyright (C) 2020
 */
///*public*/ class AbstractMeterManager extends AbstractManager<Meter>
//        implements MeterManager {

    /**
     * Create a new MeterManager instance.
     *
     * @param memo the system connection
     */
    /*public*/ AbstractMeterManager::AbstractMeterManager(SystemConnectionMemo* memo, QObject* parent) : MeterManager(memo, parent){
        //super(memo);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int AbstractMeterManager::getXMLOrder() const {
        return Manager::METERS;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ char AbstractMeterManager::typeLetter() const{
        return 'V';
    }

    /**
     * Get bean type handled.
     *
     * @return a string for the type of object handled by this manager
     */
    //@Override
    //@Nonnull
    /*public*/ QString AbstractMeterManager::getBeanTypeHandled(bool plural) const{
        return (plural ? tr("Meters") : tr("Meter"));
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString getNamedBeanClass() {
        return "Meter";
    }

    /*public*/ NamedBean *AbstractMeterManager::getBySystemName(QString name) const
    {
     return _tsys->value(name);
    }

    /*public*/ NamedBean* AbstractMeterManager::getByUserName(QString key) const
    {
     return _tuser->value(key);
    }
