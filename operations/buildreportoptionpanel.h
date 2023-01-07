#ifndef BUILDREPORTOPTIONPANEL_H
#define BUILDREPORTOPTIONPANEL_H

#include "operationspreferencespanel.h"
namespace Operations
{
 class BuildReportOptionPanel : public OperationsPreferencesPanel
 {
 public:
  BuildReportOptionPanel(QWidget* parent);
  /*public*/ QString getTabbedPreferencesTitle() override;
  /*public*/ QString getPreferencesTooltip() override;
  /*public*/ void savePreferences() override;
  /*public*/ bool isDirty() override;
  /*public*/ QString className() {return "jmri.jmrit.operations.BuildReportOptionPanel";}

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae = 0) override;

 private:
  // major buttons
  QPushButton* saveButton;// = new JButton(Bundle.getMessage("Save"));

  // radio buttons
  QRadioButton* buildReportMin;// = new JRadioButton(Bundle.getMessage("Minimal"));
  QRadioButton* buildReportNor;// = new JRadioButton(Bundle.getMessage("Normal"));
  QRadioButton* buildReportMax;// = new JRadioButton(Bundle.getMessage("Detailed"));
  QRadioButton* buildReportVD;// = new JRadioButton(Bundle.getMessage("VeryDetailed"));

  QRadioButton* buildReportRouterNor;// = new JRadioButton(Bundle.getMessage("Normal"));
  QRadioButton* buildReportRouterMax;// = new JRadioButton(Bundle.getMessage("Detailed"));
  QRadioButton* buildReportRouterVD;// = new JRadioButton(Bundle.getMessage("VeryDetailed"));

  // check boxes
  QCheckBox* buildReportCheckBox;// = new JCheckBox(Bundle.getMessage("BuildReportEdit"));
  QCheckBox* buildReportIndentCheckBox;// = new JCheckBox(Bundle.getMessage("BuildReportIndent"));
  QCheckBox* buildReportAlwaysPreviewCheckBox;// = new JCheckBox(Bundle.getMessage("BuildReportAlwaysPreview"));

  // combo boxes
  JComboBox* fontSizeComboBox;// = new JComboBox<>();
  /*private*/ void setBuildReportRadioButton();
  /*private*/ void setBuildReportRouterRadioButton();

  protected slots:
  /*protected*/ void checkBoxActionPerformed(QWidget* ae)override;
  /*protected*/ void radioButtonActionPerformed(QWidget* ae) override;

 };
}
#endif // BUILDREPORTOPTIONPANEL_H
