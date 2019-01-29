#include "jsonutilhttpservice.h"
#include "webserverpreferences.h"
#include "json.h"
#include "controlpaneleditor.h"
#include "layouteditor.h"
#include "paneleditor.h"
#include "version.h"
#include "metadata.h"
#include "profilemanager.h"
#include "profile.h"
#include "nodeidentity.h"
#include "jsonserverpreferences.h"
#include "connectionconfig.h"
#include "connectionconfigmanager.h"
#include "connectionnamefromsystemname.h"
#include "dcclocoaddress.h"
/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonUtilHttpService extends JsonHttpService {

/*public*/ JsonUtilHttpService::JsonUtilHttpService(ObjectMapper mapper, QObject* parent) : JsonHttpService(mapper, parent){
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonUtilHttpService::doGet(QString type, QString name, QLocale locale) throw (JsonException)
{
 if(type == JSON::HELLO)
 {
  return QJsonValue(this->getHello(locale, JsonServerPreferences::getDefault()->getHeartbeatInterval()));
 }
 else if(type ==  JSON::METADATA)
 {
  if (name == NULL) {
      return QJsonValue(this->getMetadata(locale));
  }
  return QJsonValue(this->getMetadata(locale, name));
 }

 else if(type == JSON::NETWORK_SERVICE || type == JSON::NETWORK_SERVICES)
 {
  if (name == NULL) {
      return this->getNetworkServices(locale);
  }
  return this->getNetworkService(locale, name);
 }

 else if(type == JSON::NODE)
 {
  return QJsonValue(this->getNode(locale));
 }
 else if(type ==JSON::PANELS)
 {
  return QJsonValue(this->getPanels(locale));
 }
 else if(type == JSON::RAILROAD)
 {
  return QJsonValue(this->getRailroad(locale));
 }
 else if(type == JSON::SYSTEM_CONNECTIONS)
 {
  return QJsonValue(this->getSystemConnections(locale));
 }
 else
  throw JsonException(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, tr(/*locale,*/ "Unknown object type %1 was requested.").arg(type));
}

//@Override
/*public*/ QJsonValue JsonUtilHttpService::doGetList(QString type, QLocale locale) throw (JsonException) {
 if(type == JSON::METADATA)
 {
  return QJsonValue(this->getMetadata(locale));
 }
 else if(type == JSON::NETWORK_SERVICES)
 {
  return this->getNetworkServices(locale);
 }
 else if(type == JSON::SYSTEM_CONNECTIONS)
 {
  return QJsonValue(this->getSystemConnections(locale));
 }
 else
 {
  return this->doGet(type, "", locale).toArray();
 }
}

//@Override
/*public*/ QJsonObject JsonUtilHttpService::doPost(QString type, QString name, QJsonObject /*data*/, QLocale locale) throw (JsonException) {
    return this->doGet(type, name, locale).toObject();
}

/**
 * Send a JSON {@link jmri.server.json.JSON#HELLO} message.
 *
 * @param locale    the client's Locale
 * @param heartbeat seconds in which a client must send a message before its
 *                  connection is broken
 * @return the JSON hello message
 */
/*public*/ QJsonObject JsonUtilHttpService::getHello(QLocale /*locale*/, int heartbeat) {
    QJsonObject root = QJsonObject(); //mapper.createObjectNode();
    root.insert(JSON::TYPE, JSON::HELLO);
    //ObjectNode data = root.putObject(JSON::DATA);
    QJsonObject data = QJsonObject();
    data.insert(JSON::JMRI, Version::name());
//        data.insert(JSON::JSON, JSON::JSON_PROTOCOL_VERSION);
    data.insert(JSON::HEARTBEAT, qRound(heartbeat * 0.9f));
    data.insert(JSON::RAILROAD, WebServerPreferences::getDefault()->getRailroadName());
    data.insert(JSON::NODE, NodeIdentity::identity());
    data.insert(JSON::ACTIVE_PROFILE, ProfileManager::getDefault()->getActiveProfile()->getName());
    root.insert(JSON::DATA, data);
    return root;
}

/**
 * Get a JSON message with a metadata element from {@link jmri.Metadata}.
 *
 * @param locale The client's Locale.
 * @param name   The metadata element to get.
 * @return JSON metadata element.
 * @throws JsonException if name is not a recognized metadata element.
 */
/*public*/ QJsonObject JsonUtilHttpService::getMetadata(QLocale /*locale*/, QString name) throw (JsonException) {
    QString metadata = Metadata::getBySystemName(name);
    QJsonObject root = QJsonObject();
    if (metadata != NULL) {
//            root = QJsonObject();//mapper.createObjectNode();
        root.insert(JSON::TYPE, JSON::METADATA);
        //QJsonObject data = root.putObject(JSON::DATA);
        QJsonObject data = QJsonObject();
        data.insert(JSON::NAME, name);
        data.insert(JSON::VALUE, Metadata::getBySystemName(name));
        root.insert(JSON::DATA, data);
    } else {
        throw JsonException(404, tr(/*locale,*/ "Unknown object type %1 was requested.").arg(JSON::METADATA, name));
    }
    return root;
}

/**
 * Get a JSON array of metadata elements as listed by
 * {@link jmri.Metadata#getSystemNameList()}.
 *
 * @param locale The client's Locale.
 * @return Array of JSON metadata elements.
 * @throws JsonException if thrown by
 *                       {@link #getMetadata(java.util.Locale, java.lang.String)}.
 */
/*public*/ QJsonArray JsonUtilHttpService::getMetadata(QLocale locale) throw (JsonException) {
    QJsonArray root = QJsonArray(); //mapper.createArrayNode();
    foreach (QString name, Metadata::getSystemNameList())
    {
        root.append(getMetadata(locale, name));
    }
    return root;
}

/**
 * Get a running {@link jmri.util.zeroconf.ZeroConfService} using the
 * protocol as the name of the service.
 *
 * @param locale the client's Locale.
 * @param name   the service protocol.
 * @return the JSON networkService message.
 * @throws jmri.server.json.JsonException if type is not a running zeroconf
 *                                        networking protocol.
 */
/*public*/ QJsonObject JsonUtilHttpService::getNetworkService(QLocale /*locale*/, QString /*name*/) throw (JsonException) {
//        for (ZeroConfService service : ZeroConfService.allServices()) {
//            if (service.type().equals(name)) {
//                return this->getNetworkService(service);
//            }
//        }
//        throw JsonException(404, tr(locale, "ErrorObject", JSON::NETWORK_SERVICE, name));
return QJsonObject();
}
#if 0
/*private*/ QJsonObject getNetworkService(ZeroConfService service) {
    ObjectNode ns = QJsonObject();//mapper.createObjectNode().put(JSON::TYPE, JSON::NETWORK_SERVICE);
    ns.insert(JSON::TYPE, JSON::NETWORK_SERVICE);
    QJsonObject data = ns.putObject(JSON::DATA);
    data.put(JSON::NAME, service.name());
    data.put(JSON::PORT, service.serviceInfo().getPort());
    data.put(JSON::TYPE, service.type());
    Enumeration<String> pe = service.serviceInfo().getPropertyNames();
    while (pe.hasMoreElements()) {
        String pn = pe.nextElement();
        data.put(pn, service.serviceInfo().getPropertyString(pn));
    }
    return ns;
}
#endif
/**
 *
 * @param locale the client's Locale.
 * @return the JSON networkServices message.
 */
/*public*/ QJsonArray JsonUtilHttpService::getNetworkServices(QLocale locale) {
    QJsonArray root = QJsonArray(); // mapper.createArrayNode();
//        ZeroConfService.allServices().stream().forEach((service) -> {
//            root.add(this->getNetworkService(service));
//        });
    return root;
}

/**
 * Send a JSON {@link jmri.server.json.JSON#NODE} message containing the
 * JMRI node identity and former identities.
 *
 * @param locale the client's Locale
 * @return the JSON node message
 * @see jmri.util.node.NodeIdentity
 */
/*public*/ QJsonObject JsonUtilHttpService::getNode(QLocale /*locale*/) {
    QJsonObject root = QJsonObject(); //mapper.createObjectNode();
    root.insert(JSON::TYPE, JSON::NODE);
    QJsonObject data = QJsonObject();//root.putObject(JSON::DATA);
    data.insert(JSON::NODE, NodeIdentity::identity());
    //ArrayNode nodes = mapper.createArrayNode();
    QJsonArray nodes;
//        NodeIdentity.formerIdentities().stream().forEach((node) -> {
    foreach(QString node, NodeIdentity::formerIdentities())
    {
        nodes.append(node);
    }//);
    data.insert(JSON::FORMER_NODES, nodes);
    root.insert(JSON::DATA, data);
    return root;
}

/*public*/ QJsonObject JsonUtilHttpService::getPanel(QLocale /*locale*/, Editor* editor, QString format)
{
 if (editor->getAllowInFrameServlet())
 {
 QString title = ((JmriJFrame*) editor->window())->title();
 if (!title.isEmpty() && !(WebServerPreferences::getDefault()->getDisallowedFrames()).contains(title))
 {
   QString type = JSON::PANEL;
   QString name = "Panel";
   if (qobject_cast<ControlPanelEditor*>(editor)!= NULL)
   {
    type = JSON::CONTROL_PANEL;
    name = "ControlPanel";
   }
   else if (qobject_cast<LayoutEditor*>(editor)!= NULL)
   {
    type = JSON::LAYOUT_PANEL;
    name = "Layout";
   }
   //ObjectNode root = this->mapper.createObjectNode();
   QJsonObject root = QJsonObject();
   root.insert(JSON::TYPE, JSON::PANEL);
   QJsonObject data = QJsonObject();
   data.insert(JSON::NAME, name + "/" + title);//.replace(" ", "%20").replace("#", "%23")); // NOI18N
   data.insert(JSON::URL, "/panel/" + data.value(JSON::NAME).toString() + "?format=" + format); // NOI18N
   data.insert(JSON::USERNAME, title);
   data.insert(JSON::TYPE, type);
   root.insert(JSON::DATA, data);
   qDebug() << QJsonDocument(root).toJson();
   return root;
 }
}
return QJsonObject();
}

/*public*/ QJsonArray JsonUtilHttpService::getPanels(QLocale locale, QString format) {
//ArrayNode root = mapper.createArrayNode();
  QJsonArray root = QJsonArray();
// list loaded Panels (ControlPanelEditor, PanelEditor, LayoutEditor)
// list ControlPanelEditors
//    Editor::getEditors("ControlPanelEditor").stream()
//            .map((editor) -> this->getPanel(locale, editor, format))
//            .filter((panel) -> (panel != NULL)).forEach((panel) ->
foreach(Editor* editor, Editor::getEditors("ControlPanelEditor"))
{

 QJsonObject panel = this->getPanel(locale, (ControlPanelEditor*)editor, format);
 if(!panel.isEmpty())
    root.append(panel);
}//);
// list LayoutEditors and PanelEditors
//    Editor::getEditors("PanelEditor").stream()
//            .map((editor) -> this->getPanel(locale, editor, format))
//            .filter((panel) -> (panel != NULL)).forEach((panel) ->
foreach(Editor* editor, Editor::getEditors("PanelEditor"))
{
 QJsonObject panel = this->getPanel(locale, (PanelEditor*)editor, format);
 if(!panel.isEmpty())
    root.append(panel);
}//);
return root;
}

/*public*/ QJsonArray JsonUtilHttpService::getPanels(QLocale locale) {
return this->getPanels(locale, JSON::XML);
}

/**
 * Send a JSON {@link jmri.server.json.JSON#NODE} message containing the
 * Railroad from the Railroad Name preferences.
 *
 * @param locale the client's Locale
 * @return the JSON railroad name message
 */
/*public*/ QJsonObject JsonUtilHttpService::getRailroad(QLocale /*locale*/) {
    QJsonObject root = QJsonObject(); //mapper.createObjectNode();
    root.insert(JSON::TYPE, JSON::RAILROAD);
    //ObjectNode data = root.putObject(JSON::DATA);
    QJsonObject data = QJsonObject();
    data.insert(JSON::NAME, WebServerPreferences::getDefault()->getRailroadName());
    root.insert(JSON::DATA, data);
    return root;
}
#if 1
/**
 *
 * @param locale the client's Locale.
 * @return the JSON networkServices message.
 */
/*public*/ QJsonArray JsonUtilHttpService::getSystemConnections(QLocale /*locale*/) {
    QJsonArray root = QJsonArray();//mapper.createArrayNode();
    QStringList prefixes = QStringList();
    foreach (ConnectionConfig* config, *((ConnectionConfigManager*) InstanceManager::getDefault("ConnectionConfigManager"))->getConnections()) {
        if (!config->getDisabled()) {
            QJsonObject connection = QJsonObject(); //mapper.createObjectNode().put(JSON::TYPE, JSON::SYSTEM_CONNECTION);
            connection.insert(JSON::TYPE, JSON::SYSTEM_CONNECTION);
            QJsonObject data = QJsonObject();
            connection.insert(JSON::DATA, data);
            data.insert(JSON::NAME, config->getConnectionName());
            data.insert(JSON::MFG, config->getManufacturer());
            data.insert(JSON::PREFIX, config->getAdapter()->getSystemConnectionMemo()->getSystemPrefix());
            prefixes.append(config->getAdapter()->getSystemConnectionMemo()->getSystemPrefix());
            root.append(connection);
        }
    }
//        InstanceManager::getList("SystemConnectionMemo").stream().map((instance) -> instance)
//                .filter((memo) -> (!memo.getDisabled() && !prefixes.contains(memo.getSystemPrefix()))).forEach((memo) ->
    foreach(QObject* obj, *InstanceManager::getList("SystemConnectionMemo"))
    {
     SystemConnectionMemo* memo = (SystemConnectionMemo*)obj;
        QJsonObject connection = QJsonObject(); //mapper.createObjectNode().put(JSON::TYPE, JSON::SYSTEM_CONNECTION);
        connection.insert(JSON::TYPE, JSON::SYSTEM_CONNECTION);
        QJsonObject data =  QJsonObject();
          connection.insert(JSON::DATA, data);
        data.insert(JSON::NAME, memo->getUserName());
        data.insert(JSON::PREFIX, memo->getSystemPrefix());
        data.insert(JSON::MFG, /*"null"*/QJsonValue());
        prefixes.append(memo->getSystemPrefix());
        root.append(connection);
    }//);
    // Following is required because despite there being a SystemConnectionMemo
    // for the default internal connection, it is not used for the default internal
    // connection. This allows a client to map the server's internal objects.
    QString prefix = "I";
    if (!prefixes.contains(prefix)) {
        QJsonObject connection = QJsonObject(); //mapper.createObjectNode().put(JSON::TYPE, JSON::SYSTEM_CONNECTION);
        connection.insert(JSON::TYPE, JSON::SYSTEM_CONNECTION);
        QJsonObject data = QJsonObject();
        connection.insert(JSON::DATA, data);
        data.insert(JSON::NAME, ConnectionNameFromSystemName::getConnectionName(prefix));
        data.insert(JSON::PREFIX, prefix);
        data.insert(JSON::MFG, /*"null"*/QJsonValue());
        root.append(connection);
    }
    return root;
}

/**
 * Gets the {@link jmri.DccLocoAddress} for a String in the form
 * {@code number(type)} or {@code number}.
 *
 * Type may be {@code L} for long or {@code S} for short. If the
 * type is not specified, type is assumed to be short.
 *
 * @param address the address
 * @return The DccLocoAddress for address
 */
/*static*/ /*public*/ DccLocoAddress* JsonUtilHttpService::addressForString(QString address) {
    QStringList components = address.split("[()]");
    int number = (components.at(0).toInt());
    bool isLong = false;
    if (components.length() > 1 && "L" == (components.at(1).toUpper())) {
        isLong = true;
    }
    return new DccLocoAddress(number, isLong);
}
#endif
