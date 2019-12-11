#include "itempalette.h"
#include "xmlfile.h"
#include "namedicon.h"
#include "catalogtreenode.h"
#include "catalogtreemanager.h"
#include "instancemanager.h"
#include "catalogtreenode.h"
#include "itempanel.h"
#include "tableitempanel.h"
#include "signalheaditempanel.h"
#include <QVBoxLayout>
#include "gridbagconstraints.h"
#include "catalogtree.h"
#include <QScrollArea>
#include "changeevent.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include "exceptions.h"
#include "catalogtreeleaf.h"
#include "abstractcatalogtree.h"
#include "defaultcatalogtreemanager.h"
#include "picklistmodel.h"
#include "imageindexeditor.h"
#include <QHash>
#include "imageindexeditor.h"
#include "fileutil.h"
#include "clockitempanel.h"
#include "signalmastitempanel.h"
#include "memoryitempanel.h"
#include "reporteritempanel.h"
#include "textitempanel.h"
#include "multisensoritempanel.h"
#include "indicatoritempanel.h"
#include "borderlayout.h"
#include "indicatortoitempanel.h"
#include "backgrounditempanel.h"
#include "defaultcatalogtreemanagerxml.h"
#include "displayframe.h"
#include "portalitempanel.h"
#include "editor.h"
#include "rpsitempanel.h"
#include "placewindow.h"
#include "joptionpane.h"

//ItemPalette::ItemPalette(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * Container for adding items to control panels
 *
 * @author Pete Cressman  Copyright (c) 2010
 */

///*public*/ class ItemPalette extends JmriJFrame implements ChangeListener  {

//    /*public*/ static final ResourceBundle rbp = ResourceBundle.getBundle("jmri.jmrit.display.palette.PaletteBundle");
//    /*public*/ static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.DisplayBundle");
//    /*public*/ static final ResourceBundle rbean = ResourceBundle.getBundle("jmri.NamedBeanBundle");

/*public*/ /*static*/ /*final*/ int ItemPalette::STRUT_SIZE = 10;
/*static*/ QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>* ItemPalette::_iconMaps = new QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>();
/*static*/ QMap<QString, QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>*>*ItemPalette:: _indicatorTOMaps = new QMap<QString, QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>*>();
/*static*/ QMap<QString, ItemPanel*>* ItemPalette::_tabIndex = 0;
/*static*/ QTabWidget* ItemPalette::_tabPane = NULL;


void ItemPalette::changeEvent(QEvent * e)
{
 if(e->type() == QEvent::ActivationChange)
   adjustSize();
}

/**
* Store palette icons in preferences file catalogTrees.xml
*/
/*public*/ /*static*/ void ItemPalette::storeIcons()
{
 if (_iconMaps==NULL)
 {
  return;     // never loaded
 }
 CatalogTreeManager* manager = (CatalogTreeManager*)InstanceManager::getDefault("CatalogTreeManager");
 // unfiltered, xml-stored, item palate icon tree
 CatalogTree* tree = manager->getBySystemName("NXPI");
 // discard old version
 if (tree != NULL)
 {
  manager->deregister((NamedBean*)tree);
 }
 tree = manager->newCatalogTree("NXPI", "Item Palette");
 CatalogTreeNode* root = (CatalogTreeNode*)tree->getRoot();

 QMapIterator<QString, QMap<QString, QMap<QString, NamedIcon*>*>*> it(*_iconMaps);
 while (it.hasNext())
 {
  //Entry<String, QHash<String, QHash<String, NamedIcon>>> entry = it.next();
  it.next();
  root->add(store3levelMap(it.key(), it.value()));
  if (log->isDebugEnabled()) log->debug("Add type node "+it.key());
 }

 QMapIterator<QString, QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>*> its( *_indicatorTOMaps);
 while (its.hasNext())
 {
  //Entry<String, QHash<String, QHash<String, QHash<String, NamedIcon>>>> entry = its.next();
  its.next();
  CatalogTreeNode* typeNode = new CatalogTreeNode(its.key());
  QMapIterator<QString, QMap<QString, QMap<QString, NamedIcon*>*>*> iter(*its.value());
  while (iter.hasNext())
  {
   //Entry<String, QHash<String, QHash<String, NamedIcon>>> ent = iter.next();
   iter.next();
   typeNode->add(store3levelMap(iter.key(), iter.value()));
   if (log->isDebugEnabled()) log->debug("Add IndicatorTO node "+iter.key());
  }
  root->add(typeNode);
  if (log->isDebugEnabled()) log->debug("Add IndicatorTO node "+iter.key());
 }
}

/*static*/ CatalogTreeNode* ItemPalette::store3levelMap(QString type, QMap<QString, QMap<QString, NamedIcon*>*>* familyMap)
{
 CatalogTreeNode* typeNode = new CatalogTreeNode(type);
 QMapIterator<QString, QMap<QString, NamedIcon*>*>  iter (*familyMap);
 while (iter.hasNext())
 {
  //QHash<QString,QHash<QString, NamedIcon*>*>* ent  =iter.next();
  iter.next();
  QString family = iter.key();
  CatalogTreeNode* familyNode = new CatalogTreeNode(family);
  QMap<QString, NamedIcon*>* iconMap = iter.value();
  QMapIterator<QString, NamedIcon*> iterat(* iconMap);
  while (iterat.hasNext())
  {
   iterat.next();
   QString state = iterat.key();
   QString path = iterat.value()->getURL();
   familyNode->addLeaf(state, path);
  }
  typeNode->add(familyNode);
  if (log->isDebugEnabled()) log->debug("Add familyNode "+familyNode->objectName());
 }
 return typeNode;
}

/*static*/ /*public*/ void ItemPalette::loadIcons(Editor *ed)
{
 if (_iconMaps==NULL)
 {
//        	long t = System.currentTimeMillis();
  DefaultCatalogTreeManagerXml* ctm = new DefaultCatalogTreeManagerXml();
  ctm->readCatalogTrees();
  _iconMaps = new QMap <QString, QMap<QString, QMap<QString, NamedIcon*>*>*>();
  _indicatorTOMaps =
            new QMap<QString, QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>*>();

  if (!loadSavedIcons(ed))
  {
   loadDefaultIcons(ed);
  }
//            System.out.println("Palette icons loaded in "+ (System.currentTimeMillis()-t)+ " milliseconds.");
 }
}

/*static*/ bool ItemPalette::loadSavedIcons(Editor* ed)
{
 log->setDebugEnabled(true);
 CatalogTreeManager* manager = (CatalogTreeManager*)InstanceManager::getDefault("CatalogTreeManager");
 CatalogTree* tree = ((DefaultCatalogTreeManager*)manager)->getBySystemName("NXPI");
 if (tree != NULL)
 {
  CatalogTreeNode* root = (CatalogTreeNode*)tree->getRoot();
  //@SuppressWarnings("unchecked")
  QListIterator<CatalogTreeNode*>* e((QListIterator<CatalogTreeNode*>*)root->children());
  while (e->hasNext())
  {
   CatalogTreeNode* node = e->next();
   if(node == NULL) break;
   QString typeName = node->getUserObject().toString();
   // detect this is a 4 level map collection.
   // not very elegant (i.e. extensible), but maybe all that's needed.
   if (typeName==("IndicatorTO"))
   {
    QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>* familyTOMap =
                                loadIndicatorFamilyMap(node,ed);
    if (log->isDebugEnabled()) log->debug("Add "+QString::number(familyTOMap->size())+
                    " indicatorTO families to item type "+typeName+" to _indicatorTOMaps.");
    _indicatorTOMaps->insert(typeName, familyTOMap);
   }
   else
   {
    QMap<QString, QMap<QString, NamedIcon*>*>* familyMap =
                                loadFamilyMap(node,ed);
    _iconMaps->insert(typeName, familyMap);
    if (log->isDebugEnabled()) log->debug("Add item type "+typeName+" to _iconMaps.");
   }
  }
  if (log->isDebugEnabled())
   log->debug("Icon Map has "+QString::number(_iconMaps->size())+" members");
  if(_iconMaps->size() < 3)
  {
      log->warn("Forcing load of default Icons!");
      return false; // temp fix force load of defaultIcons if _iconMaps has only 2 entries! (ACK)
  }
   return true;
 }
 return false;
}

/*static*/ QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>*
                                    ItemPalette::loadIndicatorFamilyMap(CatalogTreeNode* node, Editor* ed)
{
    QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>* familyMap =
                            new QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>();
    //@SuppressWarnings("unchecked")
    QVectorIterator<TreeNode*>* ee (node->children());
    while (ee->hasNext()) {
        CatalogTreeNode* famNode = (CatalogTreeNode*)ee->next();
        QString name = famNode->getUserObject().toString();
        familyMap->insert(name, loadFamilyMap(famNode,ed));
        QThread::yieldCurrentThread();
    }
    return familyMap;
}

/*static*/ QMap<QString, QMap<QString, NamedIcon *> *> *ItemPalette::loadFamilyMap(CatalogTreeNode* node, Editor *ed) {

    QMap <QString, QMap<QString, NamedIcon*>*>* familyMap =
             new QMap <QString, QMap<QString, NamedIcon*>*> ();
    //@SuppressWarnings("unchecked")
    QVectorIterator<CatalogTreeNode*>* ee((QVectorIterator<CatalogTreeNode*>*)node->children());
    while (ee->hasNext()) {
        CatalogTreeNode* famNode = ee->next();
        QString familyName = famNode->getUserObject().toString();
        QMap <QString, NamedIcon*>* iconMap = new QMap <QString, NamedIcon*> ();
        QVector <CatalogTreeLeaf*>* list = famNode->getLeaves();
        int w = 0;
        int h = 0;
        for (int i=0; i<list->size(); i++) {
            QString iconName = list->value(i)->getName();
            CatalogTreeLeaf* leaf = list->at(i);
            QString path = leaf->getPath();
            NamedIcon* icon = new NamedIcon(path, path);
            w = qMax(w, icon->getIconWidth());
            h = qMax(h, icon->getIconHeight());
            iconMap->insert(iconName, icon);
            if (log->isDebugEnabled()) log->debug("Add "+iconName+" icon to family "+familyName);
            QThread::yieldCurrentThread();
       }
        familyMap->insert(familyName, iconMap);
    }
    return familyMap;
}
/*static*/ QDomNodeList ItemPalette::getDefaultIconItemTypes() throw (JDOMException, IOException) {
        QUrl file = FileUtil::findURL("xml/defaultPanelIcons.xml");
        if (!file.isValid()) {
            log->error("defaultPanelIcons file (xml/defaultPanelIcons.xml) doesn't exist.");
            throw new IllegalArgumentException("defaultPanelIcons file (xml/defaultPanelIcons.xml) doesn't exist.");
        }
         XmlFile* xf = new XmlFile();
        QDomElement root = xf->rootFromURL(&file);
        QDomNodeList typeList = root.firstChildElement("ItemTypes").childNodes();
        return typeList;
    }

/*static*/ void ItemPalette::loadDefaultIcons(Editor *ed)
{
#if 0
 QFile* file = new QFile(FileUtil::getProgramPath()+ QString("xml")+QDir::separator()+"defaultPanelIcons.xml");
 if (!file->exists())
 {
  log->error("defaultPanelIcons file doesn't exist: "+file->fileName());
  throw  IllegalArgumentException("defaultPanelIcons file doesn't exist: "+file->fileName());
 }
 try
 {
  XmlFile* xf = new XmlFile();
  QDomElement root = xf->rootFromFile(file);
        //@SuppressWarnings("unchecked")
  QDomNodeList typeList = root.firstChildElement("ItemTypes").childNodes();
  for (int i = 0; i < typeList.size(); i++)
  {
   QString typeName = typeList.at(i).toElement().tagName();
            //@SuppressWarnings("unchecked")
   QDomNodeList families = typeList.at(i).toElement().childNodes();
   // detect this is a 4 level map collection.
   // not very elegant (i.e. extensible), but maybe all that's needed.
   if (typeName==("IndicatorTO"))
   {
    QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>* familyTOMap =
                                    loadDefaultIndicatorTOMap(families,ed);
    _indicatorTOMaps->insert(typeName, familyTOMap);
    if (log->isDebugEnabled()) log->debug("Add "+QString::number(familyTOMap->size())+
                        " indicatorTO families to item type "+typeName+" to _indicatorTOMaps.");
   }
   else
   {
    QMap<QString, QMap<QString, NamedIcon*>*>* familyMap = loadDefaultFamilyMap(families, ed);
    _iconMaps->insert(typeName, familyMap);
    if (log->isDebugEnabled()) log->debug("Add "+QString::number(familyMap->size())+
                                            " families to item type "+typeName+" to _iconMaps.");
   }
   QThread::yieldCurrentThread();
  }
 }
 catch (JDOMException e)
 {
  log->error("error reading file \""+file->fileName()+"\" due to: "+e.getMessage());
 }
 catch (IOException ioe)
 {
  log->error("error reading file \""+file->fileName()+"\" due to: "+ioe.getMessage());
 }
#else
 try {
     QDomNodeList typeList = getDefaultIconItemTypes();
     for (int i = 0; i < typeList.size(); i++) {
         QString typeName = typeList.at(i).toElement().tagName();
         QDomNodeList families = typeList.at(i).toElement().childNodes();
         loadFamilies(typeName, families, ed);
         QThread::yieldCurrentThread();
     }
 } catch (JDOMException e) {
     log->error("error reading file \"defaultPanelIcons.xml\" due to: " + e.getMessage());
 } catch (IOException ioe) {
     log->error("error reading file \"defaultPanelIcons.xml\" due to: " + ioe.getMessage());
 }
#endif
}

/*static*/ void ItemPalette::loadFamilies(QString typeName, QDomNodeList families, Editor* ed)
{
 // detect this is a 4 level map collection.
 // not very elegant (i.e. extensible), but maybe all that's needed.
 if (typeName == ("IndicatorTO")) {
     QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>* familyTOMap
             = loadDefaultIndicatorTOMap(families, ed);
     _indicatorTOMaps->insert(typeName, familyTOMap);
     if (log->isDebugEnabled()) {
         log->debug(tr("Add %1 indicatorTO families to item type %2 to _indicatorTOMaps.").arg(
                 familyTOMap->size()).arg(typeName));
     }
 } else {
     QMap<QString, QMap<QString, NamedIcon*>*>* familyMap = loadDefaultFamilyMap(families, ed);
     _iconMaps->insert(typeName, familyMap);
     if (log->isDebugEnabled()) {
         log->debug(tr("Add %1 families to item type \"%2\" to _iconMaps.").arg(
                 familyMap->size()).arg(typeName));
     }
 }
}

/*static*/ void ItemPalette::loadMissingItemType(QString itemType, Editor* ed) {
        try {
            QDomNodeList typeList = getDefaultIconItemTypes();
            for (int i = 0; i < typeList.size(); i++) {
                QString typeName = typeList.at(i).toElement().tagName();
                if (typeName!=(itemType)) {
                    continue;
                }
                QDomNodeList families = typeList.at(i).toElement().childNodes();
                loadFamilies(itemType, families, ed);
                static_cast<CatalogTreeManager*>(InstanceManager::getDefault("CatalogTreeManager"))->indexChanged(true);
            }
        } catch (JDOMException e) {
            log->error("error reading file \"defaultPanelIcons.xml\" due to: " + e.getMessage());
        } catch (IOException ioe) {
            log->error("error reading file \"defaultPanelIcons.xml\" due to: " + ioe.getMessage());
        }
    }
/*static*/ QMap<QString, QMap<QString, NamedIcon*>*>* ItemPalette::loadDefaultFamilyMap(QDomNodeList families, Editor *ed)
{

 QMap<QString, QMap<QString, NamedIcon*>*>* familyMap =
            new QMap<QString, QMap<QString, NamedIcon*>*> ();
 for (int k = 0; k < families.size(); k++)
 {
  QString familyName = families.at(k).toElement().tagName();
  QMap <QString, NamedIcon*>* iconMap =
                new QMap <QString, NamedIcon*> ();       // Map of all icons of in family, familyName
  //@SuppressWarnings("unchecked")
  QDomNodeList iconfiles = families.at(k).toElement().childNodes();
  for (int j = 0; j < iconfiles.size(); j++)
  {
   QString iconName = iconfiles.at(j).toElement().tagName();
   QString fileName = iconfiles.at(j).toElement().text().trimmed();
   if (fileName=="" || fileName.length()==0)
   {
    fileName = ":/resources/icons/misc/X-red.gif";
    log->warn("loadDefaultIcons: iconName= "+iconName+" in family "+familyName+" has no image file.");
   }
   if(fileName.startsWith("resources"))
       //fileName = FileUtil::getProgramPath() + fileName;
    fileName = ":/"+ fileName;

   NamedIcon* icon;
   try
   {
   icon = new NamedIcon(fileName, fileName);
   }
   catch (Exception e)
   {
    icon = nullptr;
   }
   if (icon == nullptr)
   {
       icon = ed->loadFailed(iconName, fileName);
       if (icon == nullptr) {
           log->info(tr("%1 removed for url= %2").arg(iconName).arg(fileName));
       }
   }
   if (icon != nullptr)
    iconMap->insert(iconName, icon);
  }
  familyMap->insert(familyName, iconMap);
  if (log->isDebugEnabled()) log->debug("Add "+QString::number(iconMap->size())+" icons to family "+familyName);
 }
 return familyMap;
}

/*static*/ QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>* ItemPalette::loadDefaultIndicatorTOMap(QDomNodeList typeList, Editor *ed)
{

 QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>* familyTOMap =
         new QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*> ();     // Map of all families of type, typeName
 for (int k = 0; k < typeList.size(); k++)
 {
  QString familyName = typeList.at(k).toElement().tagName();
  //@SuppressWarnings("unchecked")
  QDomNodeList types = typeList.at(k).toElement().childNodes();
  QMap<QString, QMap<QString, NamedIcon*>*>* familyMap = loadDefaultFamilyMap(types, ed);
  familyTOMap->insert(familyName, familyMap);
  if (log->isDebugEnabled()) log->debug(tr("Add ")+QString::number(familyMap->size())+
                         " IndicatorTO sub-families to item type "+familyName+" to IndicatorTO families.");
 }
 return familyTOMap;
}

/*static*/ /*public*/ ItemPalette* ItemPalette::getDefault(QString title,/* @Nonnull */Editor* ed) {
//        if (GraphicsEnvironment.isHeadless()) {
//            return null;
//        }
        ItemPalette* instance = static_cast<ItemPalette*>( InstanceManager::getOptionalDefault("ItemPalette"));//.orElseGet(() -> {
          if(instance == nullptr)
            return (ItemPalette*)InstanceManager::setDefault("ItemPalette", new ItemPalette(title, ed));
//        });
        QListIterator<ItemPanel*> iter(_tabIndex->values());
        while (iter.hasNext()) {
            iter.next()->setEditor(ed);
        }
        QString name = ed->getName();
        if (name == "" || name == ("")) {
            name = tr("Untitled");
        }
        instance->setTitle(tr("Item Palette") + " - " + name);
        // pack before setLocation
        instance->pack();
        instance->move(PlaceWindow::nextTo(ed, nullptr, instance));
        instance->setVisible(true);
        return instance;
    }

/*public*/ ItemPalette::ItemPalette(QWidget* parent) : DisplayFrame(true, true, parent)
{
 // super(true, true);
 init("", NULL);
 //loadIcons();
}

/*public*/ ItemPalette::ItemPalette(QString title, Editor* editor, QWidget* parent) : DisplayFrame(title, true, true, parent)
{
 //(title, true, true);
//        long t = System.currentTimeMillis();
 init(title, editor);
}

void ItemPalette::init(QString title, Editor* ed)
{
  STRUT_SIZE = 10;
  _iconMaps = NULL;
  //resize(551, 600);
  //setMinimumSize(500,600);
  _currentItemPanel = NULL;

 _tabIndex = new QMap<QString, ItemPanel*>();
 this->setTitle(title);
 loadIcons(ed);
 addWindowListener(new IPWindowListener(this));
// @Override
// public void windowClosing(java.awt.event.WindowEvent e) {
//     closePanels(e);
// }
//});

    makeMenus(ed);
    buildTabPane(this, ed);

    QWidget* centralWidget = getContentPane();
    if(centralWidget == nullptr)
    {
     centralWidget = new QWidget();
     setCentralWidget(centralWidget);
    }

//    QVBoxLayout* thisLayout = (QVBoxLayout*)centralWidget->layout();
//    if(centralWidget->layout() == nullptr)
//     thisLayout = new QVBoxLayout(centralWidget);
//    //setLayout(new BorderLayout(5, 5));
//    thisLayout->addWidget(_tabPane, 0, Qt::AlignCenter);//BorderLayout::CENTER);
    setCentralWidget(_tabPane);
    setLocation(10, 10);
//    JScrollPane sp = (JScrollPane) _tabPane.getSelectedComponent();
//    _currentItemPanel = (ItemPanel) sp.getViewport().getView();
    _currentItemPanel = (ItemPanel*)_tabPane->widget(_tabPane->currentIndex());
//    if (!jmri.util.ThreadingUtil.isGUIThread()) log.error("Not on GUI thread", new Exception("traceback"));
    //setCentralWidget(centralWidget);

    pack();
}

IPWindowListener::IPWindowListener(ItemPalette *palette) {this->palette = palette;}
void IPWindowListener::windowClosing(QCloseEvent *)
{
 palette->closePanels();
}

/**
 * Add the tabs on the Control Panel Editor.
 */
/*static*/ void ItemPalette::buildTabPane(ItemPalette* palette, Editor* editor)
{
    _tabPane = new QTabWidget();
    _tabPane->setObjectName(QString::fromUtf8("_tabPane"));
    _tabIndex = new QMap<QString, ItemPanel*>();

    ItemPanel* itemPanel;
#if 1
    itemPanel = new TableItemPanel(palette, "Turnout", NULL, PickListModel::turnoutPickModelInstance(), editor, palette);
    addItemTab(itemPanel, "Turnout", tr("Turnout"));
    itemPanel->init();  // show panel on start

    itemPanel = new TableItemPanel(palette, "Sensor", "", PickListModel::sensorPickModelInstance(), editor, palette);
    addItemTab(itemPanel, "Sensor", tr("Sensor"));
    itemPanel->init();

    itemPanel = new SignalHeadItemPanel(palette, "SignalHead", NULL, PickListModel::signalHeadPickModelInstance(), editor, palette);
    addItemTab(itemPanel, ("SignalHead"), tr("Signal Head"));
    itemPanel->init();

    itemPanel = new SignalMastItemPanel(palette, "SignalMast", NULL, PickListModel::signalMastPickModelInstance(), editor,palette);
    addItemTab(itemPanel, ("SignalMast"), tr("SignalMast"));
    itemPanel->init();

    itemPanel = new MemoryItemPanel(palette, "Memory", NULL,PickListModel::memoryPickModelInstance(), editor, palette);
    addItemTab(itemPanel, "Memory", tr("Memory"));
    itemPanel->init();

     itemPanel = new ReporterItemPanel(palette, "Reporter", NULL, PickListModel::reporterPickModelInstance(), editor, palette);
     addItemTab(itemPanel, "Reporter", tr("Reporter"));
    itemPanel->init();

    itemPanel = new TableItemPanel(palette, "Light", NULL, PickListModel::lightPickModelInstance(), editor, palette);
    addItemTab(itemPanel, "Light", tr("Light"));
    itemPanel->init();
#endif
    itemPanel = new MultiSensorItemPanel(palette, "MultiSensor", NULL, PickListModel::multiSensorPickModelInstance(), editor,palette);
    addItemTab(itemPanel, "MultiSensor", tr("MultiSensor"));
    temPanel->init();
#if 1
    itemPanel = new IconItemPanel(palette, "Icon", editor,palette);
    addItemTab(itemPanel, "Icon", tr("Icon"));
    itemPanel->init();

    itemPanel = new BackgroundItemPanel(palette, "Background", editor, palette);
    addItemTab(itemPanel, "Background", tr("Background"));
    itemPanel->init();

    itemPanel = new TextItemPanel(palette, "Text", editor,palette);
    addItemTab(itemPanel, "Text", tr("Text"));
    itemPanel->init();

    itemPanel = new RPSItemPanel(palette, "RPSReporter", NULL, editor);
    addItemTab(itemPanel, "RPSReporter", tr("RPSReporter"));
    itemPanel->init();

    itemPanel = new ClockItemPanel(palette, "FastClock", editor,palette);
    addItemTab(itemPanel, "FastClock", tr("FastClock"));
    itemPanel->init();

    itemPanel = new IndicatorItemPanel(palette, "IndicatorTrack", NULL, editor,palette);
    addItemTab(itemPanel, "IndicatorTrack", tr("IndicatorTrack"));
    itemPanel->init();

    itemPanel = new IndicatorTOItemPanel(palette, "IndicatorTO", NULL, PickListModel::turnoutPickModelInstance(), editor, palette);
    addItemTab(itemPanel, "IndicatorTO", tr("IndicatorTO"));
    itemPanel->init();

    itemPanel = new PortalItemPanel(palette, "Portal", NULL, editor);
    addItemTab(itemPanel, tr("Portal"), tr("Portal"));
    itemPanel->init();
#endif
    //_tabPane->addChangeListener(this);
    connect(_tabPane, SIGNAL(currentChanged(int)), palette, SLOT(tabPaneChanged(int)));
}

/*static*/ void ItemPalette::addItemTab(ItemPanel* itemPanel, QString key, QString tabTitle)
{
 log->debug(tr("add panel '%1', layout %2 contains %3 items, objectName = %4").arg(key).arg(itemPanel->layout()== nullptr?"null layout": itemPanel->thisLayout->metaObject()->className()).arg(itemPanel->children().size()).arg(itemPanel->thisLayout->objectName()));
  QScrollArea* scrollPane = new QScrollArea(/*itemPanel*/);
  scrollPane->setWidget(itemPanel);
  scrollPane->setWidgetResizable(true);
  _tabPane->addTab(scrollPane, tabTitle);
 _tabIndex->insert(key, itemPanel);
}

void ItemPalette::tabPaneChanged(int)
{
 adjustSize();
 stateChanged(new ChangeEvent(_tabPane));
}

/*public*/ void ItemPalette::stateChanged(ChangeEvent* /*e*/) {
// if (!jmri.util.ThreadingUtil.isGUIThread()) log.error("Not on GUI thread", new Exception("traceback"));
 // long t = System.currentTimeMillis();
 QTabWidget* tp = _tabPane;//(QTabWidget*) e->getSource();
// JScrollPane sp = (JScrollPane) tp.getSelectedComponent();
// ItemPanel p = (ItemPanel) sp.getViewport().getView();
 ItemPanel* p = (ItemPanel*)tp->widget(tp->currentIndex());
 p->init(); // (re)initialize tab pane
 log->debug("different tab displayed");
 if (_currentItemPanel != nullptr) {
//     _currentItemPanel->closeDialogs();
 }
 if (listener != NULL) listener->onInitEvent(DisplayFrame::getPreviewBg(), _tabPane->currentIndex()); // signal tab
 log->debug(tr("tab redisplayed, previewBgSet updated to %1").arg(DisplayFrame::getPreviewBg()));
 _currentItemPanel = p;
 pack();
}

/*private*/ void ItemPalette::makeMenus(Editor* editor) {
    QMenuBar* menuBar = new QMenuBar();
    QMenu* findIcon = new QMenu(tr("Find Icons"));
    menuBar->addMenu(findIcon);

    QAction* editItem = new QAction(tr("Create/Edit Image Index"),this);
//    editItem.addActionListener(new ActionListener() {
//            Editor editor;
//            /*public*/ void actionPerformed(ActionEvent e) {
//                ImageIndexEditor ii = ImageIndexEditor.instance(editor);
//                ii.pack();
//                ii.setVisible(true);
//            }
//            ActionListener init(Editor ed) {
//                editor = ed;
//                return this;
//            }
//        }.init(editor));
    IPEditItemActionListener* eial = new IPEditItemActionListener();
    connect(editItem, SIGNAL(triggered()), eial, SLOT(actionPerformed()));
    eial->init(editor);
    findIcon->addAction(editItem);
    findIcon->addSeparator();

    QAction* searchItem = new QAction(tr("Search File System for Icons"),this);
    findIcon->addAction(searchItem);
    setMenuBar(menuBar);
    addHelpMenu("package.jmri.jmrit.display.ItemPalette", true);
}
IPEditItemActionListener::IPEditItemActionListener()
{

}
IPEditItemActionListener* IPEditItemActionListener::init(Editor* ed)
{
 editor = ed;
 return this;
}

void IPEditItemActionListener::actionPerformed()
{
 ImageIndexEditor* ii = ImageIndexEditor::instance(editor);
 ii->pack();
 ii->setVisible(true);

}

/*public*/ void ItemPalette::closePanels(/*java.awt.event.WindowEvent e*/) {
    //java.awt.Component[] comps = _tabPane.getComponents();
    QObjectList comps = _tabPane->children();
    if (log->isDebugEnabled()) log->debug("closePanels: tab count= "+_tabPane->count());
    for (int i=0; i<comps.length(); i++)
    {
     //if (comps[i] instanceof ItemPanel)
        if(qobject_cast<ItemPanel*>(comps.at(i))!= NULL)
        {
            //log->debug("windowClosing "+i+"th panel= "+comps[i].getClass().getName());
// TODO:           ((ItemPanel*)comps.at(i))->dispose();
        }
    }
    JmriJFrame::windowClosing(NULL);
}

/**
* Look for duplicate name of family in the iterated set
*/
/*static*/ bool ItemPalette::familyNameOK(QWidget* frame, QString type, QString family, QStringListIterator it)
{
 if (family=="" || family.length()==0)
 {
  JOptionPane::showMessageDialog(frame,
          tr("Enter a name for this icon set."),
          tr("Warning"), JOptionPane::WARNING_MESSAGE);
     return false;
 }
 while (it.hasNext())
 {
  QString f = it.next();
  log->debug(tr("familyNameOK compare %1 %2 to %3").arg(type).arg(family).arg(f));
  if(family == f)
  {
     JOptionPane::showMessageDialog(frame,
          tr("%1 is already the name of an icon set for %2 icons.").arg(family).arg(type),
          tr("Warning"), JOptionPane::WARNING_MESSAGE);
     return false;
  }
 }
 return true;
}

/**
* Adding a new Family of icons to the device type
*/
/*static*/ /*protected*/ bool ItemPalette::addFamily(QWidget* frame, QString type, QString family, QMap<QString, NamedIcon*>* iconMap) {
    QStringListIterator iter (ItemPalette::getFamilyMaps(type)->keys());
    if (familyNameOK(frame, type, family, iter))
    {
        getFamilyMaps(type)->insert(family, iconMap);
        ItemPanel* itemPanel = _tabIndex->value(type);
        //if (itemPanel instanceof FamilyItemPanel)
        if(qobject_cast<FamilyItemPanel*>(itemPanel)!= NULL)
        {
            ((FamilyItemPanel*)itemPanel)->updateFamiliesPanel();
        }
        ImageIndexEditor::indexChanged(true);
        return true;
    }
    return false;
}

/**
* Getting all the Families of icons for a given device type
*/
/*static*/ /*protected*/ QMap<QString, QMap<QString, NamedIcon *> *> *ItemPalette::getFamilyMaps(QString type) {
    return _iconMaps->value(type);
}

/**
* Removing a Family of icons from the device type
*/
/*static*/ /*protected*/ void ItemPalette::removeIconMap(QString type, QString family) {
    if (log->isDebugEnabled()) log->debug("removeIconMap for family \""+family+" \" in type \""+type+"\"");
    _iconMaps->value(type)->remove(family);
    ImageIndexEditor::indexChanged(true);
    if (log->isDebugEnabled()) {
        QMap <QString, QMap<QString, NamedIcon*>*>* families = getFamilyMaps(type);
        if (families!=NULL && families->size()>0) {
            QStringListIterator it(families->keys());
            while (it.hasNext()) {
                log->debug("removeIconMap remaining Keys: family \""+it.next()+" \" in type \""+type+"\"");
            }
        }
    }
}

/**
* Getting a clone of the Family of icons for a given device type and family
*/
/*static*/ /*protected*/ QMap<QString, NamedIcon*>* ItemPalette::getIconMap(QString type, QString family) {

    QMap <QString, QMap<QString, NamedIcon*>*>* itemMap = _iconMaps->value(type);
    if (itemMap==NULL) {
        log->error("getIconMap failed. item type \""+type+"\" not found.");
        return NULL;
    }
    QMap<QString, NamedIcon*>* iconMap = itemMap->value(family);
    if (iconMap==NULL) {
        log->error("getIconMap failed. family \""+family+"\" not found in item type \""+type+"\".");
        return NULL;
    }
    return cloneMap(iconMap);
}
#if 1
/************** Currently only needed for IndicatorTO type ***************/

// add entire family
/*static*/ /*protected*/ bool ItemPalette::addLevel4Family(JmriJFrame* frame, QString type, QString family, QMap<QString, QMap<QString, NamedIcon*>*>* iconMap) {
    QStringListIterator iter( ItemPalette::getLevel4FamilyMaps(type)->keys());
    if (familyNameOK(frame, type, family, iter)) {
        getLevel4FamilyMaps(type)->insert(family, iconMap);
        ImageIndexEditor::indexChanged(true);
        return true;
    }
    return false;
}

// add entire family
/*static*/ /*protected*/ void ItemPalette::addLevel4FamilyMap(QString type, QString family,
                               QString key, QMap<QString, NamedIcon*>* iconMap) {
    QMap<QString, QMap<QString, NamedIcon*>*>* familyMap = getLevel4Family(type, family);
    familyMap->insert(key, iconMap);
    ImageIndexEditor::indexChanged(true);
}

// Currently only needed for IndicatorTO type
/*static protected*/ QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>*
                            ItemPalette::getLevel4FamilyMaps(QString type) {
    return _indicatorTOMaps->value(type);
}
// Currently only needed for IndicatorTO type
/*static protected*/ QMap<QString, QMap<QString, NamedIcon*>*>*
                            ItemPalette::getLevel4Family(QString type, QString family) {
    QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>* map = _indicatorTOMaps->value(type);
    return map->value(family);
}

// Currently only needed for IndicatorTO type
/*static protected*/ void ItemPalette::removeLevel4IconMap(QString type, QString family, QString key) {
    if (log->isDebugEnabled()) log->debug("removelvl4IconMap for indicator family \""+family+" \" in type \""+type+
                                        "\" with key = \""+key+"\"");
    if (key!=NULL) {
        _indicatorTOMaps->value(type)->value(family)->remove(key);
    } else {
        _indicatorTOMaps->value(type)->remove(family);
    }
    ImageIndexEditor::indexChanged(true);
}
/**************************************************************************/
#endif

/*static*/ /*protected*/ QMap<QString, NamedIcon*>* ItemPalette::cloneMap(QMap<QString, NamedIcon*>* map)
{
 QMap<QString, NamedIcon*>* clone = new QMap<QString, NamedIcon*>();
 if (map!=NULL)
 {
  QMapIterator<QString, NamedIcon*> it(*map);
  while (it.hasNext())
  {
   it.next();
   //QHash<QString, NamedIcon*>* entry = it.next();
   QString name = it.key();
   NamedIcon* icon = new NamedIcon(it.value());
   clone->insert(name, icon);
  }
 }
 return clone;
}

/*static*/ /*public*/ QString ItemPalette::convertText(QString name) {
    QString cName = name;
//    try {
//        cName = ItemPalette::rbean.getString(name);
//    } catch (MissingResourceException mre) {
//        try {
//            cName = ItemPalette.tr(name);
//        } catch (MissingResourceException mre2) {
//            cName = name;
//        }
//    }

// NOTE: See java class DisplayBundle.properties for more

    if(name == "LargeJewel")
        return tr("Large Jewel");
    if(name == "Small Jewel")
        return tr("Small Jewel");
    if(name == "ErrorTrack")
        return tr("Power Error");
    if(name == "OccupiedTrack")
        return tr("Occupied");
    if(name == "ClearTrack")
        return tr("Clear");
    if(name == "DontUseTrack")
        return tr("Out of Service");
    if(name == "AllocatedTrack")
        return tr("Allocated");
    if(name == "PositionTrack")
        return tr("Train Position");
    if(name == "BeanStateInconsistent")
        return tr("Inconsistent");
    if(name == "TurnoutStateClosed")
        return tr("Closed");
    if(name == "TurnoutStateThrown")
        return tr("Thrown");
    if(name == "BeanStateUnknown")
        return tr("Unknown");
    if(name == "SensorStateInactive")
        return tr("Inactive");
    if(name == "SensorStateActive")
        return tr("Active");
    if(name == "UpperWestToUpperEast")
        return tr("Upper West To Upper East");
    if(name == "LowerWestToLowerEast")
        return tr("Lower West To Lower East");
    if(name == "LowerWestToUpperEast")
        return tr("Lower West To Upper East");
    if(name == "UpperWestToLowerEast")
        return tr("Upper West To Lower East");
    if(name == "SignalHeadStateHeld")
        return tr("Held");
    if(name == "SignalHeadStateDark")
        return tr("Dark");
    if(name == "SignalHeadStateRed")
        return tr("Red");
    if(name == "SignalHeadStateYellow")
        return tr("Yellow");
    if(name == "SignalHeadStateGreen")
        return tr("Green");
    if(name == "SignalHeadStateLunar")
        return tr("Lunar");
    if(name == "SignalHeadStateFlashingRed")
        return tr("Flashing Red");
    if(name == "SignalHeadStateFlashingGreen")
        return tr("Flashing Green");
    if(name == "SignalHeadStateFlashingYellow")
        return tr("Flashing Yellow");
    if(name == "SignalHeadStateFlashingLunar")
        return tr("Flashing Lunar");
    if(name == "RightCrossOver")
       return tr("RH X-over");
    if(name == "LeftCrossOver")
       return tr("LH X-over");
    if(name == "RightTurnout")
       return tr("Right Hand Turnout");
    if(name == "LeftTurnout")
       return tr("Left Hand Turnout");


    return cName;
}

/*static*/ /*protected*/ QWidget* ItemPalette::makeBannerPanel(QString labelText, /*Component*/QWidget* field)
{
 QWidget* panel = new QWidget();
 QGridLayout* g;
 panel->setLayout(g=new QGridLayout());
 GridBagConstraints* c = new GridBagConstraints();
 c->gridwidth  = 1;
 c->gridheight = 1;
 c->gridx = 0;
 c->gridy = 0;
 c->anchor = GridBagConstraints::CENTER;
 g->addWidget(new QLabel(labelText),c->gridy, c->gridx,c->rowSpan(), c->colSpan());
 c->gridx = 1;
 c->anchor = GridBagConstraints::CENTER;
 c->weightx = 1.0;
 c->fill = GridBagConstraints::HORIZONTAL;  // text field will expand
 g->addWidget(field, c->gridy, c->gridx,c->rowSpan(), c->colSpan());
 return panel;
}

/*private*/ /*final*/ /*static*/ Logger* ItemPalette::log = LoggerFactory::getLogger("ItemPalette");
