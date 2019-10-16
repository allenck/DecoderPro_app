#ifndef TWOINDEXTCSPROGRAMMERFACADETESTACTION_H
#define TWOINDEXTCSPROGRAMMERFACADETESTACTION_H
#include "abstractaction.h"

class Logger;
class TwoIndexTcsProgrammerFacadeTestAction : public AbstractAction
{
 Q_OBJECT
public:
 TwoIndexTcsProgrammerFacadeTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // TWOINDEXTCSPROGRAMMERFACADETESTACTION_H
