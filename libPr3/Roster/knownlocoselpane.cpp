#include "knownlocoselpane.h"
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <rosterentryselectorpanel.h>
#include <QComboBox>
#include "progdefault.h"
#include "identifyloco.h"
#include "decoderfile.h"
#include <QMessageBox>
#include "instancemanager.h"

//KnownLocoSelPane::KnownLocoSelPane(QWidget *parent) :
//    LocoSelPane(parent)
//{
//}
/**
 * Provide GUI controls to select a known loco via the Roster.
 * <P>
 * When the "open programmer" button is pushed, i.e. the user is ready to
 * continue, the startProgrammer method is invoked.  This should be
 * overridden (e.g. in a local anonymous class) to create the programmer frame
 * you're interested in.
 *
 * @author			Bob Jacobsen   Copyright (C) 2001, 2002
 * @version			$Revision: 21935 $
 */
///*public*/ class KnownLocoSelPane extends LocoSelPane  {

/*public*/ KnownLocoSelPane::KnownLocoSelPane(QLabel* s, bool ident, ProgModeSelector* selector, QWidget *parent) : LocoSelPane(parent)
{
    mCanIdent = ident;
    mStatusLabel = s;
    this->selector = selector;
    init();
}

/*public*/ KnownLocoSelPane::KnownLocoSelPane(bool ident, QWidget *parent) : LocoSelPane(parent)
{
    //this(NULL, ident);
    mStatusLabel = NULL;
    mCanIdent = ident;
    this->selector = NULL;
    init();
}


/*protected*/ void KnownLocoSelPane::init()
{
 log = new Logger("KnownLocoSelPane");
 mStatusLabel = NULL;
 locoBox = NULL;
 setLayout(thisLayout = new QVBoxLayout);//(this, BoxLayout.Y_AXIS));
//    QWidget*  pane2a = new QWidget();
//    pane2a->setLayout(new BoxLayout(pane2a, BoxLayout.X_AXIS));
 QHBoxLayout* pane2aLayout = new QHBoxLayout;
 pane2aLayout->addWidget(new QLabel(tr("Use existing roster entry:")));

 if (mCanIdent)
 {
  QPushButton* idloco = new QPushButton(tr("Read address & select"));
//  idloco.addActionListener( new ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                if (log->isDebugEnabled()) log->debug("Identify locomotive pressed");
//                startIdentify();
//            }
//        });
  connect(idloco, SIGNAL(clicked()), this, SLOT(On_idLoco()));
  pane2aLayout->addWidget(idloco);
   //pane2a.setAlignmentX(JLabel.LEFT_ALIGNMENT);
 }
 thisLayout->addLayout(pane2aLayout);

 locoBox = new RosterEntrySelectorPanel();
 locoBox->setNonSelectedItem("Locomotive");
 thisLayout->addWidget(locoBox);

 addProgrammerBox();

 QPushButton* go2 = new QPushButton(tr("Open Programmer"));
//    go2.addActionListener( new ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                if (log->isDebugEnabled()) log->debug("Open programmer pressed");
//                openButton();
//            }
//        });
 connect(go2, SIGNAL(clicked()), this, SLOT(On_go2_clicked()));
    thisLayout->addWidget(go2, 0,Qt::AlignRight);
//    setBorder(new EmptyBorder(6,6,6,6));
}
void KnownLocoSelPane::On_idLoco()
{
 if (log->isDebugEnabled()) log->debug("Identify locomotive pressed");
  startIdentify();
}
void KnownLocoSelPane::On_go2_clicked()
{
 if (log->isDebugEnabled()) log->debug("Open programmer pressed");
  openButton();
}

/**
 * Add the GUI for selecting a specific programmer
 */
/*private*/ void KnownLocoSelPane::addProgrammerBox()
{
//    QWidget* pane3a = new JPanel();
//    pane3a.setLayout(new BoxLayout(pane3a, BoxLayout.X_AXIS));
 QHBoxLayout* pane3aLayout = new QHBoxLayout;
 pane3aLayout->addWidget(new QLabel(tr("Programmer Format")));

 // create the programmer box
 programmerBox = new QComboBox(/*ProgDefault.findListOfProgFiles()*/);
 programmerBox->addItems(ProgDefault::findListOfProgFiles());
 programmerBox->setCurrentIndex(0);
 if (ProgDefault::getDefaultProgFile()!=NULL) programmerBox->setCurrentIndex(programmerBox->findText(ProgDefault::getDefaultProgFile()));
 pane3aLayout->addWidget(programmerBox);
 // pane3a.setAlignmentX(JLabel.RIGHT_ALIGNMENT);
 thisLayout->addLayout(pane3aLayout);
}


/*private*/ void KnownLocoSelPane::startIdentify()
{
 // start identifying a loco
 /*final*/ KnownLocoSelPane* me = this;
 Programmer* p = NULL;
 if (selector != NULL && selector->isSelected()) p = selector->getProgrammer();
 if (p == NULL) {
     log->warn("Selector did not provide a programmer, use default");
     p = ((GlobalProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer();
 }
 // IdentifyLoco* id = new IdentifyLoco() {
//            private KnownLocoSelPane who = me;
//            protected void done(int dccAddress) {
//            // if Done, updated the selected decoder
//                who.selectLoco(dccAddress);
//            }
//            protected void message(String m) {
//                if (mStatusLabel != NULL) mStatusLabel.setText(m);
//            }
//            /*public*/ void error() {}
//        };
    KLSPIdentifyLoco* id = new KLSPIdentifyLoco(p, this);
    id->start();
}
/*protected*/ void KLSPIdentifyLoco::done(int dccAddress) {
// if Done, updated the selected decoder
    who->selectLoco(dccAddress);
}
/*protected*/ void KLSPIdentifyLoco::message(QString m) {
    if (who->mStatusLabel != NULL) who->mStatusLabel->setText(m);
}
KLSPIdentifyLoco::KLSPIdentifyLoco(Programmer* programmer, KnownLocoSelPane *who) : IdentifyLoco(programmer)
{
 this->who = who;
}

/*public*/ void KLSPIdentifyLoco::error() {}

/*protected*/ void KnownLocoSelPane::selectLoco(int dccAddress)
{
 // locate that loco
 QList<RosterEntry*> l = Roster::instance()->matchingList(NULL, NULL, QString::number(dccAddress),
                                            NULL, NULL, NULL, NULL);
 if (log->isDebugEnabled()) log->debug("selectLoco found "+QString::number(l.size())+" matches");
 if (l.size() > 0)
 {
  RosterEntry* r = l.at(0);
  QString id = r->getId();
  if (log->isDebugEnabled()) log->debug("Loco id is "+id);
  QString group = locoBox->getSelectedRosterGroup();
  if (group != NULL && group!=(Roster::ALLENTRIES))
  {
   QList<RosterEntry*> entries = Roster::instance()->getEntriesWithAttributeKeyValue(Roster::getRosterGroupProperty(group), "yes");
   if (entries.contains(r))
   {
    locoBox->setSelectedRosterEntry(r);
   }
   else
   {
    locoBox->setSelectedRosterEntryAndGroup(r, Roster::ALLENTRIES);
   }
  }
  else
  {
   locoBox->setSelectedRosterEntry(r);
  }
 }
 else
 {
  log->warn("Read address "+QString::number(dccAddress)+", but no such loco in roster");
 }
}


/** handle pushing the open programmer button by finding names, then calling a template method */
/*protected*/ void KnownLocoSelPane::openButton()
{

 if (locoBox->getSelectedRosterEntries()->length() != 0)
 {
  RosterEntry* re = locoBox->getSelectedRosterEntries()->at(0);
  startProgrammer(NULL, re, programmerBox->currentText());
 }
 else
 {
//        JOptionPane.showMessageDialog(this,
//                SymbolicProgBundle.bundle().getString("LocoMustSelected"),
//                SymbolicProgBundle.bundle().getString("NoSelection"),
//                JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("No Selection"), tr("LocoMustSelected"));
 }
}

/** meant to be overridden to start the desired type of programmer */
/*protected*/ void KnownLocoSelPane::startProgrammer(DecoderFile* decoderFile, RosterEntry* r,
                                QString programmerName)
{
 log->error("startProgrammer method in NewLocoSelPane should have been overridden");
}
