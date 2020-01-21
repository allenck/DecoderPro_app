#ifndef SPROGVERSIONFRAME_H
#define SPROGVERSIONFRAME_H
#include "jmrijframe.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SprogVersionFrame : public JmriJFrame
 {
  Q_OBJECT
 public:
  /*public*/ SprogVersionFrame(SprogSystemConnectionMemo* memo, QWidget* parent = 0);
  /*synchronized*/ /*public*/ void initComponents();
  /*public*/ QString getClassName();

 public slots:
  /*synchronized*/ /*public*/ void notifyVersion(SprogVersion* v);


 private:
      /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogVersionFrame");
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;

 };
}
#endif // SPROGVERSIONFRAME_H
