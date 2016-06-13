#ifndef COMMENTSDIALOG_H
#define COMMENTSDIALOG_H

#include <QDialog>
#include "locoiodata.h"
#include "sql.h"

namespace Ui {
class CommentsDialog;
}

class CommentsDialog : public QDialog
{
 Q_OBJECT
    
public:
 explicit CommentsDialog(int port, LocoIOData* data, Sql* sql, QWidget *parent = 0);
    ~CommentsDialog();
    
private:
 Ui::CommentsDialog *ui;
 LocoIOData* data;
 Sql* sql;
 int port;
private slots:
 void on_btnUpdate_clicked();
 void on_btnDelete_clicked();
 void on_btnCancel_clicked();
};

#endif // COMMENTSDIALOG_H
