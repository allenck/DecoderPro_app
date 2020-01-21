#ifndef SPROGIIUPDATEFRAME_H
#define SPROGIIUPDATEFRAME_H
#include "sprogupdateframe.h"
#include "sprogversionlistener.h"

namespace Sprog
{
 class SprogIIUpdateFrame : public SprogUpdateFrame
 {
  Q_OBJECT
 public:
  /*public*/ SprogIIUpdateFrame(SprogSystemConnectionMemo* memo, QWidget* parent =0 );
  /*public*/ void initComponents();
  /*public*/ QString getClassName();


 public slots:
  /*synchronized*/ /*public*/ void notifyVersion(SprogVersion *v);
  /*synchronized*/ /*public*/ void programButtonActionPerformed(/*ActionEvent* e*/);
  /*synchronized*/ /*public*/ void setSprogModeButtonActionPerformed(/*ActionEvent e*/);


 private:
  /*private*/ /*final*/ static Logger* log;
  int bootVer;// = 0;

 protected:
  // member declarations
  /*synchronized*/ /*protected*/ void frameCheck();
  /*synchronized*/ /*protected*/ void stateBootVerReqSent();
  /*synchronized*/ /*protected*/ void stateWriteSent();
  /*synchronized*/ /*protected*/ void stateEraseSent();
  /*synchronized*/ /*protected*/ void stateSprogModeSent();
  /*synchronized*/ /*protected*/ void stateResetSent();
  /*synchronized*/ /*protected*/ void requestBoot();
  /*synchronized*/ /*protected*/ void sendWrite();
  /*synchronized*/ /*private*/ void sendErase();
  /*synchronized*/ /*protected*/ void doneWriting();

 };
}
#endif // SPROGIIUPDATEFRAME_H
