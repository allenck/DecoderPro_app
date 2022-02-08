#include "defaultfemaleanalogactionsocketfactory.h"
#include "femalesocketmanager.h"
/**
 * Factory class for DefaultFemaleAnalogActionSocket class.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
//@ServiceProvider(service = FemaleSocketFactory.class)
///*public*/  class DefaultFemaleAnalogActionSocketFactory implements FemaleSocketFactory {

    /*private*/ /*static*/ /*final*/ FemaleSocketManager::SocketType* _femaleSocketType
     = new  DefaultFemaleAnalogActionSocketFactory::SocketType();


    //@Override
    /*public*/  FemaleSocketManager::SocketType* DefaultFemaleAnalogActionSocketFactory::getFemaleSocketType() {
        return _femaleSocketType;
    }


