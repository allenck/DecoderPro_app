#ifndef LROUTEWIDGET_H
#define LROUTEWIDGET_H

#include <QWidget>

namespace Ui {
class LRouteWidget;
}

class QSignalMapper;
class LBeanTableDataModel;
class LRouteTableAction;
class LRouteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LRouteWidget(QWidget *parent = 0);
    ~LRouteWidget();
public slots:
    //void on_editMapper_triggered(int);
    void on_btnAdd_clicked();
private:
    Ui::LRouteWidget *ui;
    LRouteTableAction* lrta;
    LBeanTableDataModel* model;
};

#endif // LROUTEWIDGET_H
