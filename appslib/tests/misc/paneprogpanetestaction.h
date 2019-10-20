#ifndef PANEPROGPANETESTACTION_H
#define PANEPROGPANETESTACTION_H
#include "abstractaction.h"

class Logger;
class PaneProgPaneTestAction : public AbstractAction
{
 Q_OBJECT
public:
 PaneProgPaneTestAction(QObject *parent);
public slots:
 void actionPerformed();

private:
 static Logger* log;

};

#endif // PANEPROGPANETESTACTION_H
