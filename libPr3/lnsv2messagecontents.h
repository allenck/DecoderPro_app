#ifndef LNSV2MESSAGECONTENTS_H
#define LNSV2MESSAGECONTENTS_H

#include <QObject>
#include "exceptions.h"
#include "loconetmessage.h"
#include "loggerfactory.h"


class LnSv2MessageContents : public QObject
{
 Q_OBJECT
public:
 //explicit LnSv2MessageContents(QObject *parent = nullptr);
 // LocoNet "SV 2 format" helper definitions: length byte value for OPC_PEER_XFER message
 /*public*/ /*final*/ static const int SV2_LENGTH_ELEMENT_VALUE;// = 0x10;

 // LocoNet "SV 2 format" helper definitions: indexes into the LocoNet message
 /*public*/ /*final*/ static const int SV2_LENGTH_ELEMENT_INDEX; // 1;
 /*public*/ /*final*/ static const int SV2_SRC_ELEMENT_INDEX; // 2;
 /*public*/ /*final*/ static const int SV2_SV_CMD_ELEMENT_INDEX; // 3;
 /*public*/ /*final*/ static const int SV2_SV_TYPE_ELEMENT_INDEX; // 4;
 /*public*/ /*final*/ static const int SV2_SVX1_ELEMENT_INDEX; // 5;
 /*public*/ /*final*/ static const int SV2_SV_DST_L_ELEMENT_INDEX; // 6;
 /*public*/ /*final*/ static const int SV2_SV_DST_H_ELEMENT_INDEX; // 7;
 /*public*/ /*final*/ static const int SV2_SV_ADRL_ELEMENT_INDEX; // 8;
 /*public*/ /*final*/ static const int SV2_SV_ADRH_ELEMENT_INDEX; // 9;
 /*public*/ /*final*/ static const int SV2_SVX2_ELEMENT_INDEX; // 10;
 /*public*/ /*final*/ static const int SV2_SVD1_ELEMENT_INDEX; // 11;
 /*public*/ /*final*/ static const int SV2_SVD2_ELEMENT_INDEX; // 12;
 /*public*/ /*final*/ static const int SV2_SVD3_ELEMENT_INDEX; // 13;
 /*public*/ /*final*/ static const int SV2_SVD4_ELEMENT_INDEX; // 14;

//  helpers for decoding SV format 2 messages (versus other OCP_PEER_XFER messages with length 0x10)
 /*public*/ /*final*/ static const int SV2_SRC_ELEMENT_MASK; // 0x7f;
 /*public*/ /*final*/ static const int SV2_SVX1_ELEMENT_VALIDITY_CHECK_MASK; // 0x70;
 /*public*/ /*final*/ static const int SV2_SVX1_ELEMENT_VALIDITY_CHECK_VALUE; // 0x10;
 /*public*/ /*final*/ static const int SV2_SV_DST_L_DSTLX7_CHECK_MASK; // 0x01;
 /*public*/ /*final*/ static const int SV2_SV_DST_H_DSTHX7_CHECK_MASK; // 0x02;
 /*public*/ /*final*/ static const int SV2_SV_ADRL_SVADRL7_CHECK_MASK; // 0x04;
 /*public*/ /*final*/ static const int SV2_SV_ADRH_SVADRH7_CHECK_MASK; // 0x08;
 /*public*/ /*final*/ static const int SV2_SVX2_ELEMENT_VALIDITY_CHECK_MASK; // 0x70;
 /*public*/ /*final*/ static const int SV2_SVX2_ELEMENT_VALIDITY_CHECK_VALUE; // 0x10;
 /*public*/ /*final*/ static const int SV2_SV_D1_D1X7_CHECK_MASK; // 0x01;
 /*public*/ /*final*/ static const int SV2_SV_D2_D2X7_CHECK_MASK; // 0x02;
 /*public*/ /*final*/ static const int SV2_SV_D3_D3X7_CHECK_MASK; // 0x04;
 /*public*/ /*final*/ static const int SV2_SV_D4_D4X7_CHECK_MASK; // 0x08;
 /*public*/ /*final*/ static const int SV2_SV_TYPE_ELEMENT_VALIDITY_CHECK_MASK; // 0x7F;
 /*public*/ /*final*/ static const int SV2_SV_TYPE_ELEMENT_VALIDITY_CHECK_VALUE; // 0x02;

// helpers for decoding SV_CMD
 /*public*/ /*final*/ static const int SV_CMD_WRITE_ONE; // 0x01;
 /*public*/ /*final*/ static const int SV_CMD_WRITE_ONE_REPLY; // 0x41; // reply to SV_CMD_WRITE_ONE

 /*public*/ /*final*/ static const int SV_CMD_QUERY_ONE; // 0x02;
 /*public*/ /*final*/ static const int SV_CMD_REPORT_ONE; // 0x42;   // reply to SV_CMD_QUERY_ONE

 /*public*/ /*final*/ static const int SV_CMD_WRITE_ONE_MASKED; // 0x03;
 /*public*/ /*final*/ static const int SV_CMD_WRITE_ONE_MASKED_REPLY; // 0x43;   // reply to SV_CMD_WRITE_ONE_MASKED

 /*public*/ /*final*/ static const int SV_CMD_WRITE_FOUR; // 0x05;
 /*public*/ /*final*/ static const int SV_CMD_WRITE_FOUR_REPLY; // 0x45;   // reply to SV_CMD_WRITE_FOUR

 /*public*/ /*final*/ static const int SV_CMD_QUERY_FOUR; // 0x06;
 /*public*/ /*final*/ static const int SV_CMD_REPORT_FOUR; // 0x46;   // reply to SV_CMD_QUERY_FOUR

 /*public*/ /*final*/ static const int SV_CMD_DISCOVER_DEVICES_QUERY; // 0x07;
 /*public*/ /*final*/ static const int SV_CMD_DISCOVER_DEVICE_REPORT; // 0x47;   // reply to SV_CMD_DISCOVER_DEVICES_QUERY

 /*public*/ /*final*/ static const int SV_CMD_IDENTIFY_DEVICE_BY_DEVICE_ADDRESS; // 0x08;
 /*public*/ /*final*/ static const int SV_CMD_IDENTIFY_DEVICE_BY_DEVICE_ADDRESS_REPLY; // 0x48;   // reply to SV_CMD_IDENTIFY_DEVICE_BY_DEVICE_ADDRESS

 /*public*/ /*final*/ static const int SV_CMD_CHANGE_ADDRESS_REQUEST; // 0x09;
 /*public*/ /*final*/ static const int SV_CMD_CHANGE_ADDRESS_REPLY; // 0x49;   // reply to SV_CMD_CHANGE_ADDRESS_REQUEST

 /*public*/ /*final*/ static const int SV_CMD_RECONFIGURE_REQUEST; // 0x0F;
 /*public*/ /*final*/ static const int SV_CMD_RECONFIGURE_REPLY; // 0x4F;   // reply to SV_CMD_RECONFIGURE_REQUEST

// LocoNet "SV 2 format" helper definitions: SV_CMD "reply" bit
 /*public*/ /*final*/ static const int SV2_SV_CMD_REPLY_BIT_NUBMER; // 0x6;
 /*public*/ /*final*/ static const int SV2_SV_CMD_REPLY_BIT_MASK; // (2^SV2_SV_CMD_REPLY_BIT_NUBMER);

 // LocoNet "SV 2 format" helper definitions for data
 /*public*/ /*final*/ static const int SV2_SV_DATA_INDEX_EEPROM_SIZE; // 1;
 /*public*/ /*final*/ static const int SV2_SV_DATA_INDEX_SOFTWARE_VERSION; // 2;
 /*public*/ /*final*/ static const int SV2_SV_DATA_INDEX_SERIAL_NUMBER_LOW; // 3;
 /*public*/ /*final*/ static const int SV2_SV_DATA_INDEX_SERIAL_NUMBER_HIGH; // 4;
 /*public*/ LnSv2MessageContents(LocoNetMessage* m, QObject *parent = 0)
         throw (IllegalArgumentException);
 /*public*/ static bool isSupportedSv2Message(LocoNetMessage* m);
// /*public*/ class Sv2Command {
// public:
  enum Sv2Command {
   NONE = 0,
     SV2_WRITE_ONE = (0x01),
     SV2_QUERY_ONE = (0x02),
     SV2_WRITE_ONE_MASKED = (0x03),
     SV2_WRITE_FOUR = (0x05),
     SV2_QUERY_FOUR = (0x06),
     SV2_DISCOVER_ALL = (0x07),
     SV2_IDENTIFY_DEVICES_BY_TYPE = (0x08),
     SV2_CHANGE_DEVICE_ADDRESS = (0x09),
     SV2_RECONFIGURE_DEVICE = (0x0f),
     SV2_WRITE_ONE_REPLY = (0x41),
     SV2_REPORT_ONE = (0x42),
     SV2_WRITE_ONE_MASKED_REPLYL = (0x43),
     SV2_WRITE_FOUR_REPLY = (0x45),
     SV2_REPORT_FOUR = (0x46),
     SV2_DISCOVER_DEVICE_REPORT = (0x47),
     SV2_DEVICE_TYPE_REPORT = (0x48),
     SV2_CHANGE_DEVICE_ADDRESS_REPLY = (0x49),
     SV2_RECONFIGURE_DEVICE_REPLY = (0x4f)
  };
  private:
  /*private*/ int cmd;

  static QList<Sv2Command> sv2Commands;// = QList<Sv2Command>() << SV2_WRITE_ONE <<
//  SV2_QUERY_ONE <<
//  SV2_WRITE_ONE_MASKED <<
//  SV2_WRITE_FOUR <<
//  SV2_QUERY_FOUR <<
//  SV2_DISCOVER_ALL <<
//  SV2_IDENTIFY_DEVICES_BY_TYPE <<
//  SV2_CHANGE_DEVICE_ADDRESS <<
//  SV2_RECONFIGURE_DEVICE <<
//  SV2_WRITE_ONE_REPLY <<
//  SV2_REPORT_ONE <<
//  SV2_WRITE_ONE_MASKED_REPLYL <<
//  SV2_WRITE_FOUR_REPLY <<
//  SV2_REPORT_FOUR <<
//  SV2_DISCOVER_DEVICE_REPORT <<
//  SV2_DEVICE_TYPE_REPORT <<
//  SV2_CHANGE_DEVICE_ADDRESS_REPLY <<
//  SV2_RECONFIGURE_DEVICE_REPLY;

//     Sv2Command(int cmd) {
//         this->cmd = cmd;
//     }
//     int getCmd() {return cmd;}
  public:
//     /*public*/ static int getCmd(Sv2Command mt) {
//         return mt.getCmd();
//     }
  //};
  /*public*/ static bool isLnMessageASpecificSv2Command(LocoNetMessage* m, Sv2Command svCmd);
  /*public*/ static Sv2Command extractMessageType(LocoNetMessage* m);
  /*public*/ QString toString();
  /*public*/ QString toString(QLocale locale);
  /*public*/ static bool isSupportedSv2Command(int possibleCmd);
  /*public*/ bool isSupportedSv2Command();
  /*public*/ bool isSupportedSv2ReadOneReply();
  /*public*/ bool isSupportedSv2ReadFourReply();
  /*public*/ bool isSupportedSv2ReadOneReplyOrSv2ReadFourReply();
  /*public*/ int getSingleReadReportData();
  /*public*/ static LocoNetMessage* createSv2Message (int source, int command,
          int destination, int svNum, int d1, int d2, int d3, int d4)
      throw (IllegalArgumentException) ;
  /*public*/ int getDestAddr();
  /*public*/ int getSVNum();
  /*public*/ int getSv2ManufacturerID();
  /*public*/ bool isSvReconfigureReply();
  /*public*/ int getSv2DeveloperID();
  /*public*/ int getSv2ProductID();
  /*public*/ int getSv2SerialNum();
  /*public*/ static LocoNetMessage* createSv2DeviceDiscoveryReply(int ida, int currentDest,
          int mfg, int devel, int prodID, int serial);
  /*public*/ static LocoNetMessage* createSv2ChangeAddressReply(int ida, int destAddr);
  /*public*/ static LocoNetMessage* createSv2ChangeAddressReply(int ida, int newDestAddr,
          int mfg, int developer, int productId, int serialNum);
  /*public*/ static LocoNetMessage* createSv2ReconfigureReply(int ida, int newDestAddr,
          int mfg, int developer, int productId, int serialNum) ;
  /*public*/ static LocoNetMessage* createSvReadReply(LocoNetMessage* m, QVector<int> svValues);
  /*public*/ static LocoNetMessage* createSvReadReply(LocoNetMessage* m, int svValue);
  /*public*/ int getSv2D1();
  /*public*/ int getSv2D2();
  /*public*/ int getSv2D3();
  /*public*/ int getSv2D4();
  /*public*/ bool isSvChangeAddressReply();
  /*public*/ static LocoNetMessage* createSvDiscoverQueryMessage();
  /*public*/ static LocoNetMessage* createSvReadRequest();
  /*public*/ static LocoNetMessage* createSvReadRequest(int deviceAddress, int svNum);
signals:

public slots:

private:
 /*private*/ int src;
 /*private*/ int sv_cmd;
 /*private*/ int dst_l;
 /*private*/ int dst_h;
 /*private*/ int dst;
 /*private*/ int sv_adrl;
 /*private*/ int sv_adrh;
 /*private*/ int sv_adr;
 /*private*/ int d1;
 /*private*/ int d2;
 /*private*/ int d3;
 /*private*/ int d4;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(LnSv2MessageContents.class);

};

#endif // LNSV2MESSAGECONTENTS_H
