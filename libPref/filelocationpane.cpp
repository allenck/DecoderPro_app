#include "filelocationpane.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "jtextfield.h"
#include "fileutil.h"
#include <QFileDialog>
#include "jframe.h"

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

/*public*/ FileLocationPane::FileLocationPane(QWidget *parent) : PreferencesPanel(parent)
{
 common();
}
FileLocationPane::FileLocationPane(const FileLocationPane &) : PreferencesPanel()
{
 common();
}

/*private*/ void FileLocationPane::common()
{
 setObjectName("FileLocationPane");
 restartRequired = false;
 scriptLocation = new JTextField();
 userLocation = new JTextField();

 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

 thisLayout->addWidget(PrefLocation());
// thisLayout->addWidget(ScriptsLocation());

    /*p = new JPanel();
     JLabel throttle = new JLabel("Default Throttle Location");
     p.add(throttle);
     p.add(throttleLocation);
     throttleLocation.setColumns(20);
     throttleLocation.setText(jmri.jmrit.throttle.ThrottleFrame.getDefaultThrottleFolder());
     add(p);*/
}
#if 0
private JPanel ScriptsLocation() {
    JButton bScript = new JButton(tr("ButtonSetDots"));
    final JFileChooser fcScript;
    fcScript = new JFileChooser(FileUtil.getScriptsPath());

    fcScript.setDialogTitle(tr("MessageSelectDirectory"));
    fcScript.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
    fcScript.setAcceptAllFileFilterUsed(false);
    bScript.addActionListener(new AbstractAction() {
        /**
         *
         */
        private static final long serialVersionUID = 6381324878582255448L;

        //@Override
        /*public*/ void actionPerformed(ActionEvent e) {
            // get the file
            fcScript.showOpenDialog(null);
            if (fcScript.getSelectedFile() == null) {
                return; // cancelled
            }
            scriptLocation.setText(fcScript.getSelectedFile() + File.separator);
            validate();
            if (getTopLevelAncestor() != null) {
                ((JFrame) getTopLevelAncestor()).pack();
            }
        }
    });
    setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
    JPanel p = new JPanel();
    JLabel scripts = new JLabel(tr("ScriptDir"));
    p.add(scripts);
    p.add(scriptLocation);
    p.add(bScript);
    scriptLocation.setColumns(30);
    scriptLocation.setText(FileUtil.getScriptsPath());
    return p;
}
#endif
/*private*/ QWidget* FileLocationPane::PrefLocation() {
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
 if (getTopLevelAncestor() != NULL)
 {
   ((JFrame*) getTopLevelAncestor())->pack();
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

