#ifndef SAVERESTOREDIALOG_H
#define SAVERESTOREDIALOG_H

#include <QDialog>
#include <QSettings>
#include "locoiodata.h"

namespace Ui {
class SaveRestoreDialog;
}

class SaveRestoreDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SaveRestoreDialog(bool bSaveMode, LocoIOData* data, QWidget *parent = 0);
    ~SaveRestoreDialog();
    void setMode(bool bSave);
    void getSettings();
    void setValues(QList<int>* vals, QString module);
    QList<int>*  getValues();
    QString getModuleName();
    QStringList moduleNames();
    QStringList moduleDescriptions();
    void setDefaults(QList<int>* vals);
    QString Description();
private:
    Ui::SaveRestoreDialog *ui;
    bool bSaveMode;
    QStringList modules;
    QStringList descriptions;
    QList<int>* vals;
    QList<int>* _defaults;
    QString moduleName;
    void saveDefaults();
    void closeEvent(QCloseEvent *);
 LocoIOData* data;
private slots:
    void on_cbModules_currentIndexChanged(int index);
    void on_btnOK_clicked();
    void on_btnCancel_clicked();
    void on_btnDelete_clicked();
    void on_editDescription_editingFinished();

};

#endif // SAVERESTOREDIALOG_H
