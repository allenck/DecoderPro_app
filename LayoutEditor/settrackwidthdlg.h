#ifndef SETTRACKWIDTHDLG_H
#define SETTRACKWIDTHDLG_H

#include <QDialog>

namespace Ui {
class SetTrackWidthDlg;
}

class SetTrackWidthDlg : public QDialog
{
    Q_OBJECT
    
public:
 explicit SetTrackWidthDlg(int sideTrackWidth, int mainlineTrackWidth, QWidget *parent = 0);
 ~SetTrackWidthDlg();
 int sidetrackWidth();
 int mainlineTrackWidth();

private:
 Ui::SetTrackWidthDlg *ui;
private slots:
 void on_okButton_clicked();
 void on_cancelButton_clicked();
};

#endif // SETTRACKWIDTHDLG_H
