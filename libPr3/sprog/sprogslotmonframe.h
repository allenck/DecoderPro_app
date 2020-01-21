#ifndef SPROGSLOTMONFRAME_H
#define SPROGSLOTMONFRAME_H
#include "jmrijframe.h"
#include "sprogsystemconnectionmemo.h"
#include <QCheckBox>
#include <QPushButton>
#include "jtable.h"
#include "jtextarea.h"

namespace Sprog
{
 class SprogSlotMonDataModel;
 class SprogSlotMonFrame : public JmriJFrame
 {
  Q_OBJECT
 public:
  SprogSlotMonFrame(SprogSystemConnectionMemo* memo, QWidget* parent = 0);
  QT_DEPRECATED static /*public*/ /*final*/ SprogSlotMonFrame* instance();
  /*public*/ void update();
  /*public*/ void updateStatus(QString a);
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void notifyMessage(SprogMessage* m);
  /*public*/ void notifyReply(SprogReply* m);
  /*public*/ void addNotify();
  /*public*/ void dispose();


 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogSlotMonFrame");
  /**
   * Controls whether not-in-use slots are shown.
   */
  QCheckBox* showAllCheckBox;// = new javax.swing.JCheckBox();

  QPushButton* estopAllButton;// = new JButton(Bundle.getMessage("ButtonEstopAll"));
  SprogSlotMonDataModel* slotModel;// = null;

  JTable* slotTable;
  //JScrollPane slotScroll;

  JTextArea* status;// = new JTextArea(Bundle.getMessage("TrackCurrentXString", "---"));

  SprogSystemConnectionMemo* _memo;// = null;
  /*private*/ SprogTrafficController* tc;// = null;

  /*private*/ static /*final*/ int STATUS_PERIOD;// = 500;
  QTimer* timer;// = null;
  /*private*/ bool mShown;// = false;

 protected:
  /*protected*/ void setHelp();
  /*protected*/ void startTimer(int delay);
  /*protected*/ void stopTimer();

 protected slots:
  /*synchronized*/ /*protected*/ void timeout();

 };
}
#endif // SPROGSLOTMONFRAME_H
