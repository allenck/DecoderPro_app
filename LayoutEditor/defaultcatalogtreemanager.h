#ifndef DEFAULTCATALOGTREEMANAGER_H
#define DEFAULTCATALOGTREEMANAGER_H
#include "abstractmanager.h"
#include "catalogtreemanager.h"
#include "liblayouteditor_global.h"
class CatalogTree;
class LIBLAYOUTEDITORSHARED_EXPORT DefaultCatalogTreeManager : public CatalogTreeManager
{
    Q_OBJECT
public:
    explicit DefaultCatalogTreeManager(QObject *parent = 0);
    ~DefaultCatalogTreeManager(){}
    DefaultCatalogTreeManager(const DefaultCatalogTreeManager&) : CatalogTreeManager() {}
    /*public*/ int getXMLOrder();
    /*public*/ QString getSystemPrefix() ;
    /*public*/ char typeLetter();
    /*public*/ CatalogTree* getCatalogTree(QString name) ;
    /*public*/ CatalogTree* getBySystemName(QString key);
    /*public*/ CatalogTree* getByUserName(QString key);
    /*public*/ CatalogTree* newCatalogTree(QString sysName, QString userName);
    /*public*/ static DefaultCatalogTreeManager* DefaultCatalogTreeManagerinstance();
    /*public*/  QStringList getSystemNameList();

signals:

public slots:
private:
    /*private*/ static DefaultCatalogTreeManager* _instance;
    /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("DefaultCatalogTreeManager");
    void Register(CatalogTree * tree);

protected:
    /*protected*/ void registerSelf();
    /*protected*/ CatalogTree* createNewCatalogTree(QString systemName, QString userName);
    QMap<QString, CatalogTree*>* _tsys;
    QMap<QString, CatalogTree*>* _tuser;

};
Q_DECLARE_METATYPE(DefaultCatalogTreeManager)
#endif // DEFAULTCATALOGTREEMANAGER_H
