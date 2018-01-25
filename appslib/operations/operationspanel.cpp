#include "operationspanel.h"
#include "control.h"
//#include "operationsmanager.h"
#include <QPushButton>
#include <QSignalMapper>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QSortFilterProxyModel>
#include <jtable.h>
#include "logger.h"
#include "engineeditframe.h"
#include "gridbagconstraints.h"
#include <QGridLayout>
#include "cartypes.h"
#include "htmltextedit.h"
#include <QScrollArea>
#include <QFontMetrics>
#include <gridbaglayout.h>
#include "htmltextedit.h"
#include "jtextarea.h"
#include "tablerowsorter.h"
#include "optional.h"
#include "instancemanager.h"
#include "jtablepersistencemanager.h"
#include "operationsxml.h"

//OperationsPanel::OperationsPanel(QWidget *parent) :
//  QWidget(parent)
//{
//}
namespace Operations
{
/**
 * Panel for operations
 *
 * @author Dan Boudreau Copyright (C) 2008, 2012
 * @version $Revision: 28077 $
 */
///*public*/ class OperationsPanel extends JPanel implements AncestorListener {

 /**
  *
  */
 //private static /*final*/ long serialVersionUID = 4203296733948891651L;
 /*public*/ /*static*/ /*final*/ QString OperationsPanel::NEW_LINE = "\n"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString OperationsPanel::NONE = ""; // NOI18N

 /*public*/ OperationsPanel::OperationsPanel(QWidget *parent) :
  QWidget(parent)
 {
       //super();
  setObjectName("OperationsPanel");
  buttonMapper = new QSignalMapper();
  OperationsFrame* owner = (OperationsFrame*)this->parent();
  Q_ASSERT(owner != NULL);
  connect(buttonMapper, SIGNAL(mapped(QWidget*)), owner, SLOT(buttonActionPerformed(QWidget*)));
  radioButtonMapper = new QSignalMapper();
  connect(radioButtonMapper, SIGNAL(mapped(QWidget*)), this, SLOT(radioButtonActionPerformed(QWidget*)));
  checkBoxMapper = new QSignalMapper();
  connect(checkBoxMapper, SIGNAL(mapped(QWidget*)), this, SLOT(checkBoxActionPerformed(QWidget*)));
  comboBoxMapper = new QSignalMapper();
  connect(comboBoxMapper, SIGNAL(mapped(QWidget*)), this, SLOT(comboBoxActionPerformed(QWidget*)));
  log = new Logger("OperationsPanel");
  gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 5px; margin-top: 1ex; /* leave space at the top for the title */} "
                 "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
 }

 /*public*/ void OperationsPanel::initMinimumSize() {
     initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight250));
 }

 /*public*/ void OperationsPanel::initMinimumSize(QSize dimension) {
     setMinimumSize(dimension);
 }

 /*public*/ void OperationsPanel::dispose() {
     // The default method does nothing.
 }

 /*protected*/ void OperationsPanel::addItem(QWidget* c, int x, int y) {
     GridBagConstraints gc = GridBagConstraints();
     gc.gridx = x;
     gc.gridy = y;
     gc.weightx = 100.0;
     gc.weighty = 100.0;
     ((QGridLayout*)this->layout())->addWidget(c, gc.gridy, gc.gridx, gc.rowSpan(), gc.colSpan(), gc.align());
 }

 /*protected*/ void OperationsPanel::addItemLeft(QWidget* c, int x, int y) {
     GridBagConstraints gc = GridBagConstraints();
     gc.gridx = x;
     gc.gridy = y;
     gc.weightx = 100.0;
     gc.weighty = 100.0;
     gc.anchor = GridBagConstraints::WEST;
     ((QGridLayout*)this->layout())->addWidget(c, gc.gridy, gc.gridx, gc.rowSpan(), gc.colSpan(), gc.align());
 }

 /*protected*/ void OperationsPanel::addItemWidth(QWidget* c, int width, int x, int y) {
     GridBagConstraints gc =  GridBagConstraints();
     gc.gridx = x;
     gc.gridy = y;
     gc.gridwidth = width;
     gc.weightx = 100.0;
     gc.weighty = 100.0;
     ((QGridLayout*)this->layout())->addWidget(c, gc.gridy, gc.gridx, gc.rowSpan(), gc.colSpan(), gc.align());
 }

 /*protected*/ void OperationsPanel::addItem(QWidget* p, QWidget* c, int x, int y)
{
  GridBagConstraints gc = GridBagConstraints();
  if(p->layout() ==NULL)
   p->setLayout(new QGridLayout);
  //else
  {
   if(x == 0 && y == 0)
   {
    p->layout()->addWidget(c);
    return;
   }
   Q_ASSERT(qobject_cast<QGridLayout*>(p->layout()) != NULL);
  }
  gc.gridx = x;
  gc.gridy = y;
  gc.weightx = 100.0;
  gc.weighty = 100.0;
  ((QGridLayout*)p->layout())->addWidget(c, gc.gridy, gc.gridx, gc.rowSpan(), gc.colSpan(), gc.align());
 }

 /*protected*/ void OperationsPanel::addItemLeft(QWidget* p, QWidget* c, int x, int y)
 {
  GridBagConstraints gc = GridBagConstraints();
  if(p->layout() ==NULL)
   p->setLayout(new QGridLayout);
  else
   Q_ASSERT(qobject_cast<QGridLayout*>(p->layout()) != NULL);
  gc.gridx = x;
  gc.gridy = y;
  gc.weightx = 100.0;
  gc.weighty = 100.0;
  gc.anchor = GridBagConstraints::WEST;
  if(qobject_cast<GridBagLayout*>(p->layout()) !=NULL)
   ((GridBagLayout*)p->layout())->addWidget(c, gc);
   else
  ((QGridLayout*)p->layout())->addWidget(c, gc.gridy, gc.gridx, gc.rowSpan(), gc.colSpan(), gc.align());
  //log->debug(tr("layout has %1 boxes").arg(p->layout()->children().count()));
 }

 /*protected*/ void OperationsPanel::addItemTop(QWidget* p, QWidget* c, int x, int y) {
     GridBagConstraints gc =  GridBagConstraints();
     if(p->layout() ==NULL)
      p->setLayout(new QGridLayout);
     else
      Q_ASSERT(qobject_cast<QGridLayout*>(p->layout()) != NULL);
     gc.gridx = x;
     gc.gridy = y;
     gc.weightx = 100;
     gc.weighty = 100;
     gc.anchor = GridBagConstraints::NORTH;
     ((QGridLayout*)p->layout())->addWidget(c, gc.gridy, gc.gridx, gc.rowSpan(), gc.colSpan(), gc.align());
 }

 /*protected*/ void OperationsPanel::addItemWidth(QWidget* p, QWidget* c, int width, int x, int y) {
     GridBagConstraints gc =  GridBagConstraints();
     if(p->layout() ==NULL)
      p->setLayout(new QGridLayout);
     else
      Q_ASSERT(qobject_cast<QGridLayout*>(p->layout()) != NULL);
     gc.gridx = x;
     gc.gridy = y;
     gc.gridwidth = width;
     gc.weightx = 100.0;
     gc.weighty = 100.0;
     gc.anchor = GridBagConstraints::WEST;
     ((QGridLayout*)p->layout())->addWidget(c, gc.gridy, gc.gridx, gc.rowSpan(), gc.colSpan(), gc.align());
 }

 /*private*/ /*static*/ /*final*/ int OperationsPanel::MIN_CHECKBOXES = 5;
 /*private*/ /*static*/ /*final*/ int OperationsPanel::MAX_CHECKBOXES = 11;

 /**
  * Gets the number of checkboxes(+1) that can fix in one row see
  * OperationsFrame.minCheckboxes and OperationsFrame.maxCheckboxes
  *
  * @return the number of checkboxes, minimum is 5 (6 checkboxes)
  */
 /*protected*/ int OperationsPanel::getNumberOfCheckboxesPerLine() {
     return getNumberOfCheckboxesPerLine(this->sizeHint());
 }

 /*protected*/ int OperationsPanel::getNumberOfCheckboxesPerLine(QSize size) {
 if (size == QSize()) {
         return MIN_CHECKBOXES; // default is 6 checkboxes per row
     }
     QString padding = QString("X");

     for (int i = 0; i < CarTypes::instance()->getMaxFullNameLength(); i++) {
         padding.append("X");
     }

     QCheckBox* box = new QCheckBox(padding);
     int number = size.width() / (box->sizeHint().width());
     if (number < MIN_CHECKBOXES) {
         number = MIN_CHECKBOXES;
     }
     if (number > MAX_CHECKBOXES) {
         number = MAX_CHECKBOXES;
     }
     return number;
 }

 /*protected*/ void OperationsPanel::addButtonAction(QPushButton* b) {
//        b.addActionListener((ActionEvent e) -> {
//            buttonActionPerformed(e);
//        });
 Q_ASSERT(b != NULL);
  connect(b, SIGNAL(clicked()), buttonMapper, SLOT(map()));
  buttonMapper->setMapping(b,b);

 }

 /*protected*/ void OperationsPanel::buttonActionPerformed(QWidget* /*b*/) {
     log->debug("button action not overridden");
 }

 /*protected*/ void OperationsPanel::addRadioButtonAction(QRadioButton* b) {
//        b.addActionListener((ActionEvent e) -> {
//            radioButtonActionPerformed(e);
//        });
 //connect(radioButtonMapper, SIGNAL(mapped(QObject*)), this, SLOT(radioButtonActionPerformed(QWidget* )));
 connect(b, SIGNAL(clicked()), radioButtonMapper, SLOT(map()));
 radioButtonMapper->setMapping(b,b);
 }

 /*protected*/ void OperationsPanel::radioButtonActionPerformed(QWidget* /*b*/) {
     log->debug("radio button action not overridden");
 }

 /*protected*/ void OperationsPanel::addCheckBoxAction(QCheckBox* b) {
//     b.addActionListener((ActionEvent e) -> {
//         checkBoxActionPerformed(e);
//     });
 //connect(checkBoxMapper, SIGNAL(mapped(int)),this, SLOT(checkBoxActionPerformed(QWidget* )));
 connect(b, SIGNAL(clicked()), checkBoxMapper, SLOT(map()));
  checkBoxMapper->setMapping(b,b);
 }

/*protected*/ void OperationsPanel::checkBoxActionPerformed(QWidget* /*b*/) {
     log->debug("check box action not overridden");
 }

 /*protected*/ void OperationsPanel::addSpinnerChangeListerner(QSpinBox* s) {
//     s.addChangeListener((ChangeEvent e) -> {
//         spinnerChangeEvent(e);
//     });
 connect(s, SIGNAL(valueChanged(int)), this, SLOT(spinnerChangeEvent()));

 }

 /*protected*/ void OperationsPanel::spinnerChangeEvent(ChangeEvent* ae) {
     log->debug("spinner action not overridden");
 }

 /*protected*/ void OperationsPanel::addComboBoxAction(QComboBox* b) {
//     b.addActionListener((ActionEvent e) -> {
//         comboBoxActionPerformed(e);
//     });
 connect(b, SIGNAL(currentIndexChanged(int)), comboBoxMapper, SLOT(map()));
 comboBoxMapper->setMapping(b,b);
 }

 /*protected*/ void OperationsPanel::comboBoxActionPerformed(QWidget* ae) {
     log->debug("combobox action not overridden");
 }

 /*protected*/ void OperationsPanel::selectNextItemComboBox(QComboBox*  b) {
     int newIndex = b->currentIndex() + 1;
     if (newIndex < b->count()) {
         b->setCurrentIndex(newIndex);
     }
 }

 /**
  * Will modify the character column width of a TextArea box to 90% of a
  * panels width. ScrollPane is set to 95% of panel width.
  *
  * @param scrollPane
  * @param textArea
  */
 /*protected*/ void OperationsPanel::adjustTextAreaColumnWidth(QWidget* scrollPane, JTextArea* textArea) {
     this->adjustTextAreaColumnWidth(scrollPane, textArea, this->sizeHint());
 }

 /*protected*/ void OperationsPanel::adjustTextAreaColumnWidth(QWidget* scrollPane, JTextArea* textArea, QSize size) {
     //FontMetrics metrics = getFontMetrics(textArea->font());
     QFontMetrics metrics = QFontMetrics(textArea->font());
     int columnWidth = metrics.charWidth("m",0);
     int width = size.width();
     int columns = width / columnWidth * 90 / 100; // make text area 90% of the panel width
     if (columns > textArea->getColumns()) {
         log->debug(tr("Increasing text area character width to %1 columns").arg(columns));
         textArea->setColumns(columns);
     }
     scrollPane->setMinimumSize(QSize(width * 95 / 100, 60));
 }

 /*protected*/ void OperationsPanel::adjustTextAreaColumnWidth(QWidget* scrollPane, HtmlTextEdit* textArea) {
     this->adjustTextAreaColumnWidth(scrollPane, textArea, this->sizeHint());
 }

/*protected*/ void OperationsPanel::adjustTextAreaColumnWidth(QWidget* scrollPane, HtmlTextEdit* textArea, QSize size) {
    //FontMetrics metrics = getFontMetrics(textArea->font());
    QFontMetrics metrics = QFontMetrics(textArea->font());
    int columnWidth = metrics.charWidth("m",0);
    int width = size.width();
    int columns = width / columnWidth * 90 / 100; // make text area 90% of the panel width
    if (columns > textArea->getColumns()) {
        log->debug(tr("Increasing text area character width to %1 columns").arg(columns));
        textArea->setColumns(columns);
    }
    scrollPane->setMinimumSize(QSize(width * 95 / 100, 60));
}


#if 0
 /**
  * Saves the table's width, position, and sorting status in the user
  * preferences file
  *
  * @param table Table to be saved.
  */
 /*protected*/ void saveTableDetails(JTable table) {
     UserPreferencesManager p = InstanceManager.getDefault(UserPreferencesManager.class);
     if (p == NULL) {
         return;
     }
     TableSorter sorter = NULL;
     String tableref = getWindowFrameRef() + ":table"; // NOI18N
     try {
         sorter = (TableSorter) table.getModel();
     } catch (Exception e) {
         log->debug("table " + tableref + " doesn't use sorter");
     }

     // is the table using XTableColumnModel?
     if (sorter != NULL && sorter.getColumnCount() != table.getColumnCount()) {
         log->debug("Sort column count: {} table column count: {} XTableColumnModel in use", sorter.getColumnCount(),
                 table.getColumnCount());
         XTableColumnModel tcm = (XTableColumnModel) table.getColumnModel();
         // need to have all columns visible so we can get the proper column order
         boolean[] columnVisible = new boolean[sorter.getColumnCount()];
         for (int i = 0; i < sorter.getColumnCount(); i++) {
             columnVisible[i] = tcm.isColumnVisible(tcm.getColumnByModelIndex(i));
             tcm.setColumnVisible(tcm.getColumnByModelIndex(i), true);
         }
         // now save with the correct column order
         for (int i = 0; i < sorter.getColumnCount(); i++) {
             int sortStatus = sorter.getSortingStatus(i);
             int width = tcm.getColumnByModelIndex(i).getPreferredWidth();
             int order = table.convertColumnIndexToView(i);
             // must save with column not hidden
             p.setTableColumnPreferences(tableref, sorter.getColumnName(i), order, width, sortStatus, false);
         }
         // now restore
         for (int i = 0; i < sorter.getColumnCount(); i++) {
             tcm.setColumnVisible(tcm.getColumnByModelIndex(i), columnVisible[i]);
         }

     } // standard table
     else {
         for (int i = 0; i < table.getColumnCount(); i++) {
             int sortStatus = 0;
             if (sorter != NULL) {
                 sortStatus = sorter.getSortingStatus(i);
             }
             p.setTableColumnPreferences(tableref, table.getColumnName(i), i, table.getColumnModel().getColumn(i)
                     .getPreferredWidth(), sortStatus, false);
         }
     }
 }
#endif
 /**
  * Loads the table's width, position, and sorting status from the user
  * preferences file.
  *
  * @param table The table to be adjusted.
  * @return true if table has been adjusted by saved xml file.
  */
 /*public*/ bool OperationsPanel::loadTableDetails(JTable* table) {
 if (table->getRowSorter() == NULL)
 {
  TableRowSorter/*<? extends TableModel>*/* sorter = new TableRowSorter(table->getModel());
  table->setRowSorter(sorter);
  // only sort on columns that are String or Integer
  for (int i =0; i < table->getColumnCount(); i++)
  {
   // TODO: if (table.getColumnClass(i) == String.class || table.getColumnClass(i) == Integer.class)
   {
    continue; // allow sorting
   }
   sorter->setSortable(i, false);
  }
 }
 // set row height
 table->setRowHeight( QComboBox().sizeHint().height());
 // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
 table->setAutoResizeMode(JTable::AUTO_RESIZE_OFF);
 // give each cell a bit of space between the vertical lines and text
 table->setIntercellSpacing(QSize(3,1));
 // table must have a name
 table->setName(getWindowFrameRef() + ":table"); // NOI18N
#if 0
 Optional<JTablePersistenceManager*>* manager = (Optional<JTablePersistenceManager*>*) InstanceManager::getOptionalDefault("JTablePersistenceManager");
 if (manager->isPresent()) {
     manager->get()->resetState(table);
     manager->get()->persist(table);
     return true;
 }
#else
 JTablePersistenceManager* manager = (JTablePersistenceManager*) InstanceManager::getOptionalDefault("JTablePersistenceManager");
 if (manager != NULL) {
     manager->resetState(table);
     manager->persist(table);
     return true;
 }
#endif
 return false;
}
#if 0
 private boolean sortTable(JTable table, UserPreferencesManager p, String tableref) {
     boolean sortDone = true;
     for (int i = 0; i < table.getColumnCount(); i++) {
         String columnName = table.getColumnName(i);
         int order = p.getTableColumnOrder(tableref, columnName);
         if (order == -1) {
             log->debug("Column name {} not found in user preference file", columnName);
             break; // table structure has changed quit sort
         }
         if (i != order && order < table.getColumnCount()) {
             table.moveColumn(i, order);
             log->debug("Move column number: {} name: {} to: {}", i, columnName, order);
             sortDone = false;
         }
     }
     return sortDone;
 }
#endif
 /*protected*/ void OperationsPanel::clearTableSort(JTable* table) {
     QSortFilterProxyModel* sorter = NULL;
     //try {
         sorter = (QSortFilterProxyModel*) table->model();
//     } catch (Exception e) {
//         log->debug("table doesn't use sorter");
//     }
     if (sorter == NULL) {
         return;
     }
#if 0 // TODO:
     for (int i = 0; i < table.getColumnCount(); i++) {
         sorter.setSortingStatus(i, TableSorter.NOT_SORTED);
     }
#endif
 }

 /*protected*/ /*synchronized*/ void OperationsPanel::createShutDownTask()
{
#if 0 // TODO:
     OperationsManager::getInstance().setShutDownTask(new SwingShutDownTask("Operations Train Window Check", // NOI18N
             Bundle.getMessage("PromptQuitWindowNotWritten"), Bundle.getMessage("PromptSaveQuit"), this) {
                 @Override
                 /*public*/ boolean checkPromptNeeded() {
                     return !OperationsXml.areFilesDirty();
                 }

                 @Override
                 /*public*/ boolean doPrompt() {
                     storeValues();
                     return true;
                 }

                 @Override
                 /*public*/ boolean doClose() {
                     storeValues();
                     return true;
                 }
             });
#endif
 }

 /*protected*/ void OperationsPanel::storeValues() {
     OperationsXml::save();
 }
#if 0
 /*protected*/ String lineWrap(String s) {
     return this.lineWrap(s, this.getPreferredSize());
 }

 /*protected*/ String lineWrap(String s, Dimension size) {
     int numberChar = 80;
     if (size != NULL) {
         JLabel X = new JLabel("X");
         numberChar = size.width / X.getPreferredSize().width;
     }

     String[] sa = s.split(NEW_LINE);
     StringBuilder so = new StringBuilder();

     for (int i = 0; i < sa.length; i++) {
         if (i > 0) {
             so.append(NEW_LINE);
         }
         StringBuilder sb = new StringBuilder(sa[i]);
         int j = 0;
         while (j + numberChar < sb.length() && (j = sb.lastIndexOf(" ", j + numberChar)) != -1) {
             sb.replace(j, j + 1, NEW_LINE);
         }
         so.append(sb);
     }
     return so.toString();
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
//		log->debug("Ancestor Added");
     // do nothing
 }

 @Override
 /*public*/ void ancestorRemoved(AncestorEvent event) {
//		log->debug("Ancestor Removed");
     // do nothing
 }

 @Override
 /*public*/ void ancestorMoved(AncestorEvent event) {
     if (pad != NULL) {
         if (pad.isVisible() ^ ((JScrollPane) event.getSource()).getHorizontalScrollBar().isShowing()) {
             pad.setVisible(((JScrollPane) event.getSource()).getHorizontalScrollBar().isShowing());
//				log->debug("Scrollbar visible: {}", pad.isVisible());
         }
     }
 }
#endif
 /*protected*/ QString OperationsPanel::getWindowFrameRef() {
     //if (this.getTopLevelAncestor() instanceof JmriJFrame)
 if(qobject_cast<JmriJFrame*>(this->window()))
  {
      return ((JmriJFrame*) this->window())->getWindowFrameRef();
  }
  return NULL;
 }

}
