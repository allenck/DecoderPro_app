#ifndef CONTROLLERFILTERACTION_H
#define CONTROLLERFILTERACTION_H
#include "abstractaction.h"

class Logger;
class ControllerFilterAction : public AbstractAction
{
 Q_OBJECT
public:
 ControllerFilterAction(QString name, QObject* parent);
 /*public*/ ControllerFilterAction(QObject* parent);
public slots:
 /*public*/ void actionPerformed(ActionEvent* ae);
 /*public*/ QString getName();


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(ControllerFilterAction.class.getName());

};

#endif // CONTROLLERFILTERACTION_H
