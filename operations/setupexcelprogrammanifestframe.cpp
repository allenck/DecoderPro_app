#include "setupexcelprogrammanifestframe.h"
#include "setup.h"
#include "operationsmanager.h"
#include "traincustommanifest.h"
#include <QLabel>
#include "file.h"
#include "operationsxml.h"
#include "joptionpane.h"
#include "loggerfactory.h"

using namespace Operations;
SetupExcelProgramManifestFrame::SetupExcelProgramManifestFrame(QWidget* parent) : SetupExcelProgramFrame(parent)
{

}
/**
 * Frame for user edit of the file name of an Excel program used to generate
 * custom manifests.
 *
 * @author Dan Boudreau Copyright (C) 2014
 *
 */
///*public*/ class SetupExcelProgramManifestFrame extends SetupExcelProgramFrame {

//@Override
/*public*/ void SetupExcelProgramManifestFrame::initComponents() {
    SetupExcelProgramFrame::initComponents();

    generateCheckBox->setText(tr("Generate Csv Manifest"));
    generateCheckBox->setChecked(Setup::isGenerateCsvManifestEnabled());
    fileNameTextField->setText(TrainCustomManifest::instance()->getFileName());
    pDirectoryNameLayout->addWidget(new QLabel(OperationsManager::getInstance()->getFile(TrainCustomManifest::instance()->getDirectoryName())->getPath()));
}

// Save and Test
//@Override
/*public*/ void SetupExcelProgramManifestFrame::buttonActionPerformed(QWidget* ae)
{
 if (ae == addButton) {
     File* f = selectFile(TrainCustomManifest::instance()->getDirectoryName());
     if (f != NULL) {
         log->debug(tr("User selected file: %1").arg(f->getName()));
         fileNameTextField->setText(f->getName());
     }
 }

 TrainCustomManifest::instance()->setFileName(fileNameTextField->text());

 if (ae == testButton)
 {
  if (TrainCustomManifest::instance()->excelFileExists())
  {
   JOptionPane::showMessageDialog(this, tr("Directory name: %1, File name: %2").arg(
           TrainCustomManifest::instance()->getDirectoryName()).arg( TrainCustomManifest::instance()->getFileName()),
           tr("Manifest Creator Excel file found!"), JOptionPane::INFORMATION_MESSAGE);
  }
  else
  {
   JOptionPane::showMessageDialog(this,
           tr("You need to load the Excel File that you want to run. Directory name: %1, File name: %2").arg(TrainCustomManifest::instance()->getDirectoryName()).arg( TrainCustomManifest::instance()->getFileName()), tr("ManifestCreatorNotFound"), JOptionPane::ERROR_MESSAGE);
  }
 }
 if (ae == saveButton)
 {
  log->debug("Save button activated");
  Setup::setGenerateCsvManifestEnabled(generateCheckBox->isChecked());
  OperationsXml::save();
  if (Setup::isCloseWindowOnSaveEnabled()) {
      dispose();
  }
 }
}

/*public*/ QString SetupExcelProgramManifestFrame::getClassName()
{
 return "jmri.jmrit.operations.trains.excel.SetupExcelProgramManifestFrame";
}

/*private*/ /*final*/ /*static*/ Logger* SetupExcelProgramManifestFrame::log = LoggerFactory::getLogger("SetupExcelProgramManifestFrame");
