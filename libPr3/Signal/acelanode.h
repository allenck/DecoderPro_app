#ifndef ACELANODE_H
#define ACELANODE_H

#include "abstractnode.h"
#include "sensor.h"

class AcelaReply;
class AcelaTrafficController;
class AcelaNode : public AbstractNode
{
 public:
  explicit AcelaNode(QObject *parent = nullptr);
  /*public*/  AcelaNode(int address, int type, AcelaTrafficController* tc, QObject* parent);
  /*public*/  static /*final*/const qint8 AC;// = 0x00; // Acela Interface module (no inputs, no outputs)
  // Does not really return a code of 0x00
  /*public*/  static /*final*/const qint8 TB;// = 0x01; // TrainBrain (4 output bits and 4 input bits)
  /*public*/  static /*final*/const qint8 D8;// = 0x02; // Dash-8 (8 output bits)
  /*public*/  static /*final*/const qint8 WM;// = 0x03; // Watchman (8 input bits)
  /*public*/  static /*final*/const qint8 SM;// = 0x04; // SignalMan (16 output bits)
  /*public*/  static /*final*/const qint8 SC;// = 0x05; // SmartCab (1 output bits. no input bits)
  /*public*/  static /*final*/const qint8 SW;// = 0x06; // SwitchMan (16 output bits. no input bits)
  /*public*/  static /*final*/const qint8 YM;// = 0x07; // YardMaster (16 output bits. no input bits)
  /*public*/  static /*final*/const qint8 SY;// = 0x08; // Sentry (no output bits. 16 input bits)
  /*public*/  static /*final*/const qint8 UN;// = 0x09; // Unidentified module -- should be FF
  /*public*/  static /*final*/ QString moduleTypes;// = "ACTBD8WMSMSCSWYMSYUN";
  /*public*/  static /*final*/ QString sensorTypes;// = "NFSBCGDT";
  /*public*/  static /*final*/ QString sensorPolarities;// = "ACTINV";
  /*public*/  static /*final*/ QString outputWireds;// = "NONC";
  /*public*/  static /*final*/ QString outputInits;// = "OFFACT";
  /*public*/  static /*final*/ QString outputTypes;// = "ONOFFPULSEBLINK";
  /*public*/  static /*final*/ int ONOFF;// = 0;
  /*public*/  static /*final*/ int PULSE;// = 1;
  /*public*/  static /*final*/ int BLINK;// = 2;
  /*public*/  static /*final*/ QString outputSignalHeadTypes;// = "UKNOWNDOUBLETRIPLEBPOLARWIGWAG";
  /*public*/  static /*final*/const int UKNOWN;// = 0;
  /*public*/  static /*final*/const int DOUBLE;// = 1;
  /*public*/  static /*final*/const int TRIPLE;// = 2;
  /*public*/  static /*final*/const int BPOLAR;// = 3;
  /*public*/  static /*final*/const int WIGWAG;// = 4;
  // These can be removed in June 2010:
  /*public*/  static /*final*/ QString outputONOFF;// = "ONOFF";   // used to dump/restore config file.
  /*public*/  static /*final*/ QString outputLEN0;// = "0";        // used to dump/restore config file.
  /*public*/  static /*final*/ QString outputNO;// = "N0";         // used to dump/restore config file.
  /*public*/  static QVector<QString> getModuleNames() ;
  /*public*/  static QVector<QString> getNodeNames() ;
  /*public*/  void initNode();
  /*public*/  void setStartingOutputAddress(int startingAddress);
  /*public*/  int getStartingOutputAddress();
  /*public*/  void setEndingOutputAddress(int endingAddress);
  /*public*/  int getEndingOutputAddress();
  /*public*/  void setStartingSensorAddress(int startingAddress);
  /*public*/  int getStartingSensorAddress();
  /*public*/  void setEndingSensorAddress(int endingAddress);
  /*public*/  int getEndingSensorAddress();
  /*public*/  void setOutputBit(int bitNumber, bool state);
  /*public*/  bool getOutputBit(int bitNumber);
  /*public*/  bool getSensorsActive()override;
  /*public*/  int getOutputWired(int circuitnum);
  /*public*/  QString getOutputWiredString(int circuitnum);
  /*public*/  void setOutputWired(int circuitnum, int type);
  /*public*/  void setOutputWiredString(int circuitnum, QString stringtype);
  /*public*/  int getOutputInit(int circuitnum);
  /*public*/  QString getOutputInitString(int circuitnum);
  /*public*/  void setOutputInit(int circuitnum, int type);
  /*public*/  void setOutputInitString(int circuitnum, QString stringtype);
  /*public*/  int getOutputType(int circuitnum);
  /*public*/  QString getOutputTypeString(int circuitnum);
  /*public*/  void setOutputType(int circuitnum, int type);
  /*public*/  void setOutputTypeString(int circuitnum, QString stringtype);
  /*public*/  int getOutputLength(int circuitnum);
  /*public*/  void setOutputLength(int circuitnum, int newlength);
  /*public*/  int getOutputSpecial(int circuitnum);
  /*public*/  void setOutputSpecial(int circuitnum, int type);
  /*public*/  int getOutputSignalHeadType(int circuitnum);
  /*public*/  QString getOutputSignalHeadTypeString(int circuitnum);
  /*public*/  void setOutputSignalHeadType(int circuitnum, int type) ;
  /*public*/  void setOutputSignalHeadTypeString(int circuitnum, QString stringtype);
  /*public*/  int getSensorType(int circuitnum);
  /*public*/  QString getSensorTypeString(int circuitnum);
  /*public*/  void setSensorType(int circuitnum, int type);
  /*public*/  void setSensorTypeString(int circuitnum, QString stringtype);
  /*public*/  int getSensorPolarity(int circuitnum);
  /*public*/  QString getSensorPolarityString(int circuitnum);
  /*public*/  void setSensorPolarity(int circuitnum, int polarity);
  /*public*/  void setSensorPolarityString(int circuitnum, QString stringpolarity) ;
  /*public*/  int getSensorThreshold(int circuitnum);
  /*public*/  void setSensorThreshold(int circuitnum, int threshold) ;
  /*public*/  int getNodeType() ;
  /*public*/  QString getNodeTypeString();
  /*public*/  void setNodeTypeString(QString stringtype);
  /*public*/  void setNodeType(int type);
  /*public*/  int getNumOutputBitsPerCard() ;
  /*public*/  int getNumSensorBitsPerCard();
  /*public*/  bool checkNodeAddress(int address)override;
  /*public*/  int getSensorBitsPerCard();
  /*public*/  int getTransmissionDelay();
  /*public*/  void setTransmissionDelay(int delay);
  /*public*/  AbstractMRMessage* createInitPacket()override;
  /*public*/  AbstractMRMessage* createOutPacket()override;
  /*public*/  void markChanges(AcelaReply* l);
  /*public*/  void registerSensor(Sensor* s, int rawaddr);
  /*public*/  bool handleTimeout(AbstractMRMessage* m, AbstractMRListener* l)override;
  /*public*/  void resetTimeout(AbstractMRMessage* m)override;

 private:
  static Logger* log;
  static /*final*/ int MAXSENSORBITS;// = 16;  // Used to initialize arrays
  static /*final*/ int MAXOUTPUTBITS;// = 16;  // Used to initialize arrays
  static /*final*/ int MAXNODE;// = 1024;
  /*private*/ static int MAXDELAY;// = 65535;
  int timeout;
  bool warned = false;

  static /*final*/ QVector<QString> nodeNames;// = new String[]{"0", "1", "2", "3", "4",
//      "5", "6", "7", "8", "9",
//      "10", "11", "12", "13", "14",
//      "15", "16", "17", "18", "19"
//  };

  static /*final*/ QVector<QString> moduleNames;// = new String[]{"Acela",
//      "TrainBrain",
//      "Dash-8",
//      "Watchman",
//      "SignalMan",
//      "SmartCab",
//      "SwitchMan",
//      "YardMaster",
//      "Sentry"
//  };

  static /*final*/ QVector<QString> moduleTips;// = new String[]{"Acela",
//      "TrainBrain has 4 output circuits and 4 input circuits",
//      "Dash-8 has 8 output circuits and no input circuits",
//      "Watchman has no output circuits and 8 input circuits",
//      "SignalMan has 16 output circuits and no input circuits",
//      "SmartCab has 1 output circuit and no input circuits",
//      "SwitchMan has 16 output circuits and no input circuits",
//      "YardMaster has 16 output circuits and no input circuits",
//      "Sentry has no output circuits and 16 input circuits"
//  };
  void common(int address, int type, AcelaTrafficController* tc);

 protected:
  // node definition instance variables (must persist between runs)
  /*protected*/ int nodeType = UN;                        // See above
  /*protected*/ int outputbitsPerCard = MAXOUTPUTBITS;    // See above
  /*protected*/ int sensorbitsPerCard = MAXSENSORBITS;    // See above
  /*protected*/ int transmissionDelay = 0;                // Delay between bytes on Receive (units of 10 microsec.)

  // operational instance variables  (should not be preserved between runs)
  /*protected*/ bool needInit = false;          // 'true' if this module needs to be initialized
  //    used for sensors
  /*protected*/ QVector<qint8> outputArray = QVector<qint8>(MAXOUTPUTBITS); // current values of the output bits for this node
  /*protected*/ QVector<qint8> outputSpecial = QVector<qint8>(MAXOUTPUTBITS); // does the output circuit require special handling
  /*protected*/ QVector<qint8> outputSignalHeadType = QVector<qint8>(MAXOUTPUTBITS); // type of SignalHead
  /*protected*/ bool hasActiveSensors = false; // 'true' if there are active Sensors for this node
  /*protected*/ int lastUsedSensor = -1;           // grows as sensors defined
  /*protected*/ QVector<Sensor*> sensorArray = QVector<Sensor*>(MAXSENSORBITS);
  /*protected*/ QVector<bool> sensorNeedInit = QVector<bool>(MAXSENSORBITS);    // used to indicate if sensor needs to be configured
  /*protected*/ QVector<bool> sensorHasBeenInit = QVector<bool>(MAXSENSORBITS); // used to indicate if sensor has been configured
  /*protected*/ QVector<qint8> sensorLastSetting = QVector<qint8>(MAXSENSORBITS);
  /*protected*/ QVector<qint8> sensorType = QVector<qint8>(MAXSENSORBITS);
  /*protected*/ QVector<qint8> sensorPolarity = QVector<qint8>(MAXSENSORBITS);
  /*protected*/ QVector<qint8> sensorThreshold = QVector<qint8>(MAXSENSORBITS);
  /*protected*/ QVector<qint8> sensorConfigArray = QVector<qint8>(MAXSENSORBITS); // configuration values of the sensor circuits for this node
  /*protected*/ QVector<qint8> outputWired = QVector<qint8>(MAXOUTPUTBITS);
  /*protected*/ QVector<qint8> outputInit = QVector<qint8>(MAXOUTPUTBITS);
  /*protected*/ QVector<qint8> outputType = QVector<qint8>(MAXOUTPUTBITS);
  /*protected*/ QVector<qint8> outputLength = QVector<qint8>(MAXOUTPUTBITS);
  /*protected*/ QVector<bool> outputNeedToSend =QVector<bool>(MAXOUTPUTBITS);

  friend class AcelaAddress;
};

#endif // ACELANODE_H
