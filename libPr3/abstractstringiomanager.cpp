#include "abstractstringiomanager.h"

/**
 * Abstract partial implementation of a StringIOManager.
 * <p>
 * Based on AbstractSignalHeadManager.java and AbstractSensorManager.java
 *
 * @author Dave Duchamp      Copyright (C) 2004
 * @author Daniel Bergqvist  Copyright (C) 2020
 */
///*public*/ abstract class AbstractStringIOManager extends AbstractManager<StringIO>
//        implements StringIOManager {

    /**
     * Create a new StringIOManager instance.
     *
     * @param memo the system connection
     */
    /*public*/ AbstractStringIOManager::AbstractStringIOManager(SystemConnectionMemo* memo, QObject* parent)
    : AbstractManager(memo, parent){
        //super(memo);
     setObjectName("AbstractStringIOManager");
    }

    /** {@inheritDoc} */
    //@Override
/*public*/ int AbstractStringIOManager::getXMLOrder() const {
    return Manager::STRINGIOS;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QChar AbstractStringIOManager::typeLetter() const{
    return 'C';
}

/**
 * Get bean type handled.
 *
 * @return a string for the type of object handled by this manager
 */
//@Override
//@Nonnull
/*public*/ QString AbstractStringIOManager::getBeanTypeHandled(bool plural) const{
    return tr(plural ? "StringIOs" : "StringIO");
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString AbstractStringIOManager::getNamedBeanClass()const {
        return "StringIO";
    }
