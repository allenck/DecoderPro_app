#include "defaultfemaledigitalactionsocketfactory.h"

/**
 * Factory class for DefaultFemaleDigitalActionSocket class.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
//@ServiceProvider(service = FemaleSocketFactory.class)
///*public*/  class DefaultFemaleDigitalActionSocketFactory implements FemaleSocketFactory {

    /*private*/ /*static*/ /*final*/ FemaleSocketManager::SocketType* DefaultFemaleDigitalActionSocketFactory::_femaleSocketType
= new DefaultFemaleDigitalActionSocketFactory::SocketType();


    //@Override
    /*public*/  FemaleSocketManager::SocketType* DefaultFemaleDigitalActionSocketFactory::getFemaleSocketType() {
        return _femaleSocketType;
    }


