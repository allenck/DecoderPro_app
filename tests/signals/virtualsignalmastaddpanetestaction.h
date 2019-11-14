#ifndef VIRTUALSIGNALMASTADDPANETESTACTION_H
#define VIRTUALSIGNALMASTADDPANETESTACTION_H
#include "abstractaction.h"

class Logger;
class VirtualSignalMastAddPaneTestAction : public AbstractAction
{
 Q_OBJECT
public:
 VirtualSignalMastAddPaneTestAction(QObject* parent);

public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // VIRTUALSIGNALMASTADDPANETESTACTION_H
