#include "backupdialog.h"
#include <QBoxLayout>
#include "gridbagconstraints.h"
#include <QGridLayout>
#include "jtextfield.h"
#include <QLabel>
#include <QPushButton>
#include "flowlayout.h"
#include "defaultbackup.h"
#include "operationsxml.h"
#include <QMessageBox>

//BackupDialog::BackupDialog(QWidget *parent) :
//  JDialog(parent)
//{
//}
namespace Operations
{
///*/*public*/*/ class BackupDialog extends JDialog {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = 5510681557160040319L;

// static Logger log = LoggerFactory
//         .getLogger(BackupDialog.class.getName());


 /**
  * Create the dialog.
  */
 /*public*/ BackupDialog::BackupDialog(QWidget *parent) :
    JDialog(parent) {
     backup = new DefaultBackup();
     contentPanel = new QWidget();
     log = new Logger("BackupDialog");
     initComponents();
 }

 /*private*/ void BackupDialog::initComponents() {
//     setModalityType(ModalityType.DOCUMENT_MODAL);
//     setModal(true);
     setTitle(tr("Backup OperationsPro Filese"));
     setGeometry(100, 100, 395, 199);
     //getContentPane().setLayout(new BorderLayout());
     QVBoxLayout* thisLayout = (QVBoxLayout*)getContentPane()->layout();
     {
      //contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));

//         GridBagLayout gbl = new GridBagLayout();
//         gbl.columnWidths = new int[]{0, 0};
//         gbl.rowHeights = new int[]{0, 0, 0, 0, 0};
//         gbl.columnWeights = new double[]{1.0, Double.MIN_VALUE};
//         gbl.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0,
//             Double.MIN_VALUE};
      QGridLayout* gb1 = new QGridLayout(contentPanel);
         //contentPanel.setLayout(gbl);
         //getContentPane().add(contentPanel, BorderLayout.CENTER);
      thisLayout->addWidget(contentPanel, 0, Qt::AlignCenter);
         {
             captionLabel = new QLabel(
                     tr("Enter the name of the backup directory:"));
             GridBagConstraints gbc_captionLabel = GridBagConstraints();
             gbc_captionLabel.anchor = GridBagConstraints::WEST;
             gbc_captionLabel.insets = new Insets(0, 0, 5, 0);
             gbc_captionLabel.gridx = 0;
             gbc_captionLabel.gridy = 0;
             gb1->addWidget(captionLabel, gbc_captionLabel.gridy, gbc_captionLabel.gridx, gbc_captionLabel.rowSpan(), gbc_captionLabel.colSpan(), gbc_captionLabel.align());
         }
         {
             setNameTextField = new JTextField();
             setNameTextField->setText(backup->suggestBackupSetName());

//             setNameTextField.getDocument().addDocumentListener(
//                     new DocumentListener() {

//                         // These should probably pass the document to
//                         // enableBackupButton....
//                         @Override
//                         /*/*public*/*/ void removeUpdate(DocumentEvent arg0) {
//                             enableBackupButton();
//                         }

//                         @Override
//                         /*/*public*/*/ void insertUpdate(DocumentEvent arg0) {
//                             enableBackupButton();
//                         }

//                         @Override
//                         /*/*public*/*/ void changedUpdate(DocumentEvent arg0) {
//                             enableBackupButton();
//                         }
//                     });

             GridBagConstraints gbc_setNameTextField = GridBagConstraints();
             gbc_setNameTextField.insets = new Insets(0, 0, 5, 0);
             gbc_setNameTextField.fill = GridBagConstraints::HORIZONTAL;
             gbc_setNameTextField.gridx = 0;
             gbc_setNameTextField.gridy = 1;
             gb1->addWidget(setNameTextField, gbc_setNameTextField.gridy, gbc_setNameTextField.gridx, gbc_setNameTextField.rowSpan(), gbc_setNameTextField.colSpan(), gbc_setNameTextField.align());
             setNameTextField->setColumns(10);
         }
         {
             infoLabel1 = new QLabel(tr("You can accept the default name or enter a new name."));
             GridBagConstraints gbc_infoLabel1 = GridBagConstraints();
             gbc_infoLabel1.insets = new Insets(0, 0, 5, 0);
             gbc_infoLabel1.anchor = GridBagConstraints::NORTHWEST;
             gbc_infoLabel1.gridx = 0;
             gbc_infoLabel1.gridy = 2;
             gb1->addWidget(infoLabel1, gbc_infoLabel1.gridy, gbc_infoLabel1.gridx, gbc_infoLabel1.rowSpan(), gbc_infoLabel1.colSpan(), gbc_infoLabel1.align());
         }
         {
             infoLabel2 = new QLabel(tr("Use a meaningful name when making a manual backup."));
             GridBagConstraints gbc_infoLabel2 = GridBagConstraints();
             gbc_infoLabel2.anchor = GridBagConstraints::WEST;
             gbc_infoLabel2.gridx = 0;
             gbc_infoLabel2.gridy = 3;
             gb1->addWidget(infoLabel2, gbc_infoLabel2.gridy, gbc_infoLabel2.gridx, gbc_infoLabel2.rowSpan(), gbc_infoLabel2.align());
         }
     }
     {
         QWidget* buttonPane = new QWidget();
         FlowLayout* fl_buttonPane = new FlowLayout(/*FlowLayout.CENTER*/);
         buttonPane->setLayout(fl_buttonPane);
         thisLayout->addWidget(buttonPane, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);
         {
             backupButton = new QPushButton(tr("Backup"));
//             backupButton.addActionListener(new ActionListener() {
//                 /*/*public*/*/ void actionPerformed(ActionEvent e) {
//                     do_backupButton_actionPerformed(e);
//                 }
//             });
             connect(backupButton, SIGNAL(clicked()), this, SLOT(do_backupButton_actionPerformed()));
             fl_buttonPane->addWidget(backupButton);
//             getRootPane().setDefaultButton(backupButton);
         }
         {
             QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//             cancelButton.addActionListener(new ActionListener() {
//                 /*/*public*/*/ void actionPerformed(ActionEvent arg0) {
//                     do_cancelButton_actionPerformed(arg0);
//                 }
//             });
//             cancelButton.setActionCommand("Cancel");	// NOI18N
             fl_buttonPane->addWidget(cancelButton);
         }
// Help button isn't used yet
//			{
//				helpButton = new JButton(tr("BackupDialog.helpButton.text"));
//				helpButton.addActionListener(new ActionListener() {
//					/*/*public*/*/ void actionPerformed(ActionEvent e) {
//						do_helpButton_actionPerformed(e);
//					}
//				});
//				helpButton.setEnabled(false);
//				buttonPane.add(helpButton);
//			}
     }
 }

 /*protected*/ void BackupDialog::do_backupButton_actionPerformed(JActionEvent* /*e*/)
 {
  // Do the backup of the files...
  QString setName = "";

//     try {
         log->debug("backup button activated");

         setName = setNameTextField->text();

         // check to see if files are dirty
         if (OperationsXml::areFilesDirty()) {
//             if (JOptionPane
//                     .showConfirmDialog(
//                             this,
//                             tr("OperationsFilesModified"),
//                             tr("SaveOperationFiles"),
//                             JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
          if(QMessageBox::question(this, tr("Save operation files?"), tr("Operations files have been modified, do you want to save them?"),QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
          {
                 OperationsXml::save();
             }
         }

         // check to see if directory already exists
         if (backup->checkIfBackupSetExists(setName)) {
//             int result = JOptionPane.showConfirmDialog(this, MessageFormat
//                     .format(tr("DirectoryAreadyExists"),
//                             new Object[]{setName}),
//                     tr("OverwriteBackupDirectory"),
//                     JOptionPane.OK_CANCEL_OPTION);
          int result = QMessageBox::question(this, tr(""), tr(""), QMessageBox::Ok | QMessageBox::Cancel);
             if (result != QMessageBox::Ok) {
                 return;
             }
         }

         backup->backupFilesToSetName(setName);
         //dispose();
         close();
//     } catch (IOException ex) {
//         ExceptionContext context = new ExceptionContext(
//                 ex,
//                 tr("BackupDialog.BackingUp") + " " + setName,
//                 tr("BackupDialog.Ensure"));
//         new ExceptionDisplayFrame(context);

//     } catch (RuntimeException ex) {
//         // ex.printStackTrace();
//         log.error("Doing backup...", ex);

//         UnexpectedExceptionContext context = new UnexpectedExceptionContext(
//                 ex, tr("BackupDialog.BackingUp") + " " + setName);

//         new ExceptionDisplayFrame(context);
//     } catch (Exception ex) {
//         // ex.printStackTrace();
//         log.error("Doing backup...", ex);

//         UnexpectedExceptionContext context = new UnexpectedExceptionContext(
//                 ex, tr("BackupDialog.BackingUp") + " " + setName);

//         new ExceptionDisplayFrame(context);
//     }
 }

 /*protected*/ void BackupDialog::do_cancelButton_actionPerformed(JActionEvent* arg0) {
     //dispose();
 close();
 }

 /*private*/ void BackupDialog::enableBackupButton() {
     // Enable only if we have something in the text field.
     // Still need to check for a string of blanks......
     QString s = setNameTextField->text();
     backupButton->setEnabled(s.length() > 0);
 }

 /*protected*/ void BackupDialog::do_helpButton_actionPerformed(JActionEvent* /*e*/) {
     // Not implemented yet.
 }

}
