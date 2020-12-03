#ifndef LNDPLXGRPINFOIMPL_H
#define LNDPLXGRPINFOIMPL_H

#include <QObject>
#include "timer.h"
#include "propertychangesupport.h"
#include "jcomponent.h"
#include "loconetlistener.h"
#include "duplexgroupmessagetype.h"

class LnTrafficController;
class Logger;
class LocoNetSystemConnectionMemo;
class LnDplxGrpInfoImpl : public QObject, public JComponent, public LocoNetListener
{
  Q_OBJECT
  Q_INTERFACES(JComponent LocoNetListener)
 public:
  explicit LnDplxGrpInfoImpl(LocoNetSystemConnectionMemo* LNCMemo, QObject *parent = nullptr);
  /*public*/ static /*final*/ bool isPasswordLimitedToNumbers();
  /*public*/ static /*final*/ bool validateGroupName(QString sGroupName);
  /*public*/ static /*final*/ bool validateGroupPassword(QString sGroupPassword);
  /*public*/ static /*final*/ bool validateGroupChannel(int iGroupChannel);
  /*public*/ static /*final*/ bool validateGroupID(int iGroupId);
  /*public*/ static /*final*/ LocoNetMessage* createUr92GroupIdentityQueryPacket();
  /*public*/ static /*final*/ LocoNetMessage *createSetUr92GroupNamePacket(QString sGroupName) throw (LocoNetException);
  /*public*/ static /*final*/ LocoNetMessage *createSetUr92GroupChannelPacket(int iChannelNumber) throw (LocoNetException);
  /*public*/ static /*final*/ LocoNetMessage* createSetUr92GroupPasswordPacket(QString sGroupPassword) throw (LocoNetException);
  /*public*/ static /*final*/ LocoNetMessage* createSetUr92GroupIDPacket(QString s) throw (LocoNetException);
  /*public*/ static /*final*/ bool isDuplexGroupMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ DuplexGroupMessageType getDuplexGroupIdentityMessageType(LocoNetMessage* m);
  /*public*/ static QString extractDuplexGroupName(LocoNetMessage* m);
  /*public*/ static int extractDuplexGroupChannel(LocoNetMessage* m);
  /*public*/ static int extractDuplexGroupID(LocoNetMessage* m);
  /*public*/ static QString extractDuplexGroupPassword(LocoNetMessage* m);
  /*public*/ void message(LocoNetMessage* m);
  /*public*/ QString getFetchedDuplexGroupName();
  /*public*/ QString getFetchedDuplexGroupChannel();
  /*public*/ QString getFetchedDuplexGroupPassword();
  /*public*/ QString getFetchedDuplexGroupId();
  /*public*/ void queryDuplexGroupIdentity();
  /*public*/ void setDuplexGroupName(QString dgn) throw (LocoNetException);
  /*public*/ void setDuplexGroupChannel(int dgc) throw (LocoNetException);
  /*public*/ void setDuplexGroupPassword(QString dgp) throw (LocoNetException);
  /*public*/ void setDuplexGroupId(QString dgi) throw (LocoNetException);
  /*public*/ void countUr92sAndQueryDuplexIdentityInfo();
  /*public*/ static /*final*/ LocoNetMessage* createUr92GroupNameReportPacket(
          QString dupName,
          QString dupPass,
          int dupChan,
          int dupId);
  /*public*/ static /*final*/ LocoNetMessage* createUr92GroupChannelReportPacket(
          int dupChan);
  /*public*/ static /*final*/ LocoNetMessage* createUr92GroupPasswordReportPacket(
          QString dupPass);
  /*public*/ static /*final*/ LocoNetMessage* createUr92GroupIdReportPacket(
          int dupId);
  /*public*/ int getNumUr92s();
  /*public*/ bool isWaitingForFirstUr92IPLReport();
  /*public*/ int getMessagesHandled();
  /*public*/ bool isIplQueryTimerRunning();
  /*public*/ bool isDuplexGroupQueryRunning();
  /*public*/ bool isAwaitingDuplexGroupReportMessage();
  /*public*/ void connect(LnTrafficController* t);
  /*public*/ void dispose();
  /*public*/ /*final*/ static QString DPLX_PC_STAT_LN_UPDATE;// = "DPLXPCK_STAT_LN_UPDATE"; // NOI18N
  /*public*/ /*final*/ static QString DPLX_PC_STAT_LN_UPDATE_IF_NOT_CURRENTLY_ERROR;// = "DPLXPCK_STAT_LN_ON_OVER_UPDATE"; // NOI18N

  // Property Change keys relating to validity of identity info
  /*public*/ /*final*/ static QString DPLX_PC_NAME_VALIDITY;// = "DPLXPCK_NAME_VALID"; // NOI18N
  /*public*/ /*final*/ static QString DPLX_PC_CHANNEL_VALIDITY;// = "DPLXPCK_CH_VALID"; // NOI18N
  /*public*/ /*final*/ static QString DPLX_PC_PASSWORD_VALIDITY;// = "DPLXPCK_PW_VALID"; // NOI18N
  /*public*/ /*final*/ static QString DPLX_PC_ID_VALIDITY;// = "DPLXPCK_ID_VALID"; // NOI18N

  // Property Change keys relating to identity info value changes
  /*public*/ /*final*/ static QString DPLX_PC_NAME_UPDATE;// = "DPLXPCK_NAME_UPDATE"; // NOI18N
  /*public*/ /*final*/ static QString DPLX_PC_CHANNEL_UPDATE;// = "DPLXPCK_CH_UPDATE"; // NOI18N
  /*public*/ /*final*/ static QString DPLX_PC_PASSWORD_UPDATE;// = "DPLXPCK_PW_UPDATE"; // NOI18N
  /*public*/ /*final*/ static QString DPLX_PC_ID_UPDATE;// = "DPLXPCK_ID_UPDATE"; // NOI18N

  // Property Change keys relating to Duplex Group Identity LocoNet messages
  /*public*/ /*final*/ static QString DPLX_PC_RCD_DPLX_IDENTITY_QUERY;// = "DPLXPCK_IDENTITY_QUERY"; // NOI18N
  /*public*/ /*final*/ static QString DPLX_PC_RCD_DPLX_IDENTITY_REPORT;// = "DPLXPCK_IDENTITY_REPORT"; // NOI18N

 signals:

 public slots:
 private:
  static Logger* log;
  /*private*/ static /*final*/ bool limitPasswordToNumericCharacters;// = false;
  /*private*/ LocoNetSystemConnectionMemo* memo;
  /*private*/ int numUr92;
  /*private*/ Timer* swingTmrIplQuery;
  /*private*/ Timer* swingTmrDuplexInfoQuery;
  /*private*/ bool waitingForIplReply;
  /*private*/ bool gotQueryReply;
  /*private*/ int messagesHandled;
  /*private*/ bool awaitingGroupReadReport;
  /*private*/ QString acceptedGroupName;
  /*private*/ QString acceptedGroupChannel;
  /*private*/ QString acceptedGroupPassword;
  /*private*/ QString acceptedGroupId;
  PropertyChangeSupport* pcs = new PropertyChangeSupport(this);
  LnDplxGrpInfoImpl* thisone;
  /*private*/ void invalidateDataAndQueryDuplexInfo();
  /*private*/ void invalidateDuplexGroupIdentityInfo();
  /*private*/ void sendUr92IplQuery();
  /*private*/ static QString extractGroupName(LocoNetMessage* m);
  /*private*/ static QString extractDuplexGroupPasswordSimplified(int byte1, int byte2, int byte3, int byte4,
                                                                  bool x1, bool x2, bool x3, bool x4);
  /*private*/ bool handleMessageIplResult(LocoNetMessage* m);
  /*private*/ bool handleMessageDuplexInfoQuery(LocoNetMessage* m);
  /*private*/ bool handleMessageDuplexInfoReport(LocoNetMessage* m);

 friend class SwingTmrIpl02;
 friend class SwingTmrDuplex02;
};

class SwingTmrIpl02 : public Timer
{
  Q_OBJECT
  LnDplxGrpInfoImpl* thisone;
 public:
  SwingTmrIpl02(int interval, ActionListener* listener, LnDplxGrpInfoImpl* thisone) : Timer(interval, listener) {this->thisone = thisone;}
  //@Override
 public slots:
  /*public*/ void actionPerformed(/*ActionEvent e*/) {
      thisone->swingTmrIplQuery->stop();
      thisone->waitingForIplReply = false;
      int oldvalue = 9999;
      int newvalue = 0;
      if (thisone->numUr92 > 0) {
          newvalue = thisone->numUr92;
          thisone->pcs->firePropertyChange("NumberOfUr92sUpdate", oldvalue, newvalue); // NOI18N
          thisone->invalidateDataAndQueryDuplexInfo();
      } else {
          thisone->pcs->firePropertyChange("NumberOfUr92sUpdate", oldvalue, newvalue); // NOI18N
          thisone->pcs->firePropertyChange(thisone->DPLX_PC_STAT_LN_UPDATE, " ", "ErrorNoUR92Found"); // NOI18N
      }
  }
};

class SwingTmrDuplex02 : public Timer
{
  Q_OBJECT
  LnDplxGrpInfoImpl* thisone;
 public:
  SwingTmrDuplex02(int interval, ActionListener* listener, LnDplxGrpInfoImpl* thisone) : Timer(interval, listener) {this->thisone = thisone;}
  public slots:
  //@Override
  /*public*/ void actionPerformed(/*java.awt.event.ActionEvent e*/) {
      thisone->swingTmrDuplexInfoQuery->stop();
      thisone->waitingForIplReply = false;
      if (thisone->gotQueryReply == true) {
          // do not want to erase any status message other than the "Processing" message.
          thisone->pcs->firePropertyChange(thisone->DPLX_PC_STAT_LN_UPDATE_IF_NOT_CURRENTLY_ERROR, "", " "); // NOI18N
          thisone->gotQueryReply = false;
      } else {
          thisone->pcs->firePropertyChange(thisone->DPLX_PC_STAT_LN_UPDATE, " ", "ErrorNoQueryResponse"); // NOI18N
          thisone->numUr92 = 0;
          int oldvalue = 9999;
          int newvalue = 0;
          thisone->pcs->firePropertyChange("NumberOfUr92sUpdate", oldvalue, newvalue); // NOI18N
      }
  }
};
#endif // LNDPLXGRPINFOIMPL_H
