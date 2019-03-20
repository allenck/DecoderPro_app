#ifndef SIMPLESERVERACTION_H
#define SIMPLESERVERACTION_H
#include "abstractaction.h"

class SimpleServerAction : public AbstractAction
{
 Q_OBJECT
public:
 SimpleServerAction(QObject* parent= 0);
 Q_INVOKABLE /*public*/ SimpleServerAction(QString s, QObject *parent);
 ~SimpleServerAction() {}
 SimpleServerAction(const SimpleServerAction&) : AbstractAction() {}
public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

};
Q_DECLARE_METATYPE(SimpleServerAction)
#endif // SIMPLESERVERACTION_H
