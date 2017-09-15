#include "loadvsdfileaction.h"
#include "jfilechooser.h"
#include "vsdecodermanager.h"
#include "vsdfile.h"
#include <QMessageBox>
#include "vsdecoderpreferences.h"
#include "file.h"

//LoadVsDFileAction::LoadVsDFileAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * Load VSDecoder Profiles from XML
 *
 * Adapted from LoadXmlThrottleProfileAction by Glen Oberhauser (2004)
 *
 * @author Mark Underwood 2011
 * @version $Revision: 28746 $
 */
//@SuppressWarnings("serial")
///*public*/ class LoadVSDFileAction extends AbstractAction {

    //static final ResourceBundle rb = VSDecoderBundle.bundle();

/**
 * Constructor
 *
 * @param s Name for the action.
 */
/*public*/ LoadVSDFileAction::LoadVSDFileAction(QString s, QObject *parent) :
AbstractAction(s, parent) {
   // super(s);
common();
}

/*public*/ LoadVSDFileAction::LoadVSDFileAction(QObject *parent)
 :     AbstractAction(tr("Load VSD File"), parent)
{
    //this(tr("Load VSD File")); // Shouldn't this be in the resource bundle?
common();
}

void LoadVSDFileAction::common()
{
 log = new Logger("LoadVsDFileAction");
 fileChooser = NULL;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*static*/ /*private*/ QString LoadVSDFileAction::last_path = "";

/**
 * The action is performed. Let the user choose the file to load from. Read
 * XML for each VSDecoder Profile.
 *
 * @param e The event causing the action.
 */
/*public*/ void LoadVSDFileAction::actionPerformed(ActionEvent* /*e*/)
{
 if (fileChooser == NULL)
 {
  // Need to somehow give the user a history...
  // Must investigate JFileChooser...
  QString start_dir = VSDecoderManager::instance()->getVSDecoderPreferences()->getDefaultVSDFilePath();
  if (last_path != NULL) {
      start_dir = last_path;
  }

  log->debug("Using path: " + start_dir);

  fileChooser = new JFileChooser(start_dir);
  //FileChooserFilter filt = new jmri.util.FileChooserFilter(rb.getString("LoadVSDFileChooserFilterLabel"));
  fileChooser->setDialogTitle("VSD Files");
  //filt.addExtension("vsd");
  //filt.addExtension("zip");
  fileChooser->setFileFilter("VS Decoder files (*.vsd, *.zip)");
  fileChooser->setDialogType(JFileChooser::OPEN_DIALOG);
  fileChooser->setCurrentDirectory(new File(start_dir));
 }
 int retVal = fileChooser->showOpenDialog(NULL);
 if (retVal != JFileChooser::APPROVE_OPTION)
 {
  return;
  // give up if no file selected
 }

 loadVSDFile(fileChooser->getSelectedFile());

 // Store the last used directory
 //try {
     last_path = fileChooser->getCurrentDirectory()->getCanonicalPath();
//    } catch (java.io.IOException err) {
//        log->debug("Error getting current directory: " + err);
//        last_path = VSDecoderManager.instance().getVSDecoderPreferences().getDefaultVSDFilePath();
//    }
}

/*public*/ /*static*/ bool LoadVSDFileAction::loadVSDFile(File* f)
{
 VSDFile* vsdfile;
 // Create a VSD (zip) file.
 //try {
  vsdfile = new VSDFile(f);
  Logger* log = new Logger("LoadVSDFileAction");
  log->debug("VSD File name = " + vsdfile->getName());
  if (vsdfile->isInitialized())
  {
   VSDecoderManager::instance()->loadProfiles(vsdfile);
  }
  // Cleanup and close files.
//TODO:       vsdfile->close();

  if (!vsdfile->isInitialized())
  {
//            JOptionPane.showMessageDialog(NULL, vsdfile.getStatusMessage(),
//                    rb.getString("VSDFileError"), JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(NULL, tr("Error Loading VSD File"), vsdfile->getStatusMessage());
  }

  return (vsdfile->isInitialized());

//    } catch (java.util.zip.ZipException ze) {
//        log->error("ZipException opening file " + f.toString(), ze);
//        return (false);
//    } catch (java.io.IOException ze) {
//        log->error("IOException opening file " + f.toString(), ze);
//        return (false);
//    }
}

/*public*/ /*static*/ bool LoadVSDFileAction::loadVSDFile(QString fp) {
    VSDFile* vsdfile;

    //try {
        // Create a VSD (zip) file.
        vsdfile = new VSDFile(fp);
        Logger* log = new Logger("LoadVSDFileAction");
        log->debug("VSD File name = " + vsdfile->getName());
        if (vsdfile->isInitialized()) {
            VSDecoderManager::instance()->loadProfiles(vsdfile);
        }
        // Cleanup and close files.
// TODO:        vsdfile->close();

        return (vsdfile->isInitialized());
//    } catch (java.util.zip.ZipException ze) {
//        log->error("ZipException opening file " + fp, ze);
//        return (false);
//    } catch (java.io.IOException ze) {
//        log->error("IOException opening file " + fp, ze);
//        return (false);
//    }

    /*
     File f = NULL;
     try {
     f = new File(fp);
     return(loadVSDFile(f));
     } catch (java.io.IOException ioe) {
     log->warn("IO Error auto-loading VSD File: " + (f==NULL?"(NULL)":f.getAbsolutePath()) + " ", ioe);
     return(false);
     } catch (NullPointerException npe) {
     log->warn("NP Error auto-loading VSD File: FP = " + fp, npe);
     return(false);
     }
     */
    }
