#ifndef LNREPORTERMANAGER_H
#define LNREPORTERMANAGER_H
#include "abstractreportermanager.h"
#include "lntrafficcontroller.h"
#include "libPr3_global.h"

/**
 * LnReporterManager implements the ReporterManager.
 * <P>
 * System names are "LRnnn", where nnn is the Reporter number without padding.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 * <P>
 * Description:		Implement Reporter manager for loconet
 * @author			Bob Jacobsen Copyright (C) 2001
 * @version         $Revision: 17977 $
 */

class LIBPR3SHARED_EXPORT LnReporterManager : public AbstractReporterManager, public LocoNetListener
{
    Q_OBJECT
    Q_INTERFACES(LocoNetListener)
public:
    explicit LnReporterManager(LocoNetSystemConnectionMemo *memo, QObject *parent = 0);
    void dispose()override;
    Reporter* createNewReporter(QString systemName, QString userName) override;
    /*public*/ int getBitFromSystemName(QString systemName) ;
    /*public*/ NameValidity validSystemNameFormat(QString systemName)  override;
    /*public*/ QString getEntryToolTip()override;
    /*public*/ QString validateSystemNameFormat(QString systemName, QLocale locale) override;
    /*public*/ QString getNamedBeanClass()const override {
        return "LnReporter";
    }
    QObject* self() override { return (QObject*)this;}

public slots:
    void message(LocoNetMessage* l)override;

signals:
    
public slots:

private:
 LnTrafficController* tc = nullptr;
 QString prefix;
 Logger log;
    
};

#endif // LNREPORTERMANAGER_H
