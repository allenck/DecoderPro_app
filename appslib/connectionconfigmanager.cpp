#include "connectionconfigmanager.h"
#include "logger.h"
#include "profileutils.h"
#include "auxiliaryconfiguration.h"
#include "xmladapter.h"
#include "metatypes.h"
#include "vptr.h"
#include "class.h"
#include "loggerfactory.h"
#include "errormemo.h"
#include <QVector>
#include <QStringList>
#include "instancemanager.h"
#include "connectiontypelist.h"

ConnectionConfigManager::ConnectionConfigManager() : AbstractPreferencesManager()
{
 connections = QList<ConnectionConfig*>();
 NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/connections-2-9-6.xsd"; // NOI18N

}
/**
 * Manager for ConnectionConfig objects.
 *
 * @author Randall Wood (C) 2015
 */
// /*public*/ class ConnectionConfigManager extends AbstractPreferencesManager implements Iterable<ConnectionConfig> {

/*public*/ /*final*/ /*static*/ QString ConnectionConfigManager::CONNECTIONS = "connections"; // NOI18N
/*public*/ /*final*/ /*static*/ QString ConnectionConfigManager::CONNECTION = "connection"; // NOI18N
/*public*/ /*final*/ /*static*/ QString ConnectionConfigManager::CLASS = "class"; // NOI18N
/*public*/ /*final*/ /*static*/ QString ConnectionConfigManager::USER_NAME = "userName"; // NOI18N
/*public*/ /*final*/ /*static*/ QString ConnectionConfigManager::SYSTEM_NAME = "systemPrefix"; // NOI18N
/*public*/ /*final*/ /*static*/ QString ConnectionConfigManager::MANUFACTURER = "manufacturer"; // NOI18N
/*private*/ /*final*/ /*static*/ Logger* ConnectionConfigManager::log = LoggerFactory::getLogger("ConnectionConfigManager");

//@Override
/*public*/ void ConnectionConfigManager::initialize(Profile* profile) /*throw new (InitializationException)*/
{
 if (!isInitialized(profile))
 {
  log-> debug("Initializing...");
  QDomElement sharedConnections = QDomElement();
  QDomElement perNodeConnections = QDomElement();
  this->setPortNamePattern();
  try {
      sharedConnections = /*JDOMUtil.toJDOMElement*/(ProfileUtils::getAuxiliaryConfiguration(profile)->getConfigurationFragment(CONNECTIONS, NAMESPACE, true));
  } catch (NullPointerException* ex)
  {
      // Normal if this is a new profile
      log-> info("No connections configured.");
      log-> debug("Null pointer thrown reading shared configuration."/*, ex*/);
  }
  if (!sharedConnections.isNull())
  {
   try
   {
    perNodeConnections = /*JDOMUtil.toJDOMElement*/(ProfileUtils::getAuxiliaryConfiguration(profile)->getConfigurationFragment(CONNECTIONS, NAMESPACE, false));
   }
   catch (NullPointerException* ex)
   {
    // Normal if the profile has not been used on this computer
    log-> info("No local configuration found.");
    log-> debug("Null pointer thrown reading local configuration."/*, ex*/);
    // TODO: notify user
   }
   //for (QDomElement shared : sharedConnections.getChildren(CONNECTION))
   QDomNodeList nl = sharedConnections.elementsByTagName(CONNECTION);
   for(int i = 0; i < nl.size(); i++)
   {
    QDomElement shared = nl.at(i).toElement();
    QDomElement perNode = shared;
    QString className = shared.attribute(CLASS);
    QString userName = shared.attribute(USER_NAME, ""); // NOI18N
    QString systemName = shared.attribute(SYSTEM_NAME, ""); // NOI18N
    QString manufacturer = shared.attribute(MANUFACTURER, ""); // NOI18N
    log-> debug(tr("Read shared connection %1:%2 (%3) class %4").arg(userName).arg(systemName).arg(manufacturer).arg(className));
    if (!perNodeConnections.isNull())
    {
        //for (QDomElement e : perNodeConnections.getChildren(CONNECTION)) {
     QDomNodeList connections = perNodeConnections.elementsByTagName(CONNECTION);
     for(int j = 0; j < connections.size(); j++)
     {
      QDomElement e = connections.at(j).toElement();
      if (systemName ==(e.attribute(SYSTEM_NAME)))
      {
          perNode = e;
          className = perNode.attribute(CLASS);
          userName = perNode.attribute(USER_NAME, ""); // NOI18N
          manufacturer = perNode.attribute(MANUFACTURER, ""); // NOI18N
          log-> debug(tr("Read perNode connection %1:%2 (%3) class %4").arg(userName).arg(systemName).arg(manufacturer).arg(className));
      }
     }
    }
    try
    {
     log-> debug(tr("Creating connection %1:%2 (%3) class %4").arg(userName).arg(systemName).arg(manufacturer).arg(className));

     QString newClassName = "ConnectionConfigXml";
     //if(className == "ConnectionConfigXml")
     {
      QStringList sl = className.split(".");
      QString prefix;
      if(sl.at(2) == "rfid" && sl.at(3) == "serialdriver")
       prefix = "RfidSerial";
      else if(sl.at(2)== "jmriclient" && sl.at(3) == "networkdriver")
          prefix = "JMRIClient";
      else
      if(sl.at(3) == "pr3")
      {
       prefix = "Pr3";
      }
      else if(sl.at(3) == "hexfile")
       prefix = "HexFile";
      else if(sl.at(3) == "loconetovertcp")
       prefix = "LnOverTcp";
      else if(sl.at(3) == "locobufferusb")
       prefix = "LocobufferUsb";
      else if(sl.at(3) == "locobuffer")
       prefix = "Locobuffer";
      else if(sl.at(3) == "locobufferii")
       prefix = "LocobufferII";
      else if(sl.at(3) == "sprog")
       prefix = "Sprog";
      else if(sl.at(3) == "sprogCS")
       prefix = "SprogCS";
      else if(sl.at(3) == "pr4")
       prefix = "Pr4";
      else if(sl.at(3) == "usb_dcs52")
       prefix = "DCS52";
      else if(sl.at(3) == "usb_dcs240")
       prefix = "DCS240";

      newClassName = prefix+"ConnectionConfigXml";
      if(!prefix.isEmpty())
        className = className.replace("ConnectionConfigXml", newClassName);
     }

     //if (!((XmlAdapter) Class.forName(className).newInstance()).load(shared, perNode)) {
     if(!((XmlAdapter*)Class::forName(newClassName))->load(shared, perNode))
     {
      log-> error(tr("Unable to create %1 for %2, load returned false").arg(newClassName).arg(shared.tagName()));
      //QString english = Bundle.getMessage(Locale.ENGLISH, "ErrorSingleConnection", userName, systemName); // NOI18N
      QString english = tr("Unable to create connection \"%1\" (%2).").arg(userName).arg(systemName);
      //QString localized = Bundle.getMessage("ErrorSingleConnection", userName, systemName); // NOI18N
      QString localized = tr("Unable to create connection \"%1\" (%2).").arg(userName).arg(systemName);
      this->addInitializationException(profile, new HasConnectionButUnableToConnectException(english, localized, NULL));
     }
    }

    catch (ClassNotFoundException* /*| InstantiationException | IllegalAccessException*/ ex)
    {
     log-> error(tr("Unable to create %1 for %2").arg(className).arg(shared.tagName()), ex);
     QString english = tr( "Unable to create connection \"%1\" (%2).").arg(userName).arg( systemName); // NOI18N
     QString localized = tr( "Unable to create connection \"%1\" (%2).").arg(userName).arg( systemName); // NOI18N
     this->addInitializationException(profile, new HasConnectionButUnableToConnectException(english, localized, NULL));
    }
    catch (Exception* ex)
    {
     log-> error(tr("Unable to load %1 into %2").arg(shared.tagName()).arg(className)/*, ex*/);
//              QString english = Bundle.getMessage(Locale.ENGLISH, "ErrorSingleConnection", userName, systemName); // NOI18N
//              QString localized = Bundle.getMessage("ErrorSingleConnection", userName, systemName); // NOI18N
     QString english = tr("Unable to create connection \"%1\" (%2).").arg(userName).arg(systemName);
     QString localized = tr("Unable to create connection \"%1\" (%2).").arg(userName).arg(systemName);
     Exception* ex1 = new Exception(ex);
     this->addInitializationException(profile, new HasConnectionButUnableToConnectException(english, localized, ex1));
    }
   }
  }
  setInitialized(profile, true);
  QList<Exception*> exceptions = this->getInitializationExceptions(profile);
  if (exceptions.size() == 1)
  {
   if (dynamic_cast<HasConnectionButUnableToConnectException*>(exceptions.at(0)) )
   {
    throw (HasConnectionButUnableToConnectException*) exceptions.at(0);
   } else {
       throw new HasConnectionButUnableToConnectException(exceptions.at(0));
   }
  }
  else if (exceptions.size() > 1)
  {
//      QString english = Bundle.getMessage(Locale.ENGLISH, "ErrorMultipleConnections"); // NOI18N
//      QString localized = Bundle.getMessage("ErrorMultipleConnections"); // NOI18N
   QString english = QString("Unable to create connection \"%1\" (%2).");
   QString localized = tr("Unable to create connection \"%1\" (%2).");
      throw new  HasConnectionButUnableToConnectException(english, localized, nullptr);
  }

  log-> debug("Initialized...");
 }
}

//@Override
///*public*/ QSet<Class<? extends PreferencesManager>> getRequires() {
/*public*/ QSet<QString>* ConnectionConfigManager::getRequires()
{
 return new QSet<QString>();
}

//@Override
/*public*/ void ConnectionConfigManager::savePreferences(Profile* profile) {
    log-> debug("Saving connections preferences...");
    // store shared Connection preferences
    savePreferences(profile, true);
    // store /*private*/ or perNode Connection preferences
    savePreferences(profile, false);
    log-> debug("Saved connections preferences...");
}

/*private*/ /*synchronized*/ void ConnectionConfigManager::savePreferences(Profile* profile, bool shared)
{
 QDomDocument doc = QDomDocument();
 QDomElement element = doc.createElementNS(NAMESPACE, CONNECTIONS);
 //connections.stream().forEach((o) ->
 foreach(ConnectionConfig* o, connections)
 {
  log-> debug(tr("Saving connection %1 (%2)...").arg(o->getConnectionName()).arg(shared));
  QDomElement e = ConfigXmlManager::elementFromObject(o);
  if (!e.isNull()) {
      element.appendChild(e);
  }
 }//);
 // save connections, or save an empty connections element if user removed all connections
 try {
  ProfileUtils::getAuxiliaryConfiguration(profile)->putConfigurationFragment(/*JDOMUtil.toW3CElement*/(element), shared);
 } catch (JDOMException* ex) {
     log-> error("Unable to create create XML"/*, ex*/);
 }
}

/**
 * Add a {@link jmri.jmrix.ConnectionConfig} following the rules specified
 * in {@link java.util.Collection#add(java.lang.Object)}.
 *
 * @param c an existing ConnectionConfig
 * @return true if c was added, false otherwise
 * @throws NullPointerException if c is NULL
 */
/*public*/ bool ConnectionConfigManager::add(/*@NonNULL*/ ConnectionConfig* c) /*throw (NullPointerException)*/
{
 if (c == NULL)
 {
  throw new NullPointerException();
 }
 if (!connections.contains(c))
 {
  /*bool result =*/ connections.append(c);
  int i = connections.indexOf(c);
  fireIndexedPropertyChange(CONNECTIONS, i, QVariant(), VPtr<ConnectionConfig>::asQVariant(c));
  return /*result*/true;
 }
 return false;
}

/**
 * Remove a {@link jmri.jmrix.ConnectionConfig} following the rules
 * specified in {@link java.util.Collection#add(java.lang.Object)}.
 *
 * @param c an existing ConnectionConfig
 * @return true if c was removed, false otherwise
 */
/*public*/ bool ConnectionConfigManager::remove(/*@NonNULL*/ ConnectionConfig* c) {
    int i = connections.indexOf(c);
    bool result = connections.removeOne(c);
    if (result) {
        fireIndexedPropertyChange(CONNECTIONS, i, VPtr<ConnectionConfig>::asQVariant(c), QVariant());
    }
    return result;
}

/**
 * Get an Array of {@link jmri.jmrix.ConnectionConfig} objects.
 *
 * @return an Array, possibly empty if there are no ConnectionConfig
 *         objects.
 */
/*@NonNULL*/
/*public*/ QVector<ConnectionConfig*> ConnectionConfigManager::getConnections() {
    //return connections.toArray(new ConnectionConfig[connections.size()]);
 return connections.toVector();
}

/**
 * Get the {@link jmri.jmrix.ConnectionConfig} at index following the rules
 * specified in {@link java.util.Collection#add(java.lang.Object)}.
 *
 * @param index index of the ConnectionConfig to return
 * @return the ConnectionConfig at the specified location
 */
/*public*/ ConnectionConfig* ConnectionConfigManager::getConnections(int index) {
    return connections.value(index);
}

//@Override
/*public*/ QListIterator<ConnectionConfig*> ConnectionConfigManager::iterator() {
    //return connections.iterator();
 return QListIterator<ConnectionConfig*>(connections);
}
#if 0
/**
 * Get the class names for classes supporting layout connections for the
 * given manufacturer.
 *
 * @param manufacturer the name of the manufacturer
 * @return An array of supporting class names; will return the list of
 *         internal connection classes if manufacturer is not a known
 *         manufacturer; the array may be empty if there are no supporting
 *         classes for the given manufacturer.
 */
/*@NonNULL*/
/*public*/ QStringList ConnectionConfigManager::getConnectionTypes(/*@NonNULL*/ QString manufacturer) {
    return this->getDefaultConnectionTypeManager()->getConnectionTypes(manufacturer);
}

/**
 * Get the list of known manufacturers.
 *
 * @return An array of known manufacturers.
 */
/*@NonNULL*/
/*public*/ QStringList ConnectionConfigManager::getConnectionManufacturers() {
    return this->getDefaultConnectionTypeManager()->getConnectionManufacturers();
}

/**
 * Get the manufacturer that is supported by a connection type. If there are
 * multiple manufacturers supported by connectionType, returns only the
 * first manufacturer.
 *
 * @param connectionType the class name of a connection type.
 * @return the supported manufacturer. Returns NULL if no manufacturer is
 *         associated with the connectionType.
 */
//@CheckForNull
/*public*/ QString ConnectionConfigManager::getConnectionManufacturer(/*@NonNULL*/ QString connectionType) {
    for (QString manufacturer : this->getConnectionManufacturers()) {
        for (QString manufacturerType : this->getConnectionTypes(manufacturer)) {
            if (connectionType ==(manufacturerType)) {
                return manufacturer;
            }
        }
    }
    return QString();
}

/**
 * Get the list of all known manufacturers that a single connection type
 * supports.
 *
 * @param connectionType the class name of a connection type.
 * @return an Array of supported manufacturers. Returns an empty Array if no
 *         manufacturer is associated with the connectionType.
 */
/*@NonNULL*/
/*public*/ QStringList ConnectionConfigManager::getConnectionManufacturers(/*@NonNULL*/ QString connectionType) {
    QStringList manufacturers = QStringList();
    for (QString manufacturer : this->getConnectionManufacturers()) {
        for (QString manufacturerType : this->getConnectionTypes(manufacturer)) {
            if (connectionType ==(manufacturerType)) {
                manufacturers.append(manufacturer);
            }
        }
    }
    //return manufacturers.toArray(new String[manufacturers.size()]);
    return QVector<QString>(manufacturers.size()).toList();
}

/**
 * Get the default {@link ConnectionTypeManager}, creating it if needed.
 *
 * @return the default ConnectionTypeManager
 */
/*private*/ ConnectionTypeManager* getDefaultConnectionTypeManager() {
    if (InstanceManager::getNullableDefault("ConnectionTypeManager") == NULL) {
        InstanceManager::setDefault("ConnectionTypeManager", new ConnectionTypeManager());
    }
    return (ConnectionTypeManager*)InstanceManager::getDefault("ConnectionTypeManager");
}

///*private*/ static class ConnectionTypeManager {

//    /*private*/ /*final*/ HashMap<QString, ConnectionTypeList> connectionTypeLists = new HashMap<>();

    /*public*/ ConnectionTypeManager::ConnectionTypeManager()
    {
     connectionTypeLists  = QMap<QString, ConnectionTypeList*>();

        for (ConnectionTypeList* ctl : ServiceLoader.load("ConnectionTypeList")) {
            for (QString manufacturer : ctl->getManufacturers()) {
                if (!connectionTypeLists.contains(manufacturer)) {
                    connectionTypeLists.insert(manufacturer, ctl);
                } else {
                    log-> debug(tr("Need a proxy for %1 from %2 in %3").arg(manufacturer).arg(ctl->metaObject()->className()).arg(this->metaObject()->className());
                    ProxyConnectionTypeList* proxy;
                    ConnectionTypeList* existing = connectionTypeLists.value(manufacturer);
                    if (qobject_cast<ProxyConnectionTypeList*>(existing)) {
                        proxy = (ProxyConnectionTypeList*) existing;
                    } else {
                        proxy = new ProxyConnectionTypeList(existing);
                    }
                    proxy.ad(ctl);
                    connectionTypeLists.insert(manufacturer, proxy);
                }
            }
        }
    }

    /*public*/ QStringList ConnectionTypeManager::getConnectionTypes(QString manufacturer) {
        ConnectionTypeList* ctl = this->connectionTypeLists.value(manufacturer);
        if (ctl != NULL) {
            return ctl->getAvailableProtocolClasses();
        }
        return this->connectionTypeLists.value(InternalConnectionTypeList::NONE)->getAvailableProtocolClasses();
    }

    /*public*/ QStringList ConnectionTypeManager::getConnectionManufacturers() {
        QStringList a = QStringList(this->connectionTypeLists.keys());
        a.remove(InternalConnectionTypeList.NONE);
        a.sort(NULL);
        a.add(0, InternalConnectionTypeList.NONE);
        return a.toArray(new String[a.size()]);
    }

//}

Logger* ConnectionTypeManager::log = LoggerFactory::getLogger("ConnectionTypeManager");

///*private*/ static class ProxyConnectionTypeList implements ConnectionTypeList {

//    /*private*/ /*final*/ ArrayList<ConnectionTypeList> connectionTypeLists = new ArrayList<>();

    /*public*/ ProxyConnectionTypeList::ProxyConnectionTypeList(/*@NonNULL*/ ConnectionTypeList* connectionTypeList) {
  /*private*/ /*final*/ connectionTypeLists =  QList<ConnectionTypeList*>();

        log-> debug("Creating proxy for {}", connectionTypeList.getManufacturers()[0]);
        this->add(connectionTypeList);
    }

    /*public*/ /*final*/ void ProxyConnectionTypeList::add(/*@NonNULL*/ ConnectionTypeList connectionTypeList) {
        log-> debug("Adding {} to proxy", connectionTypeList.getClass().getName());
        this.connectionTypeLists.add(connectionTypeList);
    }

    //@Override
    /*public*/ QStringList ProxyConnectionTypeList::getAvailableProtocolClasses() {
        TreeSet<QString> classes = new TreeSet<>();
        this.connectionTypeLists.stream().forEach((connectionTypeList) -> {
            classes.addAll(Arrays.asList(connectionTypeList.getAvailableProtocolClasses()));
        });
        return classes.toArray(new String[classes.size()]);
    }

    //@Override
    /*public*/ QStringList ProxyConnectionTypeList::getManufacturers() {
        QSet<QString> manufacturers =QSet<QString>();
//        this.connectionTypeLists.stream().forEach((connectionTypeList) ->
        foreach(ConnectionTypeList* connectionTypeList, this->connectionTypeLists)
        {
            //manufacturers.addAll(Arrays.asList(connectionTypeList.getManufacturers()));
         manufacturers.unite()
        }//);
        return manufacturers.toArray(new String[manufacturers.size()]);
    }

//}
Logger* ProxyConnectionTypeList::log = LoggerFactory::getLogger("ProxyConnectionTypeList");
#endif
/**
     * Override the default port name patterns unless the
     * purejavacomm.portnamepattern property was set on the command line.
     */
    /*private*/ void ConnectionConfigManager::setPortNamePattern() {
#if 0
        /*final*/ QString pattern = "purejavacomm.portnamepattern";
        Properties properties = System.getProperties();
        if (properties.getProperty(pattern) == null) {
            try (InputStream in = ConnectionConfigManager.class.getResourceAsStream("PortNamePatterns.properties")) { // NOI18N
                properties.load(in);
            } catch (IOException* ex) {
                log.error("Unable to read PortNamePatterns.properties", ex);
            }
        }
#endif
    }

#if 1
//    /*private*/ /*static*/ class ConnectionConfigManagerErrorHandler extends ErrorHandler {

//        ArrayList<HasConnectionButUnableToConnectException> exceptions = new ArrayList<>();

        /*public*/ ConnectionConfigManagerErrorHandler::ConnectionConfigManagerErrorHandler()
         : ErrorHandler()
        {
            //super();
             exceptions = QList<HasConnectionButUnableToConnectException>();
        }

        /**
         * Capture ErrorMemos as initialization exceptions. {@inheritDoc}
         */
        //@Override
        // The memo has a generic message (since the real cause never makes it this far anyway)
        // If the memo reliably had an exception, we could make a decision about
        // how to handle that, but since it doesn't all we can do is log it
        /*public*/ void ConnectionConfigManagerErrorHandler::handle(ErrorMemo* memo) {
            if (memo->exception != nullptr) {
                this->exceptions.append(new HasConnectionButUnableToConnectException(memo->description, tr("<html>&nbsp;&nbsp;&nbsp;&nbsp;%1</html>").arg(memo->description), memo->exception));
            } else {
                this->exceptions.append(new HasConnectionButUnableToConnectException(memo->description, tr("<html>&nbsp;&nbsp;&nbsp;&nbsp;%1</html>").arg(memo->description), memo->exception));
            }
        }
//    };
#endif
