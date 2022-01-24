#include "panenewprogaction.h"
#include "../../LayoutEditor/jmrijframe.h"
#include <QMenu>
#include <QMenuBar>
#include "rostermenu.h"
#include <QWidget>
#include <QBoxLayout>
#include "locoseltreepane.h"
#include "paneprogframe.h"

//PaneNewProgAction::PaneNewProgAction(QObject *parent) :
//    QAction(parent)
//{
//}
/**
 * Swing action to create and register a
 * frame for selecting the information needed to
 * open a PaneProgFrame for creating a new Roster entry.
 * <P>
 * The resulting JFrame
 * is constructed on the fly here, and has no specific type.
 *
 * @see  jmri.jmrit.symbolicprog.tabbedframe.PaneProgAction
 *
 * @author			Bob Jacobsen    Copyright (C) 2001, 2008
 * @version			$Revision: 18903 $
 */
///*public*/ class PaneNewProgAction extends AbstractAction {


//    static final java.util.ResourceBundle rbt = jmri.jmrit.symbolicprog.SymbolicProgBundle.bundle();

/*public*/ PaneNewProgAction::PaneNewProgAction(QObject *parent) : QAction(tr("DecoderPro service programmer"), parent)
{
    //this("DecoderPro service programmer");
    init();
}

/*public*/ PaneNewProgAction::PaneNewProgAction(QString s, QObject *parent) : QAction(s, parent)
{
    //super(s);
    init();
}
void PaneNewProgAction::init()
{
    log = new Logger("PaneNewProgAction");
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void PaneNewProgAction::actionPerformed(ActionEvent* /*e*/)
{
 if (log->isDebugEnabled()) log->debug("New roster entry programmer requested");

 // create the initial frame that steers
 JmriJFrameX* f = new JmriJFrameX(tr("New Roster Entry Setup"));
//    f->getContentPane().setLayout(new BoxLayout(f.getContentPane(), BoxLayout.Y_AXIS));
// QWidget* centralWidget = new QWidget;
// QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
// f->setCentralWidget(centralWidget);
// centralWidget->setLayout(centralWidgetLayout);
 f->setMinimumHeight(300);
 // add the Roster menu
 QMenuBar* menuBar = new QMenuBar();
 // menuBar.setBorder(new BevelBorder(BevelBorder.RAISED));
 QMenu* j = new QMenu(tr("File"));
//    j->addMenu(new PrintDecoderListAction(tr("Print decoder definitions..."), f, false));
//    j->addMenu(new PrintDecoderListAction(tr("Print Preview decoder definitions..."), f, true));
 menuBar->addMenu(j);
 menuBar->addMenu(new RosterMenu(tr("Roster"), RosterMenu::MAINMENU, f));
 f->setMenuBar(menuBar);

 QLabel* statusLabel = new QLabel;

 // new Loco on programming track
 QWidget* pane1 = new PNPLocoSelTreePane(statusLabel, NULL, NULL);
// {
//            protected void startProgrammer(DecoderFile decoderFile, RosterEntry re,
//                                            String filename) {
//                String title = tr("FrameNewEntryTitle");
//                JFrame p = new PaneProgFrame(decoderFile, re,
//                                             title, "programmers"+File.separator+filename+".xml",
//                                             null, false){
//                    protected JPanel getModePane() { return null; }
//                };
//                p.pack();
//                p.setVisible(true);

//            }
//        };

 // load primary frame

 //pane1.setAlignmentX(JLabel.CENTER_ALIGNMENT);
 pane1->setVisible(true);
 //f.getContentPane().add(pane1);
 f->setCentralWidget(pane1);
 pane1->layout()->addWidget(statusLabel);

 f->pack();
 if (log->isDebugEnabled()) log->debug("Tab-Programmer setup created");
 f->setVisible(true);
 QTimer::singleShot(50, f, SLOT(pack()));
}
PNPLocoSelTreePane::PNPLocoSelTreePane(QLabel* s, ProgModeSelector* selector, QWidget* parent) :
    LocoSelTreePane(s, selector, parent) {}

/*protected*/ void PNPLocoSelTreePane:: startProgrammer(DecoderFile* decoderFile, RosterEntry* re, QString filename)
{
 QString title = tr("Create New Roster Entry");
 JmriJFrame* p = new PNPPaneProgFrame(decoderFile, re, title, QString("programmers")+QString(QDir::separator())+filename+QString(".xml"), NULL, false);
// {
//        protected JPanel getModePane() { return null; }
//    };
 p->pack();
 p->setVisible(true);
}
PNPPaneProgFrame::PNPPaneProgFrame(DecoderFile* decoderFile, RosterEntry* re, QString frameTitle, QString filename,Programmer* pProg, bool opsMode, QWidget *parent)
    : PaneProgFrame(decoderFile, re, frameTitle, filename,pProg,opsMode, parent){}

JPanel* PNPPaneProgFrame::getModePane() {return NULL;}
