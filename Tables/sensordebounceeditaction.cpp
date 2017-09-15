#include "sensordebounceeditaction.h"
#include "jtextfield.h"
#include <QCheckBox>
#include "proxysensormanager.h"
#include "instancemanager.h"
#include "beanitempanel.h"
#include "sensor.h"
#include <QIntValidator>
#include "beanedititem.h"

SensorDebounceEditAction::SensorDebounceEditAction(QObject *parent) :
  BeanEditAction(parent)
{
 sensorDebounceInactiveField = new JTextField(5);
 sensorDebounceInactiveField->setValidator(new QIntValidator());
 sensorDebounceActiveField = new JTextField(5);
 sensorDebounceActiveField->setValidator(new QIntValidator());
 sensorDebounceGlobalCheck = new QCheckBox();
}
/**
 * Provides an edit panel for a sensor debounce object This is designed so that
 * it can be re-used in other panels.
 *
 * @author	Kevin Dickerson Copyright (C) 2011
 * @version	$Revision: 19923 $
 */
///*public*/ class SensorDebounceEditAction extends BeanEditAction {

/**
 *
 */
//private static final long serialVersionUID = -3622370435108538307L;

/*public*/ QString SensorDebounceEditAction::helpTarget() {
    return "package.jmri.jmrit.beantable.SensorTable";
} //IN18N

/*public*/ QString SensorDebounceEditAction::getBeanType() {
    return tr("Sensor");
}

/*public*/ NamedBean* SensorDebounceEditAction::getByUserName(QString name) {
    return ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getByUserName(name);
}

//@Override
/*protected*/ void SensorDebounceEditAction::initPanels() {
}

//@Override
/*public*/ void SensorDebounceEditAction::setBean(NamedBean* bean) {
    BeanEditAction::setBean(bean);
    if (bean == NULL) {
        enabled(false);
    } else {
        resetDebounceItems(NULL); //Get this to retrieve the current details.
        enabled(true);
    }
}

/*public*/ BeanItemPanel* SensorDebounceEditAction::sensorDebounce(BeanItemPanel* basic) {
    if (basic == NULL) {
        basic = new BeanItemPanel();
        basic->setName(tr("SensorDebounce"));
    }

//    sensorDebounceGlobalCheck.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if (sensorDebounceGlobalCheck.isSelected()) {
//                sensorDebounceInactiveField.setEnabled(false);
//                sensorDebounceActiveField.setEnabled(false);
//            } else {
//                sensorDebounceInactiveField.setEnabled(true);
//                sensorDebounceActiveField.setEnabled(true);
//            }
//        }
//    });
    connect(sensorDebounceGlobalCheck, SIGNAL(clicked()), this, SLOT(on_sensorDebounceGlobalCheck_clicked()));

//    sensorDebounceInactiveField.addKeyListener(new KeyListener() {
//        /*public*/ void keyPressed(KeyEvent keyEvent) {
//        }

//        /*public*/ void keyReleased(KeyEvent keyEvent) {
//            String text = sensorDebounceInactiveField.getText();
//            if (!validateNumericalInput(text)) {
//                String msg = java.text.MessageFormat.format(tr("ShouldBeNumber"), new Object[]{tr("SensorInActiveDebounce")});
//                jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class).showInfoMessage(tr("ErrorTitle"), msg, "Block Details", "Inactive", false, false);
//            }
//        }

//        /*public*/ void keyTyped(KeyEvent keyEvent) {
//        }
//    });

//    sensorDebounceActiveField.addKeyListener(new KeyListener() {
//        /*public*/ void keyPressed(KeyEvent keyEvent) {
//        }

//        /*public*/ void keyReleased(KeyEvent keyEvent) {
//            String text = sensorDebounceActiveField.getText();
//            if (!validateNumericalInput(text)) {
//                String msg = java.text.MessageFormat.format(tr("ShouldBeNumber"), new Object[]{tr("SensorActiveDebounce")});
//                jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class).showInfoMessage(tr("ErrorTitle"), msg, "Block Details", "Active", false, false);
//            }
//        }

//        /*public*/ void keyTyped(KeyEvent keyEvent) {
//        }
//    });

    basic->addItem(new BeanEditItem(NULL, NULL, tr(" The debounce timers add a delay before the sensor change state is reported, this helps to prevent false reporting due to dirty wheels etc")));
    basic->addItem(new BeanEditItem(sensorDebounceGlobalCheck, tr("Use Global Debounce Values"), NULL));
    basic->addItem(new BeanEditItem(sensorDebounceInactiveField, tr("Sensor InActive Debounce"), tr("The delay in milli seconds before reporting the sensor as Inactive")));
    basic->addItem(new BeanEditItem(sensorDebounceActiveField, tr("Sensor Active Debounce"), tr("The delay in milli seconds before reporting the sensor as Active")));

//    basic.setSaveItem(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -4211002470804824662L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            saveDebounceItems(e);
//        }
//    });
    basic->setSaveItem(new SaveItemAction(this));

//    basic.setResetItem(new AbstractAction() {
//        /**
//         *
//         */
//        private static final long serialVersionUID = -9107982698145419220L;

//        /*public*/ void actionPerformed(ActionEvent e) {
//            resetDebounceItems(e);
//        }
//    });
    basic->setResetItem(new ResetItemAction(this));
    return basic;
};

void SensorDebounceEditAction::on_sensorDebounceGlobalCheck_clicked()
{
 if (sensorDebounceGlobalCheck->isChecked()) {
     sensorDebounceInactiveField->setEnabled(false);
     sensorDebounceActiveField->setEnabled(false);
 } else {
     sensorDebounceInactiveField->setEnabled(true);
     sensorDebounceActiveField->setEnabled(true);
 }

}

/*protected*/ void SensorDebounceEditAction::saveDebounceItems(ActionEvent* /*e*/) {
    if (bean == NULL) {
        return;
    }

    Sensor* sen = (Sensor*) bean;
    QString timeVal = sensorDebounceActiveField->text();
    int time = timeVal.toInt();
    sen->setSensorDebounceGoingActiveTimer(time);

    timeVal = sensorDebounceInactiveField->text();
    time = timeVal.toInt();
    sen->setSensorDebounceGoingInActiveTimer(time);
    sen->useDefaultTimerSettings(sensorDebounceGlobalCheck->isChecked());
}

/*protected*/ void SensorDebounceEditAction::resetDebounceItems(ActionEvent* /*e*/) {
    if (bean == NULL) {
        enabled(false);
        return;
    }
    enabled(true);
    Sensor* sen = (Sensor*) bean;
    sensorDebounceGlobalCheck->setChecked(sen->useDefaultTimerSettings());
    if (sen->useDefaultTimerSettings()) {
        sensorDebounceActiveField->setEnabled(false);
        sensorDebounceInactiveField->setEnabled(false);
    } else {
        sensorDebounceActiveField->setEnabled(true);
        sensorDebounceInactiveField->setEnabled(true);
    }
    sensorDebounceActiveField->setText("" + sen->getSensorDebounceGoingActiveTimer());
    sensorDebounceInactiveField->setText("" + sen->getSensorDebounceGoingInActiveTimer());
}

/*public*/ void SensorDebounceEditAction::enabled(bool boo) {
    sensorDebounceGlobalCheck->setEnabled(boo);
    sensorDebounceInactiveField->setEnabled(boo);
    sensorDebounceActiveField->setEnabled(boo);

}
