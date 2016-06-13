#ifndef TURNOUTOPERATOR_H
#define TURNOUTOPERATOR_H

#include <QThread>
#include "exceptions.h"
#include "libPr3_global.h"

class AbstractTurnout;
class LIBPR3SHARED_EXPORT  TurnoutOperator : public QThread
{
    Q_OBJECT
public:
    //explicit TurnoutOperator(QObject *parent = 0);
    /*protected*/ TurnoutOperator(AbstractTurnout* t,QObject *parent = 0);

signals:
    
public slots:
private:
protected:
 /*protected*/ AbstractTurnout* myTurnout;
 /*protected*/ void operatorCheck() throw (TurnoutOperatorException);

    
};

#endif // TURNOUTOPERATOR_H
