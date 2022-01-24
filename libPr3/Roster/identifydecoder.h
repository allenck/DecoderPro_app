#ifndef IDENTIFYDECODER_H
#define IDENTIFYDECODER_H
#include "abstractidentify.h"

class IdentifyDecoder : public AbstractIdentify
{
    Q_OBJECT
public:
    explicit IdentifyDecoder(Programmer* programmer, QObject *parent = 0);
    /*public*/ bool test1();
    /*public*/ bool test2(int value);
    /*public*/ bool test3(int value) ;
    /*public*/ bool test4(int value);
    /*public*/ bool test5(int value) ;
    /*public*/ bool test6(int value);
    /*public*/ bool test7(int value) ;
    /*public*/ bool test8(int value);
    /*public*/ bool test9(int value);

signals:

public slots:
private:
    int mfgID = -1; 	// cv8
    int modelID = -1;	// cv7
    int productIDhigh = -1;
    int productIDlow  = -1;
    int productIDhighest = -1;
    int productIDlowest = -1;
    int productID  = -1;
    Logger* log;
protected:
    /*protected*/ void statusUpdate(QString s) ;
    /*abstract*/ /*protected*/ virtual void done(int /*mfgID*/, int /*modelID*/, int /*productID*/){}

    /*abstract*/ /*protected*/ virtual void message(QString /*m*/) {}
friend class IdentifyDecoderTest;
};

#endif // IDENTIFYDECODER_H
