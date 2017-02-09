#include "rostermedia.h"
#include "ui_rostermedia.h"
#include "rosterentry.h"
#include <QMenu>
#include "fileutil.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>

RosterMediaPane::RosterMediaPane(RosterEntry* re, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RosterMediaPane)
{
    ui->setupUi(this);
    this->re = re;
    log = new Logger("RosterMedia");
    // tab 2
    QImage img(re->getImagePath());
    ui->lblMainImage->setPixmap(QPixmap::fromImage(img).scaledToHeight(120));
    ui->lblMainImage->setContextMenuPolicy(Qt::CustomContextMenu);
    if(re->getIconPath() != "")
    {
     QImage icon(re->getIconPath());
     ui->lblIconImage->setPixmap(QPixmap::fromImage(icon).scaledToHeight(48));
    }
    else
    {
     QImage img(re->getImagePath());
     ui->lblIconImage->setPixmap(QPixmap::fromImage(img).scaledToHeight(45));
    }
    connect(ui->lblMainImage, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_customContexMenuRequest(QPoint)));
}

RosterMediaPane::~RosterMediaPane()
{
    delete ui;
}
void RosterMediaPane::on_customContexMenuRequest(QPoint)
{
    QMenu* menu = new QMenu();
    if(re->getImagePath() != "")
    {
     QAction* removeAction = new QAction(tr("Remove"), this);
     menu->addAction(removeAction);
     connect(removeAction, SIGNAL(triggered()), this, SLOT(on_removeAction_triggered()));
    }
    QAction* newImageAction = new QAction(tr("Add image"), this);
    connect(newImageAction, SIGNAL(triggered()), this, SLOT(on_addImageAction_triggered()));
    menu->addAction(newImageAction);
    menu->exec(QCursor::pos());
}
void RosterMediaPane::on_removeAction_triggered()
{
    re->setImagePath("");
    ui->lblMainImage->setPixmap(QPixmap());
}
void RosterMediaPane::on_addImageAction_triggered()
{
 setCursor(Qt::WaitCursor);
 QString fileName = QFileDialog::getOpenFileName(this,tr("Add or replace image"), FileUtil::getUserResourcePath(),tr("Image Files (*.png *.jpg *.bmp"));
 setCursor(Qt::ArrowCursor);
 QFileInfo info(fileName);
    if(info.absolutePath()+QDir::separator() != FileUtil::getUserResourcePath())
    {
     log->debug(tr("Must move image from '%1' to '%2'").arg(info.absolutePath()).arg(FileUtil::getUserResourcePath()));
     if(QFile::exists(FileUtil::getUserResourcePath()+ info.fileName()))
     {
      switch(QMessageBox::question(this, tr("File already exists"), tr("The file already exists. Do you want to replace it?"), QMessageBox::Yes | QMessageBox::No))
      {
      case QMessageBox::Yes:
       break;
      default:
      case QMessageBox::No:
       return;
      }
     }
     QFile::copy(fileName, FileUtil::getUserResourcePath()+ info.fileName());
     fileName= FileUtil::getUserResourcePath()+ info.fileName();
    }
    re->setImagePath(fileName);
    QImage img(re->getImagePath());
    ui->lblMainImage->setPixmap(QPixmap::fromImage(img).scaledToWidth(ui->lblMainImage->width()));
}
void RosterMediaPane::on_btnSave_clicked()
{

}
