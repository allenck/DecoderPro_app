#ifndef JSONSERVERPREFERENCES_H
#define JSONSERVERPREFERENCES_H
#include "bean.h"
#include "xmlfile.h"

class Preferences;
class JsonServerPreferences : public Bean
{
public:
 JsonServerPreferences(QObject* parent = 0);
 /*public*/ static /*final*/ int DEFAULT_PORT;// = 2056;
 /*public*/ static JsonServerPreferences* getDefault();
 /*public*/ JsonServerPreferences(QString fileName, QObject* parent = 0);
 /*public*/ bool compareValuesDifferent(JsonServerPreferences* prefs) ;
 /*public*/ void apply(JsonServerPreferences* prefs);
 /*public*/ /*final*/ void openFile(QString fileName) throw (FileNotFoundException) ;
 /*public*/ void save();
 /*public*/ bool isDirty();
 /*public*/ bool isRestartRequired();
 /*public*/ int getHeartbeatInterval();
 /*public*/ void setHeartbeatInterval(int value);
 /*public*/ int getPort();
 /*public*/ void setPort(int value);
 /*public*/ void load(QDomElement child);

private:
  static /*final*/ QString XML_PREFS_ELEMENT;// = "JSONServerPreferences"; // NOI18N
  static /*final*/ QString HEARTBEAT_INTERVAL;// = "heartbeatInterval"; // NOI18N
  static /*final*/ QString PORT;// = "port"; // NOI18N
 void common();
 /*private*/ int heartbeatInterval;// = 15000;
 /*private*/ int port;// = DEFAULT_PORT;
 // as loaded prefences
 /*private*/ int asLoadedHeartbeatInterval;// = 15000;
 /*private*/ int asLoadedPort;// = DEFAULT_PORT;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(JsonServerPreferences.class);
 /*private*/ void readPreferences(Preferences* sharedPreferences);

};
/*private*/ /*static*/ class JsonServerPreferencesXml : public XmlFile
{
public:
};
#endif // JSONSERVERPREFERENCES_H
