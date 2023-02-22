#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include "locoiodata.h"
#include "QButtonGroup"

namespace Ui {
class InputWidget;
}

class InputWidget : public QWidget
{
 Q_OBJECT
    
public:
 explicit InputWidget(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc, QButtonGroup* group, QWidget *parent = 0);
 ~InputWidget();
 void setValues();
 void resetControls();
 void setDoubleInputEnabled(int channel, bool b);
public slots:
 void retranslateControls();
private:
    Ui::InputWidget *ui;
    int port;
    int channel;
    LocoIOData* data;
    //LnPacketizer* packetizer;
    LnTrafficController* tc;
//    bool event(QEvent *);
    bool bSettingValues;
private slots:
    void onPropertyChange(QString propertyName, QVariant oldVal, QVariant newVal);
    void onSVChanged(int channel, int iOld, int iNew,QString ss);
    void on_rbNotUsed_toggled(bool bChecked);
    void on_rbBlockDetectionActiveHigh_toggled(bool bChecked);
    void on_rbBlockDetectionActiveLow_toggled(bool bChecked);
    void on_rbToggleSwitch_toggled(bool bChecked);
    void on_rbPushButtonActiveHigh_toggled(bool bChecked);
    void on_rbPushButtonActiveLow_toggled(bool bChecked);
    void on_chkDirectControl_toggled(bool bChecked);
    void on_rbSwitchPointFeedback_toggled(bool bChecked);
    void on_rbContact1PointFeedback_toggled(bool bChecked);
    void on_rbContact2PointFeedback_toggled(bool bChecked);
    void onMessageReceived(LocoNetMessage* msg, bool b);
    void on_rbDoubleInput_toggled(bool bChecked);
    void on_chkBlockDetectionDelay_toggled(bool bChecked);
signals:
    //void isInput(int port);
};

#endif // INPUTWIDGET_H
