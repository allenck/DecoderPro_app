#ifndef LOCONETMSGDIALOG_H
#define LOCONETMSGDIALOG_H

#include <QDialog>
#include "lnconstants.h"
#include "loconetmessage.h"
#include "jmripanel.h"
#include "libPr3_global.h"

namespace Ui {
class LocoNetMsgDialog;
}

class LIBPR3SHARED_EXPORT LocoNetMsgDialog : public JmriPanel
{
    Q_OBJECT
    
public:
 explicit LocoNetMsgDialog(QWidget *parent = 0);
 ~LocoNetMsgDialog();
 LocoNetMsgDialog(const LocoNetMsgDialog&) : JmriPanel() {}
 LocoNetMessage* locoNetMessage();
 QString getTitle();

private:
 Ui::LocoNetMsgDialog *ui;
 int opCode;
 int maxSize;
 bool buildMsg();
 void setMaxSize();

 LocoNetMessage* msg;
private slots:
 void on_cbOpcode_currentIndexChanged(int i);
 void on_btnOk_clicked();
 void on_lineEdit_textEdited(QString text);
};

#endif // LOCONETMSGDIALOG_H
