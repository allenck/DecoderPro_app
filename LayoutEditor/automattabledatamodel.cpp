#include "automattabledatamodel.h"
#include "automatsummary.h"
#include "logger.h"
#include "tablecolumnmodel.h"
#include "abstractautomaton.h"
#include <QPushButton>
#include "jtextfield.h"
#include "jtable.h"
#include <QHeaderView>
#include "tablecolumn.h"
#include "pushbuttondelegate.h"

//AutomatTableDataModel::AutomatTableDataModel(QObject *parent) :
//  AbstractTableModel(parent)
//{
//}
/**
 * Table data model for display of Automat instances.
 *
 *
 * @author	Bob Jacobsen Copyright (C) 2004
 * @version	$Revision: 28746 $
 */
///*public*/ class AutomatTableDataModel extends javax.swing.table.AbstractTableModel
//        implements PropertyChangeListener {

/**
 *
 */
//private static final long serialVersionUID = 5450062337875366030L;

/*static*/ /*final*/ int AutomatTableDataModel::NUMCOLUMN = 3;

//static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.automat.monitor.AutomatTableBundle");

/*public*/ AutomatTableDataModel::AutomatTableDataModel(QObject *parent) :
  AbstractTableModel(parent) {
    //super();
 summary = AutomatSummary::instance();
 // listen for new/gone/changed Automat instances
 summary->addPropertyChangeListener((PropertyChangeListener*)this);
 //connect(summary, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 log = new Logger("AutomatTableDataModel");
}

/*public*/ void AutomatTableDataModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("Insert")) {
        // fireTableRowsInserted(((Integer)e.getNewValue()).intValue(), ((Integer)e.getNewValue()).intValue());
        fireTableDataChanged();
    } else if (e->getPropertyName()==("Remove")) {
        //fireTableRowsDeleted(((Integer)e.getNewValue()).intValue(), ((Integer)e.getNewValue()).intValue());
        fireTableDataChanged();
    } else if (e->getPropertyName()==("Count")) {
        // it's a count indication, so update TURNS
        int row = e->getNewValue().toInt();
        // length might have changed...
        if (row < rowCount(QModelIndex())) {
            fireTableCellUpdated(row, TURNSCOL);
        }
    } else {
        log->warn("Unexpected property named " + e->getPropertyName());
    }
}

/*public*/ int AutomatTableDataModel::columnCount(const QModelIndex &parent) const
{
    return NUMCOLUMN;
}

/*public*/ int AutomatTableDataModel::rowCount(const QModelIndex &parent) const
{
 return AutomatSummary::instance()->length();
}

/*public*/ QVariant AutomatTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
    switch (section) {
        case NAMECOL:
            return "Name";
        case TURNSCOL:
            return "Cycles";
        case KILLCOL:
            return "Kill";  // problem if this is blank?

        default:
            return "unknown";
    }
 }
 return QVariant();
}

/**
 * Note that this returns String even for columns that contain buttons
 */
/*public*/ QString AutomatTableDataModel::getColumnClass(int col) {
    switch (col) {
        case NAMECOL:
        case KILLCOL:
            return "String";
        case TURNSCOL:
            return "Integer";
        default:
            return QString();
    }
}

/*public*/ Qt::ItemFlags AutomatTableDataModel::flags(const QModelIndex &index) const
{
 switch (index.column())
 {
 case KILLCOL:
     return Qt::ItemIsEditable | Qt::ItemIsEnabled;
 default:
     return Qt::ItemIsEnabled;
 }
}

/*public*/ QVariant  AutomatTableDataModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)\
 {
  int row = index.row();
  int col = index.column();
    switch (col) {
        case NAMECOL:
            return summary->get(row)->getName();
        case TURNSCOL:
            return summary->get(row)->getCount();
        case KILLCOL:  // return button text here
            return tr("Kill");
        default:
            log->error("internal state inconsistent with table requst for " + QString::number(row) + " " + QString::number(col));
     return QVariant();
    }
 }
 return QVariant();
}

/*public*/ int AutomatTableDataModel::getPreferredWidth(int col) {
    switch (col) {
        case NAMECOL:
     return  JTextField(20).sizeHint().width();
        case TURNSCOL:
     return  JTextField(5).sizeHint().width();
        case KILLCOL:
     return  QPushButton(tr("Kill")).sizeHint().width();
        default:
            log->warn("Unexpected column in getPreferredWidth: " + QString::number(col));
     return  JTextField(5).sizeHint().width();
    }
}

/*public*/ bool AutomatTableDataModel::setData(const QModelIndex &mindex, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  if (mindex.column() == KILLCOL)
  {
   // button fired, handle
   summary->get(index(mindex.row(), NAMECOL).data().toString() ) ->stop();
  }
 }
 return false;
}

/**
 * Configure a table to have our standard rows and columns. This is
 * optional, in that other table formats can use this table model. But we
 * put it here to help keep it consistent.
 *
 * @param table
 */
/*public*/ void AutomatTableDataModel::configureTable(JTable* table)
{
 // allow reordering of the columns
 //table.getTableHeader().setReorderingAllowed(true);

 // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
 //table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

 // resize columns as requested
 for (int i = 0; i < table->horizontalHeader()->count(); i++)
 {
  int width = getPreferredWidth(i);
  table->getColumnModel()->getColumn(i)->setPreferredWidth(width);
 }
 //table.sizeColumnsToFit(-1);
 table->resizeColumnsToContents();

 // have the value column hold a button
 setColumnToHoldButton(table, KILLCOL, new QPushButton(tr("Kill")));
}

/**
 * Service method to setup a column so that it will hold a button for it's
 * values
 *
 * @param table
 * @param column
 * @param sample Typical button, used for size
 */
void AutomatTableDataModel::setColumnToHoldButton(JTable* table, int column, QPushButton* sample) {
    TableColumnModel* tcm = table->getColumnModel();
#if 0
    // install a button renderer & editor
    ButtonRenderer buttonRenderer = new ButtonRenderer();
    tcm.getColumn(column).setCellRenderer(buttonRenderer);
    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
    tcm.getColumn(column).setCellEditor(buttonEditor);
    // ensure the table rows, columns have enough room for buttons
    table.setRowHeight(sample.getPreferredSize().height);
    table.getColumnModel().getColumn(column)
            .setPreferredWidth(sample.getPreferredSize().width);
#else
    table->setItemDelegateForColumn(column, new PushButtonDelegate(this));
#endif
}

/*synchronized*/ /*public*/ void AutomatTableDataModel::dispose() {
    AutomatSummary::instance()->removePropertyChangeListener((PropertyChangeListener*)this);
 //disconnect(AutomatSummary::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}
