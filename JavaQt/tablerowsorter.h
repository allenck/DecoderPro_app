#ifndef TABLEROWSORTER_H
#define TABLEROWSORTER_H
#include "defaultrowsorter.h"

class TableStringConverter;
class TableRowSorter : public DefaultRowSorter
{
public:
 TableRowSorter();
 /*public*/ TableRowSorter(QAbstractItemModel* model);
 /*public*/ void setModel(QAbstractItemModel* model);
 /*public*/ void setStringConverter(TableStringConverter* stringConverter);
 /*public*/ TableStringConverter* getStringConverter();
 /*public*/ Comparator/*<?>*/* getComparator(int column);
 QAbstractItemModel* sourceModel();

private:
 /*private*/ static /*final*/ Comparator* COMPARABLE_COMPARATOR;// = new ComparableComparator();
 /**
  * Underlying model.
  */
 /*private*/ QAbstractItemModel* tableModel;

 /**
  * For toString conversions.
  */
 /*private*/ TableStringConverter* stringConverter;
 QAbstractItemModel* model;

protected:
 /*protected*/ bool useToString(int column);

 friend class TableRowSorterModelWrapper;
};

/**
 * Implementation of DefaultRowSorter.ModelWrapper that delegates to a
 * TableModel.
 */
/*private*/ class TableRowSorterModelWrapper : public ModelWrapper//extends ModelWrapper<M,Integer>
{
 TableRowSorter* trs;
public:
    TableRowSorterModelWrapper(TableRowSorter* trs);
    /*public*/ QAbstractItemModel* getModel();
    /*public*/ int getColumnCount();
    /*public*/ int getRowCount();
    /*public*/ QVariant getValueAt(int row, int column);
    /*public*/ QString getStringValueAt(int row, int column);
    /*public*/ int getIdentifier(int index);
};


/*private*/ /*static*/ class ComparableComparator : public Comparator {
    //@SuppressWarnings("unchecked")
public:
    /*public*/ int compare(QObject* o1, QObject* o2);
};

#endif // TABLEROWSORTER_H
