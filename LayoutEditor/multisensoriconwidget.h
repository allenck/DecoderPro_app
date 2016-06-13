#ifndef MULTISENSORICONWIDGET_H
#define MULTISENSORICONWIDGET_H

#include <QWidget>
#include <QDrag>

namespace Ui {
class MultiSensorIconWidget;
}

class PropertyChangeEvent;
class AbstractSensorManager;
class Sensor;
class NamedIcon;
class SensorEntryWidget;
class MultiSensorIconEntry;
class QSignalMapper;
class Editor;
class MultiSensorIcon;
class AbstractSensor;
class MultiSensorIconWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MultiSensorIconWidget(MultiSensorIcon* icon, Editor* editor,QWidget *parent = 0);
    ~MultiSensorIconWidget();
    void setIcon(MultiSensorIcon* icon);

    bool on_btnChangeIcon_clicked();

public slots:
    void on_tableWidget_cellClicked(int row, int col);
    void on_entryChanged(int, MultiSensorIconEntry*);
    void on_pbAddIcon_clicked();
    void on_rbUpDown_toggled(bool);
    void on_deleteRequested(int);
    void on_newSensorCreated(AbstractSensorManager*,Sensor*);
    void propertyChange(PropertyChangeEvent*);
signals:
    void iconValid(bool bValid);
private:
    Ui::MultiSensorIconWidget *ui;
    void fillSensorTable();
    QList<AbstractSensor*> rows;
    MultiSensorIcon* _icon;
    Editor* editor;
    //QSignalMapper* mapper;
    QList<SensorEntryWidget*> widgets;
    bool bValid;
};

#endif // MULTISENSORICONWIDGET_H
