#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QWidget>
#include "blockmanager.h"
#include <QComboBox>
#include <QSignalMapper>

namespace Ui {
class BlockWidget;
}

class BlockWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit BlockWidget(QWidget *parent = 0);
    ~BlockWidget();
private slots:
//    void propertyChange(PropertyChangeEvent* e);
//    void on_chkInches_toggled(bool bState);
//    void on_newBlockCreated(Block*);
//    void on_tableWidget_cellChanged(int row, int col);
//    void on_btnAdd_clicked();
//    void on_deleteMapper_clicked(QObject*);
//    void on_curvatureMapper_indexChanged(QObject*);
//    void on_sensorMapper_indexChanged(QObject*);
//    void on_chkUseCurrentMapper_toggled(QObject*);
//    void on_chkPermissiveMapper_toggled(QObject*);
//    void on_speedMapper_indexChanged(QObject*);

private:
    Ui::BlockWidget *ui;
    BlockManager* mgr;
//    QComboBox* cbSensor(QString sensorName);
//    void updateRow(int row, Block* b);
//    QSignalMapper* deleteMapper;
//    QSignalMapper* curvatureMapper;
//    QSignalMapper* sensorMapper;
//    QSignalMapper* chkUseCurrentMapper;
//    QSignalMapper* chkPermissiveMapper;
//    QSignalMapper* speedMapper;
//QVector<Block*> rows;
};

#endif // BLOCKWIDGET_H
