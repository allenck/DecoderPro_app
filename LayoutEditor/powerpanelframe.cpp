#include "powerpanelframe.h"
#include "powerpane.h"
#include <QLayout>
#include <QTimer>

//PowerPanelFrame::PowerPanelFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * Frame for controlling layout power via a PowerManager.
 *
 * @author		Bob Jacobsen   Copyright (C) 2001
 * @version             $Revision: 17977 $
 */
///*public*/ class PowerPanelFrame extends JmriJFrame {


/*public*/ PowerPanelFrame::PowerPanelFrame(QWidget *parent) : JmriJFrame(tr("Power Panel"), parent)
{
    //super(ResourceBundle.getBundle("jmri.jmrit.powerpanel.PowerPanelBundle").getString("TitlePowerPanel"));
 pane	= new PowerPane();
    // general GUI config

 // install items in GUI
 //getContentPane()->layout()->addWidget(pane);
 setCentralWidget(pane);

 // add help menu to window
 addHelpMenu("package.jmri.jmrit.powerpanel.PowerPanelFrame", true);
 setTitle(pane->getTitle());
 setMaximumSize(300, 50);

 adjustSize();
 pane->setVisible(true);
 //QTimer::singleShot(50, this, SLOT(pack()));
}

/*public*/ void PowerPanelFrame::dispose() {
    pane->dispose();
    JmriJFrame::dispose();
}

/*public*/ QString PowerPanelFrame::getClassName()
{
 return "jmri.jmrit.powerpanel.PowerPanelFrame";
}

