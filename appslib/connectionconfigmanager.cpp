#include "connectionconfigmanager.h"
#include "logger.h"
#include "profileutils.h"
#include "auxiliaryconfiguration.h"
#include "xmladapter.h"
#include "metatypes.h"
#include "connectionconfig.h"
#include "vptr.h"
#include "class.h"
#include "loggerfactory.h"

ConnectionConfigManager::ConnectionConfigManager() : AbstractPreferencesManager()
{
 connections = new QList<ConnectionConfig*>();
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
/*public*/ void ConnectionConfigManager::initialize(Profile* profile) throw (InitializationException)
{
 if (!isInitialized(profile))
 {
  log-> debug("Initializing...");
  QDomElement sharedConnections = QDomElement();
  QDomElement perNodeConnections = QDomElement();
#if 1
  try {
      sharedConnections = /*JDOMUtil.toJDOMElement*/(ProfileUtils::getAuxiliaryConfiguration(profile)->getConfigurationFragment(CONNECTIONS, NAMESPACE, true));
  } catch (NullPointerException ex)
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
   catch (NullPointerException ex)
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
          log-> debug(tr("Read perNode connection %1:%2 (%3) class %4}").arg(userName).arg(systemName).arg(manufacturer).arg(className));
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
      if(sl.at(3) == "pr3")
      {
       //prefix = "Pr3";
      }
      else if(sl.at(3) == "hexfile")
       prefix = "HexFile";
      else if(sl.at(3) == "loconetovertcp")
       prefix = "LnOverTcp";
      else if(sl.at(3) == "locobufferusb")
       prefix = "LocobufferUsb";
      else if(sl.at(3) == "locobuffer")
       prefix = "Locobuffer";
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
      this->addInitializationException(profile, new InitializationException(english, localized, NULL));
     }
    }
#if 1
    catch (ClassNotFoundException /*| InstantiationException | IllegalAccessException*/ ex)
    {
     log-> error(tr("Unable to create %1 for %2").arg(className).arg(shared.tagName()), ex.getMessage());
     QString english = tr( "Unable to create connection \"%1\" (%2).").arg(userName).arg( systemName); // NOI18N
     QString localized = tr( "Unable to create connection \"%1\" (%2).").arg(userName).arg( systemName); // NOI18N
     this->addInitializationException(profile, new InitializationException(english, localized, NULL));
    }
#endif
    catch (Exception* ex)
    {
     log-> error(tr("Unable to load %1 into %2").arg(shared.tagName()).arg(className)/*, ex*/);
//              QString english = Bundle.getMessage(Locale.ENGLISH, "ErrorSingleConnection", userName, systemName); // NOI18N
//              QString localized = Bundle.getMessage("ErrorSingleConnection", userName, systemName); // NOI18N
     QString english = tr("Unable to create connection \"%1\" (%2).").arg(userName).arg(systemName);
     QString localized = tr("Unable to create connection \"%1\" (%2).").arg(userName).arg(systemName);
     this->addInitializationException(profile, new InitializationException(english, localized, ex));
    }
   }
  }
  setInitialized(profile, true);
  QList<Exception*>* exceptions = this->getInitializationExceptions(profile);
  if (exceptions->size() == 1)
  {
#if 0
      //if (exceptions.get(0) instanceof InitializationException)
   if(qobject_cast<InitializationException*>(exceptions->at(0)) != NULL)
   {
       throw (InitializationException*) exceptions->at(0);
   } else {
       throw new InitializationException(exceptions->at(0));
   }
#endif
  }
  else if (exceptions->size() > 1)
  {
//      QString english = Bundle.getMessage(Locale.ENGLISH, "ErrorMultipleConnections"); // NOI18N
//      QString localized = Bundle.getMessage("ErrorMultipleConnections"); // NOI18N
   QString english = tr("Unable to create connection \"%1\" (%2).");
   QString localized = tr("Unable to create connection \"%1\" (%2).");
//      throw new InitializationException(english, localized);
  }
#endif
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
 foreach(ConnectionConfig* o, *connections)
 {
  log-> debug(tr("Saving connection %1 (%2)...").arg(o->getConnectionName()).arg(shared));
  QDomElement e = ConfigXmlManager::elementFromObject(o, shared);
  if (!e.isNull()) {
      element.appendChild(e);
  }
 }//);
 // save connections, or save an empty connections element if user removed all connections
 try {
  ProfileUtils::getAuxiliaryConfiguration(profile)->putConfigurationFragment(/*JDOMUtil.toW3CElement*/(element), shared);
 } catch (JDOMException ex) {
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
/*public*/ bool ConnectionConfigManager::add(/*@NonNULL*/ ConnectionConfig* c) throw (NullPointerException)
{
 if (c == NULL)
 {
  throw new NullPointerException();
 }
 if (!connections->contains(c))
 {
  /*bool result =*/ connections->append(c);
  int i = connections->indexOf(c);
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
    int i = connections->indexOf(c);
    bool result = connections->removeOne(c);
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
/*public*/ QList<ConnectionConfig*>* ConnectionConfigManager::getConnections() {
    //return connections.toArray(new ConnectionConfig[connections.size()]);
 return connections;
}

/**
 * Get the {@link jmri.jmrix.ConnectionConfig} at index following the rules
 * specified in {@link java.util.Collection#add(java.lang.Object)}.
 *
 * @param index index of the ConnectionConfig to return
 * @return the ConnectionConfig at the specified location
 */
/*public*/ ConnectionConfig* ConnectionConfigManager::getConnections(int index) {
    return connections->value(index);
}

//@Override
/*public*/ QListIterator<ConnectionConfig*> ConnectionConfigManager::iterator() {
    //return connections.iterator();
 return QListIterator<ConnectionConfig*>(*connections);
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
/*public*/ QStringList getConnectionTypes(/*@NonNULL*/ QString manufacturer) {
    return this.getDefaultConnectionTypeManager().getConnectionTypes(manufacturer);
}

/**
 * Get the list of known manufacturers.
 *
 * @return An array of known manufacturers.
 */
/*@NonNULL*/
/*public*/ QStringList getConnectionManufacturers() {
    return this.getDefaultConnectionTypeManager().getConnectionManufacturers();
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
@CheckForNull
/*public*/ QString getConnectionManufacturer(/*@NonNULL*/ QString connectionType) {
    for (QString manufacturer : this.getConnectionManufacturers()) {
        for (QString manufacturerType : this.getConnectionTypes(manufacturer)) {
            if (connectionType ==(manufacturerType)) {
                return manufacturer;
            }
        }
    }
    return NULL;
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
/*public*/ QStringList getConnectionManufacturers(/*@NonNULL*/ QString connectionType) {
    ArrayList<String> manufacturers = new ArrayList<>();
    for (QString manufacturer : this.getConnectionManufacturers()) {
        for (QString manufacturerType : this.getConnectionTypes(manufacturer)) {
            if (connectionType ==(manufacturerType)) {
                manufacturers.add(manufacturer);
            }
        }
    }
    return manufacturers.toArray(new String[manufacturers.size()]);
}

/**
 * Get the default {@link ConnectionTypeManager}, creating it if needed.
 *
 * @return the default ConnectionTypeManager
 */
/*private*/ ConnectionTypeManager getDefaultConnectionTypeManager() {
    if (InstanceManager.getNullableDefault(ConnectionTypeManager.class) == NULL) {
        InstanceManager.setDefault(ConnectionTypeManager.class, new ConnectionTypeManager());
    }
    return InstanceManager.getDefault(ConnectionTypeManager.class);
}

/*private*/ static class ConnectionTypeManager {

    /*private*/ /*final*/ HashMap<QString, ConnectionTypeList> connectionTypeLists = new HashMap<>();

    /*public*/ ConnectionTypeManager() {
        for (ConnectionTypeList ctl : ServiceLoader.load(ConnectionTypeList.class)) {
            for (QString manufacturer : ctl.getManufacturers()) {
                if (!connectionTypeLists.containsKey(manufacturer)) {
                    connectionTypeLists.put(manufacturer, ctl);
                } else {
                    log-> debug("Need a proxy for {} from {} in {}", manufacturer, ctl.getClass().getName(), this);
                    ProxyConnectionTypeList proxy;
                    ConnectionTypeList existing = connectionTypeLists.get(manufacturer);
                    if (existing instanceof ProxyConnectionTypeList) {
                        proxy = (ProxyConnectionTypeList) existing;
                    } else {
                        proxy = new ProxyConnectionTypeList(existing);
                    }
                    proxy.add(ctl);
                    connectionTypeLists.put(manufacturer, proxy);
                }
            }
        }
    }

    /*public*/ QStringList getConnectionTypes(QString manufacturer) {
        ConnectionTypeList ctl = this.connectionTypeLists.get(manufacturer);
        if (ctl != NULL) {
            return ctl.getAvailableProtocolClasses();
        }
        return this.connectionTypeLists.get(InternalConnectionTypeList.NONE).getAvailableProtocolClasses();
    }

    /*public*/ QStringList getConnectionManufacturers() {
        ArrayList<String> a = new ArrayList<>(this.connectionTypeLists.keySet());
        a.remove(InternalConnectionTypeList.NONE);
        a.sort(NULL);
        a.add(0, InternalConnectionTypeList.NONE);
        return a.toArray(new String[a.size()]);
    }

}

/*private*/ static class ProxyConnectionTypeList implements ConnectionTypeList {

    /*private*/ /*final*/ ArrayList<ConnectionTypeList> connectionTypeLists = new ArrayList<>();

    /*public*/ ProxyConnectionTypeList(/*@NonNULL*/ ConnectionTypeList connectionTypeList) {
        log-> debug("Creating proxy for {}", connectionTypeList.getManufacturers()[0]);
        this.add(connectionTypeList);
    }

    /*public*/ /*final*/ void add(/*@NonNULL*/ ConnectionTypeList connectionTypeList) {
        log-> debug("Adding {} to proxy", connectionTypeList.getClass().getName());
        this.connectionTypeLists.add(connectionTypeList);
    }

    //@Override
    /*public*/ QStringList getAvailableProtocolClasses() {
        TreeSet<QString> classes = new TreeSet<>();
        this.connectionTypeLists.stream().forEach((connectionTypeList) -> {
            classes.addAll(Arrays.asList(connectionTypeList.getAvailableProtocolClasses()));
        });
        return classes.toArray(new String[classes.size()]);
    }

    //@Override
    /*public*/ QStringList getManufacturers() {
        TreeSet<QString> manufacturers = new TreeSet<>();
        this.connectionTypeLists.stream().forEach((connectionTypeList) -> {
            manufacturers.addAll(Arrays.asList(connectionTypeList.getManufacturers()));
        });
        return manufacturers.toArray(new String[manufacturers.size()]);
    }

}
#endif
