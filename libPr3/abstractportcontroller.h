#ifndef ABSTRACTPORTCONTROLLER_H
#define ABSTRACTPORTCONTROLLER_H
#include "portadapter.h"
#include <QMap>
#include "logger.h"
#include <QStringList>
#include "libPr3_global.h"
//#include "serialportadapter.h"
#include "loconet/networkportadapter.h"
#include "exceptions.h"

class LIBPR3SHARED_EXPORT Option
{
 public:
  Option();
  Option(QString displayText, QStringList options, bool advanced);
  Option(QString displayText, QStringList options);
  void configure(QString value);
  QString getCurrent();
  QStringList getOptions();
  QString getDisplayText();
  bool isAdvanced();
  bool isDirty();

 private:
  QString currentValue;
  QString displayText;
  QStringList options;
  bool advancedOption; // = true;

 protected:
  /*protected*/ QString manufacturerName;// = null;

};

class LIBPR3SHARED_EXPORT AbstractPortController : public NetworkPortAdapter
{
    Q_OBJECT
public:
    ~AbstractPortController();
    /*public*/ void dispose();
    // returns the InputStream from the port
    /*public abstract*/ /*DataInputStream*/ virtual QDataStream* getInputStream() {return NULL;}
    // returns the outputStream to the port
    /*public abstract*/ /*DataOutputStream*/virtual QDataStream* getOutputStream(){return NULL;}
    // check that this object is ready to operate
    /*public*/ bool status();
    /*abstract public*/ virtual QString getCurrentPortName()  {return "";}
    /*
        The next set of configureOptions are to support the old configuration files.
    */
    /*public*/  void configureOption1(QString value);
    /*public*/  void configureOption2(QString value);
    /*public*/  void configureOption3(QString value);
    /*public*/  void configureOption4(QString value);
    /*
    The next set of getOption Names are to support legacy configuration files
    */
    /*public*/  QString getOption1Name();
    /*public*/  QString getOption2Name();
    /*public*/  QString getOption3Name();
    /*public*/  QString getOption4Name();
    /**
    * Get a list of all the options configured against this adapter.
    */
    /*public*/  QStringList getOptions();
    /**
    * Set the value of an option
    */
    /*public*/  void setOptionState(QString option, QString value);
    /**
    *  Get the value of a specific option
    */
    /*public*/  QString getOptionState(QString option);
    /**
    *   return a list of the various choices allowed with an option.
    */
    /*public*/  QStringList getOptionChoices(QString option);
    /*public*/  QString getOptionDisplayName(QString option);
    /*public*/  bool isOptionAdvanced(QString option);
    /**
    * Get and set of the Manufacturer for network (TCP/IP) based
    * connections is handled by the ConnectionConfig code in each
    * connector.  this is here as we implement the serialdriveradpter.
    */
    /*public*/  QString getManufacturer();
    /*public*/  void setManufacturer(QString manufacturer);
    /*public*/  bool getDisabled();
    /*public*/ void setDisabled(bool disabled) ;
    /*public*/ QString getSystemPrefix();
    /*public*/ void setSystemPrefix(QString systemPrefix);
    /*public*/ QString getUserName() ;
    /*public*/ void setUserName(QString userName);
    /*abstract public*/ virtual void recover() {}
    /*public*/ bool isDirty() override;
    /*public*/ bool isRestartRequired();
    /*public*/ void setSystemConnectionMemo(SystemConnectionMemo* connectionMemo);
    /*public*/ SystemConnectionMemo* getSystemConnectionMemo() const;

signals:
    
public slots:
private:
    static Logger* log;
    // By making this private, and not protected, we are able to require that
    // all access is through the getter and setter, and that subclasses that
    // override the getter and setter must call the super implemenations of the
    // getter and setter. By channelling setting through a single method, we can
    // ensure this is never null.
    SystemConnectionMemo* connectionMemo;
protected:
    explicit AbstractPortController(SystemConnectionMemo* connectionMemo, QObject *parent = 0);
    QMap<QString, Option*> options;
    QObject* parent;
 //These are to support the old legacy files.
 QString option1Name;
 QString option2Name;
 QString option3Name;
 QString option4Name;
 /*protected*/ bool opened = false;
 /*protected*/ void setOpened();
 /*protected*/ void setClosed();
 /*protected*/ bool mDisabled;
 /*protected*/ bool allowConnectionRecovery = false;
 /*protected*/ int reconnectinterval = 1000;
 /*protected*/ int retryAttempts = 10;
 /*protected*/ static void safeSleep(long milliseconds, QString s);
 /*protected*/ QString manufacturerName;// = null;
 /*protected*/ void purgeStream(/*@Nonnull*/ QDataStream* serialStream);

 friend class LnNetworkPortController;
};

#endif // ABSTRACTPORTCONTROLLER_H
