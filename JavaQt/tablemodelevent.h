#ifndef TABLEMODELEVENT_H
#define TABLEMODELEVENT_H
#include "eventobject.h"

class TableModel;
class TableModelEvent : public EventObject
{
public:
 TableModelEvent();
 /** Identifies the addition of new rows or columns. */
 /*public*/static /*final*/ int INSERT;// =  1;
 /** Identifies a change to existing data. */
 /*public*/static /*final*/ int UPDATE;// =  0;
 /** Identifies the removal of rows or columns. */
 /*public*/static /*final*/ int DELETE;// = -1;

 /** Identifies the header row. */
 /*public*/static /*final*/ int HEADER_ROW;// = -1;

 /** Specifies all columns in a row or rows. */
 /*public*/static /*final*/ int ALL_COLUMNS;// = -1;

 /**
  *  This row of data has been updated.
  *  To denote the arrival of a completely new table with a different structure
  *  use <code>HEADER_ROW</code> as the value for the <code>row</code>.
  *  When the <code>JTable</code> receives this event and its
  *  <code>autoCreateColumnsFromModel</code>
  *  flag is set it discards any TableColumns that it had and reallocates
  *  default ones in the order they appear in the model. This is the
  *  same as calling <code>setModel(TableModel)</code> on the <code>JTable</code>.
  */
 /*public*/ TableModelEvent(TableModel* source);
 /*public*/ TableModelEvent(TableModel* source, int row);
 /*public*/ TableModelEvent(TableModel* source, int firstRow, int lastRow);
 /*public*/ TableModelEvent(TableModel* source, int firstRow, int lastRow, int column);
 /*public*/ TableModelEvent(TableModel* source, int firstRow, int lastRow, int column, int type);
 /*public*/int getFirstRow();
 /*public*/int getLastRow();
 /*public*/int getColumn();
 /*public*/int getType();

private:
 void common(TableModel* source, int firstRow, int lastRow, int column, int type);
protected:
//
//  Instance Variables
//

 /*protected*/ int       type;
 /*protected*/ int       firstRow;
 /*protected*/ int       lastRow;
 /*protected*/ int       column;

};

#endif // TABLEMODELEVENT_H
