#include "appsconfigurationmanager.h"
#include "editconnectionpreferencesdialog.h"

AppsConfigurationManager::AppsConfigurationManager(QObject *parent) :JmriConfigurationManager(parent)
{
 setObjectName("AppsConfigurationManager");
}
///*public*/ class AppsConfigurationManager extends JmriConfigurationManager {

    //@Override
    /*protected*/ bool AppsConfigurationManager::isEditDialogRestart() {
        return EditConnectionPreferencesDialog::showDialog();
    }

