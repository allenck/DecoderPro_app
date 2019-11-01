#ifndef PROXYREPORTMANAGERTESTACTION_H
#define PROXYREPORTMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class ProxyReporterManagerTestAction : public AbstractAction
{
 Q_OBJECT
public:
 ProxyReporterManagerTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;

};

#endif // PROXYREPORTMANAGERTESTACTION_H
