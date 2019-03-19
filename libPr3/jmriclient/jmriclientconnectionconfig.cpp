#include "jmriclientconnectionconfig.h"
#include "networkportadapter.h"
#include "networkdriveradapter.h"
#include "jtextfield.h"
#include "jmriclientsystemconnectionmemo.h"
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include <QCheckBox>
#include <QLabel>

/**
 * Definition of objects to handle configuring a connection to a remote JMRI
 * instance via the JMRI Network Protocol.
 *
 * @author Paul Bender Copyright (C) 2010
  */
// /*public*/ class ConnectionConfig extends jmri.jmrix.AbstractNetworkConnectionConfig {


/**
 * Constructor for an object being created during load process; Swing init
 * is deferred.
 */
/*public*/ JmriClientConnectionConfig::JmriClientConnectionConfig(NetworkPortAdapter* p)
 : AbstractNetworkConnectionConfig(p)
{
    //super(p);
 common();
}

/**
 * Constructor for a functional Swing object with no preexisting adapter
 */
/*public*/JmriClientConnectionConfig:: JmriClientConnectionConfig() {
   // super();
 common();
}

void JmriClientConnectionConfig::common()
{
 transmitPrefixLabel = new QLabel("Server Connection Prefix");
 transmitPrefixField = new JTextField(10);
}

//@Override
/*public*/ QString JmriClientConnectionConfig::name() {
    return "Simple Network Connection";
}

//@Override
/*protected*/ void JmriClientConnectionConfig::setInstance() {
    if (adapter == nullptr) {
        adapter = new NetworkDriverAdapter();
    }
}

//@Override
/*public*/ bool JmriClientConnectionConfig::isPortAdvanced() {
    return true;
}

//@Override
/*protected*/ void JmriClientConnectionConfig::checkInitDone() {
    AbstractNetworkConnectionConfig::checkInitDone();
    if (adapter->getSystemConnectionMemo() != nullptr) {
        transmitPrefixField->setText(((JMRIClientSystemConnectionMemo*) adapter->getSystemConnectionMemo())->getTransmitPrefix());
//        transmitPrefixField.addActionListener(new ActionListener() {
//            //@Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                ((JMRIClientSystemConnectionMemo) adapter.getSystemConnectionMemo()).setTransmitPrefix(transmitPrefixField.getText());
//                transmitPrefixField.setText(((JMRIClientSystemConnectionMemo) adapter.getSystemConnectionMemo()).getTransmitPrefix());
//            }
//        });
//        transmitPrefixField.addFocusListener(new FocusListener() {
//            //@Override
//            /*public*/ void focusLost(FocusEvent e) {
//                ((JMRIClientSystemConnectionMemo) adapter.getSystemConnectionMemo()).setTransmitPrefix(transmitPrefixField.getText());
//                transmitPrefixField.setText(((JMRIClientSystemConnectionMemo) adapter.getSystemConnectionMemo()).getTransmitPrefix());
//            }

//            //@Override
//            /*public*/ void focusGained(FocusEvent e) {
//            }
//        });
        connect(transmitPrefixField, SIGNAL(editingFinished()), this, SLOT(onTransmitPrefixField_editingFinished()));
        connect(transmitPrefixField, SIGNAL(leaveField()), this, SLOT(onTransmitPrefixField_left()));

    }
}


//@Override
/*protected*/ void JmriClientConnectionConfig::showAdvancedItems() {
    AbstractNetworkConnectionConfig::showAdvancedItems(); // we're adding to the normal advanced items.
    if (adapter->getSystemConnectionMemo() != nullptr) {
        cR->gridy += 2;
        cL->gridy += 2;
//        gbLayout->setConstraints(transmitPrefixLabel, *cL);
//        gbLayout->setConstraints(transmitPrefixField, *cR);
        ((GridBagLayout*)_details->layout())->addWidget(transmitPrefixLabel, *cL);
        ((GridBagLayout*)_details->layout())->addWidget(transmitPrefixField, *cR);
    }
    if (_details->parent() != nullptr) {
        _details->window()->update();
        _details->window()->repaint();
    }

}

//@Override
/*public*/ void JmriClientConnectionConfig::updateAdapter() {
    AbstractNetworkConnectionConfig::updateAdapter(); // we're adding more details to the connection.
    if (adapter->getSystemConnectionMemo() != nullptr) {
        ((JMRIClientSystemConnectionMemo*) adapter->getSystemConnectionMemo())->setTransmitPrefix(transmitPrefixField->text());
    }
}

//@Override
/*public*/ bool JmriClientConnectionConfig::isHostNameAdvanced() {
    return showAutoConfig->isChecked();
}

//@Override
/*public*/ bool JmriClientConnectionConfig::isAutoConfigPossible() {
    return true;
}
