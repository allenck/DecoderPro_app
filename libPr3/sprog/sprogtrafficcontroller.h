#ifndef SPROGTRAFFICCONTROLLER_H
#define SPROGTRAFFICCONTROLLER_H
#include "sproginterface.h"
#include "sproglistener.h"
#include "sprogconstants.h"
#include "sprogsystemconnectionmemo.h"
#include "abstractportcontroller.h"
#include <QSerialPort>

class SerialPortEvent;
class Logger;
namespace Sprog
{
 class SprogSystemConnectionMemo;
 class SprogSerialDriverAdapter;
 class SprogTrafficController : public SprogInterface
 {
  Q_OBJECT
 public:
  SprogTrafficController(SprogSystemConnectionMemo* adaptermemo, QObject* parent = 0);
  /*public*/ bool status();
  /*public*/ /*synchronized*/ void addSprogListener(SprogListener* l);
  QT_DEPRECATED static /*public*/ SprogTrafficController* instance();
  /*public*/ void setAdapterMemo(SprogSystemConnectionMemo* adaptermemo);
  /*public*/ SprogSystemConnectionMemo* getAdapterMemo();
  /*public*/ /*synchronized*/ void removeSprogListener(SprogListener* l);
  /*public*/ SprogConstants::SprogState getSprogState();
  /*public*/ void setSprogState(SprogConstants::SprogState s);
  /*public*/ bool isNormalMode();
  /*public*/ bool isSIIBootMode();
  /*public*/ bool isV4BootMode();
  /*public*/ /*synchronized*/ void sendSprogMessage(SprogMessage* m, SprogListener* replyTo);
  /*public*/ void connectPort(AbstractPortController* p);
  /*public*/ void disconnectPort(AbstractPortController* p);
  /*public*/ void serialEvent(SerialPortEvent* event);
  /*public*/ int bytesAvailable();

 public slots:
  /*public*/ void handleOneIncomingReply();
  /*public*/ void handleReadyRead();

 signals:
  void do_notifyMessage(SprogMessage*);
  void sendSprogMessage(SprogMessage*);
  void readyRead();
  void on_notifyReply(SprogReply* r);


 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogTrafficController");
  /*private*/ SprogReply* reply;// = new SprogReply();
  SprogListener* lastSender;// = null;
  /*private*/ SprogConstants::SprogState sprogState;// = SprogState.NORMAL;
  /*private*/ int lastId;
  /*private*/ SprogSystemConnectionMemo* memo = NULL;

  // data members to hold the streams
  QDataStream* istream;// = NULL;
  QDataStream* ostream;// = NULL;
  /*private*/ /*synchronized*/ QVector<SprogListener*> getCopyOfListeners();
  bool endReply(SprogReply* msg);
  // methods to connect/disconnect to a source of data in a SprogPortController
  /*private*/ AbstractPortController* controller;// = NULL;
  /*private*/ bool unsolicited;
  /*private*/ void sendreply();

 private slots:
  ///*private*/ void sendreply(SprogReply* reply);

 protected:
  /*protected*/ bool waitingForReply;// = false;
  static /*volatile*/ /*protected*/ SprogTrafficController* self;// = NULL;
  // Methods to implement the Sprog Interface

  /*protected*/ QVector<SprogListener*> cmdListeners;// = QVector<SprogListener*>();
  /*protected*/ /*synchronized*/ void notifyMessage(SprogMessage* m, SprogListener* originator);
  /*protected*/ /*synchronized*/ void notifyReply(SprogReply* r);
  /*protected*/ /*synchronized*/ void notifyReply(SprogReply* r, SprogListener* lastSender);
  /*protected*/ SprogSerialDriverAdapter* getController();
  friend class SprogSystemConnectionMemo;
  friend class ReplyWorker;
  friend class SprogRcvWorker;
  friend class SprogXmtWorker;
 };

 class ReplyWorker : public QObject
 {
  Q_OBJECT
  SprogReply* replyForLater;// = thisReply;
  SprogListener* lastSenderForLater;// = thisLastSender;
  SprogTrafficController* myTC;// = thisTC;
 public:
  ReplyWorker(SprogReply* replyForLater, SprogListener* lastSenderForLater, SprogTrafficController* myTC );
 public slots:
  void run();
 signals:
  void finished();
 };

 class SprogRcvWorker : public QObject
 {
  Q_OBJECT
  SprogSerialDriverAdapter* adapter;
  SprogReply* reply;
  SprogTrafficController* myTC;
 public:
  SprogRcvWorker(SprogReply* reply, SprogTrafficController* myTC);

 public slots:
  //void handleOneIncomingReply();
  void process();

 signals:
  void finished();
  void sendReply(SprogReply* reply);

 private:
  //bool endReply(SprogReply* msg);

 };

 class SprogXmtWorker : public QObject
 {
  Q_OBJECT
  SprogTrafficController* myTC;
  QDataStream* ostream;
 public:
  SprogXmtWorker(SprogTrafficController* myTC);

 public slots:
  /*public*/ void sendSprogMessage(SprogMessage* m);
  void process();
 signals:
  void finished();
  void writeData(QByteArray bytes);

 };

}
#endif // SPROGTRAFFICCONTROLLER_H
