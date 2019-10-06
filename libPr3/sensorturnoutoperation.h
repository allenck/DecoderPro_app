#ifndef SENSORTURNOUTOPERATION_H
#define SENSORTURNOUTOPERATION_H
#include "commonturnoutoperation.h"


class SensorTurnoutOperation : public CommonTurnoutOperation
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SensorTurnoutOperation(QObject *parent = 0);
    ~SensorTurnoutOperation() {}
    SensorTurnoutOperation(const SensorTurnoutOperation&) : CommonTurnoutOperation("Sensor",defaultInterval,defaultMaxTries) {}
    // This class can deal with explicit feedback modes
    Q_INVOKABLE /*public*/ SensorTurnoutOperation(QString n, int i, int mt, QObject *parent = 0);

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
Q_DECLARE_METATYPE(SensorTurnoutOperation)
#endif // SENSORTURNOUTOPERATION_H
