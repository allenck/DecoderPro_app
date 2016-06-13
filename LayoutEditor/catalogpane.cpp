#include "catalogpane.h"
#include "ui_catalogpane.h"
#include "fileutil.h"
#include <QDebug>

CatalogPane::CatalogPane(bool bShowFiles, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatalogPane)
{
    ui->setupUi(this);
    this->bShowFiles = bShowFiles;
//    model = new QFileSystemModel();
//    model ->setRootPath(FileUtil::getProgramPath());
//    model ->setFilter(QDir::AllDirs /*| QDir::NoDotAndDotDot*/	);
    model = new CatalogTreeModel(bShowFiles);
    model->createNewNode(tr("Program resources"),FileUtil::getProgramPath()+"resources"+QDir::separator());
    model->createNewNode(tr("User files"), FileUtil::getUserFilesPath());
    ui->tree->setModel(model);
    ui->tree->setIndentation(10);
    ui->tree->setAnimated(true);
    ui->tree->setHeaderHidden(true);
    ui->tree->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->tree, SIGNAL(clicked(QModelIndex)), this, SLOT(on_tree_clicked(QModelIndex)));
    ui->previewPanel->setVisible(this->bShowFiles);
}

CatalogPane::~CatalogPane()
{
    delete ui;
}

NamedIcon* CatalogPane::getSelectedIcon()
{
 QModelIndex index = ui->tree->currentIndex();
 QString path =index.data().toString();
 CatalogTreeItem* item = (CatalogTreeItem*)index.internalPointer();
 QFileInfo info(item->path);

 if(info.isFile())
 {
  return new NamedIcon(item->path, item->path);
 }
 return NULL;
}
void CatalogPane::on_tree_clicked(QModelIndex index)
{
 //QString path = model->filePath(index);
 QString path =index.data().toString();
 CatalogTreeItem* item = (CatalogTreeItem*)index.internalPointer();

 qDebug() << tr("selected item: row = %1, col = %2, path = %3").arg(index.row()).arg(index.column()).arg(path);
 //if(model->isDir(index))
 emit newDirectorySelected(item->path);
 QFileInfo info(item->path);
 if(info.isFile())
 {
  QIcon icon = QIcon(item->path);
  ui->tableWidget->clear();
  ui->tableWidget->setColumnCount(1);
  ui->tableWidget->setRowCount(1);
  ui->tableWidget->horizontalHeader()->setHidden(true);
  ui->tableWidget->verticalHeader()->setHidden(true);
  QWidget* item = new QWidget();
  item->setLayout(new QVBoxLayout);
  QLabel* image = new QLabel;
  image->resize(100, 100);
  QString fullname = info.absoluteFilePath();
  QPixmap pixmap(fullname);
  if(pixmap.width() > pixmap.height() && pixmap.width() > 100)
    pixmap = pixmap.scaledToWidth(100);
  else if(pixmap.height() > 100)
      pixmap = pixmap.scaledToHeight(100);
  image->setPixmap( pixmap);
  QLabel* name = new QLabel(info.fileName());
  item->layout()->addWidget(image);
  item->layout()->addWidget(name);
  ui->tableWidget->setCellWidget(0,0,item);
  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget->resizeRowsToContents();

 }
}
