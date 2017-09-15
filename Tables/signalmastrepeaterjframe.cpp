#include "signalmastrepeaterjframe.h"
#include "signalmastrepeaterpanel.h"
#include <QVBoxLayout>

//SignalMastRepeaterJFrame::SignalMastRepeaterJFrame()
//{

//}
/**
 * JFrame to create a new SignalMast
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * @version $Revision: 19910 $
 */
///*public*/ class SignalMastRepeaterJFrame extends JmriJFrame {

/**
 *
 */
//private static final long serialVersionUID = -4168900880081275831L;

/*public*/ SignalMastRepeaterJFrame::SignalMastRepeaterJFrame(QWidget* parent)
 : JmriJFrame(tr("Signal Mast Repeater"), false, true, parent)
{
    sigMastPanel = NULL;
    //super(tr("Signal Mast Repeater"), false, true);

    addHelpMenu("package.jmri.jmrit.beantable.SignalMastRepeater", true);
    getContentPane()->setLayout(new QVBoxLayout); //(this.getContentPane(), BoxLayout.Y_AXIS));

    getContentPane()->layout()->addWidget(sigMastPanel = new SignalMastRepeaterPanel());
    pack();
}


