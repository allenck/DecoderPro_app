#include "installdecoderfileaction.h"
#include "xmlfile.h"
#include "jfilechooser.h"
#include "file.h"
#include "logger.h"
#include "jmripanel.h"
#include <QUrl>

//InstallDecoderFileAction::InstallDecoderFileAction(QObject *parent) :
//  InstallDecoderURLAction(parent)
//{
//}

/**
 * Install decoder definition from local file.
 *
 * @author	Bob Jacobsen Copyright (C) 2008
 * @version	$Revision: 28746 $
 * @see jmri.jmrit.XmlFile
 */
///*public*/ class InstallDecoderFileAction extends InstallDecoderURLAction {

    /**
     *
     */
    //private static final long serialVersionUID = 8029283743478939558L;

    /*public*/ InstallDecoderFileAction::InstallDecoderFileAction(QString s, WindowInterface* wi)
 :
   InstallDecoderURLAction(s, wi){
        //super(s, wi);
 common();
    }

    /*public*/ InstallDecoderFileAction::InstallDecoderFileAction(QString s, QIcon i, WindowInterface* wi)
 :
   InstallDecoderURLAction(s,i, wi){
        //super(s, i, wi);
 common();
    }

    /*public*/ InstallDecoderFileAction::InstallDecoderFileAction(QString s,QObject *parent) :
  InstallDecoderURLAction(s, parent) {
        //super(s);
 common();
    }

    /*public*/ InstallDecoderFileAction::InstallDecoderFileAction(QString s, QWidget* who)
 : InstallDecoderURLAction(s, who)
 {
        //super(s);
 common();

    }

void InstallDecoderFileAction::common()
{
 log = new Logger("InstallDecoderFileAction");
 fci = NULL;
}

QUrl* InstallDecoderFileAction::pickURL(QWidget* who)
{
    if (fci == NULL) {
        fci = XmlFile::userFileChooser("XML files", "xml");
    }
    // request the filename from an open dialog
    //fci->rescanCurrentDirectory();
    int retVal = fci->showOpenDialog(who);
    // handle selection or cancel
    if (retVal == JFileChooser::APPROVE_OPTION) {
        File* file = fci->getSelectedFile();
        if (log->isDebugEnabled()) {
            log->debug("located file " + file->getPath() + " for XML processing");
        }
        try {
            return new QUrl("file:" + file->getCanonicalPath());
        } catch (Exception e) {
            log->error("Unexpected exception in new URL: " /*+ e*/);
            return NULL;
        }
    } else {
        log->debug("cancelled in open dialog");
        return NULL;
    }
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* InstallDecoderFileAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
