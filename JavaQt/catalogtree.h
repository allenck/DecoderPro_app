#ifndef CATALOGTREE_H
#define CATALOGTREE_H
#include "namedbean.h"
#include "catalogtreemodel.h"
#include "javaqt_global.h"

class AbstractNamedBean;
class CatalogTreeNode;
class JAVAQTSHARED_EXPORT CatalogTree :  /*public TreeModel,*/ public CatalogTreeModel
{
    Q_OBJECT
public:
    explicit CatalogTree(QObject *parent = 0);
    enum FILTER
    {
     IMAGE     = 'I',    // letter to filter for images/icons
     SOUND     = 'S',    // letter to filter for sounds
     SCRIPT    = 'T',    // letter to filter for scripts
     NOFILTER  = 'N',    // letter for unfiltered
     FILESYS   = 'F',    // typeLetter for tree based on file system
     XML       = 'X'    // typeLetter for index tree stored in XML file
    };
    /**
     * Recursively add a representation of the resources
     * below a particular resource
     * @param pName Name of the resource to be scanned; this
     *              is only used for the human-readable tree
     * @param pPath Path to this resource, including the pName part
     * @param pParent Node for the parent of the resource to be scanned, e.g.
     *              where in the tree to insert it.
     */
    /*public*/ virtual void insertNodes(QString /*pName*/, QString /*pPath*/, CatalogTreeNode* /*pParent*/) {}

    /**
     * Starting point to recursively add nodes to the tree by scanning a file directory
     * @param pathToRoot Path to Directory to be scanned
     */
    /*public*/ virtual void insertNodes(QString /*pathToRoot*/) {}
    QString getComment();
    void setComment(QString comment);
    QString getDisplayName();
    void addPropertyChangeListener(PropertyChangeListener* l, const QString beanRef, QString listenerRef);
    void addPropertyChangeListener(PropertyChangeListener* l);

    /*public*/ QString getSystemName() const;
    /*public*/ QString getUserName();
    /*public*/ void setUserName(QString s);
    /*public*/ void dispose();

signals:
    
public slots:

private:
    AbstractNamedBean* bean;
    QString systemName;
    QString userName;
protected:
    /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
 friend class DefaultCatalogTreeManager;
 friend class AbstractCatalogTree;
 friend class CatalogTreeManager;
 friend class CatalogTreeFS;
};

#endif // CATALOGTREE_H
