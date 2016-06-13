#ifndef ADDPANELEDITORDIALOG_H
#define ADDPANELEDITORDIALOG_H

#include <QMainWindow>
#include "paneleditor.h"

namespace Ui {
class AddPanelEditorDialog;
}

class LIBLAYOUTEDITORSHARED_EXPORT AddPanelEditorDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddPanelEditorDialog(QWidget *parent = 0);
    ~AddPanelEditorDialog();
    QPoint location();
private:
    Ui::AddPanelEditorDialog *ui;
    PanelEditor* editor;
private slots:
    void on_btnSetName_clicked();
    void on_edText_editingFinished(QString text);
    void on_btnAddText_clicked();
    void on_cbType_activated(int i);
    void on_chkPopup_toggled(bool bState);
    void on_chkReposition_toggled(bool bState);
    void on_chkShowTooltips_toggled(bool bState);
    void on_chkControlLayout_toggled(bool bState);
    void on_chkShowHidden_toggled(bool bState);
    void on_chkHasMenu_toggled(bool bState);
protected:

};

#endif // ADDPANELEDITORDIALOG_H
