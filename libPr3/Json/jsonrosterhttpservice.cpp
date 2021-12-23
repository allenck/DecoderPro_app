#include "jsonrosterhttpservice.h"
#include "json.h"
#include "jsonroster.h"
#include "roster.h"
#include "rosterentry.h"
#include "rostergroup.h"

/**
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JsonRosterHttpService extends JsonHttpService {

/*public*/ JsonRosterHttpService::JsonRosterHttpService(ObjectMapper mapper, QObject* parent) : JsonHttpService(mapper, parent) {
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonRosterHttpService::doGet(QString type, QString name, QLocale locale) throw (JsonException)
{
 if(type == JsonRoster::ROSTER)
 {
   QJsonObject node = QJsonObject(); //this->mapper.createObjectNode();
   if (name != NULL)
   {
       node.insert(JSON::GROUP, name);
   }
   return this->getRoster(locale, node);
 }
 else if(type == JsonRoster::ROSTER_ENTRY)
 {
  return this->getRosterEntry(locale, name);
 }
 else if(type == JsonRoster::ROSTER_GROUP)
 {
  return this->getRosterGroup(locale, name);
 }
 else if(type == JsonRoster::ROSTER_GROUPS)
 {
  return QJsonValue(this->getRosterGroups(locale));
 }
 else
 {
  throw JsonException(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, tr("Error Unknown Type %1").arg(type));
 }
}

//@Override
/*public*/ QJsonObject JsonRosterHttpService::doPost(QString type, QString /*name*/, QJsonObject /*data*/, QLocale /*locale*/) throw (JsonException)
{
 if (!(type== JsonRoster::ROSTER ||
            type ==  JsonRoster::ROSTER_ENTRY ||
       type ==  JsonRoster::ROSTER_GROUP ||
            type==  JsonRoster::ROSTER_GROUPS ))
  throw JsonException(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, tr("Error Unknown Type %1").arg(type));
 throw JsonException(HttpServletResponse::SC_METHOD_NOT_ALLOWED, tr("Posting %1 is not allowed.").arg(type));
}

//@Override
/*public*/ QJsonValue JsonRosterHttpService::doGetList(QString type, QLocale locale) throw (JsonException)
{
 if (type  ==
      JsonRoster::ROSTER || type == JsonRoster::ROSTER_ENTRY)
  return this->getRoster(locale, QJsonObject() /*this->mapper.createObjectNode()*/);
 else
 if(type ==  JsonRoster::ROSTER_GROUP || type ==  JsonRoster::ROSTER_GROUPS)
 {
  return QJsonValue(this->getRosterGroups(locale));
 }else
 {
  throw JsonException(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, tr("Error Unknown Type %1").arg(type));
 }
}

/*public*/ QJsonArray JsonRosterHttpService::getRoster(/*@NonNUll*/ QLocale locale, /*@NonNUll*/ QJsonObject data)
{
 QString group = (!(data.value(JSON::GROUP).isUndefined()) ? (data.value(JSON::GROUP).toString()) : QString(""));
 if (Roster::ALLENTRIES == group || Roster::_AllEntries(locale) == group) {
        group = "";
}
 QString roadName = (!data.value(JSON::ROAD).isUndefined()) ? data.value(JSON::ROAD).toString() : NULL;
 QString roadNumber = (!data.value(JSON::NUMBER).isUndefined()) ? data.value(JSON::NUMBER).toString() : NULL;
 QString dccAddress = (!data.value(JSON::ADDRESS).isUndefined()) ? data.value(JSON::ADDRESS).toString() : NULL;
 QString mfg = (!data.value(JSON::MFG).isUndefined()) ? data.value(JSON::MFG).toString() : NULL;
 QString decoderModel = (!data.value(JSON::DECODER_MODEL).isUndefined()) ? data.value(JSON::DECODER_MODEL).toString() : NULL;
 QString decoderFamily = (!data.value(JSON::DECODER_FAMILY).isUndefined()) ? data.value(JSON::DECODER_FAMILY).toString() : NULL;
 QString id = (!data.value(JSON::NAME).isUndefined()) ? data.value(JSON::NAME).toString() : NULL;

 QJsonArray root = QJsonArray(); //this->mapper.createArrayNode();
 foreach (RosterEntry* entry, Roster::getDefault()->getEntriesMatchingCriteria(roadName, roadNumber, dccAddress, mfg, decoderModel, decoderFamily, id, group))
 {
  root.append(getRosterEntry(locale, entry->getId()));
 }
 return root;
}

/**
 * Returns the JSON representation of a roster entry.
 *
 * Note that this returns, for images and icons, a URL relative to the root
 * folder of the JMRI server. It is expected that clients will fill in the
 * server IP address and port as they know it to be.
 *
 * @param locale The client's locale
 * @param id     The id of an entry in the roster
 * @return a roster entry in JSON notation
 * @throws jmri.server.json.JsonException If no roster entry exists for the
 *                                        given id
 */
/*public*/ QJsonValue JsonRosterHttpService::getRosterEntry(QLocale locale, QString id) throw (JsonException) {
    try {
        return this->getRosterEntry(locale, Roster::getDefault()->getEntryForId(id));
    } catch (NullPointerException* ex) {
        throw JsonException(HttpServletResponse::SC_NOT_FOUND, tr("Object type %1 named %2 not found.").arg(JsonRoster::ROSTER_ENTRY).arg(id));
    }
}

/**
 * Returns the JSON representation of a roster entry.
 *
 * Note that this returns, for images and icons, a URL relative to the root
 * folder of the JMRI server. It is expected that clients will fill in the
 * server IP address and port as they know it to be.
 *
 * @param locale the client's Locale
 * @param entry  A RosterEntry that may or may not be in the roster.
 * @return a roster entry in JSON notation
 */
/*public*/ QJsonValue JsonRosterHttpService::getRosterEntry(QLocale /*locale*/, /*@NonNUll*/ RosterEntry* entry)
{
 QJsonObject root = QJsonObject(); //this->mapper.createObjectNode();
 root.insert(JSON::TYPE, JsonRoster::ROSTER_ENTRY);
 QJsonObject data = QJsonObject(); //root.putObject(DATA);
 data.insert(JSON::NAME, entry->getId());
 data.insert(JSON::ADDRESS, entry->getDccAddress());
 data.insert(JSON::IS_LONG_ADDRESS, entry->isLongAddress());
 data.insert(JSON::ROAD, entry->getRoadName());
 data.insert(JSON::NUMBER, entry->getRoadNumber());
 data.insert(JSON::MFG, entry->getMfg());
 data.insert(JSON::DECODER_MODEL, entry->getDecoderModel());
 data.insert(JSON::DECODER_FAMILY, entry->getDecoderFamily());
 data.insert(JSON::MODEL, entry->getModel());
 data.insert(JSON::COMMENT, entry->getComment());
 data.insert(JSON::MAX_SPD_PCT, (entry->getMaxSpeedPCT()));
 data.insert(JSON::IMAGE, (entry->getImagePath() != NULL)
         ? "/" + JsonRoster::ROSTER + "/" + entry->getId() + "/" + JSON::IMAGE
         : NULL);
 data.insert(JSON::ICON, (entry->getIconPath() != NULL)
         ? "/" + JsonRoster::ROSTER + "/" + entry->getId() + "/" + JSON::ICON
         : NULL);
 data.insert(JSON::SHUNTING_FUNCTION, entry->getShuntingFunction());
 data.insert(JsonRoster::DATE_MODIFIED, (entry->getDateModified() != QDateTime())
         ? /*new ISO8601DateFormat().format(entry->entrygetDateModified())*/ QDateTime::fromString(entry->getDateUpdated()).toString(Qt::ISODate)
         : NULL);
 //QJsonArray labels = data.putArray(JSON::FUNCTION_KEYS);
 QJsonObject labels = QJsonObject();
 for (int i = 0; i <= entry->getMAXFNNUM(); i++)
 {
  QJsonObject label = QJsonObject(); //mapper.createObjectNode();
  label.insert(JSON::NAME, JSON::F + QString::number(i));
  label.insert(JSON::LABEL, entry->getFunctionLabel(i));
  label.insert(JSON::LOCKABLE, entry->getFunctionLockable(i));
  label.insert(JSON::ICON, (entry->getFunctionImage(i) != NULL)
          ? "/" + JsonRoster::ROSTER + "/" + entry->getId() + "/" + JSON::F + QString::number(i) + "/" + JSON::ICON
          : NULL);
  label.insert(JSON::SELECTED_ICON, (entry->getFunctionSelectedImage(i) != NULL)
          ? "/" + JsonRoster::ROSTER + "/" + entry->getId() + "/" + JSON::F + QString::number(i) + "/" + JSON::SELECTED_ICON
          : NULL);
  //labels.add(label);
  labels.insert(JSON::FUNCTION_KEYS, label);
 }
 data.insert(JSON::FUNCTION_KEYS, labels);
 //ArrayNode attributes = data.putArray(JsonRoster::ATTRIBUTES);
 QJsonArray attributes = QJsonArray();
 //entry->getAttributes().stream().forEach((name) -> {
 foreach(QString name, entry->getAttributes())
 {
  QJsonObject attribute = QJsonObject();//mapper.createObjectNode();
  attribute.insert(JSON::NAME, name);
  attribute.insert(JSON::VALUE, entry->getAttribute(name));
  attributes.append(attribute);
 }//);
 data.insert(JsonRoster::ATTRIBUTES, attributes);
 //ArrayNode rga = data.putArray(JsonRoster::ROSTER_GROUPS);
 QJsonArray rga = QJsonArray();
 //entry->entrygetGroups().stream().forEach((group) -> {
 foreach(RosterGroup* group, entry->getGroups())
 {
  rga.append(group->getName());
 }//);
 data.insert(JsonRoster::ROSTER_GROUPS, rga);
 root.insert(JSON::DATA, data);
 return root;
}

/*public*/ QJsonArray JsonRosterHttpService::getRosterGroups(QLocale locale) throw (JsonException)
{
 //QJsonObject root = mapper.createArrayNode();
 QJsonArray root = QJsonArray();
 root.append(getRosterGroup(locale, Roster::ALLENTRIES));
 foreach (QString name, Roster::getDefault()->getRosterGroupList())
 {
  root.append(getRosterGroup(locale, name));
 }
 return root;
}

/*public*/ QJsonObject JsonRosterHttpService::getRosterGroup(QLocale locale, QString name) throw (JsonException)
{
 int size = Roster::getDefault()->getEntriesInGroup(name).size();
 if (size != 0 || name == NULL || name.isEmpty() || name == (Roster::ALLENTRIES))
 {
  QJsonObject root = QJsonObject(); //mapper.createObjectNode();
  //ObjectNode data = root.putObject(DATA);
  QJsonObject data = QJsonObject();
  data.insert(JSON::NAME, (name == NULL || name.isEmpty()) ? Roster::_AllEntries(locale) : name);
  data.insert(JSON::LENGTH, size);
  root.insert(JSON::TYPE, JsonRoster::ROSTER_GROUP);
  root.insert(JSON::DATA, data);
  return root;
 }
 else
 {
  throw JsonException(HttpServletResponse::SC_NOT_FOUND, tr("Object type %1 named %2 not found.").arg(JsonRoster::ROSTER_GROUP).arg(name));
 }
}

