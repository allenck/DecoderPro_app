#include "powerpane.h"
#include <QLabel>
#include <QPushButton>
#include "powermanagermenu.h"
#include "powermanager.h"
#include <QGridLayout>
#include "abstractpowermanager.h"

//PowerPane::PowerPane(QWidget *parent) :
//    JmriPanel(parent)
//{
//}
/**
 * Pane for power control
 * @author	    Bob Jacobsen   Copyright (C) 2001, 2010
 * @version	    $Revision: 17977 $
 */
// /*public*/ class PowerPane extends jmri.util.swing.JmriPanel
//            implements java.beans.PropertyChangeListener {

/*public*/ QString PowerPane::getHelpTarget() {
    return "package.jmri.jmrit.powerpanel.PowerPanelFrame";
}
/*public*/ QString PowerPane::getTitle() {
    return tr("Power Control");
}

// GUI member declarations
//static ResourceBundle res = ResourceBundle.getBundle("jmri.jmrit.powerpanel.PowerPanelBundle");


/*public*/ QList<QMenu*> PowerPane::getMenus() {
    QList<QMenu*> list =  QList<QMenu*>();
    list.append(selectMenu);
    return list;
}


/*public*/ PowerPane::PowerPane(QWidget *parent) : JmriPanel(parent)
{
 log = new Logger("PowerPane");
 onOffStatus 	= new QLabel(tr("Unknown"));
 QPushButton* onButton 	= new QPushButton(tr("On"));
 QPushButton* offButton 	= new QPushButton(tr("Off"));
 listening = NULL;
 setVisible(false);

 selectMenu = new PowerManagerMenu();
//    {
//        protected void choiceChanged() {
//            managerChanged();
//        }
//    };

    // add listeners to buttons
//    onButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                onButtonPushed();
//            }
//        });
 connect(onButton, SIGNAL(clicked()), this, SLOT(onButtonPushed()));
//    offButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                offButtonPushed();
//            }
//        });
 connect(offButton, SIGNAL(clicked()), this, SLOT(offButtonPushed()));

    // general GUI config
    //setLayout(new jmri.util.javaworld.GridLayout2(2,2));
 QGridLayout* g;
 setLayout(g = new QGridLayout());

 // install items in GUI
 g->addWidget(new QLabel(tr("Layout Power:")),0,0,1,1);
 g->addWidget(onOffStatus,0,1,1,1);
 g->addWidget(onButton, 1,0,1,1);
 g->addWidget(offButton,1,1,1,1);

 setStatus();
}

void PowerPane::setStatus()
{
 // Check to see if the Power Manager has a current status
 if(mgrOK())
 {
  //try {
  if (listening->getPower()==PowerManager::ON) onOffStatus->setText(tr("On"));
  else if (listening->getPower()==PowerManager::OFF) onOffStatus->setText(tr("Off"));
  else if (listening->getPower()==PowerManager::UNKNOWN) onOffStatus->setText(tr("Unknown"));
  else {
    onOffStatus->setText(tr("Unknown"));
    log->error("Unexpected state value: +"+selectMenu->getManager()->getPower());
}
//        } catch (JmriException ex) {
//                onOffStatus.setText(tr("StatusUnknown"));
//        }
    }
}

void PowerPane::managerChanged() {
    if (listening!=NULL) listening->removePropertyChangeListener((PropertyChangeListener*)this);
//    if(listening) disconnect(listening, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    listening = NULL;
    setStatus();
}

/*private*/ bool PowerPane::mgrOK()
{
 if (listening == NULL)
 {
  listening = selectMenu->getManager();
  if (listening == NULL)
  {
   log->warn("No power manager instance found, panel not active");
   return false;
  }
  else
  {
   listening->addPropertyChangeListener((PropertyChangeListener*)this);
//   AbstractPowerManager* mgr = (AbstractPowerManager*)listening;
//   connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 }
 return true;
}

/*public*/ void PowerPane::onButtonPushed()
{
 if (mgrOK())
  //try {
  selectMenu->getManager()->setPower(PowerManager::ON);
//        } catch (JmriException e) {
//            log.error("Exception trying to turn power on " +e);
//        }
}

/*public*/ void PowerPane::offButtonPushed()
{
 if (mgrOK())
//        try {
  selectMenu->getManager()->setPower(PowerManager::OFF);
//        } catch (JmriException e) {
//            log->error("Exception trying to turn power off " +e);
//        }
}

/*public*/ void PowerPane::propertyChange(PropertyChangeEvent* ev)
{
 if(log->isDebugEnabled())
  log->debug(tr("PropertyChange received %1 old = %2, new = %3").arg(ev->getPropertyName()).arg(ev->getOldValue().toString()).arg(ev->getNewValue().toString()));
//    try {
 if (listening->getPower()==PowerManager::ON) onOffStatus->setText(tr("On"));
 else if (listening->getPower()==PowerManager::OFF) onOffStatus->setText(tr("Off"));
 else if (listening->getPower()==PowerManager::UNKNOWN) onOffStatus->setText(tr("Status Unknown"));
 else
 {
  onOffStatus->setText(tr("Status Unknown"));
  log->error("Unexpected state value: +"+listening->getPower());
 }
//    } catch (JmriException ex) {
//        onOffStatus.setText(tr("StatusUnknown"));
//    }
}

/*public*/ void PowerPane::dispose() {
    if (listening!=NULL) listening->removePropertyChangeListener((PropertyChangeListener*)this);
    //if (listening != NULL) disconnect(listening, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

}
