#ifndef CONNECTIONCONFIG_H
#define CONNECTIONCONFIG_H
#include <QObject>
#include <QMetaType>

/**
 * Definition of objects to handle configuring a layout connection.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003
 * @version	$Revision: 28085 $
 * @see JmrixConfigPane
 * @see AbstractSerialPortController
 */
class PortAdapter;
/*public*/ /*interface*/
class  ConnectionConfig : public QObject
{
 Q_OBJECT
public:
    ConnectionConfig(QObject* parent = 0) : QObject(parent) {}
    virtual ~ConnectionConfig() {}

    /*public*/ virtual QString name() {return "";}

    /*public*/ virtual void loadDetails(QWidget* /*details*/) {}

    /*public*/ virtual QString getInfo(){return "";}

    /*public*/ virtual PortAdapter* getAdapter() {return NULL;}

    /*public*/ virtual QString getConnectionName() {return "";}

    /*public*/ virtual QString getManufacturer() {return "";}

    /*public*/ virtual void setManufacturer(QString /*Manufacturer*/) {}

    /*public*/ virtual void dispose() {}

    /*public*/ virtual bool getDisabled() {return false;}

    /*public*/ virtual void setDisabled(bool /*disabled*/) {}

    /**
     * Determine if configuration needs to be written to disk.
     *
     * @return true if configuration needs to be saved, false otherwise
     */
    /*public*/ virtual bool isDirty() {return false;}


    /**
     * Determine if application needs to be restarted for configuration changes
     * to be applied.
     *
     * @return true if application needs to restart, false otherwise
     */
    /*public*/ virtual bool isRestartRequired() {return false;}

};
//Q_DECLARE_METATYPE(ConnectionConfig)
#endif // CONNECTIONCONFIG_H
