#ifndef SENSORENTRYWIDGET_H
#define SENSORENTRYWIDGET_H

#include <QWidget>

namespace Ui {
class SensorEntryWidget;
}

class MultiSensorIcon;
class MultiSensorIconEntry;
class NamedIcon;
class SensorEntryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SensorEntryWidget(int iconNum, MultiSensorIconEntry* _entry,  QWidget *parent = 0);
    ~SensorEntryWidget();
    int iconNum();
    NamedIcon* icon();
    void setIconNum(int iconNum);
    QString sensor();
    MultiSensorIconEntry* entry();
signals:
    void entryChanged(int iconNum, MultiSensorIconEntry* _entry);
    void deleteRequested(int iconNum);
private:
    Ui::SensorEntryWidget *ui;
    NamedIcon* _icon;
    QString _sensor;
    int _iconNum;
    MultiSensorIconEntry* _entry;
private slots:
    void on_edSensor_textChanged(QString text);
    void on_iconChanged(NamedIcon* icon);
    void on_btnDelete_clicked();
};

#endif // SENSORENTRYWIDGET_H
