#ifndef XMLSUPPORT_H
#define XMLSUPPORT_H

#include <QObject>
#include <QTextStream>
#include <QtXml>
#include "exceptions.h"

class Preferences;
class XmlSupport : public QObject
{
 Q_OBJECT
public:
 explicit XmlSupport(QObject *parent = 0);
 static void importPreferences(QTextStream* is);
 static void _export(QTextStream* os, /*final*/ Preferences* p, bool subTree) throw (IOException, BackingStoreException) ;

signals:

public slots:
private:
 /*private*/ static /*final*/ QString PREFS_DTD_URI;// =
//     "http://java.sun.com/dtd/preferences.dtd";

 // The actual DTD corresponding to the URI
 /*private*/ static /*final*/ QString PREFS_DTD;// =
//     "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" +

//     "<!-- DTD for preferences -->"               +

//     "<!ELEMENT preferences (root) >"             +
//     "<!ATTLIST preferences"                      +
//     " EXTERNAL_XML_VERSION CDATA \"0.0\"  >"     +

//     "<!ELEMENT root (map, node*) >"              +
//     "<!ATTLIST root"                             +
//     "          type (system|user) #REQUIRED >"   +

//     "<!ELEMENT node (map, node*) >"              +
//     "<!ATTLIST node"                             +
//     "          name CDATA #REQUIRED >"           +

//     "<!ELEMENT map (entry*) >"                   +
//     "<!ATTLIST map"                              +
//     "  MAP_XML_VERSION CDATA \"0.0\"  >"         +
//     "<!ELEMENT entry EMPTY >"                    +
//     "<!ATTLIST entry"                            +
//     "          key CDATA #REQUIRED"              +
//     "          value CDATA #REQUIRED >"          ;
 /**
  * Version number for the format exported preferences files.
  */
 /*private*/ static /*final*/ QString EXTERNAL_XML_VERSION;// = "1.0";

 /*
  * Version number for the internal map files.
  */
 /*private*/ static /*final*/ QString MAP_XML_VERSION;// = "1.0";
 /*private*/ static QDomDocument loadPrefsDoc(QTextStream* in);
 /*private*/ static void ImportSubtree(Preferences* prefsNode, QDomElement xmlNode);
 /*private*/ static void ImportPrefs(Preferences* prefsNode, QDomElement map);
 /*private*/ static void putPreferencesInXml(QDomElement elt, QDomDocument doc,
            Preferences* prefs, bool subTree) throw (BackingStoreException);
 /*private*/ static /*final*/ void writeDoc(QDomDocument doc, QTextStream* out)
     throw (IOException);

};

#endif // XMLSUPPORT_H
