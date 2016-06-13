#include "signallingframe.h"
#include <QVBoxLayout>
#include "signallingpanel.h"

//SignallingFrame::SignallingFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * Frame for the Signalling Logic
 * @author	Kevin Dickerson   Copyright (C) 2011
 * @version $Revision: 17977 $
*/
///*public*/ class SignallingFrame extends jmri.util.JmriJFrame {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.signalling.SignallingBundle");

/*public*/ SignallingFrame::SignallingFrame(QWidget *parent) : JmriJFrame(false, true, parent)
{
 //super(false, true);
}


/*public*/ void SignallingFrame::initComponents(SignalMast* source, SignalMast* dest) throw (Exception)
{
    // the following code sets the frame's initial state
    sigPanel = new SignallingPanel(source, dest, (QFrame*)this);

    setWindowTitle(tr("Signalling Pairs"));
    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(new QVBoxLayout());
    setCentralWidget(centralWidget);
    //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

    centralWidget->layout()->addWidget(sigPanel);

    addHelpMenu("package.jmri.jmrit.signalling.AddEditSignallingLogic", true);

    resize(600, 800);
    // pack for display
    pack();
}
