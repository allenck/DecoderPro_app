#ifndef PROFILETESTACTION_H
#define PROFILETESTACTION_H
#include "abstractaction.h"

class Logger;
class ProfileTestAction : public AbstractAction
{
    Q_OBJECT
public:
    ProfileTestAction(QObject* parent);
    ProfileTestAction(QString text, QObject* parent);

public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // PROFILETESTACTION_H
