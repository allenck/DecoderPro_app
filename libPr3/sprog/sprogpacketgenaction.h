#ifndef SPROGPACKETGENACTION_H
#define SPROGPACKETGENACTION_H
#include "abstractaction.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SprogPacketGenAction : public AbstractAction
 {
  Q_OBJECT

 public:
  SprogPacketGenAction(QString title, SprogSystemConnectionMemo* _memo, QWidget* parent = 0);

 public slots:
  /*public*/ void actionPerformed(/*ActionEvent e*/);

 private:
  /*private*/ SprogSystemConnectionMemo* _memo;
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogPacketGenAction");
 };
}
#endif // SPROGPACKETGENACTION_H
