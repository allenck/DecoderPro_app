#include "categoryloconet.h"
#include "loconetsystemconnectionmemo.h"
#include "instancemanager.h"

/**
 * Defines the category LocoNet
 *
 * @author Daniel Bergqvist Copyright 2020
 */
// /*public*/ final class CategoryLocoNet extends Category {

    /**
     * A item on the layout, for example turnout, sensor and signal mast.
     */
    /*public*/ /*static*/ /*final*/ CategoryLocoNet* CategoryLocoNet::LOCONET = new CategoryLocoNet();


    /*public*/ CategoryLocoNet::CategoryLocoNet(QObject *parent ) : Category("LOCONET", tr("LocoNet"), 300, parent){

    }

    /*public*/ /*static*/ void CategoryLocoNet::registerCategory() {
        // We don't want to add these classes if we don't have a LocoNet connection
        if (hasLocoNet() && !Category::values().contains(LOCONET)) {
            Category::registerCategory(LOCONET);
        }
    }

    /**
     * Do we have a LocoNet connection?
     * @return true if we have LocoNet, false otherwise
     */
    /*public*/ /*static*/ bool CategoryLocoNet::hasLocoNet() {
        /*QList<LocoNetSystemConnectionMemo*>*/QObjectList* list = InstanceManager::getList("LocoNetSystemConnectionMemo");

        // We have at least one LocoNet connection if the list is not empty
        return !list->isEmpty();
    }
