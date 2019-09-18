#ifndef SPROGMESSAGETESTACTION_H
#define SPROGMESSAGETESTACTION_H
#include "abstractaction.h"

class SprogMessageTestAction : public AbstractAction
{
    Q_OBJECT
public:
    SprogMessageTestAction(QObject *parent);
public slots:
    void actionPerformed();
};

#endif // SPROGMESSAGETESTACTION_H
