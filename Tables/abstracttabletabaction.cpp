#include "abstracttabletabaction.h"
#include "jtable.h"
//#include "abstractproxymanager.h"
#include <QBoxLayout>
#include "connectionnamefromsystemname.h"
#include "QTabWidget"
#include "exceptions.h"
#include "beantabledatamodel.h"
#include <QSortFilterProxyModel>
#include <QFrame>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include "savemenu.h"
#include "mysortfilterproxymodel.h"
#include "userpreferencesmanager.h"
#include "instancemanager.h"
#include "proxymanager.h"
#include "proxylightmanager.h"

//AbstractTableTabAction::AbstractTableTabAction(QObject *parent) :
//    AbstractTableAction(parent)
//{
//}
//abstract /*public*/ class AbstractTableTabAction extends AbstractTableAction {

/**
 *
 */
//private static final long serialVersionUID = -7423371299023131468L;

// /*public*/ static final ResourceBundle rbean = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");


/*public*/ AbstractTableTabAction::AbstractTableTabAction(QString s, QObject *parent)
    : AbstractTableAction(s, parent)
{
 //super(s);
 init = false;
 tabbedTableArray =  QList<TabbedTableItem*>();
 log = new Logger("AbstractTableTabAction");
 currTab = 0;
}

AbstractTableTabAction::~AbstractTableTabAction()
{
 dispose();
}

/*protected*/ void AbstractTableTabAction::createModel()
{
 dataPanel = new QWidget();
 dataPanel->setMinimumSize(300, 300);
 dataPanel->resize(825, 300);

 dataTabs = new QTabWidget();
 dataTabs->setMinimumSize(400,300);
 dataTabs->resize(800,600);


 QGridLayout* dataPanelLayout;
 dataPanel->setLayout(dataPanelLayout = new QGridLayout());
 //if (getManager() instanceof jmri.managers.AbstractProxyManager)
 if(qobject_cast<ProxyManager*>(getManager())!= nullptr)
 {
  ProxyManager* proxy = qobject_cast<ProxyManager*>(getManager());
  QList<Manager*> managerList = proxy->getDisplayOrderManagerList();
  AbstractTableAction* a = getNewTableAction("All");
  Q_UNUSED(a);
  tabbedTableArray.append(new TabbedTableItem("All", true, getManager(), getNewTableAction("All")));
  for(Manager* manager : managerList)
  {
   QString manuName = manager->getMemo()->getUserName();
   TabbedTableItem* itemModel = new TabbedTableItem(manuName, true, manager, getNewTableAction(manuName));
   tabbedTableArray.append(itemModel);
  }
 }
 else
 {
  QString manuName = ConnectionNameFromSystemName::getConnectionName(getManager()->getSystemPrefix());
 tabbedTableArray.append(new TabbedTableItem(manuName, true, getManager(), getNewTableAction(manuName)));
 }
 for(int x = 0; x<tabbedTableArray.size(); x++)
 {
  AbstractTableAction* table = tabbedTableArray.at(x)->getAAClass();
  table->addToPanel(this);
  //dataTabs->addTab(tabbedTableArray.at(x).getItemString(),NULL, tabbedTableArray.at(x).getPanel(),NULL);
  dataTabs->addTab(tabbedTableArray.at(x)->getPanel(), tabbedTableArray.at(x)->getItemString());
 }
// dataTabs.addChangeListener(new ChangeListener() {
//        /*public*/ void stateChanged(ChangeEvent evt) {
//            setMenuBar(f);
//        }
//    });
 dataPanelLayout->addWidget(dataTabs,0,0); //,/* BorderLayout.CENTER*/0, Qt::AlignCenter);
 init = true;
// if(!getTableClass().isEmpty())
// currTab = ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->getProperty(getClassName()+"." + getTableClass(),"currTab").toInt();
// dataTabs->setCurrentIndex(currTab);
 connect(dataTabs, SIGNAL(currentChanged(int)), this, SLOT(On_dataTabs_currentChanged(int)));
}

void AbstractTableTabAction::On_dataTabs_currentChanged(int iTab)
{
 //table = tabbedTableArray.at(iTab)->dataTable;
 tabbedTableArray.at(currTab)->bottomBox->setVisible(false);
 tabbedTableArray.at(iTab)->bottomBox->setVisible(true);
 currTab = iTab;
 setMenuBar(f);
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setProperty(getClassName()+"."+getTableClass(),"currTab",currTab);
}

/*abstract*/ /*protected*/ Manager* AbstractTableTabAction::getManager() {return nullptr;}

/*abstract*/ /*protected*/ AbstractTableAction* AbstractTableTabAction::getNewTableAction(QString /*choice*/) {return nullptr;}

//@Override
/*public*/ QWidget* AbstractTableTabAction::getPanel()
{
 if (!init)
  createModel();
 return dataPanel;
}


/*protected*/ void AbstractTableTabAction::setTitle() {
    //atf.setTitle("multiple sensors");
}

/*abstract*/ /*protected*/ QString AbstractTableTabAction::helpTarget() {return "";}

/*protected*/ void AbstractTableTabAction::addPressed(ActionEvent* /*e*/) {
    log->warn("This should not have happened");
}

void AbstractTableTabAction::actionPerformed(JActionEvent */*e*/)
{
 if(currFrame() != nullptr)
 {
  currFrame()->setVisible(true);
  return;
 }
 createModel();
 f = new ATABeanTableFrame(this);
 setCurrFrame(f);
 buildMenus(f);
 setMenuBar(f);
 //f->addHelpMenu(helpTarget(),true);
 QWidget* centralWidget = new QWidget;
 centralWidgetLayout = new QVBoxLayout;
 centralWidget->setLayout(centralWidgetLayout);
 f->setCentralWidget(centralWidget);
 centralWidgetLayout->addWidget(dataTabs);
 for(int i=0; i < tabbedTableArray.size(); i++)
 {
  centralWidgetLayout->addWidget(tabbedTableArray.at(i)->bottomBox);
  tabbedTableArray.at(i)->bottomBox->setVisible(i == currTab);
 }
 currTab = 0;
 f->pack();
 f->setVisible(true);
}

/*public*/ void AbstractTableTabAction::addToFrame(BeanTableFrame* f)
{
 try
 {
  tabbedTableArray.at(dataTabs->currentIndex())->getAAClass()->addToFrame(f);
 }
 catch (ArrayIndexOutOfBoundsException ex)
 {
  log->error(ex.getMessage() + " in add to Frame "  + QString::number(dataTabs->currentIndex()) + " " + QString::number(dataTabs->currentIndex()));
 }
}

/*public*/ void AbstractTableTabAction::setMenuBar(BeanTableFrame* f)
{
 try
 {
  tabbedTableArray.at(dataTabs->currentIndex())->getAAClass()->setMenuBar(f);
 }
 catch (ArrayIndexOutOfBoundsException ex)
 {
  log->error(ex.getMessage()  + " in add to Menu " + QString::number(dataTabs->currentIndex()) + " " + QString::number(dataTabs->currentIndex()));
 }
}

/*public*/ void AbstractTableTabAction::addToBottomBox(QWidget* c, QString str)
{
 for(int x = 0; x<tabbedTableArray.size(); x++)
 {
  if (tabbedTableArray.at(x)->getItemString()==(str))
   tabbedTableArray.at(x)->addToBottomBox(c);
 }
}

/*public*/ void AbstractTableTabAction::print(JTable::PrintMode mode, QString headerFormat, QString footerFormat)
{

 try
 {
  tabbedTableArray.at(dataTabs->currentIndex())->getDataTable()->print(mode, headerFormat, footerFormat);
 }
 catch (PrinterException e1)
 {
  log->warn("error printing: "+e1.getMessage() + e1.getMessage());
 }
 catch ( NullPointerException ex)
 {
  log->error("Trying to print returned a NPE error");
 }
}

/*public*/ void AbstractTableTabAction::dispose()
{
 for(int x=0; x<tabbedTableArray.size(); x++)
 {
  tabbedTableArray.at(x)->dispose();
 }
 AbstractTableAction::dispose();
}

/*static*/ /*final*/ int TabbedTableItem::bottomStrutWidth = 20;


/*public*/ TabbedTableItem::TabbedTableItem(QString choice, bool stdModel, Manager* manager, AbstractTableAction* tableAction)
{
 AddToFrameRan = false;
 standardModel = true;
 dataPanel = new QWidget();
 dataPanel->resize(600,300);

 this->tableAction = tableAction;
 itemText = choice;
 standardModel=stdModel;
 this->manager = manager;

 //If a panel model is used, it should really add to the bottom box
 //but it can be done this way if required.
 bottomBox = /*Box.createHorizontalBox();*/ new QFrame();
 bottomBox->setObjectName("bottomBox");
 //bottomBox.add(Box.createHorizontalGlue());
 bottomBoxIndex = 0;

// if(dataPanel->layout() != NULL)
//  dataPanelLayout = (QVBoxLayout*)dataPanel->layout();
// else
  dataPanel->setLayout(dataPanelLayout = new QGridLayout);
 if (stdModel)
  createDataModel();
 else
  addPanelModel();
}

void TabbedTableItem::createDataModel()
{
 if (manager!=nullptr)
  tableAction->setManager(manager);
 dataModel = (BeanTableDataModel*)tableAction->getTableDataModel();
 //        dataModel->updateNameList();
//        TableSorter sorter = new TableSorter(dataModel);
 MySortFilterProxyModel* sorter = new MySortFilterProxyModel();
 sorter->setSourceModel(dataModel);
 dataTable = dataModel->makeJTable(dataModel->getMasterClassName() + ":" + getItemString(), dataModel, sorter);

 tableAction->table = dataTable;
 //sorter->setSourceModel(dataModel);
 dataTable->setSortingEnabled(true);
 //sorter.setTableHeader(dataTable.getTableHeader());
 //dataScroll	= new JScrollPane(dataTable);
 dataTable->resizeRowsToContents();

//        try {
//            TableSorter tmodel = ((TableSorter)dataTable.getModel());
//            tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//            tmodel.setSortingStatus(BeanTableDataModel.SYSNAMECOL, TableSorter.ASCENDING);
//        } catch (java.lang.ClassCastException e) {}  // happens if not sortable table

 dataModel->configureTable(dataTable);
 //dataModel->loadTableColumnDetails(dataTable, dataModel->getMasterClassName()+":"+getItemString());
 dataModel->persistTable(dataTable);
 //dataModel->setPersistentButtons();


 QSize dataTableSize = dataTable->sizeHint();
 // width is right, but if table is empty, it's not high
 // enough to reserve much space.
 dataTableSize.setHeight(qMax(dataTableSize.height(), 400));
 //dataScroll.getViewport().setPreferredSize(dataTableSize);

 // set preferred scrolling options
 // dataScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
 //dataScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

 //dataPanel.setLayout(new BoxLayout(dataPanel, BoxLayout.Y_AXIS));
 dataPanel->resize(600,290);
 //QGridLayout* dataPanelLayout;
// if(dataPanel->layout() != NULL)
//  dataPanelLayout = (QGridLayout*)dataPanel->layout();
// else
  //dataPanel->setLayout(dataPanelLayout= new QGridLayout);
 //dataPanel.add(dataScroll, BorderLayout.CENTER);
 dataPanelLayout->addWidget(dataTable,0,0); //, 0, Qt::AlignCenter);

 dataPanelLayout->addWidget(bottomBox,1,0); //, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);
 if(tableAction->includeAddButton())
 {
  QPushButton* addButton = new QPushButton(tr("Add"));
  addToBottomBox(addButton);
//            addButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    tableAction.addPressed(e);
//                }
//            });
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(addButton->sizePolicy().hasHeightForWidth());
  addButton->setSizePolicy(sizePolicy);
  connect(addButton, SIGNAL(clicked()), tableAction, SLOT(addPressed()));
 }
}

void TabbedTableItem::addPanelModel()
{
 ((QGridLayout*)dataPanel->layout())->addWidget(tableAction->getPanel(),0,0); //, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
 ((QGridLayout*)dataPanel->layout())->addWidget(bottomBox,1,0); //, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);
}

/*public*/ bool TabbedTableItem::getStandardTableModel(){ return standardModel; }

/*public*/ QString TabbedTableItem::getItemString()
{
 return itemText;
}

/*public*/ AbstractTableAction* TabbedTableItem::getAAClass(){
    return tableAction;
}

/*public*/ QWidget* TabbedTableItem::getPanel() {
    return dataPanel;
}

/*public*/ bool TabbedTableItem::getAdditionsToFrameDone() { return AddToFrameRan; }

/*public*/ void TabbedTableItem::setAddToFrameRan() { AddToFrameRan=true; }

/*public*/ JTable* TabbedTableItem::getDataTable(){
    return dataTable;
}

/*protected*/ void TabbedTableItem::addToBottomBox(QWidget* comp)
{
 QHBoxLayout* bottomBoxLayout;
 if(bottomBox->layout() == nullptr)
 {
  bottomBox->setLayout(bottomBoxLayout = new QHBoxLayout);
 }
 else
  bottomBoxLayout = (QHBoxLayout*)bottomBox->layout();
 try
 {
  bottomBoxLayout->addStrut(bottomStrutWidth);
  ++bottomBoxIndex;
  bottomBoxLayout->insertWidget(bottomBoxIndex, comp);
  ++bottomBoxIndex;
 }
 catch (IllegalArgumentException ex)
 {
  // log.error (ex.getLocalizedMessage(), ex);
 }
}

/*protected*/ void TabbedTableItem::dispose()
{
 if (dataModel != nullptr)
 {
//  dataModel->saveTableColumnDetails(dataTable, dataModel->getMasterClassName()+":"+getItemString());
  dataModel->stopPersistingTable(dataTable);
  dataModel->dispose();
 }
 dataModel = nullptr;
 dataTable = nullptr;
 //dataScroll = NULL;
}

/*public*/ BeanTableFrame* AbstractTableTabAction::currFrame() {}
/*public*/ void AbstractTableTabAction::setCurrFrame(BeanTableFrame* /*frame*/) {}

/* based on code copied from ListedTableFrame */

void AbstractTableTabAction::buildMenus(BeanTableFrame* f)
{
 TabbedTableItem* item = tabbedTableArray.at(dataTabs->currentIndex());

 QMenuBar* menuBar = f->menuBar();
 QMenu* fileMenu = new QMenu(tr("File"));
 menuBar->addMenu(fileMenu);

// QAction* newItem = new QAction("New Window", this);
// fileMenu->addAction(newItem);
//    newItem.addActionListener(new ActionListener() {
//        public void actionPerformed(ActionEvent e) {
//            actionList.openNewTableWindow(list.getSelectedIndex());
//        }
//    });

 fileMenu->addMenu(new SaveMenu());

 QAction* printItem = new QAction(tr("Print Table"), this );
 fileMenu->addAction(printItem);
//    printItem.addActionListener(new ActionListener() {
//        public void actionPerformed(ActionEvent e) {
//            try {
//                // MessageFormat headerFormat = new MessageFormat(getTitle());  // not used below
//                MessageFormat footerFormat = new MessageFormat(getTitle() + " page {0,number}");
//                if (item.getStandardTableModel()) {
//                    item.getDataTable().print(JTable.PrintMode.FIT_WIDTH, NULL, footerFormat);
//                } else {
//                    item.getAAClass().print(JTable.PrintMode.FIT_WIDTH, NULL, footerFormat);
//                }
//            } catch (java.awt.print.PrinterException e1) {
//                log.warn("error printing: " + e1, e1);
//            } catch (NullPointerException ex) {
//                log.error("Trying to print returned a NPE error");
//            }
//        }
//    });
 connect(printItem, SIGNAL(triggered()), this, SLOT(On_printAction_triggered()));
 QMenu* viewMenu = new QMenu("View");
 menuBar->addMenu(viewMenu);
// for (int i = 0; i < TabbedTableItemListArrayArray.size(); i++) {
//     final TabbedTableItemListArray itemList = TabbedTableItemListArrayArray.get(i);
//     JMenuItem viewItem = new JMenuItem(itemList.getItemString());
//     viewMenu.add(viewItem);
//     viewItem.addActionListener(new ActionListener() {
//         public void actionPerformed(ActionEvent e) {
//             gotoListItem(itemList.getClassAsString());
//         }
//     });
// }

 //f->setMenuBar(menuBar);
 try
 {
  item->getAAClass()->setMenuBar(f);
  f->addHelpMenu(item->getAAClass()->helpTarget(), true);
 }
 catch (Exception ex)
 {
  log->error("Error when trying to set menu bar for " + /*item->getClassAsString()*/ QString(item->metaObject()->className())+ "\n" + ex.getMessage());
 }
// this.revalidate();
}

void AbstractTableTabAction::On_printAction_triggered()
{
 TabbedTableItem* item = tabbedTableArray.at(dataTabs->currentIndex());
 try
 {
  // MessageFormat headerFormat = new MessageFormat(getTitle());  // not used below
  //MessageFormat footerFormat = new MessageFormat(getTitle() + " page {0,number}");
  QString footerFormat = QString(f->getTitle() + " page %1");
  if (item->getStandardTableModel())
  {
   item->getDataTable()->print(JTable::FIT_WIDTH, nullptr, footerFormat);
  }
  else
  {
   item->getAAClass()->print(JTable::FIT_WIDTH, nullptr, footerFormat);
  }
 } catch (PrinterException e1)
 {
  log->warn("error printing: " + e1.getMessage());
 }
 catch (NullPointerException ex)
 {
  log->error("Trying to print returned a NPE error");
 }
}
