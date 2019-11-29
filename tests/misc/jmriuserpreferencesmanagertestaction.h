#ifndef JMRIUSERPREFERENCESMANAGERTESTACTION_H
#define JMRIUSERPREFERENCESMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class JmriUserPreferencesManagerTestAction : public AbstractAction
{
 Q_OBJECT
public:
 JmriUserPreferencesManagerTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;

};

#endif // JMRIUSERPREFERENCESMANAGERTESTACTION_H
