#include "signallingsourceframe.h"
#include <QVBoxLayout>
#include "signallingsourcepanel.h"

SignallingSourceFrame::SignallingSourceFrame(QWidget *parent) :
    JmriJFrame(false, true, parent)
{
}
/**
 * Frame for Signal Logic Source Mast status
 * @author	Kevin Dickerson   Copyright (C) 2011
 * @version $Revision: 17977 $
*/
///*public*/ class SignallingSourceFrame extends jmri.util.JmriJFrame {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.signalling.SignallingBundle");

///*public*/ SignallingSourceFrame() {
//    super(false, true);
//}


/*public*/ void SignallingSourceFrame::initComponents(SignalMast* source) throw (Exception)
{
 // the following code sets the frame's initial state
 sigPanel = new SignallingSourcePanel(source);

 setWindowTitle(tr("Signalling Pairs"));
 //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget();
 centralWidget->setLayout(new QVBoxLayout());
 setCentralWidget(centralWidget);


 centralWidget->layout()->addWidget(sigPanel);

//    addHelpMenu("package.jmri.jmrit.signalling.SignallingSourceFrame", true);

 // pack for display
 pack();
}
/*public*/ QString SignallingSourceFrame::getClassName()
{
 return "jmri.jmrit.signalling.SignallingSourceFrame";
}
