#include "loadxmlvsdecoderaction.h"
#include "vsdecoderpreferences.h"
#include "jfilechooser.h"
#include "vsdecoderpane.h"
#include "file.h"

//LoadXmlVSDecoderAction::LoadXmlVSDecoderAction(QObject *parent) :
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
// /*public*/ class LoadXmlVSDecoderAction extends AbstractAction {

    //static final ResourceBundle rb = VSDecoderBundle.bundle();

/**
 * Constructor
 *
 * @param s Name for the action.
 */
/*public*/ LoadXmlVSDecoderAction::LoadXmlVSDecoderAction(QString s, QObject *parent) :
  AbstractAction(s, parent) {
    //super(s);
    // Pretty sure I don't need this
    // disable the ourselves if there is no throttle Manager
/*
     if (jmri.InstanceManager.throttleManagerInstance() == NULL) {
     setEnabled(false);
     }
     */
 common();
}

/*public*/ LoadXmlVSDecoderAction::LoadXmlVSDecoderAction( QObject *parent) :
  AbstractAction(tr("Load VSDecoder Profile"), parent) {
    //this("Load VSDecoder Profile"); // Shouldn't this be in the resource bundle?
 common();
}

void LoadXmlVSDecoderAction::common()
{
 log = new Logger("LoadXmlVSDecoderAction");
 fileChooser = NULL;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


/**
 * The action is performed. Let the user choose the file to load from. Read
 * XML for each VSDecoder Profile.
 *
 * @param e The event causing the action.
 */
/*public*/ void LoadXmlVSDecoderAction::actionPerformed(ActionEvent* e) {
    if (fileChooser == NULL) {
        fileChooser = XmlFile::userFileChooser(tr("XML Files"), "xml");
        fileChooser->setDialogType(JFileChooser::OPEN_DIALOG);
        fileChooser->setCurrentDirectory(new File(VSDecoderPane::getDefaultVSDecoderFolder()));
    }
    int retVal = fileChooser->showOpenDialog(NULL);
    if (retVal != JFileChooser::APPROVE_OPTION) {
        return;
        // give up if no file selected
    }

    //try {
        loadVSDecoderProfile(fileChooser->getSelectedFile());
//    } catch (java.io.IOException e1) {
//        log.warn("Exception while reading file", e1);
//    }
}

/**
 * Parse the XML file and create ThrottleFrames. Returns true if throttle
 * loaded successfully.
 *
 * @param f The XML file containing throttles.
 */
/*public*/ bool LoadXmlVSDecoderAction::loadVSDecoderProfile(File* f) //throws java.io.IOException
{
    //try {
 VSDecoderPrefs* prefs = new VSDecoderPrefs();
 QDomElement root = prefs->rootFromFile(f);

 // WARNING: This may be out of sync with the Store... the root element is <VSDecoderConfig>
 // not sure, must investigate.  See what XmlFile.rootFromFile(f) does...
 QDomNodeList profiles = root.elementsByTagName("VSDecoder");
 if ((!profiles.isEmpty()) && (profiles.size() > 0))
 {
     // Create a new VSDecoder object for each Profile in the XML file.
     //for (java.util.Iterator<Element> i = profiles.iterator(); i.hasNext();)
  for(int i = 0; i < profiles.size(); i++)
  {
   QDomElement e = profiles.at(i).toElement();
   log->debug(e.tagName());
         //VSDecoder vsd = VSDecoderManager.instance().getVSDecoder(e.getAttribute("name").getValue(), f.getPath());
  }
 }

//    } catch (org.jdom2.JDOMException ex) {
//        log.warn("Loading VSDecoder Profile exception", ex);
//        return false;
//    }
 return true;
}

