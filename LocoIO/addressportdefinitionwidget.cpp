#include "addressportdefinitionwidget.h"
#include "ui_addressportdefinitionwidget.h"

AddressPortDefinitionWidget::AddressPortDefinitionWidget(LocoIOData* data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddressPortDefinitionWidget)
{
 ui->setupUi(this);
 this->data = data;
}

AddressPortDefinitionWidget::~AddressPortDefinitionWidget()
{
    delete ui;
}
void AddressPortDefinitionWidget::retranslateControls()
{
 ui->retranslateUi(this);
}
