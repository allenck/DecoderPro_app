#ifndef SECTIONTESTACTION_H
#define SECTIONTESTACTION_H
#include "abstractaction.h"

class Logger;
class SectionTestAction : public AbstractAction
{
 Q_OBJECT
public:
 SectionTestAction(QObject *parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // SECTIONTESTACTION_H
