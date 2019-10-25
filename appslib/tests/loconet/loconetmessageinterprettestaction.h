#ifndef LOCONETMESSAGEINTERPRETTESTACTION_H
#define LOCONETMESSAGEINTERPRETTESTACTION_H

#include <QObject>
#include "abstractaction.h"

class Logger;
class LocoNetMessageInterpretTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LocoNetMessageInterpretTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // LOCONETMESSAGEINTERPRETTESTACTION_H
