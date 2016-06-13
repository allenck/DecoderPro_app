#ifndef ADDREPORTERDLG_H
#define ADDREPORTERDLG_H

#include <QDialog>
#include "liblayouteditor_global.h"

namespace Ui {
class AddReporterDlg;
}

class LIBLAYOUTEDITORSHARED_EXPORT AddReporterDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddReporterDlg(QWidget *parent = 0);
    ~AddReporterDlg();
    QString getName();
    QPoint getLoc();
private:
    Ui::AddReporterDlg *ui;
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // ADDREPORTERDLG_H
