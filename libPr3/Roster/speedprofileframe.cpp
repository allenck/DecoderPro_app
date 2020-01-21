#include "speedprofileframe.h"
#include "speedprofilepanel.h"
#include <QPushButton>
#include <QBoxLayout>

//SpeedProfileFrame::SpeedProfileFrame(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
/**
 * Frame Entry Exit Frames
 *
 * @author	Kevin Dickerson Copyright (C) 2011
 * @version $Revision: 1.5 $
 */
// /*public*/ class SpeedProfileFrame extends jmri.util.JmriJFrame {

/**
 *
 */
//private static final long serialVersionUID = 665383251598012193L;

/*public*/ SpeedProfileFrame::SpeedProfileFrame(QWidget *parent) :
  JmriJFrame(false, true, parent) {
    //super(false, true);
}


/*public*/ void SpeedProfileFrame::initComponents() /*throws Exception*/ {
 // the following code sets the frame's initial state

 spPanel = new SpeedProfilePanel();

 setTitle(tr("Speed Profile"));
 //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

 //getContentPane().add(spPanel);
 setCentralWidget(spPanel);

 addHelpMenu("package.jmri.jmrit.roster.swing.speedprofile.SpeedProfileFrame", true);

 // pack for display
 pack();
}
/*public*/ QString SpeedProfileFrame::getClassName()
{
 return "jmri.jmrit.roster.swing.speedprofile.SpeedProfileFrame";
}
