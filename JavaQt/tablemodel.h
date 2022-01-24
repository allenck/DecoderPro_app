#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QString>
#include <QObject>
#include "tablemodellistener.h"
#include <QAbstractTableModel>
#include "javaqt_global.h"

class TableModelListener;
class JAVAQTSHARED_EXPORT TableModel : public QAbstractTableModel
{
 Q_OBJECT

 public:
 TableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}
 /**
      * Returns the number of rows in the model. A
      * <code>JTable</code> uses this method to determine how many rows it
      * should display.  This method should be quick, as it
      * is called frequently during rendering.
      *
      * @return the number of rows in the model
      * @see #getColumnCount
      */
     /*public*/ virtual int getRowCount() const = 0;

     /**
      * Returns the number of columns in the model. A
      * <code>JTable</code> uses this method to determine how many columns it
      * should create and display by default.
      *
      * @return the number of columns in the model
      * @see #getRowCount
      */
     /*public*/ virtual int getColumnCount() const = 0;

     /**
      * Returns the name of the column at <code>columnIndex</code>.  This is used
      * to initialize the table's column header name.  Note: this name does
      * not need to be unique; two columns in a table can have the same name.
      *
      * @param   columnIndex     the index of the column
      * @return  the name of the column
      */
     /*public*/ virtual QString getColumnName(int /*columnIndex*/) const =0;

     /**
      * Returns the most specific superclass for all the cell values
      * in the column.  This is used by the <code>JTable</code> to set up a
      * default renderer and editor for the column.
      *
      * @param columnIndex  the index of the column
      * @return the common ancestor class of the object values in the model.
      */
      /*public*/ virtual /*Class<?>*/ QString getColumnClass(int /*columnIndex*/) const = 0;

     /**
      * Returns true if the cell at <code>rowIndex</code> and
      * <code>columnIndex</code>
      * is editable.  Otherwise, <code>setValueAt</code> on the cell will not
      * change the value of that cell.
      *
      * @param   rowIndex        the row whose value to be queried
      * @param   columnIndex     the column whose value to be queried
      * @return  true if the cell is editable
      * @see #setValueAt
      */
     /*public*/ virtual bool isCellEditable(int /*rowIndex*/, int /*columnIndex*/) const {return false;}

     /**
      * Returns the value for the cell at <code>columnIndex</code> and
      * <code>rowIndex</code>.
      *
      * @param   rowIndex        the row whose value is to be queried
      * @param   columnIndex     the column whose value is to be queried
      * @return  the value Object at the specified cell
      */
     /*public*/ virtual QVariant getValueAt(int /*rowIndex*/, int /*columnIndex*/) const =0;

     /**
      * Sets the value in the cell at <code>columnIndex</code> and
      * <code>rowIndex</code> to <code>aValue</code>.
      *
      * @param   aValue           the new value
      * @param   rowIndex         the row whose value is to be changed
      * @param   columnIndex      the column whose value is to be changed
      * @see #getValueAt
      * @see #isCellEditable
      */
     /*public*/ virtual void setValueAt(QVariant /*aValue*/, int /*rowIndex*/, int /*columnIndex*/) {}

     /**
      * Adds a listener to the list that is notified each time a change
      * to the data model occurs.
      *
      * @param   l               the TableModelListener
      */
     /*public*/ virtual void addTableModelListener(TableModelListener* /*l*/) {}

     /**
      * Removes a listener from the list that is notified each time a
      * change to the data model occurs.
      *
      * @param   l               the TableModelListener
      */
     /*public*/ virtual void removeTableModelListener(TableModelListener* /*l*/) {}
};

#endif // TABLEMODEL_H
