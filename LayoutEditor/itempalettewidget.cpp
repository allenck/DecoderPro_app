#include "itempalettewidget.h"
#include "ui_itempalettewidget.h"

ItemPaletteWidget::ItemPaletteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemPaletteWidget)
{
    ui->setupUi(this);
}

ItemPaletteWidget::~ItemPaletteWidget()
{
    delete ui;
}
