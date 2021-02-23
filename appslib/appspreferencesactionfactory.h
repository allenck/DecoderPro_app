#ifndef APPSPREFERENCESACTIONFACTORY_H
#define APPSPREFERENCESACTIONFACTORY_H

#include "jmripreferencesactionfactory.h"


class AppsPreferencesActionFactory : public JmriPreferencesActionFactory
{
public:
    AppsPreferencesActionFactory(QObject* parent = nullptr);
    /*public*/ JmriAbstractAction* getDefaultAction(QObject *parent);
    /*public*/ JmriAbstractAction* getNamedAction(QString name, QObject* parent);
    /*public*/ JmriAbstractAction* getCategorizedAction(QString name, QString category, QObject *parent);
    /*public*/ JmriAbstractAction* getCategorizedAction(QString name, QString category, QString subCategory, QObject* parent);
};

#endif // APPSPREFERENCESACTIONFACTORY_H
