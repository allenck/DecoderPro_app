#ifndef SPROGCONSOLEFRAME_H
#define SPROGCONSOLEFRAME_H
#include "abstractmonframe.h"
#include "sprogsystemconnectionmemo.h"
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>

namespace Sprog
{
 class SprogConsoleFrame : public AbstractMonFrame
 {
  Q_OBJECT
 public:
  SprogConsoleFrame(SprogSystemConnectionMemo* memo, QWidget* parent = 0);
  /*public*/ void validateCurrent();
  /*public*/ bool isCurrentLimitPossible();
  /*public*/ bool isBlueLineSupportPossible();
  /*public*/ bool isFirmwareUnlockPossible();
  /*public*/ bool isZTCModePossible();
  /*public*/ void dispose();
  /*public*/ void initComponents() throw (Exception);
  /*public*/ QString getClassName();

 public slots:
  //void enterButtonActionPerformed(ActionEvent* e = 0);
  void sendButtonActionPerformed(JActionEvent* e = 0);
  void saveButtonActionPerformed(JActionEvent* e = 0);
  /*public*/ /*synchronized*/ void notifyReply(SprogReply* l);
  /*synchronized*/ /*public*/ void notifyVersion(SprogVersion* v);
  /*public*/ /*synchronized*/ void notifyMessage(SprogMessage* l); // receive a message and log it

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogConsoleFrame");
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;
  // members for handling the SPROG interface
  SprogTrafficController* tc = NULL;
  QString replyString;
  QString tmpString;// = NULL;

  SprogVersion* sv;

  enum State {

      IDLE,
      CURRENTQUERYSENT, // awaiting reply to "I"
      MODEQUERYSENT,    // awaiting reply to "M"
      CURRENTSENT,      // awaiting reply to "I xxx"
      MODESENT,         // awaiting reply to "M xxx"
      WRITESENT   	  // awaiting reply to "W"
  };
  State state;// = State::IDLE;


 protected:
  // member declarations
  /*protected*/ QLabel* cmdLabel;// = new QLabel();
  /*protected*/ QLabel* currentLabel;// = new QLabel();
  /*protected*/ QPushButton* sendButton;// = new QButton();
  /*protected*/ QPushButton* saveButton;// = new QButton();
  /*protected*/ JTextField* cmdTextField;// = new JTextField(12);
  /*protected*/ JTextField* currentTextField;// = new JTextField(12);

  /*protected*/ QCheckBox* ztcCheckBox;// = new QCheckBox();
  /*protected*/ QCheckBox* blueCheckBox;// = new QCheckBox();
  /*protected*/ QCheckBox* unlockCheckBox;// = new QCheckBox();

  /*protected*/ QButtonGroup* speedGroup;// = new QButtonGroup();
  /*protected*/ QLabel* speedLabel;// = new QLabel();
  /*protected*/ QRadioButton* speed14Button;// = new QRadioButton(tr("ButtonXStep", 14)); // i18n using shared sprogBundle
  /*protected*/ QRadioButton* speed28Button;// = new JRadioButton(tr("ButtonXStep", 28));
  /*protected*/ QRadioButton* speed128Button;// = new JRadioButton(tr("ButtonXStep", 128));

  /*protected*/ int modeWord;
  /*protected*/ int currentLimit;// = SprogConstants.DEFAULT_I;
  /*protected*/ QString title();
  /*protected*/ void init();
  /*protected*/ void setHelp();
  /*protected*/ int TIMEOUT;// = 1000;
  QTimer* timer = NULL;
  /*protected*/ void startTimer();
  /*protected*/ void stopTimer();
  /*protected*/ void restartTimer(int delay);

 protected slots:
  /*synchronized*/ /*protected*/ void timeout();


 };
}
#endif // SPROGCONSOLEFRAME_H
