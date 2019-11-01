#ifndef BUILDREPORTOPTIONPANEL_H
#define BUILDREPORTOPTIONPANEL_H

#include "operationspreferencespanel.h"
namespace Operations
{
 class BuildReportOptionPanel : public OperationsPreferencesPanel
 {
 public:
  BuildReportOptionPanel(QWidget* parent);
 public slots:

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
  QComboBox* fontSizeComboBox;// = new JComboBox<>();
  /*private*/ void setBuildReportRadioButton();
  /*private*/ void setBuildReportRouterRadioButton();
 };
}
#endif // BUILDREPORTOPTIONPANEL_H
