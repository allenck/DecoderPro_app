#ifndef ISSUEREPORTER_H
#define ISSUEREPORTER_H

#include <jframe.h>
#include "jcombobox.h"
#include "jtextarea.h"
#include "jtogglebutton.h"
#include "jtextfield.h"
#include "jlabel.h"
#include "jcheckbox.h"
#include "actionevent.h"

class IssueReport;
class DocumentEvent;
class IssueReporter : public JFrame
{
 public:
  IssueReporter(QWidget* parent =0);
  /*public*/ void insertUpdate(DocumentEvent* e);
  /*public*/ void removeUpdate(DocumentEvent* e);

 public slots:
  /*public*/ void changedUpdate(DocumentEvent* e = 0);
 private slots:

  /*private*/ void typeCBActionListener(JActionEvent* e);
  /*private*/ void submitBtnActionListener(JActionEvent* e);
  /*private*/ void submitReport(IssueReport* report);

 private:
  static Logger* log;
  /*private*/ static /*final*/ const int BUG;// = 0; // index in type combo box
  /*private*/ static /*final*/ const int RFE;// = 1; // index in type combo box
  /*private*/ JComboBox/*<String>*/* typeCB;
  /*private*/ JComboBox/*<GitHubRepository>*/* repoCB;
  /*private*/ JTextArea* bodyTA;
  /*private*/ JToggleButton* submitBtn;
  /*private*/ JTextField* titleText;
  /*private*/ JLabel* descriptionLabel;
  /*private*/ JLabel* instructionsLabel;
  /*private*/ JPanel* typeOptionsPanel;
  /*private*/ JPanel* bugReportPanel;
  /*private*/ JCheckBox* profileCB;
  /*private*/ JCheckBox* sysInfoCB;
  /*private*/ JCheckBox* logsCB;
  /*private*/ void initComponents();
};

#endif // ISSUEREPORTER_H
