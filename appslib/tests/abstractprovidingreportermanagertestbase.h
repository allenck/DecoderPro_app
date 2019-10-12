#ifndef ABSTRACTPROVIDINGREPORTERMANAGERTESTBASE_H
#define ABSTRACTPROVIDINGREPORTERMANAGERTESTBASE_H

#include <QObject>
#include "abstractmanagertestbase.h"
#include "providingmanager.h"

class ProxyReporterManager;
class Logger;
class AbstractProvidingReporterManagerTestBase : public AbstractManagerTestBase
{
 Q_OBJECT
public:
 explicit AbstractProvidingReporterManagerTestBase(QObject *parent = nullptr);
 /*public*/ void testRegisterDuplicateSystemName(ProxyReporterManager *m, QString s1, QString s2)
         throw (PropertyVetoException, /*NoSuchFieldException,
         NoSuchFieldException, */IllegalArgumentException, IllegalAccessException);

signals:

public slots:
 /*public*/ void testProvideEmpty() throw (IllegalArgumentException);
 /*public*/ void testRegisterDuplicateSystemName() throw (PropertyVetoException, /*NoSuchFieldException,
           NoSuchFieldException,*/ IllegalArgumentException, IllegalAccessException);

private:
 static Logger* log;

};

#endif // ABSTRACTPROVIDINGREPORTERMANAGERTESTBASE_H
