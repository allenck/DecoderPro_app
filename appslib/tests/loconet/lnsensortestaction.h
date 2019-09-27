#ifndef LNSENSORTESTACTION_H
#define LNSENSORTESTACTION_H

#include "abstractaction.h"

class Logger;
class LnSensorTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnSensorTestAction(QObject *parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;

};

#endif // LNSENSORTESTACTION_H
