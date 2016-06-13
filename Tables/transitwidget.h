#ifndef TRANSITWIDGET_H
#define TRANSITWIDGET_H

#include <QWidget>

namespace Ui {
class TransitWidget;
}

class BeanTableDataModel;
class TransitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransitWidget(QWidget *parent = 0);
    ~TransitWidget();

private:
    Ui::TransitWidget *ui;
    BeanTableDataModel* model;
};

#endif // TRANSITWIDGET_H
