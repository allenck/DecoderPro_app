#ifndef SOURCETESTACTION_H
#define SOURCETESTACTION_H
#include "abstractaction.h"

class Logger;
class SourceTestAction : public AbstractAction
{
 Q_OBJECT
public:
 SourceTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // SOURCETESTACTION_H
