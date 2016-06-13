#ifndef INPUTANGLEDLG_H
#define INPUTANGLEDLG_H

#include <QDialog>

namespace Ui {
class inputAngleDlg;
}

class InputAngleDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputAngleDlg(int degrees, QWidget *parent = 0);
    ~InputAngleDlg();
    int angle();
private:
    Ui::inputAngleDlg *ui;
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // INPUTANGLEDLG_H
