#ifndef PROFILETESTACTION_H
#define PROFILETESTACTION_H
#include "abstractaction.h"

class ProfileTestAction : public AbstractAction
{
    Q_OBJECT
public:
    ProfileTestAction(QObject* parent);
    ProfileTestAction(QString text, QObject* parent);

public slots:
    void actionPerformed();
};

#endif // PROFILETESTACTION_H
