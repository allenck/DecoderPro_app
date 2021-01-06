#include "sensoreditaction.h"

SensorEditAction::SensorEditAction()
{

}
/**
 * Provides an edit panel for a Sensor object.
 *
 * @author Kevin Dickerson Copyright (C) 2011
 */
// /*public*/ class SensorEditAction extends BeanEditAction<Sensor> {

    //@Override
    /*public*/ QString SensorEditAction::helpTarget() {
        return "package.jmri.jmrit.beantable.SensorAddEdit";
    } // NOI18N

#if 0
    //@Override
    /*protected*/ void initPanels() {
        super.initPanels();
        debounce = new SensorDebounceEditAction();
        debounce.setBean(bean);
        bei.add(debounce.sensorDebounce(null));
        pullup = new SensorPullUpEditAction();
        pullup.setBean(bean);
        bei.add(pullup.sensorPullUp(null));
    }

    @Override
    /*public*/ String getBeanType() {
        return Bundle.getMessage("BeanNameSensor");
    }

    @Override
    /*public*/ Sensor getByUserName(String name) {
        return InstanceManager.sensorManagerInstance().getByUserName(name);
    }

    JCheckBox inverted = new JCheckBox();

    @Override
    BeanItemPanel basicDetails() {
        BeanItemPanel basic = super.basicDetails();

        basic.addItem(new BeanEditItem(inverted, Bundle.getMessage("Inverted"), Bundle.getMessage("SensorInvertedToolTip")));

        return basic;
    }

    @Override
    protected void saveBasicItems(ActionEvent e) {
        super.saveBasicItems(e);
        bean.setInverted(inverted.isSelected());
    }

    //@Override
    /*protected*/ void resetBasicItems(JActionEvent* e) {
        super.resetBasicItems(e);
        inverted.setSelected(bean.getInverted());
    }
#endif
