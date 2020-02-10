

#ifndef CONNECTIONCONFIG_H
#define CONNECTIONCONFIG_H
#include <QObject>
#include <QMetaType>
#include "portadapter.h"
#include "jpanel.h"

/**
 * Definition of objects to handle configuring a layout connection.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003
 * @version	$Revision: 28085 $
 * @see JmrixConfigPane
 * @see AbstractSerialPortController
 */
/*public*/ /*interface*/class  ConnectionConfig : public QObject
{
 //Q_OBJECT
public:
    ConnectionConfig(QObject* parent = 0) : QObject(parent) {}
    virtual ~ConnectionConfig() {}

    /*public*/ virtual QString name() =0;

    /*public*/ virtual void loadDetails(JPanel* /*details*/) =0;

    /*public*/ virtual QString getInfo()=0;

    /*public*/ virtual PortAdapter* getAdapter() =0;

    /*public*/ virtual QString getConnectionName() =0;

    /*public*/ virtual QString getManufacturer() =0;

    /*public*/ virtual void setManufacturer(QString /*Manufacturer*/) =0;

    /**
     * Register the ConnectionConfig with the running JMRI process.
     */
    /*public*/ virtual void _register() =0;

    /*public*/ virtual void dispose() =0;

    /*public*/ virtual bool getDisabled() =0;

    /*public*/ virtual void setDisabled(bool /*disabled*/) =0;

    /**
     * Determine if configuration needs to be written to disk.
     *
     * @return true if configuration needs to be saved, false otherwise
     */
    /*public*/ virtual bool isDirty() =0;


    /**
     * Determine if application needs to be restarted for configuration changes
     * to be applied.
     *
     * @return true if application needs to restart, false otherwise
     */
    /*public*/ virtual bool isRestartRequired() =0;

};
//Q_DECLARE_METATYPE(ConnectionConfig)
#endif // CONNECTIONCONFIG_H
