#ifndef SIGNALHEADWIDGET_H
#define SIGNALHEADWIDGET_H

#include <QDialog>
#include <QSignalMapper>
#include "logger.h"

namespace Ui {
class SignalHeadWidget;
}

class AbstractSignalHeadManager;
class AbstractSignalHead;
class PropertyChangeEvent;
class SignalHeadTableAction;
class SignalHeadWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SignalHeadWidget(QWidget *parent = 0);
    ~SignalHeadWidget();

private:
    Ui::SignalHeadWidget *ui;
    AbstractSignalHeadManager* mgr;
    QSignalMapper* stateMapper;
    QSignalMapper* deleteMapper;
    QSignalMapper* litMapper;
    QSignalMapper* heldMapper;
    QSignalMapper* editMapper;
    void fillTable();
    QVector<AbstractSignalHead*> rows;
    void updateRows(int row, AbstractSignalHead* s);
    Logger* log;
    SignalHeadTableAction* signalHeadTableAction;
private slots:
    void on_newSignalHeadCreated(AbstractSignalHead*);
    void on_tableWidget_cellChanged(int,int);
    void on_stateMapper_signaled(int);
    void on_deleteMapper_signaled(int);
    void on_litMapper_signaled(int);
    void on_heldMapper_signaled(int);
    void propertyChange(PropertyChangeEvent *e);
    void on_editMapper_signaled(int);
    void on_btnAdd_clicked();

};

#endif // SIGNALHEADWIDGET_H
