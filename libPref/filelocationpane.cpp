#include "filelocationpane.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "jtextfield.h"
#include "fileutil.h"
#include <QFileDialog>
#include "jframe.h"
#include "jfilechooser.h"
#include "file.h"
#include <QComboBox>
#include "fileutilsupport.h"

//FileLocationPane::FileLocationPane(QWidget *parent) :
//    PreferencesPanel(parent)
//{
//}
/**
 * Provide GUI to configure the Default File Locations
 * <P>
 * Provides GUI configuration for the default file locations by displaying
 * textfields for the user to directly enter in their own path or a Set button
 * is provided so that the user can select the path.
 *
 * @author Kevin Dickerson Copyright (C) 2010
 * @version	$Revision: 28118 $
 */
// /*public*/ class FileLocationPane extends JPanel implements PreferencesPanel {

/**
 *
 */
//private static final long serialVersionUID = -2492371396905648159L;
//protected static final ResourceBundle rb = ResourceBundle.getBundle("apps.AppsConfigBundle");

/*public*/ FileLocationPane::FileLocationPane(QWidget *parent) : QWidget(parent)
{
 common();
}
FileLocationPane::FileLocationPane(const FileLocationPane &) : QWidget()
{
 common();
}

/*private*/ void FileLocationPane::common()
{
 setObjectName("FileLocationPane");
 restartRequired = false;
 scriptLocation = new JTextField();
 scriptLocation->setToolTip(tr("Location of user scripts. If not specified, user files location will be used."));
 userLocation = new JTextField();
 userLocation->setToolTip(tr("Specify directory path where user files are stored. If not present, the Profile path will be used!"));
 _programLocation = new JTextField();
 _programLocation->setToolTip(tr("Select location of Java program resources to be used by this program. Requires either a Java version of JMRO or the JMRI source."));
 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

 thisLayout->addWidget(prefLocation());
 thisLayout->addWidget(scriptsLocation());
 thisLayout->addWidget(programLocation());

    /*p = new JPanel();
     JLabel throttle = new JLabel("Default Throttle Location");
     p.add(throttle);
     p.add(throttleLocation);
     throttleLocation.setColumns(20);
     throttleLocation.setText(jmri.jmrit.throttle.ThrottleFrame.getDefaultThrottleFolder());
     add(p);*/
}

/*private*/ QWidget* FileLocationPane::scriptsLocation() {
    QPushButton* bScript = new QPushButton(tr("Set..."));
    fcScript = new JFileChooser(FileUtil::getScriptsPath());

    fcScript->setDialogTitle(tr("Select Directory"));
    fcScript->setFileSelectionMode(JFileChooser::DIRECTORIES_ONLY);
//    fcScript->setAcceptAllFileFilterUsed(false);
    OpenAction* act = new OpenAction(fcScript, scriptLocation, this);
    //bScript.addActionListener(new OpenAction(fcScript, scriptLocation));
    connect(bScript, SIGNAL(clicked(bool)), act, SLOT(actionPerformed()));
//    QVBoxLayout* thisLayout;
//    setLayout(thisLayout = new QVBoxLayout()); //this, BoxLayout.Y_AXIS));
    QWidget* p = new QWidget();
    QHBoxLayout* pLayout = new QHBoxLayout(p);
    QLabel* scripts = new QLabel(tr("Script Dir"));
    pLayout->addWidget(scripts);
    pLayout->addWidget(scriptLocation);
    pLayout->addWidget(bScript);
    scriptLocation->setColumns(30);
    scriptLocation->setText(FileUtil::getScriptsPath());
    return p;
}

/*private*/ QWidget* FileLocationPane::programLocation() {
    QComboBox* cbProgram = new QComboBox();
    cbProgram->addItems(*FileUtil::findProgramPath());
    cbProgram->findText(FileUtil::getProgramPath());
    _programLocation->setText(cbProgram->currentText());
    connect(cbProgram, SIGNAL(currentIndexChanged(QString)), this, SLOT(programLocationChange(QString)));
//    QVBoxLayout* thisLayout;
//    setLayout(thisLayout = new QVBoxLayout()); //this, BoxLayout.Y_AXIS));
    QWidget* p = new QWidget();
    QHBoxLayout* pLayout = new QHBoxLayout(p);
    QLabel* label = new QLabel(tr("Program Dir"));
    pLayout->addWidget(label);
    pLayout->addWidget(_programLocation);
    pLayout->addWidget(cbProgram);
    scriptLocation->setColumns(30);
    return p;
}

/*private*/ void FileLocationPane::programLocationChange(QString loc)
{
 _programLocation->setText(loc);
}

/*private*/ QWidget* FileLocationPane::prefLocation() {
    QWidget* p = new QWidget();
    QHBoxLayout* pLayout = new QHBoxLayout;
    p->setLayout(pLayout);
    QLabel* users = new QLabel(tr("User Files Location"));
    pLayout->addWidget(users);
    pLayout->addWidget(userLocation);
    userLocation->setColumns(30);
    userLocation->setText(FileUtil::getUserFilesPath());

    QPushButton* bUser = new QPushButton(tr("Set..."));
    /*final*/ QFileDialog* fcUser;
    fcUser = new QFileDialog(NULL,tr("Select Directory"), FileUtil::getUserFilesPath());

//    fcUser.setDialogTitle(tr("Select Directory"));
//    fcUser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
//    fcUser.setAcceptAllFileFilterUsed(false);
    fcUser->setFileMode(QFileDialog::DirectoryOnly);
//    bUser.addActionListener(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -4085952502159628091L;

//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            // get the file
//            fcUser.showOpenDialog(null);
//            if (fcUser.getSelectedFile() == null) {
//                return; // cancelled
//            }
//            userLocation.setText(fcUser.getSelectedFile() + File.separator);
//            validate();
//            if (getTopLevelAncestor() != null) {
//                ((JFrame) getTopLevelAncestor()).pack();
//            }
//        }
//    });
    connect(fcUser, SIGNAL(fileSelected(QString)), this, SLOT(On_fileSelected(QString)));

    pLayout->addWidget(bUser);
    return p;
}
void FileLocationPane::On_fileSelected(QString file)
{
 userLocation->setText(file + QDir::separator());
 if (window() != NULL)
 {
   ((JFrame*) window())->pack();
 }
}

//@Override
/*public*/ QString FileLocationPane::getPreferencesItem() {
    return "FILELOCATIONS"; // NOI18N
}

//@Override
/*public*/ QString FileLocationPane::getPreferencesItemText() {
    return tr("File Locations"); // NOI18N
}

//@Override
/*public*/ QString FileLocationPane::getTabbedPreferencesTitle() {
    return tr("File Locations"); // NOI18N
}

//@Override
/*public*/ QString FileLocationPane::getLabelKey() {
    return tr("The default locations for saving your files."); // NOI18N
}

//@Override
/*public*/ QWidget* FileLocationPane::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool FileLocationPane::isPersistant() {
    return true;
}

//@Override
/*public*/ QString FileLocationPane::getPreferencesTooltip() {
    return "";
}

//@Override
/*public*/ void FileLocationPane::savePreferences()
{
 if (FileUtil::getUserFilesPath()!=(this->userLocation->text()))
 {
  FileUtil::setUserFilesPath(this->userLocation->text());
  this->restartRequired = true;
 }
 if (FileUtil::getScriptsPath()!=(this->scriptLocation->text()))
 {
  FileUtil::setScriptsPath(this->scriptLocation->text());
  this->restartRequired = true;
 }
 if (FileUtil::getProgramPath()!=(this->_programLocation->text()))
 {
  FileUtil::setProgramPath(this->_programLocation->text());
  this->restartRequired = true;
 }
}

//@Override
/*public*/ bool FileLocationPane::isDirty()
{
 return (FileUtil::getUserFilesPath()!=(this->userLocation->text())
            || FileUtil::getScriptsPath()!=(this->scriptLocation->text()));
}

//@Override
/*public*/ bool FileLocationPane::isRestartRequired() {
    return this->restartRequired;
}

///*private*/ class OpenAction extends AbstractAction {
//    JFileChooser chooser;
//    JTextField field;
    OpenAction::OpenAction(JFileChooser* chooser, JTextField* field, FileLocationPane* pane) {
        this->chooser = chooser;
        this->field = field;
     this->pane = pane;
    }
//    @Override
//    @SuppressFBWarnings(value="BC_UNCONFIRMED_CAST_OF_RETURN_VALUE", justification="protected by if instanceof")
/*public*/ void OpenAction::actionPerformed(ActionEvent* /*e*/) {
    // get the file
    chooser->showOpenDialog(NULL);
    if (chooser->getSelectedFile() == NULL) {
        return; // cancelled
    }
    field->setText(chooser->getSelectedFile()->getPath() + File::separator);
//        validate();
    if (pane->window() != NULL && qobject_cast<JFrame*>(pane->window()) != NULL) {
        ((JFrame*)pane->window())->adjustSize();

    }
}

    /*public*/ QString FileLocationPane::className() {return "FileLocationPane";}
//}
