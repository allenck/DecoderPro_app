#ifndef BACKUPDIALOG_H
#define BACKUPDIALOG_H
#include "jdialog.h"
#include "appslib_global.h"

class JActionEvent;
class QLabel;
class QPushButton;
class JTextField;
namespace Operations
{
 class DefaultBackup;
 class APPSLIBSHARED_EXPORT BackupDialog : public JDialog
 {
  Q_OBJECT
 public:
  explicit BackupDialog(QWidget *parent = 0);

 signals:

 public slots:

 private:
   /*private*/ /*final*/ QWidget* contentPanel;// = new JPanel();
   /*private*/ QLabel* captionLabel;
   /*private*/ JTextField* setNameTextField;
   /*private*/ QLabel* infoLabel1;
   /*private*/ QLabel* infoLabel2;
   /*private*/ QPushButton*  backupButton;
  //	/*private*/ JButton helpButton;

   /*private*/ DefaultBackup* backup;
  /*private*/ void initComponents();
  Logger* log;
  /*private*/ void enableBackupButton();

 protected slots:
  /*protected*/ void do_backupButton_actionPerformed(JActionEvent* e = 0);
  /*protected*/ void do_cancelButton_actionPerformed(JActionEvent* arg0 = 0);
  /*protected*/ void do_helpButton_actionPerformed(JActionEvent* e = 0);

 };
}
#endif // BACKUPDIALOG_H
