#include "printdecoderlistaction.h"
#include "decoderfile.h"
#include "hardcopywriter.h"
#include "version.h"
#include "namedicon.h"
#include "fileutil.h"
#include "decoderindexfile.h"
#include "logger.h"
#include "jlabel.h"
#include <QUrl>
#include "instancemanager.h"

//PrintDecoderListAction::PrintDecoderListAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * Action to print a summary of available decoder definitions
 * <P>
 * This uses the older style printing, for compatibility with Java 1.1.8 in
 * Macintosh MRJ
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 * @author Dennis Miller Copyright (C) 2005
 * @version $Revision: 28746 $
 */
///*public*/ class PrintDecoderListAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 4693793673785831632L;

/*public*/ PrintDecoderListAction::PrintDecoderListAction(QString actionName, JFrame* frame, bool preview, QObject *parent) :
  AbstractAction(actionName, parent)
{
   //super(actionName);
    mFrame = frame;
    //mFrame->setVisible(false);
    isPreview = preview;
    log = new Logger("PrintDecoderListAction");
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


/*public*/ void PrintDecoderListAction::actionPerformed(ActionEvent* /*e*/) {

    // obtain a HardcopyWriter to do this
    HardcopyWriter* writer = NULL;
//    try {
        writer = new HardcopyWriter(mFrame, "DecoderPro V" + Version::name() + " Decoder Definitions", 10, .5, .5, .5, .5, isPreview);
//    } catch (HardcopyWriter.PrintCanceledException ex) {
//        log->debug("Print cancelled");
//        return;
//    }

    // add the image
        NamedIcon* icon = new NamedIcon(FileUtil::findURL("resources/decoderpro.gif", FileUtil::INSTALLED).path(), "");
    // we use an ImageIcon because it's guaranteed to have been loaded when ctor is complete
    writer->write(icon->getImage(), new JLabel(icon));

    // Loop through the decoder index, printing as needed
    QString lastMfg = "";
    QString lastFamily = "";

    DecoderIndexFile* f = (DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile");
    QList<DecoderFile*> l = f->matchingDecoderList(NULL, NULL, NULL, NULL, NULL, NULL); // take all
    int i = -1;
    log->debug("Roster list size: " + l.size());
    for (i = 0; i < l.size(); i++) {
        DecoderFile* d = l.at(i);
        if (d->getMfg()!=(lastMfg)) {
            printMfg(d, writer);
            lastMfg = d->getMfg();
            lastFamily = "";
        }
        if (d->getFamily()!=(lastFamily)) {
            printFamily(d, writer);
            lastFamily = d->getFamily();
        }
        if (d->getFamily()!=(d->getModel())) {
            printEntry(d, writer);
        }
    }

    // and force completion of the printing
    writer->close();
}

void PrintDecoderListAction::printEntry(DecoderFile* d, HardcopyWriter* w) {
    try {
        QString s = "\n                       " + d->getModel();
        w->write(s, 0, s.length());
    } catch (IOException e) {
        log->error("Error printing: " + e.getMessage());
    }
}

void PrintDecoderListAction::printMfg(DecoderFile* d, HardcopyWriter* w) {
    try {
        QString s = "\n\n" + d->getMfg();
        w->write(s, 0, s.length());
    } catch (IOException e) {
        log->error("Error printing: " + e.getMessage());
    }
}

void PrintDecoderListAction::printFamily(DecoderFile* d, HardcopyWriter* w) {
    try {
        QString s = "\n           " + d->getFamily();
        w->write(s, 0, s.length());
    } catch (IOException e) {
        log->error("Error printing: " + e.getMessage());
    }
}
