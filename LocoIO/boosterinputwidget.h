#ifndef BOOSTERINPUTWIDGET_H
#define BOOSTERINPUTWIDGET_H

#include <QWidget>
#include "locoiodata.h"

namespace Ui {
class BoosterInputWidget;
}

class BoosterInputWidget : public QWidget
{
    Q_OBJECT
    
public:
 explicit BoosterInputWidget(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc,QWidget *parent = 0);
 ~BoosterInputWidget();
public slots:
 void retranslateControls();

private:
 Ui::BoosterInputWidget *ui;
 int port;
 int channel;
 LocoIOData* data;
 //LnPacketizer* packetizer;
 LnTrafficController* tc;
 void setValues();
 void resetControls();
 bool bSettingValues;

private slots:
 void on_rbBlockDetectionActiveLow_toggled(bool bChecked);
 void onMessageReceived(LocoNetMessage *msg, bool b);
 void onPropertyChange(QString propertyName, QVariant oldVal, QVariant newVal);
 void onSVChanged(int channel, int iOld, int iNew,QString ss);

};

#endif // BOOSTERINPUTWIDGET_H
