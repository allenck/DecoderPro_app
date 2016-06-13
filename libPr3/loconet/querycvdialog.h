#ifndef QUERYCVDIALOG_H
#define QUERYCVDIALOG_H

#include <QWidget>
#include "../../LocoIO/locoiodialog.h"
#include "libPr3_global.h"

namespace Ui {
class QueryCvDialog;
}
class LIBPR3SHARED_EXPORT QueryCvDialog : public QWidget
{  Q_OBJECT

public:
 explicit QueryCvDialog(QWidget* parent = 0);
 QueryCvDialog(LocoIOData* data, LocoBufferAdapter* locobufferadapter, bool bHex, QWidget *parent = 0);
 ~QueryCvDialog();
 QueryCvDialog(const QueryCvDialog&) : QWidget() {}
    
private:
 Ui::QueryCvDialog *ui;
 LocoIOData* data;
 LocoBufferAdapter* locobufferadapter;
 bool bHex;
 AddressValidator* rv;
 QRegExp rxHex;
 QRegExp rxDec;
 qint32 val;
 int decodeText(QLineEdit *ctl);
 int addr;
 int subAddr;
 int cv;
 private slots:
 void on_edAddress_textChanged(QString text);
 void on_chkHex_toggled(bool bChecked);
 void on_btnOK_clicked();
 void on_btnCancel_clicked();
 void on_edCv_editingFinished();
};

#endif // QUERYCVDIALOG_H
