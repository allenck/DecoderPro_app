#ifndef CONSISTPREFERENCESMANAGER_H
#define CONSISTPREFERENCESMANAGER_H
#include "abstractpreferencesmanager.h"
#include "preferences.h"
#include "profileutils.h"

class Logger;
class ConsistPreferencesManager : public AbstractPreferencesManager
{
 Q_OBJECT
public:
 ConsistPreferencesManager(QObject *parent = nullptr);
 /*public*/ /*final*/ static QString UPDATE_CV19;// = "updateCV19";
 /*public*/ void initialize(Profile* profile) override /*throw (InitializationException)*/;
 /*public*/ void savePreferences(Profile* profile)override;
 /*public*/ bool isUpdateCV19();
 /*public*/ void setUpdateCV19(bool update);

 QObject* self() override {return (QObject*)this;}
private:
 static Logger* log;
 /*private*/ bool updateCV19 = false;

};

#endif // CONSISTPREFERENCESMANAGER_H
