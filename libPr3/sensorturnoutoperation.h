#ifndef SENSORTURNOUTOPERATION_H
#define SENSORTURNOUTOPERATION_H
#include "commonturnoutoperation.h"


class SensorTurnoutOperation : public CommonTurnoutOperation
{
    Q_OBJECT
public:
    explicit SensorTurnoutOperation(QObject *parent = 0);
    // This class can deal with explicit feedback modes
    /*public*/ SensorTurnoutOperation(QString n, int i, int mt, QObject *parent = 0);

    /*
     * Default values and constraints
     */

    static /*public*/ /*final*/const  int defaultInterval;// = 300;
    static /*public*/ /*final*/const  int defaultMaxTries;// = 3;
    /*public*/ TurnoutOperation* makeCopy(QString n);
    /*public*/ int getDefaultInterval() ;
    /*public*/ int getDefaultMaxTries();
    /*public*/ TurnoutOperator* getOperator(AbstractTurnout* t);

signals:

public slots:
    private:
    /*final*/ int feedbackModes;// = AbstractTurnout::ONESENSOR | AbstractTurnout.TWOSENSOR |AbstractTurnout.EXACT |AbstractTurnout.INDIRECT;


};

#endif // SENSORTURNOUTOPERATION_H
