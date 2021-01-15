#ifndef INTERNALREPORTERMANAGER_H
#define INTERNALREPORTERMANAGER_H
#include "abstractreportermanager.h"
#include "libPr3_global.h"

class InternalSystemConnectionMemo;
class LIBPR3SHARED_EXPORT InternalReporterManager : public AbstractReporterManager
{
    Q_OBJECT
public:
    InternalReporterManager(InternalSystemConnectionMemo *memo, QObject *parent = 0);
    /*public*/ bool allowMultipleAdditions(QString systemName)const override;

    /*public*/ SystemConnectionMemo* getMemo()const override;
    /*public*/ QString getNamedBeanClass() const override
    {
     return "Reporter";
    }
    /*public*/ QString toString() {return "InternalReporterManager";}

signals:
    
public slots:
    /**
     * Create an internal (dummy) reporter object
     * @return new null
     */

    /*protected*/ Reporter* createNewReporter(QString systemName, QString userName)const override;

};

#endif // INTERNALREPORTERMANAGER_H
