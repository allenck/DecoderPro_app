#include "audiotablepanel.h"
#include <QAction>
#include "jtable.h"
#include "xtablecolumnmodel.h"
#include "audiotableaction.h"
#include <QBoxLayout>
#include <QTabWidget>
#include <QGroupBox>
#include "flowlayout.h"
#include <QTableView>
#include "tablerowsorter.h"
#include "rowsorterutil.h"
#include "systemnamecomparator.h"

//AudioTablePanel::AudioTablePanel(QWidget *parent) :
//  QWidget(parent)
//{
//}
/**
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 * @author Matthew Harris copyright (c) 2009
 * @version $Revision: 28746 $
 */
// /*public*/ class AudioTablePanel extends JPanel {

/**
 *
 */
// /*private*/ static /*final*/ long serialVersionUID = 3379930683020715564L;

/*static*/ /*final*/ int AudioTablePanel::bottomStrutWidth = 20;

// /*private*/ static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");
// /*private*/ static final ResourceBundle rba = ResourceBundle.getBundle("jmri.jmrit.audio.swing.AudioTableBundle");

//@SuppressWarnings("OverridableMethodCallInConstructor")
/*public*/ AudioTablePanel::AudioTablePanel(
  AudioTableDataModel* listenerModel,
  AudioTableDataModel* bufferModel,
  AudioTableDataModel* sourceModel,
  QString helpTarget, QWidget *parent) :
  QWidget(parent)
{
 //super();
 this->helpTarget = helpTarget;
 listenerDataModel = listenerModel;
 //listenerDataTable = JTableUtil.sortableDataModel(listenerDataModel);
 //listenerDataTable = new JTable(listenerDataModel);
 TableRowSorter* sorter = new TableRowSorter(listenerDataModel);
 sorter->setComparator(AudioTableDataModel::SYSNAMECOL, new SystemNameComparator() );
 RowSorterUtil::setSortOrder(sorter, AudioTableDataModel::SYSNAMECOL, ASCENDING);
 listenerDataTable = listenerDataModel->makeJTable(listenerDataModel->getMasterClassName(), listenerDataModel, sorter);
 //listenerDataScroll = new JScrollPane(listenerDataTable);
 listenerDataTable->setColumnModel(new XTableColumnModel(listenerDataTable));
 listenerDataTable->createDefaultColumnsFromModel();

 bufferDataModel = bufferModel;
 //bufferDataTable = JTableUtil.sortableDataModel(bufferDataModel);
 sorter = new TableRowSorter(bufferDataModel);
 sorter->setComparator(AudioTableDataModel::SYSNAMECOL, new SystemNameComparator());
 RowSorterUtil::setSortOrder(sorter, AudioTableDataModel::SYSNAMECOL, ASCENDING);
 bufferDataTable = new JTable(bufferDataModel);
 bufferDataTable = bufferDataModel->makeJTable(bufferDataModel->getMasterClassName(), bufferDataModel, sorter);//bufferDataScroll = new JScrollPane(bufferDataTable);
 bufferDataTable->setColumnModel(new XTableColumnModel(bufferDataTable));
 bufferDataTable->createDefaultColumnsFromModel();

 sourceDataModel = sourceModel;
 //sourceDataTable = JTableUtil.sortableDataModel(sourceDataModel);
 //sourceDataTable = new JTable(sourceDataModel);
 sorter = new TableRowSorter(sourceDataModel);
 sorter->setComparator(AudioTableDataModel::SYSNAMECOL, new SystemNameComparator());
 RowSorterUtil::setSortOrder(sorter, AudioTableDataModel::SYSNAMECOL, ASCENDING);
 sourceDataTable = sourceDataModel->makeJTable(sourceDataModel->getMasterClassName(), sourceDataModel, sorter);//sourceDataScroll = new JScrollPane(sourceDataTable);
 sourceDataTable->setColumnModel(new XTableColumnModel(sourceDataTable));
 sourceDataTable->createDefaultColumnsFromModel();
 sourceDataTable->resizeColumnsToContents();
#if 0
 // give system name column as smarter sorter and use it initially
 try {
     // Listener first
     TableSorter ltmodel = ((TableSorter) listenerDataTable.getModel());
     ltmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
     ltmodel.setSortingStatus(AudioTableDataModel.SYSNAMECOL, TableSorter.ASCENDING);

     // Buffers next
     TableSorter btmodel = ((TableSorter) listenerDataTable.getModel());
     btmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
     btmodel.setSortingStatus(AudioTableDataModel.SYSNAMECOL, TableSorter.ASCENDING);

     // Sources last
     TableSorter stmodel = ((TableSorter) listenerDataTable.getModel());
     stmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
     stmodel.setSortingStatus(AudioTableDataModel.SYSNAMECOL, TableSorter.ASCENDING);
 } catch (java.lang.ClassCastException e) {
 }  // happens if not sortable table
#endif
 // configure items for GUI
 listenerDataModel->configureTable(listenerDataTable);
 listenerDataModel->configEditColumn(listenerDataTable);
 listenerDataModel->persistTable(listenerDataTable);
 bufferDataModel->configureTable(bufferDataTable);
 bufferDataModel->configEditColumn(bufferDataTable);
 bufferDataModel->persistTable(bufferDataTable);
 sourceDataModel->configureTable(sourceDataTable);
 sourceDataModel->configEditColumn(sourceDataTable);
 sourceDataModel->persistTable(sourceDataTable);

 // general GUI config
 resize(800, 400);
 QVBoxLayout* thisLayout;
 this->setLayout(thisLayout = new QVBoxLayout(this));

 // install items in GUI
 audioTabs = new QTabWidget(this);
 QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Expanding);
 sp.setHorizontalStretch(0);
 sp.setVerticalStretch(0);
 sp.setHeightForWidth(audioTabs->sizePolicy().hasHeightForWidth());
 audioTabs->setSizePolicy(sp);
 audioTabs->adjustSize();
 //audioTabs-> setMinimumHeight(300);
 audioTabs->setLayout(new QVBoxLayout);

 audioTabs->setMinimumSize(500,300);
 audioTabs->addTab(listenerDataTable, tr("Listener")/*,`                   listenerDataScroll*/);
 audioTabs->addTab(bufferDataTable, tr("Buffers")/*, bufferDataScroll*/);
 audioTabs->addTab(sourceDataTable, tr("Sources")/*, sourceDataScroll*/);

 thisLayout->addWidget(audioTabs); //, /*BorderLayout.CENTER*/0, Qt::AlignVCenter);

 //bottomBox = Box.createHorizontalBox();
 bottomBox = new QGroupBox(this);
 bottomBox->setLayout(bottomBoxLayout = new FlowLayout);
 //bottomBox.add(Box.createHorizontalGlue());	// stays at end of box
 bottomBoxIndex = 0;

 thisLayout->addWidget(bottomBox); //, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);

 // add extras, if desired by subclass
 extras();

 // set preferred scrolling options
 // listenerDataScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
 // listenerDataScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
 // bufferDataScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
 // bufferDataScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
 // sourceDataScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
 // sourceDataScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

}

/**
 * Hook to allow sub-types to install more items in GUI
 */
void AudioTablePanel::extras()
{
}

/*protected*/ QGroupBox* AudioTablePanel::getBottomBox()
{
 return bottomBox;
}

/*public*/ QAction* AudioTablePanel::getPrintItem()
{
 //    ResourceBundle rbapps = ResourceBundle.getBundle("apps.AppsBundle");
 QAction* printItem = new QAction(tr("Print Table"), this);

// printItem.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            try {
//                MessageFormat footerFormat = new MessageFormat("Page {0,number}");
//                listenerDataTable.print(JTable.PrintMode.FIT_WIDTH, new MessageFormat("Listener Table"), footerFormat);
//                bufferDataTable.print(JTable.PrintMode.FIT_WIDTH, new MessageFormat("Buffer Table"), footerFormat);
//                sourceDataTable.print(JTable.PrintMode.FIT_WIDTH, new MessageFormat("Source Table"), footerFormat);
//            } catch (java.awt.print.PrinterException e1) {
//                log.warn("error printing: " + e1, e1);
//            }
//        }
//    });
 connect(printItem, SIGNAL(triggered()), this, SLOT(On_printItemTriggered()));
    return printItem;
}
void AudioTablePanel::On_printItemTriggered()
{
#if 0
 MessageFormat footerFormat = new MessageFormat("Page {0,number}");
 listenerDataTable.print(JTable.PrintMode.FIT_WIDTH, new MessageFormat("Listener Table"), footerFormat);
 bufferDataTable.print(JTable.PrintMode.FIT_WIDTH, new MessageFormat("Buffer Table"), footerFormat);
 sourceDataTable.print(JTable.PrintMode.FIT_WIDTH, new MessageFormat("Source Table"), footerFormat);
} catch (java.awt.print.PrinterException e1) {
 log.warn("error printing: " + e1, e1);
#endif
}


/**
 * Add a component to the bottom box. Takes care of organising glue, struts
 * etc
 *
 * @param comp
 */
/*protected*/ void AudioTablePanel::addToBottomBox(QWidget* comp)
{
//    bottomBoxLayout->addW(Box.createHorizontalStrut(bottomStrutWidth), bottomBoxIndex);
 ++bottomBoxIndex;
 bottomBoxLayout->addWidget(comp);
 ++bottomBoxIndex;
}

/*public*/ void AudioTablePanel::dispose()
{
 if (listenerDataModel != NULL)
 {
  listenerDataModel->stopPersistingTable(listenerDataTable);
  listenerDataModel->dispose();
 }
 listenerDataModel = NULL;
 listenerDataTable = NULL;
//    listenerDataScroll = NULL;
 if (bufferDataModel != NULL)
 {
  bufferDataModel->stopPersistingTable(bufferDataTable);
  bufferDataModel->dispose();
 }
 bufferDataModel = NULL;
 bufferDataTable = NULL;
//    bufferDataScroll = NULL;
 if (sourceDataModel != NULL)
 {
  sourceDataModel->stopPersistingTable(sourceDataTable);
  sourceDataModel->dispose();
 }
 sourceDataModel = NULL;
 sourceDataTable = NULL;
//    sourceDataScroll = NULL;
}
