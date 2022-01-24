#ifndef LNCVMESSAGECONTENTS_H
#define LNCVMESSAGECONTENTS_H

#include <QObject>
#include "loconetmessage.h"
#include "lnconstants.h"

class LncvMessageContents;
class LncvCommand
{
 public:
  enum COMMANDS
  {
   LNCV_WRITE, // (LNCV_CMD_WRITE, LnConstants::OPC_IMM_PACKET, 0x00), // CMD=0x20, CmdData=0x0
   // LNCV_WRITE_REPLY = LACK
   LNCV_READ, // (LNCV_CMD_READ, LnConstants::OPC_IMM_PACKET, 0x00), // CMD=0x21, CmdData=0x0
   LNCV_READ_REPLY, // (LNCV_CMD_READ_REPLY, LnConstants::OPC_PEER_XFER, 0x00), // CMD=0x1f, CmdData=0x0
   LNCV_PROG_START, // (LNCV_CMD_READ, LnConstants::OPC_IMM_PACKET, LNCV_DATA_PRON_MASK), // CMD=0x21, CmdData=0x80
   LNCV_PROG_END //(LNCV_CMD_READ, LnConstants::OPC_PEER_XFER, LNCV_DATA_PROFF_MASK); // CMD=0x21, CmdData=0x40
  };
 private:
  /*private*/ /*final*/ int cmd;
  /*private*/ /*final*/ int opc;
  /*private*/ /*final*/ int cmddata;
  /*private*/ COMMANDS commands;

 public:
  LncvCommand() {}

  LncvCommand(int cmd, int opc, int cmddata) {
              this->cmd = cmd;
              this->opc = opc;
              this->cmddata = cmddata;
  }
  LncvCommand(COMMANDS c);
  int getCmd() {return cmd;}
  int getOpc() {return opc;}
  int getCmdData() {return cmddata;}
  bool equals(LncvCommand){
   return this->cmd == cmd && this->opc == opc && this->cmddata == cmddata;
  }
  static QMap<COMMANDS,LncvCommand> map;// = {new LncvCommand(LncvMessageContents::LNCV_CMD_WRITE, LnConstants::OPC_IMM_PACKET, 0x00),
//                       new LncvCommand(LncvMessageContents::LNCV_CMD_READ, LnConstants::OPC_IMM_PACKET, 0x00),
//                       new LncvCommand(LncvMessageContents::LNCV_CMD_READ_REPLY, LnConstants::OPC_PEER_XFER, 0x00),
//                       new LncvCommand(LncvMessageContents::LNCV_CMD_READ, LnConstants::OPC_IMM_PACKET, LncvMessageContents::LNCV_DATA_PRON_MASK),
//                       new LncvCommand(LncvMessageContents::LNCV_CMD_READ, LnConstants::OPC_PEER_XFER, LncvMessageContents::LNCV_DATA_PROFF_MASK)};
  /*public*/ static int getCmd(LncvCommand* mt);

  /*public*/ bool matches(int matchCommand, int matchOpc, int matchData);
  friend class LncvMessageContents;
  friend class LncvDevicesManager;
};
class Logger;
class LbcvCommand;
class LncvMessageContents : public QObject
{
  Q_OBJECT
 public:
  /*public*/ LncvMessageContents(LocoNetMessage* m, QObject* parent=nullptr) throw (IllegalArgumentException);

  // LocoNet "LNCV format" helper definitions: length byte value for LNCV message
  /*public*/ /*final*/ const static int LNCV_LENGTH_ELEMENT_VALUE = 0x0f;
  /*public*/ /*final*/ const static int LNCV_LNMODULE_VALUE = 0x05;
  /*public*/ /*final*/ const static int LNCV_CS_SRC_VALUE = 0x01;
  /*public*/ /*final*/ const static int LNCV_CSDEST_VALUE = 0x4b49;
  /*public*/ /*final*/ const static int LNCV_ALL = 0xffff; // decimal 65535
  /*public*/ /*final*/ const static int LNCV_ALL_MASK = 0xff00; // decimal 65535
  // the valid range for module addresses (CV0) as per the LNCV spec.
  /*public*/ /*final*/ const static int LNCV_MIN_MODULEADDR = 0;
  /*public*/ /*final*/ const static int LNCV_MAX_MODULEADDR = 65534;

  // LocoNet "LNCV format" helper definitions: indexes into the LocoNet message
  /*public*/ /*final*/ const static int LNCV_LENGTH_ELEMENT_INDEX = 1;
  /*public*/ /*final*/ const static int LNCV_SRC_ELEMENT_INDEX = 2;
  /*public*/ /*final*/ const static int LNCV_DST_L_ELEMENT_INDEX = 3;
  /*public*/ /*final*/ const static int LNCV_DST_H_ELEMENT_INDEX = 4;
  /*public*/ /*final*/ const static int LNCV_CMD_ELEMENT_INDEX = 5;
  /*public*/ /*final*/ const static int PXCT1_ELEMENT_INDEX = 6;
  /*public*/ /*final*/ const static int LNCV_ART_L_ELEMENT_INDEX = 7;
  /*public*/ /*final*/ const static int LNCV_ART_H_ELEMENT_INDEX = 8;
  /*public*/ /*final*/ const static int LNCV_CVN_L_ELEMENT_INDEX = 9;
  /*public*/ /*final*/ const static int LNCV_CVN_H_ELEMENT_INDEX = 10;
  /*public*/ /*final*/ const static int LNCV_MOD_L_ELEMENT_INDEX = 11; // val_l reply is in same positions as mod_l read
  /*public*/ /*final*/ const static int LNCV_MOD_H_ELEMENT_INDEX = 12; // val_h reply is in same positions as mod_h read
  /*public*/ /*final*/ const static int LNCV_CMDDATA_ELEMENT_INDEX = 13;
  // Checksum = index 14

  //  helpers for decoding CV format 2 messages (no other OCP_PEER_XFER messages with length 0x0f)
  /*public*/ /*final*/ const static int LNCV_SRC_ELEMENT_MASK = 0x7f;
  /*public*/ /*final*/ const static int PXCT1_ELEMENT_VALIDITY_CHECK_MASK = 0x70;
  /*public*/ /*final*/ const static int LNCV_ART_L_ARTL7_CHECK_MASK = 0x01;
  /*public*/ /*final*/ const static int LNCV_ART_H_ARTH7_CHECK_MASK = 0x02;
  /*public*/ /*final*/ const static int LNCV_CVN_L_CVNL7_CHECK_MASK = 0x04;
  /*public*/ /*final*/ const static int LNCV_CVN_H_CVNH7_CHECK_MASK = 0x08;
  /*public*/ /*final*/ const static int LNCV_MOD_L_MODL7_CHECK_MASK = 0x10;
  /*public*/ /*final*/ const static int LNCV_MOD_H_MODH7_CHECK_MASK = 0x20;
  /*public*/ /*final*/ const static int LNCV_CMDDATA_DAT7_CHECK_MASK = 0x40;

  // LocoNet "LNCV format" helper definitions for data
  //    /*public*/ /*final*/ const static int LNCV_DATA_START = 0x00;
  //    /*public*/ /*final*/ const static int LNCV_DATA_END = 0x40;
  /*public*/ /*final*/ const static int LNCV_DATA_PROFF_MASK = 0x40;
  /*public*/ /*final*/ const static int LNCV_DATA_PRON_MASK = 0x80;
  /*public*/ /*final*/ const static int LNCV_DATA_RO_MASK = 0x01;

  // helpers for decoding LNCV_CMD
  /*public*/ /*final*/ const static int LNCV_CMD_WRITE = 0x20;
  /*public*/ /*final*/ const static int LNCV_CMD_READ = 0x21;
  /*public*/ /*final*/ const static int LNCV_CMD_READ_REPLY = 0x1f; // reply to both LNCV_CMD_READ and ENTER_PROG_MOD (in which case CV0 VAL = MOD)
  // reply to LNCV_CMD_WRITE = LACK, already defined as general LocoNet message type
  /*public*/ static bool isSupportedLncvMessage(LocoNetMessage* m);
  /*public*/ static bool isLnMessageASpecificLncvCommand(LocoNetMessage* m, LncvCommand cvCmd);
  /*public*/ static LncvCommand *extractMessageType(LocoNetMessage* m);
  /*public*/ QString toString();
  /*public*/ QString toString(QLocale locale);
  /*public*/ static bool isSupportedLncvCommand(int simpleCommand);
  /*public*/ static bool isSupportedLncvCommand(int command, int opc, int cmdData);
  /*public*/ bool isSupportedLncvCommand();
  /*public*/ bool isSupportedLncvReadReply();
  /*public*/ static LocoNetMessage* createLncvMessage(int opc,
                                                 int source,
                                                 int destination,
                                                 int command,
                                                 int articleNum,
                                                 int cvNum,
                                                 int moduleNum,
                                                 int cmdData) throw (IllegalArgumentException);

  /*public*/ static LocoNetMessage* createLncvMessage(int source, int destination, LncvCommand::COMMANDS, int articleNum, int cvNum, int moduleNum);
  /*public*/ int getCmd();
  /*public*/ int getCvNum();
  /*public*/ int getCvValue();
  /*public*/ int getLncvArticleNum();
  /*public*/ int getLncvModuleNum();
  /*public*/ static LocoNetMessage* createAllProgStartRequest(int articleNum);
  /*public*/ static LocoNetMessage* createAllProgEndRequest(int articleNum);
  /*public*/ static LocoNetMessage* createModProgStartRequest(int articleNum, int moduleAddress);
  /*public*/ static LocoNetMessage* createModProgEndRequest(int articleNum, int moduleAddress);
  /*public*/ static LocoNetMessage* createCvWriteRequest(int articleNum, int cvNum, int newValue);
  /*public*/ static LocoNetMessage* createCvReadRequest(int articleNum, int moduleAddress, int cvNum);
  /*public*/ static LocoNetMessage* createLncvReadReply(LocoNetMessage* m);

 signals:

 public slots:
 private:
  static Logger* log;
  /*private*/ /*final*/ int opc;
  /*private*/ /*final*/ int src;
  /*private*/ /*final*/ int dst_l;
  /*private*/ /*final*/ int dst_h;
  /*private*/ /*final*/ int dst;
  /*private*/ /*final*/ int cmd;
  /*private*/ /*final*/ int art_l; // D1
  /*private*/ /*final*/ int art_h; // D2
  /*private*/ /*final*/ int art;
  /*private*/ /*final*/ QString sArt;
  /*private*/ /*final*/ int cvn_l; // D3
  /*private*/ /*final*/ int cvn_h; // D4
  /*private*/ /*final*/ int cvn;
  /*private*/ /*final*/ QString sCvn;
  /*private*/ /*final*/ int mod_l; // D5
  /*private*/ /*final*/ int mod_h; // D6
  /*private*/ /*final*/ int mod;
  /*private*/ /*final*/ QString sMod;
  /*private*/ /*final*/ int cmd_data; // D7
  /*private*/ /*final*/ LncvCommand command;

};


#endif // LNCVMESSAGECONTENTS_H
