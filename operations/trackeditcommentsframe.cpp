#include "trackeditcommentsframe.h"
#include "control.h"
#include "setup.h"
#include "operationsxml.h"
#include <QGroupBox>
#include "track.h"
#include <QPushButton>
#include "jtextarea.h"
#include "gridbaglayout.h"
#include <QBoxLayout>

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

  QGroupBox* pCb = new QGroupBox();
  //pCb.setBorder(BorderFactory.createTitledBorder(Bundle.getMessage("CommentBoth")));
  pCb->setStyleSheet(gbStyleSheet);
  pCb->setTitle(tr("Comment when there are set outs and pick ups"));
  pCb->setLayout(new GridBagLayout());
  //commentBothScroller.setMinimumSize(minScrollerDim);
  addItem(pCb, commentBothTextArea, 1, 0);

  QGroupBox* pCp = new QGroupBox();
  //pCp.setBorder(BorderFactory.createTitledBorder(Bundle.getMessage("CommentPickup")));
  pCp->setStyleSheet(gbStyleSheet);
  pCp->setTitle(tr("Comment when there is only pick ups"));
  pCp->setLayout(new GridBagLayout());
  //commentPickupScroller.setMinimumSize(minScrollerDim);
  addItem(pCp, commentPickupTextArea, 1, 0);

  QGroupBox* pCs = new QGroupBox();
  //pCs.setBorder(BorderFactory.createTitledBorder(Bundle.getMessage("CommentSetout")));
  pCs->setStyleSheet(gbStyleSheet);
  pCs->setTitle(tr("Comment when there is only set outs"));
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
