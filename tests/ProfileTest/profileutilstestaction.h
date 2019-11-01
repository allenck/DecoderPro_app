#ifndef PROFILEUTILSTESTACTION_H
#define PROFILEUTILSTESTACTION_H
#include "abstractaction.h"

class Logger;
class ProfileUtilsTestAction : public AbstractAction
{
public:
    ProfileUtilsTestAction(QObject* parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;

};

#endif // PROFILEUTILSTESTACTION_H
