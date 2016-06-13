#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include "liblayouteditor_global.h"

namespace Ui {
class InputDialog;
}

class QComboBox;
class LIBLAYOUTEDITORSHARED_EXPORT InputDialog : public QDialog
{
 Q_OBJECT
    
public:
 explicit InputDialog(QString labelText, QString currValue, QStringList* tList = 0, QWidget *parent = 0);
 InputDialog(QString labelText, QList<QVariant> list, int currIndex, QString title, QWidget* parent = 0);
 InputDialog(QString labelText, QComboBox* selections, QString title, QWidget* parent = 0);

 ~InputDialog();
 static QString showInputDialog(QString text, QWidget* parent);
 QString value();

private:
    Ui::InputDialog *ui;
    QStringList* tList;
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_lineEdit_textEdited(QString text);
};

#endif // INPUTDIALOG_H
