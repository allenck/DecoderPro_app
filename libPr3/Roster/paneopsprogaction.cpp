#include "paneopsprogaction.h"
#include <QLabel>
#include "instancemanager.h"
#include "../../LayoutEditor/jmrijframe.h"
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include "rostermenu.h"
#include "rosterentry.h"
#include "paneopsprogframe.h"
#include "lnprogrammermanager.h"
#include "addressedprogrammermanager.h"

//paneOpsProgAction::paneOpsProgAction(QObject *parent) :
//    QAction(parent)
//{
//}
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
 * @version			$Revision: 18903 $
 */
///*public*/ class PaneOpsProgAction 	extends AbstractAction {

//    Object o1, o2, o3, o4;

    //static final java.util.ResourceBundle rbt = jmri.jmrit.symbolicprog.SymbolicProgBundle.bundle();

//    /*public*/ PaneOpsProgAction() {
//        this("DecoderPro ops-mode programmer");
//    }

/*public*/ PaneOpsProgAction::PaneOpsProgAction(QString s, QObject* parent ) : AbstractAction(s, parent)
{
 //super(s);
 log = new Logger("PaneOpsProgAction");

 statusLabel = new QLabel(tr("idle"));

 if (InstanceManager::getNullableDefault("AddressedProgrammerManager") == nullptr
         || !((DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))->isAddressedModePossible()) {
     setEnabled(false);
     // This needs to return so the xmlThread is not started;
     return;
 }
 connect(this, SIGNAL(triggered()),this, SLOT(actionPerformed()));
}

/*public*/ void PaneOpsProgAction::actionPerformed()
{

 if (log->isDebugEnabled()) log->debug("Pane programmer requested");

 // create the initial frame that steers
 /*final*/ JmriJFrame* f = new JmriJFrameX(tr("Operations Mode (Main Track) Programmer Setup"));
 //f.getContentPane().setLayout(new BoxLayout(f.getContentPane(), BoxLayout.Y_AXIS));
 QWidget* contentPane = new QWidget;
 QVBoxLayout* layout = new QVBoxLayout;
 contentPane->setLayout(layout);
 f->setCentralWidget(contentPane);

 // add the Roster menu
 QMenuBar* menuBar = new QMenuBar();
    // menuBar.setBorder(new BevelBorder(BevelBorder.RAISED));
 menuBar->addMenu(new RosterMenu(tr("Roster"),RosterMenu::MAINMENU, f));
 f->setMenuBar(menuBar);

 // known loco on main track
 QWidget* pane1 = new KnownLocoSelPane(false);
// {  // no ident in ops mode yet

//        protected void startProgrammer(DecoderFile decoderFile, RosterEntry re,
//                                            String filename) {
//            String title = java.text.MessageFormat.format(rbt.getString("FrameOpsProgrammerTitle"),
//                                                    new Object[]{re.getId()});
//            // find the ops-mode programmer
//            int address = Integer.parseInt(re.getDccAddress());
//            boolean longAddr = re.isLongAddress();
//            Programmer programmer = InstanceManager.programmerManagerInstance()
//                                        .getAddressedProgrammer(longAddr, address);
//            // and created the frame
//            JFrame p = new PaneOpsProgFrame(decoderFile, re,
//                                             title, "programmers"+File.separator+filename+".xml",
//                                             programmer);
//            p.pack();
//            p.setVisible(true);

//            // f.setVisible(false);
//            // f.dispose();
//        }
//    };

    // load primary frame
    //pane1.setAlignmentX(JLabel.CENTER_ALIGNMENT);
    layout->addWidget(pane1, 0, Qt::AlignCenter);
    f->resize(400,400);
    f->pack();
    if (log->isDebugEnabled()) log->debug("Tab-Programmer setup created");
    f->setVisible(true);
}
/*public*/ PaneOpsProgAction::MyKnownLocoSelPane::MyKnownLocoSelPane(bool b, QWidget* parent) : KnownLocoSelPane(b, parent) {}

/*protected*/ void PaneOpsProgAction::MyKnownLocoSelPane::startProgrammer(DecoderFile* decoderFile, RosterEntry* re, QString filename)
{
  QString title = tr("Program %1 in Operations Mode (Main Track)").arg(re->getId());
  // find the ops-mode programmer
  int address = re->getDccAddress().toInt();
  bool longAddr = re->isLongAddress();
  Programmer* programmer = (Programmer*) ((DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))->getAddressedProgrammer(longAddr, address);
  // and created the frame
  JFrame* p = new PaneOpsProgFrame(decoderFile, re, title, "programmers"+QString(QDir::separator())+filename+".xml",
                                   programmer);
  p->pack();
  p->setVisible(true);

  // f.setVisible(false);
  // f.dispose();
}
