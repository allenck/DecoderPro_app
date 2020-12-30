#include "restoredialog.h"
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QBoxLayout>
#include "flowlayout.h"
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include "backupbase.h"
#include "autobackup.h"
#include "defaultbackup.h"
#include "operationsxml.h"
#include <QMessageBox>
#include "rosterentry.h"
#include "backupset.h"
#include "operationsmanager.h"
#include "apps.h"

//RestoreDialog::RestoreDialog(QWidget *parent) :
//  JDialog(parent)
//{
//}
namespace Operations
{
 // /*public*/ class RestoreDialog extends JDialog {

 /**
  * Create the dialog.
  */
 /*public*/ RestoreDialog::RestoreDialog(QWidget *parent) : JDialog(parent)
 {
  log = new Logger("RestoreDialog");
  initComponents();
 }

 /*private*/ void RestoreDialog::initComponents()
{
//        setModalityType(ModalityType.DOCUMENT_MODAL);
     setModal(true);

     setTitle(tr("Restore OperationsPro Files"));
     setGeometry(100, 100, 378, 251);
     //mainPanel = new QWidget();
     //mainPanel.setLayout(new BorderLayout());
     //mainPanel.setBorder(null);
     //setContentPane(mainPanel);
     QVBoxLayout* mainPanelLayout = (QVBoxLayout*)getContentPane()->layout();
     {

         contentPanel = new QWidget();
         //contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
         QVBoxLayout* contentPanelLayout;
         contentPanel->setLayout(contentPanelLayout = new QVBoxLayout(contentPanel)); //, BoxLayout.Y_AXIS));
         mainPanelLayout->addWidget(contentPanel, /*BorderLayout.NORTH)*/0, Qt::AlignTop);

         {
             QGroupBox* panel = new QGroupBox();
             //panel.setAlignmentX(Component.LEFT_ALIGNMENT);
             FlowLayout* panelLayout;
             panel->setLayout(panelLayout = new FlowLayout(/*FlowLayout.LEFT*/));
            // panel.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), // NOI18N
             QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
//                tr("Select backup store to use:"), TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 0, 0))); // NOI18N
             panel->setStyleSheet(gbStyleSheet);
             panel->setTitle("");

             contentPanelLayout->addWidget(panel);
             QButtonGroup* fromGroup = new QButtonGroup();

             {
                 automaticBackupsRadioButton = new QRadioButton(tr("Automatic backups"));
//                    automaticBackupsRadioButton.addActionListener(new ActionListener() {
//                        /*public*/ void actionPerformed(ActionEvent e) {
//                            do_automaticBackupsRadioButton_actionPerformed(e);
//                        }
//                    });
                 connect(automaticBackupsRadioButton, SIGNAL(clicked()), this, SLOT(do_automaticBackupsRadioButton_actionPerformed()));
                 panelLayout->addWidget(automaticBackupsRadioButton);
                 fromGroup->addButton(automaticBackupsRadioButton);
             }
             {
                 defaultBackupsRadioButton = new QRadioButton(tr("Manual backups"));
//                    defaultBackupsRadioButton.addActionListener(new ActionListener() {
//                        /*public*/ void actionPerformed(ActionEvent e) {
//                            do_defaultBackupsRadioButton_actionPerformed(e);
//                        }
//                    });
                 connect(defaultBackupsRadioButton, SIGNAL(clicked()), this, SLOT(do_defaultBackupsRadioButton_actionPerformed()));
                 panelLayout->addWidget(defaultBackupsRadioButton);
                 fromGroup->addButton(defaultBackupsRadioButton);
             }
         }

         {
             newLabelLabel = new QLabel(tr("and the specific backup set directory:"));
             //newLabelLabel.setBorder(new EmptyBorder(10, 0, 5, 0));
             contentPanelLayout->addWidget(newLabelLabel);
         }
         {
             comboBox = new QComboBox();
//                comboBox.addItemListener(new ItemListener() {
//                    /*public*/ void itemStateChanged(ItemEvent arg0) {
//                        do_comboBox_itemStateChanged(arg0);
//                    }
//                });
             connect(comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(do_comboBox_itemStateChanged()));
             //comboBox.setAlignmentX(Component.LEFT_ALIGNMENT);
             contentPanelLayout->addWidget(comboBox, 0, Qt::AlignLeft);
         }
     }

     {
         QWidget* buttonPane = new QWidget();
         FlowLayout* fl_buttonPane = new FlowLayout(/*FlowLayout.CENTER*/);
         buttonPane->setLayout(fl_buttonPane);
         mainPanelLayout->addWidget(buttonPane, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);
         {
             restoreButton = new QPushButton(tr("Restore"));
//                restoreButton.addActionListener(new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        do_restoreButton_actionPerformed(e);
//                    }
//                });
             connect(restoreButton, SIGNAL(clicked()), this, SLOT(do_restoreButton_actionPerformed()));
             fl_buttonPane->addWidget(restoreButton);
         }
         {
             QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//                cancelButton.addActionListener(new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent arg0) {
//                        do_cancelButton_actionPerformed(arg0);
//                    }
//                });
             connect(cancelButton, SIGNAL(clicked()), this, SLOT(do_cancelButton_actionPerformed()));
             fl_buttonPane->addWidget(cancelButton);
         }
     }

     // Start out with Default backups
     defaultBackupsRadioButton->click();

 }

 // Event handlers
 /*protected*/ void RestoreDialog::do_automaticBackupsRadioButton_actionPerformed(JActionEvent* /*e*/) {
     backup = new AutoBackup();
     loadComboBox();
 }

 /*protected*/ void RestoreDialog::do_defaultBackupsRadioButton_actionPerformed(JActionEvent* /*e*/) {
     backup = new DefaultBackup();
     loadComboBox();
 }

 /*protected*/ void RestoreDialog::do_cancelButton_actionPerformed(JActionEvent* /*arg0*/) {
     //dispose();
  reject();
  close();
 }

 /*protected*/ void RestoreDialog::do_comboBox_itemStateChanged(ItemEvent* /*arg0*/) {
     // If something has been selected, enable the Restore
     // button.
     // If we only have a deselect, then the button will remain disabled.
     // When changing between items in the list, the item being left is
     // deselected first, then the new item is selected.
     //
     // Not sure if there can be more than two states, so using the if
     // statement to be safe.
#if 0
     int stateChange = arg0.getStateChange();

     if (stateChange == ItemEvent.SELECTED) {
         restoreButton->setEnabled(true);
     } else if (stateChange == ItemEvent.DESELECTED) {
         restoreButton->setEnabled(false);
     }
#endif
     if(comboBox->currentText() == "")
      restoreButton->setEnabled(false);
     else
      restoreButton->setEnabled(true);

   \
 }

 /*protected*/ void RestoreDialog::do_helpButton_actionPerformed(JActionEvent* /*arg0*/) {
     // Not implemented yet.
 }

 /*protected*/ void RestoreDialog::do_restoreButton_actionPerformed(JActionEvent* /*e*/) {
     log->debug("restore button activated");

     // check to see if files are dirty
     if (OperationsXml::areFilesDirty()) {
//         if (JOptionPane.showConfirmDialog(this, tr("OperationsFilesModified"),
//                 tr("SaveOperationFiles"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
      if(QMessageBox::question(this, tr("Save operation files?"), tr("Operations files have been modified, do you want to save them?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
         {
             OperationsXml::save();
         }
     }

     // first backup the users data in case they forgot
     //try {
         AutoBackup* _auto = new AutoBackup();
         _auto->autoBackup();

         // now delete the current operations files in case the restore isn't a full set of files
         backup->deleteOperationsFiles();

         setName = ((BackupSet*)VPtr<BackupSet*>::asPtr( comboBox->itemData(comboBox->currentIndex())))->getSetName();

         // The restore method should probably be overloaded to accept a
         // BackupSet instead of a simple string. Later.
         backup->restoreFilesFromSetName(setName);

         // now deregister shut down task
         // If Trains window was opened, then task is active
         // otherwise it is normal to not have the task running
         OperationsManager::getInstance()->setShutDownTask(NULL);

//         JOptionPane.showMessageDialog(this, tr("YouMustRestartAfterRestore"),
//                 tr("RestoreSuccessful"), JOptionPane.INFORMATION_MESSAGE);
         QMessageBox::information(this, tr("Restore successful!"), tr("You must restart JMRI to complete the restore operation"));
        // dispose();
         close();

         Apps::handleRestart();
//     } // These may need to be enhanced to show the backup store being used,
//       // auto or default.
//     catch (IOException ex) {
//         ExceptionContext context = new ExceptionContext(ex, tr("RestoreDialog.restoring")
//                 + " " + setName, "Hint about checking valid names, etc."); // NOI18N
//         new ExceptionDisplayFrame(context);

//     } catch (Exception ex) {
//         log.error("Doing restore from " + setName, ex);

//         UnexpectedExceptionContext context = new UnexpectedExceptionContext(ex,
//                 tr("RestoreDialog.restoring") + " " + setName);

//         new ExceptionDisplayFrame(context);
//     }
 }

 /**
  * Adds the names of the backup sets that are available in either the
  * Automatic or the Default backup store.
  */
 /*private*/ void RestoreDialog::loadComboBox() {
     // Get the Backup Sets from the currently selected backup store.
     // Called after the radio button selection has changed

     // Disable the Restore button in case there is nothing loaded into the ComboBox
     restoreButton->setEnabled(false);

     comboBox->clear();

     QList<BackupSet*> sets = backup->getBackupSets();
     //ComboBoxModel<BackupSet> model = new DefaultComboBoxModel<BackupSet>(sets);

     // Clear any current selection so that the state change will fire when
     // we set a selection.
     //model.setSelectedItem(null);

     //comboBox.setModel(model);
     foreach(BackupSet* s, sets)
     {
      comboBox->addItem(s->getSetName(), VPtr<BackupSet>::asQVariant(s));
     }

     // Position at the last item, which is usually the most recent
     // This is ugly code, but it works....
     if (comboBox->count() > 0) {
         comboBox->setCurrentIndex(comboBox->count() - 1);
     }
 }
}
