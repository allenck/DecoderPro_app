#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#include "rostergroupselector.h"
/**
 *
 * @author rhwood
 */
/*public*/ /*interface*/class DeviceManager : public RosterGroupSelector {
 Q_OBJECT
public:
 inline DeviceManager(QWidget* parent) : RosterGroupSelector(parent) {}
};


#endif // DEVICEMANAGER_H
