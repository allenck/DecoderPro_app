#include "loadxmlthrottleslayoutaction.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "throttlemanager.h"
#include "jfilechooser.h"
#include "throttlewindow.h"
#include "throttleframemanager.h"
#include "joptionpane.h"
#include "xmlfile.h"
#include "throttleslistpanel.h"

/**
 * Load throttles from XML
 *
 * @author Glen Oberhauser 2004
 */
///*public*/ class LoadXmlThrottlesLayoutAction extends AbstractAction {

/**
 * Constructor
 *
 * @param s Name for the action.
 */
/*public*/ LoadXmlThrottlesLayoutAction::LoadXmlThrottlesLayoutAction(QString s, QObject* parent) : AbstractAction(s, parent){
    //super(s);
    // disable the ourselves if there is no throttle Manager
    if (InstanceManager::getNullableDefault("ThrottleManager") == NULL) {
        setEnabled(false);
    }
    connect( this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/*public*/ LoadXmlThrottlesLayoutAction::LoadXmlThrottlesLayoutAction(QObject* parent)  : AbstractAction(tr("Open Throttle"), parent){
    //this("Open Throttle");
 connect( this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}


/**
 * The action is performed. Let the user choose the file to load from. Read
 * XML for each ThrottleFrame.
 *
 * @param e The event causing the action.
 */
//@Override
/*public*/ void LoadXmlThrottlesLayoutAction::actionPerformed(/*ActionEvent e*/) {
    if (fileChooser == NULL) {
        fileChooser = XmlFile::userFileChooser(tr("XML files"), "xml");
        fileChooser->setDialogType(JFileChooser::OPEN_DIALOG);
        fileChooser->setCurrentDirectory(new File(ThrottleWindow::getDefaultThrottleFolder()));
    }
    int retVal = fileChooser->showOpenDialog(NULL);
    if (retVal != JFileChooser::APPROVE_OPTION) {
        return;
        // give up if no file selected
    }

    // if exising frames are open ask to destroy those or merge.
    if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottleWindows().hasNext()) {
        QVariantList possibleValues = QVariantList() << tr("Merge")
            << tr("Replace")
            << tr("Cancel");
        int selectedValue = JOptionPane::showOptionDialog(NULL,
                tr("Do you wish to Merge saved throttles with open throttles or\n Replace open throttles"),
                tr("Loading Throttles"),
                JOptionPane::YES_NO_CANCEL_OPTION,
                JOptionPane::INFORMATION_MESSAGE, QIcon(), possibleValues,
                possibleValues[0]);
        if (selectedValue == JOptionPane::NO_OPTION) {
            // replace chosen - close all then load
            ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->requestAllThrottleWindowsDestroyed();
        }
    }
    try {
        loadThrottlesLayout(fileChooser->getSelectedFile());
    } catch (IOException e1) {
        log->warn("Exception while reading file" + e1.getMessage());
    }
}

/**
 * Parse the XML file and create ThrottleFrames. Returns true if throttle
 * loaded successfully.
 *
 * @param f The XML file containing throttles.
 */
//@SuppressWarnings("unchecked")
/*public*/ bool LoadXmlThrottlesLayoutAction::loadThrottlesLayout(File* f) throw (IOException) {
    try {
        //ThrottlePrefs prefs = new ThrottlePrefs();
  XmlFile* prefs = new XmlFile();
        QDomElement root = prefs->rootFromFile(f);
        QDomNodeList throttles = root.elementsByTagName("ThrottleFrame");
        ThrottleFrameManager* tfManager = (ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager");
        if ((!throttles.isEmpty()) && (throttles.size() > 0)) { // OLD FORMAT
            for (int i = 0; i < throttles.size(); i++) {
             QDomElement e = throttles.at(i).toElement();
                //SwingUtilities.invokeLater(() -> {
                    ThrottleWindow* tf = tfManager->createThrottleFrame();
                    tf->setXml(e);
                    tf->toFront();
//                });
            }
        } else {
            throttles = root.elementsByTagName("ThrottleWindow");
            for (int i = 0; i < throttles.size(); i++) {
             QDomElement e = throttles.at(i).toElement();
//                SwingUtilities.invokeLater(() -> {
                    ThrottleWindow* tw = tfManager->createThrottleWindow();
                    tw->setXml(e);
                    tw->setVisible(true);
//                });
            }
            QDomElement tlp = root.firstChildElement("ThrottlesListPanel");
            if (!tlp.isNull()) {
                ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesListPanel()->setXml(tlp);
            }
        }
    } catch (JDOMException ex) {
        log->warn("Loading Throttles exception" + ex.getMessage());
        return false;
    }
    return true;
}

/**
 * An extension of the abstract XmlFile. No changes made to that class.
 *
 * @author glen
 */
//    static class ThrottlePrefs extends XmlFile {
//    }

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* LoadXmlThrottlesLayoutAction::log = LoggerFactory::getLogger("LoadXmlThrottlesLayoutAction");
