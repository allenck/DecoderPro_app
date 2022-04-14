#include "defaultfemaleanalogexpressionsocketfactory.h"
#include "femalesocketmanager.h"
/**
 * Factory class for DefaultFemaleAnalogExpressionSocket class.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
//@ServiceProvider(service = FemaleSocketFactory.class)
///*public*/  class DefaultFemaleAnalogExpressionSocketFactory implements FemaleSocketFactory {

    /*private*/ /*static*/ /*final*/ FemaleSocketManager::SocketType* DefaultFemaleAnalogExpressionSocketFactory::_femaleSocketType
= new DefaultFemaleAnalogExpressionSocketFactory::SocketType();


    //@Override
    /*public*/  FemaleSocketManager::SocketType* DefaultFemaleAnalogExpressionSocketFactory::getFemaleSocketType() {
        return _femaleSocketType;
    }



