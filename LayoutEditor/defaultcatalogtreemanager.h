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
    /*public*/ int getXMLOrder()const override;
    /*public*/ QString getSystemPrefix() const override;
    /*public*/ char typeLetter()const override ;
    /*public*/ CatalogTree* getCatalogTree(QString name) override;
    /*public*/ NamedBean* getBySystemName(QString key) const override;
    /*public*/ NamedBean* getByUserName(QString key) const override;
    /*public*/ CatalogTree* newCatalogTree(QString sysName, QString userName)override;
    /*public*/ static DefaultCatalogTreeManager* instance();
    /*public*/  QStringList getSystemNameList()override;
    /*public*/ QString getBeanTypeHandled();
    /*public*/ void storeImageIndex() /*override*/;
    /*public*/ bool isIndexChanged() /*override*/;
    /*public*/ /*final*/ /*synchronized*/ void indexChanged(bool changed) /*override*/;
    /*public*/ QString getNamedBeanClass()const override {
        return "CatalogTree";
    }
    SystemConnectionMemo* getMemo() const {return nullptr;}
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
    QMap<QString, NamedBean*>* _tsys;
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
