#include "defaultfemaledigitalexpressionsocketfactory.h"

/**
 * Factory class for DefaultFemaleDigitalExpressionSocket class.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
//@ServiceProvider(service = FemaleSocketFactory.class)
///*public*/  class DefaultFemaleDigitalExpressionSocketFactory implements FemaleSocketFactory {

    /*private*/ static /*final*/ FemaleSocketManager::SocketType* _femaleSocketType = new SocketType();


    //@Override
    /*public*/  FemaleSocketManager.SocketType getFemaleSocketType() {
        return _femaleSocketType;
    }


