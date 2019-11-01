#ifndef PANEPROGFRAMETESTACTION_H
#define PANEPROGFRAMETESTACTION_H
#include "abstractaction.h"

class Logger;
class PaneProgFrameTestAction : public AbstractAction
{
 Q_OBJECT
public:
 PaneProgFrameTestAction(QObject *parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // PANEPROGFRAMETESTACTION_H
