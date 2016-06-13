#ifndef RAWTURNOUTOPERATION_H
#define RAWTURNOUTOPERATION_H
#include "commonturnoutoperation.h"
#include "libPr3_global.h"


class LIBPR3SHARED_EXPORT RawTurnoutOperation : public CommonTurnoutOperation
{
    Q_OBJECT
public:
    explicit RawTurnoutOperation(QObject *parent = 0);
    static /*public*/ /*final*/ int defaultInterval;// = 300;
    static /*public*/ /*final*/ int defaultMaxTries;// = 1;
    /*public*/ RawTurnoutOperation(QString n, int i, int mt, QObject *parent);
    /*public*/ TurnoutOperation* makeCopy(QString n);
    /*public*/ int getDefaultInterval();
    /*public*/ int getDefaultMaxTries();
    static /*public*/ int getDefaultIntervalStatic() ;
    static /*public*/ int getDefaultMaxTriesStatic();
    /*public*/ TurnoutOperator* getOperator(AbstractTurnout* t);

signals:

public slots:
private:
    // This class should only be used with DIRECT, ONESENSOR or TWOSENSOR
        // feedback modes.
    /*final*/ int feedbackModes;// =
//              Turnout.DIRECT | Turnout.EXACT | Turnout.INDIRECT
//            | Turnout.ONESENSOR | Turnout.TWOSENSOR;
    void common();

};

#endif // RAWTURNOUTOPERATION_H
