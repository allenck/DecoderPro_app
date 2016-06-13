#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QString title, QString labelText, QComboBox* comboBox, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    setWindowTitle(title);
    ui->label->setText(labelText);
    this->comboBox = comboBox;
    for(int i=0; i < comboBox->count(); i++)
    {
     ui->comboBox->addItem(comboBox->itemText(i));
    }
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}
void OptionsDialog::on_btnCancel_clicked()
{
 reject();
 close();
}
void OptionsDialog::on_btnOK_clicked()
{
    if(ui->comboBox->currentIndex() >= 0)
    {
     this->comboBox->setCurrentIndex(ui->comboBox->currentIndex());
     accept();
     close();
    }
}
