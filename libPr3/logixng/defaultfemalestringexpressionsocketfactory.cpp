#include "defaultfemalestringexpressionsocketfactory.h"

/**
 * Factory class for DefaultFemaleStringExpressionSocket class.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
//@ServiceProvider(service = FemaleSocketFactory.class)
///*public*/  class DefaultFemaleStringExpressionSocketFactory : public FemaleSocketFactory {

    /*private*/ /*static*/ /*final*/ FemaleSocketManager::SocketType* DefaultFemaleStringExpressionSocketFactory::_femaleSocketType =
      new DefaultFemaleStringExpressionSocketFactory::SocketType();


    //@Override
    /*public*/  FemaleSocketManager::SocketType* DefaultFemaleStringExpressionSocketFactory::getFemaleSocketType() {
        return _femaleSocketType;
    }



