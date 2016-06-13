#include "dialogsignalgroupstablewidget.h"
#include "ui_dialogsignalgroupstablewidget.h"

DialogSignalGroupsTableWIdget::DialogSignalGroupsTableWIdget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSignalGroupsTableWIdget)
{
    ui->setupUi(this);
}

DialogSignalGroupsTableWIdget::~DialogSignalGroupsTableWIdget()
{
    delete ui;
}
