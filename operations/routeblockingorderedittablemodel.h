#ifndef OPERATIONS_ROUTEBLOCKINGORDEREDITTABLEMODEL_H
#define OPERATIONS_ROUTEBLOCKINGORDEREDITTABLEMODEL_H

#include <abstracttablemodel.h>
#include "route.h"
#include "routeblockingordereditframe.h"

class Logger;
namespace Operations {

 class RouteBlockingOrderEditFrame;
class RouteBlockingOrderEditTableModel : public AbstractTableModel, public PropertyChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
public:
    explicit RouteBlockingOrderEditTableModel(QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    /*public*/  QString  getColumnClass(int col) const override;
    /*public*/  void dispose();

 public slots:
    /*public*/  void propertyChange(PropertyChangeEvent* e)override;

private:
    Logger* log;
    /*private*/ static /*final*/const int ID_COLUMN = 0;
    /*private*/ static /*final*/const int NAME_COLUMN = ID_COLUMN + 1;
    /*private*/ static /*final*/const int TRAIN_DIRECTION_COLUMN = NAME_COLUMN + 1;
    /*private*/ static /*final*/const int UP_COLUMN = TRAIN_DIRECTION_COLUMN + 1;
    /*private*/ static /*final*/const int DOWN_COLUMN = UP_COLUMN + 1;

    /*private*/ static /*final*/const int HIGHEST_COLUMN = DOWN_COLUMN + 1;

    /*private*/ JTable* _table;
    /*private*/ Route* _route;
    /*private*/ RouteBlockingOrderEditFrame* _frame = nullptr;
    QList<RouteLocation*> _blockingOrderList = QList<RouteLocation*>();
    /*private*/ void updateList();
    /*private*/ void initTable(JTable* table);
    /*private*/ void moveUpRouteLocation(RouteLocation* rl) ;
    /*private*/ void moveDownRouteLocation(RouteLocation* rl);
    /*private*/ void removePropertyChangeRouteLocations();

    QObject* pself() override {return (QObject*)this;}

protected:
    /*protected*/ void initTable(RouteBlockingOrderEditFrame* frame, JTable* table, Route* route);

    friend class RouteBlockingOrderEditFrame;
};

} // namespace Operations

#endif // OPERATIONS_ROUTEBLOCKINGORDEREDITTABLEMODEL_H
