#ifndef TURNOUTTABLEWIDGET_H
#define TURNOUTTABLEWIDGET_H

#include <QWidget>
#include "proxyturnoutmanager.h"
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QSignalMapper>
#include "proxysensormanager.h"

namespace Ui {
class TurnoutTableWidget;
}

class JFrame;
class TurnoutTableWidget : public QWidget
{
    Q_OBJECT
    
public:
  enum COLUMNS
  {
   SYSNAMECOL  = 0,
   USERNAMECOL = 1,
   VALUECOL = 2,
   COMMENTCOL = 3,
   DELETECOL = 4,
   INVERTCOL = 5,
   LOCKCOL = INVERTCOL+1, //6
   KNOWNCOL = LOCKCOL+1,  //7
   MODECOL = KNOWNCOL+1,  //8
   SENSOR1COL = MODECOL+1, //9
   SENSOR2COL = SENSOR1COL+1, //10
   OPSONOFFCOL = SENSOR2COL+1, //11
   OPSEDITCOL = OPSONOFFCOL+1, //12
   LOCKOPRCOL = OPSEDITCOL+1,  //13
   LOCKDECCOL = LOCKOPRCOL+1,  //14
   STRAIGHTCOL = LOCKDECCOL+1, //15
   DIVERGCOL = STRAIGHTCOL+1   //16
  };

 explicit TurnoutTableWidget(int mgrIndex, QWidget *parent = 0);
 ~TurnoutTableWidget();
 void showFeedbackInfo(bool bVisible);
 void showLockInformation(bool bVisible);
 void showTurnoutSpeedDetails(bool bVisible);
 /*public*/ static void updateAutomationBox(AbstractTurnout* t, QComboBox* cb);

private slots:
 void propertyChange(PropertyChangeEvent* e);
 void on_newTurnoutCreated(AbstractTurnoutManager*,Turnout* t);
 void on_tableWidget_cellChanged(int row, int col);
 void on_stateMapper_clicked(QObject*);
 void on_deleteMapper_clicked(QObject*);
 void on_editMapper_clicked(QObject*);
 void on_namedBeanDeleted(NamedBean* b);
 void on_invertedMapper_toggled(QObject*);
 void on_lockedMapper_toggled(QObject*);
 void on_modeMapper_indexChanged(QObject*);
 void on_sensor1Mapper_indexChanged(QObject*);
 void on_sensor2Mapper_indexChanged(QObject*);
 void on_automateMapper_indexChanged(QObject*);
 void on_lockModeMapper_indexChanged(QObject*);
 void on_decoderMapper_indexChanged(QObject*);
 void on_closedSpeedMapper_indexChanged(QObject*);
 void on_thrownSpeedMapper_indexChanged(QObject*);
 void /*private*/ updateSensors(PropertyChangeEvent* e);


private:
 Ui::TurnoutTableWidget *ui;
 int mgrIndex;
 void fillTable(QStringList list);
 QComboBox* cbMode(AbstractTurnout* t);
 QComboBox* cbSensor(AbstractTurnout* t, int index);
 QComboBox* cbAutomate(AbstractTurnout* t);
 QComboBox* cbSpeed(AbstractTurnout* t, bool bClosed);
 QVector<AbstractTurnout*> rows;
 void createRow(int row, AbstractTurnout* t);
 void updateRow(int row, AbstractTurnout* t);
 QSignalMapper* deleteMapper;
 QSignalMapper* editMapper;
 QSignalMapper* statemapper;
 QSignalMapper* invertedMapper;
 QSignalMapper* lockedMapper;
 QSignalMapper* modeMapper;
 QSignalMapper* sensor1Mapper;
 QSignalMapper* sensor2Mapper;
 QSignalMapper* automateMapper;
 QSignalMapper* lockModeMapper;
 QSignalMapper* decoderMapper;
 QSignalMapper* closedSpeedMapper;
 QSignalMapper* thrownSpeedMapper;
 int getLockoutMode(int row);
 /*private*/ void setTurnoutOperation(AbstractTurnout* t, QComboBox* cb);
 /*private*/ void updateClosedList();
 /*private*/ void updateThrownList();
 QVector<QString>* speedListClosed;
 QString defaultClosedSpeedText;
 QVector<QString>* speedListThrown;
 QString defaultThrownSpeedText;
 //QString useBlockSpeed;
 //QVector<QString>* _speedMap;
 ProxyTurnoutManager* turnManager;
 ProxySensorManager* sensorManager;
 Logger* log;
};

#endif // TURNOUTTABLEWIDGET_H
