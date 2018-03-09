#include "pisprognanoserialdriveradapter.h"

using namespace Sprog;

/**
 * Implements SerialPortAdapter for the Sprog system.
 * <P>
 * This connects an Pi-SPROG Nano via a serial com port or virtual USB serial
 * com port.
 * <P>
 * The current implementation only handles the 115,200 baud rate, and does not use
 * any other options at configuration time.
 *
 * @author	Andrew Crosland Copyright (C) 2016
 */
// /*public*/ class PiSprogNanoSerialDriverAdapter
//
/*public*/ PiSprogNanoSerialDriverAdapter::PiSprogNanoSerialDriverAdapter(QObject* parent)
 : SerialDriverAdapter(SprogConstants::SprogMode::OPS, 115200, parent)
{
    //super(SprogMode.OPS, 115200);
    options.insert("TrackPowerState", new Option(tr("Track Power At StartUp:"),
            QStringList() <<tr("Off") << tr("On"),
            true)); // first element (TrackPowerState) NOI18N
    //Set the username to match name, once refactored to handle multiple connections or user setable names/prefixes then this can be removed
    this->getSystemConnectionMemo()->setUserName(tr("Pi-SPROG Nano Command Station"));
}

/**
 * Get an array of valid baud rates. This is currently only 115,200 bps
 */
//@Override
/*public*/ QStringList PiSprogNanoSerialDriverAdapter::validBaudRates() {
    return QStringList() << "115,200 bps";
}

/**
 * @deprecated JMRI Since 4.4 instance() shouldn't be used, convert to JMRI multi-system support structure
 */
//@Deprecated
/*static*/ /*public*/ PiSprogNanoSerialDriverAdapter* PiSprogNanoSerialDriverAdapter::instance() {
    return NULL;
}
// private final static Logger log = LoggerFactory.getLogger(PiSprogNanoSerialDriverAdapter.class);
