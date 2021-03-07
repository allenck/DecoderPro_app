#include "operationsframe.h"
#include "operationspanel.h"
#include "control.h"
#include <QPushButton>
#include <QRadioButton>
#include "jcombobox.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QSignalMapper>
#include "logger.h"
#include "jtable.h"
#include "userpreferencesmanager.h"
#include "instancemanager.h"
#include "operationssetuppanel.h"
#include "operationssetupframe.h"
#include <QScrollArea>
#include <jtextarea.h>
#include "routestableframe.h"
#include "routeeditframe.h"
#include "xtablecolumnmodel.h"
#include "htmltextedit.h"


//OperationsFrame::OperationsFrame(QWidget* parent)
// : JmriJFrame(parent)
//{
//}
namespace Operations
{
/**
 * Frame for operations
 *
 * @author Dan Boudreau Copyright (C) 2008, 2012
 * @version $Revision: 28077 $
 */
///*public*/ class OperationsFrame extends JmriJFrame implements AncestorListener {

 /**
  *
  */
 //private static final long serialVersionUID = -8263240370517832287L;
 /*public*/ /*static*/ /*final*/ QString OperationsFrame::NEW_LINE = "\n"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString OperationsFrame::NONE = ""; // NOI18N

 /*public*/ OperationsFrame::OperationsFrame(QString s, QWidget* parent)
  : JmriJFrame(s, parent) {
     //this(s, new OperationsPanel());
  common();
  setContentPane(new OperationsPanel(this));
  this->setEscapeKeyClosesWindow(true);

 }

 /*public*/ OperationsFrame::OperationsFrame(QWidget* parent)
: JmriJFrame(parent) {
     //this(new OperationsPanel());
  common();
  this->setContentPane(new OperationsPanel(this));
//  QObject* pp = p->parent();
//     this->setContentPane(p);
     this->setEscapeKeyClosesWindow(true);
 }

 /*public*/ OperationsFrame::OperationsFrame(OperationsPanel* p, QWidget* parent)
: JmriJFrame(parent)
 {
     //super();
  common();
  this->setContentPane(p);
  this->setEscapeKeyClosesWindow(true);
 }
 // NOTE: calling class should setContentPane explictly!
 /*public*/ OperationsFrame::OperationsFrame(QString s, OperationsPanel* p, QWidget* parent)
: JmriJFrame(s, parent) {
     //super(s);
common();
  QObject* pp = p->parent();
     this->setContentPane(p);
     this->setEscapeKeyClosesWindow(true);
 }

 void OperationsFrame::common()
 {
  setObjectName("OperationsFrame");
  log = new Logger("OperationsFrame");
  buttonMapper = new QSignalMapper(this);
  connect(buttonMapper, SIGNAL(mapped(QWidget*)), this, SLOT(on_buttonActionPerformed(QWidget*)));
  radioButtonMapper = new QSignalMapper();
  connect(radioButtonMapper, SIGNAL(mapped(QWidget*)), this, SLOT(on_radioButtonActionPerformed(QWidget*)));
  checkBoxMapper = new QSignalMapper();
  connect(checkBoxMapper, SIGNAL(mapped(QWidget*)), this, SLOT(on_checkBoxActionPerformed(QWidget*)));
  comboBoxMapper = new QSignalMapper();
  connect(comboBoxMapper, SIGNAL(mapped(QWidget*)), this, SLOT(on_comboBoxActionPerformed(QWidget*)));
  spinBoxMapper = new QSignalMapper();
  connect(spinBoxMapper, SIGNAL(mapped(QWidget*)), this, SLOT(on_spinnerChangeEvent(QWidget*)));
  gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 5px; margin-top: 1ex; /* leave space at the top for the title */} "
                 "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

 }
// @Override
 /*public*/ void OperationsFrame::initComponents()
 {
     // default method does nothing, but fail to call super.initComponents,
     // so that Exception does not need to be caught
 }

 /*public*/ void OperationsFrame::initMinimumSize() {
     initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight250));
 }

 /*public*/ void OperationsFrame::initMinimumSize(QSize dimension) {
     setMinimumSize(dimension);
     adjustSize();
     setVisible(true);
 }

 /*protected*/ void OperationsFrame::addItem(QWidget* c, int x, int y) {
     ((OperationsPanel*) this->getContentPane())->addItem(c, x, y);
 }
#if 1
 /*protected*/ void OperationsFrame::addItemLeft(QWidget* c, int x, int y) {
     ((OperationsPanel*) this->getContentPane())->addItemLeft(c, x, y);
 }

 /*protected*/ void OperationsFrame::addItemWidth(QWidget* c, int width, int x, int y) {
     ((OperationsPanel*) this->getContentPane())->addItemWidth(c, width, x, y);
 }
#endif
 /*protected*/ void OperationsFrame::addItem(QWidget* p, QWidget* c, int x, int y) {
     ((OperationsPanel*) this->getContentPane())->addItem(p, c, x, y);
 }

 /*protected*/ void OperationsFrame::addItemLeft(QWidget* p, QWidget* c, int x, int y) {
     ((OperationsPanel*) this->getContentPane())->addItemLeft(p, c, x, y);
 }

 /*protected*/ void OperationsFrame::addItemTop(QWidget* p, QWidget* c, int x, int y) {
     ((OperationsPanel*) this->getContentPane())->addItemTop(p, c, x, y);
 }

 /*protected*/ void OperationsFrame::addItemWidth(QWidget* p, QWidget* c, int width, int x, int y) {
     ((OperationsPanel*) this->getContentPane())->addItemWidth(p, c, width, x, y);
 }

 /**
  * Gets the number of checkboxes(+1) that can fix in one row see
  * OperationsFrame.minCheckboxes and OperationsFrame.maxCheckboxes
  *
  * @return the number of checkboxes, minimum is 5 (6 checkboxes)
  */
 /*protected*/ int OperationsFrame::getNumberOfCheckboxesPerLine() {
     return ((OperationsPanel*) this->getContentPane())->getNumberOfCheckboxesPerLine(this->sizeHint());
 }

 /*protected*/ void OperationsFrame::addButtonAction(QPushButton* b)
 {
    // b.addActionListener(this->buttonActionPerformed);
 connect(b, SIGNAL(clicked()), buttonMapper, SLOT(map()));
 buttonMapper->setMapping(b,b);
 }

 /*protected*/ void OperationsFrame::on_buttonActionPerformed(QWidget* ae)
 {
  buttonActionPerformed(ae);
 }

 /*protected*/ void OperationsFrame::buttonActionPerformed(QWidget* ae) {
  //Q_ASSERT(false); //must be overridden!
     ((OperationsPanel*) this->getContentPane())->buttonActionPerformed(ae);
 }

 /*protected*/ void OperationsFrame::addRadioButtonAction(QRadioButton* b) {
 //b.addActionListener(this->radioButtonActionPerformed());
  connect(b, SIGNAL(clicked()), radioButtonMapper , SLOT(map()));
  radioButtonMapper->setMapping(b,b);
 }

 /*protected*/ void OperationsFrame::on_radioButtonActionPerformed(QWidget* b)
 {
  radioButtonActionPerformed(b);
 }

 /*protected*/ void OperationsFrame::radioButtonActionPerformed(QWidget* /*b*/)
 {
  Q_ASSERT(false); // must be overridden!
 }

 /*protected*/ void OperationsFrame::addCheckBoxAction(QCheckBox* b) {
     //b.addActionListener(this->checkBoxActionPerformed);
  connect(b, SIGNAL(clicked()), checkBoxMapper, SLOT(map()));
  checkBoxMapper->setMapping(b,b);
 }

 /*protected*/ void OperationsFrame::on_checkBoxActionPerformed(QWidget* b)
 {
  checkBoxActionPerformed(b);
 }

 /*protected*/ void OperationsFrame::checkBoxActionPerformed(QWidget* /*b*/)
 {
  Q_ASSERT(false); // must be overridden!
 }

 /*protected*/ void OperationsFrame::addSpinnerChangeListerner(QSpinBox* s) {
     //s.addChangeListener(this::spinnerChangeEvent);
  spinBoxMapper->setMapping(s,s);
  connect(s, SIGNAL(valueChanged(int)), spinBoxMapper, SLOT(map()));
 }

 /*protected*/ void OperationsFrame::on_spinnerChangeEvent(QWidget* ae) {
  spinnerChangeEvent(ae);
 }

 /*protected*/ void OperationsFrame::spinnerChangeEvent(QWidget* /*ae*/) {
  Q_ASSERT(false); // must be overridden!
 }

 /*protected*/ void OperationsFrame::addComboBoxAction(JComboBox* b) {
     //b.addActionListener(this::comboBoxActionPerformed);
  connect(b, SIGNAL(currentIndexChanged(int)), comboBoxMapper, SLOT(map()));
  comboBoxMapper->setMapping(b,b);
 }

 /*protected*/ void OperationsFrame::on_comboBoxActionPerformed(QWidget *ae)
 {
  comboBoxActionPerformed(ae);
 }

 /*protected*/ void OperationsFrame::comboBoxActionPerformed(QWidget* /*ae*/)
 {
  Q_ASSERT(false); // should be overridden!
 }

 /*protected*/ void OperationsFrame::selectNextItemComboBox(JComboBox* b) {
     ((OperationsPanel*) this->getContentPane())->selectNextItemComboBox(b);
 }

 /**
  * Will modify the character column width of a TextArea box to 90% of a
  * panels width. ScrollPane is set to 95% of panel width.
  *
  * @param scrollPane
  * @param textArea
  */
 /*protected*/ void OperationsFrame::adjustTextAreaColumnWidth(QWidget* scrollPane, JTextArea* textArea) {
     ((OperationsPanel*) this->getContentPane())->adjustTextAreaColumnWidth(scrollPane, textArea, this->getPreferredSize());
 }

 /*protected*/ void OperationsFrame::adjustTextAreaColumnWidth(QWidget* scrollPane, HtmlTextEdit* textArea) {
     ((OperationsPanel*) this->getContentPane())->adjustTextAreaColumnWidth(scrollPane, textArea, this->getPreferredSize());
 }

 /**
  * Saves the table's width, position, and sorting status in the user
  * preferences file
  *
  * @param table Table to be saved.
  */
 /*protected*/ void OperationsFrame::saveTableDetails(JTable* table)
 {
  UserPreferencesManager* p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
  if (p == NULL) {
      return;
  }
  QSortFilterProxyModel* sorter = NULL;
  QString tableref = getWindowFrameRef() + ":table"; // NOI18N
  try {
      sorter = (QSortFilterProxyModel*) table->model();
  } catch (Exception e) {
      log->debug("table " + tableref + " doesn't use sorter");
  }
#if 0 // TODO:
  // is the table using XTableColumnModel?
  if (sorter != NULL && sorter->columnCount() != table->getColumnCount())
  {
   log->debug(tr("Sort column count: %1 table column count: %1 XTableColumnModel in use").arg(sorter->columnCount()).arg(
              table->col()));
   XTableColumnModel* tcm = (XTableColumnModel*) table->getColumnModel();
   // need to have all columns visible so we can get the proper column order
   QVector<bool> columnVisible = QVector<bool>(sorter->getColumnCount());
   for (int i = 0; i < sorter->getColumnCount(); i++)
   {
    columnVisible.replace(i, tcm->isColumnVisible(tcm->getColumnByModelIndex(i)));
    tcm->setColumnVisible(tcm->getColumnByModelIndex(i), true);
   }
   // now save with the correct column order
   for (int i = 0; i < sorter.getColumnCount(); i++)
   {
    int sortStatus = sorter->getSortingStatus(i);
    int width = tcm->getColumnByModelIndex(i)->getPreferredWidth();
    int order = table->convertColumnIndexToView(i);
    // must save with column not hidden
    p->setTableColumnPreferences(tableref, sorter->getColumnName(i), order, width, sortStatus, false);
   }
   // now restore
   for (int i = 0; i < sorter->getColumnCount(); i++) {
       tcm->setColumnVisible(tcm->getColumnByModelIndex(i), columnVisible[i]);
   }

  } // standard table

  else
  {
   for (int i = 0; i < table->getColumnCount(); i++)
   {
    int sortStatus = 0;
    if (sorter != NULL)
    {
     sortStatus = sorter->getSortingStatus(i);
    }
    p->setTableColumnPreferences(tableref, table->getColumnName(i), i, table->getColumnModel()->getColumn(i)
            .getPreferredWidth(), sortStatus, false);
   }
  }
#endif
 }

 /**
  * Loads the table's width, position, and sorting status from the user
  * preferences file.
  *
  * @param table The table to be adjusted.
  * @return true if table has been adjusted by saved xml file.
  */
 /*public*/ bool OperationsFrame::loadTableDetails(JTable* table)
 {
//  UserPreferencesManager* p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
//  QSortFilterProxyModel* sorter = NULL;
//  QString tableref = getWindowFrameRef() + ":table"; // NOI18N
//  if (p == NULL || p->getTablesColumnList(tableref).isEmpty()) {
//      return false;
  return ((OperationsPanel*) this->getContentPane())->loadTableDetails(table);

  }
#if 0
  try
  {
      sorter = (QSortFilterProxyModel*) table->getModel();
  } catch (Exception e) {
      log->debug("table " + tableref + " doesn't use sorter");
  }
  // bubble sort
  int count = 0;
  while (!sortTable(table, p, tableref) && count < 10) {
      count++;
      log->debug(tr("bubble sort pass %1:").arg(count);
  }
  // Some tables have more than one name, so use the current one for size
  for (int i = 0; i < table->getColumnCount(); i++)
  {
   QString columnName = table.getColumnName(i);
   int sort = p->getTableColumnSort(tableref, columnName);
   if (sorter != NULL) {
       sorter->setSortingStatus(i, sort);
   }
   int width = p->getTableColumnWidth(tableref, columnName);
   if (width != -1) {
       table->getColumnModel()->getColumn(i)->setPreferredWidth(width);
   } else {
       // name not found so use one that exists
       QString name = p->getTableColumnAtNum(tableref, i);
       if (name != NULL) {
           width = p.getTableColumnWidth(tableref, name);
           table->getColumnModel()->getColumn(i)->setPreferredWidth(width);
       }
   }
  }

        return true;
 }
#endif
#if 0
 /*private*/ boolean sortTable(JTable table, UserPreferencesManager p, String tableref) {
     boolean sortDone = true;
     for (int i = 0; i < table.getColumnCount(); i++) {
         String columnName = table.getColumnName(i);
         int order = p.getTableColumnOrder(tableref, columnName);
         if (order == -1) {
             log.debug("Column name {} not found in user preference file", columnName);
             break; // table structure has changed quit sort
         }
         if (i != order && order < table.getColumnCount()) {
             table.moveColumn(i, order);
             log.debug("Move column number: {} name: {} to: {}", i, columnName, order);
             sortDone = false;
         }
     }
     return sortDone;
 }
#endif
 /*protected*/ void OperationsFrame::clearTableSort(JTable* table) {
     ((OperationsPanel*) this->getContentPane())->clearTableSort(table);
 }

 /*protected*/ /*synchronized*/ void OperationsFrame::createShutDownTask() {
     ((OperationsPanel*) this->getContentPane())->createShutDownTask();
 }

 //@Override
 /*public*/ void OperationsFrame::dispose()
 {
  ((OperationsPanel*) this->getContentPane())->dispose();
  JmriJFrame::dispose();
 }

 //@Override
 /*protected*/ void OperationsFrame::storeValues() {
     ((OperationsPanel*) this->getContentPane())->storeValues();
 }
#if 0
 /*protected*/ String lineWrap(String s) {
     return ((OperationsPanel) this->getContentPane()).lineWrap(s, this->getPreferredSize());
 }

 // Kludge fix for horizontal scrollbar encroaching buttons at bottom of a scrollable window.
 /*protected*/ JPanel pad; // used to pad out lower part of window to fix horizontal scrollbar issue

 /*protected*/ void addHorizontalScrollBarKludgeFix(JScrollPane pane, JPanel panel) {
     pad = new JPanel();	// kludge fix for horizontal scrollbar
     pad.add(new JLabel(" "));
     panel.add(pad);

     // make sure control panel is the right size
     pane.setMinimumSize(new Dimension(500, 130));
     pane.setMaximumSize(new Dimension(2000, 170));
     pane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER);

     pane.addAncestorListener(this); // used to determine if scrollbar is showing
 }

 @Override
 /*public*/ void ancestorAdded(AncestorEvent event) {
     ((OperationsPanel) this->getContentPane()).ancestorAdded(event);
 }

 @Override
 /*public*/ void ancestorRemoved(AncestorEvent event) {
     ((OperationsPanel) this->getContentPane()).ancestorRemoved(event);
 }

 @Override
 /*public*/ void ancestorMoved(AncestorEvent event) {
     ((OperationsPanel) this->getContentPane()).ancestorMoved(event);
 }
#endif
}
