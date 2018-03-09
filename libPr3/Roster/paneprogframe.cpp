#include "paneprogframe.h"
#include "ui_paneprogframe.h"
#include "decoderfile.h"
#include "rosterentry.h"
#include "programmer.h"
#include "cvtablemodel.h"
#include "indexedcvtablemodel.h"
#include "variabletablemodel.h"
#include "rosterentrypane.h"
#include "resettablemodel.h"
#include "decoderindexfile.h"
#include "instancemanager.h"
#include "QMessageBox"
#include "roster.h"
#include "shutdownmanager.h"
#include "shutdowntask.h"
#include "paneprogpane.h"
#include <QDesktopWidget>
#include "rostermedia.h"
#include "functionlabelspane.h"
#include "busyglasspane.h"
#include "shortaddrvariablevalue.h"
#include "longaddrvariablevalue.h"
#include "enumvariablevalue.h"
#include "paneprogpane.h"
#include "defaultshutdownmanager.h"
#include "fileutil.h"
#include "factoryresetaction.h"
#include <QVBoxLayout>
#include "slotmanager.h"
#include <QMenuBar>
#include <QMenu>
#include "printaction.h"
#include "printcvaction.h"
#include "printrosterentry.h"
#include "defaultprogrammermanager.h"
#include "programmerfacadeselector.h"
#include "jseparator.h"
#include "programmingmode.h"
#include "programmerconfigmanager.h"
#include "verifywriteprogrammerfacade.h"
#include "csvimportaction.h"
#include "csvexportaction.h"

int PaneProgFrame::iLabel=0;

// derived from java PaneProgFrame class.
bool PaneProgFrame::showEmptyPanes = true;

PaneProgFrame::PaneProgFrame(DecoderFile* pDecoderFile, RosterEntry* pRosterEntry, QString frameTitle, QString pProgrammerFile, Programmer* pProg, bool opsMode, QWidget *parent) :
    JmriJFrame(parent),
    ui(new Ui::PaneProgFrame)
{
 ui->setupUi(this);
 setObjectName("PaneProgFrame");
 this->pProgrammerFile = pProgrammerFile;
 _opsMode = opsMode;

 log = new Logger("PaneProgFrame");
 log->setDebugEnabled(true);
 progStatus = new QLabel(tr("Programmer Status: Idle"));
 ui->statusbar->addPermanentWidget(progStatus);
 //ui->statusbar->addPermanentWidget(progStatus);
 // create the tables
 mProgrammer   = pProg;
 setWindowTitle(frameTitle);
 cvModel       = new CvTableModel(progStatus, mProgrammer);
 iCvModel      = new IndexedCvTableModel(progStatus, mProgrammer);
 QStringList list = QStringList();
 list << tr("Name") << tr("Value");
 variableModel = new VariableTableModel(progStatus, list, cvModel, iCvModel);

 resetModel    = new ResetTableModel(progStatus, mProgrammer);
 _busy = false;
 _read = true;
 _programmingPane = NULL;
 primaryAddr = NULL;
 extendAddr = NULL;
 addMode = NULL;
 decoderDirtyTask = NULL;
 fileDirtyTask = NULL;
 glassPane = NULL;
 bottom = NULL;
 modePane = NULL;

 // handle the roster entry
 _rosterEntry =  pRosterEntry;
 if (_rosterEntry == NULL) log->error("NULL RosterEntry pointer");
 else _rosterEntry->setOpen(true);
 filename = pProgrammerFile;
 readChangesButton = new JToggleButton(tr("Read changes on all sheets"));
 writeChangesButton = new JToggleButton(tr("Write changes on all sheets"));
 readAllButton = new JToggleButton(tr("Read all sheets"));
 writeAllButton = new JToggleButton(tr("Write all sheets"));


 QTimer::singleShot(1,this, SLOT(installComponents()));

 if (_rosterEntry->getFileName() != NULL)
 {
  // set the loco file name in the roster entry
  _rosterEntry->readFile();  // read, but don't yet process
 }

 if (pDecoderFile != NULL)
  loadDecoderFile(pDecoderFile, _rosterEntry);
 else
  loadDecoderFromLoco(pRosterEntry);



 // save default values
 saveDefaults();

 // finally fill the CV values from the specific loco file
 if (_rosterEntry->getFileName() != NULL) _rosterEntry->loadCvModel(cvModel, iCvModel);

 // mark file state as consistent
 variableModel->setFileDirty(false);

// // if the Reset Table was used lets enable the menu item
// if (!_opsMode) {
//     if (resetModel->rowCount(QModelIndex()) > 0) {
//         resetMenu->setEnabled(true);
//     }
// }
 connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(on_tabWidget_currentChanged(int)));
 // and build the GUI
 loadProgrammerFile(pRosterEntry);

 // optionally, add extra panes from the decoder file
 QString a;
 if ( (a = programmerRoot.firstChildElement("programmer").attribute("decoderFilePanes")) != ""
      && a==("yes"))
 {
  if (!decoderRoot.isNull())
  {
   if (log->isDebugEnabled()) log->debug("will process "+QString::number(paneList.size())+" pane definitions from decoder file");
   for (int i=0; i<decoderPaneList.size(); i++)
   {
    // load each pane
    //QString pname = jmri.util.jdom.LocaleSelector.attribute(paneList.get(i), "name");
    QString pname = decoderPaneList.at(i).toElement().attribute( "name");
    if(pname == "")
    {
     QDomElement nameElement = decoderPaneList.at(i).firstChildElement("name");
     if(!nameElement.isNull())
      pname = nameElement.text();
    }
    // handle include/exclude
    if ( isIncludedFE(decoderPaneList.at(i).toElement(), modelElem, _rosterEntry, "", "") )
    {
     newPane( pname, decoderPaneList.at(i).toElement(), modelElem, true);  // show even if empty??
    }
   }
  }
 }
 // set the programming mode
 if (pProg != NULL)
 {
  if (((AddressedProgrammerManager*)InstanceManager::getOptionalDefault("AddressedProgrammerManager"))!= NULL
                      || ((GlobalProgrammerManager*)InstanceManager::getOptionalDefault("GlobalProgrammerManager"))!= NULL)
  {
   // go through in preference order, trying to find a mode
   // that exists in both the programmer and decoder.
   // First, get attributes. If not present, assume that
   // all modes are usable
   QDomElement programming = QDomElement();
   if (!decoderRoot.isNull()
     && (programming = decoderRoot.firstChildElement("decoder").firstChildElement("programming"))!= QDomElement())
   {
    // add a verify-write facade if configured
    Programmer* pf = mProgrammer;
    if (getDoConfirmRead())
    {
     pf = new VerifyWriteProgrammerFacade(pf);
     log->debug(tr("adding VerifyWriteProgrammerFacade, new programmer is %1").arg(pf->metaObject()->className()));
    }
    // add any facades defined in the decoder file
    pf = ProgrammerFacadeSelector::loadFacadeElements(programming, pf, getCanCacheDefault(), pProg);
    log->debug("new programmer "+QString(pf->metaObject()->className()));
    mProgrammer = pf;
    cvModel->setProgrammer(pf);
    iCvModel->setProgrammer(pf);
    resetModel->setProgrammer(pf);
    log->debug("Found programmers: "+QString(cvModel->getProgrammer()->metaObject()->className())+" "+QString(iCvModel->getProgrammer()->metaObject()->className()));
   }

   if (!programming.isNull()) pickProgrammerMode(programming);

  }
  else
  {
   log->error("Can't set programming mode, no programmer instance");
  }
 }

 // now that programmer is configured, set the programming GUI
 setProgrammingGui(tempPane);

// pack();

 if (log->isDebugEnabled()) log->debug("PaneProgFrame \""+frameTitle
                                     +"\" constructed for file "+_rosterEntry->getFileName()
                                       +", unconstrained size is "+/*super.getPreferredSize()*/QString::number(QMainWindow::size().height())+","+QString::number(QMainWindow::size().width())
                                     +", constrained to "+/*getPreferredSize());*/QString::number(getPreferredSize().height())+","+QString::number(getPreferredSize().width()));

 resetStatus(CvValue::FROMFILE); // ACK reset any CvValues marked as EDITED to FROMFILE.

}

PaneProgFrame::~PaneProgFrame()
{
 delete ui;
}
/**
 * Front end to DecoderFile.isIncluded()
 * <ul>
 * <li>Retrieves "productID" and "model attributes from the "model" element
 * and "family" attribute from the roster entry. </li>
 * <li>Then invokes DecoderFile.isIncluded() with the retrieved values.</li>
 * <li>Deals deals gracefully with NULL or missing elements and attributes.</li>
 * </ul>
 * @param e                 XML element with possible "include" and "exclude" attributes to be checked
 * @param aModelElement     "model" element from the Decoder Index, used to get "model" and "productID".
 * @param aRosterEntry      The current roster entry, used to get "family".
 * @param extraIncludes     additional "include" terms
 * @param extraExcludes     additional "exclude" terms
 */


/*public*/ /*static*/ bool PaneProgFrame::isIncludedFE(QDomElement e, QDomElement aModelElement, RosterEntry* aRosterEntry, QString extraIncludes, QString extraExcludes)
{

 QString pID;
// try
// {
 pID = aModelElement.attribute("productID", "");
//    } catch (Exception ex){
//        pID = NULL;
//    }

 QString modelName;
//    try {
 modelName = aModelElement.attribute("model", "");
//    } catch (Exception ex){
//        modelName = NULL;
//    }

 QString familyName;
//    try {
 familyName = aRosterEntry->getDecoderFamily();
//    } catch (Exception ex){
//        familyName = NULL;
//    }
 return DecoderFile::isIncluded(e, pID, modelName, familyName, extraIncludes, extraExcludes);
}
/*protected*/ void PaneProgFrame::loadDecoderFromLoco(RosterEntry* r)
{
 // get a DecoderFile from the locomotive xml
 QString decoderModel = r->getDecoderModel();
 QString decoderFamily = r->getDecoderFamily();
 if (log->isDebugEnabled()) log->debug("selected loco uses decoder "+decoderFamily+" "+decoderModel);
 // locate a decoder like that.
 QList<DecoderFile*>* l = DecoderIndexFile::instance()->matchingDecoderList("", decoderFamily, "", "", "", decoderModel);
 if (log->isDebugEnabled()) log->debug("found "+QString::number(l->size())+" matches");
 if (l->size() == 0)
 {
  log->debug("Loco uses "+decoderFamily+" "+decoderModel+" decoder, but no such decoder defined");
  // fall back to use just the decoder name, not family
  l = DecoderIndexFile::instance()->matchingDecoderList("", "", "", "", "", decoderModel);
  if (log->isDebugEnabled()) log->debug("found "+QString::number(l->size())+" matches without family key");
 }
 if (l->size() > 0)
 {
  DecoderFile* d = l->at(0);
  loadDecoderFile(d, r);
 }
 else
 {
  if (decoderModel==(""))
   log->debug("blank decoderModel requested, so nothing loaded");
  else
   log->warn("no matching \""+decoderModel+"\" decoder found for loco, no decoder info loaded");
 }
}

/*protected*/ void PaneProgFrame::pickProgrammerMode(/*@NonNull*/ QDomElement programming)
{
 bool paged = true;
 bool directbit= true;
 bool directbyte= true;
 bool _register= true;
 QString a;

 // set the programming attributes for DCC
 if ( (a = programming.attribute("paged")) != "" )
  if (a==("no")) paged = false;
 if ( (a = programming.attribute("direct")) != "" )
 {
  if (a==("no")) { directbit = false; directbyte = false; }
  else if (a==("bitOnly")) { directbit = true; directbyte = false; }
  else if (a==("byteOnly")) { directbit = false; directbyte = true; }
 }
 if ( (a = programming.attribute("register")) != "" )
 if (a==("no")) _register = false;

 // is the current mode OK?
 log->debug(QString("XML specifies modes: P ")+(paged?"true":"false")+" DBi "+(directbit?"true":"false")+" Dby "+(directbyte?"true":"false")+" R "+(_register?"true":"false")+" now "+QString(mProgrammer->getMode()->toString()));

 // find a mode to set it to

 QList<ProgrammingMode*> modes = mProgrammer->getSupportedModes();
 if (modes.contains(DefaultProgrammerManager::DIRECTBITMODE)&&directbit)
 {
  mProgrammer->setMode(DefaultProgrammerManager::DIRECTBITMODE);
  log->debug("Set to DIRECTBITMODE");
 }
 else if (modes.contains(DefaultProgrammerManager::DIRECTBYTEMODE)&&directbyte)
 {
  mProgrammer->setMode(DefaultProgrammerManager::DIRECTBYTEMODE);
  log->debug("Set to DIRECTBYTEMODE");
 }
 else if (modes.contains(DefaultProgrammerManager::PAGEMODE)&&paged)
 {
  mProgrammer->setMode(DefaultProgrammerManager::PAGEMODE);
  log->debug("Set to PAGEMODE");
 }
 else if (modes.contains(DefaultProgrammerManager::REGISTERMODE)&&_register)
 {
  mProgrammer->setMode(DefaultProgrammerManager::REGISTERMODE);
  log->debug("Set to REGISTERMODE");
 }
 else log->warn("No acceptable mode found, leave as found");
}

/*protected*/ void PaneProgFrame::loadDecoderFile(DecoderFile* df, RosterEntry* re)
{
 if (df == NULL)
 {
  log->warn("loadDecoder file invoked with NULL object");
  return;
 }
 if (log->isDebugEnabled()) log->debug("loadDecoderFile from "+DecoderFile::fileLocation
                                    +" "+df->getFilename());

 try
 {
  if(DecoderFile::fileLocation.startsWith(QDir::separator()))
   decoderRoot = df->rootFromName(DecoderFile::fileLocation+df->getFilename());
  else
   decoderRoot = df->rootFromName(XmlFile::xmlDir()+DecoderFile::fileLocation+df->getFilename());
 }
 catch (Exception e)
 {
  log->error("Exception while loading decoder XML file: "+df->getFilename(), e.getMessage());
 }
    // load variables from decoder tree
    df->getProductID();
    df->loadVariableModel(decoderRoot.firstChildElement("decoder"), variableModel);

    // load reset from decoder tree
    if (variableModel->piCv() >= 0) {
        resetModel->setPiCv(variableModel->piCv());
    }
    if (variableModel->siCv() >= 0) {
        resetModel->setSiCv(variableModel->siCv());
    }
    df->loadResetModel(decoderRoot.firstChildElement("decoder"), resetModel);

    // load function names
    re->loadFunctions(decoderRoot.firstChildElement("decoder").firstChildElement("family").firstChildElement("functionlabels"));

    // get the showEmptyPanes attribute, if yes/no update our state
    if (decoderRoot.attribute("showEmptyPanes") != "")
    {
        if (log->isDebugEnabled()) log->debug("Found in decoder "+decoderRoot.attribute("showEmptyPanes"));
        if (decoderRoot.attribute("showEmptyPanes")==("yes"))
            setShowEmptyPanes(true);
        else if (decoderRoot.attribute("showEmptyPanes")==("no"))
            setShowEmptyPanes(false);
        // leave alone for "default" value
        if (log->isDebugEnabled()) log->debug(tr("result ")+(getShowEmptyPanes()?"true":"false"));
    }

    // save the pointer to the model element
    modelElem = df->getModelElement();
}

/*protected*/ void PaneProgFrame::loadProgrammerFile(RosterEntry* r)
{
 // Open and parse programmer file
 XmlFile* pf = new XmlFile();  // XmlFile is abstract
 try
 {
  if(filename.startsWith(FileUtil::SEPARATOR))
   programmerRoot = pf->rootFromName(filename);
  else
   programmerRoot = pf->rootFromName(FileUtil::getUserFilesPath()+filename);
  // programmerRoot = pf->rootFromName(FileUtil::findURL(filename).path());
  // get the showEmptyPanes attribute, if yes/no update our state
  if (programmerRoot.firstChildElement("programmer").attribute("showEmptyPanes") != "")
  {
   if (log->isDebugEnabled()) log->debug("Found in programmer "+programmerRoot.firstChildElement("programmer").attribute("showEmptyPanes"));
   if (programmerRoot.firstChildElement("programmer").attribute("showEmptyPanes")==("yes"))
    setShowEmptyPanes(true);
   else if (programmerRoot.firstChildElement("programmer").attribute("showEmptyPanes")==("no"))
    setShowEmptyPanes(false);
   // leave alone for "default" value
   if (log->isDebugEnabled()) log->debug(tr("result ")+(getShowEmptyPanes()?"true":"false"));
  }

  // get extra any panes from the decoder file
  QString a;
  if ( (a = programmerRoot.firstChildElement("programmer").attribute("decoderFilePanes")) != ""
                   && a==("yes"))
  {
   if (!decoderRoot.isNull())
   {
    decoderPaneList = decoderRoot.elementsByTagName("pane");
   }
  }// load programmer config from programmer tree
  readConfig(programmerRoot, r);
 }
 catch (Exception e)
 {
  log->error("exception reading programmer file: "+filename, e.getMessage());
  // provide traceback too
//        e.printStackTrace();
 }
}
/**
 * @return true if decoder needs to be written
 */
/*protected*/ bool PaneProgFrame::checkDirtyDecoder()
{
 if (log->isDebugEnabled()) log->debug(tr("Checking decoder dirty status. CV: ")+(cvModel->decoderDirty()?"true":"false")+" variables:"+(variableModel->decoderDirty()?"true":"false"));
 return (getModePane()!= NULL && (cvModel->decoderDirty() || variableModel->decoderDirty()) );
}

/*protected*/ void PaneProgFrame::resetStatus(int newStatus)
{
 cvModel->resetDecoderDirty(newStatus);
 variableModel->resetStatus(newStatus);
}

/**
 * @return true if file needs to be written
 */
/*protected*/ bool PaneProgFrame::checkDirtyFile()
{
 return (variableModel->fileDirty()
            || _rPane->guiChanged(_rosterEntry)
// TODO:            || _flPane.guiChanged(_rosterEntry) || _rMPane.guiChanged(_rosterEntry)
            );
}
/*protected*/ void PaneProgFrame::handleDirtyFile() {
}

void PaneProgFrame::closeEvent(QCloseEvent * e)
{
 windowClosing(e);
}

/**
 * Close box has been clicked; handle check for dirty with respect to
 * decoder or file, then close.
 * @param e Not used
 */
/*public*/ void PaneProgFrame::windowClosing(QCloseEvent* e)
{

 // Don't want to actually close if we return early
 //    setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

 // check for various types of dirty - first table data not written back
 if (log->isDebugEnabled()) log->debug(tr("Checking decoder dirty status. CV: ")+(cvModel->decoderDirty()?"true":"false")+" variables:"+(variableModel->decoderDirty()?"true":"false"));
 if (checkDirtyDecoder())
 {
  //        if (JOptionPane.showConfirmDialog(NULL,
  //                                          tr("PromptCloseWindowNotWrittenDecoder"),
  //                                          tr("PromptChooseOne"),
  //                                          JOptionPane.OK_CANCEL_OPTION) ==  JOptionPane.CANCEL_OPTION) return;
  switch(QMessageBox::question(0, tr("Close Window"), tr("Some changes have not been written to the decoder. They will be lost. Close window?"), QMessageBox::Ok | QMessageBox::Cancel))
  {
  case QMessageBox::Ok:
   break;
  default:
  case QMessageBox::Cancel:
   return;
  }
 }
 if (checkDirtyFile())
 {
//        int option = JOptionPane.showOptionDialog(NULL,tr("PromptCloseWindowNotWrittenConfig"),
//                    tr("PromptChooseOne"),
//                    JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.WARNING_MESSAGE, NULL,
//                    new String[]{tr("PromptSaveAndClose"), tr("PromptClose"), tr("PromptCancel")},
//                            tr("PromptSaveAndClose"));
//        if (option==0) {
//            // save requested
//            if (!storeFile()) return;   // don't close if failed
//        } else if (option ==2) {
//            // cancel requested
//            return; // without doing anything
//        }
  switch(QMessageBox::question(0, tr("Close Window"), tr("Some changes have not been written to the decoder. They will be lost. Close window?"), QMessageBox::Ok | QMessageBox::Save |  QMessageBox::Cancel))
  {
  case QMessageBox::Save:
   if (!storeFile()) return;   // don't close if failed
   break;
  default:
  case QMessageBox::Cancel:
   return;
  }
 }
 // Check for a "<new loco>" roster entry; if found, remove it
 QList<RosterEntry*> l = Roster::instance()->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, tr("<new loco>"));
 if (l.size() > 0 && log->isDebugEnabled()) log->debug("Removing "+QString::number(l.size())+" <new loco> entries");
int x = l.size()+1;
 while (l.size() > 0 )
 {
  Roster::instance()->removeEntry(l.at(0));
  l = Roster::instance()->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, tr("<new loco>"));
  x--;
  if (x==0)
  {
   log->error("We have tried to remove all the entries, however an error has occured which has resulted in the entries not being deleted correctly");
   l = QList<RosterEntry*>();
  }
 }

 // OK, continue close
 //    setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);

 // deregister shutdown hooks
 if (InstanceManager::shutDownManagerInstance()!=NULL)
  InstanceManager::shutDownManagerInstance()->deregister(decoderDirtyTask);
 decoderDirtyTask = NULL;
 if (InstanceManager::shutDownManagerInstance()!=NULL)
  InstanceManager::shutDownManagerInstance()->deregister(fileDirtyTask);
 fileDirtyTask = NULL;

 // do the close itself
 JmriJFrame::windowClosing(e);
}

//@SuppressWarnings("unchecked")
void PaneProgFrame::readConfig(QDomElement root, RosterEntry* r)
{
 // check for "programmer" element at start
 QDomElement base;
 if ( (base = root.firstChildElement("programmer")).isNull())
 {
  log->error("xml file top element is not programmer");
  return;
 }

 // add the Info tab
 ui->tabWidget->clear();
 if (root.firstChildElement("programmer").attribute("showRosterPane")!="")
 {
  if (root.firstChildElement("programmer").attribute("showRosterPane")==("no"))
  {
   makeInfoPane(r);
  }
  else
  {
   //tabPane.addTab(tr("ROSTER ENTRY"), makeInfoPane(r));
   ui->tabWidget->addTab(makeInfoPane(r), tr("Roster Entry"));
  }
 }
 else
 {
  //tabPane.addTab(tr("ROSTER ENTRY"), makeInfoPane(r));
  ui->tabWidget->addTab(makeInfoPane(r), tr("Roster Entry"));
 }
 // add the Function Label tab
 if(root.firstChildElement("programmer").attribute("showFnLanelPane") == "yes")
 {
  ui->tabWidget->addTab(makeFunctionLabelPane(r), tr("Function Labels"));
 }
 else
 {
  // make it, just don't make it visible
  makeFunctionLabelPane(r);
 }

 // add the Media tab
 if (root.firstChildElement("programmer").attribute("showRosterMediaPane")==("yes"))
 {
  ui->tabWidget->addTab( makeMediaPane(r), tr("Roster Media"));
 }
 else
 {
  // make it, just don't make it visible
  makeMediaPane(r);
 }
 // for all "pane" elements in the programmer
 QDomNodeList paneList = base.elementsByTagName("pane");
 if (log->isDebugEnabled()) log->debug("will process "+QString::number(paneList.size())+" pane definitions");
 for (int i=0; i<paneList.size(); i++)
 {
  // load each pane
  //QString name = LocaleSelector.attribute(paneList.get(i), "name");
  QString name = paneList.at(i).toElement().attribute("name");
  if(name == "")
  {
   QDomElement nameElement = paneList.at(i).toElement().firstChildElement("name");
   if(!nameElement.isNull())
    name = nameElement.text();
  }
  newPane( name, paneList.at(i).toElement(), modelElem, false);  // dont force showing if empty
 }
}

/**
 * reset all CV values to defaults stored earlier.  This will in turn update
 * the variables
 */
/*protected*/ void PaneProgFrame::resetToDefaults()
{
 int n = defaultCvValues.count();
 for (int i=0; i<n; i++)
 {
  CvValue* cv = cvModel->getCvByNumber(defaultCvNumbers.at(i));
  if (cv == NULL) log->warn("Trying to set default in CV "+(defaultCvNumbers.at(i))
                                 +" but didn't find the CV object");
  else cv->setValue(defaultCvValues.at(i));
 }
 n = defaultIndexedCvValues.count();
 for (int i=0; i<n; i++)
 {
  CvValue* cv = iCvModel->getCvByRow(i);
  if (cv == NULL) log->warn("Trying to set default in indexed CV from row "+QString::number(i)
                                 +" but didn't find the CV object");
  else cv->setValue(defaultIndexedCvValues.at(i));
 }
}
/**
 * Save all CV values.  These stored values are used by
 * resetToDefaults
 */
/*protected*/ void PaneProgFrame::saveDefaults()
{
 int n = cvModel->rowCount(QModelIndex());
 defaultCvValues = QVector<int>(n);
 defaultCvNumbers = QVector<QString>(n);

 for (int i=0; i<n; i++)
 {
  CvValue* cv = cvModel->getCvByRow(i);
  defaultCvValues.replace(i, cv->getValue());
  defaultCvNumbers.replace(i, cv->number());
 }

 n = iCvModel->rowCount(QModelIndex());
 defaultIndexedCvValues = QVector<int>(n);

 for (int i=0; i<n; i++)
 {
  CvValue* cv = iCvModel->getCvByRow(i);
  defaultIndexedCvValues[i] = cv->getValue();
 }
}
/*protected*/ QWidget* PaneProgFrame::makeInfoPane(RosterEntry* r)
{
 // create the identification pane (not configured by programmer file now; maybe later?

 QWidget* body = new QFrame();
 QVBoxLayout* outer = new QVBoxLayout(body);
 _rPane = new RosterEntryPane(r);
 outer->addWidget(_rPane);
 QWidget* bottom = new QWidget();
 QHBoxLayout* bottomLayout = new QHBoxLayout();
 bottom->setLayout(bottomLayout);
 outer->addWidget(bottom);
 QPushButton* btnSave = new QPushButton(tr("Save to Roster"), this);
 bottomLayout->addWidget(btnSave);
 bottomLayout->setAlignment(btnSave,Qt::AlignHCenter);
 connect(btnSave, SIGNAL(clicked()), this, SLOT(on_actionSave_triggered()));
 QPushButton* btnReset = new QPushButton(tr("Reset to defaults"),this);
 bottomLayout->addWidget(btnReset);
 bottomLayout->setAlignment(btnReset,Qt::AlignHCenter);
 connect(btnReset, SIGNAL(clicked()), this, SLOT(resetToDefaults()));

 // arrange for the dcc address to be updated
// PropertyChangeListener dccNews = new java.beans.PropertyChangeListener() {
//                 public void propertyChange(java.beans.PropertyChangeEvent e) { updateDccAddress(); }
//             };
 primaryAddr = variableModel->findVar("Short Address");
 if (primaryAddr==NULL) log->debug("DCC Address monitor didnt find a Short Address variable");
 else
 {
  //primaryAddr.addPropertyChangeListener(dccNews);
  connect(primaryAddr->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(OnDccNews(PropertyChangeEvent*)));
 }
 extendAddr = variableModel->findVar("Long Address");
 if (extendAddr==NULL) log->debug("DCC Address monitor didnt find an Long Address variable");
 else
 {
  //extendAddr.addPropertyChangeListener(dccNews);
  connect(extendAddr->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(OnDccNews(PropertyChangeEvent*)));
 }
 addMode = (EnumVariableValue*)variableModel->findVar("Address Format");
 if (addMode==NULL) log->debug("DCC Address monitor didnt find an Address Format variable");
 else
 {
  //addMode->addPropertyChangeListener(dccNews);
  connect(addMode->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(OnDccNews(PropertyChangeEvent*)));
 }

 // get right address to start
 updateDccAddress();
 //pack();

 return body;
}
void PaneProgFrame::OnDccNews(PropertyChangeEvent* ) // SLOT
{
 updateDccAddress();
}

/*protected*/ QWidget* PaneProgFrame::makeFunctionLabelPane(RosterEntry* r)
{
    // create the identification pane (not configured by programmer file now; maybe later?
#if 0 // Using QDesigner page

    JPanel outer = new JPanel();
    outer.setLayout(new BoxLayout(outer, BoxLayout.Y_AXIS));
    JPanel body = new JPanel();
    body.setLayout(new BoxLayout(body, BoxLayout.Y_AXIS));
    JScrollPane scrollPane = new JScrollPane(body);

    // add tab description
    JLabel title = new JLabel(rbt.getString("UseThisTabCustomize"));
    title.setAlignmentX(JLabel.CENTER_ALIGNMENT);
    body.add(title);
    body.add(new JLabel(" "));	// some padding

    // add roster info
    _flPane = new FunctionLabelPane(r);
    //_flPane.setMaximumSize(_flPane.getPreferredSize());
    body.add(_flPane);

    // add the store button
    JButton store = new JButton(rbt.getString("ButtonSave"));
    store.setAlignmentX(JLabel.CENTER_ALIGNMENT);
    store.addActionListener( new ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent e) {
                storeFile();
            }
        });

    JPanel buttons = new JPanel();
    buttons.setLayout(new BoxLayout(buttons, BoxLayout.X_AXIS));

    buttons.add(store);

    body.add(buttons);
    outer.add(scrollPane);
    return outer;
#endif
    QFrame* frame = new QFrame();
    QVBoxLayout* frameLayout = new QVBoxLayout();
    frame->setLayout(frameLayout);
    _flPane = new FunctionLabelsPane(r);
    frameLayout->addWidget(_flPane);
    // add the store button
    QPushButton* store = new QPushButton(tr("Save to Roster"));
    frameLayout->addWidget(store);
    frameLayout->setAlignment(store, Qt::AlignHCenter);
//    store.addActionListener( new ActionListener() {
//            public void actionPerformed(java.awt.event.ActionEvent e) {
//                storeFile();
//            }
//        });
    connect(store, SIGNAL(clicked()), this, SLOT(on_btnStore_clicked()));
    return frame;
}

/*protected*/ QWidget* PaneProgFrame::makeMediaPane(RosterEntry* r)
{
    // create the identification pane (not configured by programmer file now; maybe later?
#if 0 // see MediaPane
    JPanel outer = new JPanel();
    outer.setLayout(new BoxLayout(outer, BoxLayout.Y_AXIS));
    JPanel body = new JPanel();
    body.setLayout(new BoxLayout(body, BoxLayout.Y_AXIS));
    JScrollPane scrollPane = new JScrollPane(body);

    // add tab description
    JLabel title = new JLabel(rbt.getString("UseThisTabMedia"));
    title.setAlignmentX(JLabel.CENTER_ALIGNMENT);
    body.add(title);
    body.add(new JLabel(" "));	// some padding

    // add roster info
    _rMPane = new RosterMediaPane(r);
    _rMPane.setMaximumSize(_rMPane.getPreferredSize());
    body.add(_rMPane);

    // add the store button
    JButton store = new JButton(rbt.getString("ButtonSave"));
    store.setAlignmentX(JLabel.CENTER_ALIGNMENT);
    store.addActionListener(new ActionListener() {

        public void actionPerformed(java.awt.event.ActionEvent e) {
            storeFile();
        }
    });

    JPanel buttons = new JPanel();
    buttons.setLayout(new BoxLayout(buttons, BoxLayout.X_AXIS));

    buttons.add(store);

    body.add(buttons);
    outer.add(scrollPane);
    return outer;
#endif
    QFrame* frame = new QFrame();
    QVBoxLayout* frameLayout = new QVBoxLayout();
    frame->setLayout(frameLayout);
    _rMPane = new RosterMediaPane(r);
    frameLayout->addWidget(_rMPane);
    // add the store button
    QPushButton* store = new QPushButton(tr("Save to Roster"));
    frameLayout->addWidget(store);
    frameLayout->setAlignment(store, Qt::AlignHCenter);
//    store..addActionListener(new ActionListener() {

//        public void actionPerformed(java.awt.event.ActionEvent e) {
//            storeFile();
//        }
//    });
    connect(store, SIGNAL(clicked()), this, SLOT(on_btnStore_clicked()));
    return frame;
}
void PaneProgFrame::on_btnStore_clicked()
{
 storeFile();
}

/*protected*/ void PaneProgFrame::installComponents()
{

 // create ShutDownTasks
 if (InstanceManager::shutDownManagerInstance()!=NULL)
 {
  //if (getModePane()!=NULL && decoderDirtyTask == NULL) decoderDirtyTask =
  if (decoderDirtyTask == NULL)
      decoderDirtyTask = new DecoderDirtyTask("DecoderPro Decoder Window Check",tr("Some changes have not been written to the decoder. They will be lost. Quit?"), "", this);
//  {
//   /*public*/ bool checkPromptNeeded() { return !checkDirtyDecoder(); }
//  };
  ((DefaultShutDownManager*)InstanceManager::shutDownManagerInstance())->_register(decoderDirtyTask);

  if (fileDirtyTask == NULL) fileDirtyTask = new FileDirtyTask("DecoderPro Decoder Window Check",
                                                              tr("Some changes have not been written to a configuration file. Quit?"),
                                                              tr("Save and Continue Quitting"), this);
//  {
//    /*public*/ bool checkPromptNeeded() {
//        return !checkDirtyFile();
//    }
//    /*public*/ bool doPrompt() {
//        bool result = storeFile(); // storeFile false if failed, abort shutdown
//        return result;
//    }
//  };
  ((DefaultShutDownManager*)InstanceManager::shutDownManagerInstance())->_register(fileDirtyTask);
 }

 // Create a menu bar
 QMenuBar* menuBar = new QMenuBar();
 setMenuBar(menuBar);

 // add a "File" menu
 QMenu* fileMenu = new QMenu(tr("File"));
 menuBar->addMenu(fileMenu);

 // add a "Factory Reset" menu
 if (!_opsMode)
 {
  resetMenu = new QMenu(tr("Reset"));
  menuBar->addMenu(resetMenu);
  resetMenu->addAction(new FactoryResetAction(tr("Factory Reset"), resetModel, this));
  if(resetModel->rowCount(QModelIndex()) > 0)
   resetMenu->setEnabled(true);
  else
   resetMenu->setEnabled(false);
 }
 // Add a save item
// fileMenu.add(new AbstractAction(tr("MenuSave"))
// {
//        public void actionPerformed(ActionEvent e) {
//            storeFile();
//        }
// });
 QAction* saveAct = new QAction(tr("Save"),this);
 fileMenu->addAction(saveAct);
 connect(saveAct, SIGNAL(triggered()), this, SLOT(storeFile()));
#if 1
 QMenu* printSubMenu = new QMenu(tr("Print"));
 printSubMenu->addAction(new PrintAction(tr("Print All"), this, false));
 printSubMenu->addAction(new PrintCvAction(tr("Print CVs..."), cvModel, this, false, _rosterEntry));
 fileMenu->addMenu(printSubMenu);

 QMenu* printPreviewSubMenu = new QMenu(tr("Print Preview"));
 printPreviewSubMenu->addAction(new PrintAction(tr("Preview All..."), this, true));
 printPreviewSubMenu->addAction(new PrintCvAction(tr("Preview CVs..."), cvModel, this, true, _rosterEntry));
 fileMenu->addMenu(printPreviewSubMenu);

 // add "Import" submenu; this is heirarchical because
 // some of the names are so long, and we expect more formats
 QMenu* importSubMenu = new QMenu(tr("Import"));
 fileMenu->addMenu(importSubMenu);
//    importSubMenu.add(new Pr1ImportAction(tr("PR1 file..."), cvModel, this));

 // add "Export" submenu; this is heirarchical because
 // some of the names are so long, and we expect more formats
 QMenu* exportSubMenu = new QMenu(tr("Export"));
 fileMenu->addMenu(exportSubMenu);
 exportSubMenu->addAction(new CsvExportAction(tr("CSV file..."), cvModel, this));
//    exportSubMenu.add(new Pr1ExportAction(tr("PR1DOS file..."), cvModel, this));
//    exportSubMenu.add(new Pr1WinExportAction(tr("PR1WIN file..."), cvModel, this));

    // to control size, we need to insert a single
    // JPanel, then have it laid out with BoxLayout
//    JPanel pane = new JPanel();

    // general GUI config
//    pane.setLayout(new BorderLayout());

    // configure GUI elements
#endif
 // set read buttons enabled state, tooltips
 enableReadButtons();

//    readChangesButton.addItemListener(l1 = new ItemListener() {
//        public void itemStateChanged (ItemEvent e) {
//            if (e.getStateChange() == ItemEvent.SELECTED) {
//                prepGlassPane(readChangesButton);
//                readChangesButton.setText(tr("ButtonStopReadChangesAll"));
//                readChanges();
//            } else {
//                if (_programmingPane != NULL) {
//                    _programmingPane.stopProgramming();
//                }
//                paneListIndex = paneList.size();
//                readChangesButton.setText(tr("ButtonReadChangesAllSheets"));
//            }
//        }
//    });
 connect(readChangesButton, SIGNAL(toggled(bool)), this, SLOT(on_btnReadChangesAllSheets_clicked()));
//    readAllButton.addItemListener(l3 = new ItemListener() {
//        public void itemStateChanged (ItemEvent e) {
//            if (e.getStateChange() == ItemEvent.SELECTED) {
//                prepGlassPane(readAllButton);
//                readAllButton.setText(tr("ButtonStopReadAll"));
//                readAll();
//            } else {
//                if (_programmingPane != NULL) {
//                    _programmingPane.stopProgramming();
//                }
//                paneListIndex = paneList.size();
//                readAllButton.setText(tr("ButtonReadAllSheets"));
//            }
//        }
//    });
    connect(readAllButton, SIGNAL(toggled(bool)), this, SLOT(on_btnReadAllSheets()));

    writeChangesButton->setToolTip(tr("Write highlighted values on all sheets to decoder"));
//    writeChangesButton.addItemListener(l2 = new ItemListener() {
//        public void itemStateChanged (ItemEvent e) {
//            if (e.getStateChange() == ItemEvent.SELECTED) {
//                prepGlassPane(writeChangesButton);
//                writeChangesButton.setText(tr("ButtonStopWriteChangesAll"));
//                writeChanges();
//            } else {
//                if (_programmingPane != NULL) {
//                    _programmingPane.stopProgramming();
//                }
//                paneListIndex = paneList.size();
//                writeChangesButton.setText(tr("ButtonWriteChangesAllSheets"));
//            }
//        }
//    });
    connect(writeChangesButton, SIGNAL(toggled(bool)), this, SLOT(on_btnWriteChangesAllSheets_Clicked()));
    writeAllButton->setToolTip(tr("Write all values on all sheets to decoder"));
//    writeAllButton.addItemListener(l4 = new ItemListener() {
//        public void itemStateChanged (ItemEvent e) {
//            if (e.getStateChange() == ItemEvent.SELECTED) {
//                prepGlassPane(writeAllButton);
//                writeAllButton.setText(tr("ButtonStopWriteAll"));
//                writeAll();
//            } else {
//                if (_programmingPane != NULL) {
//                    _programmingPane.stopProgramming();
//                }
//                paneListIndex = paneList.size();
//                writeAllButton.setText(tr("ButtonWriteAllSheets"));
//            }
//        }
//    });
    connect(writeAllButton, SIGNAL(toggled(bool)), this, SLOT(on_btnWriteAllSheets()));
    // most of the GUI is done from XML in readConfig() function
    // which configures the tabPane
    //pane.add(tabPane, BorderLayout.CENTER);

 // see if programming mode is available
 modePane = getModePane();
 if (modePane!=NULL)
 {
  // if so, configure programming part of GUI
  bottom = new QFrame();
  QVBoxLayout* vBottomLayout = new QVBoxLayout();
  bottom->setLayout(vBottomLayout);
//     QHBoxLayout* hBottomLayout = new QHBoxLayout();
//     vBottomLayout->addLayout(hBottomLayout);
     // add buttons
  QWidget* bottomButtons = new QWidget();
  QHBoxLayout* buttonLayout = new QHBoxLayout();
  bottomButtons->setLayout(buttonLayout);

  buttonLayout->addWidget(readChangesButton);
  buttonLayout->addWidget(writeChangesButton);
  buttonLayout->addWidget(readAllButton);
  buttonLayout->addWidget(writeAllButton);
  vBottomLayout->addWidget(bottomButtons);

     // add programming mode
     //bottom.add(new JSeparator(javax.swing.SwingConstants.HORIZONTAL));
  QFrame* line1 = new QFrame(ui->centralwidget);
  line1->setObjectName(QString::fromUtf8("line"));
  line1->setGeometry(QRect(10, 30, 571, 16));
  line1->setFrameShape(QFrame::HLine);
  line1->setFrameShadow(QFrame::Sunken);
  vBottomLayout->addWidget(line1);
  vBottomLayout->addWidget(modePane);
     // add programming status message
     //bottom.add(new JSeparator(javax.swing.SwingConstants.HORIZONTAL));
//        progStatus.setAlignmentX(JLabel.CENTER_ALIGNMENT);
//        bottom.add(progStatus);
  ui->centralwidget->layout()->addWidget(bottom/*, BorderLayout.SOUTH*/);
 }

//    // and put that pane into the JFrame
//    getContentPane().add(pane);

 // add help
 addHelp();
 setCursor(Qt::ArrowCursor);
}
/*public*/ QList<QWidget*> PaneProgFrame::getPaneList(){
    return paneList;
}

void PaneProgFrame::addHelp()
{
 addHelpMenu("package.jmri.jmrit.symbolicprog.tabbedframe.PaneProgFrame", true);
}

/*public*/ QSize PaneProgFrame::getPreferredSize()
{
 QDesktopWidget* screen = new QDesktopWidget();
//    int width = Math.min(super.getPreferredSize().width, screen.width);
 int width = qMin(QMainWindow::size().width(), screen->width());
//    int height = Math.min(super.getPreferredSize().height, screen.height);
 int height = qMin(QMainWindow::size().height(), screen->height());
 return QSize(width, height);
}

/*public*/ QSize PaneProgFrame::getMaximumSize() {
//    Dimension screen = getToolkit().getScreenSize();
    QDesktopWidget* screen = new QDesktopWidget();
 return QSize(screen->width(), screen->height()-35);

}

/**
 * Enable the read all and read changes button if possible.
 * This checks to make sure this is appropriate, given
 * the attached programmer's capability.
 */
void PaneProgFrame::enableReadButtons()
{
 readChangesButton->setToolTip(tr("Read highlighted values on all sheets from decoder. Warning: may take a long time!"));
 readAllButton->setToolTip(tr("Read highlighted values on all sheets from decoder. Warning: may take a long time!"));
 // check with CVTable programmer to see if read is possible
 if (cvModel!= NULL && cvModel->getProgrammer()!= NULL
         && !(((SlotManager*)cvModel->getProgrammer())->getCanRead()))
 {
  // can't read, disable the button
  readChangesButton->setEnabled(false);
  readAllButton->setEnabled(false);
  readChangesButton->setToolTip(tr("No Programmer"));
  readAllButton->setToolTip(tr("No Programmer"));
 }
 else
 {
  readChangesButton->setEnabled(true);
  readAllButton->setEnabled(true);
 }
}

void PaneProgFrame::updateDccAddress()
{
 bool longMode = false;
 if (log->isDebugEnabled())
  log->debug("updateDccAddress: short "+(primaryAddr==NULL?"<NULL>":((ShortAddrVariableValue*)primaryAddr)->getValueString())+
                  " long "+(extendAddr==NULL?"<NULL>":((LongAddrVariableValue*)extendAddr)->getValueString())+
                  " mode "+(addMode==NULL?"<NULL>":addMode->getValueString()));
 QString newAddr = NULL;
 if (addMode == NULL || extendAddr == NULL || ((EnumVariableValue*)addMode)->getValueString()!=("1"))
 {
  // short address mode
  longMode = false;
  if (primaryAddr != NULL && ((ShortAddrVariableValue*)primaryAddr)->getValueString()!=(""))
   newAddr = ((ShortAddrVariableValue*)primaryAddr)->getValueString();
  }
  else
 {
  // long address
  if (extendAddr != NULL && extendAddr->getValueString()!=(""))
   longMode = true;
  newAddr = ((LongAddrVariableValue*)extendAddr)->getValueString();
 }
 // update if needed
 if (newAddr!="")
 {
  // store DCC address, type
  _rPane->setDccAddress(newAddr);
  _rPane->setDccAddressLong(longMode);
 }
}
/*public*/ void PaneProgFrame::newPane(QString name, QDomElement pane, QDomElement modelElem, bool enableEmpty)
{
 if (log->isDebugEnabled()) log->debug(tr("newPane '")+name+tr("' with enableEmpty ")+(enableEmpty?"true":"false")+" getShowEmptyPanes() "+(getShowEmptyPanes()?"true":"false"));
 // create a panel to hold columns
 PaneProgPane* p = new PaneProgPane((PaneContainer*)this, name, pane, cvModel, iCvModel, variableModel, modelElem, _rosterEntry);
//    p->setOpaque(true);
 // how to handle the tab depends on whether it has contents and option setting
 if ( enableEmpty || (p->cvList->size()!=0) || (p->varList->size()!=0) || (p->indexedCvList->size()!=0))
 {
  ui->tabWidget->addTab(p, name);  // always add if not empty
 }
 else if (getShowEmptyPanes())
 {
  // here empty, but showing anyway as disabled
  int index = ui->tabWidget->addTab(p, name);
  //int index = tabPane.indexOfTab(name);
  ui->tabWidget->setTabEnabled(index, false);
  ui->tabWidget->setTabToolTip(index,  tr("Tab disabled because there are no options in this category"));
 }
 else
 {
  // here not showing tab at all
 }
 // and remember it for programming
 paneList.append(p);
}
/*public*/ BusyGlassPane* PaneProgFrame::getBusyGlassPane() { return glassPane; }

/**
 *
 */
/*public*/ void PaneProgFrame::prepGlassPane(JToggleButton* activeButton)
{
 QList<QRect> rectangles =  QList<QRect>();

 if (glassPane != NULL)
 {
  glassPane->dispose();
  delete glassPane;
 }
 activeComponents.clear();
 activeComponents.append(activeButton);
 if (activeButton == readChangesButton || activeButton == readAllButton ||
        activeButton == writeChangesButton || activeButton == writeAllButton)
 {
  if (activeButton == readChangesButton)
  {
   for (int i = 0; i < paneList.size(); i++)
   {
    activeComponents.append(((PaneProgPane*) paneList.at(i))->readChangesButton);
   }
  }
  else if (activeButton == readAllButton)
  {
   for (int i = 0; i < paneList.size(); i++)
   {
    activeComponents.append(((PaneProgPane*) paneList.at(i))->readAllButton);
   }
  }
  else if (activeButton == writeChangesButton)
  {
   for (int i = 0; i < paneList.size(); i++)
   {
     activeComponents.append(((PaneProgPane*) paneList.at(i))->writeChangesButton);
   }
  }
  else if (activeButton == writeAllButton)
  {
   for (int i = 0; i < paneList.size(); i++)
   {
     activeComponents.append(((PaneProgPane*) paneList.at(i))->writeAllButton);
   }
  }
  for (int i = 0; i < ui->tabWidget->count(); i++)
  {
//            rectangles.append(ui->tabWidget.getUI().getTabBounds(tabPane,i));
   rectangles.append(ui->tabWidget->widget(i)->rect());
  }
 }
 glassPane = new BusyGlassPane(activeComponents, rectangles, this->getContentPane(), this);
// this->setGlassPane(glassPane);
}

/*public*/ void PaneProgFrame::paneFinished()
{
 if (!isBusy())
 {
  if (glassPane != NULL)
  {
   glassPane->setVisible(false);
   glassPane->dispose();
   delete glassPane;
   glassPane = NULL;
  }
  setCursor(Qt::ArrowCursor);
  enableButtons(true);
 }
}
/**
 * Enable the read/write buttons.
 * <p>
 * In addition, if a programming mode pane is
 * present, it's "set" button is enabled.
 *
 * @param stat Are reads possible? If false, so not enable
 * the read buttons.
 */
/*public*/ void PaneProgFrame::enableButtons(bool stat)
{
 if (stat)
 {
  enableReadButtons();
 }
 else
 {
  readChangesButton->setEnabled(false);
  readAllButton->setEnabled(false);
 }
 writeChangesButton->setEnabled(stat);
 writeAllButton->setEnabled(stat);
//    if (modePane != NULL) {
//        modePane.setEnabled(stat);
//    }
 //ui->cbProgrammerMode->setEnabled(stat);
}


/*public*/ bool PaneProgFrame::isBusy() { return _busy; }
/*private*/ void PaneProgFrame::setBusy(bool stat)
{
 _busy = stat;
 for (int i = 0; i < paneList.size(); i++)
 {
  if (stat)
  {
   ((PaneProgPane*)paneList.at(i))->enableButtons(false);
  }
  else
  {
   ((PaneProgPane*)paneList.at(i))->enableButtons(true);
  }
 }
 if (!stat)
 {
  paneFinished();
 }
}

/**
 * invoked by "Read Changes" button, this sets in motion a
 * continuing sequence of "read changes" operations on the
 * panes. Each invocation of this method reads one pane; completion
 * of that request will cause it to happen again, reading the next pane, until
 * there's nothing left to read.
 * <P>
 * @return true if a read has been started, false if the operation is complete.
 */
/*public*/ bool PaneProgFrame::readChanges()
{
 if (log->isDebugEnabled()) log->debug("readChanges starts");
 justChanges = true;
 for (int i = 0; i < paneList.size(); i++)
 {
  ((PaneProgPane*)paneList.at(i))->setToRead(justChanges, true);
 }
 setBusy(true);
 enableButtons(false);
 readChangesButton->setEnabled(true);
 glassPane->setVisible(true);
 paneListIndex = 0;
 // start operation
 return doRead();
}

/**
 * invoked by "Read All" button, this sets in motion a
 * continuing sequence of "read all" operations on the
 * panes. Each invocation of this method reads one pane; completion
 * of that request will cause it to happen again, reading the next pane, until
 * there's nothing left to read.
 * <P>
 * @return true if a read has been started, false if the operation is complete.
 */
/*public*/ bool PaneProgFrame::readAll()
{
 if (log->isDebugEnabled()) log->debug("readAll starts");
 justChanges = false;
 for (int i = 0; i < paneList.size(); i++)
 {
  ((PaneProgPane*)paneList.at(i))->setToRead(justChanges, true);
 }
 setBusy(true);
 enableButtons(false);
 readAllButton->setEnabled(true);
 glassPane->setVisible(true);
 paneListIndex = 0;
 // start operation
 return doRead();
}

bool PaneProgFrame::doRead()
{
 _read = true;
 while (paneListIndex < paneList.size())
 {
  if (log->isDebugEnabled()) log->debug("doRead on "+QString::number(paneListIndex));
  _programmingPane = (PaneProgPane*)paneList.at(paneListIndex);
  if(qobject_cast<PaneProgPane*>(_programmingPane)!=NULL)
  {
   // some programming operations are instant, so need to have listener registered at readPaneAll
   _programmingPane->addPropertyChangeListener((PropertyChangeListener*) this);
   connect(_programmingPane, SIGNAL(notifyPropertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   bool running;
   if (justChanges)
    running = ((PaneProgPane*)_programmingPane)->readPaneChanges();
   else
    running = ((PaneProgPane*)_programmingPane)->readPaneAll();

   paneListIndex++;

   if (running)
   {
    // operation in progress, stop loop until called back
    if (log->isDebugEnabled()) log->debug("doRead expecting callback from readPane "+QString::number(paneListIndex));
     return true;
   }
   else
   {
//    ((PaneProgPane*)_programmingPane)->removePropertyChangeListener((PropertyChangeListener*)this);
   }
  }
 }
 // nothing to program, end politely
 _programmingPane = NULL;
 enableButtons(true);
 setBusy(false);
 readChangesButton->setSelected(false);
 readAllButton->setSelected(false);
 if (log->isDebugEnabled()) log->debug("doRead found nothing to do");
 return false;
}

/**
 * invoked by "Write All" button, this sets in motion a
 * continuing sequence of "write all" operations on each pane.
 * Each invocation of this method writes one pane; completion
 * of that request will cause it to happen again, writing the next pane, until
 * there's nothing left to write.
 * <P>
 * @return true if a write has been started, false if the operation is complete.
 */
/*public*/ bool PaneProgFrame::writeAll()
{

    if (log->isDebugEnabled()) log->debug("writeAll starts");
    justChanges = false;
    for (int i = 0; i < paneList.size(); i++) {
        ((PaneProgPane*)paneList.at(i))->setToWrite(justChanges, true);
    }
    setBusy(true);
    enableButtons(false);
    writeAllButton->setEnabled(true);
    glassPane->setVisible(true);
    paneListIndex = 0;
    return doWrite();
}

/**
 * invoked by "Write Changes" button, this sets in motion a
 * continuing sequence of "write changes" operations on each pane.
 * Each invocation of this method writes one pane; completion
 * of that request will cause it to happen again, writing the next pane, until
 * there's nothing left to write.
 * <P>
 * @return true if a write has been started, false if the operation is complete.
 */
/*public*/ bool PaneProgFrame::writeChanges()
{

    if (log->isDebugEnabled()) log->debug("writeChanges starts");
    justChanges = true;
    for (int i = 0; i < paneList.size(); i++) {
        ((PaneProgPane*)paneList.at(i))->setToWrite(justChanges, true);
    }
    setBusy(true);
    enableButtons(false);
    writeChangesButton->setEnabled(true);
    glassPane->setVisible(true);
    paneListIndex = 0;
    return doWrite();
}

bool PaneProgFrame::doWrite()
{
 _read = false;
 while (paneListIndex < paneList.size())
 {
  if (log->isDebugEnabled()) log->debug("doWrite starts on "+QString::number(paneListIndex));
  _programmingPane = (PaneProgPane*)paneList.at(paneListIndex);
  // some programming operations are instant, so need to have listener registered at readPane
  _programmingPane->addPropertyChangeListener((PropertyChangeListener*)this);
  connect(_programmingPane, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  bool running;
  if (justChanges)
   running = _programmingPane->writePaneChanges();
  else
   running = _programmingPane->writePaneAll();

   paneListIndex++;

   if (running)
   {
    // operation in progress, stop loop until called back
    if (log->isDebugEnabled()) log->debug("doWrite expecting callback from writePane "+QString::number(paneListIndex));
     return true;
   }
   else
    _programmingPane->removePropertyChangeListener((PropertyChangeListener*)this);
   disconnect(_programmingPane, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 // nothing to program, end politely
 _programmingPane = NULL;
 enableButtons(true);
 setBusy(false);
 writeChangesButton->setSelected(false);
 writeAllButton->setSelected(false);
 if (log->isDebugEnabled()) log->debug("doWrite found nothing to do");
 return false;
}

/*public*/ void PaneProgFrame::printPanes(/*final*/ bool preview)
{

 PrintRosterEntry* pre = new PrintRosterEntry(_rosterEntry, paneList, _flPane, _rMPane, this);
 pre->printPanes(preview);
}


/**
 * get notification of a variable property change in the pane, specifically "busy" going to
 * false at the end of a programming operation
 * @param e Event, used to find source
 */
/*public*/ void PaneProgFrame::propertyChange(PropertyChangeEvent* e)
{
 // check for the right event
 if (_programmingPane == NULL)
 {
  log->warn("unexpected propertyChange: "+e->getPropertyName());
  return;
 }
 else if (log->isDebugEnabled()) log->debug("property changed: "+e->getPropertyName()
                                               +" new value: "+e->getNewValue().toString());
 log->debug(tr("check valid: ")+(e->getSource() == _programmingPane)+" "+(e->getPropertyName()!=("Busy"))+" "+((e->getNewValue().toBool())==(false)));
 if (e->getSource() == _programmingPane &&
        e->getPropertyName()==("Busy") &&
        (e->getNewValue().toBool())==(false) )
 {

  if (log->isDebugEnabled()) log->debug("end of a programming pane operation, remove");
  // remove existing listener
//  _programmingPane->removePropertyChangeListener((PropertyChangeListener*)this);
  _programmingPane = NULL;
  // restart the operation
  if (_read && readChangesButton->isSelected())
  {
   if (log->isDebugEnabled()) log->debug("restart readChanges");
    doRead();
  }
  else if (_read && readAllButton->isSelected())
  {
   if (log->isDebugEnabled()) log->debug("restart readAll");
    doRead();
  }
  else if (writeChangesButton->isSelected())
  {
   if (log->isDebugEnabled()) log->debug("restart writeChanges");
    doWrite();
  }
  else if (writeAllButton->isSelected())
  {
   if (log->isDebugEnabled()) log->debug("restart writeAll");
    doWrite();
  }
  else
  {
   if (log->isDebugEnabled()) log->debug("read/write end because button is lifted");
    setBusy(false);
  }
 }
}

/**
 * Store the locomotive's information in the roster (and a RosterEntry file).
 * @return false if store failed
 */
/*public*/ bool PaneProgFrame::storeFile()
{
 log->debug("storeFile starts");

 if (_rPane->checkDuplicate())
 {
  //JOptionPane.showMessageDialog(this, rbt.getString("ErrorDuplicateID"));
  QMessageBox::critical(0, tr("Error"), tr("This ID is a duplicate, please change it"));
  return false;
 }

 // reload the RosterEntry
 updateDccAddress();
 _rPane->update(_rosterEntry);
//    _flPane.update(_rosterEntry);
//    _rMPane.update(_rosterEntry);

 // id has to be set!
 if (_rosterEntry->getId()==("") || _rosterEntry->getId()==(tr("<new loco>")))
 {
  log->debug("storeFile without a filename; issued dialog");
 //JOptionPane.showMessageDialog(this, tr("PromptFillInID"));
  QMessageBox::critical(0, tr("Error"), tr("Please fill in the ID field first"));
  return false;
 }

 // if there isn't a filename, store using the id
 _rosterEntry->ensureFilenameExists();
 QString filename = _rosterEntry->getFileName();

 // create the RosterEntry to its file
 _rosterEntry->writeFile(cvModel, iCvModel, variableModel );

 // mark this as a success
 variableModel->setFileDirty(false);

 // and store an updated roster file
 FileUtil::createDirectory(FileUtil::getUserFilesPath());
 Roster::writeRosterFile();

 // save date changed, update
 _rPane->updateGUI(_rosterEntry);

 // show OK status
 progStatus->setText(tr("Roster file {%1} saved OK").arg(filename));
 return true;
}

/**
 * local dispose, which also invokes parent. Note that
 * we remove the components (removeAll) before taking those
 * apart.
 */
/*public*/ void PaneProgFrame::dispose()
{
 if (log->isDebugEnabled()) log->debug("dispose local");

 // remove listeners (not much of a point, though)
//    readChangesButton.removeItemListener(l1);
//    writeChangesButton.removeItemListener(l2);
//    readAllButton.removeItemListener(l3);
//    writeAllButton.removeItemListener(l4);
// if (_programmingPane != NULL) _programmingPane->removePropertyChangeListener((PropertyChangeListener*)this);

 // dispose the list of panes
 for (int i=0; i<paneList.size(); i++)
 {
  PaneProgPane* p = (PaneProgPane*) paneList.at(i);
  p->dispose();
 }
 paneList.clear();

 // dispose of things we owned, in order of dependence
 //_rPane->dispose();
// _flPane.dispose();
//    _rMPane.dispose();
 variableModel->dispose();
 cvModel->dispose();
 iCvModel->dispose();
 if(_rosterEntry!=NULL)
 {
  _rosterEntry->setOpen(false);
 }

 // remove references to everything we remember
 progStatus = NULL;
 cvModel = NULL;
 iCvModel = NULL;
 variableModel = NULL;
 _rosterEntry = NULL;
 _rPane = NULL;
//    _flPane = NULL;
//    _rMPane = NULL;

 paneList.clear();
 //paneList = NULL;
 _programmingPane = NULL;

//    tabPane = NULL;
//    readChangesButton = NULL;
//    writeChangesButton = NULL;
//    readAllButton = NULL;
//    writeAllButton = NULL;

 if (log->isDebugEnabled()) log->debug("dispose superclass");
//    removeAll();
//    super.dispose();
}

/**
 * Option to control appearance of empty panes
 */
/*public*/ /*static*/ void PaneProgFrame::setShowEmptyPanes(bool yes) {
    showEmptyPanes = yes;
}
/*public*/ /*static*/ bool PaneProgFrame::getShowEmptyPanes() {
    return showEmptyPanes;
}

/*public*/ RosterEntry* PaneProgFrame::getRosterEntry() { return _rosterEntry; }
void PaneProgFrame::on_btnReadChangesAllSheets_clicked()
{
 //readChanges();
 //if (e.getStateChange() == ItemEvent.SELECTED)
 if(readChangesButton->isSelected())
 {
  prepGlassPane(readChangesButton);
  readChangesButton->setText(tr("Stop Read changes, all sheets"));
  readChanges();
 }
 else
 {
  if (_programmingPane != NULL)
  {
   _programmingPane->stopProgramming();
  }
  paneListIndex = paneList.size();
  readChangesButton->setText(tr("Read changes on all sheets"));
 }
}

void PaneProgFrame::on_btnWriteChangesAllSheets_Clicked()
{
 //writeChanges();
 //if (e.getStateChange() == ItemEvent.SELECTED)
 if(writeChangesButton->isSelected())
 {
  prepGlassPane(writeChangesButton);
  writeChangesButton->setText(tr("Stop Write changes, all sheets"));
  writeChanges();
} else {
  if (_programmingPane != NULL)
  {
   _programmingPane->stopProgramming();
  }
  paneListIndex = paneList.size();
  writeChangesButton->setText(tr("Write changes on all sheets"));
 }
}
void PaneProgFrame::on_btnReadAllSheets()
{
 //readAll();
 //if (e.getStateChange() == ItemEvent.SELECTED)
 if(readAllButton->isSelected())
 {
  prepGlassPane(readAllButton);
  readAllButton->setText(tr("Stop Read all sheets"));
  readAll();
 }
 else
 {
  if (_programmingPane != NULL)
  {
   _programmingPane->stopProgramming();
  }
  paneListIndex = paneList.size();
  readAllButton->setText(tr("Read all sheets"));
 }
}

void PaneProgFrame::on_btnWriteAllSheets()
{
 //writeAll();
 //if (e.getStateChange() == ItemEvent.SELECTED)
 if(writeAllButton->isSelected())
 {
    prepGlassPane(writeAllButton);
    writeAllButton->setText(tr("Stop Write all sheets"));
    writeAll();
 }
 else
 {
  if (_programmingPane != NULL)
  {
   _programmingPane->stopProgramming();
  }
  paneListIndex = paneList.size();
  writeAllButton->setText(tr("Write all sheets"));
 }
}
void PaneProgFrame::on_actionSave_triggered()
{
 storeFile();
}

void PaneProgFrame::on_tabWidget_currentChanged(int i)
{
 if(ui->tabWidget->tabText(i) == tr("Roster Entry") ||
            ui->tabWidget->tabText(i) == tr("Function Labels") ||
            ui->tabWidget->tabText(i) == tr("Roster Media") || mProgrammer == NULL)
 {
  if(bottom!= NULL) bottom->setHidden(true);
 }
 else
 {
  if(bottom!= NULL)bottom->setVisible(true);
 }
}
#if 0
/**
 * Returns the <code>contentPane</code> object for this frame.
 * @return the <code>contentPane</code> property
 *
 * @see #setContentPane
 * @see RootPaneContainer#getContentPane
 */
/*public*/ QWidget* getContentPane() {
    return getRootPane().getContentPane();
}
/**
 * Sets the <code>glassPane</code> property.
 * This method is called by the constructor.
 * @param glassPane the <code>glassPane</code> object for this frame
 *
 * @see #getGlassPane
 * @see RootPaneContainer#setGlassPane
 *
 * @beaninfo
 *     hidden: true
 *     description: A transparent pane used for menu rendering.
 */
/*public*/ void setGlassPane(QWidget* glassPane) {
    getRootPane().setGlassPane(glassPane);
}
/**
 * Returns the <code>rootPane</code> object for this frame.
 * @return the <code>rootPane</code> property
 *
 * @see #setRootPane
 * @see RootPaneContainer#getRootPane
 */
/*public*/ JRootPane getRootPane() {
    return rootPane;
}
#endif
void PaneProgFrame::setProgrammingGui(QWidget* pane)
{
 // see if programming mode is available
 modePane = getModePane();
 if (modePane!=NULL)
 {
  // if so, configure programming part of GUI
  QWidget* bottom = new QWidget();
  bottom->setContentsMargins(0,0,0,0);
   QBoxLayout* bottomLayout;
   bottom->setLayout(bottomLayout = new QVBoxLayout);//(bottom, BoxLayout.Y_AXIS));
   // add buttons
   //QWidget* bottomButtons = new QWidget();
   QHBoxLayout* bottomButtonsLayout = new QHBoxLayout;
   //bottomButtons->setLayout(bottomButtonsLayout = new QHBoxLayout);//(bottomButtons, BoxLayout.X_AXIS));

   bottomButtonsLayout->addWidget(readChangesButton);
   bottomButtonsLayout->addWidget(writeChangesButton);
   bottomButtonsLayout->addWidget(readAllButton);
   bottomButtonsLayout->addWidget(writeAllButton);
   bottomLayout->addLayout(bottomButtonsLayout);

   // add programming mode
   bottomLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
   //QWidget* temp = new QWidget();
   //temp->setLayout(new QVBoxLayout);
   //((QVBoxLayout*)temp->layout())->addWidget(modePane);
   bottomLayout->addWidget(modePane);

   // add programming status message
   bottomLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
   progStatus->setAlignment(Qt::AlignCenter);
  bottomLayout->addWidget(progStatus);
  ((QVBoxLayout*)pane->layout())->addWidget(bottom,0, Qt::AlignBottom);
 }
}
/**
 * Option to control appearance of CV numbers in tool tips
 */
/*public*/ /*static*/ void PaneProgFrame::setShowCvNumbers(bool yes) {
    showCvNumbers = yes;
}
/*static*/ bool PaneProgFrame::showCvNumbers = false;
/*public*/ /*static*/ bool PaneProgFrame::getShowCvNumbers() {
    return showCvNumbers;
}

/*public*/ /*static*/ void PaneProgFrame::setCanCacheDefault(bool yes) {
        if (InstanceManager::getNullableDefault("ProgrammerConfigManager") != NULL) {
            ((ProgrammerConfigManager*)InstanceManager::getDefault("ProgrammerConfigManager"))->setCanCacheDefault(yes);
        }
    }

    /*public*/ /*static*/ bool PaneProgFrame::getCanCacheDefault() {
        return (InstanceManager::getNullableDefault("ProgrammerConfigManager") == NULL)
                ? true
                : ((ProgrammerConfigManager*)InstanceManager::getDefault("ProgrammerConfigManager"))->isCanCacheDefault();
    }

    /*public*/ /*static*/ void PaneProgFrame::setDoConfirmRead(bool yes) {
        if (InstanceManager::getNullableDefault("ProgrammerConfigManager") != NULL) {
            ((ProgrammerConfigManager*)InstanceManager::getDefault("ProgrammerConfigManager"))->setDoConfirmRead(yes);
        }
    }

    /*public*/ /*static*/ bool PaneProgFrame::getDoConfirmRead() {
        return (InstanceManager::getNullableDefault("ProgrammerConfigManager") == NULL)
                ? true
                : ((ProgrammerConfigManager*)InstanceManager::getDefault("ProgrammerConfigManager"))->isDoConfirmRead();
    }
