#ifndef ADDEDITDIALOG_H
#define ADDEDITDIALOG_H

#include <QDialog>

namespace Ui {
class AddEditDialog;
}

class AddEditDialog : public QDialog
{
 Q_OBJECT
    
public:
 explicit AddEditDialog(QString type, QObject* o = 0, QWidget *parent = 0);
 ~AddEditDialog();
 QString systemName();
 QString userName();
 QString system();
 int mgrIndex();
 bool isAddRange();
 int numToAdd();
 bool isAutoGen();
private:
    Ui::AddEditDialog *ui;
 QString type;
private slots:
 void on_btnOK_clicked();
 void on_chkAutoGen_toggled(bool bState);
 void on_chkAdd_toggled(bool bState);
};

#endif // ADDEDITDIALOG_H
