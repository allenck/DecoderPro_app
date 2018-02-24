#include "catalogpane.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include <QScrollArea>
#include "namedicon.h"
#include "defaultmutabletreenode.h"
#include "catalogtreemodel.h"
#include "treepath.h"
#include "fileutil.h"

/**
 * Create a JPanel containing a tree of resources.
 * <p>
 * The tree has two top-level visible nodes. One, "icons", represents the
 * contents of the icons directory in the resources tree in the .jar file. The
 * other, "files", is all files found in the "resources" filetree in the
 * preferences directory. Note that this means that files in the distribution
 * directory are _not_ included.
 *
 * @author Bob Jacobsen Copyright 2002
 */
// /*public*/ class CatalogPane extends JPanel {


/*public*/ CatalogPane::CatalogPane(QWidget* parent) :QWidget(parent) {

    //super(true); // isDoubleBuffered???
 log->setDebugEnabled(true);
    preview = new QLabel();
    preview->setMinimumSize(50,50);

    // create basic GUI
    dTree = new JTree((CatalogTreeModel*)InstanceManager::getDefault("CatalogTreeModel"));
    QVBoxLayout* thisLayout;
    setLayout(thisLayout = new QVBoxLayout(this)); //, BoxLayout.Y_AXIS));

    // build the tree GUI
    //add(new JScrollPane(dTree));
    thisLayout->addWidget(dTree);
    dTree->setRootVisible(true);
    dTree->setShowsRootHandles(true);
    //dTree.setScrollsOnExpand(true);
    dTree->setExpandsSelectedPaths(true);
    dTree->setHeaderHidden(true);
    dTree->setRootIsDecorated(true);

    dTree->getSelectionModel()->setSelectionMode(DefaultTreeSelectionModel::SINGLE_TREE_SELECTION);

    dTree->addTreeSelectionListener(new CPTreeSelectionListener(this));
//    {
//        @Override
//        /*public*/ void valueChanged(TreeSelectionEvent e) {
//            if (!dTree.isSelectionEmpty() && dTree.getSelectionPath() != null) {
//                // somebody has been selected
//                preview.setIcon(getSelectedIcon());
//            } else {
//                preview.setIcon(null);
//            }
//        }
//    });

    // add a listener for debugging
    if (log->isDebugEnabled())
    {
        dTree->addTreeSelectionListener(new CP2TreeSelectionListener(this));
//        {
//            @Override
//            /*public*/ void valueChanged(TreeSelectionEvent e) {
//                if (!dTree.isSelectionEmpty() && dTree.getSelectionPath() != null) {
//                    // somebody has been selected
//                    log->debug("Selection event with {}", dTree.getSelectionPath());
//                    log->debug("          icon: {}", getSelectedIcon());
//                }
//            }
//        });
    }
    qDebug() <<"catalog root child count: " << ((DefaultMutableTreeNode*)((CatalogTreeModel*)dTree->model())->getRoot())->getChildCount();
    //dTree->expandAll();
    QWidget* previewPanel = new QWidget();
    //previewPanel.setLayout(new BoxLayout(previewPanel, BoxLayout.X_AXIS));
    QHBoxLayout* previewPanelLayout = new QHBoxLayout(previewPanel);
    previewPanelLayout->addWidget(new QLabel(tr("File Preview")));
    QScrollArea* js = new QScrollArea();//JScrollPane(preview);
    js->setWidget(preview);
    previewPanelLayout->addWidget(js);
    thisLayout->addWidget(previewPanel);
}

CPTreeSelectionListener::CPTreeSelectionListener(CatalogPane *cp) {this->cp = cp;}
/*public*/ void CPTreeSelectionListener::valueChanged(TreeSelectionEvent* e)
{
 TreePath* path = e->getPath();
 CatalogTreeNode* n = (CatalogTreeNode*)path->getLastPathComponent();
 cp->log->debug(tr("%1 ").arg(e->getPath()->toString()));
 NamedIcon* icon = cp->getSelectedIcon();
 if (!cp->dTree->isSelectionEmpty() && cp->dTree->getSelectionPath() != NULL && icon != NULL)
 {
     // somebody has been selected
     //cp->preview->setIcon(cp->getSelectedIcon());
  QPixmap p =QPixmap(icon->getFilename());
//  // get label dimensions
//  int w = cp->preview->width();
//  int h = cp->preview->height();
//  cp->preview->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
  cp->preview->resize(p.size());
  cp->preview->setPixmap(p);
 }
 else {
     cp->preview->setPixmap(QPixmap());
 }
}

CP2TreeSelectionListener::CP2TreeSelectionListener(CatalogPane *cp) { this->cp = cp;}
/*public*/ void CP2TreeSelectionListener::valueChanged(TreeSelectionEvent* /*e*/)
{
 NamedIcon* icon = cp->getSelectedIcon();
 if (!cp->dTree->isSelectionEmpty() && cp->dTree->getSelectionPath() != NULL) {
     // somebody has been selected
     cp->log->debug(tr("Selection event with %1").arg(cp->dTree->getSelectionPath()->toString()));
     cp->log->debug(tr("          icon: %1").arg(icon != NULL?icon->toString():"NULL"));
 }
}


/*public*/ NamedIcon* CatalogPane::getSelectedIcon() {
    if (dTree->isSelectionEmpty() || dTree->getSelectionPath() == NULL) {
        return NULL;
    }
    // somebody has been selected
    if (log->isDebugEnabled()) log->debug(tr("getSelectedIcon with %1").arg(dTree->getSelectionPath()->toString()));
    TreePath* path = dTree->getSelectionPath();
    int level = path->getPathCount();
    if (level < 3) {
        return NULL;
    }
    QString buf;
    QString name;
    if (((DefaultMutableTreeNode*) path->getPathComponent(1))->getUserObject().toString() == ("resources")) {
        // process a .jar icon
        buf = QString(CatalogTreeModel::resourceRoot);
        for (int i = 2; i < level; i++) {
            buf.append("/");
            buf.append(/*(String) */((DefaultMutableTreeNode*) path->getPathComponent(i))->getUserObject().toString());
        }
    } else if (((DefaultMutableTreeNode*) path->getPathComponent(1))->getUserObject().toString() == ("files")) {
        // process a file
        buf = QString(CatalogTreeModel::fileRoot);
        buf.append(/*(String)*/ ((DefaultMutableTreeNode*) path->getPathComponent(2))->getUserObject().toString());
        for (int i = 3; i < level; i++) {
            buf.append(File::separator);
            buf.append(/*(String)*/ ((DefaultMutableTreeNode*) path->getPathComponent(i))->getUserObject().toString());
        }
    } else {
        log->error(tr("unexpected first element on getSelectedIcon: %1").arg(((TreePath*)path->getPathComponent(1))->toString()));
        return NULL;
    }
    name = buf/*.toString()*/;
    if (log->isDebugEnabled()) log->debug(tr("attempt to load file from %1").arg(name));
    NamedIcon* icon = NamedIcon::getIconByName(name);
    return icon;
}


/*private*/ /*final*/ /*static*/ Logger* CatalogPane::log = LoggerFactory::getLogger("CatalogPane");
