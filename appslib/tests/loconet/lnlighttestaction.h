#ifndef LIGHTTESTACTION_H
#define LIGHTTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnLightTestAction : public AbstractAction
{
public:
 LnLightTestAction(QObject* parent);
public slots:
 void actionPerformed();
};

#endif // LIGHTTESTACTION_H
