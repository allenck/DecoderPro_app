#ifndef PROFILEMANAGERTESTACTION_H
#define PROFILEMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class ProfileManagerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    ProfileManagerTestAction(QObject *parent);
    ProfileManagerTestAction(QString text, QObject *parent);

public slots:
    void actionPerformed();
private:
    static Logger* log;

};

#endif // PROFILEMANAGERTESTACTION_H
