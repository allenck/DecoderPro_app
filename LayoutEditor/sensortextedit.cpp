#include "sensortextedit.h"
#include "ui_sensortextedit.h"

/*static*/ QString SensorTextEdit::INIT = "";

SensorTextEdit::SensorTextEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorTextEdit)
{
 ui->setupUi(this);
 pl = NULL;
}

SensorTextEdit::~SensorTextEdit()
{
    delete ui;
}
/*public*/ void SensorTextEdit::initComponents(SensorIcon* l, QString name) throw (Exception)
{
 pl = l;

 // the following code sets the frame's initial state

 ui->labelName->setText(tr("Name")+": ");
 ui->labelName->setVisible(true);

 ui->nameText->setText(name);
 ui->nameText->setVisible(true);

 ui->textInact->setText("Inactive= " + pl->getInactiveText());
 ui->textInact->setVisible(true);
 ui->textAct->setText("Active= " + pl->getActiveText());
 ui->textAct->setVisible(true);
 ui->textIncon->setText("Inconsistent= " + pl->getInconsistentText());
 ui->textIncon->setVisible(true);
 ui->textUnknown->setText("Unknown= " + pl->getUnknownText());
 ui->textUnknown->setVisible(true);

 ui->inactTextField->setText(pl->getInactiveText());
 ui->inactTextField->setToolTip(tr("Enter the text to be displayed when the sensor is Inactive"));
 ui->inactTextField->setMaximumSize( QSize(
                ui->inactTextField->maximumSize().width(), ui->inactTextField
                        ->size().height()));


 ui->actTextField->setText(pl->getActiveText());
 ui->actTextField->setToolTip(tr("Enter the text to be displayed when the sensor is Active"));
 ui->actTextField->setMaximumSize( QSize(
                                      ui->actTextField->maximumSize().width(), ui->actTextField
                                      ->size().height()));

 ui->inconTextField->setText(pl->getInconsistentText());
 ui->inconTextField->setToolTip(tr("Enter the text to be displayed when the sensor is Inconsistent state"));
 ui->inconTextField->setMaximumSize( QSize(
                                        ui->inconTextField->maximumSize().width(), ui->inconTextField
                                        ->size().height()));

 ui->unknownTextField->setText(pl->getUnknownText());
 ui->unknownTextField->setToolTip(tr("Enter the text to be displayed when the sensor is in an Unknown state"));
 ui->unknownTextField->setMaximumSize( QSize(
                                          ui->unknownTextField->maximumSize().width(), ui->unknownTextField
                                          ->size().height()));

 ui->okButton->setText(tr("Set"));
 ui->okButton->setVisible(true);
 ui->okButton->setToolTip(tr("Press to change the text"));

 ui->cancelButton->setText(tr("Cancel"));
 ui->cancelButton->setVisible(true);
 ui->cancelButton->setToolTip(tr("Press to cancel changes"));

 setWindowTitle(tr("Set Text for Sensor States"));
    //getContentPane().setLayout(new GridBagLayout());

 //setSize(250, 220); // resize?
}

void SensorTextEdit::on_okButtonClicked()
{
 if (oldActive == INIT)
 {
  oldActive = pl->getActiveText();
  oldInactive = pl->getInactiveText();
  oldIncon = pl->getInconsistentText();
  oldUnknown = pl->getUnknownText();
 }
 pl->setInactiveText(ui->inactTextField->text());
 pl->setActiveText(ui->actTextField->text());
 pl->setInconsistentText(ui->inconTextField->text());
 pl->setUnknownText(ui->unknownTextField->text());
 ui->textInact->setText(tr("Inactive= ") + pl->getInactiveText());
 ui->textAct->setText(tr("Active= ") + pl->getActiveText());
 ui->textIncon->setText(tr("Inconsistent= ") + pl->getInconsistentText());
 ui->textUnknown->setText(tr("Unknown= ") + pl->getUnknownText());
 accept();
 close();
}
void SensorTextEdit::on_CancelButtonClicked()
{
 if (oldActive != INIT)
 {
  pl->setInactiveText(oldInactive);
  pl->setActiveText(oldActive);
  pl->setInconsistentText(oldIncon);
  pl->setUnknownText(oldUnknown);
 }
 //dispose();
 reject();
 close();
}
