#include "automattableframe.h"
#include "automattabledatamodel.h"
#include <QSortFilterProxyModel>
#include <QBoxLayout>
#include "jtable.h"

/**
 * Frame providing a table of Automat instances
 *
 * @author	Bob Jacobsen Copyright (C) 2004
 * @version	$Revision: 28746 $
 */
///*public*/ class AutomatTableFrame extends jmri.util.JmriJFrame {

/**
 *
 */
//private static final long serialVersionUID = -6052436715378143786L;

//static ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.automat.monitor.AutomatTableBundle");

/*public*/ AutomatTableFrame::AutomatTableFrame(AutomatTableDataModel* model, QWidget *parent) :
    JmriJFrame(parent)
{

 //super();
 setFrameRef(getClassName());
 dataModel = model;

 //dataTable = JTableUtil.sortableDataModel(dataModel);
 QSortFilterProxyModel* sorter = new QSortFilterProxyModel();
 sorter->setSourceModel(model);
 dataTable = new JTable(sorter);
 //dataScroll = new JScrollPane(dataTable);

 // configure items for GUI
 dataModel->configureTable(dataTable);

 // general GUI config
 //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget  = new QWidget;
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
 setCentralWidget(centralWidget);

 // install items in GUI
 QWidget* pane1 = new QWidget();
 //getContentPane().add(dataScroll);
 centralWidgetLayout->addWidget(dataTable);
 pack();
 pane1->setMaximumSize(pane1->size());

 setTitle(tr("Automat Table"));

 addHelpMenu("package.jmri.jmrit.automat.monitor.AutomatTableFrame", true);

 pack();
}

/*public*/ void AutomatTableFrame::dispose() {
    dataModel->dispose();
    dataModel = NULL;
    dataTable = NULL;
   // dataScroll = null;
    JmriJFrame::dispose();
}

/*public*/ QString AutomatTableFrame::getClassName()
{
 return "jmri.jmrit.operation.automation.AutomatTableFrame";
}
