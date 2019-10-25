#ifndef LNREPORTERMANAGERTESTACTION_H
#define LNREPORTERMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnReporterManagerTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LnReporterManagerTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // LNREPORTERMANAGERTESTACTION_H
