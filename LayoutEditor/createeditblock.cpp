#include "createeditblock.h"
#include "ui_createeditblock.h"
#include <QMessageBox>
#include "abstractsensor.h"
#include "instancemanager.h"

CreateEditBlock::CreateEditBlock(QString blockName, LayoutEditor* editor, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateEditBlock)
{
 ui->setupUi(this);
 this->editor = editor;
 Q_ASSERT(!blockName.isEmpty());
 this->layoutBlock = this->editor->provideLayoutBlock(blockName);

 ui->blockNameLabel ->setText(this->layoutBlock->getDisplayName());
 ui->sensorNameField->setText(this->layoutBlock->getOccupancySensorName());
 setWindowTitle(tr("Edit Block"));
 _Colors << "Black"<<"Dark Gray"<<"Gray"<<"Light Gray"<<"White"<<"Red"<<"Orange"<<"Yellow"<<"Green"<<"Blue"<<"Magenta";
 _colors << QColor(Qt::black) << QColor(Qt::darkGray) << QColor(Qt::gray) << QColor(Qt::lightGray) << QColor(Qt::white) << QColor(Qt::red) << QColor(255, 170, 0) << QColor(Qt::yellow ) << QColor(Qt::green) <<QColor(Qt::blue) <<QColor(Qt::magenta)<<QColor();
 ui->occupiedColorBox->clear();
 ui->extraColorBox->clear();
 ui->trackColorBox->clear();
 for(int i=0; i < _Colors.size(); i++)
 {
  QColor desiredColor = _colors.at(i);
  const QIcon* icon = getColourIcon(desiredColor);
  ui->occupiedColorBox->addItem(*icon,_Colors.at(i));
  ui->extraColorBox->addItem(*icon, _Colors.at(i));
  ui->trackColorBox->addItem(*icon, _Colors.at(i));
  if(desiredColor == layoutBlock->blockTrackColor)
   ui->trackColorBox->setCurrentIndex(i);
  if(desiredColor == layoutBlock->blockOccupiedColor)
   ui->occupiedColorBox->setCurrentIndex(i);
  if(desiredColor == layoutBlock->blockExtraColor)
   ui->extraColorBox->setCurrentIndex(i);
 }
}

CreateEditBlock::~CreateEditBlock()
{
    delete ui;
}
void CreateEditBlock::on_blockEditDone_clicked()
{
 bool needsRedraw = false;
 // check if Sensor changed
 if ( !(layoutBlock->getOccupancySensorName()==ui->sensorNameField->text().trimmed()) )
 {
  // sensor has changed
  QString newName = ui->sensorNameField->text().trimmed();
  bool bOk;
  int iAddr = newName.toInt(&bOk);
  if(bOk && iAddr > 0)
      newName = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->createSystemName(newName, "I");
  if (layoutBlock->validateSensor(newName,/*this*/editor)==NULL)
  {
   // invalid sensor entered
   layoutBlock->occupancyNamedSensor = NULL;
   layoutBlock->occupancySensorName = "";
   ui->sensorNameField->setText("");
   return;
  }
  else
  {
   ui->sensorNameField->setText(newName);
   needsRedraw = true;
  }
 }
 if(layoutBlock->getOccupancySensor()!=NULL)
 {
     AbstractSensor* sensor = qobject_cast<AbstractSensor*>(layoutBlock->getOccupancySensor());
  if(ui->sensorDebounceGlobalCheck->isChecked())
  {
   sensor->useDefaultTimerSettings(true);
  }
  else
  {
   sensor->useDefaultTimerSettings(false);
   if(!(layoutBlock->sensorDebounceInactiveField->text().trimmed()==("")))
    sensor->setSensorDebounceGoingInActiveTimer((ui->sensorDebounceInactiveField->text().trimmed().toLong()));
   if(!(ui->sensorDebounceActiveField->text().trimmed()==("")))
    sensor->setSensorDebounceGoingActiveTimer((ui->sensorDebounceActiveField->text().trimmed().toLong()));
  }
  if(sensor->getReporter()!=NULL && layoutBlock!=NULL)
  {
//   QString msg = java.text.MessageFormat.format(rb.getString("BlockAssignReporter"), new Object[] { layoutBlock->getOccupancySensor().getDisplayName(), layoutBlock->getOccupancySensor().getReporter().getDisplayName() });
//   if(JOptionPane.showConfirmDialog(editLayoutBlockFrame,                                             msg,rb.getString("BlockAssignReporterTitle"),                                             JOptionPane.YES_NO_OPTION)==0)
    if(QMessageBox::question(this, tr("New reporter"), tr("Add reporter %1 for sensor %2").arg(layoutBlock->getOccupancySensor()->getReporter()->getDisplayName()).arg(sensor->getDisplayName()),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    layoutBlock->block->setReporter(sensor->getReporter());
   }
  }
  // check if occupied sense changed
  int k = ui->senseBox->currentIndex();
  int oldSense = layoutBlock->occupiedSense;
  if (k==layoutBlock->senseActiveIndex)
   layoutBlock->occupiedSense = Sensor::ACTIVE;
  else
   layoutBlock->occupiedSense = Sensor::INACTIVE;
  if (oldSense != layoutBlock->occupiedSense) needsRedraw = true;
  // check if track color changed
  QColor oldColor = layoutBlock->blockTrackColor;
  layoutBlock->blockTrackColor = /*getSelectedColor(ui->trackColorBox);*/ _colors.at(ui->trackColorBox->currentIndex());
  if (oldColor!= layoutBlock->blockTrackColor) needsRedraw = true;
  // check if occupied color changed
  oldColor = layoutBlock->blockOccupiedColor;
  layoutBlock->blockOccupiedColor = /*getSelectedColor(ui->occupiedColorBox)*/ _colors.at(ui->occupiedColorBox->currentIndex());
  if (oldColor!= layoutBlock->blockOccupiedColor) needsRedraw = true;
  // check if extra color changed
  oldColor = layoutBlock->blockExtraColor;
  layoutBlock->blockExtraColor = /*getSelectedColor(ui->extraColorBox)*/ _colors.at(ui->extraColorBox->currentIndex());
  if (oldColor!=layoutBlock->blockExtraColor) needsRedraw = true;
  // check if Memory changed
  if ( !(layoutBlock->memoryName==(ui->memoryNameField->text().trimmed())) )
  {
   // memory has changed
   QString newName = ui->memoryNameField->text().trimmed();
   if ((layoutBlock->memory = layoutBlock->validateMemory(newName,NULL))==NULL)
   {
    // invalid memory entered
    layoutBlock->memoryName = "";
    ui->memoryNameField->setText("");
    return;
   }
   else
   {
    ui->memoryNameField->setText(layoutBlock->memoryName);
    needsRedraw = true;
   }
  }
  int m = (ui->metricField->text().trimmed().toInt());
  if (m!=layoutBlock->metric)
   layoutBlock->setBlockMetric(m);
  if(layoutBlock->block != NULL)
   layoutBlock->block->setPermissiveWorking(ui->permissiveCheck->isChecked());
  if(!layoutBlock->neighbourDir.isEmpty())
  {
   for(int i = 0; i<layoutBlock->neighbourDir.size(); i++)
   {
    int neigh = layoutBlock->neighbourDir.at(i)->currentIndex();
    layoutBlock->neighbours->at(i)->getBlock()->removeBlockDenyList(this->layoutBlock->blockName);
    layoutBlock->block->removeBlockDenyList(layoutBlock->neighbours->at(i)->getBlock());
    switch(neigh)
    {
     case 0 : layoutBlock->updateNeighbourPacketFlow(layoutBlock->neighbours->at(i), LayoutBlock::RXTX);
             break;
     case 1 :
            layoutBlock->neighbours->at(i)->getBlock()->addBlockDenyList(this->layoutBlock->getDisplayName());
            layoutBlock->updateNeighbourPacketFlow(layoutBlock->neighbours->at(i), LayoutBlock::TXONLY);
            break;
     case 2 :
            layoutBlock->block->addBlockDenyList(layoutBlock->neighbours->at(i)->getBlock()->getDisplayName());
            layoutBlock->updateNeighbourPacketFlow(layoutBlock->neighbours->at(i), LayoutBlock::RXONLY);
            break;
     default: break;
   }
  }
 }
 // complete
 // editOpen = false;
 // editLayoutBlockFrame.setVisible(false);
 // editLayoutBlockFrame.dispose();
 // editLayoutBlockFrame = NULL;
 if (needsRedraw) layoutBlock->redrawLayoutBlockPanels();
 //accept();
 close();
}
void CreateEditBlock::on_blockEditCancel_clicked()
{
//    editOpen = false;
//    editLayoutBlockFrame.setVisible(false);
//    editLayoutBlockFrame.dispose();
//    editLayoutBlockFrame = NULL;
    //reject();
    close();
}
const QIcon* CreateEditBlock::getColourIcon(QColor color)
{
 Q_ASSERT(color.isValid());
 int ICON_DIMENSION = 10;
// BufferedImage image = new BufferedImage(ICON_DIMENSION, ICON_DIMENSION,
// BufferedImage.TYPE_INT_RGB);
 QImage resultImage = QImage(ICON_DIMENSION,ICON_DIMENSION,QImage::Format_ARGB32_Premultiplied);

// Graphics g = image.getGraphics();
 QPainter painter(&resultImage);
//   // set completely transparent
// g.setColor(color);
// g.fillRect(0,0, ICON_DIMENSION,ICON_DIMENSION);
 QBrush brBkgnd = QBrush(QColor(color), Qt::SolidPattern);
//eRect.adjust(0, -3.0, 0, 0);
 painter.fillRect(resultImage.rect(), brBkgnd);
 painter.end();
// ImageIcon icon = new ImageIcon(image);
 QIcon* icon = new QIcon(QPixmap::fromImage(resultImage));
 return icon;
}

void CreateEditBlock::on_sensorNameField_textChanged(QString text)
{
 QCompleter* completer = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(text);
 if(completer!= NULL)
   ui->sensorNameField->setCompleter(completer);
}
