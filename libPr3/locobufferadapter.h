#ifndef LOCOBUFFERADAPTER_H
#define LOCOBUFFERADAPTER_H
#include "lnportcontroller.h"
#include "exceptions.h"
#include "serialport.h"
#include "activeflag.h"
#include "lnpacketizer.h"

//#define USE_THREAD

class LnPortController;
class LIBPR3SHARED_EXPORT LocoBufferAdapter : public LnPortController
{
    Q_OBJECT
public:
   //explicit LocoBufferAdapter(QObject *parent = 0);
    LocoBufferAdapter(LocoNetSystemConnectionMemo* adapterMemo = new LocoNetSystemConnectionMemo(), QObject *parent = 0);
    ~LocoBufferAdapter(){}
    /*public*/ QVector<QString> getPortNames();
    /*public*/ QString openPort(QString portName, QString appName)throw(NoSuchPortException);
    /**
     * Can the port accept additional characters?
     * The state of CTS determines this, as there seems to
     * be no way to check the number of queued bytes and buffer length.
     * This might
     * go false for short intervals, but it might also stick
     * off if something goes wrong.
     */
    /*public*/  bool okToSend();
    /**
     * Set up all of the other objects to operate with a LocoBuffer
     * connected to this port.
     */
    /*public*/  void configure();
    // base class methods for the LnPortController interface
    /*public*/  QDataStream* getInputStream();
    /*public*/  QDataStream* getOutputStream();
    QSerialPort* getSerialPort();
    /*public*/  bool status();
    /**
     * Get an array of valid baud rates as strings. This allows subclasses
     * to change the arrays of speeds.
     */
    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK to expose array instead of copy until Java 1.6
    /*public*/  QStringList validBaudRates();
    /**
     * Get an array of valid baud rates as integers. This allows subclasses
     * to change the arrays of speeds.
     */
    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK to expose array instead of copy until Java 1.6
    /*public*/  QVector<int> validBaudNumbers();
    ///*public*/ SystemConnectionMemo* getSystemConnectionMemo() { return adaptermemo; }

    /*public*/  void dispose();
    SerialPort* activeSerialPort;
     LnPacketizer* packetizer();
    LnPacketizer* packets;
    void sendLocoNetMessage(LocoNetMessage* m);
    virtual /*public*/ int defaultBaudIndex();
    /*public*/ QString className();


public slots:
    void dataReady();

signals:
    void error(QString msg);
    
private:
    QVector<QString> portNameVector;
    // private control members
    /*private*/ bool opened;// = false;
    QDataStream* serialStream;// = NULL;
    Logger* log;
    //ActiveFlag activeFlag;
//    LnPacketizer* packets;
    void common();
    /**
     *  Define the readable data and internal code
     */
    /*private*/ static QVector<QStringList> packetizers;// = { {Bundle.getMessage("PacketizerTypelnPacketizer"),"lnPacketizer" },
//            {Bundle.getMessage("PacketizerTypelnPacketizerStrict"),"lnPacketizerStrict"} };
    // "Normal (recommended)" "lnPacketizer"
    // "Strict"               "lnPacketizerStrict"
/*private*/ QStringList packetizerOptions();

protected:
    /**
     * Local method to do specific configuration, overridden in class
     */
    /*protected*/  void setSerialPort(SerialPort* activeSerialPort) throw(UnsupportedCommOperationException);
    /*protected*/ QStringList validSpeeds;// = new String[]{"19,200 baud (J1 on 1&2)", "57,600 baud (J1 on 2&3)"};
    /*protected*/ QVector<int> validSpeedValues; // = new int[]{19200, 57600};

    // meanings are assigned to these above, so make sure the order is consistent
    /*protected*/ QStringList validOption1;
    /*protected*/ LnPacketizer* getPacketizer(QString s);
    /*protected*/ QString getPacketizerOption(QString s);

};

#endif // LOCOBUFFERADAPTER_H
