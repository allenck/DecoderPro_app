#include "importrosterengineaction.h"
#include "importrosterengines.h"
#include <QThread>
#include "jmrijframe.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMessageBox>

namespace Operations
{
/**
 * Starts the ImportRosterEngines thread
 *
 * @author Dan Boudreau Copyright (C) 2008
 * @version $Revision: 28746 $
 */
///*public*/ class ImportRosterEngineAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -2868823519457819338L;

 /*public*/ ImportRosterEngineAction::ImportRosterEngineAction(QString actionName, QWidget* frame)
 : AbstractAction(actionName, (QObject*)frame)
 {
 textEngine = new QLabel();
 textId = new QLabel();

     //super(actionName);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void ImportRosterEngineAction::actionPerformed(ActionEvent* ae) {
#if 0
     Thread mb = new ImportRosterEngines();
     mb.setName("Import Roster Engines"); // NOI18N
     mb.start();
#endif
     // create a status frame
     QWidget* ps = new QWidget();
     ps->setLayout(new QHBoxLayout);
     fstatus = new JmriJFrameX(tr("TitleImportEngines"));
     //fstatus.setLocationRelativeTo(NULL);
     fstatus->resize(200, 100);

     ps->layout()->addWidget(textEngine);
     ps->layout()->addWidget(textId);
     //fstatus.getContentPane().add(ps);
     fstatus->getContentPane()->setLayout(new QHBoxLayout);
     textEngine->setText(tr("AddEngine"));
     textEngine->setVisible(true);
     textId->setVisible(true);
     fstatus->setVisible(true);

     QThread* thread = new QThread();
     ImportRosterEngines* worker = new ImportRosterEngines();
     worker->moveToThread(thread);
     connect(thread, SIGNAL(started()), worker, SLOT(process()));
     connect(worker, SIGNAL(finished(int)), thread, SLOT(quit()));
     connect(worker, SIGNAL(progress(QString)), this, SLOT(onProgress(QString)));
     connect(worker, SIGNAL(finished(int)), this, SLOT(onFinished(int)));
     thread->start();
 }

 void ImportRosterEngineAction::onProgress(QString textId)
 {
  this->textId->setText(textId);
 }
 void ImportRosterEngineAction::onFinished(int enginesAdded)
 {
  if (enginesAdded > 0) {
   QMessageBox::information(NULL, tr("Successful Import!"), tr("%1 locomotives added to operations roster").arg(enginesAdded));
  } else {
   QMessageBox::information(NULL, tr("Successful  Failed!"), tr("%1 locomotives added to operations roster").arg(enginesAdded));
  }
  fstatus->close();
 }
}
