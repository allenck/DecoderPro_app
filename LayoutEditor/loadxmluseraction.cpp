#include "loadxmluseraction.h"
#include <QFileDialog>
#include "jfilechooser.h"
#include <QMessageBox>
#include "logger.h"
#include <QWidget>

//LoadXmlUserAction::LoadXmlUserAction(QObject *parent) :
//  LoadXmlConfigAction(parent)
//{
//}
/**
 * Load configuration information from an XML file.
 * <P>
 * The file context for this is the "user" file chooser.
 * <P>
 * This will load whatever information types are present in the file. See
 * {@link jmri.ConfigureManager} for information on the various types of
 * information stored in configuration files.
 *
 * @author Bob Jacobsen Copyright (C) 2002
 * @version $Revision: 29359 $
 * @see jmri.jmrit.XmlFile
 */
// /*public*/ class LoadXmlUserAction extends LoadXmlConfigAction {

/**
 *
 */
//private static final long serialVersionUID = 5470543428367047464L;
//static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.DisplayBundle");
/*static*/ File*  LoadXmlUserAction::currentFile = nullptr;

/*public*/ LoadXmlUserAction::LoadXmlUserAction(QObject *parent) :
  LoadXmlConfigAction(tr("Open Panels..."), parent)
{
 //this(rb.getString("MenuItemLoad"));
 common();
}

/*public*/ LoadXmlUserAction::LoadXmlUserAction(QString s,  QObject *parent) :
 LoadXmlConfigAction(s, parent){
 //super(s);
 common();
}
void LoadXmlUserAction::common()
{
 log = new Logger("LoadXmlUserAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void LoadXmlUserAction::actionPerformed(JActionEvent * /*e*/)
{
 JFileChooser* userFileChooser = getUserFileChooser();
 userFileChooser->setDialogType(JFileChooser::OPEN_DIALOG);
 userFileChooser->setApproveButtonText(tr("Open Panels..."));
 userFileChooser->setDialogTitle(tr("Open Panels..."));
 userFileChooser->setFileFilter("Panel XML files (*.xml);;All files (*.*)");

 bool results = loadFile(userFileChooser);
 if (results)
 {
  log->debug("load was successful");
  currentFile = userFileChooser->getSelectedFile();
 }
 else
 {
  log->debug("load failed");

//     JOptionPane.showMessageDialog(null,
//             rb.getString("PanelHasErrors") + "\n"
//             + rb.getString("CheckPreferences") + "\n"
//             + rb.getString("ConsoleWindowHasInfo"),
//             rb.getString("PanelLoadError"), JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(nullptr, tr("Error Opening Panel!"), tr("Panel experienced errors during load.")+ "\n" + tr("Check your system Preferences.") + "\n" + tr("The console window contains error details."));
     currentFile = nullptr;
 }
}

/*public*/ /*static*/ File* LoadXmlUserAction::getCurrentFile() {
    return currentFile;
}
