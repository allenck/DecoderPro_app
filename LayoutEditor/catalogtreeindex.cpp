#include "catalogtreeindex.h"
#include "catalogtreenode.h"
#include <QHash>
#include <QSet>
//CatalogTreeIndex::CatalogTreeIndex(QObject *parent) :
//    AbstractCatalogTree(parent)
//{
//}
/**
 * TreeModel used by CatalogPanel to create a tree of resources.
 * This model is for trees that can be permanently stored to and
 * reloaded from an XML file.
 * <P>
 * Source of the tree content is an XML file.
 *
 * @author			Pete Cressman  Copyright 2009
 *
 */
///*public*/ class CatalogTreeIndex extends AbstractCatalogTree {

    /*public*/ CatalogTreeIndex::CatalogTreeIndex(QString sysName, QString userName, QObject *parent) : AbstractCatalogTree(sysName, userName, parent)
{
    log = new Logger("CatalogTreeIndex");
        //super(sysName, userName);
    parameters = NULL;
    }
CatalogTreeIndex::~CatalogTreeIndex()
{
 delete log;
}
    /**
     * Recursively add nodes to the tree
     * @param pName Name of the resource to be scanned; this
     *              is only used for the human-readable tree
     * @param pPath Path to this resource, including the pName part
     * @param pParent Node for the parent of the resource to be scanned, e.g.
     *              where in the tree to insert it.
     */
    /*public*/ void CatalogTreeIndex::insertNodes(QString pName, QString pPath, CatalogTreeNode* pParent) {
        CatalogTreeNode* newNode = NULL;
        if (pPath == NULL) {
            newNode = new CatalogTreeNode("Image Index");
        } else {
            newNode = new CatalogTreeNode(pName);
        }
        if (log->isDebugEnabled()) log->debug("insertNodeInto: newNode= "+newNode->getUserObject().toString()+
                                            ", into parent= "+pParent->getUserObject().toString());
        insertNodeInto(newNode, pParent, pParent->getChildCount());
    }
    /*
    public void insertNodes(QString rootName, QString pathToRoot) {
        CatalogTreeNode root = (CatalogTreeNode*)getRoot();
        insertNodes(rootName, pathToRoot, root);
    }
   */
    /*public*/ void CatalogTreeIndex::setProperty(QString key, QVariant value) {
        if (parameters == NULL)
            parameters = new QHash<QString, QVariant>();
        parameters->insert(key, value);
    }

    /*public*/ QVariant CatalogTreeIndex::getProperty(QString key) {
    if (parameters == NULL) return QVariant();
        return parameters->value(key);
    }

    /*public*/ QList<QString> CatalogTreeIndex::getPropertyKeys() {
        return parameters->keys();
    }


//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(CatalogTreeIndex.class.getName());
//}
