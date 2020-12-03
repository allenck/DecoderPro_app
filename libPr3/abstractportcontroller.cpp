#include "abstractportcontroller.h"
#include "exceptions.h"
#include "systemconnectionmemo.h"
#include "sleeperthread.h"
#include <QDataStream>
#include "loggerfactory.h"

/*protected*/ AbstractPortController::AbstractPortController(SystemConnectionMemo* connectionMemo, QObject *parent)
    : NetworkPortAdapter(parent)
{
 this->parent = parent;
 //These are to support the old legacy files.
 option1Name = "1";
 option2Name = "2";
 option3Name = "3";
 option4Name = "4";
 opened = false;
 mDisabled = false;
 allowConnectionRecovery = false;
 reconnectinterval = 1000;
 retryAttempts = 10;
 this->connectionMemo = connectionMemo;
}
/**
 * Provide an abstract base for *PortController classes.
 * <P>
 * This is complicated by the lack of multiple inheritance.
 * SerialPortAdapter is an Interface, and its implementing
 * classes also inherit from various PortController types.  But we
 * want some common behaviors for those, so we put them here.
 *
 * @see jmri.jmrix.SerialPortAdapter
 *
 * @author			Bob Jacobsen   Copyright (C) 2001, 2002
 * @version			$Revision: 21226 $
 */
//abstract public class AbstractPortController implements PortAdapter {

    // returns the InputStream from the port
//    /*public abstract*/ /*DataInputStream*/ QByteArray AbstractPortController::getInputStream();

    // returns the outputStream to the port
//    /*public abstract*/ /*DataOutputStream*/QByteArray AbstractPortController::getOutputStream();
/**
 * Clean up before removal.
 *
 * Overriding methods must call <code>super.dispose()</code> or document why
 * they are not calling the overridden implementation. In most cases,
 * failure to call the overridden implementation will cause user-visible
 * error.
 */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractPortController::dispose() {
    this->getSystemConnectionMemo()->dispose();
}

// check that this object is ready to operate
/*public*/ bool AbstractPortController::status() {return opened;}

/*protected*/ void AbstractPortController::setOpened() {opened = true; }
/*protected*/ void AbstractPortController::setClosed() {opened = false; }

AbstractPortController::~AbstractPortController()
{
 dispose();
}

//    /*abstract public*/ QString getCurrentPortName();
 /*
     The next set of configureOptions are to support the old configuration files.
 */
 /*public*/ void AbstractPortController::configureOption1(QString value)
{
 if(options.contains(option1Name))
 {
  options.value(option1Name)->configure(value);
 }
}

/*public*/ void AbstractPortController::configureOption2(QString value)
{
 if(options.contains(option2Name))
 {
  options.value(option2Name)->configure(value);
 }
}

/*public*/ void AbstractPortController::configureOption3(QString value)
{
 if(options.contains(option3Name))
 {
  options.value(option3Name)->configure(value);
 }
}

/*public*/ void AbstractPortController::configureOption4(QString value)
{
 if(options.contains(option4Name))
 {
  options.value(option4Name)->configure(value);
 }
}

/*
 The next set of getOption Names are to support legacy configuration files
*/
/*public*/ QString AbstractPortController::getOption1Name(){
    return option1Name;
}

/*public*/ QString AbstractPortController::getOption2Name(){
    return option2Name;
}

/*public*/ QString AbstractPortController::getOption3Name(){
    return option3Name;
}

/*public*/ QString AbstractPortController::getOption4Name(){
    return option4Name;
}

/**
* Get a list of all the options configured against this adapter.
*/
/*public*/ QStringList AbstractPortController::getOptions()
{
 QStringList arr;
 //Enumeration<String> en = options.keys();
 QMapIterator<QString, Option*> en(options);
 while (en.hasNext())
 {
  en.next();
  arr << en.key();
 }
 // java.util.Arrays.sort(arr);
 return arr;
}

/**
* Set the value of an option
*/
/*public*/ void AbstractPortController::setOptionState( QString option, QString value)
{
 if(options.contains(option))
 {
  options.value(option)->configure(value);
 }
}

/**
*  Get the value of a specific option
*/
/*public*/ QString AbstractPortController::getOptionState(QString option){
    if(options.contains(option)){
        return options.value(option)->getCurrent();
    }
    return "";
}

/**
*   return a list of the various choices allowed with an option.
*/
/*public*/ QStringList AbstractPortController::getOptionChoices(QString option)
{
if(options.contains(option))
{
return options.value(option)->getOptions();
}
return QStringList();
}

/*public*/ QString AbstractPortController::getOptionDisplayName(QString option){
    if(options.contains(option)){
        return options.value(option)->getDisplayText();
    }
    return "";
}

/*public*/ bool AbstractPortController::isOptionAdvanced(QString option){
    if(options.contains(option)){
        return options.value(option)->isAdvanced();
    }
    return false;
}

/**
* Get and set of the Manufacturer for network (TCP/IP) based
* connections is handled by the ConnectionConfig code in each
* connector.  this is here as we implement the serialdriveradpter.
*/
/*public*/ QString AbstractPortController::getManufacturer() { return manufacturerName; }
/*public*/ void AbstractPortController::setManufacturer(QString manufacturer) {
log->debug("update manufacturer from \""+manufacturerName+"\" to \""+manufacturer + "\"");
 manufacturerName = manufacturer;
}

/*public*/ bool AbstractPortController::getDisabled() { return mDisabled; }

/**
 * Set the connection disabled or enabled. By default connections are
 * enabled.
 *
 * If the implementing class does not use a
 * {@link jmri.jmrix.SystemConnectionMemo}, this method must be overridden.
 * Overriding methods must call <code>super.setDisabled(boolean)</code> to
 * ensure the configuration change state is correctly set.
 *
 * @param disabled true if connection should be disabled
 */
//@Override
/*public*/ void AbstractPortController::setDisabled(bool disabled) {
    this->getSystemConnectionMemo()->setDisabled(disabled);
}

//@Override
/*public*/ QString AbstractPortController::getSystemPrefix() {
    return this->getSystemConnectionMemo()->getSystemPrefix();
}

//@Override
/*public*/ void AbstractPortController::setSystemPrefix(QString systemPrefix) {
    if (!this->getSystemConnectionMemo()->setSystemPrefix(systemPrefix)) {
        throw IllegalArgumentException();
    }
}

//@Override
/*public*/ QString AbstractPortController::getUserName() {
    return this->getSystemConnectionMemo()->getUserName();
}

//@Override
/*public*/ void AbstractPortController::setUserName(QString userName) {
    if (!this->getSystemConnectionMemo()->setUserName(userName)) {
        throw IllegalArgumentException();
    }
}



//abstract public void recover();


/*protected static */void AbstractPortController::safeSleep(long milliseconds, QString /*s*/) {
//          try {
//             Thread.sleep(milliseconds);
//          }
//          catch (InterruptedException e) {
//             log->error("Sleep Exception raised during reconnection attempt" +s);
//          }
 SleeperThread::msleep(milliseconds);
}

//@Override
/*public*/ bool AbstractPortController::isDirty()
{
 bool isDirty = this->getSystemConnectionMemo()->isDirty();
 if (!isDirty)
 {
  foreach (Option* option, this->options.values())
  {
   isDirty = option->isDirty();
   if (isDirty)
   {
    break;
   }
  }
 }
 return isDirty;
}

//@Override
/*public*/ bool AbstractPortController::isRestartRequired()
{
 // Override if any option should not be considered when determining if a
 // change requires JMRI to be restarted.
 return this->isDirty();
}

/**
 * Service method to purge a stream of initial contents
 * while opening the connection.
 */
 //@SuppressFBWarnings(value = "SR_NOT_CHECKED", justification = "skipping all, don't care what skip() returns")
 /*protected*/ void AbstractPortController::purgeStream(/*@Nonnull*/ QDataStream* serialStream) //throw (IOException)
{
#if 0
    int count = serialStream->available();
    log.debug("input stream shows " + count + " bytes available");
    while (count > 0) {
        serialStream.skip(count);
        count = serialStream.available();
    #else
 while(!serialStream->atEnd())
  serialStream->skipRawData(1);
#endif
}
/**
 * Get the {@link jmri.jmrix.SystemConnectionMemo} associated with this
 * object.
 *
 * This method should only be overridden to ensure that a specific subclass
 * of SystemConnectionMemo is returned. The recommended pattern is:      <code>
 * public MySystemConnectionMemo getSystemConnectionMemo() {
 *  return (MySystemConnectionMemo) super.getSystemConnectionMemo();
 * }
 * </code>
 *
 * @return a SystemConnectionMemo
 */
//@Override
/*public*/ SystemConnectionMemo* AbstractPortController::getSystemConnectionMemo() const
{
 return this->connectionMemo;
}
/**
 * Set the {@link jmri.jmrix.SystemConnectionMemo} associated with this
 * object.
 *
 * Overriding implementations must call
 * <code>super.setSystemConnectionMemo(memo)</code> at some point to ensure
 * the SystemConnectionMemo gets set.
 *
 * @param connectionMemo
 */
//@Override
/*public*/ void AbstractPortController::setSystemConnectionMemo(SystemConnectionMemo* connectionMemo)
{
 if (connectionMemo == NULL)
 {
  throw NullPointerException();
 }
 this->connectionMemo = connectionMemo;
}
/*static*/ /*private*/ Logger* AbstractPortController::log = LoggerFactory::getLogger("AbstractPortController");
