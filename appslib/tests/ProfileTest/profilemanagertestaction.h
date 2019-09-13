#ifndef PROFILEMANAGERTESTACTION_H
#define PROFILEMANAGERTESTACTION_H
#include "abstractaction.h"

class ProfileManagerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    ProfileManagerTestAction(QObject *parent);
    ProfileManagerTestAction(QString text, QObject *parent);

public slots:
    void actionPerformed();

};

#endif // PROFILEMANAGERTESTACTION_H
