#ifndef REGISTERSWIDGET_H
#define REGISTERSWIDGET_H

#include <QWidget>
#include "locoiodata.h"
#include <QLineEdit>

namespace Ui {
class RegistersWidget;
}

class RegistersWidget : public QWidget
{
 Q_OBJECT
 Q_ENUMS(portType)
public:
 enum portType
 {
  NORMAL =0,
  SPECIAL =1,
  SERVO =2,
  BOOSTER_IN =3,
  BOOSTER_OUT =4
 };

 explicit RegistersWidget(LocoIOData* data, int port, portType type, QWidget *parent = 0);
 ~RegistersWidget();
 void setValues();
 bool displayFormat();
 void setPortType(portType type);

signals:
 void name(int, QString);

public slots:
 void retranslateControls();
// void setServo(bool bServo);
// void setSpecialPort();

private:
 Ui::RegistersWidget *ui;
 LocoIOData* data;
 int port;
 int channel;
 int decodeText(QLineEdit *ctl);
 bool bHexDisplay;
 int nbrFormat;
 QString nbrPrefix;
 //bool bServo;
 bool checkDups(int iServo, int thisAddr);
 //bool bSpecialPorts;
 //void checkSpecialPorts(int channel, int value);
 bool bAllowEdit;
 portType type;
 QList<int> validNormalCfg;
 int iState;
 bool bSetting;
 void labelCheck(int channel);


private slots:
 void on_btnRead_clicked();
 void on_btnWrite_clicked();
 void on_edAddr_editingFinished();
 void on_edCfg_editingFinished();
 void on_edVal1_editingFinished();
 void on_edVal2_editingFinished();
 void onPropertyChange(QString,QVariant,QVariant);
 void onAddrChanged(int channel, int iOld, int iNew, QString ss);
 void onSVChanged(int channel, int iOld, int iNew, QString ss);
 void onV1Changed(int channel, int iOld, int iNew, QString ss);
 void onV2Changed(int channel, int iOld, int iNew, QString ss);
 void onServoValuesChanged(int iServo, int iOld, int iNew, QString ss);
 void setHexDisplay(bool bHex);
 void onAllowEdit(bool bChecked);
 void on_btnEditVal_clicked();
 void OnIOComplete(QList<int>* = NULL);
 void setSpecialPort();
};

#endif // REGISTERSWIDGET_H
