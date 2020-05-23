#ifndef TIMETABLEACTION_H
#define TIMETABLEACTION_H
#include "abstractaction.h"

class JmriPanel;
class TimeTableAction : public AbstractAction
{
 Q_OBJECT
public:
 /*public*/ TimeTableAction(QString s, QObject* parent);
 /*public*/ TimeTableAction(QObject* parent);
 /*public*/ JmriPanel* makePanel();

public slots:
 void actionPerformed();
};

#endif // TIMETABLEACTION_H
