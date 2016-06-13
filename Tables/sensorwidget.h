#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QWidget>
#include "sensortablewidget.h"

namespace Ui {
class SensorWidget;
}

class SensorTableAction;
class SensorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SensorWidget(QWidget *parent = 0);
    ~SensorWidget();
public slots:
    void setDefaults_triggered();
private slots:
    void on_chkShowDebounceInfo_toggled(bool bState);
    void on_btnAdd_clicked();

private:
    Ui::SensorWidget *ui;
    SensorTableWidget * tableWidget1;
    SensorTableWidget * tableWidget2;
    QList<SensorTableWidget*> widgets;
    SensorTableAction* action;
protected:
    /*protected*/ void setDefaultDebounce(QWidget* _who);

};

#endif // SENSORWIDGET_H
