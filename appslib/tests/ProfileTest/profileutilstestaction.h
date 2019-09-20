#ifndef PROFILEUTILSTESTACTION_H
#define PROFILEUTILSTESTACTION_H
#include "abstractaction.h"

class ProfileUtilsTestAction : public AbstractAction
{
public:
    ProfileUtilsTestAction(QObject* parent);
public slots:
    void actionPerformed();
};

#endif // PROFILEUTILSTESTACTION_H
