#ifndef SIGNALMASTLOGICWIDGET_H
#define SIGNALMASTLOGICWIDGET_H

#include <QDialog>
#include <QSignalMapper>
#include "logger.h"
#include "../Signal/defaultsignalmastlogic.h"

namespace Ui {
class SignalMastLogicWidget;
}

class DefaultSignalMastLogicManager;
class DefaultSignalMastLogic;

class SignalMastLogicWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SignalMastLogicWidget(QWidget *parent = 0);
    ~SignalMastLogicWidget();

private:
    Ui::SignalMastLogicWidget *ui;
    DefaultSignalMastLogicManager* mgr;
    void fillTable();
    QVector<DefaultSignalMastLogic*> rows;
    void updateRows(int row, DefaultSignalMastLogic* s);
    Logger* log;
    QList<QHash<SignalMastLogic*, SignalMast*> > signalMastLogicList;// = null;
    /*public*/ SignalMast* getDestMastFromRow(int row);
    QList<SignalMastLogic*> logicList;
    QSignalMapper* deleteMapper;
    QSignalMapper* enabledMapper;
    QSignalMapper* editMapper;

private slots:
    void on_newSignalMastLogicCreated(SignalMastLogic*);
    void on_tableWidget_cellChanged(int row, int col);
    void propertyChange(PropertyChangeEvent *e);
    void on_deleteMapper_signaled(int);
    void on_enabledMapper_signaled(int);
    void on_editMapper_signaled(int);
    void on_btnAdd_clicked();
protected:
    /*protected*/ /*synchronized*/ void updateNameList();

};

#endif // SIGNALMASTLOGICWIDGET_H
