#include "paneprogaction.h"
#include "instancemanager.h"
#include "../../LayoutEditor/jmrijframe.h"
#include <QVBoxLayout>
#include "rostermenu.h"
#include "rosterentry.h"
#include "paneserviceprogframe.h"
#include "progmodeselector.h"
#include <QMenu>
#include <QMenuBar>
#include "jframe.h"
#include "progservicemodecombobox.h"
#include "lnprogrammermanager.h"
#include "jseparator.h"
#include "printdecoderlistaction.h"

//PaneProgAction::PaneProgAction(QObject *parent) :
//    QAction("DecoderPro service programmer", parent)
//{
// log = new Logger("PaneProgAction");
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
// /*public*/ class PaneProgAction 			extends AbstractAction {


//    static final java.util.ResourceBundle rbt = jmri.jmrit.symbolicprog.SymbolicProgBundle.bundle();

//    /*public*/ PaneProgAction() {
//        this("DecoderPro service programmer");
//    }

/*public*/ PaneProgAction::PaneProgAction(QString s, QObject* parent)
    : AbstractAction(s,parent)
{
 //super(s);
 log = new Logger("PaneProgAction");
 modePane = new ProgServiceModeComboBox();

 statusLabel = new QLabel(tr("idle"));

 // disable ourself if programming is not possible
// if (InstanceManager::getNullableDefault("ProgrammerManager") == NULL
//                 || !((ProgrammerManager*)InstanceManager::getDefault("ProgrammerManager"))->isGlobalProgrammerAvailable())
// {
//  setEnabled(false);
//  // This needs to return, so we don't start the xmlThread
//  return;
// }
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


/*public*/ void PaneProgAction::actionPerformed(JActionEvent *)
{
 if (log->isDebugEnabled()) log->debug("Pane programmer requested");

 // create the initial frame that steers
 /*final*/  f = new JmriJFrameX(tr("Service Mode (Programming Track) Programmer Setup"));
 //f.getContentPane().setLayout(new BoxLayout(f.getContentPane(), BoxLayout.Y_AXIS));
 QWidget* contentPane = new QWidget;
 QVBoxLayout* layout = new QVBoxLayout;
 contentPane->setLayout(layout);
 f->setCentralWidget(contentPane);

 // ensure status line is cleared on close so it is normal if re-opened
// f.addWindowListener(new WindowAdapter(){
//        /*public*/ void windowClosing(WindowEvent we){
//            statusLabel.setText(rbt.getString("StateIdle"));
//            f.windowClosing(we);}});
#if 0
 PPAWindowListener* listener = new PPAWindowListener(f, this);
 f->addWindowListener(listener);
#endif
 // add the Roster menu
 QMenuBar* menuBar = new QMenuBar();
 // menuBar.setBorder(new BevelBorder(BevelBorder.RAISED));
 QMenu* j = new QMenu(tr("File"));
 j->addAction(new PrintDecoderListAction(tr("Print Decoder Definitions"), f, false, this));
 j->addAction(new PrintDecoderListAction(tr("Print Preview Decoder Definitions"), f, true, this));
 menuBar->addMenu(j);
 menuBar->addMenu(new RosterMenu(tr("Roster"), RosterMenu::MAINMENU, f));
 f->setMenuBar(menuBar);

 // new Loco on programming track
 QWidget* pane1 = new MyCombinedLocoSelTreePane(this, statusLabel, modePane);
 ((MyCombinedLocoSelTreePane*)pane1)->init();
// {
//            protected void startProgrammer(DecoderFile decoderFile, RosterEntry re,
//                                            String filename) {
//                String title = java.text.MessageFormat.format(rbt.getString("FrameServiceProgrammerTitle"),
//                                                    new Object[]{"new decoder"});
//                if (re!=null) title = java.text.MessageFormat.format(rbt.getString("FrameServiceProgrammerTitle"),
//                                                    new Object[]{re.getId()});
//                JFrame p = new PaneServiceProgFrame(decoderFile, re,
//                                             title, "programmers"+File.separator+filename+".xml",
//                                             modePane.getProgrammer());
//                p.pack();
//                p.setVisible(true);

//                // f.setVisible(false);
//                // f.dispose();
//            }
//        };

 // load primary frame
 layout->addWidget(modePane,0, Qt::AlignHCenter);
 layout->addWidget(new JSeparator(JSeparator::HORIZONTAL));

 //pane1.setAlignmentX(JLabel.CENTER_ALIGNMENT);
 layout->addWidget(pane1, 0, Qt::AlignCenter);
 layout->addWidget(new JSeparator(JSeparator::HORIZONTAL));

 //statusLabel.setAlignmentX(JLabel.CENTER_ALIGNMENT);
 layout->addWidget(statusLabel,0, Qt::AlignCenter);

 f->pack();
 if (log->isDebugEnabled()) log->debug("Tab-Programmer setup created");
 f->setVisible(true);
}
/*public*/
/*protected*/ PaneProgAction::MyCombinedLocoSelTreePane::MyCombinedLocoSelTreePane(PaneProgAction* act, QLabel * statusLabel, ProgModeSelector* modePane, QWidget* parent)
    : CombinedLocoSelTreePane(statusLabel, modePane, parent)
{
 this->act = act;
}

void PaneProgAction::MyCombinedLocoSelTreePane::startProgrammer(DecoderFile* decoderFile, RosterEntry* re, QString filename)
{
 QString title = tr("Program %1 in Service Mode (Programming Track)").arg("new decoder");
 if (re!=NULL) title = tr("Program %1 in Service Mode (Programming Track)").arg(re->getId());
 JFrame* p = new PaneServiceProgFrame(decoderFile, re, title, "programmers"+QString(QDir::separator())+filename+".xml", act->modePane->getProgrammer());
 p->pack();
 p->setVisible(true);

    // f.setVisible(false);
    // f.dispose();
}
#if 0
void PaneProgAction::windowClosing(QCloseEvent *we)
{
 statusLabel->setText(tr("Idle"));
 f->windowClosing(we);
}

PPAWindowListener::PPAWindowListener(JFrame *p, PaneProgAction* ppa)
{
 this->p = p;
 this->ppa = ppa;
}
void PPAWindowListener::windowClosing(QCloseEvent *)
{
 //ppa->handleQuit();
}
#endif
