#include "catalogtreemodel.h"
#include <QDir>
#include <QMimeData>
#include "fileutil.h"
#include <QDataStream>

/**
 * TreeModel used by CatalogPane to create a tree of resources.
 * <P>
 * Accessed via the instance() member, as we expect to have only one of these
 * models.
 * <P>
 * The tree has two top-level visible nodes. One, "icons", represents the
 * contents of the icons directory in the resources tree in the .jar file. The
 * other, "files", is all files found in the "resources" filetree in the
 * preferences directory. Note that this means that files in the distribution
 * directory are _not_ included.
 * <P>
 * As a special case "simplification", the catalog tree will not contain CVS
 * directories, or files whose name starts with a "."
 *
 * @author Bob Jacobsen Copyright 2002
 */
// /*public*/ class CatalogTreeModel extends DefaultTreeModel implements InstanceManagerAutoDefault {

/*public*/ CatalogTreeModel::CatalogTreeModel(QObject* parent) : DefaultTreeModel(new DefaultMutableTreeNode("Root"))
{
 if(fileRoot == nullptr)
  fileRoot = FileUtil::getUserFilesPath() + "resources";
    //super(new DefaultMutableTreeNode("Root"));
    dRoot = (DefaultMutableTreeNode*) DefaultTreeModel::getRoot();  // this is used because we can't store the DMTN we just made during the super() call

    // we manually create the first node, rather than use
    // the routine, so we can name it.
    this->insertResourceNodes("resources", FileUtil::getProgramPath()+ resourceRoot, dRoot);
    FileUtil::createDirectory(FileUtil::getProgramPath() + "resources");
    this->insertFileNodes("files", fileRoot, dRoot);
    setProperty("InstanceManagerAutoDefault", "yes");

}

/**
 * Recursively add a representation of the resources below a particular
 * resource
 *
 * @param pName   Name of the resource to be scanned; this is only used for
 *                the human-readable tree
 * @param pPath   Path to this resource, including the pName part
 * @param pParent Node for the parent of the resource to be scanned, e.g.
 *                where in the tree to insert it.
 */
void CatalogTreeModel::insertResourceNodes(QString pName, QString pPath, DefaultMutableTreeNode* pParent) {
    File* fp = new File(pPath);
    if (!fp->exists()) {
        return;
    }

    // suppress overhead files
    if (fp->getName().startsWith(".")) {
        return;
    }
    if (fp->getName() == "CVS") {
        return;
    }

    // first, represent this one
    DefaultMutableTreeNode* newElement = new DefaultMutableTreeNode(pName);
    insertNodeInto(newElement, pParent, pParent->getChildCount());
    // then look for children and recurse
    if (fp->isDirectory()) {
        // work on the kids
        QStringList sp = fp->list();

        if (sp.isEmpty()) {
            log->warn(tr("unexpected null list() in insertResourceNodes from \"%1\"").arg(pPath));
            return;
        }

        for (QString item : sp) {
            if(log->isDebugEnabled()) log->trace(tr("Descend into resource: %1").arg(item));
            insertResourceNodes(item, pPath + "/" + item, newElement);
        }
    }
}

/**
 * Recursively add a representation of the files below a particular file
 *
 * @param name   Name of the file to be scanned
 * @param path   the path to the file
 * @param parent Node for the parent of the file to be scanned
 */
void CatalogTreeModel::insertFileNodes(QString name, QString path, DefaultMutableTreeNode* parent) {
    File* fp = new File(path);
    if (!fp->exists()) {
        return;
    }

    // suppress overhead files
    if (fp->getName().startsWith(".")) {
        return;
    }
    if (fp->getName() == ("CVS")) {
        return;
    }

    // represent this one
    DefaultMutableTreeNode* newElement = new DefaultMutableTreeNode(name);
    insertNodeInto(newElement, parent, parent->getChildCount());
    // then look for childrent and recurse
    // getSystemResource is a URL, getFile is the filename string
    if (fp->isDirectory()) {
        // work on the kids
        QStringList sp = fp->list();
        for (QString sp1 : sp) {
            //if (log.isDebugEnabled()) log.debug("Descend into file: "+sp[i]);
            insertFileNodes(sp1, path + "/" + sp1, newElement);
        }
    }
}

#if 0
/**
 *
 * @return the managed instance
 * @deprecated since 4.9.2; use
 * {@link jmri.InstanceManager#getDefault(java.lang.Class)} instead
 */
//@Deprecated
/*static*/ /*public*/ CatalogTreeModel* CatalogTreeModel::instance() {
    return InstanceManager::getDefault("CatalogTreeModel");
}
#endif
/**
 * Starting point in the .jar file for the "icons" part of the tree
 */
/*static*/ /*final*/ QString CatalogTreeModel::resourceRoot = "resources";
/*static*/ /*final*/ QString CatalogTreeModel::fileRoot = nullptr;//FileUtil::getUserFilesPath() + "resources";

/*private*/ /*final*/ /*static*/ Logger* CatalogTreeModel::log = LoggerFactory::getLogger("CatalogTreeModel");
