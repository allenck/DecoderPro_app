#include "listedtableframe.h"
#include "userpreferencesmanager.h"
#include "instancemanager.h"
#include <QLabel>
#include "box.h"
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include <QMenu>
#include <QStackedLayout>
#include <QSplitter>
#include <QMouseEvent>
#include "listedtableaction.h"
#include "jlist.h"
#include <QMenu>
#include <QMenuBar>
#include "storemenu.h"
#include <QPushButton>
#include <QStatusBar>
#include <QGridLayout>
#include "mysortfilterproxymodel.h"
#include "namedbeanpropertydescriptor.h"
#include <QCheckBox>
#include "flowlayout.h"
#include "guilafpreferencesmanager.h"

//ListedTableFrame::ListedTableFrame()
//{

//}
/**
 * Provide access to the various tables via a listed pane. Based upon the
 * apps.gui3.TabbedPreferences.java by Bob Jacoben
 * <P>
 * @author	Kevin Dickerson Copyright 2010
 * @author	Bob Jacobsen Copyright 2010
 */
///*public*/ class ListedTableFrame extends BeanTableFrame {


/*public*/ bool ListedTableFrame::isMultipleInstances() {
 return true;
}

/*static*/ QList<TabbedTableItemListArray*>* ListedTableFrame::tabbedTableItemListArrayArray = new QList<TabbedTableItemListArray*>();
/*static*/ bool ListedTableFrame::init = false;
/*static*/ int ListedTableFrame::lastdivider = 0;

/*public*/ ListedTableFrame::ListedTableFrame(QWidget* parent)
 : BeanTableFrame(tr("Listed Table Access"), parent)
{
//this(tr("TitleListedTable"));
 common();
}

/*public*/ ListedTableFrame::ListedTableFrame(QString s, QWidget* parent)
 : BeanTableFrame(s, parent)
{
 //super(s);
 common();
}

void ListedTableFrame::common()
{
 setObjectName("ListedTableFrame");
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 itemBeingAdded = NULL;
 log = new Logger("ListedTableFrame");
 lastSelectedItem = NULL;
 thisLayout = new QVBoxLayout(getContentPane());
 statusBar()->show();
 setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);


 if (InstanceManager::getNullableDefault("ListedTableFrame") == nullptr) {
    //We add this to the instanceManager so that other components can add to the table
    InstanceManager::store(this, "ListedTableFrame");
 }
 if (!init)
 {
  /*Add the default tables to the static list array, this should only be done
   once when first loaded*/
  addTable("jmri.jmrit.beantable.TurnoutTableTabAction", tr("Turnout Table"), false);
  addTable("jmri.jmrit.beantable.SensorTableTabAction", tr("Sensor Table"), false);
  addTable("jmri.jmrit.beantable.LightTableTabAction", tr("Light Table"), false);
  addTable("jmri.jmrit.beantable.SignalHeadTableAction", tr("Signal Table"), true);
  addTable("jmri.jmrit.beantable.SignalMastTableAction", tr("Signal Mast Table"), true);
  addTable("jmri.jmrit.beantable.SignalGroupTableAction", tr("Signal Group Table"), true);
  addTable("jmri.jmrit.beantable.SignalMastLogicTableAction", tr("Signal MastLogic Table"), true);
  addTable("jmri.jmrit.beantable.ReporterTableAction", tr("Reporter Table"), true);
  addTable("jmri.jmrit.beantable.MemoryTableAction", tr("Memory Table"), true);
  addTable("jmri.jmrit.beantable.RouteTableAction", tr("Route Table"), true);
  addTable("jmri.jmrit.beantable.LRouteTableAction", tr("LRoute Table"), true);
  addTable("jmri.jmrit.beantable.LogixTableAction", tr("Logix Table"), true);
  addTable("jmri.jmrit.beantable.BlockTableAction", tr("Block Table"), true);
  if (((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isOblockEditTabbed()) { // select _tabbed in prefs
      addTable("jmri.jmrit.beantable.OBlockTableAction", tr("MenuItemOBlockTable"), false);
  } // requires restart after changing the interface setting (on Display tab)
  addTable("jmri.jmrit.beantable.SectionTableAction", tr("Section Table"), true);
  addTable("jmri.jmrit.beantable.TransitTableAction", tr("Transit Table"), true);
  addTable("jmri.jmrit.beantable.AudioTableAction", tr("Audio Table"), false);
  addTable("jmri.jmrit.beantable.IdTagTableAction", tr("IdTag Table"), true);
  init = true;
 }
}

/*public*/ void ListedTableFrame::initComponents()
{
 //JmriJFrame::initComponents();


 actionList = new ActionJList(currTableIndex, this);

 detailpanel = new QStackedWidget();
 detailpanel->setObjectName("detailPanel");
 //resize(900,600);
 //QVBoxLayout* detailPanelLayout;
 //detailpanel->setLayout(detailPanelLayout = new QVBoxLayout()); // Java CardLayout
 //QVBoxLayout* detailPanelLayout = new QVBoxLayout(detailpanel);
 tabbedTableArray = new QList<LTFTabbedTableItem*>(); //(TabbedTableItemListArrayArray->size());
 QList<TabbedTableItemListArray*>* removeItem = new QList<TabbedTableItemListArray*>(/*5*/);
 for (int x = 0; x < tabbedTableItemListArrayArray->size(); x++)
 {
  /* Here we add all the tables into the panel*/
  TabbedTableItemListArray* item = tabbedTableItemListArrayArray->value(x);
  try {
   LTFTabbedTableItem* itemModel = new LTFTabbedTableItem(item->getClassAsString(), item->getItemString(), item->getStandardTableModel(), this);
   itemBeingAdded = itemModel;
   //detailpanel->add(itemModel->getPanel(), itemModel->getClassAsString());
   //detailPanelLayout->addWidget(itemModel->getPanel());
   detailpanel->addWidget(itemModel->getPanel());
   tabbedTableArray->append(itemModel);
   itemBeingAdded->getAAClass()->addToFrame(this);
  }
  catch (Exception ex) {
   detailpanel->addWidget(errorPanel(item->getItemString())/*, item->getClassAsString()*/);
   log->error("Error when adding " + item->getClassAsString() + " to display\n" /*+ ex*/);
  //ex.printStackTrace();
   removeItem->append(item);
  }
  detailpanel->adjustSize();
  setHidden(true);
 }

 foreach (TabbedTableItemListArray* dead, *removeItem) {
    tabbedTableItemListArrayArray->removeOne(dead);
 }

 list = new JList(getChoices());
//listScroller = new JScrollPane(list);

//    list->setSelectionMode(ListSelectionModel::SINGLE_INTERVAL_SELECTION);
//    list->setLayoutOrientation(JList.VERTICAL);
//    list->addMouseListener(actionList);
 connect(list, SIGNAL(pressed(QModelIndex)), this, SLOT(On_listSelection(QModelIndex)));


 buttonpanel = new QWidget();
 buttonpanel->setLayout(new QVBoxLayout); //BorderLayout(5, 0));
 buttonpanel->setLayout(new QVBoxLayout); //BoxLayout(buttonpanel, BoxLayout.Y_AXIS));
 buttonpanel->layout()->addWidget(/*listScroller*/list);

 buildMenus(tabbedTableArray->at(0));
 setTitle(tabbedTableArray->value(0)->getItemString());

 cardHolder = new QSplitter(Qt::Horizontal); //JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
 //            buttonpanel, detailpanel);
 cardHolder->addWidget(buttonpanel);
 cardHolder->addWidget(detailpanel);

 connect(cardHolder, SIGNAL(splitterMoved(int,int)), this, SLOT(splitterMoved(int, int)));

 cardHolder->setMinimumWidth(8);
 if (lastdivider != 0) {
     cardHolder->setMinimumWidth(lastdivider);
 }
 else
 { //Else if no specific size has been given we set it to the lists preferred width
     //cardHolder->setDividerLocation(listScroller.getPreferredSize().width);
  cardHolder->setMidLineWidth(8);
 }
#if 0
    cardHolder.addPropertyChangeListener(new PropertyChangeListener() {
        //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
                justification = "We only intend to use/save the last position of the Split frame")
        /*public*/ void propertyChange(PropertyChangeEvent e) {
            if (e.getPropertyName().equals("dividerLocation")) {
                lastdivider = (Integer) e.getNewValue();
            }
        }
    });
#endif
    connect(cardHolder, SIGNAL(splitterMoved(int,int)), this, SLOT(splitterMoved(int, int)));
 //    cardHolder->setOneTouchExpandable(true);
 getContentPane()->layout()->addWidget(cardHolder);
 adjustSize();
 actionList->selectListItem(0);
}

void ListedTableFrame::splitterMoved(int pos, int /*index*/)
{
 lastdivider = pos;
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setProperty(getClassName(),"dividerLocation", pos);
}

/*public*/ QString ListedTableFrame::getClassName()
{
 // java class name used by preferences
 return "jmri.jmrit.beantable.ListedTableFrame";
}

QWidget* ListedTableFrame::errorPanel(QString text)
{
    QWidget* error = new QWidget();
    error->setLayout(new FlowLayout());
    error->layout()->addWidget(new QLabel(tr("Sorry, an Error occurred and we are unable to display table for %1").arg( text)));
    return error;
}

/* Method allows for the table to goto a specific list item */
/*public*/ void ListedTableFrame::gotoListItem(QString selection) {
for (int x = 0; x < tabbedTableArray->size(); x++)
{
    try {
        if (tabbedTableArray->value(x)->getClassAsString()==(selection)) {
            actionList->selectListItem(x);
            currTableIndex = x;
            return;
        }
    } catch (Exception ex) {
        log->error("An error occurred in the goto list for " + selection);
    }
 }
}

/*public*/ void ListedTableFrame::addTable(QString aaClass, QString choice, bool stdModel)
{
 TabbedTableItemListArray* itemBeingAdded = NULL;
 for (int x = 0; x < tabbedTableItemListArrayArray->size(); x++)
 {
  if (tabbedTableItemListArrayArray->value(x)->getClassAsString()==(aaClass))
  {
   log->info("Class " + aaClass + " is already added");
   itemBeingAdded = tabbedTableItemListArrayArray->value(x);
   break;
  }
 }
 if (itemBeingAdded == NULL)
 {
  itemBeingAdded = new TabbedTableItemListArray(aaClass, choice, stdModel);
  tabbedTableItemListArrayArray->append(itemBeingAdded);
 }
}

/*public*/ void ListedTableFrame::dispose()
{
  pref->setSaveAllowed(false);
  for (LTFTabbedTableItem* tti : *tabbedTableArray) {
      tti->dispose();
  }
//  if (list->getListSelectionListeners().length > 0) {
//      list.removeListSelectionListener(list.getListSelectionListeners()[0]);
//  }
  BeanTableFrame::dispose();
  pref->setSaveAllowed(true);
}

void ListedTableFrame::buildMenus(/*final*/ LTFTabbedTableItem* item)
{
    QMenuBar* menuBar = new QMenuBar();
    //ResourceBundle rb = ResourceBundle.getBundle("apps.AppsBundle");
    QMenu* fileMenu = new QMenu(tr("File"));
    menuBar->addMenu(fileMenu);

    QAction* newItem = new QAction(tr("New Window"), this);
    fileMenu->addAction(newItem);
//    newItem.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            actionList.openNewTableWindow(list.getSelectedIndex());
//        }
//    });
    connect(newItem, SIGNAL(triggered(bool)), this, SLOT(On_newItem_triggered()));

    fileMenu->addMenu(new StoreMenu());

    QAction* printItem = new QAction(tr("Print Table"),this);
    fileMenu->addAction(printItem);
#if 1
//    printItem.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(printItem, &QAction::triggered, [=]{
     try {
         // MessageFormat headerFormat = new MessageFormat(getTitle());  // not used below
      QString footerFormat = QString(getTitle() + " page {0,number}");
      QString headerFormat = getTitle() + " page {0,number}";
          if (item->getStandardTableModel()) {
              item->getDataTable()->print(JTable::PrintMode::FIT_WIDTH, QString(), footerFormat);
          } else {
              item->getAAClass()->print(JTable::PrintMode::FIT_WIDTH, QString(), footerFormat);
          }
      } catch (PrinterException e1) {
          log->warn("error printing: " + e1.getLocalizedMessage(), e1);
      } catch (NullPointerException ex) {
          log->error("Trying to print returned a NPE error");
      }
//     }
    });
#endif
    QMenu* viewMenu = new QMenu(tr("View"));
    menuBar->addMenu(viewMenu);
    QSignalMapper* mapper = new QSignalMapper();
    connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(On_viewMenu_triggered(QObject*)));
    for (int i = 0; i < tabbedTableItemListArrayArray->size(); i++) {
        /*final*/ TabbedTableItemListArray* itemList = tabbedTableItemListArrayArray->at(i);
        QAction* viewItem = new QAction(itemList->getItemString(), this);
        viewMenu->addAction(viewItem);
//        viewItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                gotoListItem(itemList.getClassAsString());
//            }
//        });
        mapper->setMapping(viewItem, (QObject*)itemList);
        connect(viewItem, SIGNAL(triggered(bool)), mapper, SLOT(map()));
    }

    this->setMenuBar(menuBar);
    try {
        item->getAAClass()->setMenuBar(this);
        this->addHelpMenu(item->getAAClass()->helpTarget(), true);
    } catch (Exception ex) {
        log->error("Error when trying to set menu bar for " + item->getClassAsString() + "\n" /*+ ex*/);
    }
    this->update();
}

void ListedTableFrame::On_newItem_triggered()
{
 actionList->openNewTableWindow(list->getSelectedIndex()==-1? 0:list->getSelectedIndex());
}

void ListedTableFrame::On_viewMenu_triggered(QObject* obj)
{
    TabbedTableItemListArray* itemList = (TabbedTableItemListArray*)obj;
    gotoListItem(itemList->getClassAsString());
}

/* This is a bit of a bodge to add the contents to the bottom box and keep
* it backwardly compatable with the original views, if the original views
* are depreciated then this can be re-written
*/
//@TODO Sort out the procedure to add to bottom box
/*protected*/ void ListedTableFrame::addToBottomBox(QWidget* comp, QString c)
{
    for (int x = 0; x < tabbedTableArray->size(); x++) {
        if (tabbedTableArray->at(x)->getClassAsString()==(c)) {
            tabbedTableArray->at(x)->addToBottomBox(comp);
            return;
        }
    }
}

/*protected*/ /*static*/ QList<QString> ListedTableFrame::getChoices()
{
 QList<QString> choices = QList<QString>();
 for (int x = 0; x < tabbedTableItemListArrayArray->size(); x++)
 {
    choices.append(tabbedTableItemListArrayArray->at(x)->getItemString());
 }
 return choices;
}

//@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//    justification = "We only intend to use/save the last position of the Split frame")
/*public*/ void ListedTableFrame::setDividerLocation(int loc)
{
 if (loc == 0) {
    return;
 }
 //cardHolder.setDividerLocation(loc);
 //cardHolder->moveSplitter(loc,0);
 QList<int> sizes = cardHolder->sizes();
 if(sizes.count()==2)
 {
  int totalSize = sizes.at(0) +sizes.at(1);
  sizes.replace(0,loc);
  sizes.replace(1, totalSize-loc);
  cardHolder->setSizes(sizes);
 }
 lastdivider = loc;
 static_cast<UserPreferencesManager*>(InstanceManager::getDefault("UserPreferencesManager"))
                 ->setProperty(getClassName(), "dividerLocation", loc);
}

/*public*/ int ListedTableFrame::getDividerLocation()
{
 QList<int> sizes = cardHolder->sizes();
 lastdivider = sizes.at(0);
 return static_cast<UserPreferencesManager*>(InstanceManager::getDefault("UserPreferencesManager"))
                                ->getProperty(getClassName(), "dividerLocation").toInt();
}

//static class TabbedTableItem {

//AbstractTableAction tableAction;
//String className;
//String itemText;
//BeanTableDataModel dataModel;
//JTable dataTable;
//JScrollPane dataScroll;
//Box bottomBox;
//int bottomBoxIndex;	// index to insert extra stuff
/*static*/ /*final*/ int LTFTabbedTableItem::bottomStrutWidth = 20;

//bool TabbedTableItem::standardModel = true;


LTFTabbedTableItem::LTFTabbedTableItem(QString aaClass, QString choice, bool stdModel, ListedTableFrame* frame)
{
 this->frame = frame;
 dataModel = NULL;
 dataTable = NULL;
    dataPanel = new QWidget();
    dataPanel->setObjectName("dataPanel");
    dataPanel->resize(800,600);
    dataPanel->setMinimumSize(300,300);
    log = new Logger("LTFTabbedTableItem");

    className = aaClass;
    itemText = choice;
    standardModel = stdModel;
    tableAction = NULL;

    bottomBox = Box::createHorizontalBox();
    //QHBoxLayout* bottomBoxLayout = new QHBoxLayout(bottomBox);
    bottomBox->layout()->addWidget(Box::createHorizontalGlue());
    bottomBoxIndex = 0;
#if 0 // TODO:
    try {
        //Class<?> cl = Class.forName(aaClass);
        java.lang.reflect.Constructor<?> co = cl.getConstructor(new Class[]{String.class});
        tableAction = (AbstractTableAction) co.newInstance(choice);
    } catch (ClassNotFoundException e1) {
        log->error("Not a valid class : " + aaClass);
        return;
    } catch (NoSuchMethodException e2) {
        log->error("Not such method : " + aaClass);
        return;
    } catch (InstantiationException e3) {
        log->error("Not a valid class : " + aaClass);
        return;
    } catch (ClassCastException e4) {
        log->error("Not part of the abstractTableActions : " + aaClass);
        return;
    } catch (Exception e) {
        log->error("Exception " + e.toString());
        return;
    }
#endif
    QString classname = aaClass.mid(aaClass.lastIndexOf(".")+1);
    QObject* classPtr = NULL;
    int id = QMetaType::type(classname.toLocal8Bit());
    if(id != 0)
    {
  #if QT_VERSION < 0x050000
     classPtr = (QObject*)QMetaType::construct(id);
  #else
     classPtr = (QObject*)QMetaType::create(id);
#endif
    }
    else
    {
      log->error("Not a valid class : " + aaClass);
      return;
    }
    const QMetaObject* metaObject = classPtr->metaObject();
    int constructorCount = metaObject->constructorCount();
    //for(int i = metaObject->methodOffset(); i < metaObject->constructorCount(); ++i)
    QStringList constructors = QStringList();
    for(int i = 0; i < metaObject->constructorCount(); ++i)
    {
 #if QT_VERSION < 0x050000
     constructors << QString::fromLatin1(metaObject->method(i).signature());
 #else
     //constructors << QString::fromLatin1(metaObject->method(i).methodSignature());
     constructors << QString::fromLatin1(metaObject->constructor(i).methodSignature());
 #endif
    }

     tableAction = (AbstractTableAction*)metaObject->newInstance(Q_ARG(QString, itemText),Q_ARG(QObject*, this));
     tableAction->setText(itemText);

    //If a panel model is used, it should really add to the bottom box
    //but it can be done this way if required.
    dataPanel->setLayout(dataPanelLayout = new /*BorderLayout()*/QGridLayout);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(dataPanel->sizePolicy().hasHeightForWidth());
    dataPanel->setSizePolicy(sizePolicy);
    if (stdModel) {
        createDataModel();
    } else {
        addPanelModel();
    }
}

void LTFTabbedTableItem::createDataModel() {
    dataModel = tableAction->getTableDataModel();
    MySortFilterProxyModel* sorter = new MySortFilterProxyModel(dataModel);
    dataTable = dataModel->makeJTable(dataModel->getMasterClassName() + ":" + getItemString(), dataModel, sorter);
//    sorter->setTableHeader(dataTable->getTableHeader());
    //dataScroll = new JScrollPane(dataTable);

//    try {
//    QSortFilterProxyModel* tmodel = ((QSortFilterProxyModel*) dataTable->getModel());
//        tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        tmodel.setSortingStatus(BeanTableDataModel.SYSNAMECOL, TableSorter.ASCENDING);
//    } catch (java.lang.ClassCastException e) {
//    }  // happens if not sortable table
    dataModel->configureTable(dataTable);

    dataTable->setMinimumSize(300,300);
    QSize dataTableSize = dataTable->sizeHint();
    // width is right, but if table is empty, it's not high
    // enough to reserve much space.
    dataTableSize.setHeight(qMax(dataTableSize.height(), 400));
    //dataTable->resize(dataTableSize);

    // set preferred scrolling options
//    dataScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
//    dataScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(dataTable->sizePolicy().hasHeightForWidth());
    dataTable->setSizePolicy(sizePolicy);

    //dataPanel.add(dataScroll, BorderLayout.CENTER);
    dataPanelLayout->addWidget(dataTable,0,0); //,0, Qt::AlignHCenter);

    //dataPanel.add(bottomBox, BorderLayout.SOUTH);
    dataPanelLayout->addWidget(bottomBox, 1, 0); //, 0, Qt::AlignBottom);

    if (tableAction->includeAddButton())
    {
     QPushButton* addButton = new QPushButton(tr("Add"));
     addToBottomBox(addButton);
//        addButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                tableAction.addPressed(e);
//            }
//        });
     QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
     sizePolicy.setHorizontalStretch(0);
     sizePolicy.setVerticalStretch(0);
     sizePolicy.setHeightForWidth(addButton->sizePolicy().hasHeightForWidth());
     addButton->setSizePolicy(sizePolicy);
     connect(addButton, SIGNAL(clicked()), tableAction, SLOT(addPressed()));
    }

    if (dataModel->getPropertyColumnCount() > 0)
    {
        /*final*/ QCheckBox* propertyVisible = new QCheckBox(tr
                ("Show System-specific columns"));
        propertyVisible->setToolTip(tr
                ("If the underlying hardware has additional options to set, shows the columns for these options."));
        addToBottomBox(propertyVisible);
//        propertyVisible.addActionListener((ActionEvent e) -> {
//            dataModel.setPropertyColumnsVisible(dataTable, propertyVisible.isSelected());
//        });
        connect(propertyVisible, SIGNAL(clicked(bool)), this, SLOT(onPropertyVisible(bool)));
        dataModel->setPropertyColumnsVisible(dataTable, false);
    }
    dataModel->persistTable(dataTable);

    dataPanel->adjustSize();

    dataModel->persistTable(dataTable);
}

void LTFTabbedTableItem::onPropertyVisible(bool bChecked)
{
 dataModel->setPropertyColumnsVisible(dataTable, bChecked);

}

void LTFTabbedTableItem::addPanelModel() {
//    try {
        //dataPanel.add(tableAction.getPanel(), BorderLayout.CENTER);
     dataPanelLayout->addWidget(tableAction->getPanel(), 0,0); //, 0, Qt::AlignHCenter);
        //dataPanel.add(bottomBox, BorderLayout.SOUTH);
     dataPanelLayout->addWidget(bottomBox, 1,0); //, 0, Qt::AlignBottom);
//    } catch (NullPointerException e) {
//        log->error("An error occured while trying to create the table for " + itemText + " " + e.toString());
//        e.printStackTrace();
//    }
     dataPanel->adjustSize();

}

bool LTFTabbedTableItem::getStandardTableModel() {
    return standardModel;
}

QString LTFTabbedTableItem::getClassAsString() {
    return className;
}

QString LTFTabbedTableItem::getItemString() {
    return itemText;
}

AbstractTableAction* LTFTabbedTableItem::getAAClass() {
    return tableAction;
}

QWidget* LTFTabbedTableItem::getPanel() {
    return dataPanel;
}

JTable* LTFTabbedTableItem::getDataTable() {
    return dataTable;
}

/*protected*/ void LTFTabbedTableItem::addToBottomBox(QWidget* comp) {
    ((QHBoxLayout*)bottomBox->layout())->insertWidget(bottomBoxIndex,  Box::createHorizontalStrut( bottomStrutWidth) );
    ++bottomBoxIndex;
    ((QVBoxLayout*)bottomBox->layout())->insertWidget( bottomBoxIndex, comp);
    ++bottomBoxIndex;
}

void LTFTabbedTableItem::dispose() {
    if (dataModel != NULL) {
        dataModel->stopPersistingTable(dataTable);
        dataModel->dispose();
    }
    if (tableAction != NULL) {
        tableAction->dispose();
    }
    dataModel = NULL;
    dataTable = NULL;
    //dataScroll = NULL;
    dataTable = nullptr;
}
//};

//static class TabbedTableItemListArray {

//String className;
//String itemText;
//boolean standardModel = true;

TabbedTableItemListArray::TabbedTableItemListArray(QString aaClass, QString choice, bool stdModel) {
    className = aaClass;
    itemText = choice;
    standardModel = stdModel;
}

bool TabbedTableItemListArray::getStandardTableModel() {
    return standardModel;
}

QString TabbedTableItemListArray::getClassAsString() {
    return className;
}

QString TabbedTableItemListArray::getItemString() {
    return itemText;
}

//}

/**
* ActionJList This deals with handling non-default mouse operations on the
* List panel and allows for right click popups and double click to open new
* windows of over the items we are hovering over.
*/
//class ActionJList extends MouseAdapter {

//JPopupMenu popUp;
//JMenuItem menuItem;

//protected BeanTableFrame frame;


ActionJList::ActionJList(int index, BeanTableFrame* f) {
   clickDelay = 500;
   currentItemSelected = index;
   clickTimer = NULL;
   log = new Logger("ActionJList");
   currentWidget = NULL;
    frame = f;
    popUp = new QMenu();
    menuItem = new QAction(tr("Open in New Window"), this);
    popUp->addAction(menuItem);
//    menuItem.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            openNewTableWindow(mouseItem);
//        }
//    });
    LTFrameActionListener* listener = new LTFrameActionListener(index, this);
    connect(menuItem, SIGNAL(triggered(bool)), listener, SLOT(actionPerformed()));
#if 0
    try {
        Object p2 = Toolkit.getDefaultToolkit().getDesktopProperty("awt_multiclick_time");
        if (p2 != NULL) {
            clickDelay = ((Integer) p2).intValue();
        }
    } catch (Exception e2) {
        log->error("Error parsing DesktopProperty awt_multiclick_time to set double click interval ", e2.toString());
    }
    try {
        Object p2 = Toolkit.getDefaultToolkit().getDesktopProperty("awt.multiClickInterval");
        if (p2 != NULL) {
            clickDelay = ((Integer) p2).intValue();
        }
    } catch (Exception e1) {
        log->error("Error parsing DesktopProperty awt.multiClickInterval to set double click interval ", e1.toString());
    }
#endif
    currentItemSelected = 0;
}

void ActionJList::onOpenNewTableWindow()
{
 openNewTableWindow(currentItemSelected);
}
//int clickDelay = 500;
//int currentItemSelected = -1;

/*public*/ void ActionJList::mousePressed(QMouseEvent* e)
{
    //if (e.isPopupTrigger()) {
 if(e->buttons() & Qt::RightButton)
 {
        showPopUp(e);
    }
}

/*public*/ void ActionJList::mouseReleased(QMouseEvent* e) {
    //if (e.isPopupTrigger()) {
 if(e->buttons() & Qt::RightButton)
 {
  showPopUp(e);
 }
}

//javax.swing.Timer clickTimer = NULL;

//Records the item index that the mouse is currenlty over
//int mouseItem;

void ActionJList::showPopUp(QMouseEvent* e) {
    //popUp.show(e.getComponent(), e.getX(), e.getY());
   popUp->exec(QCursor::pos());
    mouseItem = ((ListedTableFrame*)frame)->list->locationToIndex(e->pos()).row();
}

void ActionJList::setCurrentItem(int current) {
    currentItemSelected = current;
}

/*public*/ void ActionJList::mouseClicked(QMouseEvent* e) {

    mouseItem = ((ListedTableFrame*)frame)->list->locationToIndex(e->pos()).row();
    if (popUp->isVisible()) {
        return;
    }
    //if (e.isPopupTrigger()) {
    if(e->buttons() & Qt::RightButton)
    {
        showPopUp(e);
        return;
    }
 #if 0
    if (clickTimer == NULL)
    {
        clickTimer = new Timer(clickDelay, new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent e) {
                selectListItem(mouseItem);
            }
        });
     clickTimer.setRepeats(false);
    }
    if (e.getClickCount() == 1) {
        clickTimer.start();
    } else if (e.getClickCount() == 2) {
        clickTimer.stop();
        openNewTableWindow(mouseItem);
        list.setSelectedIndex(currentItemSelected);
    }
#endif
}

void ActionJList::openNewTableWindow(int index) {
    LTFTabbedTableItem* item = ((ListedTableFrame*)frame)->tabbedTableArray->at(index);
//    class WindowMaker implements Runnable {

//        TabbedTableItem* item;

//        WindowMaker(TabbedTableItem tItem) {
//            item = tItem;
//        }

//        /*public*/ void run() {
            ListedTableAction* tmp = new ListedTableAction(item->getItemString(), item->getClassAsString(), ListedTableFrame::lastdivider, NULL);
            tmp->actionPerformed();
//        }
//    }
//    WindowMaker t = new WindowMaker(item);
//    javax.swing.SwingUtilities.invokeLater(t);
}

void ActionJList::selectListItem(int index) {
    currentItemSelected = index;
    LTFTabbedTableItem* item = ((ListedTableFrame*)frame)->tabbedTableArray->at(index);
    QStackedLayout* cl = (QStackedLayout*) (((ListedTableFrame*)frame)->detailpanel->layout());
    //cl->show(detailpanel, item->getClassAsString());
    cl->setCurrentIndex(currentItemSelected);
//    if(currentWidget != NULL)
//        currentWidget->hide();
//    if(((ListedTableFrame*)frame)->cardHolder->indexOf(item->getPanel()) < 1)
//    {
//     ((ListedTableFrame*)frame)->cardHolder->addWidget(item->getPanel());
//    }
//    else
//    {
//     item->getPanel()->show();
//    }
//    currentWidget= item->getPanel();
    frame->setTitle(item->getItemString());
    frame->generateWindowRef();
    try {
        item->getAAClass()->setFrame(frame);
        ((ListedTableFrame*)frame)->buildMenus(item);
    } catch (Exception ex) {
        log->error(ex.getLocalizedMessage()/*, ex*/);
    }
    ((ListedTableFrame*)frame)->list->ensureIndexIsVisible(index);
    ((ListedTableFrame*)frame)->list->setSelectedIndex(index);
}
//}

void ListedTableFrame::On_listSelection(QModelIndex ix)
{
 int row = ix.row();
 actionList->selectListItem(row);
}

void ListedTableFrame::setWindowSize()
{
 QSize size = pref->getWindowSize(windowFrameRef);
 resize(size);
}
