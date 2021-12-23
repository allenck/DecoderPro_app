#include "abstractcatalogtree.h"
#include "catalogtreenode.h"
#include "abstractnamedbean.h"


//AbstractCatalogTree::AbstractCatalogTree(QObject *parent) :
//    DefaultTreeModel(parent)
//{
//}
/**
 * TreeModel used by CatalogPanel to create a tree of resources.
 * <P>
 *
 * @author			Pete Cressman  Copyright 2009
 *
 */
///*public*/ /*abstract*/ class AbstractCatalogTree extends DefaultTreeModel implements CatalogTree {


// private AbstractCatalogTree() {
//      super(new CatalogTreeNode("BAD Ctor!"));
//      mSystemName = null;
//      mUserName = null;
//      log->warn("Unexpected use of null ctor");
//      Exception e = new Exception();
//      e.printStackTrace();
//  }

/*public*/ AbstractCatalogTree::AbstractCatalogTree(QString sysname, QString username, QObject *parent) : CatalogTree( parent)
{
 //super(new CatalogTreeNode(username));
 root = new CatalogTreeNode(username);
 mUserName = username;
 mSystemName = sysname.toUpper();
 bean = new AbstractNamedBean(sysname,username);
}
AbstractCatalogTree::~AbstractCatalogTree()
{
 delete log;
}

///*public*/ AbstractCatalogTree(String sysname) {
//    this(sysname, "root");
//}

/**
 * Recursively add nodes to the tree
 * @param pName Name of the resource to be scanned; this
 *              is only used for the human-readable tree
 * @param pPath Path to this resource, including the pName part
 * @param pParent Node for the parent of the resource to be scanned, e.g.
 *              where in the tree to insert it.
 */
/*public*/ /*abstract*/ void AbstractCatalogTree::insertNodes(QString pName, QString pPath, CatalogTreeNode* pParent) {}

/**
 * Starting point to recursively add nodes to the tree by scanning a file directory
 * @param pathToRoot Path to Directory to be scanned
 */
/*public*/ void AbstractCatalogTree::insertNodes(QString pathToRoot) {
    CatalogTreeNode* root = (CatalogTreeNode*)getRoot();
    if (log->isDebugEnabled()) log->debug("insertNodes: rootName= "+root->getUserObject().toString() + ", pathToRoot= " + pathToRoot);
    insertNodes(root->getUserObject().toString(), pathToRoot, root);
}


/**** NamedBean implementation (Copied from AbstractNamedBean) **********/
/**
 * Get associated comment text.
 */
/*public*/ QString AbstractCatalogTree::getComment() { return this->comment; }

/**
 * Set associated comment text.
 * <p>
 * Comments can be any valid text.
 * @param comment Null means no comment associated.
 */
/*public*/ void AbstractCatalogTree::setComment(QString comment)
{
 QString old = this->comment;
 this->comment = comment;
 emit propertyChange("Comment", old, comment);
 emit(propertyChange(new PropertyChangeEvent((QObject*)this, "Comment", old, comment)));
}

/*public*/ QString AbstractCatalogTree::getDisplayName()
{
 QString name = getUserName();
 if (name != "" && name.length() > 0)
 {
  return name;
 }
 else
 {
  return getSystemName();
 }
}
#if 0
// implementing classes will typically have a function/listener to get
// updates from the layout, which will then call
        /*public*/ void firePropertyChange(String propertyName,
                            Object oldValue,
                        Object newValue)
 _once_ if anything has changed state

// since we can't do a "super(this)" in the ctor to inherit from PropertyChangeSupport, we'll
// reflect to it
//java.beans.PropertyChangeSupport pcs = new PropertyChangeSupport(this);

///*public*/ synchronized void addPropertyChangeListener(PropertyChangeListener l) {
//    pcs.addPropertyChangeListener(l);
//}
///*public*/ synchronized void removePropertyChangeListener(PropertyChangeListener l) {
//    pcs.removePropertyChangeListener(l);
//}

/**
 * Number of current listeners. May return -1 if the
 * information is not available for some reason.
 */
///*public*/ synchronized int getNumPropertyChangeListeners() {
//    return pcs.getPropertyChangeListeners().length;
//}

//Hashtable<java.beans.PropertyChangeListener, String> register = new Hashtable<java.beans.PropertyChangeListener, String>();
//Hashtable<java.beans.PropertyChangeListener, String> listenerRefs = new Hashtable<java.beans.PropertyChangeListener, String>();

///*public*/ synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l, String beanRef, String listenerRef) {
//    pcs.addPropertyChangeListener(l);
//    if(beanRef!=null)
//        register.put(l, beanRef);
//    if(listenerRef!=null)
//        listenerRefs.put(l, listenerRef);
//}

///*public*/ synchronized ArrayList<java.beans.PropertyChangeListener> getPropertyChangeListeners(String name) {
//    ArrayList<java.beans.PropertyChangeListener> list = new ArrayList<java.beans.PropertyChangeListener>();
//    Enumeration<java.beans.PropertyChangeListener> en = register.keys();
//    while (en.hasMoreElements()) {
//        java.beans.PropertyChangeListener l = en.nextElement();
//        if(register.get(l).equals(name)){
//            list.add(l);
//        }
//    }
//    return list;
//}

/* This allows a meaning full list of places where the bean is in use!*/
/*public*/ synchronized ArrayList<String> getListenerRefs() {
    ArrayList<String> list = new ArrayList<String>();
    Enumeration<java.beans.PropertyChangeListener> en = listenerRefs.keys();
    while (en.hasMoreElements()) {
        java.beans.PropertyChangeListener l = en.nextElement();
        list.add(listenerRefs.get(l));
    }
    return list;
}

/*public*/ synchronized void updateListenerRef(java.beans.PropertyChangeListener l, String newName){
    if(listenerRefs.contains(l)){
        listenerRefs.put(l, newName);
    }
}

/*public*/ synchronized String getListenerRef(java.beans.PropertyChangeListener l) {
    return listenerRefs.get(l);
}
#endif
/*public*/ QString AbstractCatalogTree::getSystemName() {return mSystemName;}

/*public*/ QString AbstractCatalogTree::getUserName() {return mUserName;}

/*public*/ void   AbstractCatalogTree::setUserName(QString s) {
    QString old = mUserName;
    mUserName = s;
    //firePropertyChange("UserName", old, s);
    emit propertyChange("UserName", QVariant(old), QVariant(s));
    emit(propertyChange(new PropertyChangeEvent(this, "UserName", old, s)));
}



//protected void firePropertyChange(String p, Object old, Object n) { pcs.firePropertyChange(p,old,n);}

/*public*/ void AbstractCatalogTree::dispose() { /*pcs = null;*/ }

/*public*/ int AbstractCatalogTree::getState(){ return 0; }

/*public*/ void AbstractCatalogTree::setState(int s) /*throw (JmriException)*/{}

/*private*/ /*final*/ /*static*/ Logger* AbstractCatalogTree::log = LoggerFactory::getLogger("AbstractCatalogTree");


//}
