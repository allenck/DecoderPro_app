#include "rostergrouptableframe.h"
#include "rostergrouptablemodel.h"
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QBoxLayout>
#include <QGroupBox>
#include <QMenuBar>
#include <QTimer>

//RosterGroupTableFrame::RosterGroupTableFrame()
//{
//}
int RosterGroupTableFrame::bottomStrutWidth = 20;
int RosterGroupTableFrame::topStrutWidth = 20;
/**
 * Provide a JFrame to display the Roster Data Based upon BeanTableFrame.
 * <P>
 * This frame includes the table itself at the top, plus a "bottom area" for
 * things like an Add... button and checkboxes that control display options.
 * <p>
 * The usual menus are also provided here.
 * <p>
 * Specific uses are customized via the RosterGroupTableDataModel implementation
 * they provide, and by providing a {@link #extras} implementation that can in
 * turn invoke {@link #addToBottomBox} as needed.
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 * @author	Kevin Dickerson Copyright (C) 2009
 * @version	$Revision: 28746 $
 */
///*public*/ class RosterGroupTableFrame extends jmri.util.JmriJFrame {

/**
 *
 */
//private static final long serialVersionUID = 81131762773750394L;

//ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");

/*public*/ RosterGroupTableFrame::RosterGroupTableFrame(RosterGroupTableModel* model, QString helpTarget, QWidget* parent)
 : JmriJFrame(parent)
{
 //super();
 dataModel = model;

 //dataTable = JTableUtil.sortableDataModel(dataModel);
 dataTable = new QTableView();
 QSortFilterProxyModel* sortModel = new QSortFilterProxyModel();
 sortModel->setSourceModel(dataModel);
 //dataScroll = new JScrollPane(dataTable);
 dataTable->setModel(sortModel);

 // give system name column as smarter sorter and use it initially
// try {
//     TableSorter tmodel = ((TableSorter) dataTable.getModel());
//     tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//     tmodel.setSortingStatus(RosterGroupTableModel.IDCOL, TableSorter.ASCENDING);
// } catch (java.lang.ClassCastException e) {
// }  // happens if not sortable table

 // configure items for GUI
 dataModel->configureTable(dataTable);

 // general GUI config
 //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget;
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
 centralWidget->setLayout(centralWidgetLayout);
 setCentralWidget(centralWidget);

 // add save menu item
 QMenuBar* menuBar = new QMenuBar();

 setMenuBar(menuBar);

 addHelpMenu(helpTarget, true);

 // install items in GUI
// topBox = Box.createHorizontalBox();
// topBox.add(Box.createHorizontalGlue());	// stays at beginning of box
 topBox = new QGroupBox();
 topBox->setLayout(new QVBoxLayout);
 topBoxIndex = 0;
 centralWidgetLayout->addWidget(topBox);
 centralWidgetLayout->addWidget(/*dataScroll*/dataTable);

// bottomBox = Box.createHorizontalBox();
// bottomBox.add(Box.createHorizontalGlue());	// stays at end of box
 bottomBox = new QGroupBox();
 bottomBox->setLayout(new QVBoxLayout);
 bottomBoxIndex = 0;

 centralWidgetLayout->addWidget(bottomBox);

 // add extras, if desired by subclass
 QTimer::singleShot(10,this, SLOT(extras()));

 // set Viewport preferred size from size of table
 QSize dataTableSize = dataTable->sizeHint();
 // width is right, but if table is empty, it's not high
 // enough to reserve much space.
 //dataTableSize.height = Math.max(dataTableSize.height, 400);
 dataTable->setMinimumHeight(qMax(dataTableSize.height(),400));
 //dataScroll.getViewport().setPreferredSize(dataTableSize);

 // set preferred scrolling options
 /*dataScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
 dataScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);*/

}

/**
 * Hook to allow sub-types to install more items in GUI
 */
void RosterGroupTableFrame::extras()
{
}

/*protected*/ QGroupBox* RosterGroupTableFrame::getBottomBox() {
    return bottomBox;
}

/**
 * Add a component to the bottom box. Takes care of organising glue, struts
 * etc
 *
 * @param comp
 */
/*protected*/ void RosterGroupTableFrame::addToBottomBox(QWidget* comp)
{
 QVBoxLayout* bottomBoxLayout = (QVBoxLayout*)bottomBox->layout();
//    bottomBox.add(Box.createHorizontalStrut(bottomStrutWidth), bottomBoxIndex);
    ++bottomBoxIndex;
    bottomBoxLayout->insertWidget( bottomBoxIndex, comp);
    ++bottomBoxIndex;
}

/*protected*/ QGroupBox* RosterGroupTableFrame::getTopBox() {
    return topBox;
}

/**
 * Add a component to the bottom box. Takes care of organising glue, struts
 * etc
 *
 * @param comp
 */
/*protected*/ void RosterGroupTableFrame::addToTopBox(QWidget* comp)
{
 QVBoxLayout* l = (QVBoxLayout*)topBox->layout();
//    topBox(topStrutWidth), topBoxIndex);
//    ++topBoxIndex;
    l->insertWidget(topBoxIndex,comp);
    ++topBoxIndex;
}

/*public*/ void RosterGroupTableFrame::dispose() {
    if (dataModel != NULL) {
        dataModel->dispose();
    }
    dataModel = NULL;
    dataTable = NULL;
    //dataScroll = NULL;
    JmriJFrame::dispose();
}
/*public*/ QString RosterGroupTableFrame::getClassName()
{
 return "jmri.jmrit.roster.swing.rostergroup.RosterGroupTableFrame";
}
