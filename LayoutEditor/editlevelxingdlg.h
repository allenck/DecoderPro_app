#ifndef EDITLEVELXINGDLG_H
#define EDITLEVELXINGDLG_H

#include <QDialog>
#include "levelxing.h"

namespace Ui {
class EditLevelXingDlg;
}

class EditLevelXingDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditLevelXingDlg(LevelXing* x, QWidget *parent);
    ~EditLevelXingDlg();
    
private:
    Ui::EditLevelXingDlg *ui;
    LevelXing* x;
    QWidget *parent;
    LayoutEditor* layoutEditor;
private slots:
    void on_xingEdit1Block_clicked();
    void on_xingEdit2Block_clicked();
    void on_xingEditDone_clicked();
    void on_xingEditCancel_clicked();
    void on_block1Name_editingFinished(QString text);
    void on_block2Name_editingFinished(QString text);
};

#endif // EDITLEVELXINGDLG_H
