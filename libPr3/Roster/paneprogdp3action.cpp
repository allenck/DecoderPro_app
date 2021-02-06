#include "paneprogdp3action.h"
#include "progservicemodecombobox.h"
#include <QLabel>
#include "instancemanager.h"
#include <QBoxLayout>
#include "jmrijframe.h"
#include "combinedlocoseltreepane.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "rostermenu.h"
#include "borderlayout.h"
#include "decoderfile.h"
#include "rosterentry.h"
#include "decoderindexfile.h"
#include "roster.h"
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include "jseparator.h"
#include "jtextfield.h"
#include "programmer.h"
#include "fileutil.h"
#include "enumvariablevalue.h"
#include "variabletablemodel.h"
#include "cvtablemodel.h"
#include "paneserviceprogframe.h"
#include "dccaddressvarhandler.h"
#include <QMessageBox>
#include "panecontainer.h"
#include <QTreeView>
#include "globalprogrammermanager.h"
#include "defaultprogrammermanager.h"
#include "printdecoderlistaction.h"

PaneProgDp3Action::PaneProgDp3Action()
 : JmriAbstractAction("New Loco", (WindowInterface*)NULL)
{
 init();
}

PaneProgDp3Action::~PaneProgDp3Action(){}

/**
 * Swing action to create and register a
 * frame for selecting the information needed to
 * open a PaneProgFrame in service mode.
 * <P>
 * The name is a historical accident, and probably should have
 * included "ServiceMode" or something.
 * <P>
 * The resulting JFrame
 * is constructed on the fly here, and has no specific type.
 *
 * @see  jmri.jmrit.symbolicprog.tabbedframe.PaneOpsProgAction
 *
 * @author			Bob Jacobsen    Copyright (C) 2001
 * @version			$Revision: 17977 $
 */
// /*public*/ class PaneProgDp3Action 	extends JmriAbstractAction implements jmri.ProgListener, jmri.jmrit.symbolicprog.tabbedframe.PaneContainer{

/**
*
*/
//private static final long serialVersionUID = 5579779133820749548L;

/*public*/ PaneProgDp3Action::PaneProgDp3Action(QString s, WindowInterface* wi) : JmriAbstractAction(s, wi){
 //super(s, wi);
    init();
}

/*public*/ PaneProgDp3Action::PaneProgDp3Action(QString s, QIcon i, WindowInterface* wi)
 : JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
    init();
}

/*public*/ PaneProgDp3Action::PaneProgDp3Action(QObject* parent)
 : JmriAbstractAction("name", (WindowInterface*)parent)
{
    //this(tr("Name"));  // NOI18N
 init();
}

/*public*/ PaneProgDp3Action::PaneProgDp3Action(QString s, QObject* parent)
 : JmriAbstractAction("name", (WindowInterface*)parent) {
    //super(s);
    init();

}

void PaneProgDp3Action::init()
{
 log = new Logger("PaneProgDp3Action");

 statusLabel = new JLabel(tr("Idle")); // NOI18N
 log = new Logger("PaneProgDp3Action");
 lastSelectedProgrammer = QString(this->metaObject()->className())+".SelectedProgrammer"; // NOI18N
 rosterIdField = new JTextField(20);
 rosterAddressField = new JTextField(10);
 shortAddr = false;
 cv29 = 0;
 cv17 = -1;
 cv18 = -1;
 cv19 = 0;
 cv1 = 0;
 address="3";
 rosterPanel = NULL;//new QWidget();
 cvModel      = NULL;
 iCvModel     = NULL;
 modelElem = QDomElement();
 progPane = NULL;
 longMode = false;
 newAddr = "";
 // hold refs to variables to check dccAddress
 primaryAddr = NULL;
 extendAddr = NULL;
 addMode = NULL;
 teststatus = 0;
 f = NULL;

 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


/*public*/ void PaneProgDp3Action::actionPerformed(ActionEvent* e)
{
 log->debug("Pane programmer requested"); // NOI18N

 if(f==NULL)
 {
  log->debug("found f==NULL");
  // create the initial frame that steers
  f = new JmriJFrameX(tr("Create New Loco")); // NOI18N
  //f.getContentPane().setLayout(new BorderLayout());
  QWidget* centralWidget = new QWidget;
  QVBoxLayout* centralwidgetLayout = new QVBoxLayout;
  centralWidget->setLayout(centralwidgetLayout);
  f->setCentralWidget(centralWidget);
  // ensure status line is cleared on close so it is normal if re-opened
//        f.addWindowListener(new WindowAdapter(){
//            //@Override
//            /*public*/ void windowClosing(WindowEvent we){
//                statusLabel.setText(tr("StateIdle")); // NOI18N
//                f.windowClosing(we);}});
  f->addWindowListener((WindowListener*)this);

  // add the Roster menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* j = new QMenu(tr("File")); // NOI18N
  j->addAction(new PrintDecoderListAction(tr("Print Decoder Definitions"), f, false, this)); // NOI18N
  j->addAction(new PrintDecoderListAction(tr("Print Preview Decoder Definitions"), f, true, this)); // NOI18N
  menuBar->addMenu(j);
  menuBar->addMenu(new RosterMenu(tr("Roster"), RosterMenu::MAINMENU, f)); // NOI18N
  f->setMenuBar(menuBar);
  bottomPanel = new QWidget();
  BorderLayout* bottomPanelLayout = new BorderLayout();
  // new Loco on programming track
  combinedLocoSelTree = new PPD3CombinedLocoSelTreePane(statusLabel, modePane, this);
//        {
//         /**
//           *
//           */
//         //private static final long serialVersionUID = 587815634507269784L;
//         /*public*/ void windowClosing(QCloseEvent* we)
//         {
//              statusLabel.setText(tr("StateIdle")); // NOI18N
//              f.windowClosing(we);
//         }
//        });
//@Override



  // load primary frame
  QWidget* topPanel = new QWidget();
  QVBoxLayout* topPanelLayout = new QVBoxLayout(topPanel);
  topPanelLayout->addWidget(modePane);
  topPanelLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  QLayout* l = f->getContentPane()->layout();
  ((QVBoxLayout*)f->getContentPane()->layout())->addWidget(topPanel, /*BorderLayout::North*/0, Qt::AlignTop);
  //f.getContentPane().add(modePane);
  //f.getContentPane().add(new JSeparator(javax.swing.SwingConstants.HORIZONTAL));

//  combinedLocoSelTree->setAlignmentX(JLabel.CENTER_ALIGNMENT);
  ((QVBoxLayout*)f->getContentPane()->layout())->addWidget(combinedLocoSelTree, /*BorderLayout::Center*/0, Qt::AlignCenter);

  //f.getContentPane().add(new JSeparator(javax.swing.SwingConstants.HORIZONTAL));
  //basicRoster.setEnabled(false);
//  statusLabel->setAlignmentX(JLabel.CENTER_ALIGNMENT);
  bottomPanelLayout->addWidget(statusLabel, BorderLayout::South);
  ((QVBoxLayout*)f->getContentPane()->layout())->addWidget(bottomPanel, /*BorderLayout::South*/0, Qt::AlignBottom);

  f->pack();
  if (log->isDebugEnabled()) log->debug("Tab-Programmer setup created"); // NOI18N
 } 
 else 
 {
  e = NULL;
  combinedLocoSelTree->resetSelections();
 }
 f->setVisible(true);
} // end actionPerformed


// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* PaneProgDp3Action::makePanel() {
throw  IllegalArgumentException("Should not be invoked"); // NOI18N
}

/*synchronized*/ void PaneProgDp3Action::findDecoderAddress()
{
 teststatus = 1;
 readCV("29");
}

/*synchronized*/ /*public*/ void PaneProgDp3Action::programmingOpReply(int value, int status) {
switch(teststatus){
    case 1 :
             teststatus = 2;
             cv29=value;
             readCV("1");
             break;
    case 2 : teststatus = 3;
             cv1=value;
             readCV("17");
             break;
    case 3 : teststatus = 4;
             cv17 = value;
             readCV("18");
             break;
    case 4 : teststatus = 5;
             cv18 = value;
             readCV("19");
             break;
    case 5 : cv19 = value;
             finishRead();
             break;
    default: log->error("unknown test state " + teststatus);
             break;
 }
}

/*synchronized*/ void PaneProgDp3Action::finishRead(){
if((cv29&0x20) == 0){
    shortAddr = true;
    address = QString::number(cv1);
}
if(cv17!=-1 || cv18!=-1){
    longAddress = (cv17&0x3f)*256 + cv18;
    address = QString::number(longAddress);
}
if(progPane!=NULL){
    progPane->setVariableValue("Short Address", cv1); // NOI18N
    progPane->setVariableValue("Long Address", longAddress); // NOI18N
    progPane->setCVValue("29", cv29);
    progPane->setCVValue("19", cv19);
}
}

/*protected*/ void PaneProgDp3Action::readCV(QString cv) {
Programmer* p = ((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer();
if (p == NULL) {
    //statusUpdate("No programmer connected");
} else {
    try {
        p->readCV(cv, (ProgListener*)this);
    } catch (ProgrammerException ex) {
        //statusUpdate(""+ex);
    }
}
}

/*synchronized*/ void PaneProgDp3Action::setUpRosterPanel()
{
 re=NULL;
 if(rosterPanel==NULL)
 {
  rosterPanel = new QWidget();
  BorderLayout* rosterPanelLayout;
  rosterPanel->setLayout(rosterPanelLayout = new BorderLayout());
  QWidget* p = new QWidget();
  QHBoxLayout* pLayout = new QHBoxLayout(p);
  pLayout->addWidget(new QLabel(tr("RosterId"))); // NOI18N
  pLayout->addWidget(rosterIdField);
  rosterPanelLayout->addWidget(p, BorderLayout::North);
  rosterIdField->setText(tr("LabelNewDecoder")); // NOI18N
  saveBasicRoster = new QPushButton(tr("Save")); // NOI18N
//    saveBasicRoster.addActionListener( new ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            try{
//                log->debug("saveBasicRoster button pressed, calls saveRosterEntry");
//                saveRosterEntry();
//            } catch (jmri.JmriException ex){
//                return;
//            }
//        }
//    });
  connect(saveBasicRoster, SIGNAL(clicked()), this, SLOT(On_saveBasicRoster()));
//  TitledBorder border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
//  border.setTitle(tr("CreateBasicRosterEntry")); // NOI18N
//  rosterPanel->setBorder(border);
  rosterPanel->setVisible(false);
  ((BorderLayout*)f->getContentPane()->layout())->addWidget(rosterPanel, BorderLayout::East);
 } 
 else 
 {
  rosterIdField->setText(tr("LabelNewDecoder")); // NOI18N
 }
 if(progPane!=NULL)
 {
  progPane->dispose();
  rosterPanel->layout()->removeWidget(progPane);
  progPane = NULL;
//  rosterPanel->revalidate();
  //f->getContentPane()->repaint();
  f->update();
  f->adjustSize();
 }
 if (((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager")) != NULL &&
    ((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->isGlobalProgrammerAvailable()){
    this->mProgrammer = ((GlobalProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer();
 }

 cvModel       = new CvTableModel(statusLabel, mProgrammer);

 variableModel = new VariableTableModel(statusLabel, QStringList{"Name", "Value"}, cvModel);
 if(decoderFile!=NULL)
 {
  QDomElement decoderRoot = QDomElement();
  try 
  {
   decoderRoot = decoderFile->rootFromName(DecoderFile::fileLocation+decoderFile->getFileName());
  } 
  catch (Exception e)
  { 
   log->error("Exception while loading decoder XML file: "+decoderFile->getFileName(), e); return;
  } // NOI18N
  modelElem = decoderFile->getModelElement();

  decoderFile->loadVariableModel(decoderRoot.firstChildElement("decoder"), variableModel); // NOI18N
  rosterPanel->setVisible(true);
 } 
 else 
 {
  rosterPanel->setVisible(false);
  return;
 }
 QDomElement programmerRoot;
 XmlFile* pf = new XmlFile();  // XmlFile is abstract

// PropertyChangeListener* dccNews = new PropertyChangeListener() {
//        /*public*/ void propertyChange(PropertyChangeEvent e) { updateDccAddress(); }
//    };
 primaryAddr = variableModel->findVar("Short Address"); // NOI18N

 if (primaryAddr==NULL) log->debug("DCC Address monitor didnt find a Short Address variable"); // NOI18N
 else 
 {
  //primaryAddr->addPropertyChangeListener(dccNews);
  connect(primaryAddr->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 extendAddr = variableModel->findVar("Long Address"); // NOI18N
 if (extendAddr==NULL) log->debug("DCC Address monitor didnt find an Long Address variable"); // NOI18N
 else
 {
  //extendAddr.addPropertyChangeListener(dccNews);
  connect(extendAddr->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 addMode = (EnumVariableValue*)variableModel->findVar("Address Format"); // NOI18N
 if (addMode==NULL) log->debug("DCC Address monitor didnt find an Address Format variable"); // NOI18N
 else
 {
  //addMode.addPropertyChangeListener(dccNews);
  connect(addMode->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 try
 {
  programmerRoot = pf->rootFromName("programmers"+File::separator+"Basic.xml"); // NOI18N
  QDomElement base;
  if ( (base = programmerRoot.firstChildElement("programmer")) .isNull()) { // NOI18N
      log->error("xml file top element is not programmer"); // NOI18N
      return;
  }
  // for all "pane" elements in the programmer
  QDomNodeList paneList = base.elementsByTagName("pane"); // NOI18N
  if (log->isDebugEnabled()) log->debug("will process "+QString::number(paneList.size())+" pane definitions"); // NOI18N
  QString name = getLocaleAttribute(paneList.at(0).toElement(), "name", "en");
  progPane = new ThisProgPane((PaneContainer*)this, name, paneList.at(0).toElement(), cvModel, /*iCvModel,*/ variableModel, modelElem, re);

  progPane->setVariableValue("Short Address", cv1); // NOI18N
  progPane->setVariableValue("Long Address", longAddress); // NOI18N
  progPane->setCVValue("29", cv29); // NOI18N
  progPane->setCVValue("19", cv19); // NOI18N
  ((BorderLayout*)rosterPanel->layout())->addWidget(progPane, BorderLayout::Center);
//  rosterPanel->revalidate();
  rosterPanel->setVisible(true);
  f->getContentPane()->repaint();
  f->repaint();
  f->pack();
  return;
 }
 catch (Exception e)
 {
  log->error("exception reading programmer file: ", e); // NOI18N
 }
}
void PaneProgDp3Action::On_saveBasicRoster()
{
 try{
     log->debug("saveBasicRoster button pressed, calls saveRosterEntry");
     saveRosterEntry();
 } catch (JmriException ex){
     return;
 }
}

QString PaneProgDp3Action::getLocaleAttribute(QDomElement element, QString attrName, QString locale)
{
 QDomNodeList attr = element.elementsByTagName(attrName);
 if(attr.size() > 0)
 {
  for(int i=0; i < attr.size(); i++)\
  {
   QString a;
   if((a =attr.at(i).toElement().attribute("xml:lang")) == locale)
    return attr.at(i).toElement().text();
  }
 }
 return element.attribute(attrName);
}

/*public*/ void PaneProgDp3Action::propertyChange(PropertyChangeEvent* e) { updateDccAddress(); }


void PaneProgDp3Action::updateDccAddress()
{

 if (log->isDebugEnabled())
    log->debug("updateDccAddress: short "+(primaryAddr==NULL?"<NULL>":primaryAddr->getValueString())+ // NOI18N
              " long "+(extendAddr==NULL?"<NULL>":extendAddr->getValueString())+ // NOI18N
              " mode "+(addMode==NULL?"<NULL>":addMode->getValueString())); // NOI18N

 new PPD3DccAddressVarHandler(primaryAddr, extendAddr, addMode, this);
// {
//    /*protected*/ void doPrimary() {
//    longMode = false;
//        if (primaryAddr != NULL && !primaryAddr.getValueString()==("")) {
//            newAddr = primaryAddr.getValueString();
//        }
//    }
//    /*protected*/ void doExtended() {
//        // long address
//        if (!extendAddr.getValueString()==("")) {
//            longMode = true;
//            newAddr = extendAddr.getValueString();
//        }
//    }
//};
 // update if needed
 if (newAddr!=NULL)
 {
  /*synchronized(this)*/
  {
   // store DCC address, type
   address=newAddr;
   shortAddr= !longMode;
  }
 }
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="IS2_INCONSISTENT_SYNC", // NOI18N
//justification="saveBasicRoster /*protected*/ by ctor invocation, Swing thread when needed")  // NOI18N

/**
*
* @return true if the value in the id JTextField
* is a duplicate of some other RosterEntry in the roster
*/
bool PaneProgDp3Action::checkDuplicate()
{
 // check its not a duplicate
 QList<RosterEntry*> l = Roster::getDefault()->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, rosterIdField->text());
 bool oops = false;
 for (int i=0; i<l.size(); i++)
 {
  if (re!=l.at(i)) oops =true;
 }
 return oops;
}

void PaneProgDp3Action::saveRosterEntry() /*throws jmri.JmriException*/
{
 log->debug("saveRosterEntry");
 if(rosterIdField->text()==(tr("LabelNewDecoder")))
 { // NOI18N
  /*synchronized(this)*/
  {
   //JOptionPane.showMessageDialog(progPane, tr("PromptFillInID")); // NOI18N
   QMessageBox::warning(progPane, tr("Warning"), tr("PromptFillInID"));
  }
  throw new JmriException("No Roster ID"); // NOI18N
 }
 if(checkDuplicate())
 {
    /*synchronized(this)*/
  {
   //JOptionPane.showMessageDialog(progPane, tr("ErrorDuplicateID")); // NOI18N
   QMessageBox::warning(progPane, tr("Warning"), tr("ErrorDuplicateID"));
  }
  throw new JmriException("Duplicate ID"); // NOI18N
 }

 if(re==NULL)
 {
    log->debug("re NULL, creating RosterEntry");
    re = new RosterEntry();
    re->setDecoderFamily(decoderFile->getFamily());
    re->setDecoderModel(decoderFile->getModel());
    re->setId(rosterIdField->text());
    Roster::getDefault()->addEntry(re);
 }

 updateDccAddress();

 // if there isn't a filename, store using the id
 re->ensureFilenameExists();
 QString filename = re->getFileName();

 // create the RosterEntry to its file
 log->debug(tr("setting DCC address %1 %2").arg(address).arg(shortAddr));
 /*synchronized(this)*/
 {
    re->setDccAddress(""+address);  // NOI18N
    re->setLongAddress(!shortAddr);
    re->writeFile(cvModel, /*iCvModel,*/ variableModel );

    // mark this as a success
    variableModel->setFileDirty(false);
 }
 // and store an updated roster file
 FileUtil::createDirectory(FileUtil::getUserFilesPath());
 Roster::getDefault()->writeRoster();

 // show OK status
 statusLabel->setText(tr("Roster file %1 saved OK").arg(filename));
}


/*public*/ bool PaneProgDp3Action::isBusy() { return false; }

/*public*/ void PaneProgDp3Action::paneFinished() {}

/**
* Enable the read/write buttons.
* <p>
* In addition, if a programming mode pane is
* present, it's "set" button is enabled.
*
* @param enable Are reads possible? If false, so not enable
* the read buttons.
*/
/*public*/ void PaneProgDp3Action::enableButtons(bool enable) {}

/*public*/ void PaneProgDp3Action::prepGlassPane(JToggleButton* activeButton) {}

/*synchronized*/ /*public*/ BusyGlassPane* PaneProgDp3Action::getBusyGlassPane() {
return new BusyGlassPane( QList<QWidget*>(),
                                   QList<QRect>(),
                                   rosterPanel, f);
}

//class ThisProgPane extends PaneProgPane {

/**
*
*/
//private static final long serialVersionUID = 8855795459526662034L;

/*public*/ ThisProgPane::ThisProgPane(PaneContainer* parent, QString name, QDomElement pane, CvTableModel* cvModel,
                                      /*IndexedCvTableModel* icvModel,*/ VariableTableModel* varModel, QDomElement modelElem, RosterEntry* re)
    :PaneProgPane(parent, name, pane, cvModel, /*icvModel,*/ varModel, modelElem, re)
{
    bottom->layout()->removeWidget(readChangesButton);
    bottom->layout()->removeWidget(writeChangesButton);
    writeAllButton->setText(tr("ButtonWrite")); // NOI18N
    readAllButton->setText(tr("ButtonRead")); // NOI18N
    bottom->layout()->addWidget(((PaneProgDp3Action*)parent)->saveBasicRoster);
//    bottom.revalidate();
//    readAllButton.removeItemListener(l2);
//    readAllButton.addItemListener(l2 = new ItemListener() {
//        /*public*/ void itemStateChanged (ItemEvent e) {
//            if (e.getStateChange() == ItemEvent.SELECTED) {
//                readAllButton.setText(tr("ButtonStopReadSheet")); // NOI18N
//                if (container.isBusy() == false) {
//                    prepReadPane(false);
//                    prepGlassPane(readAllButton);
//                    container.getBusyGlassPane().setVisible(true);
//                    readPaneAll();
//                }
//            } else {
//                stopProgramming();
//                readAllButton.setText(tr("ButtonRead")); // NOI18N
//                if (container.isBusy()) {
//                    readAllButton.setEnabled(false);
//                }
//            }
//        }
//    });
    connect(readAllButton, SIGNAL(clicked(bool)), this, SLOT(On_readAllButton_clicked(bool)));
//    writeAllButton->removeItemListener(l4);
//    writeAllButton.addItemListener(l4 = new ItemListener() {
//        /*public*/ void itemStateChanged (ItemEvent e) {
//            if (e.getStateChange() == ItemEvent.SELECTED) {
//                writeAllButton.setText(tr("ButtonStopWriteSheet")); // NOI18N
//                if (container.isBusy() == false) {
//                    prepWritePane(false);
//                    prepGlassPane(writeAllButton);
//                    container.getBusyGlassPane().setVisible(true);
//                    writePaneAll();
//                }
//            } else {
//                stopProgramming();
//                writeAllButton.setText(tr("ButtonWrite")); // NOI18N
//                if (container.isBusy()) {
//                    writeAllButton.setEnabled(false);
//                }
//            }
//        }
//    });
    connect(writeAllButton, SIGNAL(clicked(bool)), this, SLOT(On_writeAllButton_clicked(bool)));
    if (_cvModel->getProgrammer()== NULL){
        bottom->layout()->removeWidget(readAllButton);
        bottom->layout()->removeWidget(writeAllButton);
//        bottom.revalidate();
        this->layout()->addWidget(bottom);
    }
}
void ThisProgPane::On_readAllButton_clicked(bool bSelected)
{
 //if (e.getStateChange() == ItemEvent.SELECTED) {
 if(bSelected)
 {
  readAllButton->setText(tr("ButtonStopReadSheet")); // NOI18N
  if (container->isBusy() == false)
  {
   prepReadPane(false);
   prepGlassPane(readAllButton);
   container->getBusyGlassPane()->setVisible(true);
   readPaneAll();
  }
 }
 else
 {
  stopProgramming();
  readAllButton->setText(tr("ButtonRead")); // NOI18N
  if (container->isBusy())
  {
   readAllButton->setEnabled(false);
  }
 }
}
/*public*/ void ThisProgPane::On_writeAllButton_clicked(bool bSelected)
{
 if (bSelected) {
     writeAllButton->setText(tr("ButtonStopWriteSheet")); // NOI18N
     if (container->isBusy() == false) {
         prepWritePane(false);
         prepGlassPane(writeAllButton);
         container->getBusyGlassPane()->setVisible(true);
         writePaneAll();
     }
 } else {
     stopProgramming();
     writeAllButton->setText(tr("ButtonWrite")); // NOI18N
     if (container->isBusy()) {
         writeAllButton->setEnabled(false);
     }
 }

}

/*public*/ void ThisProgPane::setCVValue(QString cv, int value){
    if(_cvModel->getCvByNumber(cv)!=NULL){
        (_cvModel->getCvByNumber(cv))->setValue(value);
        (_cvModel->getCvByNumber(cv))->setState(AbstractValue::READ);
    }
}

/*public*/ void ThisProgPane::setVariableValue(QString variable, int value){
    if(_varModel->findVar(variable)!=NULL){
        _varModel->findVar(variable)->setIntValue(value);
        _varModel->findVar(variable)->setState(AbstractValue::READ);
    }
}

/*public*/ void ThisProgPane::dispose(){
 bottom->layout()->removeWidget(((PaneProgDp3Action*)parent())->saveBasicRoster);
    PaneProgPane::dispose();
}

//};
/*public*/ PPD3CombinedLocoSelTreePane::PPD3CombinedLocoSelTreePane(QLabel *s, ProgModeSelector* selector, PaneProgDp3Action* pane)
 : CombinedLocoSelTreePane(s, selector)
{
 this->pane = pane;
 log = new Logger("PPD3CombinedLocoSelTreePane");
}

/*protected*/ void PPD3CombinedLocoSelTreePane::startProgrammer(DecoderFile* decoderFile, RosterEntry* re,
                                        QString progName) // progName is ignored here
 {
  log->debug("startProgrammer");
  QString title =(tr("FrameServiceProgrammerTitle").arg("NewDecoder")); // NOI18N
  if (re!=NULL) title = tr("FrameServiceProgrammerTitle").arg(re->getId());
  JFrame* p = new PaneServiceProgFrame(decoderFile, re,
                               title, "programmers"+File::separator+"Comprehensive.xml", // NOI18N
                               pane->modePane->getProgrammer());
  if(pane->modePane->isSelected() || (pane->modePane->getProgrammer() == nullptr) )
  {
   p = new PPD3PaneProgFrame(decoderFile, re,
                               title, "programmers" + File::separator + "Comprehensive.xml", // NOI18N
                               nullptr, false);
//   {
//            @Override
//            protected JPanel getModePane() {
//                return null;
//            }
//        };
    } else {
        p = new PaneServiceProgFrame(decoderFile, re,
                title, "programmers" + File::separator + "Comprehensive.xml", // NOI18N
                pane->modePane->getProgrammer());
    }
    p->pack();
    p->setVisible(true);
}

/*protected*/ void PPD3CombinedLocoSelTreePane::openNewLoco()
{
   log->debug("openNewLoco");
   // find the decoderFile object
   DecoderFile* decoderFile = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->fileFromTitle(selectedDecoderType());
   if (log->isDebugEnabled()) log->debug("decoder file: "+decoderFile->getFileName()); // NOI18N
   if(pane->rosterIdField->text()==(tr("LabelNewDecoder"))){ // NOI18N
       pane->re = new RosterEntry();
       pane->re->setDecoderFamily(decoderFile->getFamily());
       pane->re->setDecoderModel(decoderFile->getModel());
       pane->re->setId(tr("LabelNewDecoder")); // NOI18N
       //re->writeFile(cvModel, iCvModel, variableModel );
       // note that we're leaving the filename NULL
       // add the new roster entry to the in-memory roster
       Roster::getDefault()->addEntry(pane->re);
   } else {
       try{
           pane->saveRosterEntry();
       } catch (JmriException ex){
           log->warn(tr("Exception while saving roster entry") + ex.getMessage()); // NOI18N
           return;
       }
   }
   // create a dummy RosterEntry with the decoder info
   startProgrammer(decoderFile, pane->re, NULL);
   //Set our roster entry back to NULL so that a fresh roster entry can be created if needed
   pane->re=NULL;
}

//@Override
/*protected*/ QWidget* PPD3CombinedLocoSelTreePane::layoutRosterSelection() {
   log->debug("layoutRosterSelection");
   return NULL;
}

//@Override
/*protected*/ QWidget* PPD3CombinedLocoSelTreePane::layoutDecoderSelection() {
   log->debug("layoutDecoderSelection");
   QWidget* pan = CombinedLocoSelTreePane::layoutDecoderSelection();
#if 0
   dTree->removeTreeSelectionListener(dListener);
   dTree.addTreeSelectionListener(dListener = new TreeSelectionListener() {
       /*public*/ void valueChanged(TreeSelectionEvent e) {
           if (!dTree.isSelectionEmpty() && dTree.getSelectionPath()!=NULL &&
             // check that this isn't just a model
            ((TreeNode)dTree.getSelectionPath().getLastPathComponent()).isLeaf()  &&
             // can't be just a mfg, has to be at least a family
             dTree.getSelectionPath().getPathCount()>2 &&
             // can't be a multiple decoder selection
             dTree.getSelectionCount()<2) {
               log->debug("Selection event with "+dTree.getSelectionPath().toString());
               //if (locoBox != NULL) locoBox.setSelectedIndex(0);
               go2.setEnabled(true);
               go2.setRequestFocusEnabled(true);
               go2.requestFocus();
               go2.setToolTipText(tr("TipClickToOpen")); // NOI18N
               decoderFile = DecoderIndexFile.instance().fileFromTitle(selectedDecoderType());
               setUpRosterPanel();
           } else {
               decoderFile = NULL;
               // decoder not selected - require one
               go2.setEnabled(false);
               go2.setToolTipText(tr("TipSelectLoco")); // NOI18N
               setUpRosterPanel();
           }
       }
   });
#endif
   return pan;
}

/*protected*/ void PPD3CombinedLocoSelTreePane::selectDecoder(int mfgID, int modelID, int productID) {
   log->debug("selectDecoder");
   //On selecting a new decoder start a fresh with a new roster entry
   CombinedLocoSelTreePane::selectDecoder(mfgID, modelID, productID);
   pane->findDecoderAddress();
}


//@Override
/*protected*/ QWidget* PPD3CombinedLocoSelTreePane::createProgrammerSelection(){
   log->debug("createProgrammerSelection");
   //p=jmri.InstanceManager::getDefault(jmri.UserPreferencesManager.class);
   pane->serviceModeProg = new QRadioButton(tr("Service Mode")); // NOI18N
   pane->editModeProg = new QRadioButton(tr("Edit Only")); // NOI18N
   QWidget* pane3a = new QWidget();
   QVBoxLayout* pane3aLayout;
   pane3a->setLayout(pane3aLayout = new QVBoxLayout); //(pane3a, BoxLayout.Y_AXIS));
   // create the programmer box

   QButtonGroup* modeGroup = new QButtonGroup();
   modeGroup->addButton(pane->serviceModeProg);
   modeGroup->addButton(pane->editModeProg);

   QWidget* progModePane = new QWidget();
   QVBoxLayout* progModePaneLayout = new QVBoxLayout(progModePane);
   progModePaneLayout->addWidget(pane->serviceModeProg);
   progModePaneLayout->addWidget(pane->editModeProg);
   pane->serviceModeProg->setChecked(true);

   if (InstanceManager::getDefault("GlobalProgrammerManager")==NULL ||
       !((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->isGlobalProgrammerAvailable())
   {
    pane->editModeProg->setChecked(true);
    pane->serviceModeProg->setEnabled(false);
    iddecoder->setVisible(false);
    pane->modePane->setVisible(false);
   }

//    serviceModeProg.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            if(serviceModeProg.isSelected())
//                iddecoder.setVisible(true);
//        }
//    });
   connect(pane->serviceModeProg, SIGNAL(toggled(bool)), this, SLOT(On_ServiceMode(bool)));

//    editModeProg.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            if(editModeProg.isSelected())
//                iddecoder.setVisible(false);
//        }
//    });
   connect(pane->editModeProg, SIGNAL(toggled(bool)), this, SLOT(On_EditMode()));

   go2 = new QPushButton(tr("Open Programmer")); // NOI18N
//    go2.addActionListener( new ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                log->debug("Open programmer pressed"); // NOI18N
//                openButton();
//                // close this window to prevent having
//                // two windows processing at the same time
//                //
//                // Alternately, could have just cleared out a
//                // bunch of stuff to force starting over, but
//                // that seems to be an even more confusing
//                // user experience.
//                log->debug("Closing f {}", f);
//                WindowEvent wev = new WindowEvent(f, WindowEvent.WINDOW_CLOSING);
//                java.awt.Toolkit.getDefaultToolkit().getSystemEventQueue().postEvent(wev);
//            }
//        });
   connect(go2, SIGNAL(clicked()), this, SLOT(On_go2()));
//   go2->setAlignmentX(JLabel.RIGHT_ALIGNMENT);
   go2->setEnabled(false);
   go2->setToolTip(tr("SELECT A LOCOMOTIVE OR DECODER TO ENABLE")); // NOI18N
   ((BorderLayout*)pane->bottomPanel->layout())->addWidget(go2, BorderLayout::East);
   //pane3a.add(go2);
   return pane3a;
  }
 //}; // end PPD3CombinedLocoSelTreePane
void PPD3CombinedLocoSelTreePane::On_ServiceMode(bool b)
{
 //            if(serviceModeProg.isSelected())
 iddecoder->setVisible(b);
}
void PPD3CombinedLocoSelTreePane::On_EditMode()
{
 log->debug("Open programmer pressed"); // NOI18N
 openButton();
 // close this window to prevent having
 // two windows processing at the same time
 //
 // Alternately, could have just cleared out a
 // bunch of stuff to force starting over, but
 // that seems to be an even more confusing
 // user experience.
 log->debug(tr("Closing f %1").arg(pane->f->title()));
// WindowEvent wev = new WindowEvent(f, WindowEvent.WINDOW_CLOSING);
// java.awt.Toolkit.getDefaultToolkit().getSystemEventQueue().postEvent(wev);

}

PPD3PaneProgFrame::PPD3PaneProgFrame(DecoderFile *pDecoderFile, RosterEntry *pRosterEntry, QString frameTitle, QString programmerFile, Programmer *pProg, bool opsMode, PPD3CombinedLocoSelTreePane *parent)
 : PaneProgFrame(pDecoderFile, pRosterEntry, frameTitle, programmerFile, pProg, opsMode, parent)
{
}
/*protected*/ JPanel *PPD3PaneProgFrame::getModePane() { return NULL; }

/*public*/ PPD3DccAddressVarHandler::PPD3DccAddressVarHandler(VariableValue *primaryAddr, VariableValue *extendAddr, EnumVariableValue *addMode, PaneProgDp3Action* pane) : DccAddressVarHandler(primaryAddr, extendAddr, addMode, new JTextField, pane )
{
 this->pane = pane;
}

/*protected*/ void PPD3DccAddressVarHandler::doPrimary()
{
 pane->longMode = false;
    if (primaryAddr != NULL && primaryAddr->getValueString()!=("")) {
        pane->newAddr = primaryAddr->getValueString();
    }
}
/*protected*/ void PPD3DccAddressVarHandler::doExtended() {
    // long address
    if (extendAddr->getValueString()!=("")) {
        pane->longMode = true;
        pane->newAddr = extendAddr->getValueString();
    }
}
void PPD3CombinedLocoSelTreePane::On_go2()
{
 log->debug("Open programmer pressed"); // NOI18N
 openButton();
 // close this window to prevent having
 // two windows processing at the same time
 //
 // Alternately, could have just cleared out a
 // bunch of stuff to force starting over, but
 // that seems to be an even more confusing
 // user experience.
 log->debug(tr("Closing f %1").arg(pane->f->title()));
// WindowEvent wev = new WindowEvent(f, WindowEvent.WINDOW_CLOSING);
// java.awt.Toolkit.getDefaultToolkit().getSystemEventQueue().postEvent(wev);

}
