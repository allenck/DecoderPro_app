#ifndef WARRANTTESTACTION_H
#define WARRANTTESTACTION_H
#include "abstractaction.h"

class Logger;
class WarrantTestAction : public AbstractAction
{
 Q_OBJECT
public:
 WarrantTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // WARRANTTESTACTION_H
