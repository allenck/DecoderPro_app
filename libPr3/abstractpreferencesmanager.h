#ifndef ABSTRACTPREFERENCESMANAGER_H
#define ABSTRACTPREFERENCESMANAGER_H

#include "bean.h"

class Profile;
class AbstractPreferencesManager : public Bean
{
 Q_OBJECT
public:
 explicit AbstractPreferencesManager(QObject *parent = 0);
 /*public*/ bool isInitialized(/*@Nonnull*/ Profile* profile);

signals:

public slots:
private:
 /*private*/ /*final*/ QMap<Profile*, bool> initialized;// = new HashMap<>();
protected:
 /*protected*/ void setInitialized(/*@Nonnull*/ Profile* profile, bool initialized);

};

#endif // ABSTRACTPREFERENCESMANAGER_H
