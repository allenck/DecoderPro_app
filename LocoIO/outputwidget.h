#ifndef OUTPUTWIDGET_H
#define OUTPUTWIDGET_H

#include <QWidget>
#include "locoiodata.h"
#include <QButtonGroup>

namespace Ui {
class OutputWidget;
}

class OutputWidget : public QWidget
{
 Q_OBJECT
    
public:
 explicit OutputWidget(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc, QButtonGroup* group, QWidget *parent = 0);
 ~OutputWidget();
 void setValues(QString ss);
 void resetControls();
public slots:
 void retranslateControls();
private:
    Ui::OutputWidget *ui;
    LocoIOData* data;
    int port;
    int channel;
    //LnPacketizer* packetizer;
    LnTrafficController* tc;
    bool bSettingValues;
private slots:
 void on_btnTest_clicked();
 void onSVChanged(int channel, int iOld, int iNew,QString ss);
 void on_rbBlockOccupancy_toggled(bool bChecked);
 void on_chkBlinking_toggled(bool bChecked);
 void on_rb1On_toggled(bool bChecked);
 void on_rb1Off_toggled(bool bChecked);
 void on_rb2On_toggled(bool bChecked);
 void on_rb2Off_toggled(bool bChecked);
 void on_chk4WayPort_toggled(bool bChecked);
 void on_rb1SoftReset_toggled(bool bChecked);
 void on_rb1HardReset_toggled(bool bChecked);
 void on_rb2SoftReset_toggled(bool bChecked);
 void on_rb2HardReset_toggled(bool bChecked);

};

#endif // OUTPUTWIDGET_H
