#ifndef SPROGMESSAGETESTACTION_H
#define SPROGMESSAGETESTACTION_H
#include "abstractaction.h"

class Logger;
class SprogMessageTestAction : public AbstractAction
{
    Q_OBJECT
public:
    SprogMessageTestAction(QObject *parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // SPROGMESSAGETESTACTION_H
