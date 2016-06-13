#ifndef CONNECTIONCONFIGINTERFACE_H
#define CONNECTIONCONFIGINTERFACE_H
#include <QString>
#include <QWidget>

/**
 * Definition of objects to handle configuring a layout connection.
 *
 * @author      Bob Jacobsen   Copyright (C) 2001, 2003
 * @version	$Revision: 18905 $
 * @see JmrixConfigPane
 * @see AbstractSerialPortController
 */
/*public*/ /*interface*/class ConnectionConfigInterface
{

    /*public*/ virtual QString name() = 0;
    /*public*/ virtual void loadDetails(QWidget* details) = 0;
    /*public*/ virtual QString getInfo() = 0;

//    /*public*/ virtual PortAdapter* getAdapter() = 0;

    /*public*/ virtual QString getConnectionName() = 0;
    /*public*/ virtual QString getManufacturer() = 0;
    /*public*/ virtual void setManufacturer(QString Manufacturer) = 0;
    /*public*/ virtual void dispose()= 0;
    /*public*/ virtual bool getDisabled() = 0;
    /*public*/ virtual void setDisabled(bool disabled) = 0;

};

#endif // CONNECTIONCONFIGINTERFACE_H
