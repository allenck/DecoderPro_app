#include "defaultfemaledigitalactionsocketfactory.h"

/**
 * Factory class for DefaultFemaleDigitalActionSocket class.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
//@ServiceProvider(service = FemaleSocketFactory.class)
///*public*/  class DefaultFemaleDigitalActionSocketFactory implements FemaleSocketFactory {

    /*private*/ /*static*/ /*final*/ FemaleSocketManager::SocketType* _femaleSocketType = new SocketType();


    //@Override
    /*public*/  FemaleSocketManager::SocketType getFemaleSocketType() {
        return _femaleSocketType;
    }


