#include "paneeditaction.h"
#include "../../LayoutEditor/jmrijframe.h"
#include <QBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include "rostermenu.h"
#include <QDir>

//PaneEditAction::PaneEditAction(QObject *parent) :
//    QAction(parent)
//{
//}
/**
 * Swing action to create and register a
 * frame for selecting the information needed to
 * open a PaneProgFrame just for editing, without a programmer.
 * <P>
 * The resulting JFrame
 * is constructed on the fly here, and has no specific type.
 *
 *
 * @author			Bob Jacobsen    Copyright (C) 2008
 * @version			$Revision: 18903 $
 */
// /*public*/ class PaneEditAction 	extends AbstractAction {


//    static final java.util.ResourceBundle rbt = jmri.jmrit.symbolicprog.SymbolicProgBundle.bundle();

/*public*/ PaneEditAction::PaneEditAction(QObject *parent) : QAction(tr("Edit Roster Entry"), parent)
{
 //this("Edit Roster Entry");
 init();
}

/*public*/ PaneEditAction::PaneEditAction(QString s, QObject *parent) :
        QAction(s, parent)
{
 //super(s);
 init();
}
void PaneEditAction::init()
{
 log = new Logger("PaneEditAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void PaneEditAction::actionPerformed(ActionEvent* e)
{

 if (log->isDebugEnabled()) log->debug("Pane programmer requested");

 // create the initial frame that steers
 JmriJFrame* f = new JmriJFrame(tr("Edit Roster Entry Setup"));
//    f.getContentPane().setLayout(new BoxLayout(f.getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget;
 f->setCentralWidget(centralWidget);
 QVBoxLayout* thisLayout;
 centralWidget->setLayout(thisLayout = new QVBoxLayout);

 // add the Roster menu
 QMenuBar* menuBar = new QMenuBar();
 // menuBar.setBorder(new BevelBorder(BevelBorder.RAISED));
 menuBar->addMenu(new RosterMenu(tr("Roster"),
                         RosterMenu::MAINMENU, f));
 f->setMenuBar(menuBar);

 // known entry, no programmer
//    QWidget* pane1 = new KnownLocoSelPane(false){  // not programming
//            protected void startProgrammer(DecoderFile decoderFile, RosterEntry re,
//                                            String filename) {
//                String title = tr("FrameEditEntryTitle");
//                JFrame p = new PaneProgFrame(decoderFile, re,
//                                             title, "programmers"+File.separator+filename+".xml",
//                                             null, false){
//                    protected JPanel getModePane() { return null; }
//                };
//                p.pack();
//                p.setVisible(true);

//        }
//    };
 QWidget* pane1 = new PEKnownLocoSelPane(false, this);

 // load primary frame
 //pane1.setAlignmentX(JLabel.CENTER_ALIGNMENT);
 thisLayout->addWidget(pane1);
 pane1->setVisible(true);

 f->pack();
 if (log->isDebugEnabled()) log->debug("Tab-Programmer setup created");
 f->setVisible(true);
}
PEKnownLocoSelPane::PEKnownLocoSelPane(bool ident, PaneEditAction *self) : KnownLocoSelPane(ident )
{
 this->self = self;
}
void PEKnownLocoSelPane::startProgrammer(DecoderFile *decoderFile, RosterEntry *re, QString filename)
{
 QString title = tr("Edit Roster Entry");
// JFrame* p = new PaneProgFrame(decoderFile, re,
//         title, "programmers"+QDir::separator()+filename+".xml",
//         NULL, false){
//         /*protected*/ JPanel* getModePane() { return NULL; }
  JFrame* p = new PEPaneProgFrame(decoderFile, re,
        title, "programmers"+QString(QDir::separator())+filename+".xml",
         NULL, false);
  p->pack();
  p->setVisible(true);

}
PEPaneProgFrame::PEPaneProgFrame(DecoderFile *pDecoderFile, RosterEntry *pRosterEntry, QString frameTitle, QString programmerFile, Programmer *pProg, bool opsMode, QWidget *parent)
    : PaneProgFrame(pDecoderFile, pRosterEntry, frameTitle, programmerFile, pProg, opsMode, parent) {}
