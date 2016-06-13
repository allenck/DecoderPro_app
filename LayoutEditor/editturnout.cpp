#include "editturnout.h"
#include "ui_editturnout.h"
#include "layoutturnout.h"
#include <QMessageBox>
#include "layoutblock.h"
#include "createeditblock.h"

EditTurnout::EditTurnout(LayoutTurnout* to, QWidget *parent) :
    JmriJFrame(parent),
    ui(new Ui::EditTurnout)
{
 ui->setupUi(this);
 this->to = to;
 this->parent = parent;
 type = this->to->type;
 if(type == LayoutTurnout::DOUBLE_XOVER || type == LayoutTurnout::RH_XOVER || type ==LayoutTurnout::LH_XOVER)
 {
  ui->blockBNameField->setVisible(true);
  ui->blockBNameLabel->setVisible(true);
  ui->blockCNameLabel->setVisible(true);
  ui->blockCNameField->setVisible(true);
  ui->blockDNameField->setVisible(true);
  ui->blockDNameLabel->setVisible(true);
  ui->turnoutEditBlockB->setVisible(true);
  ui->turnoutEditBlockC->setVisible(true);
  ui->turnoutEditBlockD->setVisible(true);
  ui->additionalTurnout->setVisible(true);
  ui->secondTurnoutLabel->setVisible(true);
  ui->secondTurnoutComboBox->setVisible(true);
 }
 else
 {
  ui->blockBNameField->setVisible(false);
  ui->blockBNameLabel->setVisible(false);
  ui->blockCNameLabel->setVisible(false);
  ui->blockCNameField->setVisible(false);
  ui->blockDNameField->setVisible(false);
  ui->blockDNameLabel->setVisible(false);
  ui->turnoutEditBlockB->setVisible(false);
  ui->turnoutEditBlockC->setVisible(false);
  ui->turnoutEditBlockD->setVisible(false);
  ui->additionalTurnout->setVisible(false);
  ui->secondTurnoutLabel->setVisible(false);
  ui->secondTurnoutComboBox->setVisible(false);
 }
 // add continuing state choice, if not crossover
 if ( (type != LayoutTurnout::DOUBLE_XOVER) && (type != LayoutTurnout::RH_XOVER) && (type != LayoutTurnout::LH_XOVER) )
 {
//                 JPanel panel3 = new JPanel();
//                 panel3.setLayout(new FlowLayout());
//                 stateBox.removeAllItems();
//                 stateBox.addItem( InstanceManager.turnoutManagerInstance().getClosedText() );
  ui->stateBox->clear();
  ui->stateBox->addItem(tr("Closed"));
  turnoutClosedIndex = 0;
//                 stateBox.addItem( InstanceManager.turnoutManagerInstance().getThrownText() );
  ui->stateBox->addItem(tr("Thrown"));
  turnoutThrownIndex = 1;
//                 stateBox.setToolTipText(rb.getString("StateToolTip"));
  ui->stateBox->setToolTip(tr("Select turnout state corresponding to continuing route."));
//                 panel3.add (new JLabel(rb.getString("ContinuingState")));
//                 panel3.add (stateBox);
//                 contentPane.add(panel3);
 }
 ui->hiddenBox->setChecked(to->hidden);
 // Set up for Edit
 ui->blockNameField->setText(to->blockName);
 if ( (type ==LayoutTurnout:: DOUBLE_XOVER) || (type == LayoutTurnout::RH_XOVER) || (type == LayoutTurnout::LH_XOVER) )
 {
  ui->blockBNameField->setText(to->blockBName);
  ui->blockCNameField->setText(to->blockCName);
  ui->blockDNameField->setText(to->blockDName);
 }
 ui->turnoutNameField->setText(to->turnoutName);

 if(to->secondNamedTurnout!=NULL)
 {
  ui->additionalTurnout->setChecked(true);
  ui->secondTurnoutLabel->setEnabled(true);
  ui->secondTurnoutComboBox->setEnabled(true);
 }
 if ( (type != LayoutTurnout::DOUBLE_XOVER) && (type != LayoutTurnout::RH_XOVER) && (type != LayoutTurnout::LH_XOVER) )
 {
  if (to->continuingSense==Turnout::CLOSED)
  {
   ui->stateBox->setCurrentIndex(turnoutClosedIndex);
  }
  else
  {
   ui->stateBox->setCurrentIndex(turnoutThrownIndex);
  }
 }
 to->needsBlockUpdate = false;
 ui->secondTurnoutComboBox->clear();
 ui->secondTurnoutComboBox->addItems(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getSystemNameList());
}

EditTurnout::~EditTurnout()
{
    delete ui;
}
void EditTurnout::on_additionalTurnout_toggled(bool bChecked)
{
 if(bChecked)
 {
  ui->secondTurnoutLabel->setVisible(true);
  ui->secondTurnoutComboBox->setVisible(true);
 }
 else
 {
  ui->secondTurnoutLabel->setVisible(false);
  ui->secondTurnoutComboBox->setVisible(false);
 }
}
void EditTurnout::on_turnoutEditBlock_clicked()
{
 // check if a block name has been entered
 if (!(to->blockName==(ui->blockNameField->text().trimmed())) )
 {
  // block has changed, if old block exists, decrement use
  if ( (to->block!=NULL) && (to->block!=to->blockB) && (to->block!=to->blockC)
                        && (to->block!=to->blockD) )
  {
   to->block->decrementUse();
  }
  // get new block, or NULL if block has been removed
  to->blockName = ui->blockNameField->text().trimmed();
  to->block = to->layoutEditor->provideLayoutBlock(to->blockName);
  if (to->block==NULL)
  {
   to->blockName = "";
  }
  // decrement use if block was already counted
  if ( (to->block!=NULL) && ( (to->block==to->blockB) || (to->block==to->blockC) ||
                (to->block==to->blockD) ) )
   to->block->decrementUse();
   to->needRedraw = true;
   to->needsBlockUpdate = true;
  }
  // check if a block exists to edit
  if (to->block==NULL)
  {
//        JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
//                rb.getQString("Error1"),
//                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this,tr("Block not found"), tr("Cannot edit block without a name. Please enter a block name and try again"), QMessageBox::Ok);
   return;
  }
  //to->block->editLayoutBlock(to->editLayoutTurnoutFrame);
  CreateEditBlock* dlg = new CreateEditBlock(to->block->getUserName(), (MyLayoutEditor*) parent);
  dlg->show();
  to->needRedraw = true;
  to->layoutEditor->setDirty();
}
void EditTurnout::on_turnoutEditBlockB_clicked()
{
 // check if a block name has been entered
 if (!(to->blockBName==(ui->blockBNameField->text().trimmed())) )
 {
  // block has changed, if old block exists, decrement use
  if ( (to->blockB!=NULL) && (to->block!=to->blockB) && (to->blockB!=to->blockC)
                        && (to->blockB!=to->blockD) )
  {
   to->blockB->decrementUse();
  }
  // get new block, or NULL if block has been removed
  to->blockBName = ui->blockBNameField->text().trimmed();
  to->blockB = to->layoutEditor->provideLayoutBlock(to->blockBName);
  if (to->blockB==NULL)
  {
   to->blockBName = "";
  }
  // decrement use if block was already counted
  if ( (to->blockB!=NULL) && ( (to->block==to->blockB) || (to->blockB==to->blockC) ||
            (to->blockB==to->blockD) ) )
   to->blockB->decrementUse();
  to->needRedraw = true;
  to->needsBlockUpdate = true;
 }
 // check if a block exists to edit
 if (to->blockB==NULL)
 {
//        JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
//                rb.getQString("Error1"),
//                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("Error"), tr("Block doesn't exist"));
  return;
 }
 //to->blockB->editLayoutBlock(to->editLayoutTurnoutFrame);
 CreateEditBlock* dlg = new CreateEditBlock(to->blockB->getUserName(), (MyLayoutEditor*) parent);
 dlg->show();
 to->needRedraw = true;
 to->layoutEditor->setDirty();
}
void EditTurnout::on_turnoutEditBlockC_clicked()
{
 // check if a block name has been entered
    if (!(to->blockCName==(ui->blockCNameField->text().trimmed()) ))
 {
  // block has changed, if old block exists, decrement use
  if ( (to->blockC!=NULL) && (to->block!=to->blockC) && (to->blockB!=to->blockC)
                && (to->blockC!=to->blockD) )
  {
   to->blockC->decrementUse();
  }
  // get new block, or NULL if block has been removed
  to->blockCName = ui->blockCNameField->text().trimmed();
  to->blockC = to->layoutEditor->provideLayoutBlock(to->blockCName);
  if (to->blockC==NULL)
  {
    to->blockCName = "";
  }
  // decrement use if block was already counted
  if ( (to->blockC!=NULL) && ( (to->block==to->blockC) || (to->blockB==to->blockC) ||
        (to->blockC==to->blockD) ) )
   to->blockD->decrementUse();
  to->needRedraw = true;
  to->needsBlockUpdate = true;
 }
 // check if a block exists to edit
 if (to->blockC==NULL)
 {
//        JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
//                rb.getQString("Error1"),
//                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("Error"), tr("Block doesn't exist"));
  return;
 }
 //to->blockC->editLayoutBlock(/*to->editLayoutTurnoutFrame*/this);
 CreateEditBlock* dlg = new CreateEditBlock(to->blockC->getUserName(), (MyLayoutEditor*) parent);
 dlg->show();
 to->needRedraw = true;
 to->layoutEditor->setDirty();
}
void EditTurnout::on_turnoutEditBlockD_clicked()
{
 // check if a block name has been entered
 if (!(to->blockDName==(ui->blockDNameField->text().trimmed())) )
 {
  // block has changed, if old block exists, decrement use
  if ( (to->blockD!=NULL) && (to->block!=to->blockD) && (to->blockB!=to->blockD)
                    && (to->blockC!=to->blockD) )
  {
   to->blockD->decrementUse();
  }
  // get new block, or NULL if block has been removed
  to->blockDName = ui->blockDNameField->text().trimmed();
  to->blockD = to->layoutEditor->provideLayoutBlock(to->blockDName);
  if (to->blockD==NULL)
  {
   to->blockDName = "";
  }
  // decrement use if block was already counted
  if ( (to->blockD!=NULL) && ( (to->block==to->blockD) || (to->blockB==to->blockD) ||
            (to->blockC==to->blockD) ) )
   to->blockD->decrementUse();
  to->needRedraw = true;
  to->needsBlockUpdate = true;
  }
  // check if a block exists to edit
  if (to->blockD==NULL)
  {
//        JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
//                rb.getQString("Error1"),
//                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Error"), tr("Block doesn't exist"));
   return;
  }
  //to->blockD->editLayoutBlock(to->editLayoutTurnoutFrame);
  CreateEditBlock* dlg = new CreateEditBlock(to->blockD->getUserName(), (MyLayoutEditor*) parent);
  dlg->show();
  to->needRedraw = true;
  to->layoutEditor->setDirty();
}
void EditTurnout::on_turnoutEditDone_clicked()
{
 // check if Turnout changed
 if ((to->turnoutName != (ui->turnoutNameField->text().trimmed())) )
 {
  // turnout has changed
  QString newName = ui->turnoutNameField->text().trimmed();
  if ( to->layoutEditor->validatePhysicalTurnout(newName/*,
                        to->editLayoutTurnoutFrame*/) )
  {
   to->setTurnout(newName);
  }
  else
  {
   to->namedTurnout = NULL;
   to->turnoutName = "";
   ui->turnoutNameField->setText("");
  }
  to->needRedraw = true;
 }

 if(ui->additionalTurnout->isChecked())
 {
  if ( !(to->secondTurnoutName==(ui->secondTurnoutComboBox->currentText())) )
  {
   if ( (type == LayoutTurnout::DOUBLE_XOVER) || (type == LayoutTurnout::RH_XOVER) || (type == LayoutTurnout::LH_XOVER) )
   {
    // turnout has changed
    QString newName = ui->secondTurnoutComboBox->currentText();
    if ( to->layoutEditor->validatePhysicalTurnout(newName/*,
                        to->editLayoutTurnoutFrame*/) )
    {
     to->setSecondTurnout(newName);
    }
    else
    {
     ui->additionalTurnout->setChecked(false);
     to->secondNamedTurnout = NULL;
     to->secondTurnoutName = "";
     //secondTurnoutNameField.setText("");
    }
    to->needRedraw = true;
    }
    else
    {
     to->setSecondTurnout(ui->secondTurnoutComboBox->currentText());
    }
   }
  }
  else
  {
   to->setSecondTurnout(NULL);
  }
  // set the continuing route Turnout State
  if ( (type==LayoutTurnout::RH_TURNOUT) || (type==LayoutTurnout::LH_TURNOUT) || (type==LayoutTurnout::WYE_TURNOUT) )
  {
   to->continuingSense = Turnout::CLOSED;
   if ( ui->stateBox->currentIndex() == turnoutThrownIndex )
   {
    to->continuingSense = Turnout::THROWN;
   }
  }
  // check if Block changed
  if ( !(to->blockName==(ui->blockNameField->text().trimmed()) ))
  {
   // block has changed, if old block exists, decrement use
   if ( (to->block!=NULL) && (to->block!=to->blockB) && (to->block!=to->blockC) &&
                (to->block!=to->blockD) )
   {
    to->block->decrementUse();
   }
   // get new block, or NULL if block has been removed
   to->blockName = ui->blockNameField->text().trimmed();
   to->block = to->layoutEditor->provideLayoutBlock(to->blockName);
   if (to->block==NULL)
   {
    to->blockName = "";
   }
   // decrement use if block was already counted
   if ( (to->block!=NULL) && ( (to->block==to->blockB) || (to->block==to->blockC) ||
            (to->block==to->blockD) ) )
    to->block->decrementUse();
   to->needRedraw = true;
   to->needsBlockUpdate = true;
  }
  if ( (type==LayoutTurnout::DOUBLE_XOVER) || (type==LayoutTurnout::LH_XOVER) || (type==LayoutTurnout::RH_XOVER) )
  {
   // check if Block 2 changed
   if ( !(to->blockBName==(ui->blockBNameField->text().trimmed()) ))
   {
    // block has changed, if old block exists, decrement use
    if ( (to->blockB!=NULL) && (to->block!=to->blockB) && (to->blockB!=to->blockC)
                    && (to->blockB!=to->blockD) )
    {
     to->blockB->decrementUse();
    }
    // get new block, or NULL if block has been removed
    to->blockBName = ui->blockBNameField->text().trimmed();
    to->blockB = to->layoutEditor->provideLayoutBlock(to->blockBName);
    if (to->blockB==NULL)
    {
     to->blockBName = "";
    }
    // decrement use if block was already counted
    if ( (to-> blockB!=NULL) && ( (to->block==to->blockB) || (to->blockB==to->blockC) ||
            (to->blockB==to->blockD) ) )
     to->blockB->decrementUse();
    to->needRedraw = true;
    to->needsBlockUpdate = true;
   }
   // check if Block 3 changed
   if (!(to->blockCName==(ui->blockCNameField->text().trimmed())) )
   {
    // block has changed, if old block exists, decrement use
    if ( (to->blockC!=NULL) && (to->block!=to->blockC) && (to->blockB!=to->blockC)
                    && (to->blockC!=to->blockD) )
    {
     to->blockC->decrementUse();
    }
    // get new block, or NULL if block has been removed
    to->blockCName = ui->blockCNameField->text().trimmed();
    to->blockC = to->layoutEditor->provideLayoutBlock(to->blockCName);
    if (to->blockC==NULL)
    {
     to->blockCName = "";
    }


    // decrement use if block was already counted
    if ( (to->blockC!=NULL) && ( (to->block==to->blockC) || (to->blockB==to->blockC) ||
            (to->blockC==to->blockD) ) )
     to->blockC->decrementUse();
    to->needRedraw = true;
    to->needsBlockUpdate = true;
   }
   // check if Block 4 changed
   if (!(to->blockDName==(ui->blockDNameField->text().trimmed()) ))
   {
    // block has changed, if old block exists, decrement use
    if ( (to->blockD!=NULL) && (to->block!=to->blockD) && (to->blockB!=to->blockD)
                && (to->blockC!=to->blockD) )
    {
     to->blockD->decrementUse();
    }
    // get new block, or NULL if block has been removed
    to->blockDName = ui->blockDNameField->text().trimmed();
    to->blockD = to->layoutEditor->provideLayoutBlock(to->blockDName);
    if (to->blockD==NULL)
    {
     to->blockDName = "";
    }
    // decrement use if block was already counted
    if ( (to->blockD!=NULL) && ( (to->block==to->blockD) || (to->blockB==to->blockD) ||
            (to->blockC==to->blockD) ) )
     to->blockD->decrementUse();
    to->needRedraw = true;
    to->needsBlockUpdate = true;
   }
  }
  // set hidden
  bool oldHidden = to->hidden;
  to->hidden = ui->hiddenBox->isChecked();
  if(oldHidden!=to->hidden)
   to->needRedraw=true;
  to->editOpen = false;
  to->editLayoutTurnoutFrame->setVisible(false);
  //to->editLayoutTurnoutFrame->dispose();
  to->editLayoutTurnoutFrame = NULL;
  if (to->needsBlockUpdate)
  {
   to->updateBlockInfo();
   to->reCheckBlockBoundary();
  }
 if (to->needRedraw)
 {
  to->layoutEditor->redrawPanel();
  to->layoutEditor->setDirty();
 }
 //accept();
 close();
}
void EditTurnout::on_turnoutEditCancel_clicked()
{
 to->editOpen = false;
 to->editLayoutTurnoutFrame->setVisible(false);
 //to->editLayoutTurnoutFrame->dispose();
 to->editLayoutTurnoutFrame = NULL;
 if (to->needsBlockUpdate) to->updateBlockInfo();
 if (to->needRedraw)
 {
  to->layoutEditor->redrawPanel();
  to->layoutEditor->setDirty();
 }
 //reject();
 close();
}
void EditTurnout::on_blockNameField_textEdited(QString text)
{
 QCompleter* completer;
 if((completer = InstanceManager::blockManagerInstance()->getCompleter(text)) != NULL)
  ui->blockNameField->setCompleter(completer);
}
void EditTurnout::on_blockBNameField_textEdited(QString text)
{
 QCompleter* completer;
 if((completer = InstanceManager::blockManagerInstance()->getCompleter(text)) != NULL)
  ui->blockBNameField->setCompleter(completer);
}
void EditTurnout::on_blockCNameField_textEdited(QString text)
{
 QCompleter* completer;
 if((completer = InstanceManager::blockManagerInstance()->getCompleter(text)) != NULL)
  ui->blockCNameField->setCompleter(completer);
}
void EditTurnout::on_blockDNameField_textEdited(QString text)
{
 QCompleter* completer;
 if((completer = InstanceManager::blockManagerInstance()->getCompleter(text)) != NULL)
  ui->blockDNameField->setCompleter(completer);
}
