#ifndef NAMEFILE_H
#define NAMEFILE_H
#include "xmlfile.h"

class NameFile : public XmlFile
{
 Q_OBJECT
public:
 NameFile(QObject* parent = 0);
 /*public*/ QSet<QString> names();
 /*public*/ QDomElement elementFromName(QString name);
 /*public*/ /*synchronized*/ static NameFile* instance();
 /*public*/ bool checkName(QString name);

private:
 static QString fileLocation;// = "";
 static QString nameFileName;// = "names.xml";
 // initialize logging
 Logger* log;
 static NameFile* _instance;// = null;
 void readFile(QString name) throw (JDOMException, IOException);
 void readNames(QDomElement root);
 void storeDefinition(QDomElement el);

protected:
 // hold names in a Hashtable
 /*protected*/ QHash<QString, QDomElement>* _nameHash;// = new QHash<QString, QDomElement>();

 /*protected*/ static QString defaultNameFilename();

};

#endif // NAMEFILE_H
