#ifndef ABSTRACTSERVERPREFERENCES_H
#define ABSTRACTSERVERPREFERENCES_H
#include "bean.h"
#include "xmlfile.h"
#include <QtXml>

class Preferences;
class Logger;
class AbstractServerPreferences : public Bean
{
public:
 AbstractServerPreferences(QString fileName, QObject* parent = nullptr);
 /*public*/ AbstractServerPreferences(QObject *parent);
 /*public*/ void init(); // must be called after contructor complete!

 /*public*/ void load(QDomElement child);
 /*public*/ bool compareValuesDifferent(AbstractServerPreferences* prefs);
 /*public*/ void apply(AbstractServerPreferences* prefs);
 /*public*/ QDomElement store();
 /*public*/ /*final*/ void openFile(QString fileName);
 /*public*/ void save();
 /*public*/ bool isDirty();
 /*public*/ bool isRestartRequired();
 /*public*/ int getPort();
 /*public*/ void setPort(int value);
 /*abstract*/virtual /*public*/ int getDefaultPort();

private:
 /*private*/ int port;
 static /*final*/ QString XML_PREFS_ELEMENT;// = "AbstractServerPreferences"; // NOI18N
 static /*final*/ QString PORT;// = "port"; // NOI18N
 static Logger* log;
 /*private*/ QString fileName;
 QDomDocument doc;
 /*private*/ int asLoadedPort;

protected:
 virtual QString getClass() {}
 /*protected*/ void readPreferences(Preferences* sharedPreferences);

};
/*private*/ /*static*/ class AbstractServerPreferencesXml : public XmlFile {
};
#endif // ABSTRACTSERVERPREFERENCES_H
