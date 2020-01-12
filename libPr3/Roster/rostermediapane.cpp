#include "rostermediapane.h"
#include "ui_rostermedia.h"
#include "rosterentry.h"
#include <QMenu>
#include "fileutil.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QDragEnterEvent>

RosterMediaPane::RosterMediaPane(RosterEntry* re, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RosterMediaPane)
{
 ui->setupUi(this);
 this->re = re;
 log = new Logger("RosterMedia");
 ui->lblMainImage->setContextMenuPolicy(Qt::CustomContextMenu);
 ui->lblMainImage->setAcceptDrops(true);
 ui->lblIconImage->setAcceptDrops(true);

 // tab 2
 QImage img(re->getImagePath());
 if(!img.isNull())
 {
  ui->lblMainImage->setPixmap(QPixmap::fromImage(img).scaledToHeight(200));
  ui->btnRemoveImage->setVisible(true);
  connect(ui->btnRemoveImage, SIGNAL(clicked()), this, SLOT(on_removeAction_triggered()));
 }
 else
  ui->btnRemoveImage->setVisible(false);
 connect(ui->lblMainImage, SIGNAL(fileNameChanged(QString)), this, SLOT(dropImage(QString)));

 if(re->getIconPath() != "")
 {
  QImage icon(re->getIconPath());
  if(!icon.isNull())
  {
   ui->lblIconImage->setPixmap(QPixmap::fromImage(icon).scaledToHeight(100));
   ui->btnRemoveIcon->setVisible(true);
   connect(ui->btnRemoveIcon, SIGNAL(clicked()), this, SLOT(on_removeIcon_triggered()));
  }
  else
   ui->btnRemoveIcon->setVisible(false);
 }
 else
 {
  QImage img(re->getImagePath());
  ui->lblIconImage->setPixmap(QPixmap::fromImage(img).scaledToHeight(45));
 }
 //connect(ui->lblIconImage, SIGNAL(fileNameChanged(QString)), this, SLOT(dropIcon(QString)));

 connect(ui->lblMainImage, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_customContexMenuRequest(QPoint)));

 ui->edWebReference->setText(re->getURL());
 connect(ui->edWebReference, SIGNAL(textEdited(QString)),this, SLOT(on_edWebReference_textEdited(QString)));
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
 connect(newImageAction, SIGNAL(triggered()), this, SLOT(on_removeIcon_triggered()));
 menu->addAction(newImageAction);
 menu->exec(QCursor::pos());
}

void RosterMediaPane::on_removeAction_triggered()
{
    re->setImagePath("");
    ui->lblMainImage->setPixmap(QPixmap());
    ui->btnRemoveImage->setVisible(false);
}

void RosterMediaPane::on_removeIcon_triggered()
{
    re->setIconPath("");
    ui->lblIconImage->setPixmap(QPixmap());
    ui->btnRemoveIcon->setVisible(false);
}

void RosterMediaPane::on_addImageAction_triggered()
{
 setCursor(Qt::WaitCursor);
 fileName = QFileDialog::getOpenFileName(this,tr("Add or replace image"), FileUtil::getUserResourcePath(),tr("Image Files (*.png *.jpg *.bmp"));
 setCursor(Qt::ArrowCursor);
 dropImage(fileName);
 re->setImagePath(fileName);
 QImage img(re->getImagePath());
 ui->lblMainImage->setPixmap(QPixmap::fromImage(img).scaledToWidth(ui->lblMainImage->width()));
}

void RosterMediaPane::on_addIconAction_triggered()
{
 setCursor(Qt::WaitCursor);
 fileName = QFileDialog::getOpenFileName(this,tr("Add or replace image"), FileUtil::getUserResourcePath(),tr("Image Files (*.png *.jpg *.bmp"));
 setCursor(Qt::ArrowCursor);
 dropIcon(fileName);
 re->setIconPath(fileName);
 QImage img(re->getIconPath());
 ui->lblIconImage->setPixmap(QPixmap::fromImage(img).scaledToWidth(ui->lblIconImage->width()));
}

void RosterMediaPane::dropImage(QString fileName)
{
 ui->btnRemoveImage->setVisible(true);
 connect(ui->btnRemoveImage, SIGNAL(clicked()), this, SLOT(on_removeAction_triggered()));

 QFileInfo info(fileName);
 //if(info.absolutePath()+QDir::separator() != FileUtil::getUserResourcePath())
 if(info.absolutePath()+QDir::separator() != LocoFile::getFileLocation())
 {
  //  log->debug(tr("Must move image from '%1' to '%2'").arg(info.absolutePath()).arg(FileUtil::getUserResourcePath()));
  log->debug(tr("Must move image from '%1' to '%2'").arg(info.absolutePath()).arg(LocoFile::getFileLocation()));
  //if(QFile::exists(FileUtil::getUserResourcePath()+ info.fileName()))
  if(QFile::exists(LocoFile::getFileLocation() + info.fileName()))
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
  //QFile::copy(fileName, FileUtil::getUserResourcePath()+ info.fileName());
  QFile::copy(fileName, LocoFile::getFileLocation()+ info.fileName());
  //fileName= FileUtil::getUserResourcePath()+ info.fileName();
  this->fileName= LocoFile::getFileLocation()+ info.fileName();
  re->setImagePath(this->fileName);
 }
}

void RosterMediaPane::dropIcon(QString fileName)
{
 ui->btnRemoveIcon->setVisible(true);
 connect(ui->btnRemoveIcon, SIGNAL(clicked()), this, SLOT(on_removeIcon_triggered()));

 QFileInfo info(fileName);
 //if(info.absolutePath()+QDir::separator() != FileUtil::getUserResourcePath())
 if(info.absolutePath()+QDir::separator() != LocoFile::getFileLocation())
 {
//  log->debug(tr("Must move image from '%1' to '%2'").arg(info.absolutePath()).arg(FileUtil::getUserResourcePath()));
  log->debug(tr("Must move image from '%1' to '%2'").arg(info.absolutePath()).arg(LocoFile::getFileLocation()));
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
//  QFile::copy(fileName, FileUtil::getUserResourcePath()+ info.fileName());
  QFile::copy(fileName, LocoFile::getFileLocation()+ info.fileName());
//  fileName= FileUtil::getUserResourcePath()+ info.fileName();
  this->fileName= LocoFile::getFileLocation() + info.fileName();
  re->setIconPath(this->fileName);
 }
}

void RosterMediaPane::on_edWebReference_textEdited(QString text)
{
 re->setURL(text);
}

void RosterMediaPane::dragEnterEvent(QDragEnterEvent *evt)
{
 QRect iconImageRect = ui->lblIconImage->geometry();
 QRect mainImageRect = ui->lblMainImage->geometry();
 QPoint mousePos = ui->lblIconImage->mapFromGlobal(evt->pos());
 if(iconImageRect.contains(mousePos) || mainImageRect.contains(mousePos))
 {
  if(!evt->mimeData()->text().isEmpty())
   evt->accept();
 }
}

void RosterMediaPane::dragMoveEvent(QDragMoveEvent */*evt*/)
{

}

void RosterMediaPane::dropEvent(QDropEvent * evt)
{
 QRect iconImageRect = ui->lblIconImage->geometry();
 QRect mainImageRect = ui->lblMainImage->geometry();
 QPoint mousePos = ui->lblIconImage->mapFromGlobal(evt->pos());
 QString text = evt->mimeData()->text();
 if(text.startsWith("file://"))
 {
  text.remove("\r\n");
  //ImageIcon* icon = new ImageIcon(text.mid(7),text.mid(7));
  if(mainImageRect.contains(mousePos))
   dropImage(text);
  if(iconImageRect.contains(mousePos))
   dropIcon(text);
 }
}
