#ifndef SIGNALMASTWIDGET_H
#define SIGNALMASTWIDGET_H

#include <QDialog>
#include "logger.h"
#include <QComboBox>
#include <QSignalMapper>
#include <QCheckBox>
#include "libtables_global.h"

namespace Ui {
class SignalMastWidget;
}

class DefaultSignalMastManager;
class AbstractSignalMast;\
class AbstractSignalMast;
class PropertyChangeEvent;
class LIBTABLESSHARED_EXPORT SignalMastWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SignalMastWidget(QWidget *parent = 0);
    ~SignalMastWidget();

private:
    Ui::SignalMastWidget *ui;
    DefaultSignalMastManager* mgr;
    void fillTable();
    QVector<AbstractSignalMast*> rows;
    void updateRows(int row, AbstractSignalMast* s);
    Logger* log;
    QSignalMapper* aspectMapper;
    QSignalMapper* deleteMapper;
    QSignalMapper* editMapper;
    QSignalMapper* editLogicMapper;
    QSignalMapper* litMapper;
    QSignalMapper* heldMapper;
private slots:
    void on_newSignalMastCreated(AbstractSignalMast*);
    void on_tableWidget_cellChanged(int,int);
    void propertyChange(PropertyChangeEvent *e);
    void on_btnAdd_clicked();
    void on_aspectMapper_signaled(int);
    void on_deleteMapper_signaled(int);
    void on_editMapper_signaled(int);
    void on_editLogicMapper_signaled(int);
    void on_litMapper_signaled(int);
    void on_heldMapper_signaled(int);
    friend class PropertyChangeSupport;
};

#endif // SIGNALMASTWIDGET_H
