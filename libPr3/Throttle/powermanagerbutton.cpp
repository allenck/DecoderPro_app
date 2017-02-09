#include "powermanagerbutton.h"
#include "instancemanager.h"
#include "../../LayoutEditor/powerpane.h"
#include "abstractpowermanager.h"

PowerManagerButton::PowerManagerButton(QWidget *parent) :
    QToolButton(parent)
{
 powerControl = new PowerPane();
 powerMgr = NULL;
 fullText = false;
 log = new Logger("PowerManagerButton");
}
// /*public*/ abstract class PowerManagerButton extends JButton implements PropertyChangeListener {

    //static final ResourceBundle pprb = ResourceBundle.getBundle("jmri.jmrit.powerpanel.PowerPanelBundle");

///*public*/ PowerManagerButton() {
//    this(false);
//}

/*public*/ PowerManagerButton::PowerManagerButton(bool fullText, QWidget */*parent*/)
{
 powerControl = new PowerPane();
 powerMgr = NULL;
 this->fullText = fullText;
 log = new Logger("PowerManagerButton");
 powerMgr = InstanceManager::powerManagerInstance();
 if (powerMgr == NULL)
 {
  log->info("No power manager instance found, panel not active");
 }
 else
 {
   //powerMgr.addPropertyChangeListener(this);
  AbstractPowerManager* apm = (AbstractPowerManager*)powerMgr;
   connect(apm->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 //loadIcons(); // can't do this here
 QTimer::singleShot(10,this, SLOT(init()));
//  addActionListener(new ActionListener() {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            try {
//                if (powerMgr.getPower() == PowerManager.ON) {
//                    powerControl.offButtonPushed();
//                } else if (powerMgr.getPower() == PowerManager.OFF) {
//                    powerControl.onButtonPushed();
//                } else if (powerMgr.getPower() == PowerManager.UNKNOWN) {
//                    powerControl.offButtonPushed();
//                }
//            } catch (JmriException ex) {
//                setIcon(powerXIcon);
//            }
//        }
//    });
 connect(this, SIGNAL(clicked()), this, SLOT(OnClicked()));
 //setPowerIcons();
}

void PowerManagerButton::init()
{
 loadIcons();
 setPowerIcons();
}

void PowerManagerButton::OnClicked()
{
 try
 {
    if (powerMgr->getPower() == PowerManager::ON)
    {
        powerControl->offButtonPushed();
    } else if (powerMgr->getPower() == PowerManager::OFF) {
        powerControl->onButtonPushed();
    } else if (powerMgr->getPower() == PowerManager::UNKNOWN) {
        powerControl->offButtonPushed();
    }
} catch (JmriException ex) {
    setIcon(powerXIcon);
}

}

/*public*/ void PowerManagerButton::dispose()
{
 if (powerMgr != NULL)
 {
  //powerMgr.removePropertyChangeListener(this);
  disconnect(powerMgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

/*abstract*/ void PowerManagerButton::loadIcons() {}

//@Override
/*public*/ void PowerManagerButton::propertyChange(PropertyChangeEvent* /*evt*/)
{
 setPowerIcons();
}

/*protected*/ void PowerManagerButton::setPowerIcons()
{
 if (powerMgr == NULL)
 {
  return;
 }
 try
 {
  if (powerMgr->getPower() == PowerManager::ON)
  {
    setIcon(powerOnIcon);
    setToolTip(tr("Layout Power On. Click to turn off."));
    if (fullText) {
        setText(tr("On"));
    }
} else if (powerMgr->getPower() == PowerManager::OFF) {
    setIcon(powerOffIcon);
    setToolTip(tr("Layout Power Off. Click to turn on."));
    if (fullText) {
        setText(tr("Off"));
    }
} else if (powerMgr->getPower() == PowerManager::UNKNOWN) {
    setIcon(powerXIcon);
    setToolTip(tr("Layout Power state unknown. Click to turn off."));
    if (fullText) {
        setText(tr("Unknown"));
    }
} else {
    setIcon(powerXIcon);
    setToolTip(tr("Layout Power state unknown. Click to turn off."));
    log->error("Unexpected state value: +" + powerMgr->getPower());
    if (fullText) {
        setText(tr("Unknown"));
   }
  }
 }
 catch (JmriException ex)
 {
 setIcon(powerXIcon);
 setToolTip(tr("Layout Power state unknown. Click to turn off."));
  if (fullText)
  {
   setText(tr("Unknown"));
  }
 }
}
