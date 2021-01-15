#ifndef ROUTETURNOUTMODEL_H
#define ROUTETURNOUTMODEL_H
#include "routeoutputmodel.h"
#include "abstractrouteaddeditframe.h"

class RouteTurnoutModel : public RouteOutputModel
{
    Q_OBJECT
public:
    enum COLUMNS
    {
     SNAME_COLUMN = 0,
     UNAME_COLUMN = 1,
     INCLUDE_COLUMN = 2,
     STATE_COLUMN = 3
    };
    RouteTurnoutModel(AbstractRouteAddEditFrame * routeAddFrame, QObject* parent = nullptr);
    int rowCount(const QModelIndex &parent) const;
    //int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const override;
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    //Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) override;
    void reset();

private:
    static Logger* log;
    /*private*/ /*final*/ AbstractRouteAddEditFrame* routeAddFrame;

    friend class RouteAddFrame;
};


#endif // ROUTETURNOUTMODEL_H
