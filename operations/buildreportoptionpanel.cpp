#include "buildreportoptionpanel.h"
#include "operationssetupxml.h"
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QBoxLayout>
#include "gridbaglayout.h"
#include <QGroupBox>
#include <QCheckBox>
#include "jcombobox.h"
#include "setup.h"
#include "control.h"
#include "jpanel.h"
#include "borderfactory.h"
#include "joptionpane.h"
#include "operationssetupxml.h"
#include "instancemanager.h"

namespace Operations
{
 /**
  * Frame for user edit of the build report options
  *
  * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2012, 2013
  * @version $Revision: 21643 $
  */
 ///*public*/ class BuildReportOptionPanel extends OperationsPreferencesPanel {

    /*private*/ static /*final*/ long serialVersionUID = 755494379884398257L;
//    /*private*/ static final Logger log = LoggerFactory.getLogger(OperationsSetupPanel.class);



 /*public*/ BuildReportOptionPanel::BuildReportOptionPanel(QWidget* parent) : OperationsPreferencesPanel(parent){
 // major buttons
  saveButton = new QPushButton(tr("Save"));

 // radio buttons
 buildReportMin = new QRadioButton(tr("Minimal"));
 buildReportNor = new QRadioButton(tr("Normal"));
 buildReportMax = new QRadioButton(tr("Detailed"));
 buildReportVD = new QRadioButton(tr("VeryDetailed"));

 buildReportRouterNor = new QRadioButton(tr("Normal"));
 buildReportRouterMax = new QRadioButton(tr("Detailed"));
 buildReportRouterVD = new QRadioButton(tr("Very Detailed"));

// check boxes
 buildReportCheckBox = new QCheckBox(tr("Use Text Editor to Preview Build Reports"));
 buildReportIndentCheckBox = new QCheckBox(tr("Indent Build Report by Detail Level"));
 buildReportAlwaysPreviewCheckBox = new QCheckBox(tr("Always use Preview for Build Reports"));

 // combo boxes
 fontSizeComboBox = new JComboBox();
     // the following code sets the frame's initial state
     // add tool tips
     saveButton->setToolTip(tr("Writes this window's settings to file"));
     buildReportCheckBox->setToolTip(tr("When selected, create build report text files in JMRI->operations->buildstatus"));

     setLayout(new QVBoxLayout);//(this, BoxLayout.Y_AXIS));

     // build report
     JPanel* pReport = new JPanel();
     pReport->setLayout(new GridBagLayout());
     pReport->setBorder(BorderFactory::createTitledBorder(tr("Build Report Options")));
     // build report options
     addItemWidth(pReport, buildReportCheckBox, 3, 1, 1);
     addItemWidth(pReport, buildReportIndentCheckBox, 3, 1, 2);
     addItemWidth(pReport, buildReportAlwaysPreviewCheckBox, 3, 1, 3);

     JPanel* pFontSize = new JPanel(new FlowLayout());
     pFontSize->setBorder(BorderFactory::createTitledBorder(tr("Font Size")));
     pFontSize->layout()->addWidget(fontSizeComboBox);

     JPanel* pLevel = new JPanel();
     pLevel->setLayout(new GridBagLayout());
     pLevel->setBorder(BorderFactory::createTitledBorder(tr("Detail Level")));

     // build report level radio buttons
     addItemLeft(pLevel, buildReportMin, 1, 0);
     addItemLeft(pLevel, buildReportNor, 2, 0);
     addItemLeft(pLevel, buildReportMax, 3, 0);
     addItemLeft(pLevel, buildReportVD, 4, 0);

     JPanel* pRouterLevel = new JPanel();
     pRouterLevel->setLayout(new GridBagLayout());
     pRouterLevel->setBorder(BorderFactory::createTitledBorder(tr("Router Detail Level")));

     // build report level radio buttons
     addItemLeft(pRouterLevel, buildReportRouterNor, 2, 0);
     addItemLeft(pRouterLevel, buildReportRouterMax, 3, 0);
     addItemLeft(pRouterLevel, buildReportRouterVD, 4, 0);

     // controls
     JPanel* pControl = new JPanel(new GridBagLayout);
     pControl->setBorder(BorderFactory::createTitledBorder(""));
     pControl->setLayout(new GridBagLayout());
     addItem(pControl, saveButton, 0, 0);

     layout()->addWidget(pReport);
     layout()->addWidget(pLevel);
     layout()->addWidget(pRouterLevel);
     layout()->addWidget(pFontSize);
     layout()->addWidget(pControl);

     buildReportCheckBox->setChecked(Setup::isBuildReportEditorEnabled());
     buildReportIndentCheckBox->setChecked(Setup::isBuildReportIndentEnabled());
     buildReportIndentCheckBox->setEnabled(buildReportCheckBox->isChecked());
     buildReportAlwaysPreviewCheckBox->setChecked(Setup::isBuildReportAlwaysPreviewEnabled());

     QButtonGroup* buildReportGroup = new QButtonGroup();
     buildReportGroup->addButton(buildReportMin);
     buildReportGroup->addButton(buildReportNor);
     buildReportGroup->addButton(buildReportMax);
     buildReportGroup->addButton(buildReportVD);

     QButtonGroup* buildReportRouterGroup = new QButtonGroup();
     buildReportRouterGroup->addButton(buildReportRouterNor);
     buildReportRouterGroup->addButton(buildReportRouterMax);
     buildReportRouterGroup->addButton(buildReportRouterVD);

     setBuildReportRadioButton();
     setBuildReportRouterRadioButton();

     // load font sizes 5 through 14
     for (int i = 5; i < 15; i++) {
         fontSizeComboBox->addItem(QString::number(i),i);
     }
     fontSizeComboBox->setCurrentIndex(fontSizeComboBox->findData(QVariant(Setup::getBuildReportFontSize())));

     addButtonAction(saveButton);
     addCheckBoxAction(buildReportCheckBox);

     addRadioButtonAction(buildReportMin);
     addRadioButtonAction(buildReportNor);
     addRadioButtonAction(buildReportMax);
     addRadioButtonAction(buildReportVD);

     initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500));
 }

 // Save button
 //@Override
 /*public*/ void BuildReportOptionPanel::buttonActionPerformed(QWidget* ae) {
     if (ae == saveButton) {
         this->savePreferences();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }

 //@Override
 /*protected*/ void BuildReportOptionPanel::checkBoxActionPerformed(QWidget* /*ae*/) {
     buildReportIndentCheckBox->setEnabled(buildReportCheckBox->isChecked());
 }

 //@Override
 /*protected*/ void BuildReportOptionPanel::radioButtonActionPerformed(QWidget* /*ae*/) {
     setBuildReportRouterRadioButton();	// enable detailed and very detailed if needed
 }

 /*private*/ void BuildReportOptionPanel::setBuildReportRadioButton() {
     buildReportMin->setChecked(Setup::getBuildReportLevel()==(Setup::BUILD_REPORT_MINIMAL));
     buildReportNor->setChecked(Setup::getBuildReportLevel()==(Setup::BUILD_REPORT_NORMAL));
     buildReportMax->setChecked(Setup::getBuildReportLevel()==(Setup::BUILD_REPORT_DETAILED));
     buildReportVD->setChecked(Setup::getBuildReportLevel()==(Setup::BUILD_REPORT_VERY_DETAILED));
 }

 /*private*/ void BuildReportOptionPanel::setBuildReportRouterRadioButton() {
     // Enabled for the router only if the build report is very detailed
     buildReportRouterNor->setEnabled(buildReportVD->isChecked());
     buildReportRouterMax->setEnabled(buildReportVD->isChecked());
     buildReportRouterVD->setEnabled(buildReportVD->isChecked());

     buildReportRouterMax->setChecked(Setup::getRouterBuildReportLevel()
             ==(Setup::BUILD_REPORT_DETAILED));
     buildReportRouterVD->setChecked(Setup::getRouterBuildReportLevel()==(
             Setup::BUILD_REPORT_VERY_DETAILED));
     buildReportRouterNor->setChecked(Setup::getRouterBuildReportLevel()==(Setup::BUILD_REPORT_NORMAL)
             || !buildReportVD->isChecked());
 }

 //@Override
 /*public*/ QString BuildReportOptionPanel::getTabbedPreferencesTitle() {
     return tr("Build Report Options");
 }

 //@Override
 /*public*/ QString BuildReportOptionPanel::getPreferencesTooltip() {
     return nullptr;
 }

 //@Override
 /*public*/ void BuildReportOptionPanel::savePreferences() {
     // font size
     Setup::setBuildReportFontSize( fontSizeComboBox->getSelectedItem().toInt());

     // build report level
     if (buildReportMin->isChecked()) {
         Setup::setBuildReportLevel(Setup::BUILD_REPORT_MINIMAL);
     } else if (buildReportNor->isChecked()) {
         Setup::setBuildReportLevel(Setup::BUILD_REPORT_NORMAL);
     } else if (buildReportMax->isChecked()) {
         Setup::setBuildReportLevel(Setup::BUILD_REPORT_DETAILED);
     } else if (buildReportVD->isChecked()) {
         Setup::setBuildReportLevel(Setup::BUILD_REPORT_VERY_DETAILED);
     }

     // router build report level
     QString oldReportLevel = Setup::getRouterBuildReportLevel();
     if (buildReportRouterNor->isChecked()) {
         Setup::setRouterBuildReportLevel(Setup::BUILD_REPORT_NORMAL);
     } else if (buildReportRouterMax->isChecked()) {
         Setup::setRouterBuildReportLevel(Setup::BUILD_REPORT_DETAILED);
     } else if (buildReportRouterVD->isChecked()) {
         Setup::setRouterBuildReportLevel(Setup::BUILD_REPORT_VERY_DETAILED);
     }

     if (oldReportLevel!=(Setup::getRouterBuildReportLevel())) {
      JOptionPane::showMessageDialog(this,tr("Build reports are not longer valid!"), tr("Build reports are not longer valid!"), JOptionPane::INFORMATION_MESSAGE);
     }

     Setup::setBuildReportEditorEnabled(buildReportCheckBox->isChecked());
     Setup::setBuildReportIndentEnabled(buildReportIndentCheckBox->isChecked());
     Setup::setBuildReportAlwaysPreviewEnabled(buildReportAlwaysPreviewCheckBox->isChecked());

     ((OperationsSetupXml*)InstanceManager::getDefault("OperationsSetupXml"))->writeOperationsFile();
 }

 //@Override
 /*public*/ bool BuildReportOptionPanel::isDirty() {
     QString reportLevel = Setup::getBuildReportLevel();
     if (buildReportMin->isChecked()) {
         reportLevel = Setup::BUILD_REPORT_MINIMAL;
     } else if (buildReportNor->isChecked()) {
         reportLevel = Setup::BUILD_REPORT_NORMAL;
     } else if (buildReportMax->isChecked()) {
         reportLevel = Setup::BUILD_REPORT_DETAILED;
     } else if (buildReportVD->isChecked()) {
         reportLevel = Setup::BUILD_REPORT_VERY_DETAILED;
     }

     QString routerReportLevel = Setup::getRouterBuildReportLevel();
     if (buildReportRouterNor->isChecked()) {
         routerReportLevel = Setup::BUILD_REPORT_NORMAL;
     } else if (buildReportRouterMax->isChecked()) {
         routerReportLevel = Setup::BUILD_REPORT_DETAILED;
     } else if (buildReportRouterVD->isChecked()) {
         routerReportLevel = Setup::BUILD_REPORT_VERY_DETAILED;
     }

     return (Setup::getBuildReportFontSize() != fontSizeComboBox->getSelectedItem().toInt()
             || !reportLevel.toInt()==(Setup::getBuildReportLevel())
             || !routerReportLevel.toInt()==(Setup::getRouterBuildReportLevel())
             || Setup::isBuildReportEditorEnabled() != buildReportCheckBox->isChecked()
             || Setup::isBuildReportIndentEnabled() != buildReportIndentCheckBox->isChecked()
             || Setup::isBuildReportAlwaysPreviewEnabled() != buildReportAlwaysPreviewCheckBox->isChecked());
 }

}
