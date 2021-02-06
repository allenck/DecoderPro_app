#include "combinedlocoselpane.h"
#include "instancemanager.h"
#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>
#include "globalrosterentrycombobox.h"
#include "decoderindexfile.h"
#include "jtogglebutton.h"
#include "QPushButton"
#include "identifyloco.h"
#include "progdefault.h"
#include "rosterentry.h"
#include "decoderfile.h"
#include "defaultprogrammermanager.h"

CombinedLocoSelPane::CombinedLocoSelPane(QWidget *parent) :
    LocoSelPane(parent)
{
 common();
 init();
}
/**
 * Provide GUI controls to select a known loco and/or new decoder.
 * <P>
 * When the "open programmer" button is pushed, i.e. the user is ready to
 * continue, the startProgrammer method is invoked.  This should be
 * overridden (e.g. in a local anonymous class) to create the programmer frame
 * you're interested in.
 *
 * <P>To overide this class to use a different decoder-selection GUI,
 * replace members:
 * <UL>
 * <LI>layoutDecoderSelection
 * <LI>updateForDecoderTypeID
 * <LI>updateForDecoderMfgID
 * <LI>updateForDecoderNotID
 * <LI>resetDecoder
 * <LI>isDecoderSelected
 * <LI>selectedDecoderName
 * </UL>
 *
 * <P>
 * On MacOS Classic, this class was causing a problem with multiple
 * initialization of the programmer file default.  See
 * {@link ProgDefault} and
 * {@link jmri.jmrit.symbolicprog.configurexml.ProgrammerConfigPaneXml}
 * for further information.
 *
 * @author			Bob Jacobsen   Copyright (C) 2001, 2002
 * @version			$Revision: 21951 $
 */
// /*public*/ class CombinedLocoSelPane extends LocoSelPane implements PropertyChangeListener {

//    static final java.util.ResourceBundle rbt = jmri.jmrit.symbolicprog.SymbolicProgBundle.bundle();

/*public*/ CombinedLocoSelPane::CombinedLocoSelPane(QLabel* s, ProgModeSelector* selector, QWidget *parent) : LocoSelPane(parent)
{
 common();
 _statusLabel = s;
 this-> selector = selector;
 init();
}

//    /*public*/ CombinedLocoSelPane() {
//        init();
//    }

/**
 * Create the panel used to select the decoder
 *
 * @return a QWidget* for handling the decoder-selection GUI
 */
/*protected*/ QWidget* CombinedLocoSelPane::layoutDecoderSelection()
{
 QWidget* pane1a = new QWidget();
 pane1a->setObjectName("pane1a");
//    pane1a.setLayout(new BoxLayout(pane1a, BoxLayout.X_AXIS));
 QHBoxLayout* pane1aLayout = new  QHBoxLayout;
 pane1a->setLayout(pane1aLayout);
 pane1aLayout->addWidget(new QLabel(tr("Decoder installed: ")),0, Qt::AlignCenter);
 decoderBox = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingComboBox(NULL, NULL, NULL, NULL, NULL, NULL);
 decoderBox->addItem("<from locomotive settings>");
 decoderBox->setCurrentIndex(0);
//    decoderBox.addActionListener(new ActionListener() {

//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            if (decoderBox.getSelectedIndex() != 0) {
//                // reset and disable loco selection
//                locoBox.setSelectedIndex(0);
//                go2.setEnabled(true);
//                go2.setRequestFocusEnabled(true);
//                go2.requestFocus();
//                go2->setToolTip(tr("CLICK TO OPEN THE PROGRAMMER"));
//            } else {
//                go2.setEnabled(false);
//                go2->setToolTip(tr("SELECT A LOCOMOTIVE OR DECODER TO ENABLE"));
//            }
//        }
//    });
 connect(decoderBox, SIGNAL(currentIndexChanged(int)), this, SLOT(On_decoderBoxIndexChanged(int)));
 pane1aLayout->addWidget(decoderBox);
 iddecoder = addDecoderIdentButton();
 if (iddecoder != NULL)
 {
  pane1aLayout->addWidget(iddecoder);
 }
 //pane1a.setAlignmentX(JLabel.RIGHT_ALIGNMENT);
 return pane1a;
}

JToggleButton* CombinedLocoSelPane::addDecoderIdentButton()
{
 JToggleButton* iddecoder = new JToggleButton(tr("Read type from decoder"));
 iddecoder->setToolTip(tr("Read the decoders mfg and version, then attempt to select its type"));
 if (InstanceManager::getNullableDefault("GlobalProgrammerManager") != NULL)
 {
  Programmer* p = ((DefaultProgrammerManager*) InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer();
  if (p != NULL && !p->getCanRead())

  {
   // can't read, disable the button
   iddecoder->setEnabled(false);
   iddecoder->setToolTip(tr("Button disabled because configured command station can't read CVs"));
  }
 }
// iddecoder.addActionListener( new ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                    startIdentifyDecoder();
//            }
//    });
 connect(iddecoder, SIGNAL(clicked()), this, SLOT(startIdentifyDecoder()));
 return iddecoder;
}

void CombinedLocoSelPane::On_decoderBoxIndexChanged(int)
{
 if (decoderBox->currentIndex() != 0)
 {
  // reset and disable loco selection
  locoBox->setCurrentIndex(0);
  go2->setEnabled(true);
//  go2->setRequestFocusEnabled(true);
//  go2->requestFocus();
  go2->setFocus();
  go2->setToolTip(tr("Click to open the programmer"));
 }
 else
 {
  go2->setEnabled(false);
  go2->setToolTip(tr("Select a locomotive or decoder to enable"));
 }
}
/**
 *  Set the decoder GUI back to having no selection
 */
void CombinedLocoSelPane::setDecoderSelectionFromLoco(QString loco) {
    decoderBox->setCurrentIndex(0);
}

/**
 * Has the user selected a decoder type, either manually or
 * via a successful event?
 * @return true if a decoder type is selected
 */
bool CombinedLocoSelPane::isDecoderSelected() {
    return decoderBox->currentIndex()!=0;
}

/**
 * Convert the decoder selection UI result into a name.
 * @return The selected decoder type name, or NULL if none selected.
 */
/*protected*/ QString CombinedLocoSelPane::selectedDecoderType() {
    if (!isDecoderSelected()) return NULL;
    else return decoderBox->currentText();
}

/**
 * Create the panel used to select an existing entry
 * @return a QWidget* for handling the entry-selection GUI
 */
/*protected*/ QWidget* CombinedLocoSelPane::layoutRosterSelection()
{
 QWidget* pane2a = new QWidget();
 QHBoxLayout* pane2aLayout;
 pane2a->setLayout(pane2aLayout = new QHBoxLayout) ;//(pane2a, BoxLayout.X_AXIS));
 pane2aLayout->addWidget(new QLabel(tr("Use locomotive settings for:")));
 //locoBox->setNonSelectedItem(tr("<none - new loco>"));
 locoBox->setCurrentIndex(0);
 //Roster::getDefault()->addPropertyChangeListener(this);
 connect(Roster::getDefault(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 pane2aLayout->addWidget(locoBox);
 locoBox->setVisible(true);
// locoBox.addPropertyChangeListener(RosterEntrySelector::SELECTED_ROSTER_ENTRIES, new PropertyChangeListener() {

//        @Override
//        /*public*/ void propertyChange(PropertyChangeEvent pce) {
//            if (locoBox.getSelectedRosterEntries().length != 0) {
//                // reset and disable decoder selection
//                setDecoderSelectionFromLoco(locoBox.getSelectedRosterEntries()[0].titleString());
//                go2.setEnabled(true);
//                go2.setRequestFocusEnabled(true);
//                go2.requestFocus();
//                go2->setToolTip(tr("CLICK TO OPEN THE PROGRAMMER"));
//            } else {
//                go2.setEnabled(false);
//                go2->setToolTip(tr("SELECT A LOCOMOTIVE OR DECODER TO ENABLE"));
//            }
//        }
//    });
 connect(locoBox, SIGNAL(currentIndexChanged(int)), this, SLOT(On_locoBoxPropertyChange()));
 idloco = new JToggleButton(tr("Ident"));
 idloco->setToolTip(tr("Read the locomotive's address and attempt to select the right settings"));
 if (InstanceManager::getNullableDefault("GlobalProgrammerManager") != nullptr)
 {
  Programmer* p = (Programmer*)((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer();
  if (p != nullptr && !p->getCanRead())
  {
      // can't read, disable the button
      idloco->setEnabled(false);
      idloco->setToolTip(tr("Button disabled because configured command station can't read CVs"));
  }
 }
//    idloco.addActionListener( new ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                if (log->isDebugEnabled()) log->debug("Identify locomotive pressed");
//                startIdentifyLoco();
//            }
//        });
 connect(idloco, SIGNAL(clicked()), this, SLOT(On_idloco_clicked()));
 pane2aLayout->addWidget(idloco);
// pane2a.setAlignmentX(JLabel.RIGHT_ALIGNMENT);
 return pane2a;
}
void CombinedLocoSelPane::On_locoBoxPropertyChange()
{
 if (locoBox->getSelectedRosterEntries()->length() != 0)
 {
  // reset and disable decoder selection
  setDecoderSelectionFromLoco(locoBox->getSelectedRosterEntries()->at(0)->titleString());
  go2->setEnabled(true);
//        go2->setRequestFocusEnabled(true);
//        go2->requestFocus();
  go2->setFocus();
  go2->setToolTip(tr("Click to open the programmer"));
 }
 else
 {
  go2->setEnabled(false);
  go2->setToolTip(tr("Select a locomotive or decoder to enable"));
 }
}
void CombinedLocoSelPane::On_idloco_clicked()
{
 if (log->isDebugEnabled()) log->debug("Identify locomotive pressed");
 startIdentifyDecoder();
}
/**
 * Initialize the GUI
 */
/*protected*/ void CombinedLocoSelPane::common()
{
 log = new Logger("CombineLocoSelPane");
 decoderBox = NULL;       // private because children will override this
 locoBox = new GlobalRosterEntryComboBox();
 locoBox->setVisible(false);
 programmerBox = NULL;
 _statusLabel = NULL;
}
/*public*/ void CombinedLocoSelPane::init()
{
 //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
 //setLayout(new BorderLayout());
 QVBoxLayout* thisLayout = new QVBoxLayout;
 setLayout(thisLayout);
 setMinimumHeight(100);

 QWidget* pane2a = layoutRosterSelection();
 if (pane2a != NULL) thisLayout->addWidget(pane2a,0, Qt::AlignTop);

 thisLayout->addWidget(layoutDecoderSelection(), 0, Qt::AlignCenter);

 thisLayout->addWidget(createProgrammerSelection(),0, Qt::AlignBottom);
 //setBorder(new EmptyBorder(6,6,6,6));
}

/*protected*/ QWidget* CombinedLocoSelPane::createProgrammerSelection()
{
 QWidget* pane3a = new QWidget();
 QVBoxLayout* pane3aLayout;
 pane3a->setLayout(pane3aLayout = new QVBoxLayout);//(pane3a, BoxLayout.Y_AXIS));
 // create the programmer box
 QWidget* progFormat = new QWidget();
 QHBoxLayout* progFormatLayout;
 progFormat->setLayout(progFormatLayout = new QHBoxLayout);//(progFormat, BoxLayout.X_AXIS));
 progFormatLayout->addWidget(new QLabel(tr("Programmer format:")));
 //progFormat.setAlignmentX(JLabel.RIGHT_ALIGNMENT);

 programmerBox = new QComboBox();
 programmerBox->addItems(ProgDefault::findListOfProgFiles());
 programmerBox->setCurrentIndex(0);
 if (ProgDefault::getDefaultProgFile()!=NULL)
  programmerBox->setCurrentIndex(programmerBox->findText(ProgDefault::getDefaultProgFile()));
 progFormatLayout->addWidget(programmerBox);

 go2 = new QPushButton(tr("Open Programmer"));
//    go2.addActionListener( new ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                if (log->isDebugEnabled()) log->debug("Open programmer pressed");
//                openButton();
//            }
//        });
 connect(go2, SIGNAL(clicked()), this, SLOT(On_go2_clicked()));
 //go2.setAlignmentX(JLabel.RIGHT_ALIGNMENT);
 go2->setEnabled(false);
 go2->setToolTip(tr("Select a locomotive or decoder to enable"));
 pane3aLayout->addWidget(progFormat);
 pane3aLayout->addWidget(go2, 0, Qt::AlignRight);
 return pane3a;
}
void CombinedLocoSelPane::On_go2_clicked()
{
 if (log->isDebugEnabled()) log->debug("Open programmer pressed");
 openButton();
}

/**
 * Identify loco button pressed, start the identify operation This defines
 * what happens when the identify is done.
 */
/*protected*/ void CombinedLocoSelPane::startIdentifyLoco() {
    // start identifying a loco
    Programmer* p = NULL;
    if (selector != NULL && selector->isSelected()) {
        p = selector->getProgrammer();
    }
    if (p == NULL) {
        log->warn("Selector did not provide a programmer, use default");
        p = ((DefaultProgrammerManager*) InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer();
    }
    CLSIdentifyLoco* id = new CLSIdentifyLoco(p, this);
//    {

//        @Override
//        protected void done(int dccAddress) {
//            // if Done, updated the selected decoder
//            CombinedLocoSelPane.this.selectLoco(dccAddress);
//        }

//        @Override
//        protected void message(String m) {
//            if (_statusLabel != NULL) {
//                _statusLabel.setText(m);
//            }
//        }

//        @Override
//        protected void error() {
//            // raise the button again
//            idloco.setSelected(false);
//        }
//    };
    id->start();
}

/**
 * Identify loco button pressed, start the identify operation
 * This defines what happens when the identify is done.
 */
/*protected*/ void CombinedLocoSelPane::startIdentifyDecoder()
{
 // start identifying a decoder
 Programmer* p = NULL;
 if (selector != NULL && selector->isSelected()) {
     p = selector->getProgrammer();
 }
 if (p == NULL)
 {
     log->warn("Selector did not provide a programmer, use default");
     p = ((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer();
 }
 CLSIdentifyDecoder* id = new CLSIdentifyDecoder(p, this);
 id->start();
}

CLSIdentifyLoco::CLSIdentifyLoco(Programmer* programmer, CombinedLocoSelPane *who) : IdentifyLoco(programmer)
{
 this->who = who;
}
/*protected*/ void CLSIdentifyLoco::done(int dccAddress) {
    // if Done, updated the selected decoder
    who->selectLoco(dccAddress);
}
/*protected*/ void CLSIdentifyLoco::message(QString m)
{
 if (who->_statusLabel != NULL)
  who->_statusLabel->setText(m);
}
/*protected*/ void CLSIdentifyLoco::error() {
    // raise the button again
    who->idloco->setSelected(false);
}


CLSIdentifyDecoder::CLSIdentifyDecoder(Programmer* programmer, CombinedLocoSelPane *who) : IdentifyDecoder(programmer)
{
 this->who = who;
 who->iddecoder->setEnabled(true);
 who->setCursor(Qt::ArrowCursor);
}

/*protected*/ void CLSIdentifyDecoder::done(int mfg, int model, int productID)
{
 // if Done, updated the selected decoder
 who->selectDecoder(mfg, model, productID);
}
/*protected*/ void CLSIdentifyDecoder::message(QString m)
{
 if (who->_statusLabel != NULL)
  who->_statusLabel->setText(m);
}
/*protected*/ void CLSIdentifyDecoder::error()
{
 // raise the button again
 who->iddecoder->setSelected(false);
}

/**
 * Notification that the Roster has changed, so the locomotive
 * selection list has to be changed.
 * @param ev Ignored.
 */
/*public*/ void CombinedLocoSelPane::propertyChange(PropertyChangeEvent* /*ev*/) {
    locoBox->update();
}

/**
 * Identify locomotive complete, act on it by setting the GUI.
 * This will fire "GUI changed" events which will reset the
 * decoder GUI.
 * @param dccAddress
 */
/*protected*/ void CombinedLocoSelPane::selectLoco(int dccAddress)
{
 // raise the button again
 idloco->setChecked(false);
 // locate that loco
 QList<RosterEntry*> l = Roster::getDefault()->matchingList(NULL, NULL, QString::number(dccAddress),
                                            NULL, NULL, NULL, NULL);
 if (log->isDebugEnabled()) log->debug("selectLoco found "+QString::number(l.size())+" matches");
 if (l.size() > 0)
 {
  RosterEntry* r = l.at(0);
  if (log->isDebugEnabled()) log->debug("Loco id is "+ r->getId());
  locoBox->setCurrentIndex(locoBox->findText(r->getId()));
 }
 else
 {
  log->warn("Read address "+QString::number(dccAddress)+", but no such loco in roster");
  if(_statusLabel != NULL)
   _statusLabel->setText(tr("Read address ") + QString::number(dccAddress)+ tr(", but no such loco in roster"));
  if (log->isDebugEnabled())
   log->debug("selectLoco found "+QString::number(dccAddress)+tr(", but no such loco in roster"));
 }
}

/**
 * Identify decoder complete, act on it by setting the GUI
 * This will fire "GUI changed" events which will reset the
 * locomotive GUI.
 * @param mfgID the decoder's manufacturer ID value from CV8
 * @param modelID the decoder's model ID value from CV7
 * @param productID the decoder's product ID
 */
/*protected*/ void CombinedLocoSelPane::selectDecoder(int mfgID, int modelID, int productID)
{
 // raise the button again
 iddecoder->setChecked(false);
 //QList<DecoderFile*>* temp = new QList<DecoderFile*>();
 QList<DecoderFile*> temp;

 // if productID present, try with that
 if (productID != -1)
 {
  QString sz_productID = QString::number(productID);
  temp = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList("", "", QString::number(mfgID), QString::number(modelID), sz_productID, "");
  if (temp.size() == 0)
  {
   log->debug("selectDecoder found no items with product ID "+productID);
   temp = QList<DecoderFile*>();
  }
  else
  {
   log->debug("selectDecoder found "+QString::number(temp.size())+" matches with productID "+QString::number(productID));
  }
 }

 // try without product ID if needed
 if (temp == QList<DecoderFile*>())
 {  // i.e. if no match previously
  temp = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList("", "", QString::number(mfgID), QString::number(modelID), "", "");
  if (log->isDebugEnabled()) log->debug("selectDecoder without productID found "+QString::number(temp.size())+" matches");
 }

 // install all those in the JComboBox in place of the longer, original list
 if (temp.size() > 0)
 {
  updateForDecoderTypeID(temp);
 }
 else
 {
  QString mfg = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->mfgNameFromId(QString::number(mfgID));
  if (mfg=="")
  {
   updateForDecoderNotID(mfgID, modelID);
  }
  else
  {
   updateForDecoderMfgID(mfg, mfgID, modelID);
  }
 }
}

/**
 * Decoder identify has matched one or more specific types
 */
void CombinedLocoSelPane::updateForDecoderTypeID(QList<DecoderFile*> pList)
{
 //decoderBox->setModel(DecoderIndexFile::jComboBoxModelFromList(pList));
 decoderBox->clear();
 foreach(DecoderFile* r, pList)
  decoderBox->addItem(r->titleString());
 decoderBox->insertItem(0, "<from locomotive settings>");
 decoderBox->setCurrentIndex(1);
}
/**
 * Decoder identify has not matched specific types, but did
 * find manufacturer match
 * @param pMfg Manufacturer name. This is passed to save time,
 *              as it has already been determined once.
 * @param pMfgID Manufacturer ID number (CV8)
 * @param pModelID Model ID number (CV7)
 */
void CombinedLocoSelPane::updateForDecoderMfgID(QString pMfg, int pMfgID, int pModelID)
{
 QString msg = "Found mfg "+QString::number(pMfgID)+" ("+pMfg+") version "+QString::number(pModelID)+"; no such decoder defined";
 log->warn(msg);
 if(_statusLabel != NULL)
  _statusLabel->setText(msg);
 // try to select all decoders from that MFG
 QComboBox* temp = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingComboBox(NULL, NULL, QString::number(pMfgID), NULL, NULL, NULL);
 if (log->isDebugEnabled()) log->debug("mfg-only selectDecoder found "+QString::number(temp->count())+" matches");
 if(decoderBox == NULL)
  decoderBox = new QComboBox;
 // install all those in the JComboBox in place of the longer, original list
 if (temp->count() > 0)
 {
  //decoderBox.setModel(temp->getModel());
  for(int i = 0; i < temp->count(); i++)
   decoderBox->addItem(temp->itemText(i));
  decoderBox->insertItem(0, "<from locomotive settings>");
  decoderBox->setCurrentIndex(1);
 }
 else
 {
  // if there are none from this mfg, go back to showing everything
  temp = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingComboBox(NULL, NULL, NULL, NULL, NULL, NULL);
  //decoderBox.setModel(temp.getModel());
  for(int i = 0; i < temp->count(); i++)
   decoderBox->addItem(temp->itemText(i));
  decoderBox->insertItem(0, "<from locomotive settings>");
  decoderBox->setCurrentIndex(1);
 }
}
/**
 * Decoder identify did not match anything, warn and show all
 */
void CombinedLocoSelPane::updateForDecoderNotID(int pMfgID, int pModelID)
{
 log->warn("Found mfg "+QString::number(pMfgID)+" version "+QString::number(pModelID)+"; no such manufacterer defined");
 QComboBox* temp = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingComboBox(NULL, NULL, NULL, NULL, NULL, NULL);
 //decoderBox.setModel(temp.getModel());
 for(int i = 0; i < temp->count(); i++)
  decoderBox->addItem(temp->itemText(i));
 decoderBox->insertItem(0, "<from locomotive settings>");
 decoderBox->setCurrentIndex(1);
}


/**
 * handle pushing the open programmer button by finding names, then calling
 * a template method
 */
/*protected*/ void CombinedLocoSelPane::openButton()
{
 // figure out which we're dealing with
 if (locoBox->getSelectedRosterEntries()->length() != 0)
 {
  // known loco
   openKnownLoco();
 }
 else if (isDecoderSelected())
 {
  // new loco
  openNewLoco();
 }
 else
 {
  // should not happen, as the button should be disabled!
  log->error("openButton with neither combobox nonzero");
 }
}

/**
 * Start with a locomotive selected, so we're opening an existing
 * RosterEntry.
 */
/*protected*/ void CombinedLocoSelPane::openKnownLoco()
{
 if (locoBox->getSelectedRosterEntries()->length() != 0)
 {
  RosterEntry* re = locoBox->getSelectedRosterEntries()->at(0);
  if (log->isDebugEnabled())
  {
   log->debug("loco file: " + re->getFileName());
  }

  startProgrammer(NULL, re, programmerBox->currentText());
 }
 else
 {
  log->error("No roster entry was selected to open.");
 }
}

/**
 * Start with a decoder selected, so we're going to create a new
 * RosterEntry.
 */
/*protected*/ void CombinedLocoSelPane::openNewLoco()
{
 // find the decoderFile object
 setCursor(Qt::WaitCursor);
 DecoderFile* decoderFile = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->fileFromTitle(selectedDecoderType());
 if (log->isDebugEnabled()) log->debug("decoder file: "+decoderFile->getFileName());

 // create a dummy RosterEntry with the decoder info
 RosterEntry* re = new RosterEntry();
 re->setDecoderFamily(decoderFile->getFamily());
 re->setDecoderModel(decoderFile->getModel());
 re->setId(tr("<new loco>"));

 // note that we're leaving the filename NULL
 // add the new roster entry to the in-memory roster
 Roster::getDefault()->addEntry(re);

 startProgrammer(decoderFile, re, programmerBox->currentText());
 setCursor(Qt::ArrowCursor);

}

/** meant to be overridden to start the desired type of programmer */
/*protected*/ void CombinedLocoSelPane::startProgrammer(DecoderFile* /*decoderFile*/, RosterEntry* /*r*/, QString /*progName*/)
{
 log->error("startProgrammer method in CombinedLocoSelPane should have been overridden");
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(CombinedLocoSelPane.class.getName());

