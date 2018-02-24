#ifndef ABSTRACTCATALOGTREE_H
#define ABSTRACTCATALOGTREE_H
#include "catalogtree.h"
#include "logger.h"
#include "exceptions.h"
#include "liblayouteditor_global.h"

class PropertyChangeEvent;
class NamedBean;
class CatalogTreeNode;
class LIBLAYOUTEDITORSHARED_EXPORT AbstractCatalogTree : public CatalogTree
{
    Q_OBJECT
public:
    //explicit AbstractCatalogTree(QObject *parent = 0);
    /*public*/ AbstractCatalogTree(QString sysname, QString username="root", QObject *parent = 0);
    ~AbstractCatalogTree();
    virtual /*public*/ /*abstract*/ void insertNodes(QString pName, QString pPath, CatalogTreeNode* pParent);
    /*public*/ void insertNodes(QString pathToRoot);
    /*public*/ QString getComment();
    /*public*/ void setComment(QString comment) ;
    /*public*/ QString getDisplayName();
    /*public*/ QString getSystemName();
    /*public*/ QString getUserName();
    /*public*/ void   setUserName(QString s);
    /*public*/ void dispose();
    /*public*/ int getState();
    /*public*/ void setState(int s) throw (JmriException);
signals:
   void propertyChange(QString propertyName, QVariant old, QVariant s);
   void propertyChange(PropertyChangeEvent*);
public slots:
private:
    /*private*/ QString mUserName;
    /*private*/ QString mSystemName;
   //NamedBean* bean;
   /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("AbstractCatalogTree");

 QString comment;
 friend class DefaultCatalogTreeManager;
};

#endif // ABSTRACTCATALOGTREE_H
