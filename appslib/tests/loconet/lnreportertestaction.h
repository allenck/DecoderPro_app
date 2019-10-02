#ifndef LNREPORTERTESTACTION_H
#define LNREPORTERTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnReporterTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LnReporterTestAction(QObject* parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // LNREPORTERTESTACTION_H
