#ifndef LIGHTCONTROLTESTACTION_H
#define LIGHTCONTROLTESTACTION_H
#include "abstractaction.h"

class Logger;
class LightControlTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LightControlTestAction(QObject* parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // LIGHTCONTROLTESTACTION_H
