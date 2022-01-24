#ifndef PORTADAPTER_H
#define PORTADAPTER_H

#include <QObject>
#include <QStringList>

class SystemConnectionMemo;
class PortAdapter : public QObject
{
    //Q_OBJECT
public:
    PortAdapter(QObject *parent = 0) : QObject(parent){}
    virtual ~PortAdapter() {}
    /**
     * Enables basic setup of a interface
     * for a jmrix implementation.
     *<P>
     * This has no e.g. serial-specific information.
     *
     * @author	Bob Jacobsen   Copyright (C) 2001, 2003, 2008, 2010
     * @version	$Revision: 20927 $
     * @see         jmri.jmrix.SerialConfigException
     * @since 2.3.1
     */
    //public interface PortAdapter  {

    /**
     * Configure all of the other jmrix widgets needed to work with this adapter
     */
    virtual void configure() {}

    /**
     * Query the status of this connection.  If all OK, at least
     * as far as is known, return true
     */
    virtual bool status()   {return false;}

    /**
     *  Open the connection
     */
    virtual void _connect()  {} // throws Exception;

    virtual QString getCurrentPortName()  {return "";}

    // returns the InputStream from the port
    virtual /*DataInputStream*/QDataStream* getInputStream()  {return NULL;}
    // returns the outputStream to the port
    virtual  /*DataOutputStream*/ QDataStream* getOutputStream()  {return NULL;}

    virtual QString getOption1Name()  {return "";}

    virtual QString getOption2Name() {return "";}

    virtual  QString getOption3Name() {return "";}

    virtual QString getOption4Name()  {return "";}

    /**
     * Set the first port option.  Only to be used after construction, but
     * before the openPort call
     */
    virtual void configureOption1(QString /*value*/)  {}

    /**
    * Set the second port option.  Only to be used after construction, but
    * before the openPort call
    */
    virtual void configureOption2(QString /*value*/)  {}

    /**
    * Set the third port option.  Only to be used after construction, but
    * before the openPort call
    */
    virtual void configureOption3(QString /*value*/)  {}

    /**
    * Set the fourth port option.  Only to be used after construction, but
    * before the openPort call
    */
    virtual void configureOption4(QString /*value*/) {}

    virtual QStringList getOptions() {return QStringList();}

    virtual bool isOptionAdvanced(QString /*option*/)  {return false;}

    virtual QString getOptionDisplayName(QString /*option*/) {return "";}

    virtual void setOptionState(QString /*option*/, QString /*value*/)  {}

    virtual QString getOptionState(QString /*option*/)  {return "";}

    virtual QStringList getOptionChoices(QString /*option*/)  {return QStringList();}

     /**
     * Return the System Manufacturers Name
     */
    virtual QString getManufacturer()  {return "";}

    /**
    * Set the System Manufacturers Name
    */
    virtual void setManufacturer(QString /*Manufacturer*/)  {}
    /**
     * Return the disabled state of the adapter
     */
    virtual bool getDisabled()    {return false;}

    /**
    * Sets whether the connection is disabled
    */
    virtual void setDisabled(bool /*disabled*/)  {}

/**
     * Get the user name for this adapter.
     *
     * @return the username or null
     */
    virtual /*public*/ QString getUserName() {return "";}

    /**
     * Set the user name for this adapter.
     *
     * @param userName
     * @throws IllegalArgumentException if another adapter has this user name
     */
    virtual /*public*/ void setUserName(QString /*userName*/) /*throws IllegalArgumentException;*/{}

    /**
     * Get the system prefix for this adapter.
     *
     * @return the system prefix or null
     */
    virtual /*public*/ QString getSystemPrefix() {return "";}

    /**
     * Set the system prefix for this adapter.
     *
     * @param systemPrefix
     * @throws IllegalArgumentException if another adapter has this system
     * prefix
     */
    virtual /*public*/ void setSystemPrefix(QString /*systemPrefix*/) /*throws IllegalArgumentException;*/ {}

     /*public*/ virtual SystemConnectionMemo* getSystemConnectionMemo() const {return NULL;}

    /**
     * Replace the existing SystemConnectionMemo with another one. Overriding
     * methods should throw an {@link java.lang.IllegalAccessException} if the
     * overriding class requires a specific subclass of SystemConnectionMemo. A
     * {@link java.lang.NullPointerException} should be thrown if the parameter
     * is null.
     *
     * @param connectionMemo
     */
    virtual /*public*/ void setSystemConnectionMemo(SystemConnectionMemo* /*connectionMemo*/)/* throws IllegalArgumentException;*/{}


    virtual void dispose() {}

    virtual void recover() {}
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

signals:
    
public slots:
    
};
//Q_DECLARE_INTERFACE(PortAdapter, "Port adapter")
#endif // PORTADAPTER_H
