#ifndef DEFAULTCATALOGTREEMANAGERXML_H
#define DEFAULTCATALOGTREEMANAGERXML_H
#include "xmlfile.h"
#include "liblayouteditor_global.h"

class DefaultTreeModel;
class CatalogTreeNode;
class LIBLAYOUTEDITORSHARED_EXPORT DefaultCatalogTreeManagerXml : public XmlFile
{
    Q_OBJECT
public:
    explicit DefaultCatalogTreeManagerXml(QObject *parent = 0);
 ~DefaultCatalogTreeManagerXml() {}
 DefaultCatalogTreeManagerXml(const DefaultCatalogTreeManagerXml&) : XmlFile() {}
    /*public*/ void writeCatalogTrees() /*throw (IOException)*/;
    /*public*/ void store(QDomElement cat, QStringList trees);
    /*public*/ void storeNode(QDomElement parent, CatalogTreeNode* node);
    /*public*/ QDomElement store(QObject* o);
    /*public*/ void readCatalogTrees();
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ bool load(QDomElement catalogTrees);
    /*public*/ void loadCatalogTrees(QDomElement catalogTrees);
    /*public*/ void loadNode(QDomElement element, CatalogTreeNode* parent, DefaultTreeModel* model);

signals:

public slots:

private:
    Logger* log;
    /*private*/ static QString defaultFileName;// = FileUtil::getUserFilesPath() + "catalogTrees.xml";
    /*private*/ void addLeaves(QDomElement element, CatalogTreeNode* node);

};
Q_DECLARE_METATYPE(DefaultCatalogTreeManagerXml)
#endif // DEFAULTCATALOGTREEMANAGERXML_H
