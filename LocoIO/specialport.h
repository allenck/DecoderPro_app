#ifndef SPECIALPORT_H
#define SPECIALPORT_H

#include <QWidget>
#include "locoiodata.h"

namespace Ui {
class SpecialPort;
}

class SpecialPort : public QWidget
{
 Q_OBJECT
    
public:
 explicit SpecialPort(LocoIOData* data, int port, LnTrafficController* tc, QWidget *parent = 0);
 ~SpecialPort();
public slots:
 void retranslateControls();
 void setStatus(QString);
 void on_rbInput_toggled(bool bChecked);
 void on_rbOutput_toggled(bool bchecked);
private:
 Ui::SpecialPort *ui;
 int channel;
 LocoIOData* data;
 LnTrafficController* tc;
 bool bSettingValues;
 void resetControls();
 void setValues();

private slots:
 void onSvChanged(int channel, int iOld, int iNew, QString ss);
 void onMessageReceived(LocoNetMessage* msg, bool b);

};

#endif // SPECIALPORT_H
