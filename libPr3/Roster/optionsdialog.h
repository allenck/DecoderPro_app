#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include "libPr3_global.h"

namespace Ui {
class OptionsDialog;
}

class LIBPR3SHARED_EXPORT OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QString title, QString LabelText, QComboBox* comboBox, QWidget *parent = 0);
    ~OptionsDialog();
 public slots:
    void on_btnCancel_clicked();
    void on_btnOK_clicked();
private:
    Ui::OptionsDialog *ui;
    QComboBox* comboBox;
};

#endif // OPTIONSDIALOG_H
