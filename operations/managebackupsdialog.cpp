#include "managebackupsdialog.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include "jlist.h"
#include "autobackup.h"
#include "backupset.h"
#include "box.h"
#include "joptionpane.h"


namespace Operations
{

///*public*/ class ManageBackupsDialog extends JDialog {

 /**
  *
  */

 /**
  * Create the dialog.
  */
 /*public*/ ManageBackupsDialog::ManageBackupsDialog(QWidget* parent) : JDialog(parent)
 {
     // For now we only support Autobackups, but this can be updated later if
     // needed.
     backup = new AutoBackup();
     contentPanel = new QWidget();
     initComponents();
 }

 /*private*/ void ManageBackupsDialog::initComponents()
 {
//      setModalityType(ModalityType.DOCUMENT_MODAL);
//      setModal(true);
      setTitle(tr("Manage Backup Sets"));
      //setBounds(100, 100, 461, 431);
//      resize(461, 431);
//      BorderLayout borderLayout = new BorderLayout();
//      borderLayout.setVgap(5);
//      borderLayout.setHgap(5);
      QVBoxLayout* thisLayout = new QVBoxLayout(this);

      //getContentPane().setLayout(/*borderLayout*/);
      //contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
      thisLayout->addWidget(contentPanel, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
      GridBagLayout* gbl_contentPanel = new GridBagLayout();
//      gbl_contentPanel.columnWidths = new int[]{0, 0};
//      gbl_contentPanel.rowHeights = new int[]{0, 0, 0};
//      gbl_contentPanel.columnWeights = new double[]{1.0, Double.MIN_VALUE};
//      gbl_contentPanel.rowWeights = new double[]{0.0, 1.0, Double.MIN_VALUE};
      contentPanel->setLayout(gbl_contentPanel);
      {
          selectBackupSetsLabel = new QLabel(tr("Select Backup Sets to delete. Use Ctrl-Click to select multiple sets."));
          GridBagConstraints* gbc_selectBackupSetsLabel = new GridBagConstraints();
          gbc_selectBackupSetsLabel->anchor = GridBagConstraints::WEST;
          gbc_selectBackupSetsLabel->insets = new Insets(0, 0, 5, 0);
          gbc_selectBackupSetsLabel->gridx = 0;
          gbc_selectBackupSetsLabel->gridy = 0;
          gbl_contentPanel->addWidget(selectBackupSetsLabel, *gbc_selectBackupSetsLabel);
      }
      {
          scrollPane = new QScrollArea();
          GridBagConstraints* gbc_scrollPane = new GridBagConstraints();
          gbc_scrollPane->fill = GridBagConstraints::BOTH;
          gbc_scrollPane->gridx = 0;
          gbc_scrollPane->gridy = 1;
//          gbl_contentPanel->addWidget(scrollPane, *gbc_scrollPane);
          {
              setList =  new JList(); //<BackupSet*>();
              //setList->setVisibleRowCount(20);
              setList->setSelectionMode(QAbstractItemView::MultiSelection);

              model = new DefaultListModel(); //<BackupSet*>();

              // Load up the list control with the available BackupSets
              foreach (BackupSet* bs, backup->getBackupSets())
              {
               QVariant var;
               var.setValue(*bs);
                  model->addElement(bs->toString());
              }

              setList->setModel(model);

              // Update button states based on if anything is selected in the
              // list.
//              setList.addListSelectionListener(new ListSelectionListener() {
//                  @Override
//                  /*public*/ void valueChanged(ListSelectionEvent e) {
//                      updateButtonStates();
//                  }
//              });

              connect(setList, SIGNAL(clicked(QModelIndex)), this, SLOT(updateButtonStates()));
              //scrollPane.setViewportView(setList);
              //scrollPane->setWidget(setList);
              gbl_contentPanel->addWidget(setList, *gbc_scrollPane);
          }
      }
      {
          QWidget* buttonPane = new QWidget();
          //buttonPane.setBorder(new EmptyBorder(5, 5, 5, 5));
          buttonPane->setLayout(new QHBoxLayout);//(buttonPane, BoxLayout.X_AXIS));
          thisLayout->addWidget(buttonPane, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);
          {
              selectAllButton = new QPushButton(tr("Select All"));
//              selectAllButton.addActionListener(new ActionListener() {
//                  /*public*/ void actionPerformed(ActionEvent e) {
//                      do_selectAllButton_actionPerformed(e);
//                  }
//              });
              connect(selectAllButton, SIGNAL(clicked(bool)), this, SLOT(do_selectAllButton_actionPerformed()));
              buttonPane->layout()->addWidget(selectAllButton);
          }
          {
              horizontalStrut = Box::createHorizontalStrut(10);
              buttonPane->layout()->addWidget(horizontalStrut);
          }
          {
              clearAllButton = new QPushButton(tr("Clear All"));
//              clearAllButton.addActionListener(new ActionListener() {
//                  /*public*/ void actionPerformed(ActionEvent e) {
//                      do_clearAllButton_actionPerformed(e);
//                  }
//              });
              connect(clearAllButton, SIGNAL(clicked(bool)), this, SLOT(do_clearAllButton_actionPerformed()));
              buttonPane->layout()->addWidget(clearAllButton);
          }
          {
              horizontalGlue = Box::createHorizontalGlue();
              buttonPane->layout()->addWidget(horizontalGlue);
          }
          {
              deleteButton = new QPushButton(tr("Delete"));
//              deleteButton.addActionListener(new ActionListener() {
//                  /*public*/ void actionPerformed(ActionEvent e) {
//                      do_deleteButton_actionPerformed(e);
//                  }
//              });
              //deleteButton.setActionCommand("");
              connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(do_deleteButton_actionPerformed()));
              buttonPane->layout()->addWidget(deleteButton);
          }
          {
              horizontalStrut_1 = Box::createHorizontalStrut(10);
              buttonPane->layout()->addWidget(horizontalStrut_1);
          }
          {
              QPushButton* closeButton = new QPushButton(tr("Cancel"));
//              closeButton.addActionListener(new ActionListener() {
//                  /*public*/ void actionPerformed(ActionEvent e) {
//                      do_cancelButton_actionPerformed(e);
//                  }
//              });
              connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(do_cancelButton_actionPerformed()));
              //closeButton.setActionCommand("Cancel"); // NOI18N
              //getRootPane().setDefaultButton(closeButton);
              buttonPane->layout()->addWidget(closeButton);
          }
          {
              horizontalStrut_2 = Box::createHorizontalStrut(10);
              buttonPane->layout()->addWidget(horizontalStrut_2);
          }
          // {
          // helpButton = new JButton(tr("BackupDialog.helpButton.text"));
          // helpButton.addActionListener(new ActionListener() {
          // /*public*/ void actionPerformed(ActionEvent e) {
          // do_helpButton_actionPerformed(e);
          // }
          // });
          // helpButton.setEnabled(false);
          // buttonPane.add(helpButton);
          // }
      }

      updateButtonStates();
 }

 /*protected*/ void ManageBackupsDialog::do_cancelButton_actionPerformed() {
     //dispose();
     reject();
     close();

 }

 /*protected*/ void ManageBackupsDialog::do_clearAllButton_actionPerformed() {
     setList->clearSelection();
     updateButtonStates();
 }

 /*protected*/ void ManageBackupsDialog::do_deleteButton_actionPerformed()
 {
#if 1
      // Here we get the selected items from the list
      //QList<BackupSet> selectedSets = setList.getSelectedValuesList();
  QModelIndexList selectedSets = setList->getSelectedValues();

  if (selectedSets.size() > 0)
  {
   // Make sure OK to delete backups
   int result = JOptionPane::showConfirmDialog(this, tr("You are about to delete %1 Backup Sets. OK to delete them?").arg(selectedSets.size()),
           tr("Deleting Backup Sets"), JOptionPane::OK_CANCEL_OPTION);
   if (result == JOptionPane::OK_OPTION)
   {
           //for (BackupSet set : selectedSets) {
    foreach (QModelIndex mi, selectedSets)
    {
      QString name = mi.data().toString();

      model->removeElementAt(model->indexOf(name));

     // For now, the BackupSet deletes the associated files, but
     // we might want to move this into the BackupBase class just
     // so that it knows what is happening.
     //set.delete();
      QList<BackupSet*> sets= backup->getBackupSets();
      foreach (BackupSet* set, sets) {
       if(set->getSetName() == name)
       {
        set->_delete();
        break;
      }
     }
    }
   }
#endif
  }
 }

  /*protected*/ void ManageBackupsDialog::do_helpButton_actionPerformed() {
      // Not implemented yet.
  }

  /*protected*/ void ManageBackupsDialog::do_selectAllButton_actionPerformed() {
      //setList.setSelectionInterval(0, model.getSize() - 1);
   setList->selectAll();
   updateButtonStates();
  }

  /*private*/ void ManageBackupsDialog::updateButtonStates() {
      // Update the various button enabled states based on what is in the list
      // and what is selected.
      bool notEmpty = setList->getSelectedValues().count()>0;

      deleteButton->setEnabled(notEmpty);
      clearAllButton->setEnabled(notEmpty);

      // Can only select if we have something to select!
      int count = model->rowCount(QModelIndex());
      selectAllButton->setEnabled(count > 0);
  }
}

