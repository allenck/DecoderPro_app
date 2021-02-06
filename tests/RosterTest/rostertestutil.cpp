#include "rostertestutil.h"
#include "loggerfactory.h"
#include "fileutil.h"
#include "rosterentry.h"
#include "instancemanager.h"
#include "decoderfile.h"
#include "decoderindexfile.h"
#include "profile.h"
#include "roster.h"
#include "profilemanager.h"
#include "rosterconfigmanager.h"
#include "decoderindexfile.h"
#include "xmlinclude.h"
#include "joptionpane.h"
#include "xinclude/xinclude.h"

RosterTestUtil::RosterTestUtil(QObject *parent) : QObject(parent)
{

}
/**
 * <p>
 * Utility functions for build rosters and RosterEntries during tests.
 * </p>
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2002, 2012
 * @author	Paul Bender Copyright (C) 2019
 */
// /*public*/ class RosterTestUtil {

// originally copied from RosterTest
/**
 * create a test roster with known contents.
 *
 * @param rosterDir      location of the roster->
 * @param rosterFileName name of the roster file.
 * @return a roster with entries.
 * @throws java.io.IOException if unable to create a test roster
 */
/*public*/ /*static*/ Roster* RosterTestUtil::createTestRoster(File* rosterDir, QString rosterFileName) throw (IOException) {
    FileUtil::createDirectory(rosterDir);

    // create a roster with known contents
    Roster* r = new Roster(rosterDir->getAbsolutePath() + File::separator + rosterFileName);
    r->setRosterLocation(rosterDir->getAbsolutePath());
    r->setRosterIndexFileName(rosterFileName);
    RosterEntry* e1 = new RosterEntry("SP123");
    e1->setId("SP123");
    e1->setDccAddress("123");
    e1->setRoadNumber("123");
    e1->setRoadName("SP");
    e1->ensureFilenameExists();
    e1->putAttribute("key a", "value a");
    e1->putAttribute("key b", "value b");
    CvTableModel* cvTable = new CvTableModel(nullptr, nullptr);
    QStringList sl = QStringList() << "Name" << "Value";
    VariableTableModel* varTable = new VariableTableModel(nullptr, /*new String[]{"Name", "Value"}*/sl, cvTable);
    loadDecoderFromLoco(e1, varTable);
    e1->writeFile(cvTable, varTable);
    r->addEntry(e1);
    RosterEntry* e2 = new RosterEntry("ATSF123");
    e2->setId("ATSF123");
    e2->setDccAddress("456");
    e2->setLongAddress(true);
    e2->setRoadNumber("123");
    e2->setRoadName("ATSF");
    e2->setDecoderModel("Silver");
    e2->setDecoderFamily("Lenz Silver with 6th gen BEMF");
    e2->ensureFilenameExists();
    e2->putAttribute("key a", "value a");
    cvTable = new CvTableModel(nullptr, nullptr);
    varTable = new VariableTableModel(nullptr, QStringList() <<"Name" << "Value", cvTable);
    loadDecoderFromLoco(e2, varTable);
    e2->writeFile(cvTable, varTable);
    r->addEntry(e2);
    RosterEntry* e3 = new RosterEntry("UP123");
    e3->setId("UP123");
    e3->setRoadNumber("123");
    e3->setRoadName("UP");
    e3->ensureFilenameExists();
    e3->putAttribute("key b", "value b");
    cvTable = new CvTableModel(nullptr, nullptr);
    varTable = new VariableTableModel(nullptr, QStringList() <<"Name" << "Value", cvTable);
    loadDecoderFromLoco(e2, varTable);
    e3->writeFile(cvTable, varTable);
    r->addEntry(e3);
    ((RosterConfigManager*)InstanceManager::getDefault("RosterConfigManager"))->setRoster(ProfileManager::getDefault()->getActiveProfile(), r);
    return r;
}

/**
 * Load the variable model for a particular roster entry into memory. This
 * was originally copied from PaneProgFrame
 *
 * @param r        the roster entry to load.
 * @param varTable the variable table to load.
 */
/*public*/ /*static*/ void RosterTestUtil::loadDecoderFromLoco(RosterEntry* r, VariableTableModel* varTable) {
    // get a DecoderFile from the locomotive xml
    QString decoderModel = r->getDecoderModel();
    QString decoderFamily = r->getDecoderFamily();
    log->debug(tr("selected loco uses decoder %1 %2").arg(decoderFamily).arg(decoderModel));
    // locate a decoder like that.
    //QList<DecoderFile*>* l = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList("", decoderFamily, "", "", "", decoderModel);
    // NOTE: DecoderIndex File needs to be updated to use InstanceInitialze interface.
    QList<DecoderFile*> l = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList("", decoderFamily, "", "", "", decoderModel);
    log->debug(tr("found %1 matches").arg(l.size()));
    if (l.isEmpty()) {
        log->debug(tr("Loco uses %1 %2 decoder, but no such decoder defined").arg(decoderFamily).arg(decoderModel));
        // fall back to use just the decoder name, not family
        l = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList("", "", "", "", "", decoderModel);
        log->debug(tr("found %1 matches without family key").arg(l.size()));
    }
    if (!l.isEmpty()) {
        DecoderFile* d = l.at(0);
        loadDecoderFile(d, r, varTable);
    } else {
        if (decoderModel ==("")) {
            log->debug("blank decoderModel requested, so nothing loaded");
        } else {
            log->warn(tr("no matching \"%1\" decoder found for loco, no decoder info loaded").arg(decoderModel));
        }
    }
}

// This was originally copied from PaneProgFrame
/*private*/ /*static*/ void RosterTestUtil::loadDecoderFile(DecoderFile* df, RosterEntry* re, VariableTableModel* variableModel) {
    if (df == nullptr) {
        log->warn("loadDecoder file invoked with null object");
        return;
    }
    log->debug(tr("loadDecoderFile from %1 %2").arg(DecoderFile::fileLocation).arg(df->getFileName()));

    QDomElement decoderRoot = QDomElement();

    try {
        decoderRoot = df->rootFromName(DecoderFile::fileLocation + df->getFileName());
    } catch (/*JDOMException |*/ IOException e) {
        log->error(tr("Exception while loading decoder XML file: %1").arg(df->getFileName()));
    }

    // begin add XInclude logic ACK
    // needed because Qt XML does not automatically do this
    if(XmlInclude::scanForInclude(decoderRoot))
    {
     int ret = JOptionPane::showOptionDialog(nullptr, tr("This may take a while since some include files must be downloaded from the internet.\nDo you wish to save a local copy of the updated file.\nClick on \"Yes\", \"No\" or \"Cancel\" to abort "),tr("Load decoder file"),JOptionPane::YES_NO_CANCEL_OPTION, JOptionPane::QUESTION_MESSAGE);
     if(ret == JOptionPane::CANCEL_OPTION)
      return;
     XInclude* xinclude = new XInclude();
     File* f;
     QStringList slist = QStringList() << FileUtil::getUserFilesPath() << FileUtil::getProgramPath()+ "xml";
     QUrl url = QUrl(FileUtil::findURL(DecoderFile::fileLocation+df->getFileName(),slist));
     if(ret == JOptionPane::YES_OPTION)
     {
      xinclude->copyXml(&url, f =new File(FileUtil::getUserFilesPath()+ DecoderFile::fileLocation+ df->getFileName()), nullptr);
     }
      else
     {
      QTemporaryDir dir;
      xinclude->copyXml(&url, f = new File(dir.path()+df->getFileName()),nullptr);
     }
     decoderRoot = df->rootFromFile(f);
    }
    // end add XInclude logic ACK

    df->getProductID();
    if (!decoderRoot.isNull()) {
        // load variables from decoder tree
        df->loadVariableModel(decoderRoot.firstChildElement("decoder"), variableModel);

        // load function names
        re->loadFunctions(decoderRoot.firstChildElement("decoder").firstChildElement("family").firstChildElement("functionlabels"));
    }
}

/*private*/ /*final*/ /*static*/ Logger* RosterTestUtil::log = LoggerFactory::getLogger("RosterTestUtil");

