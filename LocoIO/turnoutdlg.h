#ifndef TURNOUTDLG_H
#define TURNOUTDLG_H

#include <QDialog>
#include "locoiodata.h"

namespace Ui {
class TurnoutDlg;
}

class TurnoutDlg : public QDialog
{
 Q_OBJECT
    
public:
 explicit TurnoutDlg(LocoIOData* data, int channel, QWidget *parent = 0);
 ~TurnoutDlg();
 int getV1();
 int getV2();
private:
 Ui::TurnoutDlg *ui;
 int opCode, v1,  v2;
 int channel;
 LocoIOData* data;
private slots:
 void on_chkDS54Aux_toggled(bool bChecked);
 void on_btnOK_clicked();
 void on_btnCancel_clicked();
 void on_sbAddr_valueChanged(int value);
 void on_chkInputHigh_toggled(bool bChecked);
 void on_chkOutputOn_toggled(bool bChecked);
 void on_chkClosedOn_toggled(bool bChecked);
};

#endif // TURNOUTDLG_H
