#include "addsignalmastjframe.h"
#include "signalmast.h"
#include <QBoxLayout>
#include "addsignalmastpanel.h"

//AddSignalMastJFrame::AddSignalMastJFrame()
//{

//}
/**
 * JFrame to create a new SignalMast
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * @version $Revision$
 */
///*public*/ class AddSignalMastJFrame extends JmriJFrame {

/**
 *
 */
//private static final long serialVersionUID = -6193330521542648003L;

/*public*/ AddSignalMastJFrame::AddSignalMastJFrame(QWidget* parent)
: JmriJFrame(tr("TitleAddSignalMast"), false, true)
{
    //super(Bundle.getMessage("TitleAddSignalMast"), false, true);
    AddSignalMastPanel* sigMastPanel = NULL;


    addHelpMenu("package.jmri.jmrit.beantable.SignalMastAddEdit", true);
    getContentPane()->setLayout(new QVBoxLayout); //(this.getContentPane(), BoxLayout.Y_AXIS));

    getContentPane()->layout()->addWidget(sigMastPanel = new AddSignalMastPanel());
    adjustSize();
}

/*public*/ AddSignalMastJFrame::AddSignalMastJFrame(SignalMast* mast, QWidget* parent)
    : JmriJFrame(tr("TitleAddSignalMast"), false, true)
{
    //super(Bundle.getMessage("TitleAddSignalMast"), false, true);

    addHelpMenu("package.jmri.jmrit.beantable.SignalMastAddEdit", true);
    getContentPane()->setLayout(new QVBoxLayout); //(this.getContentPane(), BoxLayout.Y_AXIS));

    getContentPane()->layout()->addWidget(new AddSignalMastPanel(mast));
    adjustSize();
}


/*public*/ void AddSignalMastJFrame::refresh() {
    if (sigMastPanel != NULL) {
        sigMastPanel->updateSelectedDriver();
        sigMastPanel->refreshHeadComboBox();

    }
}
