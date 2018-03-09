#ifndef SPROGIIUPDATEACTION_H
#define SPROGIIUPDATEACTION_H
#include "sprogupdateaction.h"
#include "sprogsystemconnectionmemo.h"

class Logger;
namespace Sprog
{
 class SprogIIUpdateAction : public SprogUpdateAction
 {
  Q_OBJECT
 public:
  /*public*/ SprogIIUpdateAction(QString s,SprogSystemConnectionMemo* memo, QWidget* frame);

 public slots:
  /*public*/ void actionPerformed();


 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogIIUpdateAction");
 };
}
#endif // SPROGIIUPDATEACTION_H
