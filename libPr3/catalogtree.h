#ifndef CATALOGTREE_H
#define CATALOGTREE_H
#include "namedbean.h"
#include "../LayoutEditor/treemodel.h"
#include "libPr3_global.h"

class CatalogTreeNode;
class LIBPR3SHARED_EXPORT CatalogTree :  /*public TreeModel,*/ public TreeModel
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
    /*public*/ virtual void insertNodes(QString pName, QString pPath, CatalogTreeNode* pParent) = 0;

    /**
     * Starting point to recursively add nodes to the tree by scanning a file directory
     * @param pathToRoot Path to Directory to be scanned
     */
    /*public*/ virtual void insertNodes(QString pathToRoot) = 0;

signals:
    
public slots:
    
};

#endif // CATALOGTREE_H
