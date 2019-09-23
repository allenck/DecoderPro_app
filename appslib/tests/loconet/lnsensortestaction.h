#ifndef LNSENSORTESTACTION_H
#define LNSENSORTESTACTION_H

#include "abstractaction.h"
class LnSensorTestAction : public AbstractAction
{
public:
    LnSensorTestAction(QObject *parent);
public slots:
    void actionPerformed();
};

#endif // LNSENSORTESTACTION_H
