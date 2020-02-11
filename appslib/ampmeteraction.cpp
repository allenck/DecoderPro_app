#include "ampmeteraction.h"
#include "instancemanager.h"
#include "ampmeterframe.h"

///*public*/ class AmpMeterAction extends AbstractAction {

/*public*/ AmpMeterAction::AmpMeterAction(QObject* parent) : AbstractAction(tr("Amp Meter"), parent){
    //this(Bundle.getMessage("MenuItemAmpMeter"));
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/*public*/ AmpMeterAction::AmpMeterAction(QString s, QObject* parent) : AbstractAction(s, parent){
    //super(s);
    // disable ourself if no MultiMeter available
    if (InstanceManager::getNullableDefault("MultiMeter") == nullptr) {
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void AmpMeterAction::actionPerformed(/*ActionEvent e*/) {

    AmpMeterFrame* f = new AmpMeterFrame();
    f->initComponents();
    f->setVisible(true);
}


