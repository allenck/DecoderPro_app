#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H
#include <QObject>
#include "abstractmrmessage.h"
#include "abstractmrlistener.h"

class Logger;
class AbstractNode : public QObject
{
  Q_OBJECT

 public:
  AbstractNode(QObject* parent = nullptr);
  /*public*/  int getNodeAddress();
  /*public*/  int nodeAddress = 0; // Node address, valid range varies by subclass
  /*public*/  void setNodeAddress(int address);
  /*abstract*/virtual /*public*/  AbstractMRMessage* createInitPacket()=0;
  /*abstract*/virtual /*public*/  AbstractMRMessage* createOutPacket()=0;
  /*abstract*/ virtual /*public*/  bool getSensorsActive()=0;
  /*abstract*/virtual /*public*/  bool handleTimeout(AbstractMRMessage* m, AbstractMRListener* l)=0;
  /*abstract*/virtual /*public*/  void resetTimeout(AbstractMRMessage* m)=0;
  /*public*/  bool mustSend();
  /*public*/  void resetMustSend();
  /*public*/  void setMustSend();

 private:
  static Logger* log;
  bool needSend = true; // 'true' if something has changed that requires data to be sent

 protected:
  /*abstract*/ virtual /*protected*/ bool checkNodeAddress(int address)=0;

};

#endif // ABSTRACTNODE_H
