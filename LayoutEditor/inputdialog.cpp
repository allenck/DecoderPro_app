#include "inputdialog.h"
#include "ui_inputdialog.h"
#include <QCompleter>

InputDialog::InputDialog(QString labelText, QString currValue, QStringList* tList,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
 ui->setupUi(this);
 ui->label->setText(labelText);
 this->tList = tList;
 ui->lineEdit->setVisible(true);
 ui->comboBox->setHidden(true);
}

InputDialog::InputDialog(QString labelText, QList<QVariant> list, int currIndex, QString title, QWidget* parent)
 : QDialog(parent),
    ui(new Ui::InputDialog)
{
 ui->setupUi(this);
 ui->label->setText(labelText);
 ui->lineEdit->setHidden(true);
 foreach(QVariant v, list)
 {
  ui->comboBox->addItem(v.toString());
 }
 ui->comboBox->setCurrentIndex(currIndex);
 ui->comboBox->setVisible(true);
 setWindowTitle(title);
}

InputDialog::InputDialog(QString labelText, QComboBox *selections, QString title, QWidget *parent)
 : QDialog(parent),
   ui(new Ui::InputDialog)
{
 ui->setupUi(this);
 ui->label->setText(labelText);
 ui->lineEdit->setHidden(true);
 ui->verticalLayout->removeWidget(ui->comboBox);
 delete ui->comboBox;
 ui->verticalLayout->addWidget(selections);
 ui->comboBox = selections;
 setWindowTitle(title);

}

InputDialog::InputDialog(QString labelText, QList<QWidget*> selections, QString title, QWidget *parent)
 : QDialog(parent),
   ui(new Ui::InputDialog)
{
 ui->setupUi(this);
 ui->label->setText(labelText);
 ui->lineEdit->setHidden(true);
 //ui->verticalLayout->removeWidget(ui->comboBox);
 ui->comboBox->setHidden(true);
 //ui->verticalLayout->addWidget(selections);
 foreach(QWidget* w, selections)
 {
  ui->verticalLayout->insertWidget(1,w);
 }

 //ui->comboBox = selections;
 setWindowTitle(title);

}

InputDialog::~InputDialog()
{
 delete ui;
}
QString InputDialog::showInputDialog(QString text, QWidget *parent)
{
 InputDialog dlg(text, "", NULL, parent);
 if(dlg.exec() == QDialog::Accepted)
 {
  return dlg.value();
 }
 return QString("");
}
QString InputDialog::value()
{
 //if(ui->lineEdit->isVisible())
 if(ui->lineEdit->text() != "")
  return ui->lineEdit->text();
 else
  return ui->comboBox->currentText();
}
void InputDialog::on_cancelButton_clicked()
{
 reject();
 close();
}
void InputDialog::on_okButton_clicked()
{
 accept();
 close();
}
void InputDialog::on_lineEdit_textEdited(QString text)
{
 if(tList == NULL ) return;
 QStringList cList;
 foreach(QString s, *tList)
 {
  if(s.startsWith(text))
   cList.append(s);
 }
 QCompleter* c =new QCompleter(cList);
 ui->lineEdit->setCompleter(c);
}
