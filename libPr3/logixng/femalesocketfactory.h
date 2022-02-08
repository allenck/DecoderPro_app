#ifndef FEMALESOCKETFACTORY_H
#define FEMALESOCKETFACTORY_H
#include <QtCore>
#include "femalesocketmanager.h"
/**
 * Factory class for FemaleSocket classes.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
/*public*/ /*interface*/class  FemaleSocketFactory {
public:
    /*public*/ virtual FemaleSocketManager::SocketType* getFemaleSocketType()=0;

};
Q_DECLARE_INTERFACE(FemaleSocketFactory, "FemaleSocketFactory");

#endif // FEMALESOCKETFACTORY_H
