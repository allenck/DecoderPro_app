#ifndef DEFAULTCABSIGNALTESTACTION_H
#define DEFAULTCABSIGNALTESTACTION_H
#include "abstractaction.h"

class Logger;
class DefaultCabSignalTestAction : public AbstractAction
{
 Q_OBJECT
public:
 DefaultCabSignalTestAction(QObject* parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // DEFAULTCABSIGNALTESTACTION_H
