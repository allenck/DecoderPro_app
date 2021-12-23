#include "defaultcatalogtreemanager.h"
#include "catalogtreenode.h"
#include "catalogtree.h"
#include "abstractcatalogtree.h"
#include "catalogtreeindex.h"
#include "catalogtreefs.h"
#include "catalogtreemanager.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "itempalette.h"
#include "defaultcatalogtreemanagerxml.h"
#include "instancemanager.h"

/*private*/ /*static*/ DefaultCatalogTreeManager* DefaultCatalogTreeManager::_instance = nullptr;

DefaultCatalogTreeManager::DefaultCatalogTreeManager(QObject *parent) :
    CatalogTreeManager(parent)
{
 _tsys = new QMap<QString, NamedBean*>();
 _tuser = new QMap<QString, CatalogTree*>();
 _indexChanged= false;
 registerSelf();
}

/**
 * Provide the concrete implementation for the Internal CatalogTree Manager.
 * <P>
 * Control of the systemName is internal so the more casual approach of
 * SignalHeadManager is used rather than the ProxyManager style.
 *
 * @author			Pete Cressman Copyright (C) 2009
 *
 */
// /*public*/ class DefaultCatalogTreeManager extends jmri.managers.AbstractManager
//                    implements jmri.CatalogTreeManager {

///*public*/ DefaultCatalogTreeManager() {
//}

/**
 * Override parent method to not register this object to
 * be stored automatically as part of the general storage mechanism.
 **/
/*protected*/ void DefaultCatalogTreeManager::registerSelf() {
    log->debug("not registering");
}

/*public*/ int DefaultCatalogTreeManager::getXMLOrder() const{
    return 65400;
}

/**
* This is a bogus systemPrefix.  Naming is enforced in method
* createNewCatalogTree below.
*/
/*public*/ QString DefaultCatalogTreeManager::getSystemPrefix()const { return "0"; }

/**
*  Bogus typeLetter
*/
/*public*/ char DefaultCatalogTreeManager::typeLetter() const { return '0'; }

/*public*/ CatalogTree* DefaultCatalogTreeManager::getCatalogTree(QString name) {
    CatalogTree* t = (CatalogTree*)getByUserName(name);
    if (t!=NULL) return t;

    return (CatalogTree*)getBySystemName(name);
}

/*public*/ NamedBean *DefaultCatalogTreeManager::getBySystemName(QString key) const
{
 QString name = key.toUpper();
 if (log->isDebugEnabled())
 {
  log->debug("getBySystemName: systemName= "+name);
  CatalogTree* tree = (CatalogTree*)_tsys->value(name);
  if (tree != NULL)
  {
   CatalogTreeNode* root = (CatalogTreeNode*)((AbstractCatalogTree*)tree)->getRoot();
   log->debug("root= "+root->toString()+
                      ", has "+QString::number(root->getChildCount())+" children");
  }
 }
 return _tsys->value(name);
}

/*public*/ NamedBean *DefaultCatalogTreeManager::getByUserName(QString key) const {
    return (NamedBean *)_tuser->value(key);
}

/*public*/ CatalogTree*  DefaultCatalogTreeManager::newCatalogTree(QString sysName, QString userName)
{
 if (log->isDebugEnabled()) log->debug("new CatalogTree: systemName= "+sysName
                                     +", userName= "+userName);
 if (sysName == NULL) {
     log->error("SystemName cannot be NULL. UserName= "+userName);
     return NULL;
 }
 QString systemName = sysName.toUpper();

 // return existing if there is one
 CatalogTree* s;
 if ( (userName!="") && ((s = (CatalogTree*)getByUserName(userName)) != NULL))
 {
     if ((CatalogTree*)getBySystemName(systemName)!=s)
         log->error("inconsistent user ("+userName+") and system name ("+systemName+") results; userName related to ("+s->getSystemName()+")");
     return s;
 }
 if ( (s = (CatalogTree*)getBySystemName(systemName)) != NULL)
 {
     if ((s->getUserName() == NULL) && (userName != NULL))
         s->setUserName(userName);
     else if (userName != NULL) log->warn("Found memory via system name ("+systemName
                             +") with non-NULL user name ("+userName+")");
     return s;
 }

 // doesn't exist, make a new one
 s = createNewCatalogTree(systemName, userName);

 // save in the maps
 Register(s);
 return s;
}

/**
* Create a CatalogTree.
* <P>
* Naming convention is:
* <PRE>
*   IF... - filter for image files from the file system
*   SF... - filter for sound files from the file system
*   TF... - filter for script files from the file system
*   NF... - no filter for files from the file system
*   IX... - index for image files stored in XML config file
*   SX... - index for sound files stored in XML config file
*   TX... - index for script files stored in XML config file
*   NX... - index for files stored in XML config file
* </PRE>
*/
/*protected*/ CatalogTree* DefaultCatalogTreeManager::createNewCatalogTree(QString systemName, QString userName) {
    if (systemName == "" || systemName.length() == 0) {
        log->error("Null systemName!");
        return NULL;
    }
    if (userName == "" || userName.length() == 0) {
        log->error("Null userName!");
        return NULL;
    }
    if (systemName.at(1) == CatalogTree::XML) {

        switch (systemName.at(0).toLatin1() ) {
            case CatalogTree::IMAGE:
        case CatalogTree::SOUND:
        case CatalogTree::SCRIPT:
        case CatalogTree::NOFILTER:
#if 1
                return (CatalogTree*)new CatalogTreeIndex(systemName, userName);
#endif
            default:
                log->error("Bad systemName: "+systemName+" (userName= "+userName+")");
        }
    }
#if 1
    else if (systemName.at(1) == CatalogTree::FILESYS) {
        CatalogTreeFS* catTree = NULL;
        switch (systemName.at(0).toLatin1() )
        {
#if 1
            case CatalogTree::IMAGE:
                catTree = new CatalogTreeFS(systemName, userName);
                catTree->setFilter(CatalogTreeManager::IMAGE_FILTER);
                return (CatalogTree*)catTree;
            case CatalogTree::SOUND:
                catTree = new CatalogTreeFS(systemName, userName);
                catTree->setFilter(CatalogTreeManager::SOUND_FILTER);
                return (CatalogTree*)catTree;
            case CatalogTree::SCRIPT:
                catTree = new CatalogTreeFS(systemName, userName);
                catTree->setFilter(CatalogTreeManager::SCRIPT_FILTER);
                return (CatalogTree*)catTree;
            case CatalogTree::NOFILTER:
            return(CatalogTree*) new CatalogTreeFS(systemName, userName);
#endif
            default:
                log->error("Bad systemName: "+systemName+" (userName= "+userName+")");
        }
    }
#endif
    return nullptr;
}

/*public*/ /*static*/ DefaultCatalogTreeManager* DefaultCatalogTreeManager::instance() {
 return static_cast<DefaultCatalogTreeManager*>(InstanceManager::getDefault("DefaultCatalogTreeManager"));
}

//@Override
/*public*/ QString DefaultCatalogTreeManager::getBeanTypeHandled() {
    return tr("Catalog");
}

//@Override
/*public*/ void DefaultCatalogTreeManager::storeImageIndex() {
    ItemPalette::storeIcons();

    log->debug("Start writing CatalogTree info");
    try {
         DefaultCatalogTreeManagerXml().writeCatalogTrees();
        indexChanged(false);
    } catch (IOException ioe) {
        log->error("Exception writing CatalogTrees: ", &ioe);
    }
}

/*public*/ bool DefaultCatalogTreeManager::isIndexChanged() {
    return _indexChanged;
}

//@Override
/*public*/ /*final*/ /*synchronized*/ void DefaultCatalogTreeManager::indexChanged(bool changed) {
    _indexChanged = changed;
    if(InstanceManager::getOptionalDefault("ShutDownManager") != nullptr)
    {
     ShutDownManager* sdm = static_cast<ShutDownManager*>(InstanceManager::getOptionalDefault("ShutDownManager"));

     if (changed)
     {

      if (_shutDownTask == nullptr) {
          _shutDownTask = (ShutDownTask*)new DCTSwingShutDownTask("PanelPro Save default icon check",
                  tr("Index Changed"),
                  tr("Save And Quit"), nullptr, this);
//          {
//              @Override
//              public boolean checkPromptNeeded() {
//                  return !_indexChanged;
//              }

//              @Override
//              public boolean doPrompt() {
//                  storeImageIndex();
//                  return true;
//              }
//          };
          sdm->_register(_shutDownTask);
      }
  } else {
      if (_shutDownTask != nullptr) {
          sdm->deregister(_shutDownTask);
          _shutDownTask = nullptr;
      }
     }
 }//);
}

void DefaultCatalogTreeManager::Register(CatalogTree * tree)
{
 QString systemName = ((AbstractCatalogTree*)tree)->mSystemName;
  QString userName = ((AbstractCatalogTree*)tree)->mUserName;
  Q_ASSERT(!systemName.isEmpty());
 _tsys->insert(systemName, (NamedBean*)tree);
 _tuser->insert(userName, tree);
}


/*private*/ /*final*/ /*static*/ Logger* DefaultCatalogTreeManager::log = LoggerFactory::getLogger("DefaultCatalogTreeManager");
#if 0
//@ServiceProvider(service = InstanceInitializer.class)
public static class Initializer extends AbstractInstanceInitializer {

    @Override
    public <T> Object getDefault(Class<T> type) throws IllegalArgumentException {
        if (type.equals(CatalogTreeManager.class)) {
            return new DefaultCatalogTreeManager();
        }
        return super.getDefault(type);
    }

    @Override
    public Set<Class<?>> getInitalizes() {
        Set<Class<?>> set = super.getInitalizes();
        set.add(CatalogTreeManager.class);
        return set;
    }

}
#endif

/*public*/  QStringList DefaultCatalogTreeManager::getSystemNameList()
{
 return _tsys->keys();
}
