#ifndef SIMPLESERVERACTION_H
#define SIMPLESERVERACTION_H
#include "abstractaction.h"

class SimpleServerAction : public AbstractAction
{
 Q_OBJECT
public:
 SimpleServerAction(QObject* parent);
 /*public*/ SimpleServerAction(QString s, QObject *parent);

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

};

#endif // SIMPLESERVERACTION_H
