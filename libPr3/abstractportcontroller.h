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
  /*public*/ enum Type {
              JCOMBOBOX,
              TEXT,
              PASSWORD
          };
  Option();
  Option(QString displayText, QStringList options, bool advanced);
  Option(QString displayText, QStringList options);
  void configure(QString value);
  QString getCurrent();
  QStringList getOptions();
  QString getDisplayText();
  bool isAdvanced();
  bool isDirty();
  Type getType();
 private:
  QString currentValue;
  QString displayText;
  QStringList options;
  bool advancedOption; // = true;
  Type type;

 protected:
  /*protected*/ QString manufacturerName;// = null;

};

class LIBPR3SHARED_EXPORT AbstractPortController : public NetworkPortAdapter
{
    Q_OBJECT
public:
    ~AbstractPortController();
    /*public*/ void dispose() override;
    // returns the InputStream from the port
    /*public abstract*/ /*DataInputStream*/ virtual QDataStream* getInputStream()override {return NULL;}
    // returns the outputStream to the port
    /*public abstract*/ /*DataOutputStream*/virtual QDataStream* getOutputStream()override{return NULL;}
    // check that this object is ready to operate
    /*public*/ bool status()override;
    /*abstract public*/ virtual QString getCurrentPortName() override {return "";}
    /*
        The next set of configureOptions are to support the old configuration files.
    */
    /*public*/  void configureOption1(QString value)override;
    /*public*/  void configureOption2(QString value)override;
    /*public*/  void configureOption3(QString value)override;
    /*public*/  void configureOption4(QString value)override;
    /*
    The next set of getOption Names are to support legacy configuration files
    */
    /*public*/  QString getOption1Name()override;
    /*public*/  QString getOption2Name()override;
    /*public*/  QString getOption3Name()override;
    /*public*/  QString getOption4Name()override;
    /**
    * Get a list of all the options configured against this adapter.
    */
    /*public*/  QStringList getOptions()override;
    /**
    * Set the value of an option
    */
    /*public*/  void setOptionState(QString option, QString value)override;
    /**
    *  Get the value of a specific option
    */
    /*public*/  QString getOptionState(QString option)override;
    /**
    *   return a list of the various choices allowed with an option.
    */
    /*public*/  QStringList getOptionChoices(QString option)override;
    /*public*/  QString getOptionDisplayName(QString option)override;
    /*public*/  bool isOptionAdvanced(QString option)override;
    /**
    * Get and set of the Manufacturer for network (TCP/IP) based
    * connections is handled by the ConnectionConfig code in each
    * connector.  this is here as we implement the serialdriveradpter.
    */
    /*public*/  QString getManufacturer() override;
    /*public*/  void setManufacturer(QString manufacturer) override;
    /*public*/  bool getDisabled() override;
    /*public*/ void setDisabled(bool disabled) override;
    /*public*/ QString getSystemPrefix() override;
    /*public*/ void setSystemPrefix(QString systemPrefix) override;
    /*public*/ QString getUserName() override;
    /*public*/ void setUserName(QString userName) override;
    /*abstract public*/ virtual void recover() override{}
    /*public*/ bool isDirty() override;
    /*public*/ bool isRestartRequired() override;
    /*public*/ void setSystemConnectionMemo(SystemConnectionMemo* connectionMemo) override;
    /*public*/ SystemConnectionMemo* getSystemConnectionMemo() const override;
  /*public*/ bool isOptionTypeText(QString option) override;
  /*public*/ bool isOptionTypePassword(QString option) override;


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
