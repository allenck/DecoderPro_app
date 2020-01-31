#include "editlevelxingdlg.h"
#include "ui_editlevelxingdlg.h"
#include "createeditblock.h"
#include <QMessageBox>

EditLevelXingDlg::EditLevelXingDlg(LevelXing* x, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLevelXingDlg)
{
    ui->setupUi(this);
    this->x = x;
    this->parent = parent;
    layoutEditor = (LayoutEditor*)parent;
}

EditLevelXingDlg::~EditLevelXingDlg()
{
    delete ui;
}
void EditLevelXingDlg::on_xingEdit1Block_clicked()
{
 // check if a block name has been entered
 if (!(x->blockNameAC==(ui->block1Name->text().trimmed()) ))
 {
  // block 1 has changed, if old block exists, decrement use
  if ( (x->blockAC!=NULL) && (x->blockAC!=x->blockBD) )
  {
   x->blockAC->decrementUse();
  }
  // get new block, or NULL if block has been removed
  x->blockNameAC = ui->block1Name->text().trimmed();
  if ( (x->blockNameAC!=NULL) && (x->blockNameAC.length()>0))
  {
   x->blockAC = layoutEditor->provideLayoutBlock(x->blockNameAC);
   if (x->blockAC!=NULL)
   {
    // decrement use if block was previously counted
    if ( (x->blockAC!=NULL) && (x->blockAC==x->blockBD) ) x->blockAC->decrementUse();
   }
   else
   {
    x->blockNameAC = "";
    x->block1Name->setText("");
   }
  }
  else
  {
   x->blockAC = NULL;
   x->blockNameAC = "";
  }
  x->needsRedraw = true;
  x->layoutEditor->auxTools->setBlockConnectivityChanged();
  x->needsBlockUpdate = true;
 }
 // check if a block exists to edit
 if (x->blockAC==NULL)
 {
//    JOptionPane.showMessageDialog(editLevelXingFrame,
//            rb.getString("Error1"),
//            rb.getString("Error"),JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Error"), tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."));
    return;
 }
 //blockAC.editLayoutBlock(editLevelXingFrame);
 CreateEditBlock* dlg = new CreateEditBlock(x->blockAC->getUserName(), (LayoutEditor*)parent);
 dlg->setVisible(true);
 dlg->show();
 x->needsRedraw = true;
}
void EditLevelXingDlg::on_xingEdit2Block_clicked()
{
 // check if a block name has been entered
    if (!(x->blockNameBD==(ui->block2Name->text().trimmed())) )
 {
  // block has changed, if old block exists, decrement use
  if ( (x->blockBD!=NULL) && (x->blockBD!=x->blockAC) )
  {
   x->blockBD->decrementUse();
  }
  // get new block, or NULL if block has been removed
  x->blockNameBD = ui->block2Name->text().trimmed();
  if ( (x->blockNameBD!=NULL) && (x->blockNameBD.length()>0))
  {
   x->blockBD = layoutEditor->provideLayoutBlock(x->blockNameBD);
   if (x->blockBD!=NULL)
   {
    // decrement use if block was previously counted
    if ( (x->blockBD!=NULL) && (x->blockAC==x->blockBD) ) x->blockBD->decrementUse();
   }
   else
   {
    x->blockNameBD = "";
    x->block2Name->setText("");
   }
  }
  else
  {
   x->blockBD = NULL;
   x->blockNameBD = "";
  }
  x->needsRedraw = true;
  layoutEditor->auxTools->setBlockConnectivityChanged();
  x->needsBlockUpdate = true;
 }
 // check if a block exists to edit
 if (x->blockBD==NULL)
 {
//    JOptionPane.showMessageDialog(editLevelXingFrame,
//            rb.getString("Error1"),
//            rb.getString("Error"),JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("Error"), tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."));
  return;
 }
 //blockBD.editLayoutBlock(editLevelXingFrame);
 CreateEditBlock dlg(x->blockBD->getUserName(), (LayoutEditor*)parent);
 dlg.show();
 x->needsRedraw = true;
}
void EditLevelXingDlg::on_xingEditDone_clicked()
{
 // check if Blocks changed
 if ( !(x->blockNameAC==(ui->block1Name->text().trimmed())) )
 {
  // block 1 has changed, if old block exists, decrement use
  if ( (x->blockAC!=NULL) && (x->blockAC!=x->blockBD) )
  {
   x->blockAC->decrementUse();
  }
  // get new block, or NULL if block has been removed
  x->blockNameAC = ui->block1Name->text().trimmed();
  if ( (x->blockNameAC!=NULL) && (x->blockNameAC.length()>0))
  {
   x->blockAC = layoutEditor->provideLayoutBlock(x->blockNameAC);
   if (x->blockAC!=NULL)
   {
    // decrement use if block was previously counted
    if ( (x->blockAC!=NULL) && (x->blockAC==x->blockBD) ) x->blockAC->decrementUse();
   }
   else
   {
    x->blockNameAC = "";
    x->block1Name->setText("");
   }
  }
  else
  {
   x->blockAC = NULL;
   x->blockNameAC = "";
  }
  x->needsRedraw = true;
  layoutEditor->auxTools->setBlockConnectivityChanged();
  x->needsBlockUpdate = true;
 }
 if ( !(x->blockNameBD==(ui->block2Name->text().trimmed())) )
 {
  // block 2 has changed, if old block exists, decrement use
  if ( (x->blockBD!=NULL) && (x->blockBD!=x->blockAC) )
  {
   x->blockBD->decrementUse();
  }
  // get new block, or NULL if block has been removed
  x->blockNameBD = ui->block2Name->text().trimmed();
  if ( (x->blockNameBD!=NULL) && (x->blockNameBD.length()>0))
  {
   x->blockBD = layoutEditor->provideLayoutBlock(x->blockNameBD);
   if (x->blockBD!=NULL)
   {
    // decrement use if block was previously counted
    if ( (x->blockBD!=NULL) && (x->blockAC==x->blockBD) ) x->blockBD->decrementUse();
   }
   else
   {
    x->blockNameBD = "";
    x->block2Name->setText("");
   }
  }
  else
  {
   x->blockBD = NULL;
   x->blockNameBD = "";
  }
  x->needsRedraw = true;
  layoutEditor->auxTools->setBlockConnectivityChanged();
  x->needsBlockUpdate = true;
 }
 x->editOpen = false;
//   x->editLevelXingFrame.setVisible(false);
//   editLevelXingFrame.dispose();
//   editLevelXingFrame = NULL;
 if (x->needsBlockUpdate) x->updateBlockInfo();
 if (x->needsRedraw)
 {
  layoutEditor->redrawPanel();
  layoutEditor->setDirty();
 }
 accept();
 close();
}
void EditLevelXingDlg::on_xingEditCancel_clicked()
{
 x->editOpen = false;
//            editLevelXingFrame.setVisible(false);
//            editLevelXingFrame.dispose();
//            editLevelXingFrame = NULL;
 if (x->needsBlockUpdate) x->updateBlockInfo();
 if (x->needsRedraw)
 {
  layoutEditor->redrawPanel();
  layoutEditor->setDirty();
 }
}
void EditLevelXingDlg::on_block1Name_editingFinished(QString text)
{
 QCompleter* completer = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getCompleter(text);
 if(completer)
  ui->block1Name->setCompleter(completer);
}
void EditLevelXingDlg::on_block2Name_editingFinished(QString text)
{
 QCompleter* completer = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getCompleter(text);
 if(completer)
  ui->block2Name->setCompleter(completer);
}
