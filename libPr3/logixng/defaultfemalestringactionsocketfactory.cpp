#include "defaultfemalestringactionsocketfactory.h"

/**
 * Factory class for DefaultFemaleStringActionSocket class.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
//@ServiceProvider(service = FemaleSocketFactory.class)
///*public*/  class DefaultFemaleStringActionSocketFactory implements FemaleSocketFactory {

    /*private*/ /*static*/ /*final*/ FemaleSocketManager::SocketType* DefaultFemaleStringActionSocketFactory::_femaleSocketType = new FemaleSocketManager::SocketType();


    //@Override
    /*public*/  FemaleSocketManager::SocketType* DefaultFemaleStringActionSocketFactory::getFemaleSocketType() {
        return _femaleSocketType;
    }




