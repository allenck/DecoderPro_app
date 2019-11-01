#ifndef ADDRESSEDHIGHCVPROGRANMMERFACADETESTACTION_H
#define ADDRESSEDHIGHCVPROGRANMMERFACADETESTACTION_H
#include "abstractaction.h"

class Logger;
class AddressedHighCvProgranmmerFacadeTestAction : public AbstractAction
{
 Q_OBJECT
public:
 AddressedHighCvProgranmmerFacadeTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // ADDRESSEDHIGHCVPROGRANMMERFACADETESTACTION_H
