#include "defaultcatalogtreemanagerxml.h"
#include "fileutil.h"
#include "catalogtreemanager.h"
#include "defaultcatalogtreemanager.h"
#include "abstractcatalogtree.h"
#include "catalogtreenode.h"
#include "catalogtree.h"
#include "imageindexeditor.h"
#include "instancemanager.h"
#include "catalogtreeleaf.h"
#include "version.h"

DefaultCatalogTreeManagerXml::DefaultCatalogTreeManagerXml(QObject *parent) :
    XmlFile(parent)
{
    log = new Logger("DefaultCatalogTreeManagerXml");
}
/**
 * Provides the abstract base and store functionality for
 * configuring the CatalogTreeManager.
 * <P>
 * Typically, a subclass will just implement the load(QDomElement catalogTree)
 * class, relying on implementation here to load the individual CatalogTree objects.
 *
 * @author Pete Cressman Copyright: Copyright (c) 2009
 *
 */
///*public*/ class DefaultCatalogTreeManagerXml extends XmlFile
//                    /* extends jmri.configurexml.AbstractXmlAdapter */ {

///*private*/ /*static*/ QString DefaultCatalogTreeManagerXml::defaultFileName = FileUtil::getUserFilesPath() + "catalogTrees.xml";
/*private*/ /*static*/ QString DefaultCatalogTreeManagerXml::defaultFileName = QDir::homePath() + QDir::separator()+".jmri"+ QDir::separator() + "catalogTrees.xml";

//    /*public*/ DefaultCatalogTreeManagerXml() {
//    }

    /*
     *  Writes out tree values to a file in the user's preferences directory
     */
    //@SuppressWarnings("unchecked")
/*public*/ void DefaultCatalogTreeManagerXml::writeCatalogTrees() /*throw (IOException)*/
{
 if (log-> isDebugEnabled()) log-> debug("entered writeCatalogTreeValues");
 CatalogTreeManager* manager = (CatalogTreeManager*)InstanceManager::getDefault("CatalogTreeManager");
 QStringList trees = manager->getSystemNameList();
 bool found = false;
 QStringListIterator iter( manager->getSystemNameList());
 while (iter.hasNext())
 {
  QString sname = iter.next();
  CatalogTree* tree = (CatalogTree*)manager->getBySystemName(sname);
  if (log-> isDebugEnabled())
  {
   log-> debug("Tree: sysName= "+sname+", userName= "+((AbstractCatalogTree*)tree)->getUserName());
   CatalogTreeNode* root = (CatalogTreeNode*)tree->getRoot();
   log-> debug("enumerateTree called for root= "+root->toString()+
                      ", has "+root->getChildCount()+" children");
   QVectorIterator<CatalogTreeNode*>* e =(QVectorIterator<CatalogTreeNode*>*)root->depthFirstEnumeration();
   while (e->hasNext())
   {
    CatalogTreeNode* n = e->next();
    log-> debug("nodeName= "+n->getUserObject().toString()+" has "+QString::number(n->getLeaves()->size())+
                      " leaves and "+QString::number(n->getChildCount())+" subnodes.");
   }
  }
  if (sname != "" && sname.at(1) == CatalogTree::XML)
  {
   found =true;
   break;
  }
 }
 if (found)
 {
  // there are trees defined, create root element
//  QDomElement root = doc.createElement("catalogTrees");
//  Document doc = newDocument(root, dtdLocation+"catalogTree.dtd");
  QDomDocument doc;
  QDomElement root = doc.createElement("catalogTrees");

  // add XSLT processing instruction
  // <?xml-stylesheet type="text/xsl" href="XSLT/tree-values.xsl"?>
  QMap<QString,QString>* m = new QMap<QString,QString>();
  m->insert("type", "text/xsl");
  m->insert("href", xsltLocation+"panelfile.xsl");
  //ProcessingInstruction* p = new ProcessingInstruction("xml-stylesheet", m);
  QDomProcessingInstruction p = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/xsl\" href=\"/xml/XSLT/panelfile.xsl\"");
  doc.appendChild(p);
  p = doc.createProcessingInstruction("type", "text/xsl");
  doc.appendChild(p);
  p = doc.createProcessingInstruction("xml-stylesheet", QString("type=\"text/xsl\",href=\"%1locomotive.xsl\"").arg(xsltLocation));
  doc.appendChild(p);
  root.appendChild(doc.createComment(tr("Written by JMRI version %1 on %1").arg(Version::getCanonicalVersion()).arg(QDateTime::currentDateTime().toString())));

  store(root, trees);

  try
  {
   if (!checkFile(defaultFileName))
   {
    // file does not exist, create it
    QFile* file = new QFile(defaultFileName);
    if (!file->open(QIODevice::ReadWrite | QIODevice::Truncate))
     log-> error("createNewFile failed");
   }
   // write content to file
   writeXML(findFile(defaultFileName),doc);
   // memory consistent with file
   ImageIndexEditor::indexChanged(false);
  }
  catch (IOException ioe)
  {
    log-> error("IO Exception "+ioe.getMessage());
    throw (ioe);
  }
 }
}

/**
 * Default implementation for storing the contents of a CatalogTreeManager
 * @param cat QDomElement to load with contents
 * @param trees List of contents
 */
/*public*/ void DefaultCatalogTreeManagerXml::store(QDomElement cat, QStringList trees)
{
 CatalogTreeManager* manager = (CatalogTreeManager*)InstanceManager::getDefault("CatalogTreeManager");
 cat.setAttribute("class","jmri.jmrit.catalog-> DefaultCatalogTreeManagerConfigXML");
 QStringListIterator iter(trees);
    while (iter.hasNext()) {
        QString sname = iter.next();
        if (sname==""){
            log-> error("System name null during store");
            continue;
        }
        if (log-> isDebugEnabled()) log-> debug("system name is "+sname);
        if (sname.at(1) != CatalogTree::XML) {
            continue;
        }
        CatalogTree* ct = (CatalogTree*)manager->getBySystemName(sname);
        QDomElement elem = doc.createElement("catalogTree");
        elem.setAttribute("systemName", sname);
        QString uname = ct->getUserName();
        if (uname!="") elem.setAttribute("userName", uname);
        storeNode(elem, (CatalogTreeNode*)ct->getRoot());

        if (log-> isDebugEnabled()) log-> debug("store CatalogTree "+sname);
        cat.appendChild(elem);
    }
}


/**
 * Recursively store a CatalogTree
 */
//@SuppressWarnings("unchecked")
/*public*/ void DefaultCatalogTreeManagerXml::storeNode(QDomElement parent, CatalogTreeNode* node) {
    if (log-> isDebugEnabled()) log-> debug("storeNode "+node->toString()+
                             ", has "+QString::number(node->getLeaves()->size())+" leaves.");
    QDomElement element = doc.createElement("node");
    element.setAttribute("nodeName", node->toString());
    QVector<CatalogTreeLeaf*>* leaves = node->getLeaves();
    for (int i=0; i<leaves->size(); i++) {
        QDomElement el = doc.createElement("leaf");
        CatalogTreeLeaf* leaf = leaves->at(i);
        el.setAttribute("name", leaf->getName());
        el.setAttribute("path", leaf->getPath());
        element.appendChild(el);
    }
    parent.appendChild(element);
    //Enumeration<CatalogTreeNode> e = node.children();
    QVectorIterator<CatalogTreeNode*>* e = (( QVectorIterator<CatalogTreeNode*>*)node->children());
    while (e->hasNext()) {
        CatalogTreeNode* n = e->next();
        storeNode(element, n);
    }
}


/**
 * This is invoked as part of the "store all" mechanism,
 * which is not used for these objects. Hence this is
 * implemented to do nothing.
 */
/*public*/ QDomElement DefaultCatalogTreeManagerXml::store(QObject* /*o*/)
{
 return QDomElement();
}

/*
 *  Reads CatalogTree values from a file in the user's preferences directory
 */
/*public*/ void DefaultCatalogTreeManagerXml::readCatalogTrees() {
    if (log-> isDebugEnabled()) log-> debug("entered readCatalogTrees");
    //CatalogTreeManager manager = InstanceManager.catalogTreeManagerInstance();
    try {
        // check if file exists
        if (checkFile(defaultFileName)) {
            QDomElement root = rootFromName(defaultFileName);
            if (!root.isNull()) {
                load(root);
            }
        } else if (log-> isDebugEnabled()) log-> debug("File: "+defaultFileName+" not Found");
    }
    catch (JDOMException jde) { log-> error("Exception reading CatalogTrees: "+jde.getMessage()); }
    catch (IOException ioe) { log-> error("Exception reading CatalogTrees: "+ioe.getMessage()); }
}

/*public*/ void DefaultCatalogTreeManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
}

/**
 * Create a CatalogTreeManager object of the correct class, then
 * register and fill it.
 * @param catalogTrees Top level QDomElement to unpack.
 * @return true if successful
 */
/*public*/ bool DefaultCatalogTreeManagerXml::load(QDomElement catalogTrees) {
    loadCatalogTrees(catalogTrees);
    return true;
}

/**
 * Utility method to load the individual CatalogTree objects.
 */
//@SuppressWarnings("unchecked")
/*public*/ void DefaultCatalogTreeManagerXml::loadCatalogTrees(QDomElement catalogTrees) {
   QDomNodeList catList = catalogTrees.elementsByTagName("catalogTree");
    if (log-> isDebugEnabled()) log-> debug("loadCatalogTrees: found "+QString::number(catList.size())+" CatalogTree objects");
    CatalogTreeManager* mgr = (CatalogTreeManager*)InstanceManager::getDefault("CatalogTreeManager");

    for (int i=0; i<catList.size(); i++) {
        QDomElement elem = catList.at(i).toElement();
        QString attr = elem.attribute("systemName");
        if ( attr == "") {
            log-> warn("unexpected null systemName. elem= "+elem.tagName()+", attrs= "+QString::number(elem.attributes().count()));
            continue;
        }
        QString sysName = attr;
        QString userName = "";
        attr = elem.attribute("userName");
        if ( attr == "") {
            log-> warn("unexpected null userName. attrs= "+QString::number(elem.attributes().count()));
            continue;
        } else {
            userName = attr;
        }
        DefaultTreeModel* ct = (DefaultTreeModel*)((DefaultCatalogTreeManager*)mgr)->getBySystemName(sysName);
        if (ct != NULL) {
            continue;   // tree already registered
        }
        ct = (DefaultTreeModel*)((DefaultCatalogTreeManager*)mgr)->newCatalogTree(sysName, userName);
        if (log-> isDebugEnabled()) log-> debug("CatalogTree: sysName= "+sysName+", userName= "+userName);
        CatalogTreeNode* root = (CatalogTreeNode*)ct->getRoot();
        elem = elem.firstChildElement("node");
        loadNode(elem, root, ct);
    }
}

//@SuppressWarnings("unchecked")
/*private*/ void DefaultCatalogTreeManagerXml::addLeaves(QDomElement element, CatalogTreeNode* node) {
   QDomNodeList leafList = element.elementsByTagName("leaf");
    for (int i=0; i<leafList.size(); i++) {
        QDomElement elem = leafList.at(i).toElement();
        QString attr = elem.attribute("name");
        if ( attr == "") {
            log-> error("unexpected null leaf name. elem= "+elem.tagName()+", attrs= "+QString::number(elem.attributes().count()));
            continue;
        }
        QString name = attr;
        attr = elem.attribute("path");
        if ( attr == "") {
            log-> error("unexpected null leaf path. elem= "+elem.tagName()+", attrs= "+QString::number(elem.attributes().count()));
            continue;
        }
        QString path = attr;
        // use the method that maintains the same order
        node->addLeaf(new CatalogTreeLeaf(name, path, 0));
    }
}

/**
* Recursively load a CatalogTree
*/
//@SuppressWarnings("unchecked")
/*public*/ void DefaultCatalogTreeManagerXml::loadNode(QDomElement element, CatalogTreeNode* parent, DefaultTreeModel* model) {
   QDomNodeList nodeList = element.elementsByTagName("node");
    if (log-> isDebugEnabled()) log-> debug("Found "+QString::number(nodeList.size())+" CatalogTreeNode objects");
    for (int i=0; i<nodeList.size(); i++) {
        QDomElement elem = nodeList.at(i).toElement();
        QString attr = elem.attribute("nodeName");
        if ( attr == "") {
            log-> warn("unexpected null nodeName. elem= "+elem.tagName()+", attrs= "+QString::number(elem.attributes().count()));
            continue;
        }
        QString nodeName = attr;
        CatalogTreeNode* n = new CatalogTreeNode(nodeName);
        addLeaves(elem, n);
        model->insertNodeInto(n, parent, parent->getChildCount());
        loadNode(elem, n, model);
    }
}
