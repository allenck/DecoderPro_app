#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include <QWidget>
#include "defaultmemorymanager.h"
#include <QSignalMapper>
#include "abstractmemory.h"

namespace Ui {
class MemoryWidget;
}

class MemoryWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MemoryWidget(QWidget *parent = 0);
    ~MemoryWidget();
public slots:
    void on_btnAdd_clicked();
    void propertyChange(PropertyChangeEvent* e);
    void on_newMemoryCreated(Memory*);
    void on_tableWidget_cellChanged(int, int);
    void on_deleteMapper_signaled(int);

private:
    Ui::MemoryWidget *ui;
    DefaultMemoryManager* mgr;
    QSignalMapper* deleteMapper;
    QVector<AbstractMemory*> rows;
    void updateRow(int row, AbstractMemory* m);

};

#endif // MEMORYWIDGET_H
