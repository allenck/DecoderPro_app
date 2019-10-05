#ifndef TESTUSERPREFERENCESMANAGER_H
#define TESTUSERPREFERENCESMANAGER_H
#include "jmriuserpreferencesmanager.h"

class TestUserPreferencesManager : public JmriUserPreferencesManager
{
 Q_OBJECT
public:
 TestUserPreferencesManager(QObject *parent = nullptr);

protected:
 /*protected*/ void showMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, int type);

};

#endif // TESTUSERPREFERENCESMANAGER_H
