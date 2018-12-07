#include "rfidserialconnectionconfig.h"
#include "serialportadapter.h"
#include <QComboBox>
#include "rfidserialdriveradapter.h"
/**
 * Definition of objects to handle configuring a layout connection.
 *
 * @author Bob Jacobsen Copyright (C) 2003, 2006, 2007, 2008
 * @author Matthew Harris Copyright (C) 2011
 * @author B. Milhaupt    Copyright (C) 2017
 * @since 2.11.4
 */
// /*public*/ class ConnectionConfig extends jmri.jmrix.AbstractSerialConnectionConfig {

/**
 * Ctor for an object being created during load process; Swing init is
 * deferred.
 *
 * @param p {@link jmri.jmrix.SerialPortAdapter} to configure
 */
/*public*/RfidSerialConnectionConfig::RfidSerialConnectionConfig(SerialPortAdapter* p, QObject* parent) : AbstractSerialConnectionConfig(p, parent){
    //super(p);
}

/**
 * Ctor for a functional Swing object with no preexisting adapter.
 */
/*public*/ RfidSerialConnectionConfig::RfidSerialConnectionConfig(QObject *parent) : AbstractSerialConnectionConfig(parent) {
    //super();
}

//@SuppressWarnings("unchecked")
//@Override
/*public*/ void RfidSerialConnectionConfig::loadDetails(QWidget* details)
{
    AbstractSerialConnectionConfig::loadDetails(details);

    // Add a listener to the combo box
    //        ((QComboBox*) options.value(adapter->getOption1Name())->getComponent()).addActionListener(new ActionListener() {
    //            @Override
    //            /*public*/ void actionPerformed(ActionEvent e) {
    //                enableOpt2(options.get(adapter.getOption1Name()).getItem());
    //                enableOpt3(options.get(adapter.getOption1Name()).getItem());
    //                enableOpt4(options.get(adapter.getOption3Name()).getItem());
    //            }
    //        });
connect(((QComboBox*) options.value(adapter->getOption1Name())->getComponent()), SIGNAL(currentTextChanged(QString)), this, SLOT(optionBox1(QString)) );

    // Add a listener to the combo box
//        ((JComboBox<Option>) options.get(adapter.getOption3Name()).getComponent()).addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                enableOpt2(options.get(adapter.getOption1Name()).getItem());
//                enableOpt3(options.get(adapter.getOption1Name()).getItem());
//                enableOpt4(options.get(adapter.getOption3Name()).getItem());
//            }
//        });
connect(((QComboBox*)options.value(adapter->getOption3Name())->getComponent()), SIGNAL(currentTextChanged(QString)), this, SLOT(optionBox3(QString)));
    enableOpt2(options.value(adapter->getOption1Name())->getItem());
    enableOpt3(options.value(adapter->getOption1Name())->getItem());
    enableOpt4(options.value(adapter->getOption3Name())->getItem());
}

/*private*/ void RfidSerialConnectionConfig::enableOpt2(QVariant o) {
    bool enable =( o.toString() == ("MERG Concentrator")); // NOI18N
    options.value(adapter->getOption2Name())->getLabel()->setEnabled(enable);
    options.value(adapter->getOption2Name())->getComponent()->setEnabled(enable);
    options.value(adapter->getOption2Name())->getComponent()->setToolTip(enable
            ? tr("Choose RFID concentrator range setting")
            : tr("Range setting not applicable for selected RFID reader type"));
}

//@SuppressWarnings("unchecked")
/*private*/ void RfidSerialConnectionConfig::enableOpt3(QVariant o) {
    bool enable = !(o.toString()==("MERG Concentrator")); // NOI18N
    options.value(adapter->getOption3Name())->getLabel()->setEnabled(enable);
    options.value(adapter->getOption3Name())->getComponent()->setEnabled(enable);
    options.value(adapter->getOption3Name())->getComponent()->setEnabled(enable);
    options.value(adapter->getOption3Name())->getComponent()->setToolTip(enable
            ? tr("Choose RFID protocol")
            : tr("Protocol setting not applicable for selected RFID reader type"));
    if (!enable) {
        ((QComboBox*) options.value(adapter->getOption3Name())->getComponent())->setCurrentIndex(0);
    }
}

//@SuppressWarnings("unchecked")
/*private*/ void RfidSerialConnectionConfig::enableOpt4(QVariant o) {
    bool enable =( o.toString() == ("Olimex")); // NOI18N
    options.value(adapter->getOption4Name())->getLabel()->setEnabled(enable);
    options.value(adapter->getOption4Name())->getComponent()->setEnabled(enable);
    options.value(adapter->getOption4Name())->getComponent()->setEnabled(enable);
    options.value(adapter->getOption4Name())->getComponent()->setToolTip(enable
            ? tr("Choose RFID Reader model")
            : tr("Reader Model setting not applicable for selected RFID reader protocol"));
    if (!enable) {
        ((QComboBox*) options.value(adapter->getOption4Name())->getComponent())->setCurrentIndex(0);
    }
}
void RfidSerialConnectionConfig::optionBox1(QString)
{
 enableOpt2(options.value(adapter->getOption1Name())->getItem());
 enableOpt3(options.value(adapter->getOption1Name())->getItem());
 enableOpt4(options.value(adapter->getOption3Name())->getItem());
}

void RfidSerialConnectionConfig::optionBox3(QString)
{
  enableOpt2(options.value(adapter->getOption1Name())->getItem());
  enableOpt3(options.value(adapter->getOption1Name())->getItem());
  enableOpt4(options.value(adapter->getOption3Name())->getItem());
}

//@Override
/*public*/ QString RfidSerialConnectionConfig::name() {
    return "Direct Serial Connection";
}

//@Override
/*protected*/ void RfidSerialConnectionConfig::setInstance() {
    if (adapter == nullptr) {
        adapter = new RfidSerialDriverAdapter();
    }
}


