#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QDialog>
#include "lighttablewidget.h"
#include "libtables_global.h"

namespace Ui {
class LightWidget;
}

class AddEditLightDialog;
class LIBTABLESSHARED_EXPORT LightWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LightWidget(QWidget *parent = 0);
    ~LightWidget();

private:
    Ui::LightWidget *ui;
    LightTableWidget* tableWidget1;
    LightTableWidget* tableWidget2;
    AddEditLightDialog* dlg;
private slots:
 void on_btnAdd_clicked();

};

#endif // LIGHTWIDGET_H
