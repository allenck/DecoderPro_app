#ifndef SPROGMONFRAME_H
#define SPROGMONFRAME_H
#include "abstractmonframe.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{

 class SprogMonFrame : public AbstractMonFrame
 {
  Q_OBJECT
 public:
  SprogMonFrame(SprogSystemConnectionMemo* memo, QWidget* parent = 0);
  /*public*/ void dispose();
  /*public*/ /*synchronized*/ void notifyMessage(SprogMessage* l) ;
  /*public*/ /*synchronized*/ void notifyReply(SprogReply* l);
  /*public*/ QString getClassName();

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogMonFrame");
  SprogSystemConnectionMemo* _memo;

 protected:
  /*protected*/ QString title();
  /*protected*/ void init();

 };
}
#endif // SPROGMONFRAME_H
