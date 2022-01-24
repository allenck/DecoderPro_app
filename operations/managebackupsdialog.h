#ifndef MANAGEBACKUPSDIALOG_H
#define MANAGEBACKUPSDIALOG_H

#include "jdialog.h"
#include <QList>
#include <defaultlistmodel.h>
#include "appslib_global.h"

class JActionEvent;
class JList;
class QLabel;
class QPushButton;
class QScrollArea;
namespace Operations
{
 class AutoBackup;
 class BackupSet;
 class APPSLIBSHARED_EXPORT ManageBackupsDialog : public JDialog
 {
  Q_OBJECT
 public:
  ManageBackupsDialog(QWidget* parent = 0);
 public slots:

 private:
  /*private*/ /*final*/ QWidget* contentPanel;// = new JPanel();
  /*private*/ QLabel* selectBackupSetsLabel;
  /*private*/ QPushButton* selectAllButton;
  /*private*/ QPushButton* clearAllButton;
  /*private*/ QScrollArea* scrollPane;
  /*private*/ JList* /*List<BackupSet*>*/ setList;

  /*private*/ QPushButton* deleteButton;
  // /*private*/ JButton helpButton;

  /*private*/ DefaultListModel* /*<BackupSet*>*/ model;

  /*private*/ AutoBackup* backup;
  /*private*/ QWidget* horizontalGlue;
  /*private*/ QWidget* horizontalStrut;
  /*private*/ QWidget* horizontalStrut_1;
  /*private*/ QWidget* horizontalStrut_2;
  /*private*/ void initComponents();

 private slots:
  /*private*/ void updateButtonStates();

 protected slots:
  /*protected*/ void do_cancelButton_actionPerformed();
  /*protected*/ void do_clearAllButton_actionPerformed();
  /*protected*/ void do_selectAllButton_actionPerformed();
  /*protected*/ void do_helpButton_actionPerformed();
  /*protected*/ void do_deleteButton_actionPerformed();

 };
}
#endif // MANAGEBACKUPSDIALOG_H
