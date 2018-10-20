#ifndef BOOSTEROUTPUTWIDGET_H
#define BOOSTEROUTPUTWIDGET_H

#include <QWidget>
#include "locoiodata.h"

namespace Ui {
class BoosterOutputWidget;
}

class BoosterOutputWidget : public QWidget
{
 Q_OBJECT
    
public:
 explicit BoosterOutputWidget(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc, QWidget *parent = 0);
 ~BoosterOutputWidget();
public slots:
 void retranslateControls();
private:
 Ui::BoosterOutputWidget *ui;
 LocoIOData* data;
 int port;
 int channel;
 void setValues(QString ss);
 void resetControls();
 bool bSettingValues;
 //LnPacketizer* packetizer;
 LnTrafficController* tc;

private slots:
 void on_rb1On_toggled(bool bChecked);
 void on_rb1Off_toggled(bool bChecked);
 void on_rb2On_toggled(bool bChecked);
 void on_rb2Off_toggled(bool bChecked);
 void onSVChanged(int channel, int iOld, int iNew,QString ss);
 void on_tbPower_clicked();
};

#endif // BOOSTEROUTPUTWIDGET_H
