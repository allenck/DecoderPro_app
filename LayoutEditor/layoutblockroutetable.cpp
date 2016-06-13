#include "layoutblockroutetable.h"
#include "layoutblock.h"
#include <QSplitter>
#include <QSortFilterProxyModel>
#include "jtable.h"
#include "layoutblockneighbourtablemodel.h"
#include "layoutblockroutetablemodel.h"
#include "layoutblockthroughpathstablemodel.h"

//LayoutBlockRouteTable::LayoutBlockRouteTable(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * Provide a table of block route entries
 * as a JmriJPanel
 *
 * @author	Kevin Dickerson   Copyright (C) 2011
 * @version	$Revision: 17977 $
 */
///*public*/ class LayoutBlockRouteTable extends jmri.util.swing.JmriPanel {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");


/*public*/ LayoutBlockRouteTable::LayoutBlockRouteTable(bool editable, LayoutBlock* block,QWidget *parent) :
        QWidget(parent)
{
 //super();

 //This could do with being presented in a JSplit Panel

 dataModel = new LayoutBlockRouteTableModel(editable, block);
 sorter = new QSortFilterProxyModel();
 sorter->setSourceModel(dataModel);
 dataTable = new JTable(sorter);
//    sorter.setTableHeader(dataTable.getTableHeader());
//    dataScroll	= new JScrollPane(dataTable, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

 neighbourDataModel = new LayoutBlockNeighbourTableModel(editable, block);
 neighbourSorter = new QSortFilterProxyModel(neighbourDataModel);
 neighbourSorter->setSourceModel(neighbourDataModel);
 neighbourDataTable = new JTable(neighbourSorter);
 //neighbourSorter.setTableHeader(neighbourDataTable.getTableHeader());
 //neighbourDataScroll	= new JScrollPane(neighbourDataTable, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

 throughPathsDataModel = new LayoutBlockThroughPathsTableModel(editable, block);
 throughPathsSorter = new QSortFilterProxyModel(throughPathsDataModel);
 throughPathsSorter->setSourceModel(throughPathsDataModel);
 throughPathsDataTable = new JTable(throughPathsSorter);
 //throughPathsSorter->setTableHeader(throughPathsDataTable.getTableHeader());
 //throughPathsDataScroll	= new JScrollPane(throughPathsDataTable, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

 // set initial sort
 QSortFilterProxyModel* tmodel = ((QSortFilterProxyModel*)dataTable->getModel());
// tmodel.setSortingStatus(LayoutBlockRouteTableModel.HOPCOUNTCOL, TableSorter.ASCENDING);
 tmodel->sort(LayoutBlockRouteTableModel::HOPCOUNTCOL,Qt::AscendingOrder);

 QSortFilterProxyModel* ntmodel = ((QSortFilterProxyModel*)neighbourDataTable->getModel());
 ntmodel->sort(LayoutBlockNeighbourTableModel::NEIGHBOURCOL, Qt::AscendingOrder);

 QSortFilterProxyModel* nptmodel = ((QSortFilterProxyModel*)throughPathsDataTable->getModel());
 nptmodel->sort(LayoutBlockThroughPathsTableModel::SOURCECOL, Qt::AscendingOrder);

 // allow reordering of the columns
 //dataTable.getTableHeader().setReorderingAllowed(true);
 //neighbourDataTable.getTableHeader().setReorderingAllowed(true);
 //throughPathsDataTable.getTableHeader().setReorderingAllowed(true);

 // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
// dataTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
// neighbourDataTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
 //throughPathsDataTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
 // resize columns as requested
 for (int i=0; i<dataTable->model()->columnCount(); i++)
 {
  int width = dataModel->getPreferredWidth(i);
  //dataTable->getColumnModel().getColumn(i).setPreferredWidth(width);
  dataTable->setColumnWidth(i, width);
 }
 dataTable->resizeColumnsToContents();

 // general GUI config
 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout(this/*, BoxLayout.Y_AXIS*/));

 // install items in GUI


  // set Viewport preferred size from size of table
 QSize dataTableSize = dataTable->sizeHint();
 // width is right, but if table is empty, it's not high
 // enough to reserve much space.
 dataTableSize.setHeight(qMax(dataTableSize.height(), 400));
 dataTableSize.setWidth(qMax(dataTableSize.width(), 400));
 //dataScroll.getViewport().setPreferredSize(dataTableSize);

 // set preferred scrolling options
 //        dataScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
 //        dataScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);

 // set to single selection
         dataTable->setSelectionMode(QAbstractItemView::SingleSelection);

        // resize columns as requested
 for (int i=0; i<neighbourDataTable->model()->columnCount(); i++)
 {
  int width = neighbourDataModel->getPreferredWidth(i);
  // neighbourDataTable->getColumnModel().getColumn(i).setPreferredWidth(width);
   neighbourDataTable->setColumnWidth(i, width);
 }
 neighbourDataTable->resizeColumnsToContents();

 // general GUI config
 //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

 // install items in GUI


 // set Viewport preferred size from size of table
 QSize neighbourDataTableSize = neighbourDataTable->sizeHint();
 // width is right, but if table is empty, it's not high
 // enough to reserve much space.
 neighbourDataTableSize.setHeight( qMax(neighbourDataTableSize.height(), 400));
 neighbourDataTableSize.setWidth(qMax(neighbourDataTableSize.width(), 400));
 //neighbourDataScroll.getViewport().setPreferredSize(neighbourDataTableSize);

 // set preferred scrolling options
// neighbourDataScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
// neighbourDataScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);

 // set to single selection
// neighbourDataTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);


 for (int i=0; i<neighbourDataTable->model()->columnCount(); i++)
 {
  int width = neighbourDataModel->getPreferredWidth(i);
  //neighbourDataTable->getColumnModel().getColumn(i).setPreferredWidth(width);
  neighbourDataTable->setColumnWidth(i,width);
 }
 neighbourDataTable->resizeColumnsToContents();


 // set Viewport preferred size from size of table
 QSize throughPathsDataTableSize = throughPathsDataTable->sizeHint();
 // width is right, but if table is empty, it's not high
 // enough to reserve much space.
 throughPathsDataTableSize.setHeight(qMax(throughPathsDataTableSize.height(), 400));
 throughPathsDataTableSize.setWidth(qMax(throughPathsDataTableSize.width(), 400));
 //throughPathsDataScroll.getViewport().setPreferredSize(throughPathsDataTableSize);

 // set preferred scrolling options
// throughPathsDataScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
// throughPathsDataScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);

 // set to single selection
 throughPathsDataTable->setSelectionMode(QAbstractItemView::SingleSelection);



 QWidget* neigh = new QWidget();
 neigh->setLayout(new QVBoxLayout);//(neigh/*, BoxLayout.Y_AXIS*/));
 neigh->layout()->addWidget(new JLabel(tr("Neighbouring Blocks")));
 neigh->layout()->addWidget(/*neighbourDataScroll*/neighbourDataTable);

 QWidget* through = new QWidget();
 through->setLayout(new QVBoxLayout(through/*, BoxLayout.Y_AXIS*/));
 through->layout()->addWidget(new JLabel(tr("Valid Paths Through This Block")));
 through->layout()->addWidget(/*throughPathsDataScroll*/throughPathsDataTable);

 QWidget* routePane = new QWidget();
 routePane->setLayout(new QVBoxLayout);//(routePane, BoxLayout.Y_AXIS));
 routePane->layout()->addWidget(new JLabel(tr("Accessible Blocks")));
 routePane->layout()->addWidget(/*dataScroll*/dataTable);

 QSplitter* splitTopPane = new QSplitter();
 //JSplitPane.VERTICAL_SPLIT,
 //          neigh, through);
 splitTopPane->setOrientation(Qt::Vertical);
 splitTopPane->addWidget(neigh);
 splitTopPane->addWidget(through);
 //splitTopPane.setOneTouchExpandable(true);
 //splitTopPane->setDividerLocation(150);
 QSplitter* splitBotPane = new QSplitter();
// (JSplitPane.VERTICAL_SPLIT,
//           splitTopPane, routePane);
 splitBotPane->setOrientation(Qt::Vertical);
 splitBotPane->addWidget(splitTopPane);
 splitBotPane->addWidget(routePane);
 //splitBotPane.setOneTouchExpandable(true);
 //splitBotPane.setDividerLocation(300);

 thisLayout->addWidget(splitBotPane);

}

/*public*/ JTable* LayoutBlockRouteTable::getTable() { return dataTable; }
/*public*/ QSortFilterProxyModel* LayoutBlockRouteTable::getModel() { return sorter; }

/*public*/ JTable* LayoutBlockRouteTable::getNeighbourTable() { return neighbourDataTable; }
/*public*/ QSortFilterProxyModel* LayoutBlockRouteTable::getNeighbourModel() { return neighbourSorter; }

/*public*/ void LayoutBlockRouteTable::dispose() {
    if (dataModel != NULL)
        dataModel->dispose();
    dataModel = NULL;
    dataTable = NULL;
    //dataScroll = NULL;
    neighbourDataModel = NULL;
    neighbourSorter = NULL;
    neighbourDataTable = NULL;
    //neighbourDataScroll = NULL;

    //super.dispose();
    close();
}
