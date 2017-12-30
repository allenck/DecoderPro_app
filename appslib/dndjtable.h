#ifndef DNDJTABLE_H
#define DNDJTABLE_H
#include "jtable.h"
#include "javaqt_global.h"
class TableModel;
class DataFlavor;
class JAVAQTSHARED_EXPORT DnDJTable : public JTable
{
 Q_OBJECT
public:
 //explicit DnDJtable(QWidget *parent = 0);
 ///*public*/ static /*final*/ DataFlavor TABLECELL_FLAVOR; //= new DataFlavor(
 DnDJTable(QAbstractItemModel* model, QList<int> skipCols, QWidget *parent = 0);

signals:

public slots:

private:
 QPoint _dropPoint;
 QList<int> _skipCols;// = new int[0];

};

#endif // DNDJTABLE_H
