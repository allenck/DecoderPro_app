#ifndef EXTRAOPCODEWIDGET_H
#define EXTRAOPCODEWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include "locoiodata.h"
#include <QLineEdit>

namespace Ui {
class ExtraOpcodeWidget;
}

class ExtraOpcodeWidget : public QWidget
{
    Q_OBJECT
    
public:
 explicit ExtraOpcodeWidget(LocoIOData* data, int port, int extra, QWidget *parent = 0);
 ~ExtraOpcodeWidget();
 bool displayFormat();
public slots:
 void retranslateControls();

private:
    Ui::ExtraOpcodeWidget *ui;
    QButtonGroup* group, *group2;
    LocoIOData* data;
    int port;
    int channel, /*channelMax,*/ channelBase;
    int decodeText(QLineEdit *ctl);
    bool bHexDisplay;
    int nbrFormat;
    QString nbrPrefix;
    void paintEvent(QPaintEvent *);
    int extra;
    bool bSetting;
private slots:
    void onAddrChanged(int channel, int iOld, int INew, QString p);
    void onSVChanged(int channel, int iOld, int INew, QString p);
    void onV1Changed(int channel, int iOld, int INew, QString p);
    void onV2Changed(int channel, int iOld, int INew, QString p);
    void on_rbOff_toggled(bool bChecked);
    void on_rbDirect_toggled(bool bChecked);
    void on_rbIndirect_toggled(bool bChecked);
    void on_rbContact1_toggled(bool bChecked);
    void on_rbContact2_toggled(bool bChecked);
    void on_edAddr_editingFinished();
    void on_edCfg_editingFinished();
    void on_edVal1_editingFinished();
    void on_edVal2_editingFinished();
    void setHexDisplay(bool bHex);
    void onAllowEdit(bool bChecked);
};

#endif // EXTRAOPCODEWIDGET_H
