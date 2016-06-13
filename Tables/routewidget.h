#ifndef ROUTEWIDGET_H
#define ROUTEWIDGET_H

#include <QDialog>
#include "libtables_global.h"
#include "route.h"
#include "defaultroutemanager.h"
#include <QCheckBox>

namespace Ui {
class RouteWidget;
}

class RouteTableAction;
class DefaultRouteManager;
class  RouteWidget : public QDialog
{
    Q_OBJECT

public:
    explicit RouteWidget(QWidget *parent = 0);
    ~RouteWidget();

private:
    Ui::RouteWidget *ui;
    QVector<DefaultRoute*> rows;
    DefaultRouteManager* mgr;
    void updateRow(int row, DefaultRoute* r);
    QSignalMapper* deleteMapper;
    QSignalMapper* editMapper;
    QSignalMapper* setMapper;
    RouteTableAction* act;
    Logger* log;
    bool bLoading;
private slots:
    void on_btnAdd_clicked();
    void propertyChange(PropertyChangeEvent*);
    void on_newRouteCreated(Route* r);
    void on_tableWidget_cellChanged(int,int);
    void on_setMapper_clicked(int);
    void on_deleteMapper_clicked(int);
    void on_editMapper_clicked(int);
    void on_beanDeleted(NamedBean* bean);

};

#endif // ROUTEWIDGET_H
