#include "editorfilepane.h"
#include "spjfile.h"
#include "editortabledatamodel.h"
#include <QBoxLayout>
#include <QSortFilterProxyModel>
#include <QTableView>
#include "jseparator.h"
#include <QLabel>
#include "jtextfield.h"
#include "file.h"
#include "jmripanel.h"

//EditorFilePane::EditorFilePane(QWidget *parent) :
//  QWidget(parent)
//{
//}
/**
 * Pane for editing Digitrax SPJ files
 *
 * @author	Bob Jacobsen Copyright (C) 2006, 2010
 * @version	$Revision: 28746 $
 */
///*public*/ class EditorFilePane extends javax.swing.JPanel {

/**
 *
 */
//private static final long serialVersionUID = -4194558549451699808L;

// GUI member declarations
//static ResourceBundle res = ResourceBundle.getBundle("jmri.jmrix.loconet.soundloader.Editor");

/*public*/ EditorFilePane::EditorFilePane(File name, QWidget *parent) :
  QWidget(parent)
{
 // open and save file
//    try {
 file = new SpjFile(new File(name.getPath()));
 file->read();
//    } catch (IOException e) {
//        log.error("Exception reading file: " + e);
//        e.printStackTrace();
//        return;
//    }

 // start to configure GUI
 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

 // create and include table
 dataModel = new EditorTableDataModel(file);

 QSortFilterProxyModel* sorter =  new QSortFilterProxyModel();
 sorter->setSourceModel(dataModel);
 QTableView* dataTable = /*JTableUtil.sortableDataModel(dataModel);*/ new QTableView;
 //JScrollPane dataScroll = new JScrollPane(dataTable);
 dataTable->setModel(sorter);
 // give system name column a smarter sorter and use it initially
// try {
//     TableSorter tmodel = ((TableSorter) dataTable.getModel());
//     tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//     tmodel.setSortingStatus(EditorTableDataModel.HEADERCOL, TableSorter.ASCENDING);
// } catch (java.lang.ClassCastException e) {
// }  // happens if not sortable table

 // configure items for GUI
 dataModel->configureTable(dataTable);

 //add(dataScroll);
 thisLayout->addWidget(dataTable);

 // some stuff at bottom for now
 thisLayout->addWidget(new JSeparator());
// JPanel bottom = new JPanel();
// bottom.setLayout(new BoxLayout(bottom, BoxLayout.Y_AXIS));
 QVBoxLayout* bottomLayout = new QVBoxLayout;

 //JPanel p1 = new JPanel();
 QHBoxLayout* p1Layout = new QHBoxLayout;
 p1Layout->addWidget(new QLabel(tr("Project Size (bytes)")));
 JTextField* t1 = new JTextField(12);
 t1->setReadOnly(false);
 t1->setText(QString::number(name.length()));
 p1Layout->addWidget(t1);

 bottomLayout->addLayout(p1Layout);
 thisLayout->addLayout(bottomLayout);
}

/*public*/ void EditorFilePane::saveFile(QString name) /*throws java.io.IOException*/ {
    file->save(name);
}

/**
 * Get rid of any held resources
 */
void EditorFilePane::dispose() {
    file->dispose();
    file = NULL;  // not for GC, this flags need to reinit
}

