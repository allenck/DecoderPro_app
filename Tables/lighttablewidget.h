#ifndef LIGHTTABLEWIDGET_H
#define LIGHTTABLEWIDGET_H

#include <QDialog>
#include "proxylightmanager.h"
#include <QSignalMapper>
#include <QCheckBox>
#include <QPushButton>

namespace Ui {
class LightTableWidget;
}

class AbstractLight;
class AbstractLightManager;
class LightTableWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LightTableWidget(bool bInternal, QWidget *parent = 0);
    ~LightTableWidget();
    /*public*/ QString getValue(AbstractLight* l);

private:
 Ui::LightTableWidget *ui;
 bool bInternal;
 ProxyLightManager* mgr;
 QVector<AbstractLight*> rows;
 QSignalMapper* stateMapper;
 QSignalMapper* deleteMapper;
 QSignalMapper* enabledMapper;
 QSignalMapper* editMapper;
 void fillTable(AbstractLightManager*);
 void newRow(int row, AbstractLight* s);
 void updateRow(int row, AbstractLight* s);

private slots:
 void on_newLightCreated(AbstractLightManager*, Light*);
 void on_tableWidget_cellChanged(int,int);
 void on_stateMapper_signaled(int);
 void on_deleteMapper_signaled(int);
 void on_enabledMapper_signaled(int);
 void on_editMapper_signaled(int);
 void propertyChange(PropertyChangeEvent *e);
friend class AddEditLightDialog;
friend class LightControlTableModel;
};

#endif // LIGHTTABLEWIDGET_H
