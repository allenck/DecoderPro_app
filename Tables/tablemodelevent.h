#ifndef TABLEMODELEVENT_H
#define TABLEMODELEVENT_H
#include "tablemodel.h"
#include "eventobject.h"

class TableModel;
class LIBPR3SHARED_EXPORT TableModelEvent : public QObject
{
    Q_OBJECT
public:
    //explicit TableModelEvent(QObject *parent = 0);
    /** Identifies the addtion of new rows or columns. */
    /*public*/ static /*final*/ const int INSERT =  1;
    /** Identifies a change to existing data. */
    /*public*/ static /*final*/ int const UPDATE =  0;
    /** Identifies the removal of rows or columns. */
    /*public*/ static /*final*/ int const _DELETE = -1;

    /** Identifies the header row. */
    /*public*/ static /*final*/ const int HEADER_ROW = -1;

    /** Specifies all columns in a row or rows. */
    /*public*/ static /*final*/ const int ALL_COLUMNS = -1;
    /*public*/ TableModelEvent(TableModel* source, QObject *parent = 0);
    /*public*/ TableModelEvent(TableModel* source, int row, QObject *parent = 0);
    /*public*/ TableModelEvent(TableModel* source, int firstRow, int lastRow, QObject* parent = 0);
    /*public*/ TableModelEvent(TableModel* source, int firstRow, int lastRow, int column, QObject* parent = 0);
    /*public*/ TableModelEvent(TableModel* source, int firstRow, int lastRow, int column, int type, QObject* parent = 0);
#if 0
    /*public*/ int getFirstRow();
    /*public*/ int getLastRow();
    /*public*/ int getColumn();
    /*public*/ int getType();
#endif
signals:

public slots:
private:
    /*private*/ void common(TableModel* source, int firstRow, int lastRow, int column, int type);

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
