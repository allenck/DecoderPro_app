#ifndef SIGNALGROUPSWIDGET_H
#define SIGNALGROUPSWIDGET_H

#include <QDialog>

namespace Ui {
class SignalGroupsWidget;
}

class SignalGroupTableAction;
class SignalGroupsWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SignalGroupsWidget(QWidget *parent = 0);
    ~SignalGroupsWidget();

private:
    Ui::SignalGroupsWidget *ui;
    SignalGroupTableAction* sgta;
    QList<int> buttonMap;
private slots:
    void on_editMapper_triggered(int);
    void on_deleteMapper_triggered(int row);
};

#endif // SIGNALGROUPSWIDGET_H
