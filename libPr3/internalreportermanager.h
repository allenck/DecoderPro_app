#ifndef INTERNALREPORTERMANAGER_H
#define INTERNALREPORTERMANAGER_H
#include "abstractreportermanager.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT InternalReporterManager : public AbstractReporterManager
{
    Q_OBJECT
public:
    InternalReporterManager(QObject *parent = 0);
    /*public*/ bool allowMultipleAdditions(QString systemName);

    /*public*/ QString getSystemPrefix();

signals:
    
public slots:
    /**
     * Create an internal (dummy) reporter object
     * @return new null
     */
#if 1
    /*protected*/ AbstractReporter* createNewReporter(QString systemName, QString userName);
#endif
};

#endif // INTERNALREPORTERMANAGER_H
