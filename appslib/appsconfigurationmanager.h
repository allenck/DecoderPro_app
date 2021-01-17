#ifndef APPSCONFIGURATIONMANAGER_H
#define APPSCONFIGURATIONMANAGER_H
#include "jmriconfigurationmanager.h"

class AppsConfigurationManager : public JmriConfigurationManager
{
    Q_OBJECT
public:
    AppsConfigurationManager(QObject* parent = nullptr);
protected:
    /*protected*/ bool isEditDialogRestart();

};

#endif // APPSCONFIGURATIONMANAGER_H
