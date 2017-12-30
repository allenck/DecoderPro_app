#ifndef TABLECOLUMNMODELEVENT_H
#define TABLECOLUMNMODELEVENT_H

class TableColumnModel;
class TableColumnModelEvent
{
public:
 TableColumnModelEvent(TableColumnModel* source, int from, int to);
 /*public*/ int getFromIndex() ;
 /*public*/ int getToIndex();

protected:
 //  Instance Variables
 //

     /** The index of the column from where it was moved or removed */
     /*protected*/ int       fromIndex;

     /** The index of the column to where it was moved or added */
     /*protected*/ int       toIndex;

};

#endif // TABLECOLUMNMODELEVENT_H
