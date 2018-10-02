#ifndef SLOTLISTENER_H
#define SLOTLISTENER_H

#include <QObject>
#include "loconetslot.h"

class LocoNetSlot;
class SlotListener : public QObject
{
    Q_OBJECT
public slots:
    //explicit SlotListener(QObject *parent = 0);
    /**
     * Interface for objects that want to be notified when a
     * {@link jmri.jmrix.loconet.LocoNetSlot} is modified.
     *
     * @author			Bob Jacobsen  Copyright (C) 2001, 2008
     * @version	$Revision: 17977 $
     */
    //public interface SlotListener extends java.util.EventListener{
    virtual void notifyChangedSlot(LocoNetSlot* s) =0;
signals:
    
public slots:
    
};

#endif // SLOTLISTENER_H
