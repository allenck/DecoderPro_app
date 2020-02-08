#include "locobufferiiadapter.h"

/**
 * Update the code in jmri.jmrix.loconet.locobuffer so that it refers to the
 * switch settings on the new LocoBuffer-II.
 *
 * @author Bob Jacobsen Copyright (C) 2004
 */
///*public*/ class LocoBufferIIAdapter extends LocoBufferAdapter {

    /*public*/ LocoBufferIIAdapter::LocoBufferIIAdapter(LocoNetSystemConnectionMemo* adapterMemo, QObject* parent)
      : LocoBufferAdapter(adapterMemo)
    {
        //super(adapterMemo);
    }

    /*public*/ LocoBufferIIAdapter::LocoBufferIIAdapter(QObject* parent)
      : LocoBufferAdapter(new LocoNetSystemConnectionMemo())
    {
        //this(new LocoNetSystemConnectionMemo());
    }

    /**
     * {@inheritDoc}
     * This is modified to have different comments. Because the speeds are the same as
     * the parent class (19200 and 57600), we don't override validBaudNumbers().
     */
    //@Override
    /*public*/ QStringList LocoBufferIIAdapter::validBaudRates() {
        return QStringList() << "Baud19200LBII" << tr("57,600 baud (Sw1 on, Sw3 off)");
    }

    /**
     * Get a String that says what Option 1 represents.
     */
    /*public*/ QString LocoBufferIIAdapter::option1Name() {
        return tr("%1 connectionU uses:").arg("LocoBuffer-II");
    }
