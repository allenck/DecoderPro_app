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
 explicit SpecialPort(LocoIOData* data, int port, QWidget *parent = 0);
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
 bool bSettingValues;
private slots:
 void onSvChanged(int channel, int iOld, int iNew, QString ss);
};

#endif // SPECIALPORT_H
