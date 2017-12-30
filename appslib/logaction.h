#ifndef LOGACTION_H
#define LOGACTION_H

#include "abstractaction.h"

class Logger;
class LogAction : public AbstractAction
{
 Q_OBJECT
public:
 LogAction(QObject* parent = 0);
 /*public*/ LogAction(QString s, QObject* parent=0);

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

private:
 /*private*/ /*final*/ static Logger* log;// = new Logger("LogAction");
};

#endif // LOGACTION_H
