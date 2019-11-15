#ifndef DCCSIGNALMASTADDPANETESTACTION_H
#define DCCSIGNALMASTADDPANETESTACTION_H
#include "abstractaction.h"

class Logger;
class DccSignalMastAddPaneTestAction : public AbstractAction
{
 Q_OBJECT
public:
 DccSignalMastAddPaneTestAction(QObject* parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // DCCSIGNALMASTADDPANETESTACTION_H
