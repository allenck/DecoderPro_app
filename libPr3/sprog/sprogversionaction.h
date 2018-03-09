#ifndef SPROGVERSIONACTION_H
#define SPROGVERSIONACTION_H
#include "abstractaction.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SprogVersionAction : public AbstractAction
 {
  Q_OBJECT
  public:
  /*public*/ SprogVersionAction(QString s,SprogSystemConnectionMemo* memo, QObject* parent);

  public slots:
  /*public*/ void actionPerformed(/*ActionEvent* e*/);


  private:
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogVersionAction");

 };
}
#endif // SPROGVERSIONACTION_H
