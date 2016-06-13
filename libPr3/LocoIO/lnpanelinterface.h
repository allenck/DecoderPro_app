#ifndef LNPANELINTERFACE_H
#define LNPANELINTERFACE_H
#include <QObject>
#include "libPr3_global.h"

class LocoNetSystemConnectionMemo;
class LIBPR3_GLOBAL_H LnPanelInterface : public QObject
{
public:
 LnPanelInterface(QObject* parent= 0): QObject(parent) {}
 /**
     * 2nd stage of initialization, invoked after the constuctor is complete.
     * <p>
     * This needs to be connected to the initContext() method in implementing
     * classes.
     */
    virtual /*public*/ void initComponents(LocoNetSystemConnectionMemo* memo) { return; }
};

#endif // LNPANELINTERFACE_H
