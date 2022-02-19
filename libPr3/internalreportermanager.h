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
    /*public*/ bool allowMultipleAdditions(QString systemName) override;

    /*public*/ SystemConnectionMemo* getMemo() override;
    /*public*/ QString getNamedBeanClass() const override
    {
     return "Reporter";
    }
    /*public*/ QString toString() {return "InternalReporterManager";}

    QObject* self() override {return (QObject*)this;}
    QObject* vself() override { return (QObject*)this;}

signals:
    
public slots:
    /**
     * Create an internal (dummy) reporter object
     * @return new null
     */

    /*protected*/ Reporter* createNewReporter(QString systemName, QString userName) override;

};

#endif // INTERNALREPORTERMANAGER_H
