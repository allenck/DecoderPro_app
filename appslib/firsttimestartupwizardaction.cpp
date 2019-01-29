#include "firsttimestartupwizardaction.h"
#include "jmrijframe.h"
#include "apps3.h"
#include "firsttimestartupwizard.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>

// /*public*/ class FirstTimeStartUpWizardAction extends jmri.util.swing.JmriAbstractAction {

/*public*/ FirstTimeStartUpWizardAction::FirstTimeStartUpWizardAction(QString s, WindowInterface* wi, QObject* parent) : JmriAbstractAction(s,wi) {
    //super(s, wi);
 common();
}

/*public*/ FirstTimeStartUpWizardAction::FirstTimeStartUpWizardAction(QString s, QIcon i, WindowInterface* wi) : JmriAbstractAction(s,i,wi)
{
   // super(s, i, wi);
    common();
}

/*public*/ FirstTimeStartUpWizardAction::FirstTimeStartUpWizardAction(QString s, QObject* parent) : JmriAbstractAction(s, parent){
    //super(s);
 common();
}

void FirstTimeStartUpWizardAction::common()
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* FirstTimeStartUpWizardAction::makePanel() {
    throw  IllegalArgumentException("Should not be invoked");
}

/*static*/ JmriJFrame* FirstTimeStartUpWizardAction::f = nullptr;


/*public*/ void FirstTimeStartUpWizardAction::setApp(Apps3* app) {
    this->app = app;
}

/*public*/ void FirstTimeStartUpWizardAction::actionPerformed(ActionEvent* e) {
    // create the JTable model, with changes for specific NamedBean
    // create the frame
    if (f == nullptr) {
        f = new JmriJFrame("Decoder Pro Wizard", false, false);
        // Update the GUI Look and Feel
        // This is needed as certain controls are instantiated
        // prior to the setup of the Look and Feel
//        SwingUtilities.updateComponentTreeUI(f);
    }
    FirstTimeStartUpWizard* wiz = new FirstTimeStartUpWizard(f, app);
    f->resize(QSize(700, 400));
    f->setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
    f->getContentPane()->setLayout(new QVBoxLayout());
    f->getContentPane()->layout()->addWidget(wiz->getPanel());
    f->pack();

    QRect screenDim
             = QApplication::desktop()->screenGeometry();;
    QRect winDim = screenDim;
    //QRect winDim = f->getBounds();
    winDim.setHeight(winDim.height() + 10);
    winDim.setWidth(winDim.width() + 10);
    f->setLocation((screenDim.width() - winDim.width()) / 2,
            (screenDim.height() - winDim.height()) / 2);
    f->resize(winDim.width(), winDim.height());

    f->setVisible(true);
}

////@Override
///*public*/ void FirstTimeStartUpWizardAction::actionPerformed(ActionEvent* e) {
//    actionPerformed();
//}

