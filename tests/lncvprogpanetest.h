#ifndef LNCVPROGPANETEST_H
#define LNCVPROGPANETEST_H
#include "jmripaneltest.h"
#include "loconetsystemconnectionmemo.h"
#include "lncvprogpane.h"
#include "jframeoperator.h"
#include "junitutil.h"

class LncvProgPaneTest : public JmriPanelTest
{
  Q_OBJECT
 public:
  LncvProgPaneTest();
  Q_INVOKABLE /*public*/ void setUp() override;
  Q_INVOKABLE /*public*/ void tearDown() override;

public slots:
  /*public*/ void testCTor();
  /*public*/ void testInitComponents();// throw (Exception) override;
  /*public*/ void testGetHelpTarget() override;
  /*public*/ void testGetTitle() override;
  /*public*/ void testDispose();
  /*public*/ void testPanel();

 private:
  LocoNetSystemConnectionMemo* memo;
  LncvProgPane* panel;

};

class Work1 : public QObject
{
  Q_OBJECT
  QThread* dialog_thread1;
 public:
  Work1(QThread* dialog_thread1) {
   this->dialog_thread1 = dialog_thread1;
   connect(dialog_thread1, SIGNAL(started()), this, SLOT(process()));
   connect(this, SIGNAL(finished()), dialog_thread1, SLOT(quit()));
   moveToThread(dialog_thread1);
  }
 signals:
  void finished();
 public slots:
  void process()
  {
   JDialogOperator* jfo = new JDialogOperator(tr("Warning") );
   (new JButtonOperator(jfo, tr("Proceed")))->doClick();
   //emit finished();
  }
};

class Lncvppt_ready : public ReleaseUntil
{
 Q_OBJECT
  QThread* dialog_thread1;
  public:
  Lncvppt_ready(QThread* dialog_thread1) {this->dialog_thread1 = dialog_thread1;}
  bool ready()throw (Exception) {return !!(dialog_thread1->isRunning());}
};
#endif // LNCVPROGPANETEST_H
