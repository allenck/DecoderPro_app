#ifndef OPTIONSMENUTESTACTION_H
#define OPTIONSMENUTESTACTION_H
#include "abstractaction.h"

class Logger;
class OptionsMenuTestAction : public AbstractAction
{
 Q_OBJECT
 public:
 OptionsMenuTestAction(QObject *parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // OPTIONSMENUTESTACTION_H
