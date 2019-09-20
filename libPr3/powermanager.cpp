#include "powermanager.h"

/*static*/ /*final*/ QString PowerManager::POWER = "Power"; // NOI18N

/*public*/ /*default*/ bool implementsIdle() {
        // By default the Power Manager does not implement the IDLE power state
        return false;
    }
