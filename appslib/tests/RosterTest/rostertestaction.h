#ifndef ROSTERTESTACTION_H
#define ROSTERTESTACTION_H
#include "abstractaction.h"

class Logger;
class RosterTestAction : public AbstractAction
{
    Q_OBJECT
public:
    RosterTestAction(QObject* parent);
    RosterTestAction(QString text, QObject* parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // ROSTERTESTACTION_H
