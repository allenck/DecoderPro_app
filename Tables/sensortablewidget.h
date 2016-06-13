#ifndef SENSORTABLEWIDGET_H
#define SENSORTABLEWIDGET_H

#include <QWidget>
#include "proxysensormanager.h"
#include <QPushButton>
#include <QCheckBox>
#include "QSignalMapper"

namespace Ui {
class SensorTableWidget;
}

class SensorTableAction;
//class AbstractSensor;
class SensorTableWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SensorTableWidget(int iMgr, QWidget *parent = 0);
    ~SensorTableWidget();
 void showDebounceInfo(bool bState);

public slots:
// void propertyChange(PropertyChangeEvent* e);
// void on_newSensorCreated(AbstractSensorManager*,Sensor*);
// void on_tableWidget_cellChanged(int, int);
// void on_stateMapper_signaled(int row);
// void on_deleteMapper_signaled(int);
// void on_invertedMapper_signaled(int);
// void on_delayMapper_signaled(int);

private:
 Ui::SensorTableWidget *ui;
// bool bInternal;
 ProxySensorManager* mgr;
// void fillTable();
// void fillTable(/*AbstractSensorManager* sMgr*/QStringList list);
// QVector<AbstractSensor*> rows;
// void updateRows(int row, AbstractSensor* s);
// QSignalMapper* stateMapper;
// QSignalMapper* deleteMapper;
// QSignalMapper* invertedMapper;
// QSignalMapper* delayMapper;
 int iMgr;
 SensorTableAction* action;
};

#endif // SENSORTABLEWIDGET_H
