#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H
#include <QObject>
/**
 * @author Brett Hoffman Copyright (C) 2010
 */
/*public*/ /*interface*/class ControllerInterface : public QObject
{
public slots:
    /*public*/ inline virtual void sendPacketToDevice(QString /*message*/) {}

};
#endif // CONTROLLERINTERFACE_H
