#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#include "devicelistener.h".h"
#include <QThread>
/**
 * Interface for WiThrottle device managers.
 *
 * @author Randall Wood Copyright 2011, 2017
 */
/*public*/ /*interface*/ class DeviceManager {
public:
 /*public*/ virtual void listen() {}

    /*public*/ virtual /*default*/ void createServerThread() {
//        new DeviceManagerThread(this).start();
    }

    /**
     * Add a device listener that will be added for each new
     * device connection
     *
     * @param dl the device listener to add
     */
 /*public*/ virtual void addDeviceListener(DeviceListener* /*dl*/) {}

    /**
     * Remove a device listener from the list that will be added for each new
     * device connection
     *
     * @param dl the device listener to remove
     */
 /*public*/ virtual void removeDeviceListener(DeviceListener* /*dl*/) {}

    /**
     * Specify a roster group to send
     *
     * @param group the roster group.
     */
 /*public*/ virtual void setSelectedRosterGroup(QString /*group*/) {}

    /**
     * the roster group to send.
     *
     * @return the roster group
     */
 /*public*/ virtual QString getSelectedRosterGroup() {return QString();}
#if 0
    /**
     * Container for running {@link #listen() } in a separate thread.
     */
    /*public*/ static class DeviceManagerThread extends Thread {

        DeviceManager manager;

        DeviceManagerThread(DeviceManager manager) {
            this.manager = manager;
            this.setName("WiThrottleServer"); // NOI18N
        }

        @Override
        /*public*/ void run() {
            manager.listen();
            log.debug("Leaving DeviceManagerThread.run()");
        }

        private final static Logger log = LoggerFactory.getLogger(DeviceManagerThread.class);
#endif
    };

#endif // DEVICEMANAGER_H
