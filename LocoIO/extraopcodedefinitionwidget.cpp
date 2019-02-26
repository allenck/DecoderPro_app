#include "extraopcodedefinitionwidget.h"
#include "ui_extraopcodedefinitionwidget.h"
#include <QPainter>
#include <QStyleOption>
#include <QStyle>

ExtraOpcodeDefinitionWidget::ExtraOpcodeDefinitionWidget(int extra, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtraOpcodeDefinitionWidget)
{
 ui->setupUi(this);
 ui->lblHeading->setText(QString("Extra Opcode %1").arg(extra));
 if(extra == 1)
 {
  //QPalette p(Qt::blue);
  this->setStyleSheet("QWidget {background-color : rgb(137,255,236); font-size : 7pt; }");
 }
 else
 {
  //QPalette p(Qt::blue);
  this->setStyleSheet("QWidget {background : rgb(255,170,127); font-size : 7pt; }");
 }
}

ExtraOpcodeDefinitionWidget::~ExtraOpcodeDefinitionWidget()
{
 delete ui;
}
void ExtraOpcodeDefinitionWidget::paintEvent(QPaintEvent *)
 {
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 }
void ExtraOpcodeDefinitionWidget::retranslateControls()
{
 ui->retranslateUi(this);
}
