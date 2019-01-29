#ifndef DEFAULTCATALOGTREEMANAGER_H
#define DEFAULTCATALOGTREEMANAGER_H
#include "abstractmanager.h"
#include "catalogtreemanager.h"
#include "liblayouteditor_global.h"
#include "swingshutdowntask.h"


class ShutDownTask;
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
    /*public*/ char typeLetter() ;
    /*public*/ CatalogTree* getCatalogTree(QString name) ;
    /*public*/ CatalogTree* getBySystemName(QString key);
    /*public*/ CatalogTree* getByUserName(QString key);
    /*public*/ CatalogTree* newCatalogTree(QString sysName, QString userName);
    /*public*/ static DefaultCatalogTreeManager* instance();
    /*public*/  QStringList getSystemNameList();
    /*public*/ QString getBeanTypeHandled();
    /*public*/ void storeImageIndex();
    /*public*/ bool isIndexChanged();
    /*public*/ /*final*/ /*synchronized*/ void indexChanged(bool changed);
signals:

public slots:
private:
    /*private*/ static DefaultCatalogTreeManager* _instance;
    /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("DefaultCatalogTreeManager");
    void Register(CatalogTree * tree);
    bool _indexChanged;
    ShutDownTask* _shutDownTask = nullptr;

protected:
    /*protected*/ void registerSelf();
    /*protected*/ CatalogTree* createNewCatalogTree(QString systemName, QString userName);
    QMap<QString, CatalogTree*>* _tsys;
    QMap<QString, CatalogTree*>* _tuser;
friend class DCTSwingShutDownTask;
};

class DCTSwingShutDownTask : SwingShutDownTask
{
 Q_OBJECT
 DefaultCatalogTreeManager* parent;
public:
 DCTSwingShutDownTask(QString name, QString warning, QString action, QWidget* component, DefaultCatalogTreeManager* parent) : SwingShutDownTask(name, warning, action, component)
 {
  this->parent = parent;
 }
 //@Override
 /*public*/ bool checkPromptNeeded() {
     return !parent->_indexChanged;
 }

 //@Override
 /*public*/ bool doPrompt() {
     parent->storeImageIndex();
     return true;
 }

};

Q_DECLARE_METATYPE(DefaultCatalogTreeManager)
#endif // DEFAULTCATALOGTREEMANAGER_H
