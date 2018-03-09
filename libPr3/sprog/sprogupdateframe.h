#ifndef SPROGUPDATEFRAME_H
#define SPROGUPDATEFRAME_H
#include "jmrijframe.h"
#include "sprogsystemconnectionmemo.h"
#include "sprogtrafficcontroller.h"
#include <QPushButton>
#include "jfilechooser.h"
#include <QLabel>
#include <QVBoxLayout>
#include "flowlayout.h"

namespace Sprog
{
 class SprogHexFile;
 class SprogUpdateFrame : public JmriJFrame
 {
  Q_OBJECT
 public:
  /*public*/ SprogUpdateFrame(SprogSystemConnectionMemo* memo, QWidget* parent =0);
  /*public*/ void dispose();
  /*public*/ void initComponents();

 public slots:
  /*public*/ virtual void notifyMessage(SprogMessage* m);
  /*synchronized*/ /*public*/ void notifyReply(SprogReply* m);
  /*synchronized*/ /*public*/ void openFileChooserButtonActionPerformed(/*ActionEvent e*/);
  /*public*/ void setSprogModeButtonActionPerformed(/*ActionEvent e*/);
  /*public*/ /*synchronized*/ void programButtonActionPerformed(/*ActionEvent e*/);

 private:
  /*private*/ /*final*/ static Logger* log;

  // to find and remember the hex file
  JFileChooser* hexFileChooser;// = new JFileChooser(FileUtil::getUserFilesPath());
  // member declarations

  QLabel* statusBar;// = new JLabel();
  // File to hold name of hex file
  SprogMessage* msg;
  /*transient*/ SprogHexFile* hexFile ;//= null;
  // members for handling the bootloader interface
  static /*final*/ bool UNKNOWN;// = false;
  static /*final*/ bool KNOWN;// = true;
  int blockLen;// = 0;
  QTimer* timer;// = NULL;

 protected:
  /*protected*/ SprogReply* reply;
  /*protected*/ QString replyString;
  /*protected*/ enum BootState {

      IDLE,
      CRSENT, // awaiting reply to " "
      QUERYSENT, // awaiting reply to "?"
      SETBOOTSENT, // awaiting reply from bootloader
      VERREQSENT, // awaiting reply to version request
      WRITESENT, // write flash command sent, waiting reply
      NULLWRITE, // no write sent
      ERASESENT, // erase sent
      SPROGMODESENT, // enable sprog mode sent
      RESETSENT, // reset sent
      EOFSENT, // v4 end of file sent
      V4RESET,          // wait for v4 to reset
  };

  /*protected*/ SprogTrafficController* tc;// = null;
  /*protected*/ SprogSystemConnectionMemo* _memo;// = null;
  /*protected*/ QPushButton*  programButton;// = new QPushButton ();
  /*protected*/ QPushButton*  openFileChooserButton;// = new QPushButton ();
  /*protected*/ QPushButton*  setSprogModeButton;// = new QPushButton ();

  /*protected*/ SprogVersion* sv;
  /*protected*/ BootState bootState;// = BootState.IDLE;
  /*protected*/ int eraseAddress;
  /*protected*/ QString title();
  /*protected*/ void init();
  QVBoxLayout* contentPaneLayout;
  /*protected*/ virtual void frameCheck();
  /*protected*/ void stateIdle();
  /*protected*/ void stateSetBootSent();
  /*protected*/ virtual void stateBootVerReqSent();
  /*protected*/ virtual void stateWriteSent();
  /*protected*/ virtual void stateEraseSent();
  /*protected*/ virtual void stateSprogModeSent();
  /*protected*/ virtual void stateResetSent();
  /*protected*/ void stateEofSent() ;
  /*protected*/ void stateV4Reset();
  /*synchronized*/ /*protected*/ void stateDefault();
  /*abstract*/ virtual /*protected*/ void requestBoot() =0;

  /*abstract*/ virtual /*protected*/ void sendWrite() =0;

  /*abstract*/ virtual /*protected*/ void doneWriting() =0;
  /*protected*/ int V_SHORT_TIMEOUT;// = 5;
  /*protected*/ int SHORT_TIMEOUT;// = 500;
  /*protected*/ int LONG_TIMEOUT;// = 4000;
  /*protected*/ void startVShortTimer();
  /*protected*/ void startShortTimer();
  /*synchronized*/ /*protected*/ void startLongTimer();
  /*synchronized*/ /*protected*/ void stopTimer();
  /*synchronized*/ /*protected*/ void restartTimer(int delay);


 protected slots:
  /*synchronized*/ /*protected*/ void timeout();

  friend class SprogIIUpdateFrame;
 };
}
#endif // SPROGUPDATEFRAME_H
