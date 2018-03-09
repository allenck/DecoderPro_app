#ifndef SPROGTURNOUT_H
#define SPROGTURNOUT_H
#include "abstractturnout.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SprogTurnout : public AbstractTurnout
 {
  Q_OBJECT
 public:
  SprogTurnout(int number, SprogSystemConnectionMemo* memo, QObject* parent = 0);
  /*public*/ int getNumber();
  /*public*/ bool canInvert();

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogTurnout");
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;
  // data members
  int _number; // turnout number


 protected:
  /*protected*/ void forwardCommandChangeToLayout(int s);
  /*protected*/ void turnoutPushbuttonLockout(bool _pushButtonLockout);
  /*protected*/ void sendMessage(bool closed);

 };
}
#endif // SPROGTURNOUT_H
