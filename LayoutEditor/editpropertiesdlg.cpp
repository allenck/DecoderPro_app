#include "editpropertiesdlg.h"
#include "ui_editpropertiesdlg.h"

PositionablePropertiesUtil::PositionablePropertiesUtil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPropertiesDlg)
{
 ui->setupUi(this);
 _fontcolors << "Black"<<"Dark Gray"<<"Gray"<<"Light Gray"<<"White"<<"Red"<<"Orange"<<"Yellow"<<"Green"<<"Blue"<<"Magenta";
}

PositionablePropertiesUtil::~PositionablePropertiesUtil()
{
    delete ui;
}
