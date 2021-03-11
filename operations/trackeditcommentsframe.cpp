#include "trackeditcommentsframe.h"
#include "control.h"
#include "setup.h"
#include "operationsxml.h"
#include "jpanel.h"
#include "track.h"
#include <QPushButton>
#include "jtextarea.h"
#include "gridbaglayout.h"
#include <QBoxLayout>
#include "borderfactory.h"

namespace Operations
{
///*public*/ class TrackEditCommentsFrame extends OperationsFrame {

    /**
     *
     */
    //private static final long serialVersionUID = 3428891268059200871L;
    // text areas

 /*public*/ TrackEditCommentsFrame::TrackEditCommentsFrame(Track* track, QWidget* parent) : OperationsFrame(parent)
 {
     //super();
  log = new Logger("TrackEditCommentsFrame");
  commentBothTextArea = new JTextArea(5, 100);
  commentPickupTextArea = new JTextArea(5, 100);
  commentSetoutTextArea = new JTextArea(5, 100);
  saveButton = new QPushButton(tr("Save"));
  initComponents(track);
 }

 /*private*/ void TrackEditCommentsFrame::initComponents(Track* track)
 {
  if (track == NULL) {
      log->debug("Track is NULL can't edit track comments");
      return;
  }
  _track = track;
  // the following code sets the frame's initial state
  //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  JPanel* pCb = new JPanel();
  pCb->setBorder(BorderFactory::createTitledBorder(tr("Comment when there are set outs and pick ups")));
  pCb->setLayout(new GridBagLayout());
  //commentBothScroller.setMinimumSize(minScrollerDim);
  addItem(pCb, commentBothTextArea, 1, 0);

  JPanel* pCp = new JPanel();
  pCp->setBorder(BorderFactory::createTitledBorder(tr("Comment when there is only pick ups")));
  pCp->setLayout(new GridBagLayout());
  //commentPickupScroller.setMinimumSize(minScrollerDim);
  addItem(pCp, commentPickupTextArea, 1, 0);

  JPanel* pCs = new JPanel();
  pCs->setBorder(BorderFactory::createTitledBorder(tr("Comment when there is only set outs")));
  pCs->setLayout(new GridBagLayout());
  //commentSetoutScroller.setMinimumSize(minScrollerDim);
  addItem(pCs, commentSetoutTextArea, 1, 0);

  commentBothTextArea->setPlainText(track->getCommentBoth());
  commentPickupTextArea->setText(track->getCommentPickup());
  commentSetoutTextArea->setText(track->getCommentSetout());

  QWidget* pB = new QWidget();
  pB->setLayout(new GridBagLayout());
  addItem(pB, saveButton, 0, 0);

  thisLayout->addWidget(pCb);
  thisLayout->addWidget(pCp);
  thisLayout->addWidget(pCs);
  thisLayout->addWidget(pB);

  addButtonAction(saveButton);

  setTitle(track->getName());
  initMinimumSize(QSize(Control::panelHeight400, Control::panelWidth600));
 }

 // Buttons
 /*public*/ void TrackEditCommentsFrame::buttonActionPerformed(QWidget* ae) {
  QPushButton* source = (QPushButton*)ae;
     if (source == saveButton) {
         _track->setCommentBoth(commentBothTextArea->toPlainText());
         _track->setCommentPickup(commentPickupTextArea->toPlainText());
         _track->setCommentSetout(commentSetoutTextArea->toPlainText());
         // save location file
         OperationsXml::save();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             OperationsFrame::dispose();
         }
     }
 }

 /*public*/ QString TrackEditCommentsFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.tools.TrackEditCommentsFrame";
 }
}
