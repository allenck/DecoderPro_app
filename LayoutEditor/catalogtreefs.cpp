#include "catalogtreefs.h"
#include <QFileInfo>
#include "catalogtreenode.h"
#include <QDir>

//CatalogTreeFS::CatalogTreeFS(QObject *parent) :
//    AbstractCatalogTree(parent)
//{
//}
/**
 * TreeModel used by CatalogPanel to create a tree of resources.
 * <P>
 * Source of the tree content is the file system. Only directories are
 * included in the tree.  A filter can be set
 * to extract particular file types.
 *
 * @author			Pete Cressman  Copyright 2009
 *
 */
// /*public*/ class CatalogTreeFS extends AbstractCatalogTree {


/*public*/ CatalogTreeFS::CatalogTreeFS(QString sysName, QString userName, QObject *parent) : AbstractCatalogTree(sysName, userName, parent){
        //super(sysName, userName);
    parameters = new QMap<QString, QString>();
    }

/*public*/ void CatalogTreeFS::setFilter(QStringList filter) {
    _filter =  QStringList();
    for (int i=0; i<filter.length(); i++) {
        _filter.append(filter.at(i));
    }
}

/*public*/ QStringList CatalogTreeFS::getFilter() {
    QStringList filter =  QStringList();
    for (int i=0; i<_filter.length(); i++) {
        filter.append( _filter.at(i));
    }
    return filter;
}

bool CatalogTreeFS::filter(QString ext) {
    if (ext == "") return false;
    if (/*_filter == null ||*/ _filter.length() == 0) return true;
    for (int i=0; i<_filter.length(); i++) {
        if (ext==(_filter.at(i))) {
            return true;
        }
    }
    return false;
}

/**
 * Recursively add nodes to the tree
 * @param pName Name of the resource to be scanned; this
 *              is only used for the human-readable tree
 * @param pPath Path to this resource, including the pName part
 * @param pParent Node for the parent of the resource to be scanned, e.g.
 *              where in the tree to insert it.
 */
/*public*/ void CatalogTreeFS::insertNodes(QString pName, QString pPath, CatalogTreeNode* pParent) {
    QFileInfo fp = QFileInfo(pPath);
    if (!fp.exists()) return;

    // suppress overhead files
    QString filename = fp.fileName();
    if (filename.startsWith(".")) return;
    if (filename==("CVS")) return;

    if (fp.isDir()) {
        // first, represent this one
        CatalogTreeNode* newElement = new CatalogTreeNode(pName);
        insertNodeInto(newElement, pParent, pParent->getChildCount());
        QDir dir(fp.absoluteDir());
        QStringList sp = dir.entryList();
        for (int i=0; i<sp.length(); i++) {
            //if (log.isDebugEnabled()) log.debug("Descend into resource: "+sp[i]);
            insertNodes(sp.at(i), pPath+"/"+sp.at(i), newElement);
        }
    } else /* leaf */ {
        //QString ext = FileChooserFilter.getFileExtension(fp);
        QString ext = fp.suffix();
        if (!filter(ext)) return;
        int index = filename.indexOf('.');
        if (index > 0) {
            filename = filename.mid(0, index);
        }
        pParent->addLeaf(filename, pPath);
    }
}

/*public*/ void CatalogTreeFS::setProperty(QString key, QString value) {
    if (parameters == NULL)
        parameters = new QMap<QString, QString>();
    parameters->insert(key, value);
}

/*public*/ QVariant CatalogTreeFS::getProperty(QString key) {
    if (parameters == NULL) return QVariant();
    return parameters->value(key);
}

/*public*/ QList<QString> CatalogTreeFS::getPropertyKeys() {
    return parameters->keys();
}

