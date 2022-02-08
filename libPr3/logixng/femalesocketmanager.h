#ifndef FEMALESOCKETMANAGER_H
#define FEMALESOCKETMANAGER_H
#include <QtCore>
#include "base.h"

class FemaleSocketListener;
class BaseManager;
/**
 * Manager for FemaleSockets
 *
 * @author Daniel Bergqvist Copyright (C) 2020
 */
/*public*/ /*interface*/class FemaleSocketManager {
    public:
    /*public*/ /*interface*/class SocketType {
     public:
        /*public*/ virtual QString getName()=0;

        /*public*/ virtual QString getDescr()=0;

        /*public*/ virtual BaseManager/*<? extends MaleSocket>*/* getManager()=0;

        /*public*/ virtual FemaleSocket* createSocket(Base* parent, FemaleSocketListener* listener, QString name)=0;

    };

    /*public*/ virtual QMap<QString, SocketType*> getSocketTypes()=0;

    /*public*/ virtual SocketType* getSocketTypeByType(QString type)=0;

};

#endif // FEMALESOCKETMANAGER_H
