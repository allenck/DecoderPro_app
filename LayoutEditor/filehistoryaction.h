#ifndef FILEHISTORYACTION_H
#define FILEHISTORYACTION_H
#include "abstractaction.h"

class FileHistoryAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit FileHistoryAction(QObject *parent = 0);
 /*public*/ FileHistoryAction(QString s,QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* /*e*/);
private:
 void common();
};

#endif // FILEHISTORYACTION_H
