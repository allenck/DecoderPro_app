#ifndef RESTOREDIALOG_H
#define RESTOREDIALOG_H

#include "jdialog.h"
#include "appslib_global.h"

class ItemEvent;
class JActionEvent;
class QLabel;
class QComboBox;
class QRadioButton;
namespace Operations
{
 class BackupBase;
 class APPSLIBSHARED_EXPORT RestoreDialog : public JDialog
 {
  Q_OBJECT
 public:
 explicit RestoreDialog(QWidget* parent = 0);

 signals:

 public slots:

 private:
  /*private*/ QWidget*mainPanel;
  /*private*/ QWidget*contentPanel;
  /*private*/ QRadioButton* automaticBackupsRadioButton;
  /*private*/ QRadioButton* defaultBackupsRadioButton;
  /*private*/ QComboBox* comboBox;
  /*private*/ QPushButton* restoreButton;
  ///*private*/ JButton helpButton;

  /*private*/ BackupBase* backup;
  /*private*/ QString setName;
  /*private*/ QLabel* newLabelLabel;
  /*private*/ void initComponents();
  /*private*/ void loadComboBox();
  Logger* log;

protected slots:
  /*protected*/ void do_automaticBackupsRadioButton_actionPerformed(JActionEvent* e = 0);
  /*protected*/ void do_defaultBackupsRadioButton_actionPerformed(JActionEvent* e = 0);
  /*protected*/ void do_cancelButton_actionPerformed(JActionEvent* arg0 =0);
  /*protected*/ void do_comboBox_itemStateChanged(ItemEvent* arg0 = 0);
  /*protected*/ void do_helpButton_actionPerformed(JActionEvent* arg0 =0);
  /*protected*/ void do_restoreButton_actionPerformed(JActionEvent* e = 0);

 };
}
#endif // RESTOREDIALOG_H
