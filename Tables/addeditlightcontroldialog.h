#ifndef ADDEDITLIGHTCONTROLDIALOG_H
#define ADDEDITLIGHTCONTROLDIALOG_H

#include <QDialog>

namespace Ui {
class AddEditLightControlDialog;
}

class AddEditLightControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditLightControlDialog(QWidget *parent = 0);
    ~AddEditLightControlDialog();
private:
 Ui::AddEditLightControlDialog *ui;
private slots:
 void on_comboBox_currentIndexChanged(int index);
};

#endif // ADDEDITLIGHTCONTROLDIALOG_H
