#include "audiowidget.h"
#include "ui_audiowidget.h"

AudioWidget::AudioWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AudioWidget)
{
 ui->setupUi(this);
}

AudioWidget::~AudioWidget()
{
 delete ui;
}
void AudioWidget::setPanel(QWidget *panel)
{
 ui->verticalLayout->insertWidget(0, panel, 0,Qt::AlignTop);
}
QPushButton* AudioWidget::addSourceButton()
{
 return ui->addSource;
}
QPushButton* AudioWidget::addBufferButton()
{
 return ui->addBuffer;
}
