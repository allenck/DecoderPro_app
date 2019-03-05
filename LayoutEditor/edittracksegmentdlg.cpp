#include "edittracksegmentdlg.h"
#include "ui_edittracksegmentdlg.h"
#include <QMessageBox>
#include "createeditblock.h"
#include <QCompleter>

EditTrackSegmentDlg::EditTrackSegmentDlg(TrackSegment* trackSegment, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditTrackSegmentDlg)
{
 this->parent = parent;
 ui->setupUi(this);
 setWindowTitle("Edit Track Segment");
 this->trackSegment = trackSegment;
 if(this->trackSegment->getDashed())
  ui->cbStyle->setCurrentIndex(1);
 else
  ui->cbStyle->setCurrentIndex(0);
 if(this->trackSegment->getMainline())
  ui->cbTrackType->setCurrentIndex(1);
 else
  ui->cbTrackType->setCurrentIndex(0);
 ui->edBlockName->setText(this->trackSegment->getBlockName());
 ui->pbEditBlock->setEnabled(!ui->edBlockName->text().isEmpty());
 ui->chkHide->setChecked(this->trackSegment->getHidden());
}

EditTrackSegmentDlg::~EditTrackSegmentDlg()
{
 delete ui;
}
void EditTrackSegmentDlg::on_edBlockName_textChanged(QString text)
{
 ui->pbEditBlock->setEnabled(!ui->edBlockName->text().isEmpty());
 QCompleter* completer = InstanceManager::blockManagerInstance()->getCompleter(text);
 if(completer!= NULL)
   ui->edBlockName->setCompleter(completer);
}
void EditTrackSegmentDlg::on_pbCancel_clicked()
{
 this->close();
}
void EditTrackSegmentDlg::on_pbDone_clicked()
{
 switch(ui->cbStyle->currentIndex())
 {
 default:
 case 0: // solid
  trackSegment->setDashed(false);
  break;
 case 1:
  trackSegment->setDashed(true);
 break;
 }

 switch(ui->cbTrackType->currentIndex())
 {
 default:
 case 1:
  trackSegment->setMainline(true);
  break;
 case 0:
  trackSegment->setMainline(false);
 }
 trackSegment->hidden = ui->chkHide->isChecked();
 QString text = ui->edBlockName->text().trimmed();
 if (trackSegment->getBlockName()!=text )
 {
  // block has changed, if old block exists, decrement use
  if (trackSegment->layoutBlock!=NULL)
  {
   trackSegment->layoutBlock->decrementUse();
  }
  // get new block, or NULL if block has been removed
  trackSegment->blockName =text;
  trackSegment->layoutBlock = trackSegment->layoutEditor->provideLayoutBlock(trackSegment->blockName);
  if (trackSegment->layoutBlock == NULL)
  {
   trackSegment->blockName = "";
  }
  trackSegment->needsRedraw = true;
  //layoutEditor.auxTools.setBlockConnectivityChanged();
  trackSegment->updateBlockInfo();
 }
 // check if a block exists to edit
 if (trackSegment->layoutBlock==NULL)
 {
//     JOptionPane.showMessageDialog(editTrackSegmentFrame,
//             rb.getQString("Error1"),
//             rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(0, tr("Error"), tr("Error1 Block does not exist to edit"));
     return;
 }
// trackSegment->block->editLayoutBlock(editTrackSegmentFrame);  // ??
 trackSegment->layoutEditor->setDirty();
 trackSegment->needsRedraw = true;
 trackSegment->layoutEditor->redrawPanel();
 this->close();
}
void EditTrackSegmentDlg::on_pbEditBlock_clicked()
{
 CreateEditBlock* dlg = new CreateEditBlock(ui->edBlockName->text(), (LayoutEditor*)parent);
 dlg->show();
}
void EditTrackSegmentDlg::on_chkHide_toggled(bool bChecked)
{
 trackSegment->setHidden(bChecked);
}
