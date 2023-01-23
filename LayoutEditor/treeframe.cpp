#include "treeframe.h"
#include <QVBoxLayout>
#include "treepanel.h"

TreeFrame::TreeFrame(QWidget* parent) : JmriJFrame(parent)
{
 setFrameRef(getClassName());

}
/**
 * Frame for controlling JInput access to USN
 *
 * @author	Bob Jacobsen Copyright (C) 2008
  */
// /*public*/ class TreeFrame extends JmriJFrame {

    //ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrix.jinput.treecontrol.TreeBundle");

//@Override
/*public*/ void TreeFrame::initComponents() //throws Exception
{

    // set the frame's initial state
    setTitle(tr("USB Assignments"));

    QWidget* contentPane = getContentPane();
    QVBoxLayout* thisLayout;
    contentPane->setLayout(thisLayout = new QVBoxLayout()); //new BoxLayout(contentPane, BoxLayout.Y_AXIS));

    // add only content pane
    thisLayout->addWidget(new Usb::TreePanel());

    // add help menu
    addHelpMenu("package.jmri.jmrix.jinput.treecontrol.TreeFrame", true);

    // pack for displaytree
    pack();
}

/*public*/ QString TreeFrame::getClassName()
{
 return "jmri.jmrix.jinput.treecontrol.TreeFrame";
}
