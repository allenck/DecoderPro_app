#include "lighteditaction.h"
#include "instancemanager.h"
#include "lightmanager.h"
#include "lightcontrolpane.h"
#include "lightintensitypane.h"
#include "beanitempanel.h"
#include "proxylightmanager.h"

LightEditAction::LightEditAction()
{

}
/**
 * Provides an edit panel for a Light object.
 *
 * @author Kevin Dickerson Copyright (C) 2011
 * @author Steve Young Copyright (C) 2021
 */
// /*public*/ class LightEditAction extends BeanEditAction<Light> {


//@Override
/*protected*/ void LightEditAction::initPanels() {
    if (InstanceManager::getNullableDefault("LightManager") == nullptr) {
        setEnabled(false);
    }
    BeanEditAction::initPanels();
    lightControlPanel();
    lightIntensityPanel();

    applyBut->setToolTip(tr("Click here to change this Light"));
}

//@Override
/*public*/ QString LightEditAction::helpTarget() {
    return "package.jmri.jmrit.beantable.LightAddEdit";
} // NOI18N

//@Override
/*public*/ NamedBean* LightEditAction::getByUserName(QString name) {
    return (NamedBean*)InstanceManager::lightManagerInstance()->getByUserName(name);
}

//@Override
/*protected*/ void LightEditAction::cancelButtonAction(/*ActionEvent e*/) {
    if (lcp!=nullptr) {
        lcp->dispose(); // ensures add / edit single LightControl Frame is closed
    }
    BeanEditAction::cancelButtonAction(/*e*/);
}

/**
 * Hide the Bean Properties Tab.
 * @return null
 */
//@Override
BeanItemPanel* LightEditAction::propertiesDetails() {
    return nullptr;
}

BeanItemPanel* LightEditAction::lightControlPanel() {
    BeanItemPanel* lcPanel = new BeanItemPanel();
    lcPanel->setName(tr("Light Controllers"));

    lcp = new LightControlPane((Light*)bean->self());
    lcPanel->layout()->addWidget(lcp);

//    lcPanel->setResetItem(new AbstractAction() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            lcp.setToLight(bean);
//        }
//    });
    lcPanel->setResetItem(new LEAResetAction(this));

//    lcPanel->setSaveItem(new AbstractAction() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            lcp.setLightFromControlTable(bean);
//        }
//    });
    lcPanel->setSaveItem(new LEASaveAction(this));
    bei.append(lcPanel);
    return lcPanel;
}

BeanItemPanel* LightEditAction::lightIntensityPanel() {
    BeanItemPanel* liPanel = new BeanItemPanel();
    liPanel->setName(tr("LightVariableBorder"));
    lip = new LightIntensityPane(true);
    lip->setToLight((Light*)bean->self());
    liPanel->layout()->addWidget(lip);

//    liPanel.setResetItem(new AbstractAction() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            lip.setToLight(bean);
//        }
//    });
    liPanel->setResetItem(new LEAResetAction(this));

//    liPanel.setSaveItem(new AbstractAction() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if (bean instanceof VariableLight) {
//                lip.setLightFromPane((VariableLight)bean);
//            }
//        }
//    });
    liPanel->setSaveItem(new LEASaveAction(this));
    bei.append(liPanel);

    if (!(qobject_cast<VariableLight*>(bean->self()))) {
        liPanel->setEnabled(false);
        liPanel->setToolTip(tr("%1 Lights do not support Variable Intensity.").arg(getBeanManagerSystemUserName()));
    }
    return liPanel;
}

/**
 * Get Bean Manager System UserName.
 * Human readable form of System Username.
 * e.g. "Internal", "MERG"
 *
 * @return Manager UserName, else empty String.
 */
//@Nonnull
/*private*/ QString LightEditAction::getBeanManagerSystemUserName(){
    //Manager<Light> lm = InstanceManager.getDefault(LightManager.class);
 LightManager* lm = (LightManager*)InstanceManager::getDefault("LightManager");
    if (qobject_cast<ProxyManager*>(lm->self())){
        ProxyLightManager* plm = (ProxyLightManager*)lm;
        for (Manager* m : plm->getManagerList()) {
            if (m->getBySystemName(bean->getSystemName())!=nullptr) {
                return m->getMemo()->getUserName();
            }
        }
    }
    return "";
}
