#ifndef LOGIXLOADACTION_H
#define LOGIXLOADACTION_H
#include "abstractaction.h"

class Logger;
class LogixLoadAction : public AbstractAction
{
 Q_OBJECT
public:
 LogixLoadAction();
 /*public*/ LogixLoadAction(QString s, QWidget* who);

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

private:
 QWidget* _who;
 Logger* log;
};

#endif // LOGIXLOADACTION_H
