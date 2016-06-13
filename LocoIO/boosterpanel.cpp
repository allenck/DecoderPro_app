#include "boosterpanel.h"
#include "ui_boosterpanel.h"

BoosterPanel::BoosterPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoosterPanel)
{
    ui->setupUi(this);
}

BoosterPanel::~BoosterPanel()
{
    delete ui;
}
void BoosterPanel::retranslateControls()
{
 ui->retranslateUi(this);
}
