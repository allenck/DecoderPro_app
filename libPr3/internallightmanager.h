#ifndef INTERNALLIGHTMANAGER_H
#define INTERNALLIGHTMANAGER_H
#include "abstractlightmanager.h"

class LIBPR3SHARED_EXPORT InternalLightManager : public AbstractLightManager
{
    Q_OBJECT
public:
 explicit InternalLightManager(QObject *parent = 0);
    /*public*/ QString getSystemPrefix();
    /*public*/ bool validSystemNameConfig(QString systemName);
    /*public*/ NameValidity validSystemNameFormat(QString systemName);
    /*public*/ bool supportsVariableLights(QString systemName);
    /*public*/ bool allowMultipleAdditions(QString systemName);

signals:

public slots:
protected:
 /*protected*/ Light* createNewLight(QString systemName, QString userName);

};

#endif // INTERNALLIGHTMANAGER_H
