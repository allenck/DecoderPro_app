#ifndef IMPORTROSTERENGINEACTION_H
#define IMPORTROSTERENGINEACTION_H
#include "abstractaction.h"

class JmriJFrame;
class QLabel;
namespace Operations
{
 class ImportRosterEngineAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ ImportRosterEngineAction(QString actionName, QWidget* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* ae = 0);
  void onProgress(QString textId);
  void onFinished(int);

 private:
  QLabel* textEngine;// = new javax.swing.JLabel();
  QLabel* textId;//= new javax.swing.JLabel();
  JmriJFrame* fstatus;
 };
}
#endif // IMPORTROSTERENGINEACTION_H
