#include "addentryexitpairframe.h"
#include <QMenu>
#include <QMenuBar>
#include "layouteditor.h"
#include <QBoxLayout>
#include "addentryexitpairpanel.h"

/**
 * Frame Entry Exit Frames
 *
 * @author	Kevin Dickerson Copyright (C) 2011
 * @version $Revision: 1.5 $
 */
///*public*/ class AddEntryExitPairFrame extends jmri.util.JmriJFrame {

/**
 *
 */
//private static final long serialVersionUID = -1133603057019255324L;

/*public*/ AddEntryExitPairFrame::AddEntryExitPairFrame(QWidget *parent) :
  JmriJFrame(false, true, parent)
{
 //super(false, true);
 setFrameRef(getClassName());

}


/*public*/ void AddEntryExitPairFrame::initComponents(LayoutEditor* panel) //throws Exception
{
 // the following code sets the frame's initial state

 nxPanel = new AddEntryExitPairPanel(panel);

 setTitle("Add Entry Exit Points");
 //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget;
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
 setCentralWidget(centralWidget);

centralWidgetLayout->addWidget(nxPanel);

 QMenuBar* menuBar = new QMenuBar();//getJMenuBar();
 QAction* options = new QAction(tr("Options"), this);
 menuBar->addAction(options);
// options.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent event) {
//         nxPanel.optionWindow(event);
//     }
// });
 connect(options, SIGNAL(triggered()), this, SLOT(on_options()));

 setMenuBar(menuBar);
 addHelpMenu("package.jmri.jmrit.signalling.EntryExitFrame", true);
 // pack for display
 adjustSize();
}

void AddEntryExitPairFrame::on_options()
{
 nxPanel->optionWindow();
}
/*public*/ QString AddEntryExitPairFrame::getClassName()
{
 return "jmri.jmrit.entryexit.AddEntryExitPairFrame";
}
