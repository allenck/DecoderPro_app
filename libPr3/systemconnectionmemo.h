#ifndef SYSTEMCONNECTIONMEMO_H
#define SYSTEMCONNECTIONMEMO_H

#include <QObject>
#include <QStringList>
#include <QVector>
#include "logger.h"
#include "propertychangelistener.h"
#include "libPr3_global.h"
#include "propertychangesupport.h"
#include "bean.h"
/**
 * Lightweight abstract class to denote that a system is active,
 * and provide general information.
 * <p>
 * Objects of specific subtypes are registered
 * in the instance manager to activate their
 * particular system.
 *
 * @author		Bob Jacobsen  Copyright (C) 2010
 * @version             $Revision: 18843 $
 */
class ConsistManager;
class ResourceBundle;
class Manager;
class LIBPR3SHARED_EXPORT SystemConnectionMemo : public Bean
{
 Q_OBJECT
public:
  SystemConnectionMemo(QObject * parent = 0) : Bean(parent) {}
// explicit SystemConnectionMemo(QString Prefix= "I", QString userName= "Internal", QObject *parent = 0);
    ~SystemConnectionMemo() {}
    SystemConnectionMemo(const SystemConnectionMemo&) : Bean() {}
 /**
  * Store in InstanceManager with
  * proper ID for later retrieval as a
  * generic system
  */
    virtual void _register() {}
 /**
  * Provides access to the system prefix string.
  * This was previously called the "System letter"
  */
    virtual QString getSystemPrefix() const {return QString();}
 //This should probably throwing an exception
    virtual bool setSystemPrefix(QString systemPrefix) {return false;}
    virtual QString getUserName()const {return QString();}
  /**
   * Get if connection is dirty. Checked fields are disabled, prefix, userName
   *
   * @return true if changed since loaded
   */
    virtual bool isDirty() {return false;}

 virtual bool isRestartRequired() {return false;}

 //This should probably throwing an exception
 virtual bool setUserName(QString name) {return false;}
 virtual int getOutputInterval() {return 0;}
 virtual int getDefaultOutputInterval() {return 0;}
    virtual void setOutputInterval(int newInterval) {}

 /**
  * Does this connection provide a manager of this type?
  */
 virtual bool provides(QString c) {return false;}
 /**
  * Does this connection provide a manager of this type?
  */
 virtual Manager* get(QString T) {return nullptr;}
    virtual void dispose() {}
 virtual bool getDisabled() {return false;}
    virtual void setDisabled(bool disabled)  {}
 //static SystemConnectionMemo* instance();
// static void addPropertyChangeListener(PropertyChangeListener* l);
// static void removePropertyChangeListener(PropertyChangeListener* l);
 /*public*/ static /*final*/ QString DISABLED;// = "ConnectionDisabled";
 /*public*/ static /*final*/ QString USER_NAME;// = "ConnectionNameChanged";
 /*public*/ static /*final*/ QString SYSTEM_PREFIX;// = "ConnectionPrefixChanged";
 /*public*/ static /*final*/ QString INTERVAL;// = "OutputInterval";
// /*public*/ ConsistManager* getConsistManager();
// /*public*/ void setConsistManager(ConsistManager* c);
    virtual QObject* self() {return (QObject*)this;}
signals:
 //void propertyChange(PropertyChangeEvent*);

public slots:
private:
// /*private*/ bool disabled;// = false;
// /*private*/ bool disabledAsLoaded;// = null; // Boolean can be true, false, or null
// /*static*/ QString prefix;
// /*private*/ QString prefixAsLoaded;
// /*static*/ QString userName;
// /*private*/ QString userNameAsLoaded;

 protected:
// PropertyChangeSupport* propertyChangeSupport = nullptr;

// /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SystemConnectionMemo");
 //const static bool initialised = false;
 /**
  * Provides a method to reserve System Names and prefixes at creation
  */
 //static void initialise();
 // static bool addUserName(QString userName);
 // static bool addSystemPrefix(QString systemPrefix);
 // static void removeUserName(QString userName);
 // static void removeSystemPrefix(QString systemPrefix);
 //bool mDisabled;
 // data members to hold contact with the property listeners
// static QVector<PropertyChangeListener*>* listeners;
 //static SystemConnectionMemo* _instance;
// /*private*/ ConsistManager* consistManager = nullptr;

protected:
// static QStringList* userNames; // = new ArrayList<String>();
// static QStringList* sysPrefixes; // = new ArrayList<String>();
// virtual void notifyPropertyChangeListener(QString property, QVariant oldValue, QVariant newValue) ;
// virtual ResourceBundle* getActionModelResourceBundle()  {return NULL;}
// void addToActionList();
// void removeFromActionList();

    friend class DefaultRouteManager;
};

//QVector<PropertyChangeListener*> SystemConnectionMemo::listeners;
//void SystemConnectionMemo::removePropertyChangeListener(PropertyChangeListener* l);
//void SystemConnectionMemo::initialise();
//bool SystemConnectionMemo::addUserName(QString userName);
//bool SystemConnectionMemo::addSystemPrefix(QString systemPrefix);
//void SystemConnectionMemo::removeUserName(QString userName);
//void SystemConnectionMemo::removeSystemPrefix(QString systemPrefix);
//QStringList SystemConnectionMemo::userNames = new QStringList();
//QStringList SystemConnectionMemo::sysPrefixes; // = new ArrayList<String>();

//void SystemConnectionMemo::addPropertyChangeListener(PropertyChangeListener* l);
Q_DECLARE_METATYPE(SystemConnectionMemo)
//Q_DECLARE_INTERFACE(SystemConnectionMemo, "SystemConnectionMemo")
#endif // SYSTEMCONNECTIONMEMO_H
