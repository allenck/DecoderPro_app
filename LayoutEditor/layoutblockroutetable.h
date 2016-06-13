#ifndef LAYOUTBLOCKROUTETABLE_H
#define LAYOUTBLOCKROUTETABLE_H

#include <QWidget>
//#include <QTableView>
//#include <QScrollArea>

class JTable;
class QSortFilterProxyModel;
class LayoutBlockRouteTableModel;
class LayoutBlockNeighbourTableModel;
class LayoutBlockThroughPathsTableModel;
class LayoutBlock;
class LayoutBlockRouteTable : public QWidget
{
    Q_OBJECT
public:
    //explicit LayoutBlockRouteTable(QWidget *parent = 0);
    /*public*/ LayoutBlockRouteTable(bool editable, LayoutBlock* block, QWidget *parent = 0);
    /*public*/ JTable* getTable();
    /*public*/ QSortFilterProxyModel* getModel();
    /*public*/ JTable* getNeighbourTable();
    /*public*/ QSortFilterProxyModel* getNeighbourModel();
    /*public*/ void dispose();
signals:

public slots:
private:
    LayoutBlockRouteTableModel*    dataModel;
    LayoutBlockNeighbourTableModel* neighbourDataModel;
    QSortFilterProxyModel*        neighbourSorter;
    JTable*		    neighbourDataTable;
//    QScrollArea* 		neighbourDataScroll;
    QSortFilterProxyModel*        sorter;
    JTable*		    dataTable;
//    QScrollArea* 		dataScroll;

    LayoutBlockThroughPathsTableModel* throughPathsDataModel;
    QSortFilterProxyModel*         throughPathsSorter;
    JTable*			throughPathsDataTable;
//    QScrollArea* 		throughPathsDataScroll;


};

#endif // LAYOUTBLOCKROUTETABLE_H
