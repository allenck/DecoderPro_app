#ifndef NOFEEDBACKTURNOUTOPERATION_H
#define NOFEEDBACKTURNOUTOPERATION_H
#include "abstractturnout.h"
#include "commonturnoutoperation.h"
#include "libPr3_global.h"

class CommonTurnoutOperation;
class AbstractTurnout;
class LIBPR3SHARED_EXPORT NoFeedbackTurnoutOperation : public CommonTurnoutOperation
{
 Q_OBJECT
public:
 //explicit NoFeedbackTurnoutOperation(QObject *parent = 0);
    // This class can deal with ANY feedback mode, although it may not be the best one
    /*final*/ int feedbackModes;// =
//            Turnout::DIRECT | Turnout::ONESENSOR | Turnout::TWOSENSOR| Turnout::INDIRECT | Turnout::EXACT | Turnout::MONITORING;
/*
 * Default values and constraints
 */
 static /*public*/ /*final*/const int defaultInterval;// = 300;
 static /*public*/ /*final*/ const int defaultMaxTries;// = 2;
 Q_INVOKABLE/*public*/ NoFeedbackTurnoutOperation(QString n, int i, int mt, QObject *parent = 0);
 Q_INVOKABLE/*public*/ NoFeedbackTurnoutOperation(QObject *parent = 0);
 ~NoFeedbackTurnoutOperation() {}
 NoFeedbackTurnoutOperation(const NoFeedbackTurnoutOperation&)
  : CommonTurnoutOperation("NoFeedback", defaultInterval, defaultMaxTries) {}
 /*public*/ TurnoutOperation* makeCopy(QString n);
 /*public*/ int getDefaultInterval();
 /*public*/ int getDefaultMaxTries() ;
 static /*public*/ int getDefaultIntervalStatic() ;
 static /*public*/ int getDefaultMaxTriesStatic();
 /*public*/ TurnoutOperator* getOperator(AbstractTurnout* t);

signals:
    
public slots:
    
};
Q_DECLARE_METATYPE(NoFeedbackTurnoutOperation)
#endif // NOFEEDBACKTURNOUTOPERATION_H
