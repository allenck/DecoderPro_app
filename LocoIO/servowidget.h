#ifndef SERVOWIDGET_H
#define SERVOWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QToolButton>
#include <QSpinBox>
#include <QLabel>
#include "locoiodata.h"

namespace Ui {
class ServoWidget;
}

class ServoWidget : public QWidget
{
 Q_OBJECT
    
public:
 explicit ServoWidget(LocoIOData* data, /*LnPacketizer* packetizer*/LnTrafficController* tc,  QWidget *parent = 0);
 ~ServoWidget();
 void set4PositionServo(bool bSet);
 int getColumn(int w, QPoint pt);
public slots:
 void retranslateControls();
private:
 Ui::ServoWidget *ui;
 QList<QRadioButton*> NotUsedButtons;
 QList<QRadioButton*> ServoButtons;
 QList<QToolButton*> TestButtons;
 QList<QToolButton*> CenterButtons;
 QList<QSpinBox*> Pos1SpinBoxes;
 QList<QSpinBox*> Pos2SpinBoxes;
 QList<QSpinBox*> SpeedSpinBoxes;
 QList<QLabel*> Pos1Labels;
 QList<QLabel*> Pos2Labels;
 LocoIOData* data;
 bool bHexDisplay;
 int nbrFormat;
 QString nbrPrefix;
 bool b4PositionServo;
 void validateValues(int iServo);
 //LnPacketizer* packetizer;
 LnTrafficController* tc;
 bool bSetting;
 QWidget* parent;
 void setFields(int iServo);

public slots:
 void onSVChanged(int channel, int iOld, int iNew, QString ss);
 void setName(int, QString);

private slots:
 void OnRbNotUsed_toggled(int);
 void OnRbServo_toggled(int);
 void OnTestButton_clicked(int);
 void OnCenterButton_clicked(int);
 void OnPos1_valueChanged(int);
 void OnPos2_valueChanged(int);
 void OnSpeed_valueChanged(int);
 void onPos1Changed(int channel, int iOld, int iNew, QString ss);
 void onPos2Changed(int channel, int iOld, int iNew, QString ss);
 void onSpeedChanged(int channel, int iOld, int iNew, QString ss);

};

#endif // SERVOWIDGET_H
