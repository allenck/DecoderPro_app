#ifndef FILELOCATIONPANEXML_H
#define FILELOCATIONPANEXML_H
#include "abstractxmladapter.h"
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT FileLocationPaneXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    explicit FileLocationPaneXml(QObject *parent = 0);
    ~FileLocationPaneXml() {}
    FileLocationPaneXml(const FileLocationPaneXml&) : AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement e)  throw (Exception);
    /*public*/ void load(QDomElement /*element*/, QObject* /*o*/) throw (Exception);

signals:

public slots:
private:
    Logger* log;
    /*private*/ void storeLocation(QDomElement locations, QString attr, QString value);
    /*private*/ void storeUserFilesLocation(QDomElement locations, QString value);
    /*private*/ QString loadUserLocations(QDomElement messages, QString attr);
    /*private*/ void storeProgramFilesLocation(QDomElement locations, QString value);

};
Q_DECLARE_METATYPE(FileLocationPaneXml)
#endif // FILELOCATIONPANEXML_H
