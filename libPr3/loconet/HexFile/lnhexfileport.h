#ifndef LNHEXFILEPORT_H
#define LNHEXFILEPORT_H

#include "lnportcontroller.h"
#include "libPr3_global.h"

//class BufferedReader;
class LIBPR3SHARED_EXPORT LnHexFilePort : public LnPortController
{
    Q_OBJECT
public:
    explicit LnHexFilePort(QObject *parent = 0);
    /*public*/ void load(QFile* file);
    /*public*/ void _connect(); // throw (Exception);
    /*public*/ void run(); // invoked in a new thread
    /*public*/ void setDelay(int newDelay);
    /*public*/ /*DataInputStream*/QDataStream* getInputStream();
    /*public*/ QDataStream* getOutputStream();
    /*public*/ bool status();
    /*public*/ bool running();
    /*public*/ bool okToSend();
    /*public*/ QVector<QString> getPortNames();
    /*public*/ QString openPort(QString portName, QString appName);
    /*public*/ void configure() ;
    /*public*/ QStringList validBaudRates();
    /*public*/ QStringList validOption3() ;
    /*public*/ QString option3Name();
    /*public*/ void configureOption3(QString value);

signals:

public slots:
    void On_interrupted();
private:
    /*BufferedReader*/ QTextStream* sFile;// = NULL;
    Logger * log;
    // private data
    /*private*/ bool _running;// = false;

    // streams to share with user class
    /*private*/ /*DataOutputStream*/QDataStream* pout;// = NULL; // this is provided to classes who want to write to us
    /*private*/ /*DataInputStream*/QDataStream* pin;// = NULL;  // this is provided to class who want data from us

    // internal ends of the pipes
    /*private*/ /*DataOutputStream*/QDataStream* outpipe;// = NULL;  // feed pin
    /*private*/ int delay;//=100;  				// units are milliseconds; default is quiet a busy LocoNet

};

#endif // LNHEXFILEPORT_H
