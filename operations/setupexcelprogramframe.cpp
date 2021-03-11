#include "setupexcelprogramframe.h"
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include "control.h"
#include "file.h"
#include "jfilechooser.h"
#include "xmlfile.h"
#include "operationsmanager.h"
#include "instancemanager.h"
#include "borderfactory.h"

using namespace Operations;

SetupExcelProgramFrame::SetupExcelProgramFrame(QWidget* parent) : OperationsFrame(parent)
{
 generateCheckBox = new QCheckBox();
 fileNameTextField = new JTextField(30);
 addButton = new QPushButton(tr("Add"));
 testButton = new QPushButton(tr("Test"));
 saveButton = new QPushButton(tr("Save"));
 pDirectoryName = new JPanel();
}
/**
 * Frame for user edit of the file name and setup of an Excel program.
 *
 * @author Dan Boudreau Copyright (C) 2013
 *
 */
///*public*/ class SetupExcelProgramFrame extends OperationsFrame {

    // checkboxes
//    /*protected*/ static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.operations.setup.JmritOperationsSetupBundle");


    //@Override
/*public*/ void SetupExcelProgramFrame::initComponents() {
    QVBoxLayout* thisLayout;
    getContentPane()->setLayout(thisLayout = new QVBoxLayout()); //(getContentPane(), BoxLayout.Y_AXIS));

    // Layout the panel by rows
    // row 1
    JPanel* pOptions = new JPanel();
    QVBoxLayout* pOptionsLayout = new QVBoxLayout(pOptions);
    pOptions->setBorder(BorderFactory::createTitledBorder(tr("Options")));
    pOptionsLayout->addWidget(generateCheckBox);

    // row 2
    pDirectoryName->setBorder(BorderFactory::createTitledBorder(tr("Directory")));
    pDirectoryNameLayout = new QVBoxLayout(pDirectoryName);

    JPanel* pFileName = new JPanel();
    pFileName->setBorder(BorderFactory::createTitledBorder(tr("File Name")));
    QVBoxLayout* pFileNameLayout = new QVBoxLayout(pFileName);
    pFileNameLayout->addWidget(fileNameTextField);

    // row 4 buttons
    QWidget* pButtons = new QWidget();
    GridBagLayout* g;
    pButtons->setLayout(g = new GridBagLayout());
    addItem(pButtons, addButton, 1, 0);
    addItem(pButtons, testButton, 2, 0);
    addItem(pButtons, saveButton, 3, 0);

    thisLayout->addWidget(pOptions);
    thisLayout->addWidget(pDirectoryName);
    thisLayout->addWidget(pFileName);
    thisLayout->addWidget(pButtons);

    // setup buttons
    addButtonAction(addButton);
    addButtonAction(testButton);
    addButtonAction(saveButton);

    addHelpMenu("package.jmri.jmrit.operations.Operations_SetupExcelProgram", true); // NOI18N
    setTitle(tr("Setup Excel Program"));

    initMinimumSize(QSize(Control::panelWidth400, Control::panelHeight300));
}

/**
 * Opens a dialog window in either the csvManifest or csvSwitchLists
 * directory
 * @param directoryName The string name of the directory
 * @return The File selected.
 *
 */
/*protected*/ File* SetupExcelProgramFrame::selectFile(QString directoryName) {
    JFileChooser* fc = XmlFile::userFileChooser(tr("Excel programFiles"), "xls", "xlsm"); // NOI18N
    fc->setCurrentDirectory(((Operations::OperationsManager*)InstanceManager::getDefault("Operations::OperationsManager"))->getFile(directoryName));
    fc->setDialogTitle(tr("Find desired Excel file"));
    // when reusing the chooser, make sure new files are included
//    fc->rescanCurrentDirectory();
    int retVal = fc->showOpenDialog(NULL);
    // handle selection or cancel
    if (retVal == JFileChooser::APPROVE_OPTION) {
        File* file = fc->getSelectedFile();
        // Run the script from it's filename
        return file;
    }
    return NULL;
}
