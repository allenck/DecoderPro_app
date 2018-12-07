#ifndef RFIDPANELINTERFACE_H
#define RFIDPANELINTERFACE_H
#include <QObject>
#include "rfidsystemconnectionmemo.h"

/**
 * JPanel interface to handle providing system connection information to a
 * panel.
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
/*public*/ /*interface*/class  RfidPanelInterface  : public QObject
{
 Q_OBJECT
public:
    /**
     * 2nd stage of initialisation, invoked after the constructor is complete.
     * <p>
     * This needs to be connected to the initContext() method in implementing
     * classes.
     * @param memo SystemConnectionMemo for configured RFID system
     */
 /*public*/ virtual void initComponents(RfidSystemConnectionMemo* memo) {}

};
#endif // RFIDPANELINTERFACE_H
